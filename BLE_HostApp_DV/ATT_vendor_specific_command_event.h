struct _ATT_vendor_specific_command
{
	unsigned short Opcode;
	unsigned short connectionHandle;
	unsigned char  CommandPDU[128];
}__attribute__((packed));

struct _ATT_vendor_specific_event
{
	unsigned short Opcode;
	unsigned char  status;
	unsigned short connectionHandle;
	unsigned char  pduLen;
	unsigned char  EventPDU[128];
}__attribute__((packed));


#define ATT_STATUS_CMD_SUCCESS 					0x00
#define ATT_STATUS_CMD_INVALID_PARAM 			0x02
#define ATT_STATUS_CMD_MSG_BUFFER_NOT_AVAIL 	0x04
#define ATT_STATUS_CMD_bleMemAllocError	 		0x13	
#define ATT_STATUS_CMD_bleNotConnected	 		0x14	
#define ATT_STATUS_CMD_blePending	 			0x16	
#define ATT_STATUS_CMD_bleLinkEncrypted	 		0x19	
#define ATT_STATUS_CMD_bleInvalidPDU	 		0x40	
#define ATT_STATUS_CMD_bleInsufficientAuthen	0x41	
#define ATT_STATUS_CMD_bleInsufficientEncrypt	0x42	
#define ATT_STATUS_CMD_bleInsufficientKeySize	0x43	

#define ATT_STATUS_EVENT_SUCCESS				0x00
#define ATT_STATUS_EVENT_bleNotConnected		0x14
#define ATT_STATUS_EVENT_bleTimeout				0x17
#define ATT_STATUS_EVENT_bleProcedureCompletei	0x1A


//  #define ATT_CMD_ErrorRsp			0xFD01
//  #define ATT_CMD_ExchangeMTUReq		0xFD02
//  #define ATT_CMD_ExchangeMTURsp		0xFD03
//  #define ATT_CMD_FindInfoReq			0xFD04
//  #define ATT_CMD_FindInfoRsp			0xFD05
//  #define ATT_CMD_FindByTypeValueReq	0xFD06
//  #define ATT_CMD_FindByTypeValueRsp	0xFD07
//  #define ATT_CMD_ReadByTypeValueReq	0xFD08
//  #define ATT_CMD_ReadByTypeValueRsp	0xFD09
//  #define ATT_CMD_ReadReq				0xFD0A
//  #define ATT_CMD_ReadRsp				0xFD0B
//  #define ATT_CMD_ReadBlobReq			0xFD0C 
//  #define ATT_CMD_ReadBlobRsp			0xFD0D	//No Event
//  #define ATT_CMD_ReadMultiReq		0xFD0E	
//  #define ATT_CMD_ReadMultiRsp		0xFD0F	
//  #define ATT_CMD_ReadByGrpTypeReq	0xFD10	
//  #define ATT_CMD_ReadByGrpTypeRsp	0xFD11	
//  #define ATT_CMD_WriteReq			0xFD12	
//  #define ATT_CMD_WriteRsp			0xFD13	
//  #define ATT_CMD_PrepareWriteReq		0xFD16	
//  #define ATT_CMD_PrepareWriteRsp		0xFD17	
//  #define ATT_CMD_ExecurteWriteReq	0xFD18	
//  #define ATT_CMD_ExecurteWriteRsp	0xFD19	
//  #define ATT_CMD_HandleValueNoti		0xFD1B	
//  #define ATT_CMD_HandleValueIndi		0xFD1D	
//  #define ATT_CMD_HandleValueCfm		0xFD1E	
//  
//  #define ATT_EVENT_ErrorRsp				0x0501
//  #define ATT_EVENT_ExchangeMTUReq		0x0502
//  #define ATT_EVENT_ExchangeMTURsp		0x0503
//  #define ATT_EVENT_FindInfoReq			0x0504
//  #define ATT_EVENT_FindInfoRsp			0x0505
//  #define ATT_EVENT_FindByTypeValueReq	0x0506
//  #define ATT_EVENT_FindByTypeValueRsp	0x0507
//  #define ATT_EVENT_ReadByTypeValueReq	0x0508
//  #define ATT_EVENT_ReadByTypeValueRsp	0x0509
//  #define ATT_EVENT_ReadReq				0x050A
//  #define ATT_EVENT_ReadRsp				0x050B
//  #define ATT_EVENT_ReadBlobReq			0x050C 
//  #define ATT_EVENT_ReadBlobRsp			0x050D	//No Event
//  #define ATT_EVENT_ReadMultiReq		    0x050E	
//  #define ATT_EVENT_ReadMultiRsp		    0x050F	
//  #define ATT_EVENT_ReadByGrpTypeReq	    0x0510	
//  #define ATT_EVENT_ReadByGrpTypeRsp	    0x0511	
//  #define ATT_EVENT_WriteReq			    0x0512	
//  #define ATT_EVENT_WriteRsp				0x0513	
//  #define ATT_EVENT_PrepareWriteReq		0x0516	
//  #define ATT_EVENT_PrepareWriteRsp		0x0517	
//  #define ATT_EVENT_ExecurteWriteReq		0x0518	
//  #define ATT_EVENT_ExecurteWriteRsp		0x0519	
//  #define ATT_EVENT_HandleValueNoti		0x051B	
//  #define ATT_EVENT_HandleValueIndi		0x051D	
//  #define ATT_EVENT_HandleValueCfm		0x051E	
//  
//  
//  
//  
//  
//  
//  
