#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>


int main(int argc,char* argv[])
{
	int fd;
	int add1=0x01,add2=0x01,command=0x01;

	if(argc>3)
	{
		add1=atoi(argv[1]);
		add2=atoi(argv[2]);
		command=atoi(argv[3]);
	}
	
	printf("0x%x 0x%x 0x%x\n",add1,add2,command);
	fflush(stdout);
		
	unsigned int nextTime;

	if((fd = serialOpen("/dev/ttyUSB0",9600))<0)
	{
		fprintf(stderr,"Unable to open Serial:%s\n",strerror(errno));
		return 1;	
	}

	if(wiringPiSetup()==-1)
	{
		fprintf(stdout,"Unable to start wiringPi:%s\n",strerror(errno));
		return 1;
	}

	nextTime = millis() + 300;
	serialPutchar(fd,0xfd);
	serialPutchar(fd,0x03);
	serialPutchar(fd,add1);
	serialPutchar(fd,add2);
	serialPutchar(fd,command);
	serialPutchar(fd,0xa0);
	serialPutchar(fd,0xdf);

	while(!serialDataAvail(fd))
	{
	
	}

	while(serialDataAvail(fd))
	{
		printf("0x%x",serialGetchar(fd));
	}	
	printf("\n");
	return 0;
}
