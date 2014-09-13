                                                    //       OGF | OCF     Opcode
#define HCI_CMD_LE_SetEventMask                       0x2001 // (8 << 10 |  1 )   //0x2001
#define HCI_CMD_LE_ReadBufferSize                     0x2002 // (8 << 10 |  2 )   //0x2002
#define HCI_CMD_LE_ReadLocalSupportedFeature          0x2003 // (8 << 10 |  3 )   //0x2003
#define HCI_CMD_LE_SetRandomAddress                   0x2005 // (8 << 10 |  5 )   //0x2005
#define HCI_CMD_LE_SetAdvertisingParameters           0x2006 // (8 << 10 |  6 )   //0x2006
#define HCI_CMD_LE_ReadAdvertisingChannelTXPower      0x2007 // (8 << 10 |  7 )   //0x2007
#define HCI_CMD_LE_SetAdvertisingData                 0x2008 // (8 << 10 |  8 )   //0x2008
#define HCI_CMD_LE_SetScanResponseData                0x2009 // (8 << 10 |  9 )   //0x2009
#define HCI_CMD_LE_SetAdvertiseEnable                 0x200A // (8 << 10 | 10 )   //0x200A
#define HCI_CMD_LE_SetScanParameters                  0x200B // (8 << 10 | 11 )   //0x200B
#define HCI_CMD_LE_SetScanEnable                      0x200C // (8 << 10 | 12 )   //0x200C
#define HCI_CMD_LE_CreateConnection                   0x200D // (8 << 10 | 13 )   //0x200D
#define HCI_CMD_LE_CreateConnectionCancel             0x200E // (8 << 10 | 14 )   //0x200E
#define HCI_CMD_LE_ReadWhiteListSize                  0x200F // (8 << 10 | 15 )   //0x200F
#define HCI_CMD_LE_ClearWhiteList                     0x2010 // (8 << 10 | 16 )   //0x2010
#define HCI_CMD_LE_AddDeviceToWhiteList               0x2011 // (8 << 10 | 17 )   //0x2011
#define HCI_CMD_LE_RemoveDeviceFromWhiteList          0x2012 // (8 << 10 | 18 )   //0x2012
#define HCI_CMD_LE_ConnectionUpdate                   0x2013 // (8 << 10 | 19 )   //0x2013
#define HCI_CMD_LE_SetHostChannelClassification       0x2014 // (8 << 10 | 20 )   //0x2014
#define HCI_CMD_LE_ReadChannelMap                     0x2015 // (8 << 10 | 21 )   //0x2015
#define HCI_CMD_LE_ReadRemoteUsedFeatures             0x2016 // (8 << 10 | 22 )   //0x2016
#define HCI_CMD_LE_Encrypt                            0x2017 // (8 << 10 | 23 )   //0x2017
#define HCI_CMD_LE_Rand                               0x2018 // (8 << 10 | 24 )   //0x2018
#define HCI_CMD_LE_StartEncryption                    0x2019 // (8 << 10 | 25 )   //0x2019
#define HCI_CMD_LE_LongTermKeyRequestedReply          0x201A // (8 << 10 | 26 )   //0x201A
#define HCI_CMD_LE_LongTermKeyRequestedNegativeReply  0x201B // (8 << 10 | 27 )   //0x201B
#define HCI_CMD_LE_ReadSupportedStates                0x201C // (8 << 10 | 28 )   //0x201C
#define HCI_CMD_LE_ReceiverTest                       0x201D // (8 << 10 | 29 )   //0x201D
#define HCI_CMD_LE_TransmitterTest                    0x201E // (8 << 10 | 30 )   //0x201E
#define HCI_CMD_LE_TestEndCommand                     0x201F // (8 << 10 | 31 )   //0x201F

// Internet에서 찾아서 적는다.
// http://www.dziwior.org/Bluetooth/HCI_Commands.html
// Link Control                                                             OGF     OCF        Op-code               
#define HCI_CMD_Inquiry                           0x0401 // (1 << 10 |  1 ) //  0x01    0x0001    0x0401    V1.1    V1.2    Inquiry
#define HCI_CMD_InquiryCancle                     0x0402 // (1 << 10 |  2 ) //  0x01    0x0002    0x0402    V1.1    V1.2    Inquiry_Cancel
#define HCI_CMD_PeriodicInquiryMode               0x0403 // (1 << 10 |  3 ) //  0x01    0x0003    0x0403    V1.1    V1.2    Periodic_Inquiry_Mode
#define HCI_CMD_ExitPeriodicInquiryMode           0x0404 // (1 << 10 |  4 ) //  0x01    0x0004    0x0404    V1.1    V1.2    Exit_Periodic_Inquiry_Mode
#define HCI_CMD_CreateConnection                  0x0405 // (1 << 10 |  5 ) //  0x01    0x0005    0x0405    V1.1    V1.2    Create_Connection
#define HCI_CMD_Disconnect                        0x0406 // (1 << 10 |  6 ) //  0x01    0x0006    0x0406    V1.1    V1.2    Disconnect
#define HCI_CMD_AddSCOConnection                  0x0407 // (1 << 10 |  7 ) //  0x01    0x0007    0x0407    V1.1    —        Add_SCO_Connection
#define HCI_CMD_CreateConnectionCancel            0x0408 // (1 << 10 |  8 ) //  0x01    0x0008    0x0408    —        V1.2    Create_Connection _Cancel
#define HCI_CMD_AcceptConnectionCancel            0x0409 // (1 << 10 |  9 ) //  0x01    0x0009    0x0409    V1.1    V1.2    Accept_Connection_Request
#define HCI_CMD_RejectConnectionCancel            0x040A // (1 << 10 | 10 ) //  0x01    0x000A    0x040A    V1.1    V1.2    Reject_Connection_Request
#define HCI_CMD_LinkKeyRequestReply               0x040B // (1 << 10 | 11 ) //  0x01    0x000B    0x040B    V1.1    V1.2    Link_Key_Request_Reply
#define HCI_CMD_LinkKeyRequestNegativeReply       0x040C // (1 << 10 | 12 ) //  0x01    0x000C    0x040C    V1.1    V1.2    Link_Key_Request_Negative_Reply
#define HCI_CMD_PinCodeRequestReply               0x040D // (1 << 10 | 13 ) //  0x01    0x000D    0x040D    V1.1    V1.2    PIN_Code_Request_Reply
#define HCI_CMD_PinCodeRequestNegativeReply       0x040E // (1 << 10 | 14 ) //  0x01    0x000E    0x040E    V1.1    V1.2    PIN_Code_Request_Negative_Reply
#define HCI_CMD_ChangeConnectionPacketType        0x040F // (1 << 10 | 15 ) //  0x01    0x000F    0x040F    V1.1    V1.2    Change_Connection_Packet_Type
//  #define HCI_CMD_Inquiry                       0x0410 // (1 << 10 | 16 ) //  0x01    0x0010    0x0410              not used
#define HCI_CMD_AuthenticationRequested           0x0411 // (1 << 10 | 17 ) //  0x01    0x0011    0x0411    V1.1    V1.2    Authentication_Requested
//  #define HCI_CMD_Inquiry                       0x0412 // (1 << 10 | 18 ) //  0x01    0x0012    0x0412              not used
#define HCI_CMD_SetConnectionEncryption            0x0413 // (1 << 10 | 19 ) //  0x01    0x0013    0x0413    V1.1    V1.2    Set_Connection_Encryption
//  #define HCI_CMD_Inquiry                        0x0414 // (1 << 10 | 20 ) //  0x01    0x0014    0x0414              not used
#define HCI_CMD_ChangeConnectionLinkKey            0x0415 // (1 << 10 | 21 ) //  0x01    0x0015    0x0415    V1.1    V1.2    Change_Connection_Link_Key
//  #define HCI_CMD_Inquiry                        0x0416 // (1 << 10 | 22 ) //  0x01    0x0016    0x0416              not used
#define HCI_CMD_MasterLinkKey                      0x0417 // (1 << 10 | 23 ) //  0x01    0x0017    0x0417    V1.1    V1.2    Master_Link_Key
//  #define HCI_CMD_Inquiry                        0x0418 // (1 << 10 | 24 ) //  0x01    0x0018    0x0418              not used
#define HCI_CMD_RemoteNameRequest                  0x0419 // (1 << 10 | 25 ) //  0x01    0x0019    0x0419    V1.1    V1.2    Remote_Name_Request
#define HCI_CMD_RemoteNameRequestCancel            0x041A // (1 << 10 | 26 ) //  0x01    0x001A    0x041A    —        V1.2    Remote_Name_Request_Cancel
#define HCI_CMD_ReadRemoteSupportedFeatures        0x041B // (1 << 10 | 27 ) //  0x01    0x001B    0x041B    V1.1    V1.2    Read_Remote_Supported_Features
#define HCI_CMD_ReadRemoteExtendedFeatures         0x041C // (1 << 10 | 28 ) //  0x01    0x001C    0x041C    —        V1.2    Read_Remote_Extended_Features
#define HCI_CMD_ReadRemoteVersionInfomation        0x041D // (1 << 10 | 29 ) //  0x01    0x001D    0x041D    V1.1    V1.2    Read_Remote_Version_Information
//  #define HCI_CMD_Inquiry                        0x041E // (1 << 10 | 30 ) //  0x01    0x001E    0x041E              not used
#define HCI_CMD_ReadClockOffset                    0x041F // (1 << 10 | 31 ) //  0x01    0x001F    0x041F    V1.1    V1.2    Read_Clock_Offset
#define HCI_CMD_ReadLMP_Handle                     0x0420 // (1 << 10 | 32 ) //  0x01    0x0020    0x0420    —        V1.2    Read_LMP_Handle
//  #define HCI_CMD_Inquiry                        0x0421 // (1 << 10 | 33 ) //  0x01    0x0021    0x0421              not used
//  #define HCI_CMD_Inquiry                        0x0422 // (1 << 10 | 34 ) //  0x01    0x0022    0x0422              not used
//  #define HCI_CMD_Inquiry                        0x0423 // (1 << 10 | 35 ) //  0x01    0x0023    0x0423              not used
//  #define HCI_CMD_Inquiry                        0x0424 // (1 << 10 | 36 ) //  0x01    0x0024    0x0424              not used
//  #define HCI_CMD_Inquiry                        0x0425 // (1 << 10 | 37 ) //  0x01    0x0025    0x0425              not used
//  #define HCI_CMD_Inquiry                        0x0426 // (1 << 10 | 38 ) //  0x01    0x0026    0x0426              not used
//  #define HCI_CMD_Inquiry                        0x0427 // (1 << 10 | 39 ) //  0x01    0x0027    0x0427              not used
#define HCI_CMD_SetupSynchronousConnection         0x0428 // (1 << 10 | 40 ) //  0x01    0x0028    0x0428    —        V1.2    Setup_Synchronous_Connection
#define HCI_CMD_AcceptSynchronousConnection        0x0429 // (1 << 10 | 41 ) //  0x01    0x0029    0x0429    —        V1.2    Accept_Synchronous_Connection_Request
#define HCI_CMD_RejectSynchronousConnection        0x042A // (1 << 10 | 42 ) //  0x01    0x002A    0x042A    —        V1.2    Reject_Synchronous_Connection_Request


