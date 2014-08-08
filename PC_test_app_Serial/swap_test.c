#include <stdio.h>

//  #include <sys/select.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <signal.h>

// shcho for select
// #include <stdio.h>
// #include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
// #include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define DEBUG
#ifdef DEBUG
#define INNO_SHCHO_PRINT(fmt, args...)	fprintf(stdout, fmt, ## args)
#else
#define INNO_SHCHO_PRINT(fmt, args...)	
#endif



#define swap16(a)	( ((a >> 8) & 0x00ff) | ((a << 8) & 0xff00) )
#define SHORT_INT_HIGH(a) (( a >> 8 ) & 0x00ff)
#define SHORT_INT_LOW(a)  (( a >> 0 ) & 0x00ff)

int main(int argc, char *argv[])
{
	unsigned short bit16 = 0x1234;

	printf("org:%4x, swap16 : %04x, high:%02x low:%02x \n", bit16, swap16(bit16), SHORT_INT_HIGH(bit16), SHORT_INT_LOW(bit16));
	return -1;
}


