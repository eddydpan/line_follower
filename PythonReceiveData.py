import serial
import pandas as pd
import matplotlib.pyplot as plt

arduinoComPort = "/dev/ttyACM0"
baudRate = 9600
serialPort = serial.Serial(arduinoComPort, baudRate, timeout=1)

serialOutputs = [] # In the form of a tuple with (leftIR, rightIR, leftMotorVel, rightMotorVel)
num_timesteps = 0 # Initialize at 1

leftIRs = []
rightIRs = []
leftMotorVels = []
rightMotorVels = []
try:
  while True:

    lineOfData = serialPort.readline().decode().strip()
    if len(lineOfData) > 0:
      print(lineOfData)
      
      data = lineOfData.split(",") 
      if len(data) == 4:
        leftIRs.append(int(data[0]))
        rightIRs.append(int(data[1]))
        leftMotorVels.append(int(data[2]))
        rightMotorVels.append(int(data[3]))
        num_timesteps += 1

except KeyboardInterrupt:
  timesteps = range(num_timesteps)
  data = {
    'Timesteps': timesteps,
    'Left IRs' : leftIRs,
    'Right IRs' : rightIRs,
    'Left Motor Speeds' : leftMotorVels,
    'Right Motor Speeds' : rightMotorVels
  }


  df = pd.DataFrame(data)
  df.to_csv("LineFollowerData.csv")
  fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True)

  ax1.plot(timesteps, leftIRs)
  ax1.plot(timesteps, rightIRs)
  ax1.set_ylabel('Analog Voltage')
  ax1.legend()

  # Plot the second dataset on the bottom subplot
  ax2.plot(timesteps, leftMotorVels)
  ax2.plot(timesteps, rightMotorVels)
  ax2.set_xlabel('Timesteps')
  ax2.set_ylabel('DC Motor Velocity')
  ax2.legend()


  fig.suptitle('Motor Commands + IR Readings Over Time', fontsize=10)
  plt.show()