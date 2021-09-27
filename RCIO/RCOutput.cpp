#include "RCOutput.h"

//constructor class
RCOutput::RCOutput() {
}

//Init routine
void RCOutput::initialize(int num) {
	NUMSIGNALS = num;
	pwmcomms = (int *) calloc(NUMSIGNALS,sizeof(int));

	////////I REALIZE THERE ARE 3 LOOPS AND YOU COULD DO THIS WITH
	// 1 loop. BUT IT WILL NOT WORK. JUST TRUST ME. Dr. C 9/27/2021
	
	//Initialize channels
	for (int i = 0;i<NUMSIGNALS;i++) { 
	  printf("Initializing PWM Output = %d \n",i);
	  if(!(pwm.init(i))) {
	    exit(1);
	  }
	}
	//INITIALIZE FREQUENCY
	for (int i = 0;i<NUMSIGNALS;i++) { 
	  printf("Setting Frequency of %d Servo \n",i);
	  pwm.set_period(i, 50);
	  if (!(pwm.enable(i))) {
	    exit(1);
	  }
	}
	//SET INITIAL DUTY CYCLE
	for (int i = 0;i<NUMSIGNALS;i++) { 
	  printf("Running Servo Start of %d servo \n",i);
	  pwm.set_duty_cycle(i,OUTMIN/1000);
	}
}

//Write function
void RCOutput::write() {
  //Write the pwm signals in comms but only loop until comms.getRow()
  for (int i = 0;i<NUMSIGNALS;i++) {
    float us = pwmcomms[i];
    //printf("Sending PWM signal to channel = %d \n",i);
    pwm.set_duty_cycle(i,us/1000.0);
  } 
}
