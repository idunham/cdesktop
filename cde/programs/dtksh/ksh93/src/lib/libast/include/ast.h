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
/* $XConsortium: ast.h /main/3 1995/11/01 17:34:52 rswiston $ */
/***************************************************************
*                                                              *
*                      AT&T - PROPRIETARY                      *
*                                                              *
*         THIS IS PROPRIETARY SOURCE CODE LICENSED BY          *
*                          AT&T CORP.                          *
*                                                              *
*                Copyright (c) 1995 AT&T Corp.                 *
*                     All Rights Reserved                      *
*                                                              *
*           This software is licensed by AT&T Corp.            *
*       under the terms and conditions of the license in       *
*       http://www.research.att.com/orgs/ssr/book/reuse        *
*                                                              *
*               This software was created by the               *
*           Software Engineering Research Department           *
*                    AT&T Bell Laboratories                    *
*                                                              *
*               For further information contact                *
*                     gsf@research.att.com                     *
*                                                              *
***************************************************************/

/* : : generated by proto : : */
                  
/*
 * Advanced Software Technology Library
 * AT&T Bell Laboratories
 *
 * std + posix + ast
 */

#ifndef _AST_H
#if !defined(__PROTO__)
#if defined(__STDC__) || defined(__cplusplus) || defined(_proto) || defined(c_plusplus)
#if defined(__cplusplus)
#define __MANGLE__	"C"
#else
#define __MANGLE__
#endif
#define __STDARG__
#define __PROTO__(x)	x
#define __OTORP__(x)
#define __PARAM__(n,o)	n
#if !defined(__STDC__) && !defined(__cplusplus)
#if !defined(c_plusplus)
#define const
#endif
#define signed
#define void		int
#define volatile
#define __V_		char
#else
#define __V_		void
#endif
#else
#define __PROTO__(x)	()
#define __OTORP__(x)	x
#define __PARAM__(n,o)	o
#define __MANGLE__
#define __V_		char
#define const
#define signed
#define void		int
#define volatile
#endif
#if defined(__cplusplus) || defined(c_plusplus)
#define __VARARG__	...
#else
#define __VARARG__
#endif
#if defined(__STDARG__)
#define __VA_START__(p,a)	va_start(p,a)
#else
#define __VA_START__(p,a)	va_start(p)
#endif
#endif

#define _AST_H

#ifndef _AST_STD_H
#include <ast_std.h>
#endif

#ifndef _SFIO_H
#include <sfio.h>
#endif

#ifndef	ast
#define ast	_ast_info
#endif

#ifndef PATH_MAX
#define PATH_MAX	1024
#endif

/*
 * workaround botched headers that assume <stdio.h>
 */

#if defined(linux)
#ifndef __FILE
#define __FILE	FILE
#endif
#endif

#if !defined(CSRG_BASED)
#ifndef FILE
#define FILE	Sfio_t
#endif
#endif

/*
 * exit() support -- this matches shell exit codes
 */

#define EXIT_BITS	8			/* # exit status bits	*/

#define EXIT_USAGE	2			/* usage exit code	*/
#define EXIT_NOTFOUND	((1<<(EXIT_BITS-1))-1)	/* command not found	*/
#define EXIT_NOEXEC	((1<<(EXIT_BITS-1))-2)	/* other exec error	*/

#define EXIT_CODE(x)	((x)&((1<<EXIT_BITS)-1))
#define EXIT_CORE(x)	(EXIT_CODE(x)|(1<<EXIT_BITS)|(1<<(EXIT_BITS-1)))
#define EXIT_TERM(x)	(EXIT_CODE(x)|(1<<EXIT_BITS))

/*
 * NOTE: for compatibility the following work for EXIT_BITS={7,8}
 */

