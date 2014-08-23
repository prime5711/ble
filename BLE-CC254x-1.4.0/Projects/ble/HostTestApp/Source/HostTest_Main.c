/**************************************************************************************************
  Filename:       HostTest_Main.c
  Revised:        $Date: 2012-08-31 11:31:40 -0700 (Fri, 31 Aug 2012) $
  Revision:       $Revision: 31449 $

  Description:    This file contains the main and callback functions


  Copyright 2009-2012 Texas Instruments Incorporated. All rights reserved.

  IMPORTANT: Your use of this Software is limited to those specific rights
  granted under the terms of a software license agreement between the user
  who downloaded the software, his/her employer (which must be your employer)
  and Texas Instruments Incorporated (the "License").  You may not use this
  Software unless you agree to abide by the terms of the License. The License
  limits your use, and you acknowledge, that the Software may not be modified,
  copied or distributed unless embedded on a Texas Instruments microcontroller
  or used solely and exclusively in conjunction with a Texas Instruments radio
  frequency transceiver, which is integrated into your product.  Other than for
  the foregoing purpose, you may not use, reproduce, copy, prepare derivative
  works of, modify, distribute, perform, display or sell this Software and/or
  its documentation for any purpose.

  YOU FURTHER ACKNOWLEDGE AND AGREE THAT THE SOFTWARE AND DOCUMENTATION ARE
  PROVIDED �AS IS?WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED,
  INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF MERCHANTABILITY, TITLE,
  NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL
  TEXAS INSTRUMENTS OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER CONTRACT,
  NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR OTHER
  LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
  INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE
  OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT
  OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
  (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.

  Should you have any questions regarding your right to use this Software,
  contact Texas Instruments Incorporated at www.TI.com.
**************************************************************************************************/


//shcho add
#define chip	2541

/**************************************************************************************************
 *                                           Includes
 **************************************************************************************************/
/* Hal Drivers */
#include "hal_types.h"
#include "hal_key.h"
#include "hal_timer.h"
#include "hal_drivers.h"
#include "hal_led.h"


/* OSAL */
#include "OSAL.h"
#include "OSAL_Tasks.h"
#if defined POWER_SAVING
#include "OSAL_PwrMgr.h"
#endif
#include "osal_snv.h"
//shcho add start ===================================================================================
/***********************************************************************************
* INCLUDES
*/
//  #include <hal_types.h>
#include "hal_wait.h"
#include "dma.h"
// Include Name definitions of individual bits and bit-fields in the CC254x device registers.
#include "ioCC254x_bitdef.h"
// Include device specific file
//  #if (chip==2541)
#include "ioCC2541.h"
//  #elif (chip==2543)
//  #include "ioCC2543.h"
//  #elif (chip==2544)
//  #include "ioCC2544.h"
//  #warning "The CC2544Dongle is not supported for this software example."
//  #warning "The definitions for CC2544 in the code illustrate how to set up an SPI interface."
//  #elif (chip==2545)
//  #include "ioCC2545.h"
//  #else
//  #error "Chip not supported!"
//  #endif

/***********************************************************************************
* CONSTANTS
*/

// Size of allocated UART RX/TX buffer (just an example).
#define SIZE_OF_UART_RX_BUFFER   50
#define SIZE_OF_UART_TX_BUFFER   SIZE_OF_UART_RX_BUFFER

// UART test characters.
#define UART_TEST_DATA "Texas Instruments LPRF!"

// Test definitions.
#define UART_TST_MODE_RX
//  #define UART_TST_MODE_TX

// Baudrate = 115.2.kbps (U0BAUD.BAUD_M = 216, U0GCR.BAUD_E = 11), given 32 MHz system clock.
#define UART_BAUD_M  216
#define UART_BAUD_E  11

//shcho add end ===================================================================================


/**************************************************************************************************
 * FUNCTIONS
 **************************************************************************************************/

/* This callback is triggered when a key is pressed */
void MSA_Main_KeyCallback(uint8 keys, uint8 state);

/**************************************************************************************************
 * @fn          main
 *
 * @brief       Start of application.
 *
 * @param       none
 *
 * @return      none
 **************************************************************************************************
 */
