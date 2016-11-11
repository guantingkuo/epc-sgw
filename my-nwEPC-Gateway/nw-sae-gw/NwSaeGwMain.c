/*----------------------------------------------------------------------------*
 *                                                                            *
 *                                n w - e p c                                 * 
 *       L T E / S A E        S E R V I N G / P D N       G A T E W A Y       *
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

/** 
 * @file NwSaeGwMain.c
 * @brief This main file demostrates usage of nw-gtpv2c library for a SAE gateway(SGW/PGW) 
 * application.
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>


#include "NwEvt.h"
#include "NwLog.h"
#include "NwMem.h"
#include "NwUtils.h"
#include "NwSaeGwLog.h"
#include "NwLogMgr.h"
#include "NwGtpv2c.h"
#include "NwSaeGwUe.h"
#include "NwSaeGwUlp.h"
#include "NwGtpv2cIf.h"
#include "NwSaeGwDpe.h"

#ifdef __cplusplus
extern "C" {
#endif

#define NW_SAE_GW_MAX_GW_INSTANCE               (10)
typedef enum{
  NW_CMD_LINE_STAT_SS11=0X01,
  NW_CMD_LINE_STAT_SS5=0X02,
  NW_CMD_LINE_STAT_GI=0X04,
  NW_CMD_LINE_STAT_ALL=0x7,
}NW_CMD_LINE_STATS;

typedef struct
{
  NwU8T                         isCombinedGw;
  NwU8T                         apn[1024];
  NwU32T                        ippoolSubnet;
  NwU32T                        ippoolMask;
  NwU32T                        numOfUe;
  NwGtpv2cIfT                   udp;

  struct {
    NwU32T                      s11cIpv4Addr;
    NwU32T                      s5cIpv4Addr;
    NwU32T                      s4cIpv4Addr;
    NwU32T                      s1uIpv4Addr;
    NwSaeGwUlpT                 *pGw;
  } sgwUlp;

  struct {
    NwU32T                      s5cIpv4Addr;
    NwU32T                      s5uIpv4Addr;
    NwSaeGwUlpT                 *pGw;
  } pgwUlp;

  struct {
    NwSaeGwDpeT                 *pDpe;           /*< Data Plane Entity   */
    NwU32T                      gtpuIpv4Addr;
    NwU8T                       sgiNwIfName[128];
  } s5dataPlane;
  /* add for gtpu out by S5/S8 by guan */
  struct {
    NwSaeGwDpeT                 *pDpe;           /*< Data Plane Entity   */
    NwU32T                      gtpuIpv4Addr;
    NwU8T                       sgiNwIfName[128];
  } s1dataPlane;
  /* add end */
} NwSaeGwT;

NwRcT
nwSaeGwCmdLineHelp()
{
  printf("\nSupported command line arguments are:\n");
  printf("\n+----------------------+-------------+----------------------------------------+");
  printf("\n| ARGUMENT             | PRESENCE    | DESCRIPTION                            |");
  printf("\n+----------------------+-------------+----------------------------------------+");
  printf("\n| --sgw-s11-ip | -ss11 | MANDATORY   | S11 control IP address of the SGW.     |");
  printf("\n| --sgw-s5-ip  | -ss5  | MANDATORY   | S5 control IP address of the SGW.      |");
  printf("\n| --sgw-s1u-ip | -ss1u | MANDATORY   | IP address for the GTPU User Plane.    |");
  printf("\n| --sgw-s4-ip  | -ss4  | OPTIONAL    | S4 control IP address of the SGW.      |");
//printf("\n| --pgw-s5-ip  | -ps5  | MANDATORY   | S5 control IP address of the PGW.      |");
//printf("\n| --apn        | -ap   | OPTIONAL    | Access Point Name to be served.        |");
//printf("\n| --ippool-subnet| -is | OPTIONAL    | IPv4 address pool for UEs.             |");
//printf("\n| --ippool-mask | -im  | OPTIONAL    | IPv4 address pool for UEs.             |");
//printf("\n| --sgi-if     | -si   | OPTIONAL    | Network interface name for the SGi.    |");
//printf("\n| --max-ue     | -mu   | OPTIONAL    | Maximum number of UEs to support.      |");
//printf("\n| --combined-gw | -cgw | OPTIONAL    | Combine SGW and PGW funtions.          |");
  printf("\n+----------------------+-------------+----------------------------------------+");
//printf("\n\nExample Usage: \n$ nwLteSaeGw --sgw-s11-ip 10.124.25.153 --sgw-s5-ip 192.168.0.1 --pgw-s5-ip 192.168.139.5 --gtpu-ip 10.124.25.153 --sgi-if eth0 --ippool-subnet 10.66.10.0 --ippool-mask 255.255.255.0 -cgw");
  printf("\n\nExample Usage: \n$ nwLteSaeGw --sgw-s11-ip 10.124.25.153 --sgw-s5-ip 192.168.0.1 --sgw-s4-ip 192.168.139.5 --sgw-s1u-ip 10.124.25.153 ");
  printf("\n");
  exit(0);
}

