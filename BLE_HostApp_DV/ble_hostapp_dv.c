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
#include <math.h>


#include "HCI_command_event.h"

//  #include <sys/inotify.h>


//  #define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))



#define DEBUG

#ifdef DEBUG
#define INNO_SHCHO_PRINT(fmt, args...)	fprintf(stdout, fmt, ## args)
#else
#define INNO_SHCHO_PRINT(fmt, args...)	
#endif

//  코드 범위          UTF-8                             표현 설명
//      00-    7F   0xxxxxxx                            : ASCII와 동일한 범위
//     080-   7FF   110xxxxx 10xxxxxx                   : 첫 바이트는 110 으로 시작하고, 나머지 바이트들은 10으로 시작함
//    0800-  FFFF   1110xxxx 10xxxxxx 10xxxxxx          : 첫 바이트는 1110으로 시작하고, 나머지 바이트들은 10으로 시작함
//  010000-10FFFF   11110zzz 10zzxxxx 10xxxxxx 10xxxxxx : UTF-8로 표시된 비트 패턴은 실제 코드 포인트와 동일하다.

#define MAX_FULL_NAME_CHAR	32
#define MAX_FULL_NAME_SHORT	(MAX_FULL_NAME_CHAR/sizeof(short))

#define UTF8_MASK_ASCII  0x80

#define UTF8_MASK_LATIN1 0xe0
#define UTF8_MASK_LATIN2 0xc0
#define UTF8_HEAD_LATIN1 0xc0

#define UTF8_MASK_HAN1   0xf0
#define UTF8_MASK_HAN2   0xc0
#define UTF8_MASK_HAN3   0xc0

#define UTF8_HEAD_HAN1   0xe0
#define UTF8_HEAD_2      0x80

#define CONVERT_to_UNICODE_ArabRegion(a,b)  (( ((a&0x1f)<<6) ) | (((b&0x3f)<< 0 ) )) 

#define CONVERT_to_UNICODE_HANRegion(a,b,c)  (( ((((a&0x0f)<<4) & 0xf0) | (((b&0x3c)>>2) & 0x0f) ) << 8 )  | \
				                              ( ((((b&0x03)<<6) & 0xc0) | (((c&0x3f)>>0) & 0x3f) ) << 0 )  )

#define BIA_CHECK_WAIT_SEC	120
// MUST: should be char : not unsigned char
unsigned char str_utf8[] = "조승훈:가각:안녕하세요? 조승훈입니다. shcho@genexon.co.kr";
unsigned short array_unicode[100] ;

#define MODE_READ 	0
#define MODE_WRITE	1
#define MODE_ERASE 	2
int process_mode = MODE_READ ;

int convert_to_utf8(unsigned short *unicode_array, unsigned char *string) ;
int convert_to_unicode(unsigned char *string,unsigned short *unicode_array);
void hexDump(unsigned char *buf, int count);




//  unsigned short unicode[10] = { 0xAC00, 0xAC01, 0xAC02, 0xAC03, 0xAC04, 0x0031, 0x0032, 0xA321, 0x0065, 0x000d };
int convert_to_utf8(unsigned short *unicode_array, unsigned char *string)
{
	int i ;
	int num_of_convert  ;
	int str_index  ;
	char *unicode_array_1char ; 
	unsigned short *unicode_array_tmp;

	num_of_convert = 0 ;
	str_index = 0 ;

	hexDump((char *)unicode_array, 32 );

	unicode_array_1char = (char *)unicode_array;

//  	for( i = 0 ; i < (32*3/2) ; )
	for( i = 0 ; i < (32) ; )
	{
		printf("i=%2d, str_index=%2d:   :",i,str_index);

		unicode_array_tmp = (unsigned short *)&(unicode_array_1char[i]);

		if( unicode_array_1char[i] == 0 && unicode_array_1char[i+1] == 0 )
		{
			printf("unicode_array_1char is null (%i)\n",i);
			break;
		}

		if( (unicode_array_1char[i] >=0x00) && ( unicode_array_1char[i] <= 0x7f ))
		{
			if( i == 31 )
			{
				printf("ascii region last:%02x\n",unicode_array_1char[i]);
				string[str_index] = (unsigned char)(unicode_array_1char[i] & 0x00ff);
				str_index += 1;
				i += 1 ;
				num_of_convert++;
				continue;

			}
			if( (unicode_array_1char[i+1] >=0x00) && ( unicode_array_1char[i+1] <= 0x7f ))
			{
				printf("ascii region:%02x\n",unicode_array_1char[i]);
				string[str_index] = (unsigned char)(unicode_array_1char[i] & 0x00ff);
				str_index += 1;
				i += 2 ;
				num_of_convert++;
				continue;
			}
			else if( (unicode_array_tmp[0] >=0x80) && ( unicode_array_tmp[0] <= 0x7ff ))
			{
	            //     080-   7FF   110xxxxx 10xxxxxx                   : 첫 바이트는 110 으로 시작하고, 나머지 바이트들은 10으로 시작함
				string[str_index+0] =  (0xc0 | (unsigned char)((unicode_array_tmp[0] & 0xf800)>> 6)) ;
				string[str_index+1] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x003f)>> 0)) ;
	
				printf("arab region:%02x %02x\n",string[str_index], string[str_index+1]);
				str_index += 2 ;
				i += 2 ;
				num_of_convert++;
				continue;
			}
			if( (unicode_array_tmp[0] >=0x800) && ( unicode_array_tmp[0] <= 0xffff ))
			{
				printf("look 1 char seems to ascii but it is HanRegion:\n");
				string[str_index+0] =  (0xe0 | (unsigned char)((unicode_array_tmp[0] & 0xf000)>>12)) ;
				string[str_index+1] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x0fc0)>> 6)) ;
				string[str_index+2] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x003f)>> 0)) ;
	
				printf("han  region:%02x %02x %02x\n",string[str_index], string[str_index+1], string[str_index+2]);
	
				str_index += 3 ; 
				i += 2 ;
				num_of_convert++;
				continue;
			}
		}

		else if( (unicode_array_tmp[0] >=0x80) && ( unicode_array_tmp[0] <= 0x7ff ))
		{
            //     080-   7FF   110xxxxx 10xxxxxx                   : 첫 바이트는 110 으로 시작하고, 나머지 바이트들은 10으로 시작함
			string[str_index+0] =  (0xc0 | (unsigned char)((unicode_array_tmp[0] & 0xf800)>> 6)) ;
			string[str_index+1] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x003f)>> 0)) ;

			printf("arab region:%02x %02x\n",string[str_index], string[str_index+1]);
			str_index += 2 ;
			i += 2 ;
			num_of_convert++;
			continue;
		}

		else if( (unicode_array_tmp[0] >=0x800) && ( unicode_array_tmp[0] <= 0xffff ))
		{
			//  000800-00FFFF   1110xxxx 10xxxxxx 10xxxxxx          : 첫 바이트는 110 또는 1110으로 시작하고, 나머지 바이트들은 10으로 시작함
			string[str_index+0] =  (0xe0 | (unsigned char)((unicode_array_tmp[0] & 0xf000)>>12)) ;
			string[str_index+1] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x0fc0)>> 6)) ;
			string[str_index+2] =  (0x80 | (unsigned char)((unicode_array_tmp[0] & 0x003f)>> 0)) ;

			printf("han  region:%02x %02x %02x\n",string[str_index], string[str_index+1], string[str_index+2]);

			str_index += 3 ; 
			i += 2 ;
			num_of_convert++;
			continue;
		}
	}	

	return num_of_convert;
}

int convert_to_unicode(unsigned char *string,unsigned short *unicode_array)
{
	int i = 0 ;
	char tmp_buf[4];
	int count_unicode = 0 ;
	int count_unicode_1char = 0 ;
	int string_length=0;
	char *unicode_array_1char ;
	unsigned short tmp_short;

	string_length = strlen((const char*)string);

//  	if(string_length > MAX_FULL_NAME_CHAR )
//  		string_length = MAX_FULL_NAME_CHAR;

	unicode_array_1char = (char*)unicode_array;

	// Check Max Length
	if( string_length > MAX_FULL_NAME_CHAR*3/2 )
		string_length = MAX_FULL_NAME_CHAR*3/2;

	printf("string_length=%d\n",string_length);
	sleep(1);

	printf("count_unicode_1char=%d\n",count_unicode_1char);

	for( i = 0 ; i < string_length ; )
	{
		memset(tmp_buf,0,sizeof(tmp_buf));


		if( (string[i] & UTF8_MASK_ASCII) == 0x00)
		{
			unicode_array_1char[count_unicode_1char] = string[i];

			INNO_SHCHO_PRINT("a:(%2d):%04x(%02x) \n", count_unicode_1char, unicode_array[count_unicode], string[i+0]);

			count_unicode_1char += 2;
			i += 1 ;

//  			continue;
		}

		else if( (string[i] & UTF8_MASK_LATIN1) == 0xc0)
		{
			tmp_short= (unsigned short)CONVERT_to_UNICODE_ArabRegion(string[i+0], string[i+1]);
			memcpy( &unicode_array_1char[count_unicode_1char] , &tmp_short, 2); 
			INNO_SHCHO_PRINT("A:(%2d):%04x(%02x %02x) \n", count_unicode_1char, unicode_array[count_unicode], string[i+0], string[i+1]);
			count_unicode_1char += 2 ;
			i += 2 ;
//  			continue;
		}

		else if( (string[i] & UTF8_MASK_HAN1) == 0xe0)
		{
			tmp_short= (unsigned short)CONVERT_to_UNICODE_HANRegion(string[i+0], string[i+1], string[i+2]);
			memcpy( &unicode_array_1char[count_unicode_1char] , &tmp_short, 2); 

			INNO_SHCHO_PRINT("H:(%2d):%04x(%02x %02x %02x) \n", count_unicode, unicode_array[count_unicode], string[i+0],string[i+1], string[i+2]);

			count_unicode_1char += 2 ;
			i += 3 ;
//  			continue;
		}
		printf("count_unicode_1char=%d\n",count_unicode_1char);

		if( (count_unicode_1char/2) >= MAX_FULL_NAME_SHORT )
			break;

	}
	INNO_SHCHO_PRINT("\n");

	for(i = 0 ; i < count_unicode_1char ; i++)
	{
		INNO_SHCHO_PRINT("(%2d):%04x \n", i, unicode_array[i]);
	}
	INNO_SHCHO_PRINT("\n");

	return count_unicode;
}