// Link Policy                                                               OGF     OCF        Op-code               
#define HCI_CMD_HoldMode                           0x0801 // (2 << 10 |  1 ) //  0x02    0x0001    0x0801    V1.1    V1.2    Hold_Mode
//  #define HCI_CMD_Inquiry                        0x0802 // (2 << 10 |  2 ) //  0x02    0x0002    0x0802              not used
#define HCI_CMD_SniffMode                          0x0803 // (2 << 10 |  3 ) //  0x02    0x0003    0x0803    V1.1    V1.2    Sniff_Mode
#define HCI_CMD_ExitSniffMode                      0x0804 // (2 << 10 |  4 ) //  0x02    0x0004    0x0804    V1.1    V1.2    Exit_Sniff_Mode
#define HCI_CMD_ParkMode                           0x0805 // (2 << 10 |  5 ) //  0x02    0x0005    0x0805    V1.1    V1.2    Park_Mode
#define HCI_CMD_ExitParkMode                       0x0806 // (2 << 10 |  6 ) //  0x02    0x0006    0x0806    V1.1    V1.2    Exit_Park_Mode
#define HCI_CMD_QoSSetup                           0x0807 // (2 << 10 |  7 ) //  0x02    0x0007    0x0807    V1.1    V1.2    QoS_Setup
//  #define HCI_CMD_Inquiry                        0x0808 // (2 << 10 |  8 ) //  0x02    0x0008    0x0808              not used
#define HCI_CMD_RoleDiscovery                      0x0809 // (2 << 10 |  9 ) //  0x02    0x0009    0x0809    V1.1    V1.2    Role_Discovery
//  #define HCI_CMD_Inquiry                        0x080A // (2 << 10 | 10 ) //  0x02    0x000A    0x080A              not used
#define HCI_CMD_SwitchRole                         0x080B // (2 << 10 | 11 ) //  0x02    0x000B    0x080B    V1.1    V1.2    Switch_Role
#define HCI_CMD_ReadLinkPolicySettings             0x080C // (2 << 10 | 12 ) //  0x02    0x000C    0x080C    V1.1    V1.2    Read_Link_Policy_Settings
#define HCI_CMD_WriteLinkPolicySettings            0x080D // (2 << 10 | 13 ) //  0x02    0x000D    0x080D    V1.1    V1.2    Write_Link_Policy_Settings
#define HCI_CMD_ReadDefaultLinkPolicySettings      0x080E // (2 << 10 | 14 ) //  0x02    0x000E    0x080E    —        V1.2    Read_Default_Link_Policy_Settings
#define HCI_CMD_WriteDefaultLinkPolicySettings     0x080F // (2 << 10 | 15 ) //  0x02    0x000F    0x080F    —        V1.2    Write_Default_Link_Policy_Settings
#define HCI_CMD_FlowSpecification                  0x0810 // (2 << 10 | 16 ) //  0x02    0x0010    0x0810    —        V1.2    Flow_Specification
                                                         
