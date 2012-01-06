#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

int main(int a_ArgCount, char* a_ArgValue[])
{
	int fd = open("/dev/lpt_data", O_WRONLY);
	
	if (fd < 0)
	{
		printf("Error open file\n");
		return -1;
	}
	
	for(int i = 0; i < 1000; i++)
	{
		char wBuf = 0xFF;
		write(fd, &wBuf, 1);
		printf("Write %x\n", wBuf);
		sleep(1);
	}
	close(fd);
	return 0;
}