#define BAUDRATE	B115200
//  #define BAUDRATE 	B38400

int select_ret;
fd_set          rfds;
struct timeval  tv;
struct timespec  ts;

#define ACT_AS_OLD		0
#define ACT_AS_NEW		1

#define YES		1
#define NO		0

#define STRING_MATCH	0

int loop_stop = -1;

unsigned char   uart_buf[300];
unsigned char   stdin_buf[300];
int uart_fd;
int stat_file_fd;

int device_spec_info(void) ;
void Processing_UartPacket(unsigned char *buf);
//  unsigned char* find_model_name( int id );
//  unsigned char* find_model_type( int id );

struct timeval power_up_time_timeval;
struct timeval current_time_timeval;

time_t power_up_time_sec;
time_t current_time_sec;

time_t the_time;
struct tm *pTime_tm;
struct tm Power_up_time_tm;
struct tm Ccurrent_up_time_tm;

#define swap16(a)	  ( ((a >> 8) & 0x00ff) | ((a << 8) & 0xff00) )
#define swap32(a)     ( ((a & 0xff000000) >> 24) | ((a & 0x00ff0000) >> 8) | ((a & 0x0000ff00) <<  8) | ((a & 0x000000ff) << 24) ) 
#define SHORT_INT_HIGH(a) (( a >> 8 ) & 0x00ff)
#define SHORT_INT_LOW(a)  (( a >> 0 ) & 0x00ff)
#define CHANGE_TO_SHORT(low, high)  (((high<<8) & 0xff00)  | (low & 0x00ff) )

#define MAX_DATA_LENGTH 1024

#define STATUS_FAIL 			        -2
#define STATUS_INIT 			        -1
#define STATUS_CARD_DETECTED 	         1
#define STATUS_CARD_RFON 				10
#define STATUS_CARD_READ_INFO 	        11
#define STATUS_BIA_START 		         3
#define STATUS_BIA_END 			         4
#define STATUS_CARD_WRITE_INFO 	         5

#define STATUS_CARD_INFO_RECHECK	     6
#define STATUS_CARD_INFO_CHECK_SUCCESS	 7
#define STATUS_CARD_INFO_CHECK_FAIL	     8

#define BIA_CHECK_INIT			0xff00
#define BIA_CHECK_START			0xff01
#define BIA_CHECK_END			0xff02

int gStatus = STATUS_INIT;
char gCard_UID[8] ;
char gCard_Type ;
int gBia_Status = BIA_CHECK_INIT; 

#define STR_INIT 			"#init"
#define STR_CARD_DETECTED 	"#end"
//  #define STR_CARD_READ_INFO 2
//  #define STR_BIA_START 3
//  #define STR_BIA_END 4

#define CMD_CARD_TYPE_ALL_SERIAL_READ 		0x16
#define CMD_CARD_SET_TO_DUMMY_MODE 		0x81





struct _rfid_request
{
	unsigned char STX;
	unsigned char cmd;
	unsigned short packet_length;
	unsigned char packet_buffer[MAX_DATA_LENGTH];
	unsigned char checksum;
	unsigned char ETX;
}__attribute__((packed));

struct _rfid_response
{
	unsigned char STX;
	unsigned char cmd;
	unsigned char state; // 0x01: 성공, 0xff : 실패
	unsigned short packet_length;
	unsigned char packet_buffer[MAX_DATA_LENGTH];
	unsigned char checksum;
	unsigned char ETX;
}__attribute__((packed));

struct _rfid_recv_header
{
	unsigned char STX;
	unsigned char cmd;
	unsigned char state; // 0x01: 성공, 0xff : 실패
	unsigned short packet_length;
}__attribute__((packed));



unsigned char RFID_SET_DUMMY_READER        [ 6] = { 0x02, 0x81, 0x00, 0x00, 0x81, 0x03 };
//  unsigned char RFID_SET_AUTODETECT          [10] = { 0x02, 0x82, 0x00, 0x04, 0x05, 0x01, 0x00, 0x00, 0x8c, 0x03}; // polling time 0x05: 500msec 0x01: Beep On:All Card
unsigned char RFID_SET_AUTODETECT          [10] =     { 0x02, 0x82, 0x00, 0x04, 0x05, 0x01, 0x03, 0x00, 0x8f, 0x03}; // polling time 0x05: 500msec 0x01: Beep On:ISO15693 Only
unsigned char RFID_SET_RFON_USING_READ_UID [ 6] = { 0x02, 0x40, 0x00, 0x00, 0x40, 0x03}; 						// RF On using UID Read 
unsigned char RFID_SET_RFOFF               [ 6] = { 0x02, 0x3C, 0x00, 0x00, 0x3C, 0x03}; 						// RF Off
unsigned char RFID_READ_USER_BLOCK_ALL     [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x1c, 0x62, 0x03 }; // Multi Block Read: All user block 28(0x1c)
unsigned char RFID_READ_USER_BLOCK_0x12    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x12, 0x58, 0x03 }; // Multi Block Read: All user block 18(0x12)
unsigned char RFID_READ_USER_BLOCK_0x0a    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x0a, 0x50, 0x03 }; // Multi Block Read: All user block 18(0x12)
unsigned char RFID_READ_USER_BLOCK_0x10    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x10, 0x56, 0x03 }; // Multi Block Read: All user block 16(0x10)
unsigned char RFID_BUZZER_BEEP             [ 6] = { 0x02, 0x11, 0x00, 0x00, 0x11, 0x03             }; // Beep 
unsigned char RFID_WRITE_BLOCK26           [11] = { 0x02, 0xC2, 0x00, 0x05, 0x1a, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x03 }; // Beep + Block Write
unsigned char RFID_WRITE_BLOCK             [11] = { 0x02, 0x42, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03 }; // Beep + Block Write


unsigned char RFID_TEST_CARD_ID_RECV       [18] = { 0x02, 0x16, 0x01, 0x00, 0x0A, 0x04, 0x08, 0x9E, 0x93, 0x15, 0x79, 0x00, 0x01, 0x04, 0xE0, 0xD1, 0x03, 0x00 }; // Beep + Block Write

unsigned char add_checksum_str(unsigned char *packet)
{
	int  i ; 
	int sum = 0 ;
	int length = 0 ;

	length = CHANGE_TO_SHORT(packet[3],packet[2]);

	for(i = 0 ; i < length+3;i++)
	{
		sum += packet[i+1];
//  		printf("(sum=%d)(%03d)\n",sum, packet[i+1]);

	}
//  	printf("length=%d(sum=%d(%02x)\n",length,(unsigned char)sum,(unsigned char)sum);

	packet[length+4] = (unsigned char)(sum & 0x000000ff);

	return 1;
}

unsigned char add_checksum(struct _rfid_request *packet)
{
	unsigned char chk;
	int  i ; 

	packet->STX = 0x02;
	chk  = packet->cmd;
	chk += SHORT_INT_HIGH(packet->packet_length);
	chk += SHORT_INT_LOW (packet->packet_length);

	for(i = 0 ; i < packet->packet_length ;i++)
		chk += (packet->packet_buffer)[i];

//  	// length가 0x1234라면  0x34 0x12 순서로 보내야 한다.
//  	// 그래서 packet_length를 swap16한다.
//  	packet->packet_length = swap16(packet->packet_length);

	packet->checksum = (unsigned char)(chk & 0x000000ff);
	packet->STX = 0x03;

	if( packet->packet_length >= MAX_DATA_LENGTH )
		return -1;
	else
		return 1;
}
unsigned char check_checksum(unsigned char *recv_buf )
{
	int chk;
	int  i ; 
	int length;

	length = CHANGE_TO_SHORT(recv_buf[4], recv_buf[3]);

	chk = 0 ;
	for(i = 0 ; i < length+4 ;i++)
		chk += recv_buf[1+i];

	chk = (unsigned char)(chk & 0x000000ff);

	return chk;
}

union _int_char
{
	unsigned int i;
	char ch[4];
};
union _short_char
{
	unsigned short s;
	char ch[2];
};

struct _gender_birthyear_bit
{
	unsigned char birth_year:7;
	unsigned char gender:1 ;
}__attribute__((packed));

struct _birthmonth_bit
{
	unsigned char birth_month:4;
	unsigned char reserved:4 ;
}__attribute__((packed));

struct _bodytype_bodyindex
{
	unsigned char body_type:4;
	unsigned char body_index:4 ;
}__attribute__((packed));



union _int_char gNUGA_CARD_ID;

unsigned char NUGA_ID[4] = {0x11, 0x11, 0x11, 0x11};


