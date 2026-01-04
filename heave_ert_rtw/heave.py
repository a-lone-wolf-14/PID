import serial
import time
import pandas as pd
import numpy as np
from scipy.interpolate import interp1d
from heave_rt import Heave   # ✅ matches wrapper.cpp

# ================= CONFIG =================
PORT = "COM6"
BAUD = 115200

HEAVE_GOAL = 0.0
CONTROL_PERIOD = 0.2

PWM_NEUTRAL = 1500
PWM_MIN = 1100
PWM_MAX = 1900

SUPPLY_VOLTAGE = 14.0

LOG_FILE = "heave_pid_log.txt"
EXCEL_FILE = "T200.xlsx"
# ==========================================

# ---------- Load thrust table ----------
df = pd.read_excel(EXCEL_FILE)

PWM = df["PWM"].to_numpy()

thrust_data = {}
voltages = []

for col in df.columns:
    if col.startswith("Thrust_"):
        v = float(col.replace("Thrust_", "").replace("V", ""))
        thrust_data[v] = df[col].to_numpy()
        voltages.append(v)

voltages = np.array(sorted(voltages))


# ---------- Thrust vs Voltage ----------
def thrust_at_voltage(voltage):
    thrust_matrix = np.array([thrust_data[v] for v in voltages])

    thrust_interp = [
        interp1d(
            voltages,
            thrust_matrix[:, i],
            kind="linear",
            fill_value="extrapolate"
        )
        for i in range(len(PWM))
    ]

    return np.array([f(voltage) for f in thrust_interp])


# ---------- SAFE Thrust → PWM ----------
def thrust_to_pwm(desired_thrust, voltage):
    thrust_curve = thrust_at_voltage(voltage)

    # 🔒 Saturation (positive & negative)
    max_thrust = np.max(thrust_curve)
    min_thrust = np.min(thrust_curve)

    desired_thrust = np.clip(desired_thrust, min_thrust, max_thrust)

    pwm_interp = interp1d(
        thrust_curve,
        PWM,
        kind="linear",
        bounds_error=False,
        fill_value=(PWM_MIN, PWM_MAX)
    )

    pwm = float(pwm_interp(desired_thrust))
    return int(np.clip(pwm, PWM_MIN, PWM_MAX))


# ---------- Serial parse ----------
def parse_ptd(line):
    try:
        p, t, d = map(float, line.split("/"))
        return p, t, d
    except Exception:
        return None


# ---------- Main ----------
def main():
    ser = serial.Serial(PORT, BAUD, timeout=1)

    pid = Heave()
    pid.initialize()   # ✅ lifecycle function

    print("\nLive Heave PID Control Running... (CTRL+C to stop)\n")

    with open(LOG_FILE, "w") as log:
        log.write("Depth,Pressure,Temperature,PWM_FL,PWM_FR,PWM_BL,PWM_BR\n")
        last_time = time.time()

        pwm = {"FL": 1500, "FR": 1500, "BL": 1500, "BR": 1500}

        while True:
            line = ser.readline().decode("ascii", errors="ignore").strip()
            if not line:
                continue

            data = parse_ptd(line)
            if data is None:
                continue

            pressure, temperature, depth = data

            now = time.time()
            if now - last_time >= CONTROL_PERIOD:
                last_time = now

                if abs(depth - HEAVE_GOAL) > 0.1:
                    pid.set_inputs(HEAVE_GOAL, depth)
                    pid.step()       # base rate
                    pid.step1()      # subrate (optional but recommended)

                    out = pid.outputs()

                    pwm["FL"] = thrust_to_pwm(out["FL"], SUPPLY_VOLTAGE)
                    pwm["FR"] = thrust_to_pwm(out["FR"], SUPPLY_VOLTAGE)
                    pwm["BL"] = thrust_to_pwm(out["BL"], SUPPLY_VOLTAGE)
                    pwm["BR"] = thrust_to_pwm(out["BR"], SUPPLY_VOLTAGE)

                log.write(
                    f"{depth},{pressure},{temperature},"
                    f"{pwm['FL']},{pwm['FR']},{pwm['BL']},{pwm['BR']}\n"
                )
                log.flush()

                print(
                    f"Depth={depth:.2f} m | "
                    f"P={pressure:.1f} Pa | "
                    f"T={temperature:.2f} C | "
                    f"PWM: {pwm['FL']} {pwm['FR']} {pwm['BL']} {pwm['BR']}"
                )


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("\nStopped.")
