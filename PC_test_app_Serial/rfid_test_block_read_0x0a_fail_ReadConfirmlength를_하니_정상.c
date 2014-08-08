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

#define BIA_CHECK_WAIT_SEC	120
// MUST: should be char : not unsigned char
unsigned char str_utf8[] = "조승훈:가각:안녕하세요? 조승훈입니다. shcho@genexon.co.kr";
unsigned short array_unicode[100] ;

int convert_to_utf8(unsigned short *unicode_array, unsigned char *string) ;
int convert_to_unicode(unsigned char *string,unsigned short *unicode_array);
void hexDump(unsigned char *buf, int count);


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

unsigned char   uart_buf[255];
unsigned char   stdin_buf[255];
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
unsigned char RFID_SET_AUTODETECT          [10] = { 0x02, 0x82, 0x00, 0x04, 0x05, 0x01, 0x00, 0x00, 0x8c,0x03}; // polling time 0x05: 500msec 0x01: Beep On
unsigned char RFID_SET_RFON_USING_READ_UID [ 6] = { 0x02, 0x40, 0x00, 0x00, 0x40, 0x03}; 						// RF On using UID Read 
unsigned char RFID_READ_USER_BLOCK_ALL     [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x1c, 0x62,0x03 }; // Multi Block Read: All user block 28(0x1c)
unsigned char RFID_READ_USER_BLOCK_0x12    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x12, 0x58,0x03 }; // Multi Block Read: All user block 18(0x12)
unsigned char RFID_READ_USER_BLOCK_0x0a    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x0a, 0x50,0x03 }; // Multi Block Read: All user block 18(0x12)
unsigned char RFID_READ_USER_BLOCK_0x10    [ 8] = { 0x02, 0x44, 0x00, 0x02, 0x00, 0x10, 0x56,0x03 }; // Multi Block Read: All user block 16(0x10)
unsigned char RFID_BUZZER_BEEP             [ 6] = { 0x02, 0x11, 0x00, 0x00, 0x11, 0x03 }; // Beep 
unsigned char RFID_WRITE_BLOCK26           [11] = { 0x02, 0xC2, 0x00, 0x05, 0x1a, 0x00, 0x00, 0x00, 0x00, 0xc0,0x03 }; // Beep + Block Write
unsigned char RFID_WRITE_BLOCK             [11] = { 0x02, 0x42, 0x00, 0x05, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,0x03 }; // Beep + Block Write

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

unsigned char NUGA_ID[3] = {0x11, 0x11, 0x11};

struct _card_block_info
{
	//block 0
	unsigned char nuga_sig[3];
	unsigned char birth_year:7;
	unsigned char gender:1;

