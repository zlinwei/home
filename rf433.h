#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>


int sendCommand(char* ser,int addr1,int addr2,int cmd)
{
	int fd;
	if((fd = serialOpen(ser,9600))<0)
        {
                fprintf(stderr,"Unable to open Serial:%s\n",strerror(errno));
                return 1;
        }
	if(wiringPiSetup()==-1)
        {
                fprintf(stdout,"Unable to start wiringPi:%s\n",strerror(errno));
                return 1;
        }

	serialPutchar(fd,0xfd);
        serialPutchar(fd,0x03);
        serialPutchar(fd,addr1);
        serialPutchar(fd,addr2);
        serialPutchar(fd,cmd);
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