#if 0 // old shcho
struct _card_block_info
{
	//block 0
	unsigned char nuga_sig[3];
	unsigned char birth_year:7;
	unsigned char gender:1;

	//block 1 ~ block 9
	unsigned char FullName[34]; 
	unsigned char birth_day;
	unsigned char birth_month:4;
	unsigned char reserved1:4;

	//block 10 ~ block14 : Reserved for others
	unsigned char reserved2[20]; 
	//block 15
	unsigned short weight; 
	unsigned short height; 
	unsigned short icf;      // 세포내액량  
	unsigned short ecf;      // 세포외액량
	unsigned short protein;  //근육량
	unsigned short mm;       //무기질량
	unsigned short smm;      //골격근량
	unsigned short fat;      //체지방량
	unsigned short trs;      //몸통근육
	unsigned short ras;      //오른팔 근육량
	unsigned short las;      //왼팔   근육량
	unsigned short rls;      //오른다리  근육량
	unsigned short lls;      //왼쪽다리  근육량
	unsigned short bmi;      //체질량 지수
	unsigned short pbf;      //체지방률
	unsigned short od;       //비만도
	unsigned short whr;      //복부미반률
	unsigned short vfa;      //내장지방면적
	unsigned char body_type:4;
	unsigned char body_index:4;
	unsigned char scr; // 종합평가지수
	         char cwe; //체중조절량
	         char cfa; //체지방조절량
	unsigned short mean_bp;
	unsigned short heart_rate;
	unsigned short systolic_bp;
	unsigned short diastolic_bp;
	unsigned short minute:6;
	unsigned short hour:5;
	unsigned short day:5;
	unsigned char month:4;
	unsigned char year:4; // 2014년 기준
	unsigned char reserved3; // 2014년 기준

}__attribute__((packed));
#else // new layout from Nuga
struct _card_block_info
{
	//block 0
	unsigned char nuga_sig[4];
	//block 1
	unsigned char birth_month:4;
	unsigned char gender:4;
	unsigned char birth_year;
	unsigned char birth_day;
	unsigned char scr;

	//block 2 ~ block 9
	short FullName[MAX_FULL_NAME_SHORT]; 

	//block 10
	unsigned short weight; 
	unsigned short height; 
	//block 11
	unsigned short icf;      // 세포내액량  
	unsigned short ecf;      // 세포외액량
	//block 12
	unsigned short protein;  //근육량
	unsigned short mm;       //무기질량
	//block 13
	unsigned short smm;      //골격근량
	unsigned short fat;      //체지방량
	//block 14
	unsigned short trs;      //몸통근육
	unsigned short ras;      //오른팔 근육량
	//block 15
	unsigned short las;      //왼팔   근육량
	unsigned short rls;      //오른다리  근육량
	//block 16
	unsigned short lls;      //왼쪽다리  근육량
	unsigned short cfa;     //체지방조절량(Fat Control) //체질량 지수
//  	unsigned short bmi;     //체질량 지수 : 삭제

	//block 17
	unsigned short pbf;      //체지방률
	unsigned short od;       //비만도
	//block 18
	unsigned short whr;      //복부미반률
	unsigned short vfa;      //내장지방면적
	//block 19
	unsigned short csl; //근육조절량  (Muscle Control)
	unsigned short nwe; //적정 체중   (Normal Weight)
	//block 20
	unsigned short cwe; //체중조절량  (Weight Control)
	unsigned char  body_type:4;
	unsigned char  body_index:4;
	unsigned char  situp_count;// 윗몸 일으키기 횟수
	//block 21
	unsigned short vertical_leap1; // 제자리 높이 뛰기 1차
	unsigned short vertical_leap2; // 제자리 높이 뛰기 2차
	//block 22
	unsigned short equ1;           // 눈감고 외발서기 1차
	unsigned short equ2;           // 눈검고 외발서기 2차
	//block 23
	unsigned short agility1;    // 민첩성 1차
	unsigned short agility2;    // 민첩성 2차
	//block 24
	unsigned short Grap_force1;    // 악력 1차
	unsigned short Grap_force2;    // 악력 2차
	//block 25
	unsigned short flex1;          // 앉아 윗몸 앞으로 굽히기 2차
	unsigned short flex2;          // 앉아 윗몸 앞으로 굽히기 2차
	//block 26
	unsigned short mean_bp;
	unsigned short heart_rate;
	//block 27
	unsigned short systolic_bp;
	unsigned short diastolic_bp;

}__attribute__((packed));
#endif

struct _card_block_info gCard_Block_Info;
struct _card_block_info gCard_Block_Info_check;

unsigned char gGender = 1 ;// 남성:1 / 여성 0
unsigned char gBirth_year = 1973-1900 ;// 
unsigned char gBirth_month = 2 ;// 
unsigned char gBirth_day = 19 ;// 
unsigned char gName_utf8[48]="한기웅";
short gName_Unicode[16+1];

char  gName_utf8_tmp[48+1];
short gName_Unicode_tmp[16+1];

unsigned short gHeight=181*100;


void swap16_2byte_member(struct _card_block_info *p)
{
	 p->weight = swap16(p->weight);
	 p->height = swap16(p->height);
	p->protein = swap16(p->protein);
	    p->icf = swap16(p->icf);
	    p->ecf = swap16(p->ecf);
	     p->mm = swap16(p->mm);
	    p->smm = swap16(p->smm);
	    p->fat = swap16(p->fat);
	    p->trs = swap16(p->trs);
	    p->ras = swap16(p->ras);
	    p->las = swap16(p->las);
	    p->rls = swap16(p->rls);
	    p->lls = swap16(p->lls);
//  	    p->bmi = swap16(p->bmi);
	    p->pbf = swap16(p->pbf);
	     p->od = swap16(p->od);
	    p->whr = swap16(p->whr);
	    p->vfa = swap16(p->vfa);
}

void Print_Card_Info(struct _card_block_info *p)
{
 INNO_SHCHO_PRINT("\n\n\t \033[22;35m \n");
	printf("   nuga_sig=0x%02x%02x%02x%02x\n",  p->nuga_sig[3],p->nuga_sig[2],p->nuga_sig[1],p->nuga_sig[0]);
	printf("     gender=%s\n",         p->gender ? "male" :"female");
	printf(" birth_year=%d년\n",   p->birth_year+1900);
	printf("birth_month=%d월\n",  p->birth_month);
	printf("  birth_day=%d월\n",    p->birth_day);

	memset(gName_utf8_tmp ,0, sizeof(gName_utf8_tmp));
	convert_to_utf8(p->FullName , gName_utf8_tmp);
	printf("       name=%s\n",           gName_utf8_tmp);

	printf("\n");

	printf("     weight=%04x(%3.1fKg)\n",   p->weight, p->weight/100.0);
	printf("     height=%04x(%3.1fcm)\n",   p->height, p->height/100.0);
	printf("    protein=%04x(%3.1fKg)\n",  p->protein, p->protein/100.0);
	printf("        ief=%04x(%3.1fKg)\n",      p->icf, p->icf/100.0);
	printf("        ecf=%04x(%3.1fKg)\n",      p->ecf, p->ecf/100.0);
	printf("         mm=%04x(%3.1fKg)\n",       p->mm,  p->mm/100.0);
	printf("        smm=%04x(%3.1fKg)\n",      p->smm, p->smm/100.0);
	printf("        fat=%04x(%3.1fKg)\n",      p->fat, p->fat/100.0);
	printf("        trs=%04x(%3.1fKg)\n",      p->trs, p->trs/100.0);
	printf("        ras=%04x(%3.1fKg)\n",      p->ras, p->ras/100.0);
	printf("        las=%04x(%3.1fKg)\n",      p->las, p->las/100.0);
	printf("        rls=%04x(%3.1fKg)\n",      p->rls, p->rls/100.0);
	printf("        lls=%04x(%3.1fKg)\n",      p->lls, p->lls/100.0);
//  	printf("        bmi=%04x(%3.1fKg/m^2)\n",     p->bmi, p->bmi/100.0);
	printf("        pbf=%04x(%3.1f)\n",          p->pbf, p->pbf/100.0);
	printf("        od=%04x(%3.1f)\n",           p->od,  p->od/100.0);
	printf("        whr=%04x(%3.2f)\n",           p->whr, p->whr/100.0);
	printf("        vfa=%04x(%3.1fcm^2)\n",       p->vfa, p->vfa/100.0);
	printf("  body_type=(%d(dec)형)\n",     p->body_type);
	printf(" body_index=(%d(dec)등급)\n",  p->body_index);
	printf("        scr=%04x(%3d점)\n",           p->scr,p->scr);

	printf("\n");

	printf("        nwe=%04x(%3.1fKg:적정체중    )\n",  p->nwe, p->nwe/100.0);
	printf("        cwe=%04x(%3.1fKg:체중조절량  )\n",  p->cwe, p->cwe/100.0);
	printf("        cfa=%04x(%3.1fKg:지방조절량  )\n",  p->cfa, p->cfa/100.0);
	printf("        csl=%04x(%3.1fKg:근육조절량  )\n",  p->csl, p->csl/100.0);
	printf("      situp=%3d(윗몸일으키기)\n",  (int)p->situp_count);
 INNO_SHCHO_PRINT("\033[0m \n");
}

#define MEM_MATCH	0
#define STR_MATCH	0

#define FAIL_COUNT_MAX	20
int fail_count = 0;

int	Read_Confirm_length(int fd, unsigned char *buf,int length);
void write_copy_for_resend(int fd, unsigned char *buf,int length);

