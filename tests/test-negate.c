/* Test decoded facility.

   Copyright (C) 2012 Free Software Foundation, Inc.

   This file is part of the Decimal Floating Point C Library.

   Author(s): Ryan S. Arnold <rsa@us.ibm.com>

   The Decimal Floating Point C Library is free software; you can
   redistribute it and/or modify it under the terms of the GNU Lesser
   General Public License version 2.1.

   The Decimal Floating Point C Library is distributed in the hope that
   it will be useful, but WITHOUT ANY WARRANTY; without even the implied
   warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
   the GNU Lesser General Public License version 2.1 for more details.

   You should have received a copy of the GNU Lesser General Public
   License version 2.1 along with the Decimal Floating Point C Library;
   if not, write to the Free Software Foundation, Inc., 59 Temple Place,
   Suite 330, Boston, MA 02111-1307 USA.

   Please see libdfp/COPYING.txt for more information.  */

#ifndef __STDC_WANT_DEC_FP__
#define __STDC_WANT_DEC_FP__
#endif

#include <float.h>
#include <stdio.h>
#include <wchar.h> /* This should pick up the libdfp wchar in dfp/wchar.h.  */

#define _WANT_DC 1
#include "scaffold.c" /* Pick up the _DC_P(x,y,...) macro.  */

/* Inspired by GLIBC stdio-common/tfformat.c  */
typedef struct{
  int line;
  _Decimal128 d;
  const char *expect;
} d128_type;

typedef struct{
  int line;
  _Decimal64 d;
  const char *expect;
} d64_type;

/*typedef union{
  _Decimal128 d;
  long i[4];
} d128_u;

typedef union{
  _Decimal64 d;
  long i[4];
} d64_u; */

#define DEC_INFINITY	__builtin_infd32()
#define DEC_NAN		(0.0DF * DEC_INFINITY)

int main (void)
{
  d64_type *d64ptr = NULL;
  d128_type *d128ptr = NULL;

  d64_type d64types[] =
    {
#ifdef _DPD_BACKEND
     {__LINE__, 1.2345678901E+24DD, "-0,000,012,345,678,901E+14"},
#else
      {__LINE__,1.00DD, "BID not supported."},
#endif
      {0,0,0 }
    };

  d128_type d128types[] =
    {
#ifdef _DPD_BACKEND
#else
      {__LINE__,1.00DL, "BID not supported."},
#endif
      {  0,0,0 }
    };

  for (d128ptr = d128types; d128ptr->line; d128ptr++)
    {
      /* Notice the '-' negate.  */
      _DC_P(__FILE__,d128ptr->line, d128ptr->expect,-d128ptr->d);
    }

  for (d64ptr = d64types; d64ptr->line; d64ptr++)
    {
     /* Notice the '-' negate.  */
      _DC_P(__FILE__,d64ptr->line, d64ptr->expect,-d64ptr->d);
    }

  _REPORT();

  /* fail comes from scaffold.c  */
  return fail;
}