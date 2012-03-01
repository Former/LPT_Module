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
	
	char buf[] = {0x1, 0x5, 0x4, 0x6, 0x2, 0xA, 0x8, 0x9};
	//char buf[] = {0x5, 0x6, 0xA, 0x9};
	//char buf[] = {0x1, 0x4, 0x2, 0x8};
	
	for (int k = 0; k < 100; k++)
	for(int i = 0; i < 2000 ; i++)
	{		
		const char signal = 1 << 4;
		
		bool rotate = k % 2;
		int bufInd = rotate ? (i % sizeof(buf)) : (sizeof(buf) - 1 - i % sizeof(buf));
		char wBuf = signal | buf[bufInd];

		write(fd, &wBuf, 1);
		int sl = 50000;
		usleep(sl * ((sizeof(buf) == 8) ? 1 : 2));
	}

	// Clear output
	char wBuf = 0;
	write(fd, &wBuf, 1);
	close(fd);
	return 0;
}
