#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char buf[1024] ;

	memset(buf,0,sizeof(buf));
 	sprintf(buf,"echo \"birth_year=%d\r\n\" > %s" ,70+1900, "test_str.txt");   
	system(buf);

	return 1;

}
