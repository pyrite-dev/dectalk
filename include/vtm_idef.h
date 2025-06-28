/*
 ***********************************************************************
 *
 *                           Coryright (c)
 *    � Digital Equipment Corporation 1995. All rights reserved.
 *
 *    Restricted Rights: Use, duplication, or disclosure by the U.S.
 *    Government is subject to restrictions as set forth in subparagraph
 *    (c) (1) (ii) of DFARS 252.227-7013, or in FAR 52.227-19, or in FAR
 *    52.227-14 Alt. III, as applicable.
 *
 *    This software is proprietary to and embodies the confidential
 *    technology of Digital Equipment Corporation and other parties.
 *    Possession, use, or copying of this software and media is authorized
 *    only pursuant to a valid written license from Digital or an
 *    authorized sublicensor.
 *
 ***********************************************************************
 *    File Name:	vtm_idef.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *  This include declares functions used by the DECtalk vocal tract
 *  model vtm.c
 *
 ***********************************************************************
 *    Revision History:
 * 0001 23-Mar-95 CJL File new.
 */

#ifndef VTM_IDEF_H
#define VTM_IDEF_H
 
#include "viport.h"

/**********************************************************************/
/*  Declare and initialize the sample rate scaling parameters.        */
/**********************************************************************/
#ifndef MINIMAL_SYNTH
extern UINT uiSampleRate;
extern UINT uiSampleRateChange;
#endif
extern int16_t rate_scale;
extern int16_t inv_rate_scale;
#ifndef MINIMAL_SYNTH
extern double SampleRate;
extern double SamplePeriod;
#endif

/**********************************************************************/
/*  Flag to test for sample rate conversion. (Not currently used)     */
/**********************************************************************/
extern char bEightKHz;
extern unsigned int uiCurrentSpeaker;

/**********************************************************************/
/*  Constant B0 controls shape of glottal pulse as a function         */
/*  of desired duration of open phase N0.                             */
/**********************************************************************/
#ifdef VARIABLE_OPEN_PERIOD
extern const int16_t B0[224];
#else
extern const int16_t voices[14];
#endif

/**********************************************************************/
/*  Data arrays for conversion of nasal antiresonator FZinHZ & BW to  */
/*  difference equation coeficients azero, bzero, and czero           */
/**********************************************************************/
extern const int16_t azero_tab[35];
extern const int16_t bzero_tab[35];
extern const int16_t czero_tab[35];

/**********************************************************************/
/*  Convertion table, db to linear,                                   */
/**********************************************************************/
extern const int16_t amptable[88];

/**********************************************************************/
/*  Cosine table used by function setb()                              */
/**********************************************************************/
extern const int16_t cosine_table[];

/**********************************************************************/
/*  Radius table used by function setc()                              */
/**********************************************************************/
extern const int16_t radius_table[];

#endif
