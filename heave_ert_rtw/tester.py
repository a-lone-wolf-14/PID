import serial
import time
import math

# ================= CONFIG =================
PORT = "/dev/ttyUSB0"        # change if needed
BAUD = 115200
SEND_PERIOD = 0.1    # seconds
# ==========================================

def main():
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print(f"Sending test PTDA data on {PORT} @ {BAUD} baud")
    print("Format: pressure/temperature/depth\n")

    start_time = time.time()

    try:
        while True:
            t = time.time() - start_time

            # ---- Fake sensor data ----
            pressure = 101325 + 1000 * math.sin(0.2 * t)     # Pa
            temperature = 25.0 + 0.5 * math.sin(0.1 * t)     # °C
            depth = 1.5 + 0.5 * math.sin(0.3 * t)            # meters

            line = f"{pressure:.2f}/{temperature:.2f}/{depth:.3f}\n"

            ser.write(line.encode("ascii"))
            ser.flush()

            print("Sent:", line.strip())

            time.sleep(SEND_PERIOD)

    except KeyboardInterrupt:
        print("\nStopped sender.")
    finally:
        ser.close()

if __name__ == "__main__":
    main()
