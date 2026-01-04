import time
import math
import pandas as pd
import numpy as np
from scipy.interpolate import interp1d
import sys
sys.path.append("../heave_ert_rtw")
from vectornav import Sensor, Registers
from roll_ctrl import RollController   # ✅ CORRECT MODULE
from heave_rt import Heave
import serial
# ================= OFFSETS =================
OFFSET_ROLL = 0.0
OFFSET_P = 0.0
offset_set = False

# ================= CONFIG =================
PORT = "/dev/ttyUSB0"
INPUT = "/dev/ttyS4"
OUT = "/dev/ttyS4"
BAUD = 115200

RATE_HZ = 100
DT = 1.0 / RATE_HZ

ROLL_GOAL = 0.0          # radians
SUPPLY_VOLTAGE = 14.0

PWM_MIN = 1100
PWM_MAX = 1900

LOG_FILE = "roll_pid_log.csv"
EXCEL_FILE = "T200.xlsx"
# ==========================================


# ================= THRUSTER MODEL =================
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
thrust_matrix = np.array([thrust_data[v] for v in voltages])

# Prebuild interpolation (FAST)
thrust_interp_voltage = [
    interp1d(
        voltages,
        thrust_matrix[:, i],
        kind="linear",
        fill_value="extrapolate",
    )
    for i in range(len(PWM))
]

def thrust_at_voltage(voltage):
    return np.array([f(voltage) for f in thrust_interp_voltage])


def thrust_to_pwm(desired_thrust, voltage):
    thrust_curve = thrust_at_voltage(voltage)

    # 🔒 SAFE SATURATION
    max_thrust = np.max(thrust_curve)
    min_thrust = np.min(thrust_curve)
    desired_thrust = np.clip(desired_thrust, min_thrust, max_thrust)

    pwm_interp = interp1d(
        thrust_curve,
        PWM,
        bounds_error=False,
        fill_value=(PWM_MIN, PWM_MAX),
    )

    pwm = float(pwm_interp(desired_thrust))
    return int(np.clip(pwm, PWM_MIN, PWM_MAX))

def parse_ptd(line):
    try:
        p, t, d = map(float, line.split("/"))
        return p, t, d
    except Exception:
        return None


# ================= IMU =================
sensor = Sensor()

ypr_reg = Registers.Attitude.YawPitchRoll()
gyro_reg = Registers.IMU.Gyro()


def read_gyro():
    """
    Returns:
        roll (rad)
        p    (rad/s)
    """
    sensor.readRegister(ypr_reg)
    sensor.readRegister(gyro_reg)

    roll = math.radians(ypr_reg.roll)
    p = gyro_reg.gyroX

    return roll, p


# ================= MAIN =================
def main():
    global offset_set, OFFSET_ROLL, OFFSET_P

    print("Connecting to VN-100...")
    sensor.connect(PORT, BAUD)
    print("VN-100 connected")
    ser = serial.Serial(OUT, BAUD, timeout=1)

    # ---- Roll Controller (wrapper initializes model internally) ----
    pid = RollController()

    with open(LOG_FILE, "w") as log:
        log.write("Roll,P,FL,FR,BL,BR\n")

        try:
            while True:
                if not offset_set:
                    OFFSET_ROLL, OFFSET_P = read_gyro()
                    offset_set = True
                    print(
                        f"Offset set: Roll={math.degrees(OFFSET_ROLL):.2f}°, "
                        f"P={OFFSET_P:.3f} rad/s"
                    )
                    continue
                line = ser2.readline().decode("ascii", errors="ignore").strip()
                if not line:
                    continue
                
                data = parse_ptd(line)
                if data is None:
                    continue
                pressure, temperature, depth = data

                heave_pid.set_inputs(0.5,depth)
                heave_pid.step()
                heave_pid.step1()
                out_heave = heave_pid.outputs()

                T_heave = (out_heave["FL"] + out_heave["FR"] + out_heave["BL"] + out_heave["BR"])/4.0
                t0 = time.time()

                # ---- IMU ----
                roll_imu, p_imu = read_gyro()
                roll_rel = roll_imu - OFFSET_ROLL
                p_rel = p_imu - OFFSET_P

                pwm = {"FL": 1500, "FR": 1500, "BL": 1500, "BR": 1500}

                if abs(ROLL_GOAL - roll_rel) > 0.01:
                    pid.set_inputs(
                        ROLL_GOAL,
                        roll_rel,
                        p_rel,
                        T_heave       # heave input (set to 0 unless coupled)
                    )

                    # Wrapper handles 1 kHz base + 100 Hz subrate internally
                    for _ in range(10):   # simulate 1 kHz
                        pid.step()

                    out = pid.outputs()

                    pwm["FL"] = thrust_to_pwm(out["FL"], SUPPLY_VOLTAGE)
                    pwm["FR"] = thrust_to_pwm(out["FR"], SUPPLY_VOLTAGE)
                    pwm["BL"] = thrust_to_pwm(out["BL"], SUPPLY_VOLTAGE)
                    pwm["BR"] = thrust_to_pwm(out["BR"], SUPPLY_VOLTAGE)

                # ---- Logging ----
                log.write(
                    f"{roll_imu:.6f},{p_imu:.6f},"
                    f"{pwm['FL']},{pwm['FR']},{pwm['BL']},{pwm['BR']}\n"
                )
                log.flush()

                print(
                    f"Roll={math.degrees(roll_rel):+.2f}° | "
                    f"FL={pwm['FL']} FR={pwm['FR']} "
                    f"BL={pwm['BL']} BR={pwm['BR']}"
                )

                out_str=(f"{pwm['BL']}/{pwm['FR']}/1500/1500/{pwm['BR']}/{pwm['FL']}/1500/1500\n")
                ser.write(out_str.encode())
                ser.flush()
                # ---- Timing ----
                sleep = DT - (time.time() - t0)
                if sleep > 0:
                    time.sleep(sleep)

        except KeyboardInterrupt:
            print("\nStopping controller...")

        finally:
            sensor.disconnect()
            ser.close()
            print("VN-100 disconnected")


if __name__ == "__main__":
    main()