// Host Controller and baseband                                                  OGF     OCF           Op-code               
#define HCI_CMD_SetEventMask                       0x0C01 // (3 << 10 |  1 ) //  0x03    0x0001    0x0C01    V1.1    V1.2    Set_Event_Mask
//  #define HCI_CMD_Inquiry                        0x0C02 // (3 << 10 |  2 ) //  0x03    0x0002    0x0C02              not used
#define HCI_CMD_Reset                              0x0C03 // (3 << 10 |  3 ) //  0x03    0x0003    0x0C03    V1.1    V1.2    Reset
//  #define HCI_CMD_Inquiry                        0x0C04 // (3 << 10 |  4 ) //  0x03    0x0004    0x0C04              not used
#define HCI_CMD_SetEventFilter                     0x0C05 // (3 << 10 |  5 ) //  0x03    0x0005    0x0C05    V1.1    V1.2    Set_Event_Filter
//  #define HCI_CMD_Inquiry                        0x0C06 // (3 << 10 |  6 ) //  0x03    0x0006    0x0C06              not used
//  #define HCI_CMD_Inquiry                        0x0C07 // (3 << 10 |  7 ) //  0x03    0x0007    0x0C07              not used
#define HCI_CMD_Flush                              0x0C08 // (3 << 10 |  8 ) //  0x03    0x0008    0x0C08    V1.1    V1.2    Flush
#define HCI_CMD_ReadPINType                        0x0C09 // (3 << 10 |  9 ) //  0x03    0x0009    0x0C09    V1.1    V1.2    Read_PIN_Type
#define HCI_CMD_WritePINType                       0x0C0A // (3 << 10 | 10 ) //  0x03    0x000A    0x0C0A    V1.1    V1.2    Write_PIN_Type
#define HCI_CMD_CreateNewUnitKey                   0x0C0B // (3 << 10 | 11 ) //  0x03    0x000B    0x0C0B    V1.1    V1.2    Create_New_Unit_Key
//  #define HCI_CMD_Inquiry                        0x0C0C // (3 << 10 | 12 ) //  0x03    0x000C    0x0C0C              not used
#define HCI_CMD_ReadStoredLinkKey                  0x0C0D // (3 << 10 | 13 ) //  0x03    0x000D    0x0C0D    V1.1    V1.2    Read_Stored_Link_Key
//  #define HCI_CMD_Inquiry                        0x0C0E // (3 << 10 | 14 ) //  0x03    0x000E    0x0C0E              not used
//  #define HCI_CMD_Inquiry                        0x0C0F // (3 << 10 | 15 ) //  0x03    0x000F    0x0C0F              not used
//  #define HCI_CMD_Inquiry                        0x0C10 // (3 << 10 | 16 ) //  0x03    0x0010    0x0C10              not used
#define HCI_CMD_WriteStoredLinkKey                 0x0C11 // (3 << 10 | 17 ) //  0x03    0x0011    0x0C11    V1.1    V1.2    Write_Stored_Link_Key
#define HCI_CMD_DeleteStoredLinkKey                0x0C12 // (3 << 10 | 18 ) //  0x03    0x0012    0x0C12    V1.1    V1.2    Delete_Stored_Link_Key
#define HCI_CMD_WriteLocalName                     0x0C13 // (3 << 10 | 19 ) //  0x03    0x0013    0x0C13    V1.1    V1.2    Write_Local_Name (previously Change_Local_Name)
#define HCI_CMD_ReadLocalName                      0x0C14 // (3 << 10 | 20 ) //  0x03    0x0014    0x0C14    V1.1    V1.2    Read_Local_Name
#define HCI_CMD_ReadConnectionAcceptTimeout        0x0C15 // (3 << 10 | 21 ) //  0x03    0x0015    0x0C15    V1.1    V1.2    Read_Connection_Accept_Timeout
#define HCI_CMD_WriteConnectionAcceptTimeout       0x0C16 // (3 << 10 | 22 ) //  0x03    0x0016    0x0C16    V1.1    V1.2    Write_Connection_Accept_Timeout
#define HCI_CMD_ReadPageTimeout                    0x0C17 // (3 << 10 | 23 ) //  0x03    0x0017    0x0C17    V1.1    V1.2    Read_Page_Timeout
#define HCI_CMD_WritePageTimeout                   0x0C18 // (3 << 10 | 24 ) //  0x03    0x0018    0x0C18    V1.1    V1.2    Write_Page_Timeout
#define HCI_CMD_ReadScanEnable                     0x0C19 // (3 << 10 | 25 ) //  0x03    0x0019    0x0C19    V1.1    V1.2    Read_Scan_Enable
#define HCI_CMD_WriteScanEnable                    0x0C1A // (3 << 10 | 26 ) //  0x03    0x001A    0x0C1A    V1.1    V1.2    Write_Scan_Enable
#define HCI_CMD_ReadPageScanActivity               0x0C1B // (3 << 10 | 27 ) //  0x03    0x001B    0x0C1B    V1.1    V1.2    Read_Page_Scan_Activity
#define HCI_CMD_WritePageScanActivity              0x0C1C // (3 << 10 | 28 ) //  0x03    0x001C    0x0C1C    V1.1    V1.2    Write_Page_Scan_Activity
#define HCI_CMD_ReadInquiryScanActivity            0x0C1D // (3 << 10 | 29 ) //  0x03    0x001D    0x0C1D    V1.1    V1.2    Read_Inquiry_Scan_Activity
#define HCI_CMD_WriteInquiryScanActivity           0x0C1E // (3 << 10 | 30 ) //  0x03    0x001E    0x0C1E    V1.1    V1.2    Write_Inquiry_Scan_Activity
#define HCI_CMD_ReadAuthenticationEnable           0x0C1F // (3 << 10 | 31 ) //  0x03    0x001F    0x0C1F    V1.1    V1.2    Read_Authentication_Enable
#define HCI_CMD_WriteAuthenticationEnable          0x0C20 // (3 << 10 | 32 ) //  0x03    0x0020    0x0C20    V1.1    V1.2    Write_Authentication_Enable
#define HCI_CMD_ReadEncryptionMode                 0x0C21 // (3 << 10 | 33 ) //  0x03    0x0021    0x0C21    V1.1    V1.2    Read_Encryption_Mode
#define HCI_CMD_WriteEncryptionMode                0x0C22 // (3 << 10 | 34 ) //  0x03    0x0022    0x0C22    V1.1    V1.2    Write_Encryption_Mode
#define HCI_CMD_ReadClassOfDevice                  0x0C23 // (3 << 10 | 35 ) //  0x03    0x0023    0x0C23    V1.1    V1.2    Read_Class_of_Device
#define HCI_CMD_WriteClassOfDevice                 0x0C24 // (3 << 10 | 36 ) //  0x03    0x0024    0x0C24    V1.1    V1.2    Write_Class_of_Device
#define HCI_CMD_ReadVoiceSetting                   0x0C25 // (3 << 10 | 37 ) //  0x03    0x0025    0x0C25    V1.1    V1.2    Read_Voice_Setting
#define HCI_CMD_WriteVoiceSetting                  0x0C26 // (3 << 10 | 38 ) //  0x03    0x0026    0x0C26    V1.1    V1.2    Write_Voice_Setting
#define HCI_CMD_ReadAutomaticFlushTimeout          0x0C27 // (3 << 10 | 39 ) //  0x03    0x0027    0x0C27    V1.1    V1.2    Read_Automatic_Flush_Timeout
#define HCI_CMD_WriteAutomaticFlushTimeout         0x0C28 // (3 << 10 | 40 ) //  0x03    0x0028    0x0C28    V1.1    V1.2    Write_Automatic_Flush_Timeout
#define HCI_CMD_ReadNum_Broadcast_Retransmissions  0x0C29 // (3 << 10 | 41 ) //  0x03    0x0029    0x0C29    V1.1    V1.2    Read_Num_Broadcast_Retransmissions
#define HCI_CMD_WriteNum_Broadcast_Retransmissions 0x0C2A // (3 << 10 | 42 ) //  0x03    0x002A    0x0C2A    V1.1    V1.2    Write_Num_Broadcast_Retransmissions
#define HCI_CMD_ReadHoldModeActivity               0x0C2B // (3 << 10 | 43 ) //  0x03    0x002B    0x0C2B    V1.1    V1.2    Read_Hold_Mode_Activity
#define HCI_CMD_WriteHoldModeActivity              0x0C2C // (3 << 10 | 44 ) //  0x03    0x002C    0x0C2C    V1.1    V1.2    Write_Hold_Mode_Activity
#define HCI_CMD_ReadTransmitPowerControl           0x0C2D // (3 << 10 | 45 ) //  0x03    0x002D    0x0C2D    V1.1    V1.2    Read_Transmit_Power_Level
#define HCI_CMD_ReadSCOFlowControlEnable           0x0C2E // (3 << 10 | 46 ) //  0x03    0x002E    0x0C2E    V1.1    V1.2    Read_SCO_Flow_Control_Enable
#define HCI_CMD_WriteSCOFlowControlEnable          0x0C2F // (3 << 10 | 47 ) //  0x03    0x002F    0x0C2F    V1.1    V1.2    Write_SCO_Flow_Control_Enable
//  #define HCI_CMD_Inquiry                        0x0C30 // (3 << 10 | 48 ) //  0x03    0x0030    0x0C30              not used
#define HCI_CMD_SetHostControllerToHostFlowControl 0x0C31 // (3 << 10 | 49 ) //  0x03    0x0031    0x0C31    V1.1    V1.2    Set_Host_Controller_To_Host_Flow_Control
//  #define HCI_CMD_Inquiry                        0x0C32 // (3 << 10 | 50 ) //  0x03    0x0032    0x0C32              not used
#define HCI_CMD_HostBufferSize                     0x0C33 // (3 << 10 | 51 ) //  0x03    0x0033    0x0C33    V1.1    V1.2    Host_Buffer_Size
//  #define HCI_CMD_Inquiry                        0x0C34 // (3 << 10 | 52 ) //  0x03    0x0034    0x0C34              not used
#define HCI_CMD_HostNumOfCompletedPackets          0x0C35 // (3 << 10 | 53 ) //  0x03    0x0035    0x0C35    V1.1    V1.2    Host_Number_Of_Completed_Packets
#define HCI_CMD_ReadLinkSupervisinTimeout          0x0C36 // (3 << 10 | 54 ) //  0x03    0x0036    0x0C36    V1.1    V1.2    Read_Link_Supervision_Timeout
#define HCI_CMD_WriteLinkSupervisinTimeout         0x0C37 // (3 << 10 | 55 ) //  0x03    0x0037    0x0C37    V1.1    V1.2    Write_Link_Supervision_Timeout
#define HCI_CMD_ReadNumOfSupportedIAC              0x0C38 // (3 << 10 | 56 ) //  0x03    0x0038    0x0C38    V1.1    V1.2    Read_Number_Of_Supported_IAC
#define HCI_CMD_ReadCurrentIACLAP                  0x0C39 // (3 << 10 | 57 ) //  0x03    0x0039    0x0C39    V1.1    V1.2    Read_Current_IAC_LAP
#define HCI_CMD_WriteCurrentIACLAP                 0x0C3A // (3 << 10 | 58 ) //  0x03    0x003A    0x0C3A    V1.1    V1.2    Write_Current_IAC_LAP
#define HCI_CMD_ReadPageScanPeriodMode             0x0C3B // (3 << 10 | 59 ) //  0x03    0x003B    0x0C3B    V1.1    V1.2    Read_Page_Scan_Period_Mode
#define HCI_CMD_WritePageScanPeriodMode            0x0C3C // (3 << 10 | 60 ) //  0x03    0x003C    0x0C3C    V1.1    V1.2    Write_Page_Scan_Period_Mode
#define HCI_CMD_ReadPageScanMode                   0x0C3D // (3 << 10 | 61 ) //  0x03    0x003D    0x0C3D    V1.1    —        Read_Page_Scan_Mode
#define HCI_CMD_WritePageScanMode                  0x0C3E // (3 << 10 | 62 ) //  0x03    0x003E    0x0C3E    V1.1    —        Write_Page_Scan_Mode
#define HCI_CMD_SetAFHHostChannelClassification    0x0C3F // (3 << 10 | 63 ) //  0x03    0x003F    0x0C3F    —        V1.2    Set_AFH_Host_Channel_ Classification
//  #define HCI_CMD_Inquiry                        0x0C40 // (3 << 10 | 64 ) //  0x03    0x0040    0x0C40              not used
//  #define HCI_CMD_Inquiry                        0x0C41 // (3 << 10 | 65 ) //  0x03    0x0041    0x0C41              not used
#define HCI_CMD_ReadInquiryScanType                0x0C42 // (3 << 10 | 66 ) //  0x03    0x0042    0x0C42    —        V1.2    Read_Inquiry_Scan_Type
#define HCI_CMD_WriteInquiryScanType               0x0C43 // (3 << 10 | 67 ) //  0x03    0x0043    0x0C43    —        V1.2    Write_Inquiry_Scan_Type
#define HCI_CMD_ReadInquiryMode                    0x0C44 // (3 << 10 | 68 ) //  0x03    0x0044    0x0C44    —        V1.2    Read_Inquiry_Mode
#define HCI_CMD_WriteInquiryMode                   0x0C45 // (3 << 10 | 69 ) //  0x03    0x0045    0x0C45    —        V1.2    Write_Inquiry_Mode
#define HCI_CMD_ReadPageScanType                   0x0C46 // (3 << 10 | 70 ) //  0x03    0x0046    0x0C46    —        V1.2    Read_Page_Scan_Type
#define HCI_CMD_WritePageScanType                  0x0C47 // (3 << 10 | 71 ) //  0x03    0x0047    0x0C47    —        V1.2    Write_Page_Scan_Type
#define HCI_CMD_ReadAFHChannelAssessmentMode       0x0C48 // (3 << 10 | 72 ) //  0x03    0x0048    0x0C48    —        V1.2    Read_AFH_Channel_Assessment_Mode
#define HCI_CMD_WriteAFHChannelAssessmentMode      0x0C49 // (3 << 10 | 73 ) //  0x03    0x0049    0x0C49    —        V1.2    Write_AFH_Channel_Assessment_Mode
                                                         