	//block 1 ~ block 9
	unsigned char FullName[35]; 
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

struct _card_block_info gCard_Block_Info;

void Print_Card_Info(struct _card_block_info *p)
{
	printf("nuga_sig=0x%02x%02x%02x\n",  p->nuga_sig[2],p->nuga_sig[1],p->nuga_sig[0]);
	printf("gender=%s\n",         p->gender ? "Male" :"Female");
	printf("birth_year=%d년\n",   p->birth_year+1900);
	printf("name=%s\n",           p->FullName);
	printf("birth_month=%d월\n",  p->birth_month);
	printf("weight=%04x(%d)\n",   p->weight, p->weight);
	printf("height=%04x(%d)\n",   p->height, p->height);
	printf("protein=%04x(%d)\n",  p->protein, p->protein);
	printf("ief=%04x(%d)\n",  p->icf, p->icf);
	printf("ecf=%04x(%d)\n",  p->ecf, p->ecf);
	printf("mm=%04x(%d)\n",       p->mm,  p->mm);
	printf("smm=%04x(%d)\n",      p->smm, p->smm);
	printf("fat=%04x(%d)\n",      p->fat, p->fat);
	printf("trs=%04x(%d)\n",      p->trs, p->trs);
	printf("ras=%04x(%d)\n",      p->ras, p->ras);
	printf("las=%04x(%d)\n",      p->las, p->las);
	printf("rls=%04x(%d)\n",      p->rls, p->rls);
	printf("lls=%04x(%d)\n",      p->lls, p->lls);
	printf("bmi=%04x(%d)\n",      p->bmi, p->bmi);
	printf("pbf=%04x(%d)\n",      p->pbf, p->pbf);
	printf("od=%04x(%d)\n",       p->od,  p->od);
	printf("whr=%04x(%d)\n",      p->whr, p->whr);
	printf("vfa=%04x(%d)\n",      p->vfa, p->vfa);
	printf("body_type=(%d(dec))\n",   p->body_type);
	printf("body_index=(%d(dec))\n",  p->body_index);
	printf("scr=%04x(%d)\n",      p->scr,p->scr);

	printf("cwe=%04x(%d)\n",      p->cwe, p->cwe);
	printf("cfa=%04x(%d)\n",      p->cfa, p->cfa);
	printf("     mean_bp=%04x\n",      p->mean_bp);
	printf("  heart_rate=%04x\n",      p->heart_rate);
	printf(" systolic_bp=%04x\n",      p->systolic_bp);
	printf("diastolic_bp=%04x\n",      p->diastolic_bp);
	printf("minute=%d분\n",      p->minute);
	printf("  hour=%d시\n",      p->hour);
	printf("   day=%d일\n",      p->day);
	printf(" month=%d월\n",      p->month);
	printf("  year=%d년\n",      p->year+2014);
}

#define MEM_MATCH	0
#define STR_MATCH	0

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


	packet_recv.STX   = buf[0];
	packet_recv.cmd   = buf[1];
	packet_recv.state = buf[2];
	packet_recv.packet_length =  CHANGE_TO_SHORT(buf[4], buf[3]);

	for(i = 0 ; i < packet_recv.packet_length ; i++ )
		packet_recv.packet_buffer[i] = buf[5+i];

	
	checksum = check_checksum(buf);
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
		write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));

		hexDump( buf, 5+packet_recv.packet_length+2 );
//  		for( i = 0 ; i < 5+packet_recv.packet_length+2 ; i++ )
//  			printf("%02x ", buf[i] );
//  		printf("\n");
		return ;
	}
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
				printf("Type=%02x:gCard_UID=", gCard_Type);
				for(i=0;i< packet_recv.packet_buffer[1] ; i++)
				{
					printf("%02x ", packet_recv.packet_buffer[2+i]);
				}
				printf("\n");
				write(uart_fd, RFID_SET_DUMMY_READER, sizeof(RFID_SET_DUMMY_READER));
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
				write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
			}
			else
			{
				gStatus = STATUS_CARD_RFON;
				write(uart_fd, RFID_SET_RFON_USING_READ_UID, sizeof(RFID_SET_RFON_USING_READ_UID));
				fail = 0 ;
			}

			break;

		case STATUS_CARD_RFON :

			gStatus = STATUS_CARD_READ_INFO;
			printf("RFON Reply\n");

//  			#ifdef __LINUX__
			//반드시 sleep이 있어야 함.
			//그런데 android 하고 cygwin하고 위치가 달라야 함.
			usleep(300000);
//  			#endif

//  			write(uart_fd, RFID_READ_USER_BLOCK_ALL, sizeof(RFID_READ_USER_BLOCK_ALL));
			write(uart_fd, RFID_READ_USER_BLOCK_0x0a, sizeof(RFID_READ_USER_BLOCK_0x0a));