// 여기서 응답을 처리하면 main에서 select가 되지 않는다.
int RFID_write_confirm(int fd, unsigned char *buf, int length)
{
	int select_ret_local;
	fd_set rfds_local;
	struct timeval  tv_local;
	int loop_count = 0;
	unsigned char buf_local[1024];
	int buf_count;
	int ret_local=0;
	int residue;
	int loop_stop;
	struct _rfid_recv_header recv_header;
	int timeout;
	int ret;
	int timeout_count = 0 ;

	memset(buf_local,0,sizeof(buf_local));

	printf("RFID_write_confirm 1st\n");
	hexDump(buf,length);

	write(fd, buf, length);

	loop_stop = NO;
	while(loop_stop == NO)
	{

		FD_ZERO(&rfds_local);
		FD_SET(fd,&rfds_local); 		// stdin

		tv_local.tv_sec = 5 ;
		tv_local.tv_usec = 0 ;

		timeout = 5 ;

		fprintf(stderr,"Before Select \n");
		select_ret_local = select(fd+1, &rfds_local, NULL, NULL, &tv_local);

		if (select_ret == -1)
		{
			fprintf(stderr,"select error\n");
			perror("select()");
			continue;
		}
		else if (select_ret_local)
		{
			if( FD_ISSET(fd,&rfds_local) )
			{
				fprintf(stderr,"RFID_write_confirm  uart_selected.\n");
				INNO_SHCHO_PRINT("\n\n\t \033[22;31m line:%d:@%s in %s \033[0m \n",__LINE__,__FUNCTION__,__FILE__  ); 
				ret=Read_Confirm_length(fd, buf_local,5);
				memcpy(&recv_header,buf_local,5);


				if( ret == -1 )
				{
					printf("\n\n\t \033[22;30;31m line:%d:@%s in %s  \033[0m \n\n",__LINE__,__FUNCTION__,__FILE__  ); 
					printf("read from fd timout within given time\n");
					continue;
				}
				printf("header recveived\n");
//  				hexDump((unsigned char *)&recv_header,5);

				if( recv_header.state == 0xff)
				{
				//fail이면 RF가 Off되었을 것이기 때문에
					ret=Read_Confirm_length(fd, buf_local+5,2); // 나머지 Packet을 읽는다.

//  					tcflush(uart_fd, TCIOFLUSH);
					usleep(100000);
					write(uart_fd, RFID_SET_RFON_USING_READ_UID, sizeof(RFID_SET_RFON_USING_READ_UID));
					// should be more than 300msec
					usleep(300000);
					write(fd, buf, length);

					fail_count++;
					INNO_SHCHO_PRINT("\n\n\t \033[22;31m fail_count=%2d line:%d:@%s in %s \033[0m \n",fail_count, __LINE__,__FUNCTION__,__FILE__  ); 
					if( fail_count > FAIL_COUNT_MAX )
					{
						INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m Packet Response Fail : max(%d): \033[0m \n\n",FAIL_COUNT_MAX); 
						fail_count = 0 ;
						gStatus = STATUS_INIT;
						gBia_Status = BIA_CHECK_INIT;
						write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
						sleep(3);
					}
					continue;
				}
				else // 0x01
				{
//  					printf("packet_length=%d\n",swap16(recv_header.packet_length));
					fail_count = 0 ;
					INNO_SHCHO_PRINT("\n\n\t \033[22;31m line:%d:@%s in %s \033[0m \n",__LINE__,__FUNCTION__,__FILE__  ); 
					ret = Read_Confirm_length(fd, &buf_local[5],swap16(recv_header.packet_length)+2);
					if( ret == -1 )
					{
						printf("\n\n\t \033[22;30;31m line:%d:@%s in %s                \033[0m \n\n",__LINE__,__FUNCTION__,__FILE__  ); 
					}
//  					hexDump(buf_local,5+swap16(recv_header.packet_length)+2);
					break;
				}
			}
		} 
		else
		{
			fprintf(stderr,"RFID_write_confirm  No data within %d seconds.\n",timeout);
			if( timeout_count > 4 )
				return -1;
			timeout_count++;
			continue;
		}
	
	}
}

struct _packet_resend
{
	int fd;
	unsigned char buf[1024];
	int len;
}__attribute__((packed));

struct _packet_resend packet_resend;

void write_copy_for_resend(int fd, unsigned char *buf,int length)
{
	write(fd, buf, length);
	packet_resend.fd = fd;
	memcpy(packet_resend.buf, buf, length);
	packet_resend.len = length;
}

int getline_and_split(char *buf,int range, char* buf1, char *buf2)
{
	int i = 0 ; 
	int next=0;
	int len1;
	int len2;

	len1= 0 ;
	len2= 0 ;



	next = 0;
	for(i=0;i < range ; i++)
	{
		
		if( buf[i] == '\n' )
		{
//  			printf("len1=%d,len2=%d\n",len1,len2);
			return i;
		}

		if( buf[i] == '=')
		{
			next=1;
//  			printf("next(%d)\n",i);
			continue;
		}
		if( next == 0 ) { buf1[len1++] = buf[i]; }
		else            { buf2[len2++] = buf[i]; }
	}

//  	printf("buf1=%s:buf2=%s\n",buf1,buf2);
}

char Read_File_1char( char * filename)
{
	int fd;
	char ret;

	fd = open(filename, O_RDONLY | O_NONBLOCK | O_SYNC );
	read(fd, &ret,1);
	close(fd);

	return ret;
}

int Read_BIA_Info_from_File( char * filename, struct _card_block_info *p)
{
	int fd;
	char *ptr;
	char buf_all[1024*2];
	struct stat f_stat;
	int i = 0 ;
	char buf1[100];
	char buf2[100];



	fd = open(filename, O_RDONLY | O_NONBLOCK | O_SYNC );

	fstat(fd, &f_stat);
//  
	read(fd, buf_all,f_stat.st_size);

	close(fd);

	for(i = 0 ; i < f_stat.st_size ; i++)
	{
		memset(buf1,0,sizeof(buf1));
		memset(buf2,0,sizeof(buf2));
		i += getline_and_split( &buf_all[i],f_stat.st_size-i,buf1,buf2);
		printf("buf1=%s:buf2=%s\n",buf1,buf2);

		if( buf1[0] == '#')
			continue;

		if( strcmp(buf1, "wei"			) == STRING_MATCH ) 	{ p->weight 	= atoi(buf2); }
		if( strcmp(buf1, "icf"			) == STRING_MATCH )		{ p->icf 		= atoi(buf2); }
		if( strcmp(buf1, "ecf"			) == STRING_MATCH ) 	{ p->ecf 		= atoi(buf2); }
		if( strcmp(buf1, "protein"		) == STRING_MATCH )		{ p->protein 	= atoi(buf2); }
		if( strcmp(buf1, "mm"			) == STRING_MATCH ) 	{ p->mm 		= atoi(buf2); }
		if( strcmp(buf1, "smm"			) == STRING_MATCH ) 	{ p->smm 		= atoi(buf2); }
		if( strcmp(buf1, "fat"			) == STRING_MATCH ) 	{ p->fat 		= atoi(buf2); }
		if( strcmp(buf1, "trs"			) == STRING_MATCH ) 	{ p->trs 		= atoi(buf2); }
		if( strcmp(buf1, "ras"			) == STRING_MATCH ) 	{ p->ras 		= atoi(buf2); }
		if( strcmp(buf1, "las"			) == STRING_MATCH ) 	{ p->las 		= atoi(buf2); }
		if( strcmp(buf1, "rls"			) == STRING_MATCH )		{ p->rls 		= atoi(buf2); }
		if( strcmp(buf1, "lls"			) == STRING_MATCH ) 	{ p->lls 		= atoi(buf2); }
//  		if( strcmp(buf1, "bmi"			) == STRING_MATCH ) 	{ p->bmi 		= atoi(buf2); }
		if( strcmp(buf1, "pbf"			) == STRING_MATCH ) 	{ p->pbf 		= atoi(buf2); }
		if( strcmp(buf1, "od"			) == STRING_MATCH ) 	{ p->od 		= atoi(buf2); }
		if( strcmp(buf1, "whr"			) == STRING_MATCH ) 	{ p->whr 		= atoi(buf2); }
		if( strcmp(buf1, "vfa"			) == STRING_MATCH ) 	{ p->vfa 		= atoi(buf2); }
		if( strcmp(buf1, "body_type"	) == STRING_MATCH ) 	{ p->body_type 	= atoi(buf2); }
		if( strcmp(buf1, "body_index"	) == STRING_MATCH ) 	{ p->body_index = atoi(buf2); }
		if( strcmp(buf1, "scr"			) == STRING_MATCH ) 	{ p->scr 		= atoi(buf2); }

		if( strcmp(buf1, "nwe"			) == STRING_MATCH ) 	{ p->nwe 		= atoi(buf2); }
		if( strcmp(buf1, "cwe"			) == STRING_MATCH ) 	{ p->cwe 		= atoi(buf2); }
		if( strcmp(buf1, "cfa"			) == STRING_MATCH ) 	{ p->cfa 		= atoi(buf2); }
		if( strcmp(buf1, "csl"			) == STRING_MATCH ) 	{ p->csl 		= atoi(buf2); }
	}


	return 1;
}

int gInit_Card = 0 ;

int Read_User_Info_from_File( char * filename, struct _card_block_info *p)
{
	int fd;
	char *ptr;
	char buf_all[1024*2];
	struct stat f_stat;
	int i = 0 ;
	char buf1[100];
	char buf2[100];



	fd = open(filename, O_RDONLY | O_NONBLOCK | O_SYNC );

	fstat(fd, &f_stat);
//  
	read(fd, buf_all,f_stat.st_size);

	close(fd);

	for(i = 0 ; i < f_stat.st_size ; i++)
	{
		memset(buf1,0,sizeof(buf1));
		memset(buf2,0,sizeof(buf2));
		i += getline_and_split( &buf_all[i],f_stat.st_size-i,buf1,buf2);
		printf("buf1=%s:buf2=%s\n",buf1,buf2);

		if( strcmp(buf1, "FullName"		) == STRING_MATCH ) 	
		{ 
			memset(gName_Unicode, 0 , sizeof(gName_Unicode));
			hexDump(buf2,strlen(buf2));
//  			sleep(3);
			convert_to_unicode(buf2,gName_Unicode);
			memcpy(p->FullName, gName_Unicode, sizeof(gName_Unicode));
		}
		if( strcmp(buf1, "gender"		) == STRING_MATCH )		
		{ 
			if( strncmp(buf2, "Male", 4 ) == STRING_MATCH )
				p->gender 		= 0xf; 
			else
				p->gender 		= 0; 
		}
		if( strcmp(buf1, "birth_year"	) == STRING_MATCH ) 	
		{ 
			p->birth_year 		= atoi(buf2)-1900; 
		}
		if( strcmp(buf1, "birth_month"	) == STRING_MATCH )		
		{ 
			p->birth_month 	= atoi(buf2); 
		}
		if( strcmp(buf1, "birth_day"	) == STRING_MATCH ) 	
		{ 
			p->birth_day 		= atoi(buf2); 
		}
		if( strcmp(buf1, "height"	) == STRING_MATCH ) 	
		{ 
			p->height 		= atoi(buf2)*100; 
		}
		if( strcmp(buf1, "init"			) == STRING_MATCH ) 	
		{
			if( strncmp( buf2, "1", 1 ) == STRING_MATCH ) { gInit_Card = 1 ; }

		}
	}


	return 1;
}




void Processing_UartPacket(unsigned char *buf)
{
	int i = 0 ;
	int checksum;

	int f_write_fd;

	int fail = 0 ;

	struct _rfid_response packet_recv ;

	int select_ret_local;
	fd_set          rfds_local;
	struct timeval  tv_local;
	int loop_count;
	unsigned char *gCard_char;

	time_t the_time_check;
	struct tm *pTime_tm_check;
	struct tm Check_time_tm;
	int ret;

	int block_end_index ;

	packet_recv.STX   = buf[0];
	packet_recv.cmd   = buf[1];
	packet_recv.state = buf[2];
	packet_recv.packet_length =  CHANGE_TO_SHORT(buf[4], buf[3]);

	for(i = 0 ; i < packet_recv.packet_length ; i++ )
		packet_recv.packet_buffer[i] = buf[5+i];

	
	checksum = check_checksum(buf);

	if( packet_recv.state == 0xff )
	{
		write(uart_fd, RFID_SET_RFON_USING_READ_UID, sizeof(RFID_SET_RFON_USING_READ_UID));
		usleep(400000);
		write(packet_resend.fd, packet_resend.buf, packet_resend.len);
		printf("--------------------------------------------------\n");
		printf("packet response : Fail !!\n\n");
		printf("response :\n");
		hexDump(packet_recv.packet_buffer, packet_recv.packet_length);
		printf("backup packet\n");
		hexDump(packet_resend.buf, packet_resend.len);
		printf("--------------------------------------------------\n");

		fail_count++;
		INNO_SHCHO_PRINT("\n\n\t \033[22;31m fail_count=%2d line:%d:@%s in %s \033[0m \n",fail_count, __LINE__,__FUNCTION__,__FILE__  ); 
		if( fail_count >  FAIL_COUNT_MAX)
		{
			INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m Packet Response Fail : max(%d): \033[0m \n\n",FAIL_COUNT_MAX); 
			fail_count = 0 ;
			gStatus = STATUS_INIT;
			gBia_Status = BIA_CHECK_INIT;
			write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
			sleep(3);
		}
		return;
	}


	if(checksum != buf[5+packet_recv.packet_length])
	{
		printf("Checksum Fail(Tobe:%02x)\n ", checksum);

		usleep(150000);
		write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
		usleep(150000);
		write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
		usleep(150000);
		write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));

		gStatus = STATUS_INIT;
		gBia_Status = BIA_CHECK_INIT;
		usleep(150000);
		write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));

		hexDump( buf, 5+packet_recv.packet_length+2 );