// Infomation Parameter Command                              OGF     OCF        Op-code               
#define HCI_CMD_ReadLocaVersionInfomation          0x1001 // (4 << 10 |  1 ) //  0x04    0x0001    0x1001    V1.1    V1.2    Read_Local_Version_Information
#define HCI_CMD_ReadLocalSupportedCommands         0x1002 // (4 << 10 |  2 ) //  0x04    0x0002    0x1002    —        V1.2    Read_Local_Supported_Commands
#define HCI_CMD_ReadLocalSupportedFeatures         0x1003 // (4 << 10 |  3 ) //  0x04    0x0003    0x1003    V1.1    V1.2    Read_Local_Supported_Features
#define HCI_CMD_ReadLocalExtendedFeatures          0x1004 // (4 << 10 |  4 ) //  0x04    0x0004    0x1004    —        V1.2    Read_Local_ Extended_Features
#define HCI_CMD_ReadBufferSize                     0x1005 // (4 << 10 |  5 ) //  0x04    0x0005    0x1005    V1.1    V1.2    Read_Buffer_Size
//  #define HCI_CMD_Inquiry                        0x1006 // (4 << 10 |  6 ) //  0x04    0x0006    0x1006              not used
#define HCI_CMD_ReadCountryCode                    0x1007 // (4 << 10 |  7 ) //  0x04    0x0007    0x1007    V1.1    —        Read_Country_Code
//  #define HCI_CMD_Inquiry                        0x1008 // (4 << 10 |  8 ) //  0x04    0x0008    0x1008              not used
#define HCI_CMD_ReadBDADDR                         0x1009 // (4 << 10 |  9 ) //  0x04    0x0009    0x1009    V1.1    V1.2    Read_BD_ADDR
                                                         
// Status  Parameter Command                                 OGF     OCF        Op-code               
#define HCI_CMD_ReadFailedContactCounter           0x1401 // (5 << 10 |  1 ) //  0x05    0x0001    0x1401    V1.1    V1.2    Read_Failed_Contact_Counter
#define HCI_CMD_ResetFailedContactCounter          0x1402 // (5 << 10 |  2 ) //  0x05    0x0002    0x1402    V1.1    V1.2    Reset_Failed_Contact_Counter
#define HCI_CMD_GetLinkQuality                     0x1403 // (5 << 10 |  3 ) //  0x05    0x0003    0x1403    V1.1    V1.2    Get_Link_Quality
//  #define HCI_CMD_Inquiry                        0x1404 // (5 << 10 |  4 ) //  0x05    0x0004    0x1404              not used
#define HCI_CMD_ReadRSSI                           0x1405 // (5 << 10 |  5 ) //  0x05    0x0005    0x1405    V1.1    V1.2    Read_RSSI
#define HCI_CMD_ReadAFHChannelMap                  0x1406 // (5 << 10 |  6 ) //  0x05    0x0006    0x1406    —        V1.2    Read_AFH _Channel_Map
#define HCI_CMD_ReadClock                          0x1407 // (5 << 10 |  7 ) //  0x05    0x0007    0x1407    —        V1.2    Read_Clock
 
//=========================================================================================
// TI Vendor Specific HCI 에는 아래만 있다.
//
//  #define HCI_CMD_Disconnect                       (1 << 10 |  6 )   //0x0406
//  #define HCI_CMD_ReadRemoteVersionInfomation      (1 << 10 | 29 )   //0x041D

//  #define HCI_CMD_SetEventMask                     (3 << 10 |  1 )   //0x0C01
//  #define HCI_CMD_Reset                            (3 << 10 |  3 )   //0x0C03
//  #define HCI_CMD_ReadTransmitPorwerLevel          (3 << 10 | 45 )   //0x0C2D
//  #define HCI_CMD_SetControllerToHostFlowControl   (3 << 10 | 49 )   //0x0C31
//  #define HCI_CMD_HostBufferSize                   (3 << 10 | 51 )   //0x0C33
//  #define HCI_CMD_HostNumberofCompletedPackets     (3 << 10 | 53 )   //0x0C35
//  
//  #define HCI_CMD_ReadLocalVersionInfomation       (4 << 10 |  1 )   //0x1001
//  #define HCI_CMD_ReadLocalSupportedCommand        (4 << 10 |  2 )   //0x1002
//  #define HCI_CMD_ReadLocalSupportedFeatures       (4 << 10 |  3 )   //0x1003
//  #define HCI_CMD_ReadBD_ADDR                      (4 << 10 |  9 )   //0x1009
//  
//  #define HCI_CMD_ReadRSSI                         (5 << 10 |  5 )   //0x1405
//=========================================================================================


#define HCI_EVENT_LE_EventCode                                      0x3E
#define HCI_EVENT_LE_ConnectionComplete_SubEvent                    0x01
#define HCI_EVENT_LE_AdvertisingReport_SubEvent                     0x02
#define HCI_EVENT_LE_ConnectionUpdateComplete_SubEvent              0x03
#define HCI_EVENT_LE_ReadRemoteUsedFeafuresComplete_SubEvent        0x04
#define HCI_EVENT_LE_LongTermKeyRequested_SubEvent                  0x05

#define HCI_EVENT_DisconnectionComplete                0x05
#define HCI_EVENT_EncryptionChnage                     0x08
#define HCI_EVENT_ReadRemoteVersionInfomationComplete  0x0C
#define HCI_EVENT_CommandComplete                      0x0E
#define HCI_EVENT_CommandStatus                        0x0F
#define HCI_EVENT_HardwareError                        0x10
#define HCI_EVENT_NumberOfCompletedPackets             0x13
#define HCI_EVENT_DataBufferOverflow                   0x1A
#define HCI_EVENT_EncryptionKeyRefreshComplete         0x30

// HCI Vendor Specific Command Opcode, CSG=0..6
//    f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0   
//  [ VendorSpecific 0x3f ] [ CSG     ] [ Command                  ]  
// 111111b(6bit) + CSG(=0..6)(3bit) + Command(7bit)

// HCI Vendor Specific Command Opcode, CSG=7
// 111111b(6bit) + CSG(=7   )(3bit) + ProfileID(7bit) + ProfileCommand(8bit)

// CSG : Command Opcode Subgroups
// CSG 0 : HCI
// CSG 1 : L2CAP
// CSG 2 : ATT
// CSG 3 : GATT
// CSG 4 : GAP
// CSG 5 : UTIL
// CSG 6 : Reserved
// CSG 7 : User Profile

