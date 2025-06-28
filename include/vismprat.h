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
 *    File Name:	vismprat.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *  This include file declares the default sample rates for the VTM
 *      (Vocal Tract Model) used in DECtalk.
 *
 ***********************************************************************
 *    Revision History:
 * 0001 23-Mar-95 CJL Change this file name from samprate.h to
 *                      vismprat.h, add #define to exclude muliple
 *                      includes.
 * 0002 24-Mar-95 CJL Move d2pole_cf45, d2pole_cf123 & d2pole_pf from
 *						vtm_i.h and vtmfunci.h here, when vtm.c was
 *						broken into sub-files.
 */

#ifndef VISMPRAT_H
#define VISMPRAT_H


#ifdef Multiple_Sample_Rates
#define  PC_SAMPLE_RATE    11025
#define  MULAW_SAMPLE_RATE   8000

/**********************************************************************/
/*  Declare and initialize the sample rate scaling parameters.        */
/**********************************************************************/

UINT uiSampleRate = 11025;
UINT uiSampleRateChange = SAMPLE_RATE_INCREASE;
int16_t rate_scale = 18063;
int16_t inv_rate_scale = 29722;
UINT uiNumberOfSamplesPerFrame = 71;
double SampleRate = 11025.0;
double SamplePeriod = 9.07029478458E-5;

#else
//#define  PC_SAMPLE_RATE    8000
//#define  MULAW_SAMPLE_RATE   8000
//UINT uiSampleRate = 8000;
//UINT uiSampleRateChange = SAMPLE_RATE_DECREASE;
//int16_t rate_scale = 18063;
//int16_t inv_rate_scale = 29722;
//UINT uiNumberOfSamplesPerFrame = 51;
//double SampleRate = 8000.0;
//double SamplePeriod = 9.07029478458E-5;
#endif

extern short arg1,arg2,arg3;
/**********************************************************************/
/*  Flag to test for sample rate conversion. (Not currently used)     */
/**********************************************************************/
char bEightKHz = FALSE;
unsigned int uiCurrentSpeaker = 0;

/**********************************************************************/
/*                                                                    */
/*  Function: d2pole_cf45                                             */
/*                                                                    */
/*  Convert formant bandwidth into resonator difference equation      */
/*  constants "acoef, bcoef, and ccoef".                              */
/*                                                                    */
/*  If the filter response extends to over Fs/2 then this function    */
/*  will make the filter an all pass filter with unity gain. This is  */
/*  used only for the cascade filters for formants 4 and 5.           */
/*                                                                    */
/**********************************************************************/

int16_t radius;    /*  Radius of pole locations                           */
/* 24-mar-95 cjl missing declaration.*/
int16_t temp5;

int16_t d2pole_cf45( int16_t * bcoef,
                 int16_t * ccoef,
                 int16_t frequency,
                 int16_t bandwidth,
                 int16_t gain )
{
  int16_t acoef;

  /********************************************************************/
  /*  Scale the frequency and bandwidth if the sample rate is not     */
  /*  10 KHz.                                                         */
  /********************************************************************/
#ifdef Multiple_Sample_Rates
  if ( uiSampleRateChange == SAMPLE_RATE_DECREASE )
  {
	  frequency = frac1mul(inv_rate_scale, frequency) << 1;
	  bandwidth = frac1mul(inv_rate_scale, bandwidth) << 1;
  }
  else
  {
    if ( uiSampleRateChange == SAMPLE_RATE_INCREASE )
    {
	  arg1=inv_rate_scale; arg2=frequency;
      frequency = frac1mul(inv_rate_scale, frequency);
      bandwidth = frac1mul(inv_rate_scale, bandwidth);
    }
  }
#else

	  frequency = frac1mul(20480, frequency) << 1;
	  bandwidth = frac1mul(20480, bandwidth) << 1;
#endif

  /********************************************************************/
  /*  Zap resonator if center frequency above maximum frequency.      */ 
  /********************************************************************/

  if ( frequency >= 4500 )
  {
    *bcoef = 0;
    *ccoef = 0;
  }
  else
  {
    /******************************************************************/
    /*  calculate radius = exp( -pi * T * bandwidth ).                */
    /******************************************************************/

    radius = radius_table[bandwidth >> 3];

    /******************************************************************/
    /*  bcoef = radius * 2 * cos( 2* pi * T * frequency )             */
    /******************************************************************/

    *bcoef = frac4mul( radius, cosine_table[ frequency >> 3 ] );

    /******************************************************************/
    /*  Let ccoef = - r^2                                             */
    /******************************************************************/

    *ccoef = - frac4mul( radius, radius );
  }

  /********************************************************************/
  /*  Let acoef = 1.0 - bcoef - ccoef                                 */
  /********************************************************************/

  temp5 = 4096 - *bcoef - *ccoef;
  
  /********************************************************************/
  /*  Adjust "acoef" by the gain term to keep output signal of the    */
  /*  resonator in the high-order bits.                               */
  /********************************************************************/

  acoef = frac4mul( gain, temp5 ) << 1;

  return( acoef );
}

/**********************************************************************/
/*                                                                    */
/*  Function: d2pole_cf123                                            */
/*                                                                    */
/*  Convert formant bandwidth into resonator difference equation      */
/*  constants "acoef, bcoef, and ccoef".                              */
/*                                                                    */
/*  If the filter response extends to over Fs/2 then this function    */
/*  will set the filter center frequency to Fs/2 and make the         */
/*  bandwidth Fs/4. This is used for cascade formants 1, 2, and 3.    */
/*  If the formant frequency move over Fs/2, this function will cause */
/*  the filter to be effectively removed (over a short filter decay   */
/*  time) without causing an abrupt gain change.                      */
/*                                                                    */
/**********************************************************************/

