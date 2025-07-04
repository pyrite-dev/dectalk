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
 *    File Name:	vtmtabi.h
 *    Author:
 *    Creation Date:
 *
 *    Functionality:
 *  This include declares the tables used by the DECtalk vocal tract  
 *  model vtm.c                                                       
 *                                                                    
 *  This file is "included" in VAX.C (separated for clarity)          
 *  Data tables used to speed up synthesizer calculations             
 *                                                                    
 *  Modified 3-Sep-86 to accept samrat=8000                           
 *                                                                    
 *  Tables herein not modified, but all tables should be accessed     
 *  by a pointer p that has been changed to (p*10)>>3.                
 *  I.e. a freq of 4000 should access f=5000 in icos[]                
 *  and in azero[], bzero[], and czero[].                             
 *  And the number of samples in the open portion of the glottal      
 *  period n should be changed to (n*8)/10 before accessing           
 *  the B0[] table, but since this involves a divide and is           
 *  not that critical, (n*13)>>4 will be performed instead.           
 *
 ***********************************************************************
 *    Revision History:
 * 0001 23-Mar-95 CJL Changed this file from vtmtable.h to vtmtabli.h
 *                      add #define to exclude multiple includes.
 */

#ifndef VTMTABLI_H
#define VTMTABLI_H

//#ifdef VARIABLE_OPEN_PERIOD
/**********************************************************************/
/*                                                                    */
/*  Constant B0 controls shape of glottal pulse as a function         */
/*  of desired duration of open phase N0.                             */
/*                                                                    */
/*  (Note that N0 is specified in terms of 4 times the output sample  */
/*  rate )                                                            */
/*                                                                    */
/*  Assume voicing waveform V(t) has form: k1 t**2 - k2 t**3          */
/*                                                                    */
/*  If the radiation characteristic, a temporal derivative is folded  */
/*  in, and we go from continuous time to discrete integers n:        */
/*                                                                    */
/*  dV/dt = voice0[n] = sum over i=1,2,...,n of { a - (i * b) }       */
/*                                                                    */
/*                    = a n  -  b/2 n**2                              */
/*                                                                    */
/*  WHERE the constants a and b control the detailed shape and        */
/*  amplitude of the voicing waveform over the open portion of the    */
/*  voicing cycle "nopen".                                            */
/*                                                                    */
/*  Let integral of dV/dt have no net dc flow --> a = (b * nopen) / 3 */
/*                                                                    */
/*  Let maximum of dUg(n)/dn be constant i.e. :                       */
/*                                                                    */
/*      b = gain / (nopen * nopen)                                    */
/*                                                                    */
/*  meaning as nopen gets bigger, V has bigger peak proportional to n */
/*                                                                    */
/*  Thus, to generate the table below for 40 <= nopen <= 263:         */
/*                                                                    */
/*      B0[nopen - 40] = 1920000 / (nopen * nopen)                    */
/*                                                                    */
/**********************************************************************/