//  			#ifdef __CYGWIN__
//  			//반드시 sleep이 있어야 함.
//  			//그런데 android 하고 cygwin하고 위치가 달라야 함.
//  			usleep(300000);
//  			#endif


			printf("\n\n\t \033[22;35m Card Reader RF Stable Time Delay\033[0m \n"); 

			break;

		case STATUS_CARD_READ_INFO :

			gStatus = STATUS_BIA_START;

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
				if( memcmp(gCard_Block_Info.nuga_sig, (const void*)NUGA_ID, 3) != MEM_MATCH )
				{
					fail=1;
					printf("\n\n\t \033[22;31m Unregisterd Card : Abort Bia Check\033[0m \n"); 
				}
			}

			if( fail == 1 )
			{
				write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
				usleep(150000);
				write(uart_fd,RFID_BUZZER_BEEP,sizeof(RFID_BUZZER_BEEP));
				usleep(150000);

				gStatus = STATUS_INIT;
				write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
				break;
			}

//  			INNO_SHCHO_PRINT("\n\n\t \033[22;30;31m line:%d:@%s in %s                \033[0m \n\n",__LINE__,__FUNCTION__,__FILE__  ); 
//  			Print_Card_Info(&gCard_Block_Info);

			/////// BIA Complete Check ///////////////
			printf("Send Event to Android App using JNI \n");
			gBia_Status = BIA_CHECK_START;


			tv_local.tv_sec = 1 ;
			tv_local.tv_usec = 0 ;
	
			loop_count = BIA_CHECK_WAIT_SEC/tv_local.tv_sec+1 ;
	
			while(loop_count)
			{
				loop_count--;

				FD_ZERO(&rfds_local);
				FD_SET(0,&rfds_local); 		// stdin
		
				tv_local.tv_sec = 1 ;
				tv_local.tv_usec = 0 ;
	
				select_ret_local = select(1, &rfds_local, NULL, NULL, &tv_local);
		
				if (select_ret_local == -1)
				{
					fprintf(stderr,"select error\n");
					perror("select()");
					continue;
				}
				else if (select_ret_local)
				{
					if( FD_ISSET(0,&rfds_local) )
					{			
						memset(stdin_buf, 0 , sizeof(stdin_buf));
						printf("before read stdin\n");
						read(0,stdin_buf,1);
						printf("before after stdin\n");
		
						printf("\n\n\t \033[22;35m  stdin input occurred \033[0m \n"); 
//  						read(0,stdin_buf,sizeof(stdin_buf)); // just read
						break;; // protocol start from #
					}	
				}
				else
				{
					printf(" Wait for BIA Check Completion wait (%d) sec\n", (int)tv_local.tv_sec);
					// break for test
					break;
				}

			}

			printf("loop_count=%d\n",loop_count);
			if( loop_count == 0 )
			{
				printf("\n\n\t \033[22;31m BIA Check Timeout (%3d sec) : Abort Bia Check\033[0m \n",BIA_CHECK_WAIT_SEC); 
				gStatus = STATUS_INIT;
				gBia_Status = BIA_CHECK_INIT;
				write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));
	
				break;
			}

			printf("Bia Check is Completed \n");
			printf("Write Bia Result to RFID \n");


			memcpy(gCard_Block_Info.FullName, "조승훈",strlen("조승훈"));
			gCard_Block_Info.FullName[strlen("조승훈")] = 0 ; 
			gCard_Block_Info.weight = 8010;
			gCard_Block_Info.height =17000;
			gCard_Block_Info.protein =1220;
			gCard_Block_Info.icf =2990;
			gCard_Block_Info.ecf =1500;
			gCard_Block_Info.mm = 420;
			gCard_Block_Info.smm= 3400;
			gCard_Block_Info.fat= 1010;
			gCard_Block_Info.trs= 2660;
			gCard_Block_Info.ras= 336;
			gCard_Block_Info.las= 334;
			gCard_Block_Info.rls= 999;
			gCard_Block_Info.lls= 1000;
			gCard_Block_Info.bmi= 2160;
			gCard_Block_Info.pbf= 1410;
			gCard_Block_Info.od= 9820;
			gCard_Block_Info.whr= 83;
			gCard_Block_Info.vfa= 6330;
			gCard_Block_Info.body_type= 1;
			gCard_Block_Info.body_index= 2;
			gCard_Block_Info.scr= 88; //이것은 100을 곱하지 말아야 함.
			gCard_Block_Info.cwe= 150;
			gCard_Block_Info.cfa= 150;
			gCard_Block_Info.minute= 42;
			gCard_Block_Info.hour= 13;
			gCard_Block_Info.day= 26;
			gCard_Block_Info.month= 5;
			gCard_Block_Info.year= 2014-2014;
			gCard_Block_Info.reserved3= 0;

			gCard_Block_Info.minute +=1 ;
			gCard_Block_Info.minute %= 60 ;

