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

#define CONVERT_to_UNICODE_HANRegion(a,b,c)  (( ((((a&0x0f)<<4) & 0xf0) | (((b&0x3c)>>2) & 0x0f) ) << 8 )  | \
				                              ( ((((b&0x03)<<6) & 0xc0) | (((c&0x3f)>>0) & 0x3f) ) << 0 )  )

// MUST: should be char : not unsigned char
unsigned char str_utf8[] = "조승훈:가각:안녕하세요? 조승훈입니다. shcho@genexon.co.kr";
unsigned short array_unicode[100] ;

//  unsigned short unicode[10] = { 0xAC00, 0xAC01, 0xAC02, 0xAC03, 0xAC04, 0x0031, 0x0032, 0xA321, 0x0065, 0x000d };
int convert_to_utf8(unsigned short *unicode_array, unsigned char *string)
{
	int i ;
	int num_of_convert  ;
	int str_index  ;

	num_of_convert = 0 ;
	str_index = 0 ;

	for( i = 0 ; ; i++)
	{
		if( unicode_array[i] == 0)
			break;

		if( (unicode_array[i] >=0x00) && ( unicode_array[i] <= 0x7f ))
		{
			string[str_index] = (unsigned char)(unicode_array[i] & 0x00ff);
//  			printf("ascii region:%02x\n",string[str_index]);
			str_index += 1;
		}
		if( (unicode_array[i] >=0x80) && ( unicode_array[i] <= 0x7ff ))
		{
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
		}
		if( (unicode_array[i] >=0x800) && ( unicode_array[i] <= 0xffff ))
		{
			//  000800-00FFFF   1110xxxx 10xxxxxx 10xxxxxx          : 첫 바이트는 110 또는 1110으로 시작하고, 나머지 바이트들은 10으로 시작함
			string[str_index+0] =  (0xe0 | (unsigned char)((unicode_array[i] & 0xf000)>>12)) ;
			string[str_index+1] =  (0x80 | (unsigned char)((unicode_array[i] & 0x0fc0)>> 6)) ;
			string[str_index+2] =  (0x80 | (unsigned char)((unicode_array[i] & 0x003f)>> 0)) ;
//  			printf("han  region:%02x %02x %02x\n",string[str_index], string[str_index+1], string[str_index+2]);
			str_index += 3 ; 
		}
		num_of_convert++;
	}	

	return num_of_convert;
}

int convert_to_unicode(unsigned char *string,unsigned short *unicode_array)
{
	int i = 0 ;
	char tmp_buf[4];
	int count_unicode = 0 ;
	int string_length=0;

	string_length = strlen((const char*)string);

	for( i = 0 ; i < string_length ; )
	{
		memset(tmp_buf,0,sizeof(tmp_buf));

		if( (string[i] & UTF8_MASK_ASCII) == 0x00)
		{
			unicode_array[count_unicode++] = string[i];

//  //  			memcpy(tmp_buf, &string[i], 1); printf("(%2d)char is ascii   (%s)  ", count_unicode,tmp_buf); 
			INNO_SHCHO_PRINT("(%2d):%04x(%02x) \n", count_unicode, unicode_array[count_unicode], string[i+0]);

			//여기서 증가시키면 다음 조건문에서 다시 check된다.
			//그래서 count_unicode를 넣을때 증가시켜야 한다.
			i += 1 ;
		}

		if( (string[i] & UTF8_MASK_LATIN1) == 0xc0)
		{
//  //  			memcpy(tmp_buf, &string[i], 2); printf("(%2d)char is Latin   (%s)\n", count_unicode,tmp_buf); 
			i += 2 ;
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
			printf("Bad Character: Not Supported\n");
		}

		if( (string[i] & UTF8_MASK_HAN1) == 0xe0)
		{
			unicode_array[count_unicode++] = (unsigned short)CONVERT_to_UNICODE_HANRegion(string[i+0], string[i+1], string[i+2]);

//  //  			memcpy(tmp_buf, &string[i], 3); printf("(%2d)char is HAN     (%s) ", count_unicode,tmp_buf); 
			INNO_SHCHO_PRINT("(%2d):%04x(%02x %02x %02x) \n", count_unicode, unicode_array[count_unicode], string[i+0],string[i+1], string[i+2]);

			i += 3 ;
			continue;
		}

	}
	INNO_SHCHO_PRINT("\n");

	for(i = 0 ; i < count_unicode ; i++)
	{
		INNO_SHCHO_PRINT("(%2d):%04x \n", i, unicode_array[i]);
	}
	INNO_SHCHO_PRINT("\n");

	return count_unicode;
}

int main(int argc, char *argv[])
{
	unsigned char tmp_utf8_buffer[300];

	int count_unicode;
	int num_of_convert ; 
	
	


	printf("     str_utf8:%s\n", str_utf8);

	memset(array_unicode,0,sizeof(array_unicode));

	count_unicode  = convert_to_unicode(str_utf8     ,array_unicode);
	num_of_convert = convert_to_utf8   (array_unicode,tmp_utf8_buffer);

	printf("글자수=%d.\n",count_unicode);

	if( count_unicode != num_of_convert )
	{
		printf("Conversion Error\n");
	}
	printf("converted str:%s\n",tmp_utf8_buffer);

	return 1 ;

}