const int16_t B0[224] = {
        1200,   1142,   1088,   1038,   991,    
        948,    907,    869,    833,    799,
        768,    738,    710,    683,    658,
        634,    612,    590,    570,    551,
        533,    515,    499,    483,    468,
        454,    440,    427,    415,    403,
        391,    380,    370,    360,    350,
        341,    332,    323,    315,    307,
        300,    292,    285,    278,    272,
        265,    259,    253,    247,    242,
        237,    231,    226,    221,    217,
        212,    208,    204,    199,    195,
        192,    188,    184,    180,    177,
        174,    170,    167,    164,    161,
        158,    155,    153,    150,    147,
        145,    142,    140,    137,    135,
        133,    131,    128,    126,    124,
        122,    120,    119,    117,    115,
        113,    111,    110,    108,    106,
        105,    103,    102,    100,    99,
        97,     96,     95,     93,     92,
        91,     90,     88,     87,     86,
        85,     84,     83,     82,     80,
        79,     78,     77,     76,     75,
        75,     74,     73,     72,     71,
        70,     69,     68,     68,     67,
        66,     65,     64,     64,     63,
        62,     61,     61,     60,     59,
        59,     58,     57,     57,     56,
        56,     55,     55,     54,     54,
        53,     53,     52,     52,     51,
        51,     50,     50,     49,     49,
        48,     48,     47,     47,     46,
        46,     45,     45,     44,     44,
        43,     43,     42,     42,     41,
        41,     41,     41,     40,     40,
        39,     39,     38,     38,     38,
        38,     37,     37,     36,     36,
        36,     36,     35,     35,     35,
        35,     34,     34,     33,     33,
        33,     33,     32,     32,     32,
        32,     31,     31,     31,     31,
        30,     30,     30,     30,     29,
        29,     29,     29,     28,     28,
        28,     28,     27,     27
};
//#else
const int16_t voices[14]= {
		752,	3280,	5040,	6032,	6256,
		5712,	4400,	2320,	-528,	-3168,
		-4144,	-8528,	-13680,	-19600
};
//#endif


/**********************************************************************/
/*                                                                    */
/*  Data arrays for conversion of nasal antiresonator FZinHZ & BW to  */
/*  difference equation coeficients azero, bzero, and czero           */
/*                                                                    */
/*  The arrays azero_tab[FZinHZ/8 - 31],                              */
/*             bzero_tab[FZinHZ/8 - 31],                              */
/*             czero_tab[FZinHZ/8 - 31],                              */
/*                                                                    */
/*  were computed from the equations:                                 */
/*                                                                    */
/*    C = exp(- 2 pi BW T )                                           */
/*      =~ (2 * BW) - 4096                                            */
/*                                                                    */
/*    B = 2 exp(- pi BW T) * cos(2 pi FZinHZ T)                       */
/*      =~ (8192 - 2*BW) * getcos(FZinHZ) / 8192                      */
/*                                                                    */
/*    A = 1.0 - A - B                                                 */
/*      = 4096 - A - B                                                */
/*                                                                    */
/*      azero = 4096 * ZGAIN/A                                        */
/*      bzero = -B * ZGAIN/A                                          */
/*      czero = -C * ZGAIN/A                                          */
/*                                                                    */
/*  where  FZinHZ = 248, 256, 264, ..., 528 Hz                        */
/*  and BW was fixed at 80 Hz                                         */
/*  and the gain factor ZGAIN is currently 93, but could be           */
/*  increased to keep signal in high-order bits.                      */
/*                                                                    */
/**********************************************************************/

const int16_t azero_tab[35] = {
        3864, 3611, 3405, 3207, 3018,
        2861, 2700, 2555, 2434, 2309,
        2195, 2093, 1994, 1904, 1822,
        1742, 1669, 1598, 1533, 1473,
        1415, 1361, 1312, 1263, 1216,
        1172, 1131, 1094, 1056, 1020,
        988,  963,  926,  897,  869
};

const int16_t bzero_tab[35] = {
        -7453, -6960, -6558, -6171, -5802,
        -5496, -5181, -4899, -4662, -4418,
        -4197, -3996, -3803, -3628, -3467,
        -3312, -3169, -3031, -2905, -2788,
        -2674, -2569, -2472, -2377, -2285,
        -2200, -2120, -2046, -1974, -1903,
        -1840, -1778, -1719, -1662, -1609
};

const int16_t czero_tab[35] = {
        3677, 3437, 3241, 3052, 2872,
        2723, 2569, 2432, 2316, 2197,
        2089, 1992, 1897, 1812, 1734,
        1658, 1588, 1521, 1459, 1402,
        1347, 1296, 1248, 1202, 1157,
        1115, 1077, 1041, 1005,  971,
         940,  910,  881,  853,  827
};