NwRcT
nwSaeGwParseCmdLineOpts(NwSaeGwT*  thiz, int argc, char* argv[])
{
  NwRcT rc = NW_OK;
  int i = 0;
  int cmdline_stat;

  if(argc < 2)
    return NW_FAILURE;
  
  /* Set default values */
  thiz->isCombinedGw    = NW_FALSE;
  thiz->numOfUe         = 1000;
  thiz->ippoolSubnet    = ntohl(inet_addr("10.128.0.0"));
  thiz->ippoolMask      = ntohl(inet_addr("255.255.0.0"));
  strcpy((char*)thiz->s1dataPlane.sgiNwIfName, "");
  strcpy((char*)thiz->s5dataPlane.sgiNwIfName, "");
  cmdline_stat=0;

  i++;
  while( i < argc )
  {
    NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "Processing cmdline arg %s", argv[i]);
    if((strcmp("--sgw-s11-ip", argv[i]) == 0)
        || (strcmp(argv[i], "-ss11") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      thiz->sgwUlp.s11cIpv4Addr = ntohl(inet_addr(argv[i]));
	  cmdline_stat|=NW_CMD_LINE_STAT_SS11;
    }
    else if((strcmp("--sgw-s5-ip", argv[i]) == 0)
        || (strcmp(argv[i], "-ss5") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      thiz->sgwUlp.s5cIpv4Addr  = ntohl(inet_addr(argv[i]));
	  cmdline_stat|=NW_CMD_LINE_STAT_SS5;
    }
    else if((strcmp("--sgw-s4-ip", argv[i]) == 0)
        || (strcmp(argv[i], "-ss4") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      thiz->sgwUlp.s4cIpv4Addr  = ntohl(inet_addr(argv[i]));
    }
#if 0
    else if((strcmp("--pgw-s5-ip", argv[i]) == 0)
        || (strcmp(argv[i], "-ps5") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      thiz->pgwUlp.s5cIpv4Addr  = ntohl(inet_addr(argv[i])); 
    }
#endif
    else if((strcmp("--apn", argv[i]) == 0)
        || (strcmp(argv[i], "-ap") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;
      strncpy((char*)thiz->apn, argv[i], 1023);
    }
    else if((strcmp("--ippool-subnet", argv[i]) == 0)
        || (strcmp(argv[i], "-is") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;
      thiz->ippoolSubnet = ntohl(inet_addr(argv[i]));
      NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "IP pool subnet address %s", argv[i]);
    }
    else if((strcmp("--ippool-mask", argv[i]) == 0)
        || (strcmp(argv[i], "-im") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;
      thiz->ippoolMask = ntohl(inet_addr(argv[i]));
      NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "Ip pool mask %s", argv[i]);
    }
    else if((strcmp("--sgw-s1u-ip", argv[i]) == 0)
        || (strcmp(argv[i], "-ss1u") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "User Plane IP address %s", argv[i]);
      thiz->s1dataPlane.gtpuIpv4Addr = ntohl(inet_addr(argv[i]));
	  cmdline_stat |= NW_CMD_LINE_STAT_GI;
    }
    else if((strcmp("--sgi-if", argv[i]) == 0)
        || (strcmp(argv[i], "-si") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "SGi network inteface name %s", argv[i]);
      strcpy((char*)thiz->s1dataPlane.sgiNwIfName, (argv[i]));
    }
    else if((strcmp("--num-of-ue", argv[i]) == 0)
        || (strcmp(argv[i], "-nu") == 0))
    {
      i++;
      if(i >= argc)
        return NW_FAILURE;

      NW_SAE_GW_LOG(NW_LOG_LEVEL_DEBG, "number of UE %s", argv[i]);
      thiz->numOfUe = atoi(argv[i]);
    }
#if 0
    else if((strcmp("--combined-gw", argv[i]) == 0)
        || (strcmp(argv[i], "-cgw") == 0))
    {
      thiz->isCombinedGw = NW_TRUE;
    }
#endif
    else if((strcmp("--help", argv[i]) == 0)
        || (strcmp(argv[i], "-h") == 0))
    {
      nwSaeGwCmdLineHelp();
    }
    else
    {
      rc = NW_FAILURE;
    }
    i++;
  }

  if(cmdline_stat != (NW_CMD_LINE_STAT_ALL))
  {
	  nwSaeGwCmdLineHelp();
  }
  return rc;
}

NwRcT
nwSaeGwInitialize(NwSaeGwT* thiz)
{
  NwRcT rc = NW_OK;
  NwSaeGwUlpT* pGw;
  NwSaeGwUlpConfigT cfg;

  /* Create Data Plane instance. */

  thiz->s1dataPlane.pDpe    = nwSaeGwDpeInitialize();
  thiz->s5dataPlane.pDpe    = nwSaeGwDpeInitialize();

  /* Create SGW and PGW ULP instances. */
  if(thiz->sgwUlp.s11cIpv4Addr)
  {

    NW_SAE_GW_LOG(NW_LOG_LEVEL_NOTI, "Creating SGW instance with S11 IPv4 address "NW_IPV4_ADDR, NW_IPV4_ADDR_FORMAT(htonl(thiz->sgwUlp.s11cIpv4Addr)));

    cfg.maxUeSessions   = thiz->numOfUe;
    cfg.ippoolSubnet    = thiz->ippoolSubnet;
    cfg.ippoolMask      = thiz->ippoolMask;
    cfg.s11cIpv4Addr    = thiz->sgwUlp.s11cIpv4Addr;
    cfg.s5cIpv4AddrSgw  = thiz->sgwUlp.s5cIpv4Addr;
    cfg.s4cIpv4AddrSgw  = thiz->sgwUlp.s4cIpv4Addr;
/* add for gtpu out by s5/s8 by guan */
    cfg.s1pDpe            = thiz->s1dataPlane.pDpe;
	cfg.s5pDpe			  = thiz->s5dataPlane.pDpe;
/* add end */
    strncpy((char*)cfg.apn, (const char*)thiz->apn, 1023);

    pGw = nwSaeGwUlpNew(); 
    rc = nwSaeGwUlpInitialize(pGw, NW_SAE_GW_TYPE_SGW, &cfg);
    NW_ASSERT( NW_OK == rc );
    thiz->sgwUlp.pGw = pGw;
  }
/* del the pgw by guan */
#if 0

  if(thiz->pgwUlp.s5cIpv4Addr)
  {

    NW_SAE_GW_LOG(NW_LOG_LEVEL_NOTI, "Creating PGW instance with S5 Ipv4 address "NW_IPV4_ADDR, NW_IPV4_ADDR_FORMAT(htonl(thiz->pgwUlp.s5cIpv4Addr)));

    cfg.maxUeSessions   = thiz->numOfUe;
    cfg.ippoolSubnet    = thiz->ippoolSubnet;
    cfg.ippoolMask      = thiz->ippoolMask;
    cfg.s5cIpv4AddrPgw  = thiz->pgwUlp.s5cIpv4Addr;
    cfg.pDpe            = thiz->dataPlane.pDpe;

    strncpy((char*)cfg.apn, (const char*)thiz->apn, 1023);

    pGw = nwSaeGwUlpNew(); 
    rc = nwSaeGwUlpInitialize(pGw, NW_SAE_GW_TYPE_PGW, &cfg);
    NW_ASSERT( NW_OK == rc );
    thiz->pgwUlp.pGw = pGw;
  }
  
  /* Register collocated PGW, if any */
  if(thiz->isCombinedGw && 
      (thiz->sgwUlp.pGw && thiz->pgwUlp.pGw))
  {
    rc = nwSaeGwUlpRegisterCollocatedPgw(thiz->sgwUlp.pGw, thiz->pgwUlp.pGw);
    NW_ASSERT(NW_OK == rc);
  }

#endif

  if(thiz->s1dataPlane.gtpuIpv4Addr)
  {
  	/* mod for gtpu out by S5/S8 by guan */
    //rc = nwSaeGwDpeCreateGtpuService(thiz->dataPlane.pDpe, thiz->dataPlane.gtpuIpv4Addr);
    thiz->s5dataPlane.gtpuIpv4Addr = thiz->sgwUlp.s5cIpv4Addr;
    rc = nwSaeGwDpeCreateSgwGtpuService(thiz->s1dataPlane.pDpe, thiz->s1dataPlane.gtpuIpv4Addr,thiz->s5dataPlane.pDpe, thiz->s5dataPlane.gtpuIpv4Addr);
	/* mod end */
	
  }

  if(strlen((const char*)(thiz->s1dataPlane.sgiNwIfName)) != 0)
  {
    rc = nwSaeGwDpeCreateIpv4Service(thiz->s1dataPlane.pDpe, thiz->s1dataPlane.sgiNwIfName);
  }
 
  return rc;
}

NwRcT
nwSaeGwFinalize(NwSaeGwT*  thiz)
{
  return NW_OK;
}

/*---------------------------------------------------------------------------
 *                T H E      M A I N      F U N C T I O N 
 *--------------------------------------------------------------------------*/

int main(int argc, char* argv[])
{
  NwRcT rc; 

  NwSaeGwT                  saeGw;
  memset(&saeGw, 0, sizeof(NwSaeGwT));

  /*---------------------------------------------------------------------------
   *  Parse Commandline Arguments 
   *--------------------------------------------------------------------------*/

  rc = nwSaeGwParseCmdLineOpts(&saeGw, argc, argv);
  if(rc != NW_OK)
  {
    printf("\nUsage error. Please refer help.\n\n");
    exit(0);
  }


  /*---------------------------------------------------------------------------
   *  Initialize event library
   *--------------------------------------------------------------------------*/

  NW_EVT_INIT();

  /*---------------------------------------------------------------------------
   *  Initialize Memory Manager 
   *--------------------------------------------------------------------------*/

  rc = nwMemInitialize();
  NW_ASSERT(NW_OK == rc);

  /*---------------------------------------------------------------------------
   *  Initialize LogMgr
   *--------------------------------------------------------------------------*/

  rc = nwLogMgrInit(nwLogMgrGetInstance(), (NwU8T*)"NW-SGW", getpid());
  NW_ASSERT(NW_OK == rc);

  /*---------------------------------------------------------------------------
   * Initialize SAE GW 
   *--------------------------------------------------------------------------*/

  rc =  nwSaeGwInitialize(&saeGw);
  NW_ASSERT(NW_OK == rc);

  /*---------------------------------------------------------------------------
   * Event Loop 
   *--------------------------------------------------------------------------*/

  NW_EVT_LOOP();

  NW_SAE_GW_LOG(NW_LOG_LEVEL_ERRO, "Exit from eventloop, no events to process!");

  /*---------------------------------------------------------------------------
   * Finalize SAE GW 
   *--------------------------------------------------------------------------*/

  rc =  nwSaeGwFinalize(&saeGw);
  NW_ASSERT(NW_OK == rc);

  rc =  nwMemFinalize();
  NW_ASSERT(NW_OK == rc);

  return 0;
}

#ifdef __cplusplus
}
#endif
