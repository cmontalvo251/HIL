#include "RCOutput.h"

//constructor class
RCOutput::RCOutput() {
}

//Init routine
void RCOutput::initialize(int num) {
	NUMSIGNALS = num;
	pwmcomms = (int *) calloc(NUMSIGNALS,sizeof(int));
	//Initialize channels
	for (int i = 0;i<NUMSIGNALS;i++) {
		printf("Initializing PWM Output = %d \n",i);
	}
}

//Write function
void RCOutput::write() {
	//Write the pwm signals in comms but only loop until comms.getRow()
	for (int i = 0;i<NUMSIGNALS;i++) {
		int us = pwmcomms[i];
		//printf("Sending PWM signal to channel = %d \n",i);
	} 
}