#define EXITED_CORE(x)	(((x)&((1<<EXIT_BITS)|(1<<(EXIT_BITS-1))))==((1<<EXIT_BITS)|(1<<(EXIT_BITS-1)))||((x)&((1<<(EXIT_BITS-1))|(1<<(EXIT_BITS-2))))==((1<<(EXIT_BITS-1))|(1<<(EXIT_BITS-2))))
#define EXITED_TERM(x)	((x)&((1<<EXIT_BITS)|(1<<(EXIT_BITS-1))))

/*
 * pathcanon() flags
 */

#define PATH_PHYSICAL	01
#define PATH_DOTDOT	02
#define PATH_EXISTS	04

/*
 * pathaccess() flags
 */

#define PATH_READ	004
#define PATH_WRITE	002
#define PATH_EXECUTE	001
#define	PATH_REGULAR	010
#define PATH_ABSOLUTE	020

/*
 * pathcheck() info
 */

typedef struct
{
	unsigned long	date;
	char*		feature;
	char*		host;
	char*		user;
} Pathcheck_t;

/*
 * strmatch() flags
 */

#define STR_MAXIMAL	01
#define STR_LEFT	02
#define STR_RIGHT	04

/*
 * common macros
 */

#define elementsof(x)	(sizeof(x)/sizeof(x[0]))
#define newof(p,t,n,x)	((p)?(t*)realloc((char*)(p),sizeof(t)*(n)+(x)):(t*)calloc(1,sizeof(t)*(n)+(x)))
#define oldof(p,t,n,x)	((p)?(t*)realloc((char*)(p),sizeof(t)*(n)+(x)):(t*)malloc(sizeof(t)*(n)+(x)))
#define roundof(x,y)	(((x)+(y)-1)&~((y)-1))
#define streq(a,b)	(*(a)==*(b)&&!strcmp(a,b))
#define strneq(a,b,n)	(*(a)==*(b)&&!strncmp(a,b,n))

#if defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#define NiL		0
#define NoP(x)		(void)(x)
#else
#define NiL		((char*)0)
#define NoP(x)		(&x,1)
#endif

#if !defined(NoN)
#if defined(__STDC__) || defined(__STDPP__)
#define NoN(x)		int _STUB_ ## x;
#else
#define NoN(x)		int _STUB_/**/x;
#endif
#if !defined(_STUB_)
#define _STUB_
#endif
#endif

#define NOT_USED(x)	NoP(x)

typedef int (*Ast_confdisc_t) __PROTO__((const char*, const char*, const char*));

extern __MANGLE__ char*		astconf __PROTO__((const char*, const char*, const char*));
extern __MANGLE__ Ast_confdisc_t	astconfdisc __PROTO__((Ast_confdisc_t));
extern __MANGLE__ void		astconflist __PROTO__((Sfio_t*, const char*, int));
extern __MANGLE__ off_t		astcopy __PROTO__((int, int, off_t));
extern __MANGLE__ int		astquery __PROTO__((int, const char*, ...));
extern __MANGLE__ void		astwinsize __PROTO__((int, int*, int*));