/**********************************************************************/
/*                                                                    */
/*  Convertion table, db to linear,                                   */
/*                                                                    */
/*  87 dB --> 32767                                                   */
/*  86 dB --> 29491 (1 dB down = 0.5**1/6)                            */
/*  ...                                                               */
/*  81 dB --> 16384 (6 dB down = 0.5)                                 */
/*  ...                                                               */
/*  0 dB -->     0                                                    */
/*                                                                    */
/*  The just noticeable difference for a change in sensitivity of a   */
/*  vowel is approximately 1 dB.  Thus all amplitudes are quantized   */
/*  to 1 dB steps.                                                    */
/*                                                                    */
/**********************************************************************/

const int16_t amptable[88] = {
        0,0,0,0,0,0,0,0,0,0,0,0,0,6,7,8,
        9,10,11,13,14,16,18,20,22,25,28,32,
        35,40,45,51,57,64,71,80,90,101,114,128,
        142,159,179,202,227,256,284,318,359,405,455,512,
        568,638,719,811,911,1024,
        1137,1276,1438,1622,1823,2048,
        2273,2552,2875,3244,3645,4096,
        4547,5104,5751,6488,7291,8192,
        9093,10207,11502,12976,14582,16384,
        18350,20644,23429,26214,29491,32767
};

/**********************************************************************/
/*                                                                    */
/*  Cosine table used by function setb()                              */
/*                                                                    */
/*  (Note that the just-noticable difference for a formant frequency  */
/*  change in a vowel is about 3%.)                                   */
/*  (Note also that a 8 Hz change at F=200Hz is a 4% change,          */
/*  yet it affects only the 2 least-significant bits of "cosine",     */
/*  implying that a 13-bit coefficent constraint would lead           */
/*  to perceptable formant frequency quantization.)                   */
/*                                                                    */
/*  cosine = 8192 * cos(2 pi F / 10,000) where F=0,8,16,...,4996      */
/*                                                                    */
/**********************************************************************/