int main(void)
{
  /* Initialize hardware */
  // --> CC2541EB Project���� CC2540EB/hal_board_cfg.h�� �����Ѵ�.
  HAL_BOARD_INIT();

//shcho add start==================================================================================================

  //shcho add from /c/Work.git/ble/CC2541_43_44_45_Peripherals_Software_Examples/software_examples
    /****************************************************************************
    * Clock setup
    * See basic software example "clk_xosc_cc254x"
    */
  
    // Set system clock source to HS XOSC, with no pre-scaling.
//      CLKCONCMD = (CLKCONCMD & ~(CLKCON_OSC | CLKCON_CLKSPD)) | CLKCON_CLKSPD_32M;
//      while (CLKCONSTA & CLKCON_OSC);   // Wait until clock source has changed.

   // Note the 32 kHz RCOSC starts calibrating, if not disabled.
  
//shcho add end==================================================================================================

  /* Initialze the HAL driver */
  HalDriverInit();


//  	//shcho add start==================================================================================================
//  
//    
//    
//      /***************************************************************************
//      * Setup I/O ports
//      *
//      * Port and pins used by USART0 operating in UART-mode, at the Alternative 1
//      * location for CC2541EM, CC2543EM and CC2545EM are:
//      * RX     : P0_2
//      * TX     : P0_3
//      * CT/CTS : P0_4
//      * RT/RTS : P0_5
//      *
//      * These pins must be set to function as peripheral I/O to be used by UART0.
//      * The TX pin on the transmitter must be connected to the RX pin on the receiver.
//      * If enabling hardware flow control (U0UCR.FLOW = 1) the CT/CTS (Clear-To-Send)
//      * on the transmitter must be connected to the RS/RTS (Ready-To-Send) pin on the
//      * receiver.
//      */
//  
//  //  #if (chip==2541 || chip==2543 || chip==2545)
//      // Configure USART0 for Alternative 1 => Port P0 (PERCFG.U0CFG = 0).
//      PERCFG = (PERCFG & ~PERCFG_U0CFG) | PERCFG_U0CFG_ALT1;    
//  //  #endif
//          
//  //  #if (chip==2541)
//      // Give priority to USART 0 over Timer 1 for port 0 pins.
//      P2DIR &= P2DIR_PRIP0_USART0;
//  //  #elif (chip==2543 || chip==2545)
//  //      // Give priority to USART 0 over Timer 1 for port 0 pins.
//  //      PPRI &= ~PPRI_PRI0P0;
//  //  #endif
//  
//  //  #if (chip==2541 || chip==2543 || chip==2545)
//      // Set pins 2, 3 and 5 as peripheral I/O and pin 4 as GPIO output.
//      //P0SEL |= BIT5 | BIT4 | BIT3 | BIT2;
//      P0SEL |=  BIT3 | BIT2;
//  //  #elif (chip==2544)
//  //      // Set pins 1, 2 and 3 as peripheral I/O and pin 0 as GPIO output.
//  //      P0SEL0 = 0x11;        // Map P0_0 and P0_1 as UASRT0. 
//  //      P0SEL1 = 0x11;        // Map P0_3 and P0_2 as UASRT0. 
//  //  #endif
//       
//  //  #if (chip==2541 || chip==2543 || chip==2545)
//      // Initialize P0_1 for SRF05EB S1 button
    P0SEL &= ~(BIT7 | BIT1) ;           // Function as General Purpose I/O
    P0DIR &= ~BIT1;           // Input
    P0DIR |= BIT7; // output
    P0_7 = 0; // Regulator Bypass mode
//  //  #elif (chip==2544)
//  //      // Initialize P0_1 for SRF05EB S1 button
//  //      P0SEL0 &= ~P0SEL0_SELP0_1;// Function as General Purpose I/O
//  //      PDIR &= ~PDIR_DIRP0_1;    // Input
//  //  #endif
//  
//    
//      /***************************************************************************
//      * Configure UART
//      *
//      */
//  
//      // Initialise bitrate = 57.6 kbps.
    U0BAUD = UART_BAUD_M;
    U0GCR = (U0GCR&~U0GCR_BAUD_E) | UART_BAUD_E;

    // Initialise UART protocol (start/stop bit, data bits, parity, etc.):
    // USART mode = UART (U0CSR.MODE = 1).
    U0CSR |= U0CSR_MODE;

    // Start bit level = low => Idle level = high  (U0UCR.START = 0).
    U0UCR &= ~U0UCR_START;

    // Stop bit level = high (U0UCR.STOP = 1).
    U0UCR |= U0UCR_STOP;

    // Number of stop bits = 1 (U0UCR.SPB = 0).
    U0UCR &= ~U0UCR_SPB;

    // Parity = disabled (U0UCR.PARITY = 0).
    U0UCR &= ~U0UCR_PARITY;

    // 9-bit data enable = 8 bits transfer (U0UCR.BIT9 = 0).
    U0UCR &= ~U0UCR_BIT9;

    // Level of bit 9 = 0 (U0UCR.D9 = 0), used when U0UCR.BIT9 = 1.
    // Level of bit 9 = 1 (U0UCR.D9 = 1), used when U0UCR.BIT9 = 1.
    // Parity = Even (U0UCR.D9 = 0), used when U0UCR.PARITY = 1.
    // Parity = Odd (U0UCR.D9 = 1), used when U0UCR.PARITY = 1.
    U0UCR &= ~U0UCR_D9;

    // Flow control = disabled (U0UCR.FLOW = 0).
    U0UCR &= ~U0UCR_FLOW;
//  
//      // Bit order = LSB first (U0GCR.ORDER = 0).
//      U0GCR &= ~U0GCR_ORDER;
//  
//  //shcho add end==================================================================================================


  /* Initialize NV system */
  osal_snv_init();

  /* Initialize the operating system */
  osal_init_system();

  /* Enable interrupts */
  HAL_ENABLE_INTERRUPTS();

  /* Setup Keyboard callback */
  HalKeyConfig(false, MSA_Main_KeyCallback);

  /* Blink LED on startup */
  HalLedSet (HAL_LED_4, HAL_LED_MODE_ON);

#if defined POWER_SAVING
  osal_pwrmgr_device( PWRMGR_BATTERY );
#endif

  /* Start OSAL */
  osal_start_system(); // No Return from here

  return 0;
}

/**************************************************************************************************
                                           CALL-BACKS
**************************************************************************************************/


/**************************************************************************************************
 * @fn      MSA_Main_KeyCallback
 *
 * @brief   Callback service for keys
 *
 * @param   keys  - keys that were pressed
 *          state - shifted
 *
 * @return  void
 **************************************************************************************************/
void MSA_Main_KeyCallback(uint8 keys, uint8 state)
{
  /* Key callbacks */
}

/*************************************************************************************************
**************************************************************************************************/