//  			Print_Card_Info(&gCard_Block_Info);
	
//  			hexDump((char *)&gCard_Block_Info.bia_2c,2);
//  			hexDump((char *)&gCard_Block_Info.bia_2d,2);
//  
//  			num_bia_check = swap16(gCard_Block_Info.bia_2d.s);
//  			num_bia_check += 1;
//  			gCard_Block_Info.bia_2d.s = swap16(num_bia_check);
//  			
//  			RFID_WRITE_BLOCK26[5] =  gCard_Block_Info.bia_2c.ch[0];
//  			RFID_WRITE_BLOCK26[6] =  gCard_Block_Info.bia_2c.ch[1];
//  			RFID_WRITE_BLOCK26[7] =  gCard_Block_Info.bia_2d.ch[0];
//  			RFID_WRITE_BLOCK26[8] =  gCard_Block_Info.bia_2d.ch[1];
//  
//  			add_checksum_str(RFID_WRITE_BLOCK26);
//  
//  			hexDump(RFID_WRITE_BLOCK26, sizeof(RFID_WRITE_BLOCK26));
//  			write(uart_fd,RFID_WRITE_BLOCK26,sizeof(RFID_WRITE_BLOCK26));
//  			usleep(100000);
//  
			f_write_fd =  open("gCard_Block_Info.bin", O_RDWR | O_CREAT | O_NONBLOCK | O_SYNC | O_TRUNC, S_IRWXU| S_IRGRP| S_IXGRP | S_IROTH | S_IXOTH );
			write(f_write_fd, &gCard_Block_Info, sizeof(struct _card_block_info));
			close(f_write_fd);
			printf("sizeof(struct _card_block_info)=%d(%02x)\n",(int)sizeof(struct _card_block_info), (int)sizeof(struct _card_block_info));
			printf("sizeof(struct _card_block_info)=%d(%02x)\n",(int)sizeof(struct _card_block_info), (int)sizeof(struct _card_block_info));
			printf("sizeof(struct _card_block_info)=%d(%02x)\n",(int)sizeof(struct _card_block_info), (int)sizeof(struct _card_block_info));
			printf("sizeof(struct _card_block_info)=%d(%02x)\n",(int)sizeof(struct _card_block_info), (int)sizeof(struct _card_block_info));

			gCard_char = (unsigned char *)&gCard_Block_Info;
			for( i = 15 ; i < 28; i++)
			{
				if( i == 25 || i == 26 )
					continue;

				RFID_WRITE_BLOCK[4] = i;
				memcpy(&RFID_WRITE_BLOCK[5],&gCard_char[i*4], 4);
				add_checksum_str(RFID_WRITE_BLOCK);
//  				hexDump(RFID_WRITE_BLOCK, sizeof(RFID_WRITE_BLOCK));
				write(uart_fd,RFID_WRITE_BLOCK,sizeof(RFID_WRITE_BLOCK));
				usleep(100000);
			}
			printf("Card Block Info Write\n");
			
			gStatus = STATUS_INIT;
			gBia_Status = BIA_CHECK_INIT;
			write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));


			INNO_SHCHO_PRINT("\n\n\t \033[22;35m Have a Nice Day ! \033[0m \n"); 

			INNO_SHCHO_PRINT("\n\n\t \033[22;35m Thanks for using N20 Body Composition Analyzer!\033[0m \n"); 


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
		printf("expected=%d, actual=%d\n", residue, ret_local);
		printf("buf_count=%d, residue=%d\n", buf_count, residue);
		buf_count += ret_local;
		residue   -= ret_local;
		printf("buf_count=%d, residue=%d\n", buf_count, residue);
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
	INNO_SHCHO_PRINT("    0  1  2  3  4  5  6  7    8  9  a  b  c  d  e  f\n");
	INNO_SHCHO_PRINT("  ------------------------ -------------------------\n");
	for(i=0 ; i < count ; i++ )
	{
		if( (i % 16) == 0 ) INNO_SHCHO_PRINT("%02x", i);
		INNO_SHCHO_PRINT(" %02x", buf[i]);
		if( (i % 8) == 7 )	INNO_SHCHO_PRINT("  ");
		if( (i % 16) == 15 )	INNO_SHCHO_PRINT(" \n");
	}
	INNO_SHCHO_PRINT("\n");
	INNO_SHCHO_PRINT("  ------------------------ -------------------------\n");
}