int16_t d2pole_cf123( int16_t * bcoef,
                  int16_t * ccoef,
                  int16_t frequency,
                  int16_t bandwidth,
                  int16_t gain )
{
  int16_t acoef;

  /********************************************************************/
  /*  Scale the frequency and bandwidth if the sample rate is not     */
  /*  10 KHz.                                                         */
  /********************************************************************/
#ifdef Multiple_Sample_Rates
  if ( uiSampleRateChange == SAMPLE_RATE_DECREASE )
  {
    frequency = frac1mul(inv_rate_scale, frequency) << 1;
    bandwidth = frac1mul(inv_rate_scale, bandwidth) << 1;
  }
  else
  {
    if ( uiSampleRateChange == SAMPLE_RATE_INCREASE )
    {
      frequency = frac1mul(inv_rate_scale, frequency);
      bandwidth = frac1mul(inv_rate_scale, bandwidth);
    }
  }
#else
    frequency = frac1mul(20480, frequency) << 1;
    bandwidth = frac1mul(20480, bandwidth) << 1;
#endif
  /********************************************************************/
  /*  Zap resonator if center frequency above maximum frequency.      */ 
  /********************************************************************/
#ifdef Multiple_Sample_Rates
  if ( frequency >= 4500 )
  {
    frequency = uiSampleRate >> 1;
    bandwidth = uiSampleRate >> 2;
  }
#endif
  /********************************************************************/
  /*  calculate radius = exp( -pi * T * bandwidth ).                  */
  /********************************************************************/

  radius = radius_table[bandwidth >> 3];

  /********************************************************************/
  /*  bcoef = radius * 2 * cos( 2* pi * T * frequency )               */
  /********************************************************************/

  *bcoef = frac4mul( radius, cosine_table[ frequency >> 3 ] );

  /********************************************************************/
  /*  Let ccoef = - r^2                                               */
  /********************************************************************/

  *ccoef = - frac4mul( radius, radius );

  /********************************************************************/
  /*  Let acoef = 1.0 - bcoef - ccoef                                 */
  /********************************************************************/

  temp5 = 4096 - *bcoef - *ccoef;
  
  /********************************************************************/
  /*  Adjust "acoef" by the gain term to keep output signal of the    */
  /*  resonator in the high-order bits.                               */
  /********************************************************************/

  acoef = frac4mul( gain, temp5 );

  return( acoef );
}

/**********************************************************************/
/*                                                                    */
/*  Function: d2pole_pf                                               */
/*                                                                    */
/*  Convert formant bandwidth into resonator difference equation      */
/*  constants "acoef, bcoef, and ccoef".                              */
/*                                                                    */
/*  If the filter response extends to over Fs/2 then this function    */
/*  will set the filter gain to zero to remove the filter. This is    */
/*  used for the parallel filters (Except P6 which is used to         */
/*  to generate the 'S' sound.)                                       */
/*                                                                    */
/**********************************************************************/

int16_t d2pole_pf( int16_t * bcoef,
               int16_t * ccoef,
               int16_t frequency,
               int16_t bandwidth,
               int16_t gain )
{
  int16_t acoef;

  /********************************************************************/
  /*  Scale the frequency and bandwidth if the sample rate is not     */
  /*  10 KHz.                                                         */
  /********************************************************************/
#ifdef Multiple_Sample_Rates
  if ( uiSampleRateChange == SAMPLE_RATE_DECREASE )
  {
    frequency = frac1mul(inv_rate_scale, frequency) << 1;
    bandwidth = frac1mul(inv_rate_scale, bandwidth) << 1;
  }
  else
  {
    if ( uiSampleRateChange == SAMPLE_RATE_INCREASE )
    {
      frequency = frac1mul(inv_rate_scale, frequency );
      bandwidth = frac1mul(inv_rate_scale, bandwidth );
    }
  }
#else
    frequency = frac1mul(20480, frequency) << 1;
    bandwidth = frac1mul(20480, bandwidth) << 1;


#endif
  /********************************************************************/
  /*  Zap resonator if center frequency above maximum frequency.      */ 
  /********************************************************************/

  if ( frequency >= 4500 )
  {
    *bcoef = 0;
    *ccoef = 0;
    acoef = 0;
  }
  else
  {
    /******************************************************************/
    /*  calculate radius = exp( -pi * T * bandwidth ).                */
    /******************************************************************/

    radius = radius_table[bandwidth >> 3];

    /******************************************************************/
    /*  bcoef = radius * 2 * cos( 2* pi * T * frequency )             */
    /******************************************************************/

    *bcoef = frac4mul( radius, cosine_table[ frequency >> 3 ] );

    /******************************************************************/
    /*  Let ccoef = - r^2                                             */
    /******************************************************************/

    *ccoef = - frac4mul( radius, radius );

    /******************************************************************/
    /*  Let acoef = 1.0 - bcoef - ccoef                               */
    /******************************************************************/

    temp5 = 4096 - *bcoef - *ccoef;
  
    /******************************************************************/
    /*  Adjust "acoef" by the gain term to keep output signal of the  */
    /*  resonator in the high-order bits.                             */
    /******************************************************************/

    acoef = frac4mul( gain, temp5 ) << 1;
  }
  return( acoef );
}

#endif
