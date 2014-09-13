struct _GATT_vendor_specific_command
{
	unsigned short Opcode;
	unsigned short connectionHandle;
	unsigned char  CommandPDU[128];
}__attribute__((packed));

struct _GATT_vendor_specific_event
{
	unsigned short Opcode;
	unsigned char  status;
	unsigned short connectionHandle;
	unsigned char  pduLen;
	unsigned char  EventPDU[128];
}__attribute__((packed));

#define GATT_STATUS_CMD_SUCCESS 				0x00
#define GATT_STATUS_CMD_INVALID_PARAM 			0x02
#define GATT_STATUS_CMD_MSG_BUFFER_NOT_AVAIL 	0x04
#define GATT_STATUS_CMD_bleMemAllocError	 	0x13	
#define GATT_STATUS_CMD_bleNotConnected	 		0x14	
#define GATT_STATUS_CMD_bleInvalidPDU	 		0x40	

#define GATT_STATUS_EVENT_SUCCESS				0x00
#define GATT_STATUS_EVENT_bleNotConnected		0x14
#define GATT_STATUS_EVENT_bleTimeout			0x17
#define GATT_STATUS_EVENT_bleProcedureCompletei	0x1A

//  #define GATT_CMD_ExchangeMTU						0xFD82
//  #define GATT_CMD_DiscAllPrimaryServices				0xFD90
//  #define GATT_CMD_DiscPrimaryServiceByUUID			0xFD86
//  #define GATT_CMD_FindIncludedServices				0xFDB0
//  #define GATT_CMD_DiscAllChars						0xFDB2
//  #define GATT_CMD_DiscCharsByUUID					0xFD88
//  #define GATT_CMD_DiscAllCharDescs					0xFD84
//  #define GATT_CMD_ReadCharValue						0xFD8A
//  #define GATT_CMD_ReadUsingCharUUID					0xFDB4
//  #define GATT_CMD_ReadLongCharValue					0xFD8C
//  #define GATT_CMD_ReadMultiCharValues				0xFD8E
//  #define GATT_CMD_WriteNoRsp							0xFDB6
//  #define GATT_CMD_SignedWriteNoRsp					0xFDB8
//  #define GATT_CMD_WriteCharValue						0xFD92
//  #define GATT_CMD_WriteLongCharValue					0xFD96
//  #define GATT_CMD_ReliableWrites						0xFDBA
//  #define GATT_CMD_ReadCharDesc						0xFDBC
//  #define GATT_CMD_ReadLongCharDesc					0xFDBE
//  #define GATT_CMD_WriteCharDesc						0xFDC0
//  #define GATT_CMD_WriteLongCharDesc					0xFDC2
//  #define GATT_CMD_Notification						0xFD9B
//  #define GATT_CMD_Indication							0xFD9D
//  #define GATT_CMD_AddService							0xFDFC
//  #define GATT_CMD_DelService							0xFDFD
//  #define GATT_CMD_AddAttribute						0xFDFE
//  
//  #define GATT_EVENT_ClientCharCfgUpdated				0x0580