//  		for( i = 0 ; i < 5+packet_recv.packet_length+2 ; i++ )
//  			printf("%02x ", buf[i] );
//  		printf("\n");
		fail_count++;
		INNO_SHCHO_PRINT("\n\n\t \033[22;31m fail_count=%2d line:%d:@%s in %s \033[0m \n",fail_count, __LINE__,__FUNCTION__,__FILE__  ); 
		if( fail_count >  FAIL_COUNT_MAX)
		{
			INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m Packet Response Fail : max(%d): \033[0m \n\n",FAIL_COUNT_MAX); 
			fail_count = 0 ;
			gStatus = STATUS_INIT;
			gBia_Status = BIA_CHECK_INIT;
			write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
			sleep(3);
		}
		return ;
	}

	fail_count = 0 ;



	packet_recv.checksum = checksum;
	packet_recv.ETX = 0x02; // uart에서 Read할 때 이미 Check하기 때문에 여기서는 바로 넣기만 한다.

	switch( gStatus )
	{
		case STATUS_INIT :
			if( packet_recv.cmd == CMD_CARD_TYPE_ALL_SERIAL_READ ) 
			{
				gStatus = STATUS_CARD_DETECTED ;
	
				gCard_Type = packet_recv.packet_buffer[0];
				memcpy(gCard_UID,&(packet_recv.packet_buffer)[2], packet_recv.packet_buffer[1]);
				INNO_SHCHO_PRINT("\n\n\t \033[22;35m \n"); 
				printf("Type=%02x:gCard_UID=", gCard_Type);
				for(i=0;i< packet_recv.packet_buffer[1] ; i++)
				{
					printf("%02x ", packet_recv.packet_buffer[2+i]);
				}
				printf("\n");
				INNO_SHCHO_PRINT("\033[0m \n"); 
				write_copy_for_resend(uart_fd, RFID_SET_DUMMY_READER, sizeof(RFID_SET_DUMMY_READER));
				printf("Set Card Reader : Dummy Reader Mode\n");
			}

			break;

		case STATUS_CARD_DETECTED :
			if( packet_recv.cmd == CMD_CARD_SET_TO_DUMMY_MODE )
			{
				if( packet_recv.state == 0x01 )
				{
					printf("Card Set to Dummy Mode : Success\n");
				}
				else if( packet_recv.state == 0xff )
				{
					printf("Card Set to Dummy Mode : Fail\n");
					fail = 1 ;
				}
			}

			if( fail == 1 )
			{
				gStatus = STATUS_INIT;
				gBia_Status = BIA_CHECK_INIT;
				write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
			}
			else
			{
				gStatus = STATUS_CARD_RFON;
				write_copy_for_resend(uart_fd, RFID_SET_RFON_USING_READ_UID, sizeof(RFID_SET_RFON_USING_READ_UID));
				fail = 0 ;
			}

			break;

		case STATUS_CARD_RFON :
			printf("STATUS_CARD_RFON\r\n");
			if( process_mode  == MODE_READ )
			{
				gStatus = STATUS_CARD_READ_INFO;
				printf("RFON Reply: Read\n");
	
				//반드시 sleep이 있어야 함.
				//그런데 android 하고 cygwin하고 위치가 달라야 함.
				usleep(300000);
	
				write_copy_for_resend(uart_fd, RFID_READ_USER_BLOCK_ALL, sizeof(RFID_READ_USER_BLOCK_ALL));
	//  			write_copy_for_resend(uart_fd, RFID_READ_USER_BLOCK_0x0a, sizeof(RFID_READ_USER_BLOCK_0x10));
	//  			write_copy_for_resend(uart_fd, RFID_READ_USER_BLOCK_0x10, sizeof(RFID_READ_USER_BLOCK_0x10));
	
				printf("\n\n\t \033[22;35m Card Reader RF Stable Time Delay\033[0m \n"); 

			}
			else // MODE_WRITE or MODE_ERASE
			{
				printf("RFON Reply : Write\n");
	
				//반드시 sleep이 있어야 함.
				//그런데 android 하고 cygwin하고 위치가 달라야 함.
				usleep(300000);
	
				memset(gName_Unicode,0, sizeof(gName_Unicode));

				#if 0
					convert_to_unicode(gName_utf8,gName_Unicode);
					memcpy(gCard_Block_Info.FullName, gName_Unicode, sizeof(gName_Unicode));
		
					gCard_Block_Info.nuga_sig[3] = 0x11;
					gCard_Block_Info.nuga_sig[2] = 0x11;
					gCard_Block_Info.nuga_sig[1] = 0x11;
					gCard_Block_Info.nuga_sig[0] = 0x11;
					gCard_Block_Info.gender = gGender;
					gCard_Block_Info.birth_year = gBirth_year;
					gCard_Block_Info.birth_month = gBirth_month;
					gCard_Block_Info.birth_day = gBirth_day;
					gCard_Block_Info.height = gHeight;

				#else

					Read_User_Info_from_File( "userinfo.txt", &gCard_Block_Info);
					gCard_Block_Info.nuga_sig[3] = 0x11;
					gCard_Block_Info.nuga_sig[2] = 0x11;
					gCard_Block_Info.nuga_sig[1] = 0x11;
					gCard_Block_Info.nuga_sig[0] = 0x11;
				#endif
	
				if( process_mode == MODE_ERASE )
				{
					memset(&gCard_Block_Info, 0 , sizeof(gCard_Block_Info));
				}
	
				Print_Card_Info(&gCard_Block_Info);


	
				printf("Card Block Info Write\n");
	
				// Nuga : other devices  has endian Error: So, N20Plus change it
				swap16_2byte_member(&gCard_Block_Info);


				gCard_char = (unsigned char *)&gCard_Block_Info;
	
				// Check Card Info: Touched Card is match // gender/birth_month//Birth_year/birth_day
	
				if( gInit_Card == 1 ) { block_end_index = 28; }
				else                  { block_end_index = 10; }

				for( i = 0 ; i < block_end_index; i++)
				{
	
					RFID_WRITE_BLOCK[4] = i;
					memcpy(&RFID_WRITE_BLOCK[5],&gCard_char[i*4], 4);
					add_checksum_str(RFID_WRITE_BLOCK);
					ret = RFID_write_confirm(uart_fd,RFID_WRITE_BLOCK,sizeof(RFID_WRITE_BLOCK));
					if( ret == -1 )
					{
						printf("RFID_write_confirm too many timeout : Debug this asap\n");
						fail = 1 ;
						break;
					}
					usleep(200000);
				}
	
				
				gStatus = STATUS_INIT;
				gBia_Status = BIA_CHECK_INIT;
				write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
	
				if( fail == 1 )
				{
					INNO_SHCHO_PRINT("\n\n\t \033[22;35m Very Bad Bad News BIA Result write failed !!! \033[0m \n"); 
					INNO_SHCHO_PRINT("\n\n\t \033[22;35m I will degug it ASAP !!! \033[0m \n"); 
//  					system("echo E > /mnt/sdcard/N20Plus/status.flag");
				}
				else
				{
					INNO_SHCHO_PRINT("\n\n\t \033[22;35m Have a Nice Day ! \033[0m \n"); 
					INNO_SHCHO_PRINT("\n\n\t \033[22;35m Thanks for using N20 Body Composition Analyzer!\033[0m \n"); 
//  					system("echo 0 > /mnt/sdcard/N20Plus/status.flag");

		
					swap16_2byte_member(&gCard_Block_Info);
					Print_Card_Info(&gCard_Block_Info);
	
				}

				exit(0);
	
	
			}

			break;

		case STATUS_CARD_READ_INFO :


			printf("Multi-Block Read Reply+++++++++++++++++++++++++\n");
			memcpy( &gCard_Block_Info, packet_recv.packet_buffer, packet_recv.packet_length);

			fail = 0 ;

			if( packet_recv.state == 0xff )
			{
				fail = 1 ;
				printf("\n\n\t \033[22;31m Card Block Read Fail \033[0m \n"); 
			}
			else
			{
//  				INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m line:%d:@%s in %s                \033[0m \n\n",__LINE__,__FUNCTION__,__FILE__  ); 
				if( memcmp(gCard_Block_Info.nuga_sig, (const void*)NUGA_ID, 4) != MEM_MATCH )
				{
					fail=1;
					printf("\n\n\t \033[22;31m 미등록 카드입니다.Unregisterd Card : Abort Bia Check\033[0m \n"); 
					sleep(1);
				}
			}

			if( fail == 1 )
			{
				write_copy_for_resend(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
				usleep(150000);
				write_copy_for_resend(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
				usleep(150000);

				gStatus = STATUS_INIT;
				write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
				break;
			}

//  			INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m line:%d:@%s in %s                \033[0m \n\n",__LINE__,__FUNCTION__,__FILE__  ); 

			swap16_2byte_member(&gCard_Block_Info);


			Print_Card_Info(&gCard_Block_Info);
			gStatus = STATUS_INIT;
			gBia_Status = BIA_CHECK_INIT;
			write_copy_for_resend(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));

			break;

	}
	return ;
}

