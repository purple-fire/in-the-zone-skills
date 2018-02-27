/**
 * Functions for controlling the lift, during both driver control and
 * autonomous.
 */

#include "liftControl.h"
#include "pid.h"
#include "utilities.h"

int liftToggle = false;
int desiredLiftAngle = LIFT_UP;
int liftPosition;

void liftControl(void *parameter)
{
    // Separate variables to simplify tuning
    const float kp = 0.2;
    const float ki = 0.001; //0.7;
    const float kd = 0.0;

    PIDData data;
    pidDataInit(&data, kp, ki, kd, 125, 4095, 50);

    while (true)
    {
        if (liftToggle)
        {
            liftPosition = analogReadCalibrated(POTENTIOMETER_PORT);
            int errorLiftAngle = desiredLiftAngle - liftPosition;
            int liftPowerOut = pidNextIteration(&data, errorLiftAngle);

            motorSet (liftMotor,liftPowerOut);
        }
        else
        {
            motorStop(liftMotor);
        }

        delay(20);
    }
}

void setLiftAngle(int liftAngle)
{
    desiredLiftAngle = liftAngle;
}
