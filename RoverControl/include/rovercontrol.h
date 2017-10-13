#ifndef ROVERCONTROL_H
#define ROVERCONTROL_H
#ifdef __cplusplus
extern "C" {
#endif
extern int rovercontrolSetup();
extern void setPortTo0(int port);
extern void setPortTo1(int port);
extern int getPortValue(int port);
extern void setServo(int channel, int degree);
extern int getDistanceInCm(int trig, int echo);
extern int getSpeedValue();
extern int getFrontSteeringValue();
extern int getRearSteeringValue();
extern int getExternalCommand();
#ifdef __cplusplus
}
#endif
#endif /* ROVERCONTROL_H */

