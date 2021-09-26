#include <RCIO/RCOutput.h>

RCOutput rcout; //this calls the constructor which does nothing

int main() {

	//You then need to initialize the pwm ports 
	rcout.initialize(2); //The default is 9 pwm signals

	int output = OUTMIN;
	int i = 0;
	while (1) {
		printf("i = %d ",i);
		//Add 100 to signal
		output += 100;
		if (output > OUTMAX) {
			output = OUTMIN;
		}
		//Set every value in matrix to output
		for (int j = 0;j<rcout.NUMSIGNALS;j++) {
			rcout.pwmcomms[j] = output;
			printf("%d ",output);
		}
		rcout.write();
		printf("\n");
		i++;
		usleep(1000000);
	}
	return 0;
};