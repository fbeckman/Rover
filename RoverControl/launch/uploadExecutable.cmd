REM Upload to ROSberryPi
..\Tools\plink -ssh pi@ROSberryPi -pw pilot6301 /home/pi/stop
..\Tools\pscp.exe -p -pw pilot6301 .\RaspberryPi\RoverControl pi@ROSberryPi:/usr/local/bin/rovercontrol
..\Tools\plink -ssh pi@ROSberryPi -pw pilot6301 /home/pi/start