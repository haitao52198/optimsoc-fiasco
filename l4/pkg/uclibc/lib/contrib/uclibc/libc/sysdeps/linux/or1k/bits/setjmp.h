/* Copyright (C) 1997, 1998, 2000 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.  */

/* Define the machine-dependent type `jmp_buf'.  or1k version.  */

#ifndef _BITS_SETJMP_H
#define _BITS_SETJMP_H  1

#ifndef _SETJMP_H
# error "Never include <bits/setjmp.h> directly; use <setjmp.h> instead."
#endif

#ifndef	_ASM
typedef long int __jmp_buf[32];
#endif

#endif