#define HCI_CMD_Ext_SetRxGain                      0xFC00 // ( (63<<10) | ( 0 << 7 ) | (  0 << 0 ) ) // 0xFC00
#define HCI_CMD_Ext_SetTxPower                     0xFC01 // ( (63<<10) | ( 0 << 7 ) | (  1 << 0 ) ) // 0xFC01
#define HCI_CMD_Ext_OnePacketPerEvent              0xFC02 // ( (63<<10) | ( 0 << 7 ) | (  2 << 0 ) ) // 0xFC02
#define HCI_CMD_Ext_ClockDivideOnHalt              0xFC03 // ( (63<<10) | ( 0 << 7 ) | (  3 << 0 ) ) // 0xFC03
#define HCI_CMD_Ext_DeclareNVUsage                 0xFC04 // ( (63<<10) | ( 0 << 7 ) | (  4 << 0 ) ) // 0xFC04
#define HCI_CMD_Ext_Decrypt                        0xFC05 // ( (63<<10) | ( 0 << 7 ) | (  5 << 0 ) ) // 0xFC05
#define HCI_CMD_Ext_SetLocalSupportedFeatures      0xFC06 // ( (63<<10) | ( 0 << 7 ) | (  6 << 0 ) ) // 0xFC06
#define HCI_CMD_Ext_SetFastTxResponseTime          0xFC07 // ( (63<<10) | ( 0 << 7 ) | (  7 << 0 ) ) // 0xFC07
#define HCI_CMD_Ext_ModemTestTx                    0xFC08 // ( (63<<10) | ( 0 << 7 ) | (  8 << 0 ) ) // 0xFC08
#define HCI_CMD_Ext_ModemHopTestTx                 0xFC09 // ( (63<<10) | ( 0 << 7 ) | (  9 << 0 ) ) // 0xFC09
#define HCI_CMD_Ext_ModemTestRx                    0xFC0A // ( (63<<10) | ( 0 << 7 ) | ( 10 << 0 ) ) // 0xFC0A
#define HCI_CMD_Ext_EndModemTest                   0xFC0B // ( (63<<10) | ( 0 << 7 ) | ( 11 << 0 ) ) // 0xFC0B
#define HCI_CMD_Ext_SetBDADDR                      0xFC0C // ( (63<<10) | ( 0 << 7 ) | ( 12 << 0 ) ) // 0xFC0C
#define HCI_CMD_Ext_SetSCA                         0xFC0D // ( (63<<10) | ( 0 << 7 ) | ( 13 << 0 ) ) // 0xFC0D
#define HCI_CMD_Ext_EnablePTM                      0xFC0E // ( (63<<10) | ( 0 << 7 ) | ( 14 << 0 ) ) // 0xFC0E
#define HCI_CMD_Ext_SetFrequencyTuning             0xFC0F // ( (63<<10) | ( 0 << 7 ) | ( 15 << 0 ) ) // 0xFC0F
#define HCI_CMD_Ext_SaveFrequencyTuning            0xFC10 // ( (63<<10) | ( 0 << 7 ) | ( 16 << 0 ) ) // 0xFC10
#define HCI_CMD_Ext_SetMaxDTMTxPower               0xFC11 // ( (63<<10) | ( 0 << 7 ) | ( 17 << 0 ) ) // 0xFC11
#define HCI_CMD_Ext_MapPMIOPort                    0xFC12 // ( (63<<10) | ( 0 << 7 ) | ( 18 << 0 ) ) // 0xFC12
#define HCI_CMD_Ext_DisconnectImmediate            0xFC13 // ( (63<<10) | ( 0 << 7 ) | ( 19 << 0 ) ) // 0xFC13
#define HCI_CMD_Ext_PacketErrorRate                0xFC14 // ( (63<<10) | ( 0 << 7 ) | ( 20 << 0 ) ) // 0xFC14
#define HCI_CMD_Ext_PacketErrorRateByChannel       0xFC15 // ( (63<<10) | ( 0 << 7 ) | ( 21 << 0 ) ) // 0xFC15
#define HCI_CMD_Ext_ExtendRFRange                  0xFC16 // ( (63<<10) | ( 0 << 7 ) | ( 22 << 0 ) ) // 0xFC16
#define HCI_CMD_Ext_AdvertiserEventNotice          0xFC17 // ( (63<<10) | ( 0 << 7 ) | ( 23 << 0 ) ) // 0xFC17
#define HCI_CMD_Ext_ConnectionEventNotice          0xFC18 // ( (63<<10) | ( 0 << 7 ) | ( 24 << 0 ) ) // 0xFC18
#define HCI_CMD_Ext_HaltDuringRF                   0xFC19 // ( (63<<10) | ( 0 << 7 ) | ( 25 << 0 ) ) // 0xFC19
#define HCI_CMD_Ext_SetSlaveLatencyOverride        0xFC1A // ( (63<<10) | ( 0 << 7 ) | ( 26 << 0 ) ) // 0xFC1A
#define HCI_CMD_Ext_BuildRevision                  0xFC1B // ( (63<<10) | ( 0 << 7 ) | ( 27 << 0 ) ) // 0xFC1B
#define HCI_CMD_Ext_DelaySleep                     0xFC1C // ( (63<<10) | ( 0 << 7 ) | ( 28 << 0 ) ) // 0xFC1C
#define HCI_CMD_Ext_ResetSystem                    0xFC1D // ( (63<<10) | ( 0 << 7 ) | ( 29 << 0 ) ) // 0xFC1D
#define HCI_CMD_Ext_OverlappedProcessing           0xFC1E // ( (63<<10) | ( 0 << 7 ) | ( 30 << 0 ) ) // 0xFC1E
#define HCI_CMD_Ext_NumberCompletedPacketsLimit    0xFC1F // ( (63<<10) | ( 0 << 7 ) | ( 31 << 0 ) ) // 0xFC1F
                                                          // 
#define L2CAP_CMD_ConnectionParameterUpdateRequest 0xFC92 // ( (63<<10) | ( 1 << 7 ) | ( 18 << 0 ) ) // 0xFC92
                                                         
#define ATT_CMD_ErrorResponse                      0xFD01 // ( (63<<10) | ( 2 << 7 ) | (  1 << 0 ) ) // 0xFD01
#define ATT_CMD_ExchangeMTURequest                 0xFD02 // ( (63<<10) | ( 2 << 7 ) | (  2 << 0 ) ) // 0xFD02
#define ATT_CMD_ExchangeMTUResponse                0xFD03 // ( (63<<10) | ( 2 << 7 ) | (  3 << 0 ) ) // 0xFD03
#define ATT_CMD_FindInfomationRequest              0xFD04 // ( (63<<10) | ( 2 << 7 ) | (  4 << 0 ) ) // 0xFD04
#define ATT_CMD_FindInfomationResponse             0xFD05 // ( (63<<10) | ( 2 << 7 ) | (  5 << 0 ) ) // 0xFD05
#define ATT_CMD_FindByTypeValueRequest             0xFD06 // ( (63<<10) | ( 2 << 7 ) | (  6 << 0 ) ) // 0xFD06
#define ATT_CMD_FindByTypeValueResponse            0xFD07 // ( (63<<10) | ( 2 << 7 ) | (  7 << 0 ) ) // 0xFD07
#define ATT_CMD_ReadByTypeValueRequest             0xFD08 // ( (63<<10) | ( 2 << 7 ) | (  8 << 0 ) ) // 0xFD08
#define ATT_CMD_ReadByTypeValueResponse            0xFD09 // ( (63<<10) | ( 2 << 7 ) | (  9 << 0 ) ) // 0xFD09
#define ATT_CMD_ReadRequest                        0xFD0A // ( (63<<10) | ( 2 << 7 ) | ( 10 << 0 ) ) // 0xFD0A
#define ATT_CMD_ReadResponse                       0xFD0B // ( (63<<10) | ( 2 << 7 ) | ( 11 << 0 ) ) // 0xFD0B
#define ATT_CMD_ReadBlobRequest                    0xFD0C // ( (63<<10) | ( 2 << 7 ) | ( 12 << 0 ) ) // 0xFD0C
#define ATT_CMD_ReadBlobResponse                   0xFD0D // ( (63<<10) | ( 2 << 7 ) | ( 13 << 0 ) ) // 0xFD0D
#define ATT_CMD_ReadMultipleRequest                0xFD0E // ( (63<<10) | ( 2 << 7 ) | ( 14 << 0 ) ) // 0xFD0E
#define ATT_CMD_ReadMultipleResponse               0xFD0F // ( (63<<10) | ( 2 << 7 ) | ( 15 << 0 ) ) // 0xFD0F
#define ATT_CMD_ReadByGroupTypeRequest             0xFD10 // ( (63<<10) | ( 2 << 7 ) | ( 16 << 0 ) ) // 0xFD10
#define ATT_CMD_ReadByGroupTypeResponse            0xFD11 // ( (63<<10) | ( 2 << 7 ) | ( 17 << 0 ) ) // 0xFD11
#define ATT_CMD_WriteRequest                       0xFD12 // ( (63<<10) | ( 2 << 7 ) | ( 18 << 0 ) ) // 0xFD12
#define ATT_CMD_WriteResponse                      0xFD13 // ( (63<<10) | ( 2 << 7 ) | ( 19 << 0 ) ) // 0xFD13
#define ATT_CMD_PrepareWriteRequest                0xFD16 // ( (63<<10) | ( 2 << 7 ) | ( 22 << 0 ) ) // 0xFD16
#define ATT_CMD_PrepareWriteResponse               0xFD17 // ( (63<<10) | ( 2 << 7 ) | ( 23 << 0 ) ) // 0xFD17
#define ATT_CMD_ExecuteWriteRequest                0xFD18 // ( (63<<10) | ( 2 << 7 ) | ( 24 << 0 ) ) // 0xFD18
#define ATT_CMD_ExecuteWriteResponse               0xFD19 // ( (63<<10) | ( 2 << 7 ) | ( 25 << 0 ) ) // 0xFD19
#define ATT_CMD_HandleValueNotification            0xFD1B // ( (63<<10) | ( 2 << 7 ) | ( 27 << 0 ) ) // 0xFD1B
#define ATT_CMD_HandleValueIndication              0xFD1D // ( (63<<10) | ( 2 << 7 ) | ( 29 << 0 ) ) // 0xFD1D
#define ATT_CMD_HandleValueConfirmation            0xFD1E // ( (63<<10) | ( 2 << 7 ) | ( 30 << 0 ) ) // 0xFD1E
                                                          // 
