/*
 * CDE - Common Desktop Environment
 *
 * Copyright (c) 1993-2012, The Open Group. All rights reserved.
 *
 * These libraries and programs are free software; you can
 * redistribute them and/or modify them under the terms of the GNU
 * Lesser General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 * These libraries and programs are distributed in the hope that
 * they will be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with these librararies and programs; if not, write
 * to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
 * Floor, Boston, MA 02110-1301 USA
 */
/*
 * $XConsortium: ifparser.h /main/4 1996/09/28 16:15:24 rws $
 *
 * Copyright 1992 Network Computing Devices, Inc.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Network Computing Devices may not be
 * used in advertising or publicity pertaining to distribution of the software
 * without specific, written prior permission.  Network Computing Devices makes
 * no representations about the suitability of this software for any purpose.
 * It is provided ``as is'' without express or implied warranty.
 * 
 * NETWORK COMPUTING DEVICES DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS,
 * IN NO EVENT SHALL NETWORK COMPUTING DEVICES BE LIABLE FOR ANY SPECIAL,
 * INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 * 
 * Author:  Jim Fulton
 *          Network Computing Devices, Inc.
 * 
 * Simple if statement processor
 *
 * This module can be used to evaluate string representations of C language
 * if constructs.  It accepts the following grammar:
 * 
 *     EXPRESSION	:=	VALUE
 * 			 |	VALUE  BINOP	EXPRESSION
 * 
 *     VALUE		:=	'('  EXPRESSION  ')'
 * 			 |	'!'  VALUE
 * 			 |	'-'  VALUE
 * 			 |	'defined'  '('  variable  ')'
 * 			 |	variable
 * 			 |	number
 * 
 *     BINOP		:=	'*'	|  '/'	|  '%'
 * 			 |	'+'	|  '-'
 * 			 |	'<<'	|  '>>'
 * 			 |	'<'	|  '>'	|  '<='  |  '>='
 * 			 |	'=='	|  '!='
 * 			 |	'&'	|  '|'
 * 			 |	'&&'	|  '||'
 * 
 * The normal C order of precidence is supported.
 * 
 * 
 * External Entry Points:
 * 
 *     ParseIfExpression		parse a string for #if
 */

#include <stdlib.h>
#include <stdio.h>

#define const /**/
typedef int Bool;
#define False 0
#define True 1

typedef struct _if_parser {
    struct {				/* functions */
	char *(*handle_error) (/* struct _if_parser *, const char *,
				 const char * */);
	long (*eval_variable) (/* struct _if_parser *, const char *, int */);
	int (*eval_defined) (/* struct _if_parser *, const char *, int */);
    } funcs;
    char *data;
} IfParser;

char *ParseIfExpression (
#ifdef __STDC__
    IfParser *, 
    const char *, 
    long *
#endif
);