struct timeval power_up_time_timeval;
struct timeval current_time_timeval;

time_t power_up_time_sec;
time_t current_time_sec;

time_t the_time;
struct tm *pTime_tm;
struct tm Power_up_time_tm;
struct tm Ccurrent_up_time_tm;

int	Read_Confirm_length(int fd, unsigned char *buf,int length)
{
	int select_ret_local;
	fd_set rfds_local;
	struct timeval  tv_local;
	int loop_count = 0;
	unsigned char buf_local[1024];
	int buf_count;
	int ret_local=0;
	int residue;

	memset(buf_local,0,sizeof(buf_local));

	buf_count = 0;
	residue = length;

//  	printf("expected length=%d\n",length);

	while(1)
	{
		ret_local = read(fd, &buf_local[buf_count], residue);
//  		printf("expected=%d, actual=%d\n", residue, ret_local);
//  		printf("buf_count=%d, residue=%d\n", buf_count, residue);
		buf_count += ret_local;
		residue   -= ret_local;
//  		printf("buf_count=%d, residue=%d\n", buf_count, residue);
		if( residue <=0 )
		{
			memcpy(buf,buf_local,length);
			return 1;
		}

		if( loop_count > 3 )
			return -1;

		loop_count++;
	}
}


void hexDump(unsigned char *buf, int count)
{
	int i = 0 ;
	INNO_SHCHO_PRINT("      0  1  2  3  4  5  6  7    8  9  a  b  c  d  e  f\n");
	INNO_SHCHO_PRINT("    ------------------------ -------------------------\n");
	for(i=0 ; i < count ; i++ )
	{
		if( (i % 16) == 0 ) INNO_SHCHO_PRINT("%02x:", i);
		INNO_SHCHO_PRINT(" %02x", buf[i]);
		if( (i % 8) == 7 )	INNO_SHCHO_PRINT("  ");
		if( (i % 16) == 15 )	INNO_SHCHO_PRINT(" \n");
	}
	INNO_SHCHO_PRINT("\n");
	INNO_SHCHO_PRINT("    ------------------------ -------------------------\n");
}

struct termios  oldtio, newtio;
int setupUart(int fd);


int setupUart(int fd)
{

	/*
	 * BAUDRATE: Set bps rate. You could also use cfsetispeed and cfsetospeed. CRTSCTS : output hardware flow control (only used if the cable has all necessary lines.
	 * See sect. 7 of Serial-HOWTO) CS8 : 8n1 (8bit,no parity,1 stopbit) CLOCAL : local connection, no modem contol CREAD : enable receiving characters
	 */
	// newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
	newtio.c_cflag = CS8 | CLOCAL | CREAD;
	// shcho : should be use
	cfsetispeed(&newtio, BAUDRATE);
	cfsetospeed(&newtio, BAUDRATE);

	/*
	 * IGNPAR : ignore bytes with parity errors ICRNL : map CR to NL (otherwise a CR input on the other computer will not terminate input) otherwise make device raw (no
	 * other input processing)
	 */
	// newtio.c_iflag = IGNPAR | ICRNL;
	newtio.c_iflag = IGNPAR | IGNBRK;

	/*
	 * Raw output.
	 */
	// newtio.c_oflag = 0;
	newtio.c_oflag = OFDEL;

	/*
	 * ICANON : enable canonical input disable all echo functionality, and don't send signals to calling program
	 */
	// newtio.c_lflag = ICANON;
	// non-canonical
	newtio.c_lflag = 0;

	/*
	 * initialize all control characters default values can be found in /usr/include/termios.h, and are given in the comments, but we don't need them here
	 */
	newtio.c_cc[VINTR] = 0;		/* Ctrl-c */
	newtio.c_cc[VQUIT] = 0;		/* Ctrl-\ */
	newtio.c_cc[VERASE] = 0;	/* del */
	newtio.c_cc[VKILL] = 0;		/* @ */
	newtio.c_cc[VEOF] = 4;		/* Ctrl-d */

// original: tested in cygwin
#ifdef __CYGWIN__
	newtio.c_cc[VTIME] = 0;		/* inter-character timer unused */
	newtio.c_cc[VMIN] = 12;		/* blocking read until 1 character arrives */
#else
	#ifdef __LINUX__
// xCON6410에서는 설정을 변경해야 함.
	newtio.c_cc[VTIME] = 1;		/* inter-character timer unused */
	newtio.c_cc[VMIN] = 1;		/* blocking read until 1 character arrives */
	#endif
#endif

	newtio.c_cc[VSWTC] = 0;		/* '\0' */
	newtio.c_cc[VSTART] = 0;	/* Ctrl-q */
	newtio.c_cc[VSTOP] = 0;		/* Ctrl-s */
	newtio.c_cc[VSUSP] = 0;		/* Ctrl-z */
	newtio.c_cc[VEOL] = 0;		/* '\0' */
	newtio.c_cc[VREPRINT] = 0;	/* Ctrl-r */
	newtio.c_cc[VDISCARD] = 0;	/* Ctrl-u */
	newtio.c_cc[VWERASE] = 0;	/* Ctrl-w */
	newtio.c_cc[VLNEXT] = 0;	/* Ctrl-v */
	newtio.c_cc[VEOL2] = 0;		/* '\0' */

	/*
	 * now clean the modem line and activate the settings for the port
	 */


	tcflush(fd, TCIOFLUSH);
	tcsetattr(fd, TCSANOW, &newtio);
}