//  #define GATT_CMD_DiscoverCharecteristicsByUUID 0xFD88 // ( (63<<10) | ( 3 << 7 ) | (  8 << 0 ) ) // 0xFD88
//  #define GATT_CMD_WriteLong                     0xFD96 // ( (63<<10) | ( 3 << 7 ) | ( 22 << 0 ) ) // 0xFD96
                                                          // 
#define GATT_CMD_ExchangeMTU                       0xFD82 // ( (63<<10) | ( 3 << 7 ) | (  2 << 0 ) ) // 0xFD82
#define GATT_CMD_DiscoverAllCharDescs              0xFD84 // ( (63<<10) | ( 3 << 7 ) | (  4 << 0 ) ) // 0xFD84
#define GATT_CMD_DiscoverPrimaryServiceByUUID      0xFD86 // ( (63<<10) | ( 3 << 7 ) | (  6 << 0 ) ) // 0xFD86
#define GATT_CMD_DiscoverCharsByUUID               0xFD88 // ( (63<<10) | ( 3 << 7 ) | (  8 << 0 ) ) // 0xFD88
#define GATT_CMD_ReadCharValue                     0xFD8A // ( (63<<10) | ( 3 << 7 ) | ( 10 << 0 ) ) // 0xFD8A
#define GATT_CMD_ReadLongCharValue                 0xFD8C // ( (63<<10) | ( 3 << 7 ) | ( 12 << 0 ) ) // 0xFD8C
#define GATT_CMD_ReadMultiCharValues               0xFD8E // ( (63<<10) | ( 3 << 7 ) | ( 14 << 0 ) ) // 0xFD8E
                                                          // 
#define GATT_CMD_DiscoverAllPrimaryServices        0xFD90 // ( (63<<10) | ( 3 << 7 ) | ( 16 << 0 ) ) // 0xFD90
#define GATT_CMD_WriteCharValue                    0xFD92 // ( (63<<10) | ( 3 << 7 ) | ( 18 << 0 ) ) // 0xFD92
#define GATT_CMD_WriteLongCharValue                0xFD96 // ( (63<<10) | ( 3 << 7 ) | ( 22 << 0 ) ) // 0xFD96
#define GATT_CMD_Notification                      0xFD9B // ( (63<<10) | ( 3 << 7 ) | ( 27 << 0 ) ) // 0xFD9B
#define GATT_CMD_Indication                        0xFD9D // ( (63<<10) | ( 3 << 7 ) | ( 29 << 0 ) ) // 0xFD9D
                                                          // 
#define GATT_CMD_FindIncludedServices              0xFDB0 // ( (63<<10) | ( 3 << 7 ) | ( 48 << 0 ) ) // 0xFDB0
#define GATT_CMD_DiscoverAllChars                  0xFDB2 // ( (63<<10) | ( 3 << 7 ) | ( 50 << 0 ) ) // 0xFDB2
#define GATT_CMD_ReadUsingCharUUID                 0xFDB4 // ( (63<<10) | ( 3 << 7 ) | ( 60 << 0 ) ) // 0xFDB4
#define GATT_CMD_WriteNoRsp                        0xFDB6 // ( (63<<10) | ( 3 << 7 ) | ( 54 << 0 ) ) // 0xFDB6
#define GATT_CMD_SignedWriteNoRsp                  0xFDB8 // ( (63<<10) | ( 3 << 7 ) | ( 56 << 0 ) ) // 0xFDB8
#define GATT_CMD_ReliableWrites                    0xFDBA // ( (63<<10) | ( 3 << 7 ) | ( 58 << 0 ) ) // 0xFDBA
#define GATT_CMD_ReadCharDesc                      0xFDBC // ( (63<<10) | ( 3 << 7 ) | ( 60 << 0 ) ) // 0xFDBC
#define GATT_CMD_ReadLongCharDesc                  0xFDBE // ( (63<<10) | ( 3 << 7 ) | ( 62 << 0 ) ) // 0xFDBE
#define GATT_CMD_WriteCharDesc                     0xFDC0 // ( (63<<10) | ( 3 << 7 ) | ( 64 << 0 ) ) // 0xFDC0
#define GATT_CMD_WriteLongCharDesc                 0xFDC2 // ( (63<<10) | ( 3 << 7 ) | ( 66 << 0 ) ) // 0xFDC2
#define GATT_CMD_AddService                        0xFDFC // ( (63<<10) | ( 3 << 7 ) | (124 << 0 ) ) // 0xFDFC
#define GATT_CMD_DelService                        0xFDFD // ( (63<<10) | ( 3 << 7 ) | (125 << 0 ) ) // 0xFDFD
#define GATT_CMD_AddAttribute                      0xFDFE // ( (63<<10) | ( 3 << 7 ) | (126 << 0 ) ) // 0xFDFE
                                                          // 
                                                          // 
#define GAP_CMD_DeviceInitialization               0xFE00 // ( (63<<10) | ( 4 << 7 ) | (  0 << 0 ) ) // 0xFE00
#define GAP_CMD_ConfigureDeviceAddress             0xFE03 // ( (63<<10) | ( 4 << 7 ) | (  3 << 0 ) ) // 0xFE03
#define GAP_CMD_DeviceDiscoveryRequest             0xFE04 // ( (63<<10) | ( 4 << 7 ) | (  4 << 0 ) ) // 0xFE04
#define GAP_CMD_DeviceDiscoveryCancel              0xFE05 // ( (63<<10) | ( 4 << 7 ) | (  5 << 0 ) ) // 0xFE05
#define GAP_CMD_MakeDiscoverable                   0xFE06 // ( (63<<10) | ( 4 << 7 ) | (  6 << 0 ) ) // 0xFE06
#define GAP_CMD_UpdateAdvertisingData              0xFE07 // ( (63<<10) | ( 4 << 7 ) | (  7 << 0 ) ) // 0xFE07
#define GAP_CMD_EndDiscoverable                    0xFE08 // ( (63<<10) | ( 4 << 7 ) | (  8 << 0 ) ) // 0xFE08
#define GAP_CMD_EstablishLinkRequest               0xFE09 // ( (63<<10) | ( 4 << 7 ) | (  9 << 0 ) ) // 0xFE09
#define GAP_CMD_TerminateLinkRequest               0xFE0A // ( (63<<10) | ( 4 << 7 ) | ( 10 << 0 ) ) // 0xFE0A
#define GAP_CMD_Authneticate                       0xFE0B // ( (63<<10) | ( 4 << 7 ) | ( 11 << 0 ) ) // 0xFE0B
#define GAP_CMD_PasskeyUpdate                      0xFE0C // ( (63<<10) | ( 4 << 7 ) | ( 12 << 0 ) ) // 0xFE0C
#define GAP_CMD_SlaveSecurityRequest               0xFE0D // ( (63<<10) | ( 4 << 7 ) | ( 13 << 0 ) ) // 0xFE0D
#define GAP_CMD_Signable                           0xFE0E // ( (63<<10) | ( 4 << 7 ) | ( 14 << 0 ) ) // 0xFE0E
#define GAP_CMD_Bond                               0xFE0F // ( (63<<10) | ( 4 << 7 ) | ( 15 << 0 ) ) // 0xFE0F
#define GAP_CMD_TerminateAuth                      0xFE10 // ( (63<<10) | ( 4 << 7 ) | ( 16 << 0 ) ) // 0xFE10
#define GAP_CMD_UpdateLinkParameterRequest         0xFE11 // ( (63<<10) | ( 4 << 7 ) | ( 17 << 0 ) ) // 0xFE11
#define GAP_CMD_SetParameter                       0xFE30 // ( (63<<10) | ( 4 << 7 ) | ( 48 << 0 ) ) // 0xFE30
#define GAP_CMD_GetParameter                       0xFE31 // ( (63<<10) | ( 4 << 7 ) | ( 49 << 0 ) ) // 0xFE31
#define GAP_CMD_ResolvePrivateAddress              0xFE32 // ( (63<<10) | ( 4 << 7 ) | ( 50 << 0 ) ) // 0xFE32
#define GAP_CMD_SetAdvertisementToken              0xFE33 // ( (63<<10) | ( 4 << 7 ) | ( 51 << 0 ) ) // 0xFE33
#define GAP_CMD_RemoveAdvertisementToken           0xFE34 // ( (63<<10) | ( 4 << 7 ) | ( 52 << 0 ) ) // 0xFE34
#define GAP_CMD_UpdateAdvertisementTokens          0xFE35 // ( (63<<10) | ( 4 << 7 ) | ( 53 << 0 ) ) // 0xFE35
#define GAP_CMD_BondSetParameter                   0xFE36 // ( (63<<10) | ( 4 << 7 ) | ( 54 << 0 ) ) // 0xFE36
#define GAP_CMD_BondGetParameter                   0xFE37 // ( (63<<10) | ( 4 << 7 ) | ( 55 << 0 ) ) // 0xFE37
                                                          // 
