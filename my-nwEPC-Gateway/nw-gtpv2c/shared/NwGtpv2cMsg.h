/*----------------------------------------------------------------------------*
 *                                                                            *
 *                              n w - g t p v 2 c                             * 
 *    G P R S   T u n n e l i n g    P r o t o c o l   v 2 c    S t a c k     *
 *                                                                            *
 *                                                                            *
 * Copyright (c) 2010-2011 Amit Chawre                                        *
 * All rights reserved.                                                       *
 *                                                                            *
 * Redistribution and use in source and binary forms, with or without         *
 * modification, are permitted provided that the following conditions         *
 * are met:                                                                   *
 *                                                                            *
 * 1. Redistributions of source code must retain the above copyright          *
 *    notice, this list of conditions and the following disclaimer.           *
 * 2. Redistributions in binary form must reproduce the above copyright       *
 *    notice, this list of conditions and the following disclaimer in the     *
 *    documentation and/or other materials provided with the distribution.    *
 * 3. The name of the author may not be used to endorse or promote products   *
 *    derived from this software without specific prior written permission.   *
 *                                                                            *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR       *
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES  *
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.    *
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,           *
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT   *
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF   *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.          *
 *----------------------------------------------------------------------------*/

#ifndef __NW_GTPV2C_MSG_H__
#define __NW_GTPV2C_MSG_H__

#include "NwTypes.h"
#include "NwGtpv2c.h"

/** 
 * @file NwGtpv2cMsg.h
 * @brief This file defines APIs for to build new outgoing gtpv2c messages and to parse incoming messages.
 */

