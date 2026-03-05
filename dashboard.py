import serial
import tkinter as tk

ser = serial.Serial('COM5', 115200)

root = tk.Tk()
root.title("Zero-Touch Safety Dashboard")
root.geometry("400x300")

sound_label = tk.Label(root, text="Sound: --", font=("Arial", 14))
sound_label.pack(pady=5)

vib_label = tk.Label(root, text="Vibration: --", font=("Arial", 14))
vib_label.pack(pady=5)

acc_label = tk.Label(root, text="Acceleration: --", font=("Arial", 14))
acc_label.pack(pady=5)

status_label = tk.Label(root, text="Status: --", font=("Arial", 16, "bold"))
status_label.pack(pady=10)

def update():
    if ser.in_waiting:
        data = ser.readline().decode().strip()
        parts = data.split(",")

        for part in parts:
            if "SOUND" in part:
                sound_label.config(text="Sound: " + part.split(":")[1])
            if "VIB" in part:
                vib_label.config(text="Vibration: " + part.split(":")[1])
            if "ACC" in part:
                acc_label.config(text="Acceleration: " + part.split(":")[1])
            if "STATUS" in part:
                status = part.split(":")[1]
                status_label.config(text="Status: " + status)

                if status == "DANGER":
                    status_label.config(fg="red")
                else:
                    status_label.config(fg="green")

    root.after(500, update)

update()
root.mainloop()