#define UTIL_CMD_Reserved                          0xFE80 // ( (63<<10) | ( 5 << 7 ) | (  0 << 0 ) ) // 0xFE80
#define UTIL_CMD_NVRead                            0xFE81 // ( (63<<10) | ( 5 << 7 ) | (  1 << 0 ) ) // 0xFE81
#define UTIL_CMD_NVWrite                           0xFE82 // ( (63<<10) | ( 5 << 7 ) | (  2 << 0 ) ) // 0xFE82
                                                         
#define RESERVED_CMD_LE                            0xFF00 // ( (63<<10) | ( 6 << 7 ) | (  0 << 0 ) ) // 0xFF00
                                                         
#define USERPROFILE_CMD_LE                         0xFF80 // ( (63<<10) | ( 7 << 7 ) | (  0 << 0 ) ) // 0xFF80




//Vendor Specific Events
//    f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0     f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0
//  [ EventCode(EC) 0xff          ] [ Length                      ]   [ Event OpCode                                                ] 
//               0xFF              + Length(8bit)                    + Event Opcode(16bit)

// Event OpCode
// Mirror the Command Opcode
//    f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0     f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0
//  [ EventCode(EC) 0xff          ] [ Length                      ]    [  EOGF              ] [ EOEF                                ] 
//                                                                       EOGF(6bit)          + EOEF(10bit)

// EOEF
//    f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0     f   e   d   c   b   a   9   8   7   6   5   4   3   2   1   0
//  [ EventCode(EC) 0xff          ]  [ Length                     ]    [  EOGF              ] [ ESG     ][   Event                  ] 
//                                                                                             ESG(3bit) + Event(7bit)


//  EOGF
// 0     :  Embedded Opcode
// 1     :  Core     Opcode
// 2     :  Profile  Request
// 3     :  Profile  Response
// 4..63 :  Reserved 

#define HCI_EVENT_Ext_SetRxGain                        0x0400  // ( (1<<10) | ( 0 << 7 ) | (  0 << 0 ) ) // 0x0400
#define HCI_EVENT_Ext_SetTxPower                       0x0401  // ( (1<<10) | ( 0 << 7 ) | (  1 << 0 ) ) // 0x0401
#define HCI_EVENT_Ext_OnePacketPerEvent                0x0402  // ( (1<<10) | ( 0 << 7 ) | (  2 << 0 ) ) // 0x0402
#define HCI_EVENT_Ext_ClockDivideOnHalt                0x0403  // ( (1<<10) | ( 0 << 7 ) | (  3 << 0 ) ) // 0x0403
#define HCI_EVENT_Ext_DeclareNVUsage                   0x0404  // ( (1<<10) | ( 0 << 7 ) | (  4 << 0 ) ) // 0x0404
#define HCI_EVENT_Ext_Decrypt                          0x0405  // ( (1<<10) | ( 0 << 7 ) | (  5 << 0 ) ) // 0x0405
#define HCI_EVENT_Ext_SetLocalSupportedFeatures        0x0406  // ( (1<<10) | ( 0 << 7 ) | (  6 << 0 ) ) // 0x0406
#define HCI_EVENT_Ext_SetFastTxResponseTime            0x0407  // ( (1<<10) | ( 0 << 7 ) | (  7 << 0 ) ) // 0x0407
#define HCI_EVENT_Ext_ModemTestTx                      0x0408  // ( (1<<10) | ( 0 << 7 ) | (  8 << 0 ) ) // 0x0408
#define HCI_EVENT_Ext_ModemHopTestTx                   0x0409  // ( (1<<10) | ( 0 << 7 ) | (  9 << 0 ) ) // 0x0409
#define HCI_EVENT_Ext_ModemTestRx                      0x040A  // ( (1<<10) | ( 0 << 7 ) | ( 10 << 0 ) ) // 0x040A
#define HCI_EVENT_Ext_EndModemTest                     0x040B  // ( (1<<10) | ( 0 << 7 ) | ( 11 << 0 ) ) // 0x040B
#define HCI_EVENT_Ext_SetBDADDR                        0x040C  // ( (1<<10) | ( 0 << 7 ) | ( 12 << 0 ) ) // 0x040C
#define HCI_EVENT_Ext_SetSCA                           0x040D  // ( (1<<10) | ( 0 << 7 ) | ( 13 << 0 ) ) // 0x040D
#define HCI_EVENT_Ext_EnablePTM                        0x040E  // ( (1<<10) | ( 0 << 7 ) | ( 14 << 0 ) ) // 0x040E
#define HCI_EVENT_Ext_SetFrequencyTuning               0x040F  // ( (1<<10) | ( 0 << 7 ) | ( 15 << 0 ) ) // 0x040F
#define HCI_EVENT_Ext_SaveFrequencyTuning              0x0410  // ( (1<<10) | ( 0 << 7 ) | ( 16 << 0 ) ) // 0x0410
#define HCI_EVENT_Ext_SetMaxDTMTxPower                 0x0411  // ( (1<<10) | ( 0 << 7 ) | ( 17 << 0 ) ) // 0x0411
#define HCI_EVENT_Ext_MapPMIOPort                      0x0412  // ( (1<<10) | ( 0 << 7 ) | ( 18 << 0 ) ) // 0x0412
#define HCI_EVENT_Ext_DisconnectImmediate              0x0413  // ( (1<<10) | ( 0 << 7 ) | ( 19 << 0 ) ) // 0x0413
#define HCI_EVENT_Ext_PacketErrorRate                  0x0414  // ( (1<<10) | ( 0 << 7 ) | ( 20 << 0 ) ) // 0x0414
#define HCI_EVENT_Ext_PacketErrorRateByChannel         0x0415  // ( (1<<10) | ( 0 << 7 ) | ( 21 << 0 ) ) // 0x0415
#define HCI_EVENT_Ext_ExtendRFRange                    0x0416  // ( (1<<10) | ( 0 << 7 ) | ( 22 << 0 ) ) // 0x0416
#define HCI_EVENT_Ext_AdvertiserEventNotice            0x0417  // ( (1<<10) | ( 0 << 7 ) | ( 23 << 0 ) ) // 0x0417
#define HCI_EVENT_Ext_ConnectionEventNotice            0x0418  // ( (1<<10) | ( 0 << 7 ) | ( 24 << 0 ) ) // 0x0418
#define HCI_EVENT_Ext_HaltDuringRF                     0x0419  // ( (1<<10) | ( 0 << 7 ) | ( 25 << 0 ) ) // 0x0419
#define HCI_EVENT_Ext_SetSlaveLatencyOverride          0x041A  // ( (1<<10) | ( 0 << 7 ) | ( 26 << 0 ) ) // 0x041A
#define HCI_EVENT_Ext_BuildRevision                    0x041B  // ( (1<<10) | ( 0 << 7 ) | ( 27 << 0 ) ) // 0x041B
#define HCI_EVENT_Ext_DelaySleep                       0x041C  // ( (1<<10) | ( 0 << 7 ) | ( 28 << 0 ) ) // 0x041C
#define HCI_EVENT_Ext_ResetSystem                      0x041D  // ( (1<<10) | ( 0 << 7 ) | ( 29 << 0 ) ) // 0x041D
#define HCI_EVENT_Ext_OverlappedProcessing             0x041E  // ( (1<<10) | ( 0 << 7 ) | ( 30 << 0 ) ) // 0x041E
#define HCI_EVENT_Ext_NumberCompletedPacketsLimit      0x041F  // ( (1<<10) | ( 0 << 7 ) | ( 31 << 0 ) ) // 0x041F
                                                               // 
