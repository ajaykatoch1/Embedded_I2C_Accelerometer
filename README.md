# Embedded_I2C_Accelerometer
In this project, we implemented an adxl1345 accelerometer on an ATmega2560 arduino board utilizing the I2C communication protocol. 
The speed of an attached motor to the board could be measured in the x,y, or z axis with accurate results. We utilized C/C++ in VSCODE and platform.io. 
The included requirements pdf goes into more detail about the requirements and how I2C and the board was created and implemented. We also utilized a bread board circuit to hook up
the adxl1345 properly to the ATmega2560. The l293 Integrated circuit (IC) by Texas Instruments was also used to send bidirectional current
to the motor, once this occured then the accelerometer could measre the speed using the I2C protcol integrated from software. 