int main(int argc, char *argv[])
{
	int ret ;
	struct termios  oldtio,
	                newtio;
	int packet_len;
	int i = 0 ;
	int timeout = 0 ;
	struct _rfid_recv_header recv_header;

	printf("NUGA_ID=0x%02x%02x%02x\n",  NUGA_ID[2], NUGA_ID[1],NUGA_ID[0]);

	if(argc != 2)
	{
		printf("Usage : ./a.exe /dev/com[0-9][0-9] : 실행한 후에 Card를 접촉하면\n");
		printf("     com1~com99   (소문자로)                 \n");
		printf("           --  처음에는 Card Reader : Auto Detect모드 \n");
		printf("           --  Card를 접촉하면 - Reader가 Card UID를 보낸다.\n");
		printf("           --         Dummy Reader Mode로 전환\n");
		printf("           --            기본 신상정보(나이,성별,키,id)와 이전 Data를 읽는다.\n");
		printf("           --            체성분을 측정한다..\n");
		printf("           --            측정이 끝나면 결과를 Write한다.\n");
		printf("           --                                                  \n");
		printf("           --  Card정보를 읽어보고 실패하면 \n");
		printf("           --  Card Reader를 다시  Auto Detect모드로 바꾼다.\n");

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


	tcflush(uart_fd, TCIOFLUSH);
	tcsetattr(uart_fd, TCSANOW, &newtio);

	gStatus = STATUS_INIT;
	write(uart_fd,RFID_SET_AUTODETECT,sizeof(RFID_SET_AUTODETECT));

	loop_stop = NO;
	while(loop_stop == NO)
	{

		FD_ZERO(&rfds);
		FD_SET(uart_fd, &rfds); //uart_fd
		FD_SET(0,&rfds); 		// stdin

		tv.tv_sec = 5 ;
		tv.tv_usec = 0 ;

		timeout = 5 ;

		memset(uart_buf,0,sizeof(uart_buf));

		printf("uart_fd=%d(tv_sec=%d)\n",uart_fd, tv.tv_sec);

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
//  				printf("packet first5= ");
//  				for(i = 0 ; i < 5 ; i++ )
//  					printf("%02x ", uart_buf[i] );
//  				printf("\n");


//  				packet_len = CHANGE_TO_SHORT(uart_buf[4], uart_buf[3]);
				packet_len = swap16(recv_header.packet_length);
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
			fprintf(stderr,"No data within %d seconds.\n",timeout);
			continue;
		}
	
	}

	tcsetattr(uart_fd, TCSANOW, &oldtio);
	close(uart_fd);

	return 1 ;
}