//이 부분이 약간 다르다. Command와 모두 같으나                 // 
#define L2CAP_EVENT_CommandReject                      0x0481  // ( (1<<10) | ( 1 << 7 ) | (  1 << 0 ) ) // 0x0481
#define L2CAP_EVENT_ConnectionParameterUpdateResponse  0x0493  // ( (1<<10) | ( 1 << 7 ) | ( 19 << 0 ) ) // 0x0493
                                                             
#define ATT_EVENT_ErrorResponse                        0x0501  // ( (1<<10) | ( 2 << 7 ) | (  1 << 0 ) ) // 0x0501
#define ATT_EVENT_ExchangeMTURequest                   0x0502  // ( (1<<10) | ( 2 << 7 ) | (  2 << 0 ) ) // 0x0502
#define ATT_EVENT_ExchangeMTUResponse                  0x0503  // ( (1<<10) | ( 2 << 7 ) | (  3 << 0 ) ) // 0x0503
#define ATT_EVENT_FindInfomationRequest                0x0504  // ( (1<<10) | ( 2 << 7 ) | (  4 << 0 ) ) // 0x0504
#define ATT_EVENT_FindInfomationResponse               0x0505  // ( (1<<10) | ( 2 << 7 ) | (  5 << 0 ) ) // 0x0505
#define ATT_EVENT_FindByTypeValueRequest               0x0506  // ( (1<<10) | ( 2 << 7 ) | (  6 << 0 ) ) // 0x0506
#define ATT_EVENT_FindByTypeValueResponse              0x0507  // ( (1<<10) | ( 2 << 7 ) | (  7 << 0 ) ) // 0x0507
#define ATT_EVENT_ReadByTypeRequest                    0x0508  // ( (1<<10) | ( 2 << 7 ) | (  8 << 0 ) ) // 0x0508
#define ATT_EVENT_ReadByTypeResponse                   0x0509  // ( (1<<10) | ( 2 << 7 ) | (  9 << 0 ) ) // 0x0509
#define ATT_EVENT_ReadRequest                          0x050A  // ( (1<<10) | ( 2 << 7 ) | ( 10 << 0 ) ) // 0x050A
#define ATT_EVENT_ReadResponse                         0x050B  // ( (1<<10) | ( 2 << 7 ) | ( 11 << 0 ) ) // 0x050B
#define ATT_EVENT_ReadBlobRequest                      0x050C  // ( (1<<10) | ( 2 << 7 ) | ( 12 << 0 ) ) // 0x050C
#define ATT_EVENT_ReadBlobResponse                     0x050D  // ( (1<<10) | ( 2 << 7 ) | ( 13 << 0 ) ) // 0x050D
#define ATT_EVENT_ReadMultipleRequest                  0x050E  // ( (1<<10) | ( 2 << 7 ) | ( 14 << 0 ) ) // 0x050E
#define ATT_EVENT_ReadMultipleResponse                 0x050F  // ( (1<<10) | ( 2 << 7 ) | ( 15 << 0 ) ) // 0x050F
#define ATT_EVENT_ReadByGroupTypeRequest               0x0510  // ( (1<<10) | ( 2 << 7 ) | ( 16 << 0 ) ) // 0x0510
#define ATT_EVENT_ReadByGroupTypeResponse              0x0511  // ( (1<<10) | ( 2 << 7 ) | ( 17 << 0 ) ) // 0x0511
#define ATT_EVENT_WriteRequest                         0x0512  // ( (1<<10) | ( 2 << 7 ) | ( 18 << 0 ) ) // 0x0512
#define ATT_EVENT_WriteResponse                        0x0513  // ( (1<<10) | ( 2 << 7 ) | ( 19 << 0 ) ) // 0x0513
#define ATT_EVENT_PrepareWriteRequest                  0x0516  // ( (1<<10) | ( 2 << 7 ) | ( 22 << 0 ) ) // 0x0516
#define ATT_EVENT_PrepareWriteResponse                 0x0517  // ( (1<<10) | ( 2 << 7 ) | ( 23 << 0 ) ) // 0x0517
#define ATT_EVENT_ExecuteWriteRequest                  0x0518  // ( (1<<10) | ( 2 << 7 ) | ( 24 << 0 ) ) // 0x0518
#define ATT_EVENT_ExecuteWriteResponse                 0x0519  // ( (1<<10) | ( 2 << 7 ) | ( 25 << 0 ) ) // 0x0519
#define ATT_EVENT_HandleValueNotification              0x051B  // ( (1<<10) | ( 2 << 7 ) | ( 27 << 0 ) ) // 0x051B
#define ATT_EVENT_HandleValueIndication                0x051D  // ( (1<<10) | ( 2 << 7 ) | ( 29 << 0 ) ) // 0x051D
#define ATT_EVENT_HandleValueConfirmation              0x051E  // ( (1<<10) | ( 2 << 7 ) | ( 30 << 0 ) ) // 0x051E
                                                               // 
//  #define GATT_EVENT_DiscoverCharecteristicsByUUID   0xFD1E  // ( (1<<10) | ( 3 << 7 ) | (  8 << 0 ) ) // 0xFD1E
//  #define GATT_EVENT_WriteLong                       0xFD1E  // ( (1<<10) | ( 3 << 7 ) | ( 22 << 0 ) ) // 0xFD1E
                                                               // 
// commadn에서는 DeviceInitialization                        
#define GAP_EVENT_DeviceInitDone                       0x0600  // ( (1<<10) | ( 4 << 7 ) | (  0 << 0 ) ) // 0x0600
#define GAP_EVENT_DeviceDiscovery                      0x0600  // ( (1<<10) | ( 4 << 7 ) | (  1 << 0 ) ) // 0x0600
#define GAP_EVENT_AdvertDataUpdateDone                 0x0600  // ( (1<<10) | ( 4 << 7 ) | (  2 << 0 ) ) // 0x0600
#define GAP_EVENT_MakeDiscoverableDone                 0x0603  // ( (1<<10) | ( 4 << 7 ) | (  3 << 0 ) ) // 0x0603
#define GAP_EVENT_EndDiscoverableDone                  0x0603  // ( (1<<10) | ( 4 << 7 ) | (  4 << 0 ) ) // 0x0603
#define GAP_EVENT_LinkEstablished                      0x0605  // ( (1<<10) | ( 4 << 7 ) | (  5 << 0 ) ) // 0x0605
#define GAP_EVENT_LinkTerminated                       0x0606  // ( (1<<10) | ( 4 << 7 ) | (  6 << 0 ) ) // 0x0606
#define GAP_EVENT_LinkParameterUpdate                  0x0607  // ( (1<<10) | ( 4 << 7 ) | (  7 << 0 ) ) // 0x0607
#define GAP_EVENT_RandomAddressChanged                 0x0608  // ( (1<<10) | ( 4 << 7 ) | (  8 << 0 ) ) // 0x0608
#define GAP_EVENT_SignatureUpdate                      0x0609  // ( (1<<10) | ( 4 << 7 ) | (  9 << 0 ) ) // 0x0609
#define GAP_EVENT_AuthenticationComplete               0x060A  // ( (1<<10) | ( 4 << 7 ) | ( 10 << 0 ) ) // 0x060A
#define GAP_EVENT_PasskeyNeeded                        0x060B  // ( (1<<10) | ( 4 << 7 ) | ( 11 << 0 ) ) // 0x060B
#define GAP_EVENT_SlaveRequestedSecurity               0x060C  // ( (1<<10) | ( 4 << 7 ) | ( 12 << 0 ) ) // 0x060C
#define GAP_EVENT_DeviveInfomation                     0x060D  // ( (1<<10) | ( 4 << 7 ) | ( 13 << 0 ) ) // 0x060D
#define GAP_EVENT_BondComplete                         0x060E  // ( (1<<10) | ( 4 << 7 ) | ( 14 << 0 ) ) // 0x060E
#define GAP_EVENT_PairingRequested                     0x060F  // ( (1<<10) | ( 4 << 7 ) | ( 15 << 0 ) ) // 0x060F
#define GAP_EVENT_CommandStatus                        0x067F  // ( (1<<10) | ( 4 << 7 ) | (127 << 0 ) ) // 0x067F