#ifdef __cplusplus
extern "C" {
#endif

/*--------------------------------------------------------------------------*
 *                   S H A R E D     A P I    M A C R O S                   *
 *--------------------------------------------------------------------------*/


#define NW_GTP_VERSION                                          (0x02) /**< GTP Version                         */
#define NW_GTPV2C_MINIMUM_HEADER_SIZE                           (8)    /**< Size of GTPv2c minimun header       */
#define NW_GTPV2C_EPC_SPECIFIC_HEADER_SIZE                      (12)   /**< Size of GTPv2c EPC specific header  */

/* GTP Message Type Values */
#define NW_GTP_ECHO_REQ                                         (1)
#define NW_GTP_ECHO_RSP                                         (2)
#define NW_GTP_VERSION_NOT_SUPPORTED_IND                        (3)
#define NW_GTP_CREATE_SESSION_REQ                               (32)
#define NW_GTP_CREATE_SESSION_RSP                               (33)
#define NW_GTP_MODIFY_BEARER_REQ                                (34)
#define NW_GTP_MODIFY_BEARER_RSP                                (35)
#define NW_GTP_DELETE_SESSION_REQ                               (36)
#define NW_GTP_DELETE_SESSION_RSP                               (37)
#define NW_GTP_MODIFY_BEARER_CMD                                (64)
#define NW_GTP_MODIFY_BEARER_FAILURE_IND                        (65)
#define NW_GTP_DELETE_BEARER_CMD                                (66)
#define NW_GTP_DELETE_BEARER_FAILURE_IND                        (67)
#define NW_GTP_BEARER_RESOURCE_CMD                              (68)
#define NW_GTP_BEARER_RESOURCE_FAILURE_IND                      (69)
#define NW_GTP_DOWNLINK_DATA_NOTIFICATION_FAILURE_IND           (70)
#define NW_GTP_TRACE_SESSION_ACTIVATION                         (71)
#define NW_GTP_TRACE_SESSION_DEACTIVATION                       (72)
#define NW_GTP_STOP_PAGING_IND                                  (73)
#define NW_GTP_CREATE_BEARER_REQ                                (95)
#define NW_GTP_CREATE_BEARER_RSP                                (96)
#define NW_GTP_UPDATE_BEARER_REQ                                (97)
#define NW_GTP_UPDATE_BEARER_RSP                                (98)
#define NW_GTP_DELETE_BEARER_REQ                                (99)
#define NW_GTP_DELETE_BEARER_RSP                                (100)
#define NW_GTP_DELETE_PDN_CONNECTION_SET_REQ                    (101)
#define NW_GTP_DELETE_PDN_CONNECTION_SET_RSP                    (102)
#define NW_GTP_IDENTIFICATION_REQ                               (128)
#define NW_GTP_IDENTIFICATION_RSP                               (129)
#define NW_GTP_CONTEXT_REQ                                      (130)
#define NW_GTP_CONTEXT_RSP                                      (131)
#define NW_GTP_CONTEXT_ACK                                      (132)
#define NW_GTP_FORWARD_RELOCATION_REQ                           (133)
#define NW_GTP_FORWARD_RELOCATION_RSP                           (134)
#define NW_GTP_FORWARD_RELOCATION_COMPLETE_NTF                  (135)
#define NW_GTP_FORWARD_RELOCATION_COMPLETE_ACK                  (136)
#define NW_GTP_FORWARD_ACCESS_CONTEXT_NTF                       (137)
#define NW_GTP_FORWARD_ACCESS_CONTEXT_ACK                       (138)
#define NW_GTP_RELOCATION_CANCEL_REQ                            (139)
#define NW_GTP_RELOCATION_CANCEL_RSP                            (140)
#define NW_GTP_CONFIGURE_TRANSFER_TUNNEL                        (141)
#define NW_GTP_DETACH_NTF                                       (149)
#define NW_GTP_DETACH_ACK                                       (150)
#define NW_GTP_CS_PAGING_INDICATION                             (151)
#define NW_GTP_RAN_INFORMATION_RELAY                            (152)
#define NW_GTP_ALERT_MME_NTF                                    (153)
#define NW_GTP_ALERT_MME_ACK                                    (154)
#define NW_GTP_UE_ACTIVITY_NTF                                  (155)
#define NW_GTP_UE_ACTIVITY_ACK                                  (156)
#define NW_GTP_CREATE_FORWARDING_TUNNEL_REQ                     (160)
#define NW_GTP_CREATE_FORWARDING_TUNNEL_RSP                     (161)
#define NW_GTP_SUSPEND_NTF                                      (162)
#define NW_GTP_SUSPEND_ACK                                      (163)
#define NW_GTP_RESUME_NTF                                       (164)
#define NW_GTP_RESUME_ACK                                       (165)
#define NW_GTP_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_REQ       (166)
#define NW_GTP_CREATE_INDIRECT_DATA_FORWARDING_TUNNEL_RSP       (167)
#define NW_GTP_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_REQ       (168)
#define NW_GTP_DELETE_INDIRECT_DATA_FORWARDING_TUNNEL_RSP       (169)
#define NW_GTP_RELEASE_ACCESS_BEARERS_REQ                       (170)
#define NW_GTP_RELEASE_ACCESS_BEARERS_RSP                       (171)
#define NW_GTP_DOWNLINK_DATA_NOTIFICATION                       (176)
#define NW_GTP_DOWNLINK_DATA_NOTIFICATION_ACK                   (177)
#define NW_GTP_RESERVED                                         (178)
#define NW_GTP_UPDATE_PDN_CONNECTION_SET_REQ                    (200)
#define NW_GTP_UPDATE_PDN_CONNECTION_SET_RSP                    (201)
#define NW_GTP_MBMS_SESSION_START_REQ                           (231)
#define NW_GTP_MBMS_SESSION_START_RSP                           (232)
#define NW_GTP_MBMS_SESSION_UPDATE_REQ                          (233)
#define NW_GTP_MBMS_SESSION_UPDATE_RSP                          (234)
#define NW_GTP_MBMS_SESSION_STOP_REQ                            (235)
#define NW_GTP_MBMS_SESSION_STOP_RSP                            (236)
#define NW_GTP_MSG_END                                          (255)


/* Cause Values */
#define NW_GTPV2C_CAUSE_BIT_NONE                                (0x00)
#define NW_GTPV2C_CAUSE_BIT_CS                                  (0x01)
#define NW_GTPV2C_CAUSE_BIT_BCE                                 (0x02)
#define NW_GTPV2C_CAUSE_BIT_PCE                                 (0x04)

/* RAT Type Values */
#define NW_RAT_TYPE_EUTRAN                                      (0x06)

/* PDN Type Values */
#define NW_PDN_TYPE_IPv4                                        (0x01)
#define NW_PDN_TYPE_IPv6                                        (0x02)
#define NW_PDN_TYPE_IPv4IPv6                                    (0x03)

/* Interface Type Values */
#define NW_GTPV2C_IFTYPE_S1U_ENODEB_GTPU                        (0)
#define NW_GTPV2C_IFTYPE_S1U_SGW_GTPU                           (1)
#define NW_GTPV2C_IFTYPE_S12_RNC_GTPU                           (2)
#define NW_GTPV2C_IFTYPE_S12_SGW_GTPU                           (3)
#define NW_GTPV2C_IFTYPE_S5S8_SGW_GTPU                          (4)
#define NW_GTPV2C_IFTYPE_S5S8_PGW_GTPU                          (5)
#define NW_GTPV2C_IFTYPE_S5S8_SGW_GTPC                          (6)
#define NW_GTPV2C_IFTYPE_S5S8_PGW_GTPC                          (7)
#define NW_GTPV2C_IFTYPE_S5S8_SGW_PIMPv6                        (8)
#define NW_GTPV2C_IFTYPE_S5S8_PGW_PIMPv6                        (9)
#define NW_GTPV2C_IFTYPE_S11_MME_GTPC                           (10)
#define NW_GTPV2C_IFTYPE_S11S4_SGW_GTPC                         (11)

/* Indication Flag Values */
#define NW_GTPV2C_INDICATION_FLAG_NONE                          (0x0000)
#define NW_GTPV2C_INDICATION_FLAG_DAF                           (0x8000)
#define NW_GTPV2C_INDICATION_FLAG_DTF                           (0x4000)
#define NW_GTPV2C_INDICATION_FLAG_HI                            (0x2000)
#define NW_GTPV2C_INDICATION_FLAG_DFI                           (0x1000)
#define NW_GTPV2C_INDICATION_FLAG_OI                            (0x0800)
#define NW_GTPV2C_INDICATION_FLAG_ISRSI                         (0x0400)
#define NW_GTPV2C_INDICATION_FLAG_ISRAI                         (0x0200)
#define NW_GTPV2C_INDICATION_FLAG_SGWCI                         (0x0100)

#define NW_GTPV2C_INDICATION_FLAG_SPARE                         (0x0080)
#define NW_GTPV2C_INDICATION_FLAG_UMSI                          (0x0040)
#define NW_GTPV2C_INDICATION_FLAG_CSFI                          (0x0020)
#define NW_GTPV2C_INDICATION_FLAG_CRSI                          (0x0010)
#define NW_GTPV2C_INDICATION_FLAG_PS                            (0x0008)
#define NW_GTPV2C_INDICATION_FLAG_PT                            (0x0004)
#define NW_GTPV2C_INDICATION_FLAG_SI                            (0x0002)
#define NW_GTPV2C_INDICATION_FLAG_MSV                           (0x0001)

/*--------------------------------------------------------------------------*
 *   G T P V 2 C     I E    D A T A - T Y P E      D E F I N I T I O N S    *
 *--------------------------------------------------------------------------*/

#pragma pack(1)

typedef struct NwGtpv2cIeTv1
{
  NwU8T  t;
  NwU16T l;
  NwU8T  i;
  NwU8T  v;
} NwGtpv2cIeTv1T;

typedef struct NwGtpv2cIeTv2
{
  NwU8T  t;
  NwU16T l;
  NwU8T  i;
  NwU16T  v;
} NwGtpv2cIeTv2T;

typedef struct NwGtpv2cIeTv4
{
  NwU8T  t;
  NwU16T l;
  NwU8T  i;
  NwU32T  v;
} NwGtpv2cIeTv4T;

typedef struct NwGtpv2cIeTv8
{
  NwU8T  t;
  NwU16T l;
  NwU8T  i;
  NwU64T v;
} NwGtpv2cIeTv8T;

typedef struct NwGtpv2cIeTlv
{
  NwU8T  t;
  NwU16T l;
  NwU8T  i;
} NwGtpv2cIeTlvT;

#pragma pack()


 /**
  * Allocate a gtpv2c message.
  *
  * @param[in] hGtpcStackHandle : gtpv2c stack handle.
  * @param[in] teidPresent : TEID is present flag.
  * @param[in] msgType : Message type for this message.
  * @param[in] teid : TEID for this message.
  * @param[in] seqNum : Sequence number for this message.
  * @param[out] phMsg : Pointer to message handle.
  */

NwRcT
nwGtpv2cMsgNew( NW_IN NwGtpv2cStackHandleT hGtpcStackHandle,
                NW_IN NwU8T     teidPresent,
                NW_IN NwU8T     msgType,
                NW_IN NwU32T    teid,
                NW_IN NwU32T    seqNum,
                NW_OUT NwGtpv2cMsgHandleT *phMsg);


 /**
  * Allocate a gtpv2c message from data buffer.
  *
  * @param[in] hGtpcStackHandle : gtpv2c stack handle.
  * @param[in] pBuf: Buffer to be copied in this message.
  * @param[in] bufLen: Buffer length to be copied in this message.
  * @param[out] phMsg : Pointer to message handle.
  */

NwRcT
nwGtpv2cMsgFromBufferNew( NW_IN NwGtpv2cStackHandleT hGtpcStackHandle,
                         NW_IN NwU8T* pBuf,
                         NW_IN NwU32T bufLen,
                         NW_OUT NwGtpv2cMsgHandleT *phMsg);

 /**
  * Free a gtpv2c message.
  *
  * @param[in] hGtpcStackHandle : gtpv2c stack handle.
  * @param[in] hMsg : Message handle.
  */

NwRcT
nwGtpv2cMsgDelete( NW_IN NwGtpv2cStackHandleT hGtpcStackHandle,
                   NW_IN NwGtpv2cMsgHandleT hMsg);

 /**
  * Set TEID for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  * @param[in] teid: TEID value.
  */

NwRcT
nwGtpv2cMsgSetTeid(NW_IN NwGtpv2cMsgHandleT hMsg, NwU32T teid);

 /**
  * Set TEID present flag for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  * @param[in] teidPesent: Flag boolean value.
  */

NwRcT
nwGtpv2cMsgSetTeidPresent(NW_IN NwGtpv2cMsgHandleT hMsg, NwBoolT teidPresent);

 /**
  * Set sequence for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  * @param[in] seqNum: Flag boolean value.
  */

NwRcT
nwGtpv2cMsgSetSeqNumber(NW_IN NwGtpv2cMsgHandleT hMsg, NwU32T seqNum);

 /**
  * Get TEID present for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  */

NwU32T
nwGtpv2cMsgGetTeid(NW_IN NwGtpv2cMsgHandleT hMsg);

 /**
  * Get TEID present for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  */

NwBoolT
nwGtpv2cMsgGetTeidPresent(NW_IN NwGtpv2cMsgHandleT hMsg);

 /**
  * Get sequence number for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  */

NwU32T
nwGtpv2cMsgGetSeqNumber(NW_IN NwGtpv2cMsgHandleT hMsg);

 /**
  * Get msg lenght for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  */

NwU32T
nwGtpv2cMsgGetLength(NW_IN NwGtpv2cMsgHandleT hMsg);

 /**
  * Add a gtpv2c information element of length 1 to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE type.
  * @param[in] instance : IE instance.
  * @param[in] value : IE value.
  */

NwRcT
nwGtpv2cMsgAddIeTV1(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU8T       instance,
              NW_IN NwU8T       value);


 /**
  * Add a gtpv2c information element of length 2 to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE type.
  * @param[in] instance : IE instance.
  * @param[in] value : IE value.
  */

NwRcT
nwGtpv2cMsgAddIeTV2(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU8T       instance,
              NW_IN NwU16T      value);


 /**
  * Add a gtpv2c information element of length 4 to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE type.
  * @param[in] instance : IE instance.
  * @param[in] value : IE value.
  */

NwRcT
nwGtpv2cMsgAddIeTV4(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU8T       instance,
              NW_IN NwU32T      value);
/* add for create session'dns for sgw by guan */
NwRcT
nwGtpv2cMsgAddIePCO(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU16T      length,
              NW_IN NwU8T       instance,
              NW_IN NwU8T*      pVal);

/* add end */
 /**
  * Add a gtpv2c information element of variable length to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE type.
  * @param[in] length : IE length.
  * @param[in] instance : IE instance.
  * @param[in] value : IE value.
  */

NwRcT
nwGtpv2cMsgAddIe(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU16T      length,
              NW_IN NwU8T       instance,
              NW_IN NwU8T*      pVal);

 /**
  * Add CAUSE information element to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] instance : IE instance.
  * @param[in] causeValue: Cause value.
  * @param[in] bitFlags: PDN Connetiion IE Error Flag, Bearer Context IE Error Flag, Cause Source Flag.
  * @param[in] offendingIeType: Offending IE type.
  * @param[in] offendingIeInstance: Offending IE instance.
  */

NwRcT
nwGtpv2cMsgAddIeCause(NW_IN NwGtpv2cMsgHandleT hMsg, 
                      NW_IN NwU8T instance,
                      NW_IN NwU8T causeValue,
                      NW_IN NwU8T bitFlags,
                      NW_IN NwU8T offendingIeType,
                      NW_IN NwU8T offendingIeInstance);

 /**
  * Add F-TEID information element to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] instance : IE instance.
  * @param[in] ifType : Interface Type.
  * @param[in] teidOrGreKey: TEID/ GRE Key
  * @param[in] ipv4Addr : Ipv4 Address in Network Byte Order.
  * @param[in] pIpv6Addr: Pointer to IPv6 Address in Network Byte Order.
  */

NwRcT
nwGtpv2cMsgAddIeFteid(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       instance,
              NW_IN NwU8T       ifType,
              NW_IN NwU32T      teidOrGreKey,
              NW_IN NwU32T      ipv4Addr,
              NW_IN NwU8T*      pIpv6Addr);

NwRcT
nwGtpv2cMsgGroupedIeStart(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN NwU8T       type,
              NW_IN NwU8T       instance);

NwRcT
nwGtpv2cMsgGroupedIeEnd(NW_IN NwGtpv2cMsgHandleT hMsg);


 /**
  * Check if information element of type and instance is present
  * in gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE Type.
  * @param[in] instance : IE instance.
  * @return NW_TRUE on success, NW_FALSE on failure.
  */

NwBoolT
nwGtpv2cMsgIsIePresent(NW_IN NwGtpv2cMsgHandleT hMsg, 
                       NW_IN NwU8T type,
                       NW_IN NwU8T instance);

 /**
  * Get an information element of type 'NwU8T' from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] type : IE Type.
  * @param[in] instance : IE instance.
  * @param[out] pVal : Pointer to value buffer.
  * @return NW_OK on success.
  */

NwRcT
nwGtpv2cMsgGetIeTV1(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_OUT NwU8T* pVal);

 /**
  * Get an information element of type 'NwU16T' from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] tyep : IE Type.
  * @param[in] instance : IE instance.
  * @param[out] pVal : Pointer to value buffer.
  * @return NW_OK on success.
  */


NwRcT
nwGtpv2cMsgGetIeTV2(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_OUT NwU16T* pVal);

 /**
  * Get an information element of type 'NwU32T' from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] tyep : IE Type.
  * @param[in] instance : IE instance.
  * @param[out] pVal : Pointer to value buffer.
  * @return NW_OK on success.
  */


NwRcT
nwGtpv2cMsgGetIeTV4(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_OUT NwU32T* pVal);

 /**
  * Get an information element of type 'NwU64T' from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] tyep : IE Type.
  * @param[in] instance : IE instance.
  * @param[out] pVal : Pointer to IE value buffer.
  * @return NW_OK on success.
  */


NwRcT
nwGtpv2cMsgGetIeTV8(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_OUT NwU64T* pVal);

 /**
  * Get an information element of variable length from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] tyep : IE Type.
  * @param[in] instance : IE instance.
  * @param[in] maxLen : Maximum length of IE.
  * @param[out] pVal : Pointer to IE value buffer.
  * @param[out] pLen : Pointer to IE length buffer.
  * @return NW_OK on success.
  */

NwRcT
nwGtpv2cMsgGetIeTlv(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_IN NwU16T maxLen,
                        NW_OUT NwU8T* pVal,
                        NW_OUT NwU16T* pLen);

 /**
  * Get an information element of variable length from gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] tyep : IE Type.
  * @param[in] instance : IE instance.
  * @param[out] ppVal : Pointer to IE value buffer pointer.
  * @param[out] pLen : Pointer to IE length buffer.
  * @return NW_OK on success.
  */

NwRcT
nwGtpv2cMsgGetIeTlvP(NW_IN NwGtpv2cMsgHandleT hMsg, 
                        NW_IN NwU8T type,
                        NW_IN NwU8T instance,
                        NW_OUT NwU8T** ppVal,
                        NW_OUT NwU16T* pLen);


 /**
  * Get F-TEID information element to gtpv2c message.
  *
  * @param[in] hMsg : Handle to gtpv2c message.
  * @param[in] instance : IE instance.
  * @param[out] ifType : Interface Type.
  * @param[out] teidOrGreKey: TEID/ GRE Key
  * @param[out] ipv4Addr : Ipv4 Address in Network Byte Order.
  * @param[out] pIpv6Addr: Pointer to IPv6 Address in Network Byte Order.
  */

NwRcT
nwGtpv2cMsgGetIeFteid(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN  NwU8T       instance,
              NW_OUT NwU8T*      ifType,
              NW_OUT NwU32T*     teidOrGreKey,
              NW_OUT NwU32T*     ipv4Addr,
              NW_OUT NwU8T*      pIpv6Addr);

NwRcT
nwGtpv2cMsgGetIeCause(NW_IN NwGtpv2cMsgHandleT hMsg, 
              NW_IN  NwU8T       instance,
              NW_OUT NwU8T*      causeValue,
              NW_OUT NwU8T*      flags,
              NW_OUT NwU8T*      offendingIeType,
              NW_OUT NwU8T*      offendingIeInstance);

 /**
  * Get msg type for gtpv2c message.
  *
  * @param[in] hMsg : Message handle.
  */

NwU32T
nwGtpv2cMsgGetMsgType(NW_IN NwGtpv2cMsgHandleT hMsg);

/**
 * Dump the contents of gtpv2c message.
 *
 * @param[in] hMsg : Handle to gtpv2c message.
 * @param[in] fp: Pointer to output file.
 */

NwRcT
nwGtpv2cMsgHexDump(NwGtpv2cMsgHandleT hMsg, FILE* fp);

#ifdef __cplusplus
}
#endif

#endif /* __NW_GTPV2C_MSG_H__ */


/*--------------------------------------------------------------------------*
 *                      E N D     O F    F I L E                            *
 *--------------------------------------------------------------------------*/