const int16_t cosine_table[] = {
/* frequency = 0,... */
      8192,  8191,  8191,  8191,  8190,  8189,  8188,  8186,  8185,  8183,
/* frequency = 80,... */
      8181,  8179,  8177,  8174,  8171,  8168,  8165,  8162,  8158,  8154,
/* frequency = 160,... */
      8150,  8146,  8141,  8137,  8132,  8127,  8122,  8116,  8110,  8105,
/* frequency = 240,... */
      8099,  8092,  8086,  8079,  8072,  8065,  8058,  8050,  8043,  8035,
/* frequency = 320,... */
      8026,  8018,  8010,  8001,  7992,  7983,  7973,  7964,  7954,  7944,
/* frequency = 400,... */
      7934,  7924,  7913,  7903,  7892,  7880,  7869,  7858,  7846,  7834,
/* frequency = 480,... */
      7822,  7809,  7797,  7784,  7771,  7758,  7745,  7731,  7718,  7704,
/* frequency = 560,... */
      7690,  7675,  7661,  7646,  7631,  7616,  7601,  7586,  7570,  7554,
/* frequency = 640,... */
      7538,  7522,  7505,  7489,  7472,  7455,  7438,  7421,  7403,  7385,
/* frequency = 720,... */
      7367,  7349,  7331,  7313,  7294,  7275,  7256,  7237,  7218,  7198,
/* frequency = 800,... */
      7178,  7158,  7138,  7118,  7097,  7077,  7056,  7035,  7014,  6992,
/* frequency = 880,... */
      6971,  6949,  6927,  6905,  6883,  6861,  6838,  6815,  6792,  6769,
/* frequency = 960,... */
      6746,  6722,  6699,  6675,  6651,  6627,  6603,  6578,  6554,  6529,
/* frequency = 1040,... */
      6504,  6479,  6453,  6428,  6402,  6377,  6351,  6325,  6298,  6272,
/* frequency = 1120,... */
      6245,  6219,  6192,  6165,  6138,  6110,  6083,  6055,  6027,  5999,
/* frequency = 1200,... */
      5971,  5943,  5915,  5886,  5857,  5828,  5799,  5770,  5741,  5712,
/* frequency = 1280,... */
      5682,  5652,  5622,  5592,  5562,  5532,  5501,  5471,  5440,  5409,
/* frequency = 1360,... */
      5378,  5347,  5316,  5284,  5253,  5221,  5189,  5158,  5126,  5093,
/* frequency = 1440,... */
      5061,  5029,  4996,  4963,  4930,  4898,  4864,  4831,  4798,  4765,
/* frequency = 1520,... */
      4731,  4697,  4664,  4630,  4596,  4561,  4527,  4493,  4458,  4424,
/* frequency = 1600,... */
      4389,  4354,  4319,  4284,  4249,  4214,  4178,  4143,  4107,  4072,
/* frequency = 1680,... */
      4036,  4000,  3964,  3928,  3892,  3856,  3819,  3783,  3746,  3709,
/* frequency = 1760,... */
      3673,  3636,  3599,  3562,  3525,  3487,  3450,  3413,  3375,  3338,
/* frequency = 1840,... */
      3300,  3262,  3225,  3187,  3149,  3111,  3073,  3034,  2996,  2958,
/* frequency = 1920,... */
      2919,  2881,  2842,  2803,  2765,  2726,  2687,  2648,  2609,  2570,
/* frequency = 2000,... */
      2531,  2492,  2453,  2413,  2374,  2334,  2295,  2255,  2216,  2176,
/* frequency = 2080,... */
      2136,  2097,  2057,  2017,  1977,  1937,  1897,  1857,  1817,  1776,
/* frequency = 2160,... */
      1736,  1696,  1656,  1615,  1575,  1535,  1494,  1454,  1413,  1372,
/* frequency = 2240,... */
      1332,  1291,  1251,  1210,  1169,  1128,  1087,  1047,  1006,   965,
/* frequency = 2320,... */
       924,   883,   842,   801,   760,   719,   678,   637,   596,   555,
/* frequency = 2400,... */
       514,   473,   432,   391,   349,   308,   267,   226,   185,   144,
/* frequency = 2480,... */
       102,    61,    20,   -20,   -61,  -102,  -144,  -185,  -226,  -267,
/* frequency = 2560,... */
      -308,  -349,  -391,  -432,  -473,  -514,  -555,  -596,  -637,  -678,
/* frequency = 2640,... */
      -719,  -760,  -801,  -842,  -883,  -924,  -965, -1006, -1047, -1087,
/* frequency = 2720,... */
     -1128, -1169, -1210, -1250, -1291, -1332, -1372, -1413, -1454, -1494,
/* frequency = 2800,... */
     -1535, -1575, -1615, -1656, -1696, -1736, -1776, -1817, -1857, -1897,
/* frequency = 2880,... */
     -1937, -1977, -2017, -2057, -2097, -2136, -2176, -2216, -2255, -2295,
/* frequency = 2960,... */
     -2334, -2374, -2413, -2453, -2492, -2531, -2570, -2609, -2648, -2687,
/* frequency = 3040,... */
     -2726, -2765, -2803, -2842, -2881, -2919, -2958, -2996, -3034, -3073,
/* frequency = 3120,... */
     -3111, -3149, -3187, -3225, -3262, -3300, -3338, -3375, -3413, -3450,
/* frequency = 3200,... */
     -3487, -3525, -3562, -3599, -3636, -3673, -3709, -3746, -3783, -3819,
/* frequency = 3280,... */
     -3855, -3892, -3928, -3964, -4000, -4036, -4072, -4107, -4143, -4178,
/* frequency = 3360,... */
     -4214, -4249, -4284, -4319, -4354, -4389, -4424, -4458, -4493, -4527,
/* frequency = 3440,... */
     -4561, -4596, -4630, -4663, -4697, -4731, -4765, -4798, -4831, -4864,
/* frequency = 3520,... */
     -4898, -4930, -4963, -4996, -5029, -5061, -5093, -5125, -5158, -5189,
/* frequency = 3600,... */
     -5221, -5253, -5284, -5316, -5347, -5378, -5409, -5440, -5471, -5501,
/* frequency = 3680,... */
     -5532, -5562, -5592, -5622, -5652, -5682, -5711, -5741, -5770, -5799,
/* frequency = 3760,... */
     -5828, -5857, -5886, -5915, -5943, -5971, -5999, -6027, -6055, -6083,
/* frequency = 3840,... */
     -6110, -6138, -6165, -6192, -6219, -6245, -6272, -6298, -6325, -6351,
/* frequency = 3920,... */
     -6377, -6402, -6428, -6453, -6479, -6504, -6529, -6554, -6578, -6603,
/* frequency = 4000,... */
     -6627, -6651, -6675, -6699, -6722, -6746, -6769, -6792, -6815, -6838,
/* frequency = 4080,... */
     -6861, -6883, -6905, -6927, -6949, -6971, -6992, -7014, -7035, -7056,
/* frequency = 4160,... */
     -7077, -7097, -7118, -7138, -7158, -7178, -7198, -7218, -7237, -7256,
/* frequency = 4240,... */
     -7275, -7294, -7313, -7331, -7349, -7367, -7385, -7403, -7421, -7438,
/* frequency = 4320,... */
     -7455, -7472, -7489, -7505, -7522, -7538, -7554, -7570, -7586, -7601,
/* frequency = 4400,... */
     -7616, -7631, -7646, -7661, -7675, -7690, -7704, -7718, -7731, -7745,
/* frequency = 4480,... */
     -7758, -7771, -7784, -7797, -7809, -7822, -7834, -7846, -7858, -7869,
/* frequency = 4560,... */
     -7880, -7892, -7903, -7913, -7924, -7934, -7944, -7954, -7964, -7973,
/* frequency = 4640,... */
     -7983, -7992, -8001, -8010, -8018, -8026, -8035, -8043, -8050, -8058,
/* frequency = 4720,... */
     -8065, -8072, -8079, -8086, -8092, -8099, -8105, -8110, -8116, -8122,
/* frequency = 4800,... */
     -8127, -8132, -8137, -8141, -8146, -8150, -8154, -8158, -8162, -8165,
/* frequency = 4880,... */
     -8168, -8171, -8174, -8177, -8179, -8181, -8183, -8185, -8186, -8188,
/* frequency = 4960,... */
     -8189, -8190, -8191, -8191, -8191, -8191
};