extern __MANGLE__ int		chresc __PROTO__((const char*, char**));
extern __MANGLE__ int		chrtoi __PROTO__((const char*));
extern __MANGLE__ char*		fmtbase __PROTO__((long, int, int));
extern __MANGLE__ char*		fmtdev __PROTO__((struct stat*));
extern __MANGLE__ char*		fmtelapsed __PROTO__((unsigned long, int));
extern __MANGLE__ char*		fmterror __PROTO__((int));
extern __MANGLE__ char*		fmtesc __PROTO__((const char*));
extern __MANGLE__ char*		fmtfs __PROTO__((struct stat*));
extern __MANGLE__ char*		fmtgid __PROTO__((int));
extern __MANGLE__ char*		fmtmatch __PROTO__((const char*));
extern __MANGLE__ char*		fmtmode __PROTO__((int, int));
extern __MANGLE__ char*		fmtperm __PROTO__((int));
extern __MANGLE__ char*		fmtre __PROTO__((const char*));
extern __MANGLE__ char*		fmtsignal __PROTO__((int));
extern __MANGLE__ char*		fmttime __PROTO__((const char*, time_t));
extern __MANGLE__ char*		fmtuid __PROTO__((int));
extern __MANGLE__ void		mematoe __PROTO__((__V_*, const __V_*, size_t));
extern __MANGLE__ __V_*		memdup __PROTO__((const __V_*, size_t));
extern __MANGLE__ void		memetoa __PROTO__((__V_*, const __V_*, size_t));
extern __MANGLE__ char*		pathaccess __PROTO__((char*, const char*, const char*, const char*, int));
extern __MANGLE__ char*		pathbin __PROTO__((void));
extern __MANGLE__ char*		pathcanon __PROTO__((char*, int));
extern __MANGLE__ char*		pathcat __PROTO__((char*, const char*, int, const char*, const char*));
extern __MANGLE__ int		pathcd __PROTO__((const char*, const char*));
extern __MANGLE__ int		pathcheck __PROTO__((const char*, const char*, Pathcheck_t*));
extern __MANGLE__ int		pathgetlink __PROTO__((const char*, char*, int));
extern __MANGLE__ char*		pathkey __PROTO__((char*, char*, const char*, const char*));
extern __MANGLE__ char*		pathpath __PROTO__((char*, const char*, const char*, int));
extern __MANGLE__ char*		pathprobe __PROTO__((char*, char*, const char*, const char*, const char*, int));
extern __MANGLE__ char*		pathrepl __PROTO__((char*, const char*, const char*));
extern __MANGLE__ char*		pathtemp __PROTO__((char*, const char*, const char*));
extern __MANGLE__ int		pathsetlink __PROTO__((const char*, const char*));
extern __MANGLE__ char*		pathshell __PROTO__((void));
extern __MANGLE__ char*		setenviron __PROTO__((const char*));
extern __MANGLE__ int		sigcritical __PROTO__((int));
extern __MANGLE__ char*		strcopy __PROTO__((char*, const char*));
extern __MANGLE__ char*		strdup __PROTO__((const char*));
extern __MANGLE__ unsigned long	strelapsed __PROTO__((const char*, char**, int));
extern __MANGLE__ char*		strerror __PROTO__((int));
extern __MANGLE__ int		stresc __PROTO__((char*));
extern __MANGLE__ long		streval __PROTO__((const char*, char**, long(*)(const char*, char**)));
extern __MANGLE__ long		strexpr __PROTO__((const char*, char**, long(*)(const char*, char**, __V_*), __V_*));
extern __MANGLE__ int		strgid __PROTO__((const char*));
extern __MANGLE__ int		strgrpmatch __PROTO__((const char*, const char*, int*, int, int));
extern __MANGLE__ __V_*		strlook __PROTO__((const __V_*, int, const char*));
extern __MANGLE__ int		strmatch __PROTO__((const char*, const char*));
extern __MANGLE__ int		strmode __PROTO__((const char*));
extern __MANGLE__ int		stropt __PROTO__((const char*, const __V_*, int, int(*)(__V_*, const __V_*, int, const char*), __V_*));
extern __MANGLE__ int		strperm __PROTO__((const char*, char**, int));
extern __MANGLE__ char*		strsignal __PROTO__((int));
extern __MANGLE__ void		strsort __PROTO__((char**, int, int(*)(const char*, const char*)));
extern __MANGLE__ char*		strsubmatch __PROTO__((const char*, const char*, int));
extern __MANGLE__ char*		strtape __PROTO__((const char*, char**));
extern __MANGLE__ long		strton __PROTO__((const char*, char**, char*, int));
extern __MANGLE__ int		struid __PROTO__((const char*));

/*
 * C library global data symbols not prototyped by <unistd.h>
 */

#ifndef environ
#if _DLL_INDIRECT_DATA && _DLL
#define	environ		(*_ast_getdll()->_ast_environ)
#else
extern __MANGLE__ char**		environ;
#endif
#endif

#endif
