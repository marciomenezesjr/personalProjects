/*
 * rfm69Gateway.h
 *
 *  Created on: 27.05.2017
 *      Author: marcio
 */

#ifndef APPLICATION_RFM69GATEWAY_H_
#define APPLICATION_RFM69GATEWAY_H_


// Includes
#include "rfm69.h"
#include "USB_config/descriptors.h"
#include "USB_app/usbConstructs.h"

// Defines
#define NODEID          29
#define NETWORKID       100
#define FREQUENCY       RF69_433MHZ
#define ENCRYPTKEY      "sampleEncryptKey"
#define RADIOPOWERLEVEL 31

// Spy configuration parameters
#define LISTENTIMEOUT   10000
#define SWEEPACTIVE     1000
#define SWEEPPERIOD     1000
#define CMD_BUF_SIZE    16
#define DEVPASSWD       0xAB
#define ENABLE_DEVICE   0xEF
#define DISABLE_DEVICE  0xFE

// Payload offsets
#define YYP     1   //position of year in payload
#define MM      3   //position of month in payload
#define DD      5   //position of day in payload
#define HPOS    8   //position of hour in payload
#define MPOS    10  //position of minute in payload
#define WPOS    13  //start position for VWC value in payload
#define TPOS    19  //start position for temperature value in payload
#define CHK     24  //position of checksum in payload
#define SPOS    26  //position of success indicator in payload

// Custom data types
typedef struct spyConfiguration_s{
    uint32_t listenTimeout;
    uint32_t sweepPeriod;
    uint32_t sweepActive;
} spyConfiguration_t;

// Function prototypes
extern void gatewayInit(void);
extern void gatewayReceiveCmd(void);
extern void gatewayPassiveListen(void);
extern void gatewayReceiveFrame(void);

extern volatile bool spyEnable;
extern volatile spyConfiguration_t devConfig;
extern uint8_t cmdBuffer[] ;


#endif /* APPLICATION_RFM69GATEWAY_H_ */
