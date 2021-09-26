#ifndef RCOUTPUT_H
#define RCOUTPUT_H

//#include "PWM.h" //Not yet
#include <unistd.h> //This is for sleep()
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>

#define OUTMIN 600
#define OUTMAX 2400

class RCOutput {
public:
    RCOutput(); //constructor
    bool init_channel(int channel);
    bool enable(int channel);
    bool set_frequency(int channel, float frequency);
    bool set_duty_cycle(int channel, float period);
    void initialize(int);
    void write();
    int *pwmcomms=NULL;
    int NUMSIGNALS;
private:
    //PWM pwm; not yet
};

#endif // RCOUTPUT_H