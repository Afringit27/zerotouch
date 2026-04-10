import serial
import tkinter as tk

ser = serial.Serial('COM5',115200)

root = tk.Tk()
root.title("Zero Touch AI Safety System")
root.geometry("420x350")

title = tk.Label(root,text="AI Safety Monitor",font=("Arial",18,"bold"))
title.pack(pady=10)

sound_label = tk.Label(root,text="Sound:",font=14)
sound_label.pack()

vib_label = tk.Label(root,text="Vibration:",font=14)
vib_label.pack()

acc_label = tk.Label(root,text="Acceleration:",font=14)
acc_label.pack()

hr_label = tk.Label(root,text="Heart Rate:",font=14)
hr_label.pack()

status_label = tk.Label(root,text="Status:",font=("Arial",18,"bold"))
status_label.pack(pady=20)

def update():

    if ser.in_waiting:

        line = ser.readline().decode().strip()

        parts = line.split(",")

        for part in parts:

            if "SOUND" in part:
                sound_label.config(text="Sound: "+part.split(":")[1])

            elif "VIB" in part:
                vib_label.config(text="Vibration: "+part.split(":")[1])

            elif "ACC" in part:
                acc_label.config(text="Acceleration: "+part.split(":")[1])

            elif "HR" in part:
                hr_label.config(text="Heart Rate: "+part.split(":")[1]+" bpm")

            elif "STATUS" in part:

                status = part.split(":")[1]

                status_label.config(text="Status: "+status)

                if status=="DANGER":
                    status_label.config(fg="red")
                    root.bell()   # laptop alert sound
                else:
                    status_label.config(fg="green")

    root.after(700,update)

update()

root.mainloop()