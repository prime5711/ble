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

//  코드 범위          UTF-8                             표현 설명
//  000000-00007F   0xxxxxxx                            : ASCII와 동일한 범위
//  000080-0007FF   110xxxxx 10xxxxxx                   : 첫 바이트는 110 또는 1110으로 시작하고, 나머지 바이트들은 10으로 시작함
//  000800-00FFFF   1110xxxx 10xxxxxx 10xxxxxx          : 첫 바이트는 110 또는 1110으로 시작하고, 나머지 바이트들은 10으로 시작함
//  010000-10FFFF   11110zzz 10zzxxxx 10xxxxxx 10xxxxxx : UTF-8로 표시된 비트 패턴은 실제 코드 포인트와 동일하다.

#define UTF8_MASK_ASCII  0x80

#define UTF8_MASK_LATIN1 0xe0
#define UTF8_MASK_LATIN2 0xc0
#define UTF8_HEAD_LATIN1 0xc0

#define UTF8_MASK_HAN1   0xf0
#define UTF8_MASK_HAN2   0xc0
#define UTF8_MASK_HAN3   0xc0

#define UTF8_HEAD_HAN1   0xe0
#define UTF8_HEAD_2      0x80

//  #define CONVERT_to_LATIN(a,b)      (( ((((a&0x1f)<<4) & 0xf0) | (((b&0x3c)>>2) & 0x0f) ) << 8 )  | \
//  				                    ( ((((b&0x03)<<6) & 0xc0) | (((c&0x3f)>>0) & 0x3f) ) << 0 )  )

#define CONVERT_to_HANCODE(a,b,c)  (( ((((a&0x0f)<<4) & 0xf0) | (((b&0x3c)>>2) & 0x0f) ) << 8 )  | \
				                    ( ((((b&0x03)<<6) & 0xc0) | (((c&0x3f)>>0) & 0x3f) ) << 0 )  )


unsigned char str_utf8[] = "가각:안녕하세요? 조승훈입니다. shcho@genexon.co.kr\0";
unsigned short array_unicode[100] ;

//  unsigned short unicode[10] = { 0xAC00, 0xAC01, 0xAC02, 0xAC03, 0xAC04, 0x0031, 0x0032, 0xA321, 0x0065, 0x000d };

int convert_to_unicode(unsigned char *string,unsigned short *unicode_array)
{
	int i = 0 ;
	char tmp_buf[4];
	int count_unicode = 0 ;

	for( i = 0 ; i < strlen(string) ; )
	{
		memset(tmp_buf,0,sizeof(tmp_buf));
		if( (string[i] & UTF8_MASK_ASCII) == 0x00)
		{
			memcpy(tmp_buf, &string[i], 1); printf("(%2d)char is ascii   (%s)\n", count_unicode,tmp_buf); 
			i += 1 ;
			unicode_array[count_unicode] = string[i];
		}
		if( (string[i] & UTF8_MASK_LATIN1) == 0xc0)
		{
			memcpy(tmp_buf, &string[i], 2); printf("(%2d)char is Latin   (%s)\n", count_unicode,tmp_buf); 
			i += 2 ;
			printf("Bad Character\n");
			printf("Bad Character\n");
			printf("Bad Character\n");
			printf("Bad Character\n");
		}
		if( (string[i] & UTF8_MASK_HAN1) == 0xe0)
		{
			memcpy(tmp_buf, &string[i], 3); printf("(%2d)char is HAN     (%s) ", count_unicode,tmp_buf); 
			i += 3 ;
			unicode_array[count_unicode] = (unsigned short)CONVERT_to_HANCODE(string[i+0], string[i+1], string[i+2]);
			printf("(%2d):%04x(%02x %02x %02x) \n", count_unicode, unicode_array[count_unicode], string[i+0],string[i+1], string[i+2]);
		}
		count_unicode++;
	}
	printf("\n");

	for(i = 0 ; i < count_unicode ; i++)
	{
		printf("(%2d):%04x \n", i, unicode_array[i]);
	}
	printf("\n");

	return count_unicode;
}

int main(int argc, char *argv[])
{
	int ret;
	struct termios  oldtio,
	                newtio;
	char *end_ptr;
	int packet_len;
	int stdin_count;
	int i = 0 ;

	char tmp_buf[4];

	int count_unicode;
	
	
	printf("str_utf8=%s\n", str_utf8);

	memset(array_unicode,0,sizeof(array_unicode));
	count_unicode = convert_to_unicode(str_utf8, array_unicode);
	printf("글자수=%d.\n",count_unicode);



}