#define MODE_SCAN_ALL	            0x03
#define MODE_SCAN_LIMITED	        0x02
#define MODE_SCAN_GENERAL	        0x01
#define MODE_SCAN_NONDISCOVERABLE	0x00

#define ADDR_TYPE_PrivateResolve	0x03
#define ADDR_TYPE_Public	        0x00

#define ACTIVE_SCAN_ENABLE			0x01
#define ACTIVE_SCAN_DISABLE			0x00
#define WHITELIST_ENABLE			0x01
#define WHITELIST_DISABLE			0x00

#define STATUS_Already_Performing_That_Task	0x11

//  #define Opcode_GAP_DeviceInit				0xFE00
//  #define Opcode_GAP_DeviceDiscoveryRequest	0xFE04
//  #define Opcode_GAP_SetParam					0xFE30
//  #define Opcode_GAP_GetParam					0xFE31
//  #define Opcode_GAP_EstablishLinkRequest		0xFE09
//  #define Opcode_GAP_TerminateLinkRequest		0xFE0A
//  
//  #define Opcode_GATT_ReadUsingCharUUID		0xFDB4

#define Reason_Remote_User_Terminated_Connection		0x13
#define Reason_Host_Requested		0x16

#define ParamID_TGAP_CONN_EST_INT_MIN			0x15
#define ParamID_TGAP_CONN_EST_INT_MAX			0x16
#define ParamID_TGAP_CONN_EST_LATENCY			0x1A
#define ParamID_TGAP_CONN_EST_SUPERV_TIMEOUT	0x19

#define EventCode_HCI_LE_ExtEvent	0xFF

#define PROFILE_ROLE_CENTRAL	0x08

#define PacketType_COMMAND		0x01
#define PacketType_ASYNCDATA	0x02
#define PacketType_SYNCDATA		0x03
#define PacketType_EVENT		0x04

#define EventCode_HCI_LE_ExtEvent 			 0xFF

//  #define Event_GAP_HCI_ExtentionCommandStatus 0x067F
//  #define Event_GAP_DeviceInitDone	 		 0x0600
//  #define Event_GAP_DeviceDiscoveryDone		 0x0601
//  #define Event_GAP_EstablishLink	 		     0x0605
//  #define Event_GAP_TerminateLink	 		     0x0606
//  #define Event_GAP_DeviceInfomation	 		 0x060D
//  #define Event_GAP_LinkParamUpdate	 		 0x0607
//  
//  #define Event_ATT_ReadByTypeRsp	 		     0x0509

#define EventType_Connectable_Undirect_Advertisement	0x00
#define EventType_Scan_Response							0x04


unsigned short ConnHandleList[100];

//====================================================================
struct _CMD_GAP_DeviceInitParam
{
	unsigned char ProfileRole;
	unsigned char MaxScanRsps;
	unsigned char IRK[16];
	unsigned char CSRK[16];
	unsigned int  SignCounter;
}__attribute__((packed));

struct _EVENT_GAP_DeviceInitDone
{
	unsigned short Event;
	unsigned char  Status;
	unsigned char  DevAddr[6];
	unsigned short DataPktLength;
	unsigned char  NumOfDataPkts;
	unsigned char  IRK[16];
	unsigned char  CSRK[16];
}__attribute__((packed));
//====================================================================

//====================================================================
struct _CMD_GAP_EstablishLinkRequestParam
{
	unsigned char HighDutyCycle;
	unsigned char WhiteList;
	unsigned char AddrTypePeer;
	unsigned char PeerAddr[6];
}__attribute__((packed));

struct _EVENT_GAP_EstablishLinkRequestParam
{
	unsigned short Event;
	unsigned char  Status;
	unsigned char  DevAddrType;
	unsigned char  DevAddr[6];
	unsigned short ConnHandle;
	unsigned short ConnInterval;
	unsigned short ConnLatency;
	unsigned short ConnTimeout;
	unsigned char  ClockAccuracy;
}__attribute__((packed));
//====================================================================

//====================================================================
struct _CMD_GATT_ReadUsingCharUUIDParam
{
	unsigned short ConnHandle;
	unsigned short StartHandle;
	unsigned short EndHandle;
	unsigned char  Type[2];
}__attribute__((packed));

struct _EVENT_ATT_ReadByTypeResponse_0x00_Param
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short ConnHandle;
	unsigned char  PduLen;
	unsigned char  Length;
	unsigned char  Handle;
	unsigned char  Data[256];
}__attribute__((packed));

struct _EVENT_ATT_ReadByTypeResponse_0x1A_Param
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short ConnHandle;
	unsigned char  PduLen;
}__attribute__((packed));

struct _EVENT_ATT_ErrorResponse_Param
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short ConnHandle;
	unsigned char  PduLen;
	unsigned char  ReqOpcode;
	unsigned char  Handle;
	unsigned char  ErrorCode;
}__attribute__((packed));
//====================================================================

//====================================================================
struct _EVENT_GAP_LinkParamUpdateParam
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short ConnHandle;
	unsigned short ConnInterval;
	unsigned short ConnLatency;
	unsigned short ConnTimeout;
}__attribute__((packed));

//====================================================================

//====================================================================
struct _CMD_GAP_DeviceDiscoveryRequestParam
{
	unsigned char Mode;
	unsigned char ActiveScan;
	unsigned char WhiteList;
}__attribute__((packed));

struct _EVENT_GAP_DeviceInfomationParam
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short EventType;
	unsigned short AddrType;
	unsigned char  Addr[6];
	unsigned char  Rssi;
	unsigned char  DataLength;
	unsigned char  Data[256];
}__attribute__((packed));

struct _DiscoveryDoneParam 
{
	unsigned char  EventType;
	unsigned char  AddrType;
	unsigned char  Addr[6];
}__attribute__((packed));

struct _EVENT_GAP_DeviceDiscoveryDoneParam
{
	unsigned short Event;
	unsigned char  Status;
	unsigned char  NumDevs;
	struct _DiscoveryDoneParam DiscDoneParams[100] ; // max scan 100
}__attribute__((packed));
//====================================================================

//====================================================================
struct _EVENT_GAP_CommandStatusParam
{
	unsigned short Event;
	unsigned char  Status;
	unsigned short OpCode;
	unsigned char  CSRK[16];
	unsigned char  DataLength;
}__attribute__((packed));
//==================================================================================

//==================================================================================
struct _CommandPacket
{
	unsigned char  Type;
	unsigned short OpCode;
	unsigned char  ParamTotalLength;
	unsigned char  Params[256];
}__attribute__((packed));

struct _EventPacket
{
	unsigned char  Type;
	unsigned char  EventCode;
	unsigned char  ParamTotalLength;
	unsigned char  Params[256];
}__attribute__((packed));
//==================================================================================

//  struct _DeviceParameter
//  {
//  	int ConHandle
//  }__attribute__((packed));


int GAP_DeviceInit(int fd);
int DeviceScan(int fd);
int GAP_GetConnectionSetting(int fd);
int Uart_SendPacket(int fd,void *ptr, int len);
int Uart_RecvPacket(int fd, unsigned char *ptr, int timeout);

int Uart_SendPacket(int fd,void *ptr, int len)
{
	write(fd,ptr,len);
	printf("length=%d\n",len);
	hexDump(ptr,len);
}

int Uart_RecvPacket(int fd, unsigned char *ptr, int timeout)
{
	int select_ret;
	fd_set          rfds;
	struct timeval  tv;
	struct timespec  ts;
	int loop_stop_local = NO;
	int ret;
	int i;

	while(loop_stop_local == NO)
	{

		FD_ZERO(&rfds);
		FD_SET(uart_fd, &rfds); //uart_fd
//  		FD_SET(0,&rfds); 		// stdin

		tv.tv_sec = timeout ;
		tv.tv_usec = 0 ;

//  		memset(uart_buf,0,sizeof(uart_buf));

//  		printf("uart_fd=%d(tv_sec=%d)\n",uart_fd, (int)tv.tv_sec);

		select_ret = select(uart_fd+1, &rfds, NULL, NULL, &tv);

		if (select_ret == -1)
		{
			fprintf(stderr,"select error\n");
			perror("select()");
			continue;
		}
		else if (select_ret)
		{
			if( FD_ISSET(uart_fd,&rfds) )
			{

				INNO_SHCHO_PRINT("\n\n\t \033[22;31m line:%d:@%s in %s \033[0m \n",__LINE__,__FUNCTION__,__FILE__  ); 
				ret=read(uart_fd, ptr,3);

				printf("packet first3= ");
				for(i = 0 ; i < 3 ; i++ )
					printf("%02x ", ptr[i] );
				printf("\n");


				ret=Read_Confirm_length(uart_fd, &ptr[3], ((unsigned char *)ptr)[2]);
				if( ret == -1 )
				{
					printf("read from fd timout within given time\n");
					continue;
				}
				
				hexDump(ptr, ((unsigned char *)ptr)[2]+3);

//  				Processing_UartPacket(uart_buf);
			}
		} 
		else
		{
			fprintf(stderr,"No data within %d seconds.\n",tv.tv_sec);
			break;
		}
	
	}
}

