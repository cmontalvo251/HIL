#include "ADC.h"

ADC::ADC() {
	printf("Initializing ADC \n");	
	#ifndef DESKTOP
	initialize();
	#else
	//On Desktop we don't need to initialize the channels
	printf("Using DESKTOP configuration so no initialization required \n");
	#endif
	channel_count = get_channel_count();
	printf("ADC Channel Count = %d \n",channel_count);
	//Now we create a MATLAB vector
	results.zeros(channel_count,1,"ADC Results");
}

void ADC::initialize()
{
    for (size_t i = 0; i < ARRAY_SIZE(channels); i++) {
        channels[i] = open_channel(i);
        if (channels[i] < 0) {
            perror("open");
        }
    }
}

int ADC::get_channel_count(void)
{
    return CHANNEL_COUNT;
}

int ADC::read(int ch)
{
    if (ch > ARRAY_SIZE(channels) )
	{
        fprintf(stderr,"Channel number too large\n");
        return -1;
	}
    char buffer[10];

    #ifndef DESKTOP
    //Only actually read the buffer if we're running on hardware
    if (::pread(channels[ch], buffer, ARRAY_SIZE(buffer), 0) < 0) {
        perror("pread");
    }
    return atoi(buffer);
    #else
    //Otherwise we just set all the values to -99 for now
    return -99;
    #endif
}

int ADC::open_channel(int channel)
{
    char *channel_path;
    if (asprintf(&channel_path, "%s/ch%d", ADC_SYSFS_PATH, channel) == -1) {
        err(1, "adc channel: %d\n", channel);
    }

    int fd = ::open(channel_path, O_RDONLY);

    free(channel_path);

    return fd;
}

void ADC::get_results() {
	for (int i = 0; i < channel_count; i++)
        {
            results.set(i+1,1,read(i)/1000.0);
        }
}

void ADC::print_results() {
	printf(" ADC = ");
	for (int i = 0;i < channel_count;i++) {
		printf("%lf ",results.get(i+1,1));
	}
}