/**********************************************************************/
/*                                                                    */
/*  Radius table used by function setc()                              */
/*                                                                    */
/*  radius = 4096 * exp(-pi*b/10,000) where b = 0,8,16,...,1992       */
/*                                                                    */
/**********************************************************************/

const int16_t radius_table[] = {
/*  bandwidth = 0, ... */
  4096,  4085,  4075,  4065,  4055,  4044,  4034,  4024,  4014,  4004,
/*  bandwidth = 80, ... */
  3994,  3984,  3974,  3964,  3954,  3944,  3934,  3924,  3914,  3905,
/*  bandwidth = 160, ... */
  3895,  3885,  3875,  3865,  3856,  3846,  3836,  3827,  3817,  3808,
/*  bandwidth = 240, ... */
  3798,  3788,  3779,  3769,  3760,  3751,  3741,  3732,  3722,  3713,
/*  bandwidth = 320, ... */
  3704,  3694,  3685,  3676,  3667,  3657,  3648,  3639,  3630,  3621,
/*  bandwidth = 400, ... */
  3612,  3603,  3594,  3585,  3576,  3567,  3558,  3549,  3540,  3531,
/*  bandwidth = 480, ... */
  3522,  3513,  3504,  3496,  3487,  3478,  3469,  3461,  3452,  3443,
/*  bandwidth = 560, ... */
  3435,  3426,  3417,  3409,  3400,  3392,  3383,  3375,  3366,  3358,
/*  bandwidth = 640, ... */
  3349,  3341,  3333,  3324,  3316,  3308,  3299,  3291,  3283,  3275,
/*  bandwidth = 720, ... */
  3266,  3258,  3250,  3242,  3234,  3226,  3217,  3209,  3201,  3193,
/*  bandwidth = 800, ... */
  3185,  3177,  3169,  3161,  3153,  3145,  3138,  3130,  3122,  3114,
/*  bandwidth = 880, ... */
  3106,  3098,  3091,  3083,  3075,  3067,  3060,  3052,  3044,  3037,
/*  bandwidth = 960, ... */
  3029,  3021,  3014,  3006,  2999,  2991,  2984,  2976,  2969,  2961,
/*  bandwidth = 1040, ... */
  2954,  2946,  2939,  2932,  2924,  2917,  2910,  2902,  2895,  2888,
/*  bandwidth = 1120, ... */
  2881,  2873,  2866,  2859,  2852,  2845,  2837,  2830,  2823,  2816,
/*  bandwidth = 1200, ... */
  2809,  2802,  2795,  2788,  2781,  2774,  2767,  2760,  2753,  2746,
/*  bandwidth = 1280, ... */
  2739,  2732,  2726,  2719,  2712,  2705,  2698,  2692,  2685,  2678,
/*  bandwidth = 1360, ... */
  2671,  2665,  2658,  2651,  2645,  2638,  2631,  2625,  2618,  2612,
/*  bandwidth = 1440, ... */
  2605,  2598,  2592,  2585,  2579,  2572,  2566,  2560,  2553,  2547,
/*  bandwidth = 1520, ... */
  2540,  2534,  2528,  2521,  2515,  2509,  2502,  2496,  2490,  2483,
/*  bandwidth = 1600, ... */
  2477,  2471,  2465,  2459,  2452,  2446,  2440,  2434,  2428,  2422,
/*  bandwidth = 1680, ... */
  2416,  2410,  2404,  2398,  2392,  2386,  2380,  2374,  2368,  2362,
/*  bandwidth = 1760, ... */
  2356,  2350,  2344,  2338,  2332,  2326,  2321,  2315,  2309,  2303,
/*  bandwidth = 1840, ... */
  2297,  2292,  2286,  2280,  2274,  2269,  2263,  2257,  2252,  2246,
/*  bandwidth = 1920, ... */
  2240,  2235,  2229,  2223,  2218,  2212,  2207,  2201,  2196,  2190,
/*  bandwidth = 2000, ... */
  2185,  2179,  2174,  2168,  2163,  2157,  2152,  2147,  2141,  2136,
/*  bandwidth = 2080, ... */
  2130,  2125,  2120,  2114,  2109,  2104,  2099,  2093,  2088,  2083,
/*  bandwidth = 2160, ... */
  2078,  2072,  2067,  2062,  2057,  2052,  2046,  2041,  2036,  2031,
/*  bandwidth = 2240, ... */
  2026,  2021,  2016,  2011,  2006,  2001,  1996,  1991,  1986,  1981,
/*  bandwidth = 2320, ... */
  1976,  1971,  1966,  1961,  1956,  1951,  1946,  1941,  1936,  1931,
/*  bandwidth = 2400, ... */
  1927,  1922,  1917,  1912,  1907,  1903,  1898,  1893,  1888,  1884,
/*  bandwidth = 2480, ... */
  1879,  1874,  1869,  1865,  1860,  1855,  1851,  1846,  1841,  1837,
/*  bandwidth = 2560, ... */
  1832,  1828,  1823,  1818,  1814,  1809,  1805,  1800,  1796,  1791,
/*  bandwidth = 2640, ... */
  1787,  1782,  1778,  1773,  1769,  1764,  1760,  1755,  1751,  1747,
/*  bandwidth = 2720, ... */
  1742,  1738,  1734,  1729,  1725,  1721,  1716,  1712,  1708,  1703,
/*  bandwidth = 2800, ... */
  1699,  1695,  1691,  1686,  1682,  1678,  1674,  1669,  1665,  1661,
/*  bandwidth = 2880, ... */
  1657,  1653,  1649,  1644,  1640,  1636,  1632,  1628,  1624,  1620,
/*  bandwidth = 2960, ... */
  1616,  1612,  1608,  1604,  1600,  1596,  1592,  1588,  1584,  1580,
/*  bandwidth = 3040, ... */
  1576,  1572,  1568,  1564,  1560,  1556,  1552,  1548,  1544,  1540,
/*  bandwidth = 3120, ... */
  1537,  1533,  1529,  1525,  1521,  1517,  1513,  1510,  1506,  1502,
/*  bandwidth = 3200, ... */
  1498,  1495,  1491,  1487,  1483,  1480,  1476,  1472,  1469,  1465,
/*  bandwidth = 3280, ... */
  1461,  1457,  1454,  1450,  1447,  1443,  1439,  1436,  1432,  1428,
/*  bandwidth = 3360, ... */
  1425,  1421,  1418,  1414,  1411,  1407,  1404,  1400,  1397,  1393,
/*  bandwidth = 3440, ... */
  1389,  1386,  1383,  1379,  1376,  1372,  1369,  1365,  1362,  1358,
/*  bandwidth = 3520, ... */
  1355,  1352,  1348,  1345,  1341,  1338,  1335,  1331,  1328,  1325,
/*  bandwidth = 3600, ... */
  1321,  1318,  1315,  1311,  1308,  1305,  1302,  1298,  1295,  1292,
/*  bandwidth = 3680, ... */
  1289,  1285,  1282,  1279,  1276,  1272,  1269,  1266,  1263,  1260,
/*  bandwidth = 3760, ... */
  1257,  1253,  1250,  1247,  1244,  1241,  1238,  1235,  1232,  1228,
/*  bandwidth = 3840, ... */
  1225,  1222,  1219,  1216,  1213,  1210,  1207,  1204,  1201,  1198,
/*  bandwidth = 3920, ... */
  1195,  1192,  1189,  1186,  1183,  1180,  1177,  1174,  1171,  1168,
/*  bandwidth = 4000, ... */
  1165,  1162,  1159,  1157,  1154,  1151,  1148,  1145,  1142,  1139,
/*  bandwidth = 4080, ... */
  1136,  1133,  1131,  1128,  1125,  1122,  1119,  1117,  1114,  1111,
/*  bandwidth = 4160, ... */
  1108,  1105,  1103,  1100,  1097,  1094,  1092,  1089,  1086,  1083,
/*  bandwidth = 4240, ... */
  1081,  1078,  1075,  1072,  1070,  1067,  1064,  1062,  1059,  1056,
/*  bandwidth = 4320, ... */
  1054,  1051,  1048,  1046,  1043,  1041,  1038,  1035,  1033,  1030,
/*  bandwidth = 4400, ... */
  1028,  1025,  1022,  1020,  1017,  1015,  1012,  1010,  1007,  1005,
/*  bandwidth = 4480, ... */
  1002,  1000,  997,  995,  992,  990,  987,  985,  982,  980,
/*  bandwidth = 4560, ... */
  977,  975,  972,  970,  967,  965,  963,  960,  958,  955,
/*  bandwidth = 4640, ... */
  953,  951,  948,  946,  943,  941,  939,  936,  934,  932,
/*  bandwidth = 4720, ... */
  929,  927,  925,  922,  920,  918,  915,  913,  911,  908,
/*  bandwidth = 4800, ... */
  906,  904,  902,  899,  897,  895,  893,  890,  888,  886,
/*  bandwidth = 4880, ... */
  884,  881,  879,  877,  875,  873,  870,  868,  866,  864,
/*  bandwidth = 4960, ... */
  862,  860,  857,  855,  853
};
#endif
/* 23-Mar-95 CJL Add to exclude multiple includes. */