//  int GAP_DeviecInit(void)
int GAP_DeviceInit(int fd)
{
	struct _CommandPacket            CMD_Packet;
	struct _EventPacket              EVENT_Packet;
	struct _CMD_GAP_DeviceInitParam  DeviceInitParam;

	CMD_Packet.Type   = PacketType_COMMAND;
	CMD_Packet.OpCode = GAP_CMD_DeviceInitialization;
	CMD_Packet.ParamTotalLength = 0x26;

	DeviceInitParam.ProfileRole = PROFILE_ROLE_CENTRAL;
	DeviceInitParam.MaxScanRsps = 0x05;
	memset(DeviceInitParam.IRK , 0x00, 16);
	memset(DeviceInitParam.CSRK, 0x00, 16);
	DeviceInitParam.SignCounter = 0x00000001;

	memcpy(CMD_Packet.Params,&DeviceInitParam, CMD_Packet.ParamTotalLength);

	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );
	Uart_RecvPacket(fd, (unsigned char *)&EVENT_Packet,2);

	return 1;
}

int	GAP_GetConnectionSetting(int fd)
{
	struct _CommandPacket            CMD_Packet;
	struct _EventPacket              EVENT_Packet;

	CMD_Packet.Type   = PacketType_COMMAND;
	CMD_Packet.OpCode = GAP_CMD_GetParameter;
	CMD_Packet.ParamTotalLength = 0x01;

//  1549 #define ParamID_TGAP_CONN_EST_INT_MIN           0x15
//  1550 #define ParamID_TGAP_CONN_EST_INT_MAX           0x16
//  1551 #define ParamID_TGAP_CONN_EST_LATENCY           0x1A
//  1552 #define ParamID_TGAP_CONN_EST_SUPERV_TIMEOUT    0x19

	CMD_Packet.Params[0] = ParamID_TGAP_CONN_EST_INT_MIN;
	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );
	
	CMD_Packet.Params[0] = ParamID_TGAP_CONN_EST_INT_MAX;
	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );

	CMD_Packet.Params[0] = ParamID_TGAP_CONN_EST_LATENCY;
	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );

	CMD_Packet.Params[0] = ParamID_TGAP_CONN_EST_SUPERV_TIMEOUT;
	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );

	Uart_RecvPacket(fd, (unsigned char *)&EVENT_Packet,2);

	
}

int DeviceScan(int fd)
{
	struct _CommandPacket            CMD_Packet;
	struct _EventPacket              EVENT_Packet;
	struct _CMD_GAP_DeviceInitParam  DeviceInitParam;

	CMD_Packet.Type   = PacketType_COMMAND;
	CMD_Packet.OpCode = GAP_CMD_DeviceDiscoveryRequest;
	CMD_Packet.ParamTotalLength = 0x03;
	CMD_Packet.Params[0] = 0x03; //Mode
	CMD_Packet.Params[1] = 0x01; //ActiveScan
	CMD_Packet.Params[2] = 0x00; //WhiteList

	Uart_SendPacket(fd, &CMD_Packet,   CMD_Packet.ParamTotalLength+4 );
	Uart_RecvPacket(fd, (unsigned char *)&EVENT_Packet, 11);

	return 1;
}


int main(int argc, char *argv[])
{
	int ret ;
	int packet_len;
	int i = 0 ;
	int timeout = 0 ;
	struct _rfid_recv_header recv_header;
	char *pFilename ;


	switch(argc)
	{

//  		case 3:
//  			     if( strncmp("init", argv[2], 4) == STRING_MATCH ) { process_mode = MODE_ERASE ; }
//  			else if( strncmp("r"   , argv[2], 1) == STRING_MATCH ) { process_mode = MODE_READ  ; }
//  			else                                                   { process_mode = MODE_WRITE ; }
//  
//  			break;
		case 1:
			printf("Usage : ./a.exe /dev/com15 \n");
			printf("\n");
			return -1;
	}
	///////////////////////////////////////////////////////////////////////////////
	time(&power_up_time_sec);

	time(&the_time);
	pTime_tm = localtime((const time_t *)&the_time);
	memcpy(&Power_up_time_tm, pTime_tm, sizeof(struct tm));

	printf("\n\n");
    printf("		Power Up Time : %d년 %d월 %d일 %d:%d\n",
            Power_up_time_tm.tm_year + 1900, Power_up_time_tm.tm_mon +1,
            Power_up_time_tm.tm_mday,        Power_up_time_tm.tm_hour,
            Power_up_time_tm.tm_min);
	///////////////////////////////////////////////////////////////////////////////
	
	uart_fd = open(argv[1], O_RDWR | O_NONBLOCK | O_NDELAY);

	if (uart_fd == -1)
	{
		perror(argv[1]);
		exit(-1);
	} 
	else
		fcntl(uart_fd, F_SETFL, 0);

	setupUart(uart_fd);

//  	// ConnHandle init to 0xFFFF
//  	memset(ConnHandleList, 0xFF, sizeof(ConnHandleList));

	// HostDevice Init
	GAP_DeviceInit(uart_fd);

	// Get Connection Setting
	GAP_GetConnectionSetting(uart_fd);

	// DeviceScan
	DeviceScan(uart_fd);

//  	// Scan : Result :Device List
//  	GAP_DeviceDiscoveryRequest();
//  
//  	// Establish Link
//  	GAP_EstablishLink();
//  
	loop_stop = NO;
	while(loop_stop == NO)
	{

		FD_ZERO(&rfds);
		FD_SET(uart_fd, &rfds); //uart_fd
//  		FD_SET(0,&rfds); 		// stdin

		tv.tv_sec = 5 ;
		tv.tv_usec = 0 ;

		timeout = 5 ;

		memset(uart_buf,0,sizeof(uart_buf));

		printf("uart_fd=%d(tv_sec=%d)\n",uart_fd, (int)tv.tv_sec);

		select_ret = select(uart_fd+1, &rfds, NULL, NULL, &tv);

		if (select_ret == -1)
		{
			fprintf(stderr,"select error\n");
			perror("select()");
			continue;
		}
		else if (select_ret)
		{
			if( FD_ISSET(0,&rfds) )
			{
				memset(stdin_buf, 0 , sizeof(stdin_buf));
				ret = read(0,stdin_buf,10);

				if( stdin_buf[0] != '#' )
				{
					INNO_SHCHO_PRINT("\n\n\t \033[22;35m  stdin input no start with \'#\' continue \033[0m \n"); 
					ret = read(0,stdin_buf,sizeof(stdin_buf)); // just read
//  					memset(stdin_buf,0,sizeof(stdin_buf));
					continue; // protocol start from #
				}
				
				printf("stdin_buf=%s\n", stdin_buf);

				// shcho
				// this code add because
				// shcho test environment : 1 Serial loop back
				// others : 2 serial :1 serial is Wisd Remote . 1 serial is device_emulation
				if( strncmp("#init", (char *)stdin_buf, 5) == STRING_MATCH )
				{
					printf("Processing #init\n");

					gStatus = STATUS_INIT;
					write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
				}

				if( strncmp("#end", (char *)stdin_buf, 4) == STRING_MATCH )
				{
					printf("Bia Processing End\n");
					gBia_Status = BIA_CHECK_END;
				}

			}
			if( FD_ISSET(uart_fd,&rfds) )
			{

				INNO_SHCHO_PRINT("\n\n\t \033[22;31m line:%d:@%s in %s \033[0m \n",__LINE__,__FUNCTION__,__FILE__  ); 
				ret=Read_Confirm_length(uart_fd, uart_buf,5);
				memcpy(&recv_header,uart_buf,5);
//  				ret = read(uart_fd, uart_buf, 5);
//  				printf("expected=5,ret=%d\n",ret);
//  struct _rfid_recv_header
//  {
//  	unsigned char STX;
//  	unsigned char cmd;
//  	unsigned char state; // 0x01: 성공, 0xff : 실패
//  	unsigned short packet_length;
//  }__attribute__((packed));


				if( ret == -1 )
				{
					printf("read from fd timout within given time\n");
					continue;
				}
				if( uart_buf[0] != 0x02 )
				{
					fprintf(stderr,"0:uart_buf[0]=%02x\n",uart_buf[0]);
					tcflush(uart_fd, TCIOFLUSH);

					usleep(150000);
					write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
					usleep(150000);
					write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
					usleep(150000);
					write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
			
					gStatus = STATUS_INIT;
					gBia_Status = BIA_CHECK_INIT;
					usleep(150000);
					write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
	
					continue; // protocol start from #
				}
//  				printr("uart Event \n");
//  
				printf("packet first5= ");
				for(i = 0 ; i < 5 ; i++ )
					printf("%02x ", uart_buf[i] );
				printf("\n");


//  				packet_len = CHANGE_TO_SHORT(uart_buf[4], uart_buf[3]);
				packet_len = swap16(recv_header.packet_length);
				INNO_SHCHO_PRINT("\n\n\t \033[22;31m line:%d:@%s in %s \033[0m \n",__LINE__,__FUNCTION__,__FILE__  ); 
				ret=Read_Confirm_length(uart_fd, &uart_buf[5], packet_len+2);
				if( ret == -1 )
				{
					printf("read from fd timout within given time\n");
					continue;
				}

//  				ret = read(uart_fd, &uart_buf[5], packet_len+2);
//  				printf("expected=%d,ret=%d\n",packet_len+2,ret);


				if( packet_len > 0)
				{
					printf("packet(%02x)= \n", packet_len);

					hexDump(&uart_buf[5], packet_len+2);
				}	
				Processing_UartPacket(uart_buf);
			}
		} 
		else
		{
//  			fprintf(stderr,"No data within %d seconds.\n",tv.tv_sec);
			fprintf(stderr,"main No data within %d seconds.\n",timeout);
			continue;
		}
	
	}

	tcsetattr(uart_fd, TCSANOW, &oldtio);
	close(uart_fd);

	return 1 ;
}







