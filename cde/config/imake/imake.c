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
/* $TOG: imake.c /main/104 1998/03/24 12:45:15 kaleb $ */

/***************************************************************************
 *                                                                         *
 *                                Porting Note                             *
 *                                                                         *
 * Add the value of BOOTSTRAPCFLAGS to the cpp_argv table so that it will  *
 * be passed to the template file.                                         *
 *                                                                         *
 ***************************************************************************/

/*
 * 
Copyright (c) 1985, 1986, 1987, 1998 The Open Group  

All Rights Reserved.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.
 * 
 * Original Author:
 *	Todd Brunhoff
 *	Tektronix, inc.
 *	While a guest engineer at Project Athena, MIT
 *
 * imake: the include-make program.
 *
 * Usage: imake [-Idir] [-Ddefine] [-T template] [-f imakefile ] [-C Imakefile.c ] [-s] [-e] [-v] [make flags]
 *
 * Imake takes a template file (Imake.tmpl) and a prototype (Imakefile)
 * and runs cpp on them producing a Makefile.  It then optionally runs make
 * on the Makefile.
 * Options:
 *		-D	define.  Same as cpp -D argument.
 *		-I	Include directory.  Same as cpp -I argument.
 *		-T	template.  Designate a template other
 *			than Imake.tmpl
 *		-f	specify the Imakefile file
 *		-C	specify the name to use instead of Imakefile.c
 *		-s[F]	show.  Show the produced makefile on the standard
 *			output.  Make is not run is this case.  If a file
 *			argument is provided, the output is placed there.
 *              -e[F]   execute instead of show; optionally name Makefile F
 *		-v	verbose.  Show the make command line executed.
 *
 * Environment variables:
 *		
 *		IMAKEINCLUDE	Include directory to use in addition to "."
 *		IMAKECPP	Cpp to use instead of /lib/cpp
 *		IMAKEMAKE	make program to use other than what is
 *				found by searching the $PATH variable.
 * Other features:
 *	imake reads the entire cpp output into memory and then scans it
 *	for occurences of "@@".  If it encounters them, it replaces it with
 *	a newline.  It also trims any trailing white space on output lines
 *	(because make gets upset at them).  This helps when cpp expands
 *	multi-line macros but you want them to appear on multiple lines.
 *	It also changes occurences of "XCOMM" to "#", to avoid problems
 *	with treating commands as invalid preprocessor commands.
 *
 *	The macros MAKEFILE and MAKE are provided as macros
 *	to make.  MAKEFILE is set to imake's makefile (not the constructed,
 *	preprocessed one) and MAKE is set to argv[0], i.e. the name of
 *	the imake program.
 *
 * Theory of operation:
 *   1. Determine the name of the imakefile from the command line (-f)
 *	or from the content of the current directory (Imakefile or imakefile).
 *	Call this <imakefile>.  This gets added to the arguments for
 *	make as MAKEFILE=<imakefile>.
 *   2. Determine the name of the template from the command line (-T)
 *	or the default, Imake.tmpl.  Call this <template>
 *   3. Determine the name of the imakeCfile from the command line (-C)
 *	or the default, Imakefile.c.  Call this <imakeCfile>
 *   4. Store lines of input into <imakeCfile>:
 *	- A c-style comment header (see ImakefileCHeader below), used
 *	  to recognize temporary files generated by imake.
 *	- If DEFAULT_OS_NAME is defined, format the utsname struct and
 *	  call the result <defaultOsName>.  Add:
 *		#define DefaultOSName <defaultOsName>
 *	- If DEFAULT_OS_MAJOR_REV is defined, format the utsname struct
 *	  and call the result <defaultOsMajorVersion>.  Add:
 *		#define DefaultOSMajorVersion <defaultOsMajorVersion>
 *	- If DEFAULT_OS_MINOR_REV is defined, format the utsname struct
 *	  and call the result <defaultOsMinorVersion>.  Add:
 *		#define DefaultOSMinorVersion <defaultOsMinorVersion>
 *	- If DEFAULT_OS_TEENY_REV is defined, format the utsname struct
 *	  and call the result <defaultOsTeenyVersion>.  Add:
 *		#define DefaultOSTeenyVersion <defaultOsTeenyVersion>
 *	- If the file "localdefines" is readable in the current
 *	  directory, print a warning message to stderr and add: 
 *		#define IMAKE_LOCAL_DEFINES	"localdefines"
 *		#include IMAKE_LOCAL_DEFINES
 *	- If the file "admindefines" is readable in the current
 *	  directory, print a warning message to stderr and add: 
 *		#define IMAKE_ADMIN_DEFINES	"admindefines"
 *		#include IMAKE_ADMIN_DEFINES
 *	- The following lines:
 *		#define INCLUDE_IMAKEFILE	< <imakefile> >
 *		#define IMAKE_TEMPLATE		" <template> "
 *		#include IMAKE_TEMPLATE
 *	- If the file "adminmacros" is readable in the current
 *	  directory, print a warning message to stderr and add: 
 *		#define IMAKE_ADMIN_MACROS	"adminmacros"
 *		#include IMAKE_ADMIN_MACROS
 *	- If the file "localmacros" is readable in the current
 *	  directory, print a warning message to stderr and add: 
 *		#define IMAKE_LOCAL_MACROS	"localmacros"
 *		#include IMAKE_LOCAL_MACROS
 *   5. Start up cpp and provide it with this file.
 *	Note that the define for INCLUDE_IMAKEFILE is intended for
 *	use in the template file.  This implies that the imake is
 *	useless unless the template file contains at least the line
 *		#include INCLUDE_IMAKEFILE
 *   6. Gather the output from cpp, and clean it up, expanding @@ to
 *	newlines, stripping trailing white space, cpp control lines,
 *	and extra blank lines, and changing XCOMM to #.  This cleaned
 *	output is placed in a new file, default "Makefile", but can
 *	be specified with -s or -e options.
 *   7. Optionally start up make on the resulting file.
 *
 * The design of the template makefile should therefore be:
 *	<set global macros like CFLAGS, etc.>
 *	<include machine dependent additions>
 *	#include INCLUDE_IMAKEFILE
 *	<add any global targets like 'clean' and long dependencies>
 */
#include <stdio.h>
#include <ctype.h>
#include "Xosdefs.h"
#ifdef WIN32
# include "Xw32defs.h"
#endif
#ifndef X_NOT_POSIX
# ifndef _POSIX_SOURCE
#  define _POSIX_SOURCE
# endif
#endif
#include <sys/types.h>
#include <fcntl.h>
#ifdef X_NOT_POSIX
# ifndef WIN32
#  include <sys/file.h>
# endif
#else
# include <unistd.h>
#endif
#if defined(X_NOT_POSIX) || defined(_POSIX_SOURCE)
# include <signal.h>
#else
# define _POSIX_SOURCE
# include <signal.h>
# undef _POSIX_SOURCE
#endif
#include <sys/stat.h>
#ifndef X_NOT_POSIX
# ifdef _POSIX_SOURCE
#  include <sys/wait.h>
# else
#  define _POSIX_SOURCE
#  include <sys/wait.h>
#  undef _POSIX_SOURCE
# endif
# define waitCode(w)	WEXITSTATUS(w)
# define waitSig(w)	WTERMSIG(w)
typedef int		waitType;
#else /* X_NOT_POSIX */
# ifdef SYSV
#  define waitCode(w)	(((w) >> 8) & 0x7f)
#  define waitSig(w)	((w) & 0xff)
typedef int		waitType;
# else /* SYSV */
#  ifdef WIN32
#   include <process.h>
typedef int		waitType;
#  else
#   include <sys/wait.h>
#   define waitCode(w)	((w).w_T.w_Retcode)
#   define waitSig(w)	((w).w_T.w_Termsig)
typedef union wait	waitType;
#  endif
# endif
# ifndef WIFSIGNALED
#  define WIFSIGNALED(w) waitSig(w)
# endif
# ifndef WIFEXITED
#  define WIFEXITED(w) waitCode(w)
# endif
#endif /* X_NOT_POSIX */
#ifndef X_NOT_STDC_ENV
# include <stdlib.h>
#else
char *malloc(), *realloc();
void exit();
#endif
#if defined(macII) && !defined(__STDC__)  /* stdlib.h fails to define these */
char *malloc(), *realloc();
#endif /* macII */
#ifdef X_NOT_STDC_ENV
extern char	*getenv();
#endif
#include <errno.h>
#ifdef X_NOT_STDC_ENV
extern int	errno;
#endif
#ifndef WIN32
#include <sys/utsname.h>
#else
#include <windows.h>
#endif
#ifndef SYS_NMLN
# ifdef _SYS_NMLN
#  define SYS_NMLN _SYS_NMLN
# else
#  define SYS_NMLN 257
# endif
#endif
#ifdef linux
#include <limits.h>
#endif
/* 
 * is strstr() in <strings.h> on X_NOT_STDC_ENV? 
 * are there any X_NOT_STDC_ENV machines left in the world?
 */
#include <string.h>
#include <stdarg.h>
#include "imakemdep.h"

/*
 * This define of strerror is copied from (and should be identical to)
 * Xos.h, which we don't want to include here for bootstrapping reasons.
 */
#if defined(X_NOT_STDC_ENV) || (defined(sun) && !defined(SVR4)) || defined(macII)
# ifndef strerror
extern char *sys_errlist[];
extern int sys_nerr;
#  define strerror(n) \
    (((n) >= 0 && (n) < sys_nerr) ? sys_errlist[n] : "unknown error")
# endif
#endif

#define	TRUE		1
#define	FALSE		0

#ifdef FIXUP_CPP_WHITESPACE
static int	InRule = FALSE;
# ifdef INLINE_SYNTAX
static int	InInline = 0;
# endif
#endif
#ifdef MAGIC_MAKE_VARS
static int xvariable = 0;
static int xvariables[10];
#endif

/*
 * Some versions of cpp reduce all tabs in macro expansion to a single
 * space.  In addition, the escaped newline may be replaced with a
 * space instead of being deleted.  Blech.
 */
#ifdef FIXUP_CPP_WHITESPACE
static void KludgeOutputLine(char **pline);
static void KludgeResetRule(void);
#else
# define KludgeOutputLine(arg)
# define KludgeResetRule()
#endif

typedef	unsigned char	boolean;

#ifdef USE_CC_E
# ifndef DEFAULT_CC
#  define DEFAULT_CC "cc"
# endif
#else
# ifndef DEFAULT_CPP
#  ifdef CPP_PROGRAM
#   define DEFAULT_CPP CPP_PROGRAM
#  else
#   define DEFAULT_CPP "/lib/cpp"
#  endif
# endif
#endif

static char *cpp = NULL;

static char *tmpMakefile = "/tmp/Imf.XXXXXX";
static char	*tmpImakefile    = "/tmp/IIf.XXXXXX";
static char	*make_argv[ ARGUMENTS ] = {
#ifdef WIN32
    "nmake"
#else
    "make"
#endif
};

static int	make_argindex;
static int	cpp_argindex;
static char	*Imakefile = NULL;
static char	*Makefile = "Makefile";
static char	*Template = "Imake.tmpl";
static char	*ImakefileC = "Imakefile.c";
static boolean haveImakefileC = FALSE;
static char	*cleanedImakefile = NULL;
static char	*program;
static boolean	verbose = FALSE;
static boolean	show = TRUE;

static char	*FindImakefile(char *);
static char	*ReadLine(FILE *, const char *);
static char	*CleanCppInput(char *);
static char	*Strdup(const char *);
static char	*Emalloc(int);
static void	LogFatal(const char *, ...);
static void	LogMsg(const char *, ...);
static void	Log(const char *, va_list);

static void	showit(FILE *);
static void	wrapup(void);
static
#ifdef SIGNALRETURNSINT
int
#else
void
#endif
catch(int);
static void	init(void);
static void	AddMakeArg(char *);
static void	AddCppArg(char *);
static void	SetOpts(int, char **);
static void	showargs(char **);
static void	CheckImakefileC(const char *);
static boolean	optional_include(FILE *, const char *, const char *);
static void	doit(FILE *, const char *, char **);
#if (defined(DEFAULT_OS_NAME) || defined(DEFAULT_OS_MAJOR_REV) || \
     defined(DEFAULT_OS_MINOR_REV) || defined(DEFAULT_OS_TEENY_REV))
static void	parse_utsname(struct utsname *, const char *, char *, const char *);
#endif
#if (defined(DEFAULT_OS_MAJOR_REV) || defined(DEFAULT_OS_MINOR_REV) || defined(DEFAULT_OS_TEENY_REV))
static const char	*trim_version(const char *);
#endif
#ifdef linux
static void	get_distrib(FILE *);
static void	get_libc_version(FILE *);
static void	get_ld_version(FILE *);
#endif
#if defined(sun) && defined(__SVR4)
static void	get_sun_compiler_versions(FILE *);
#endif
static void	get_gcc_incdir(FILE *);
static boolean	define_os_defaults(FILE *);
static void	cppit(const char *i, const char *, const char *, FILE *, const char *);
static void	makeit(void);
static void	CleanCppOutput(FILE *, const char *);
static boolean	isempty(char *);
static void	writetmpfile(FILE *, const char *, int, const char *);

int
main(int argc, char *argv[])
{
	FILE	*tmpfd;
	char	makeMacro[ BUFSIZ ];
	char	makefileMacro[ BUFSIZ ];

	program = argv[0];
	init();
	SetOpts(argc, argv);

	Imakefile = FindImakefile(Imakefile);
	CheckImakefileC(ImakefileC);
	if (Makefile)
		tmpMakefile = Makefile;
	else {
		tmpMakefile = Strdup(tmpMakefile);
		mkstemp(tmpMakefile);
	}
	AddMakeArg("-f");
	AddMakeArg( tmpMakefile );
	sprintf(makeMacro, "MAKE=%s", program);
	AddMakeArg( makeMacro );
	sprintf(makefileMacro, "MAKEFILE=%s", Imakefile);
	AddMakeArg( makefileMacro );

	if ((tmpfd = fopen(tmpMakefile, "w+")) == NULL)
		LogFatal("Cannot create temporary file %s.", tmpMakefile);

	cleanedImakefile = CleanCppInput(Imakefile);
	cppit(cleanedImakefile, Template, ImakefileC, tmpfd, tmpMakefile);

	if (show) {
		if (Makefile == NULL)
			showit(tmpfd);
	} else
		makeit();
	wrapup();
	return 0;
}

static void
showit(FILE *fd)
{
	char	buf[ BUFSIZ ];
	int	red;

	fseek(fd, 0, 0);
	while ((red = fread(buf, 1, BUFSIZ, fd)) > 0)
		writetmpfile(stdout, buf, red, "stdout");
	if (red < 0)
	    LogFatal("Cannot read %s.", tmpMakefile);
}

static void
wrapup(void)
{
	if (tmpMakefile != Makefile)
		unlink(tmpMakefile);
	if (cleanedImakefile && cleanedImakefile != Imakefile)
		unlink(cleanedImakefile);
	if (haveImakefileC)
		unlink(ImakefileC);
}

static
#ifdef SIGNALRETURNSINT
int
#else
void
#endif
catch(int sig)
{
	errno = 0;
	LogFatal("Signal %d.", sig);
}

/*
 * Initialize some variables.
 */
static void
init(void)
{
	char	*p;

	make_argindex=0;
	while (make_argv[ make_argindex ] != NULL)
		make_argindex++;
	cpp_argindex = 0;
	while (cpp_argv[ cpp_argindex ] != NULL)
		cpp_argindex++;

	/*
	 * See if the standard include directory is different than
	 * the default.  Or if cpp is not the default.  Or if the make
	 * found by the PATH variable is not the default.
	 */
	if ((p = getenv("IMAKEINCLUDE"))) {
		if (*p != '-' || *(p+1) != 'I')
			LogFatal("Environment var IMAKEINCLUDE %s must begin with -I");
		AddCppArg(p);
		for (; *p; p++)
			if (*p == ' ') {
				*p++ = '\0';
				AddCppArg(p);
			}
	}
	if ((p = getenv("IMAKECPP")))
		cpp = p;
	if ((p = getenv("IMAKEMAKE")))
		make_argv[0] = p;

	if (signal(SIGINT, SIG_IGN) != SIG_IGN)
		signal(SIGINT, catch);
}

static void
AddMakeArg(char *arg)
{
	errno = 0;
	if (make_argindex >= ARGUMENTS-1)
		LogFatal("Out of internal storage.");
	make_argv[ make_argindex++ ] = arg;
	make_argv[ make_argindex ] = NULL;
}

static void
AddCppArg(char *arg)
{
	errno = 0;
	if (cpp_argindex >= ARGUMENTS-1)
		LogFatal("Out of internal storage.");
	cpp_argv[ cpp_argindex++ ] = arg;
	cpp_argv[ cpp_argindex ] = NULL;
}

static void
SetOpts(int argc, char **argv)
{
	errno = 0;
	/*
	 * Now gather the arguments for make
	 */
	for(argc--, argv++; argc; argc--, argv++) {
	    /*
	     * We intercept these flags.
	     */
	    if (argv[0][0] == '-') {
		if (argv[0][1] == 'D') {
		    AddCppArg(argv[0]);
		} else if (argv[0][1] == 'I') {
		    AddCppArg(argv[0]);
		} else if (argv[0][1] == 'f') {
		    if (argv[0][2])
			Imakefile = argv[0]+2;
		    else {
			argc--, argv++;
			if (! argc)
			    LogFatal("No description arg after -f flag");
			Imakefile = argv[0];
		    }
		} else if (argv[0][1] == 's') {
		    if (argv[0][2])
			Makefile = ((argv[0][2] == '-') && !argv[0][3]) ?
			    NULL : argv[0]+2;
		    else {
			argc--, argv++;
			if (!argc)
			    LogFatal("No description arg after -s flag");
			Makefile = ((argv[0][0] == '-') && !argv[0][1]) ?
			    NULL : argv[0];
		    }
		    show = TRUE;
		} else if (argv[0][1] == 'e') {
		   Makefile = (argv[0][2] ? argv[0]+2 : NULL);
		   show = FALSE;
		} else if (argv[0][1] == 'T') {
		    if (argv[0][2])
			Template = argv[0]+2;
		    else {
			argc--, argv++;
			if (! argc)
			    LogFatal("No description arg after -T flag");
			Template = argv[0];
		    }
		} else if (argv[0][1] == 'C') {
		    if (argv[0][2])
			ImakefileC = argv[0]+2;
		    else {
			argc--, argv++;
			if (! argc)
			    LogFatal("No imakeCfile arg after -C flag");
			ImakefileC = argv[0];
		    }
		} else if (argv[0][1] == 'v') {
		    verbose = TRUE;
		} else
		    AddMakeArg(argv[0]);
	    } else
		AddMakeArg(argv[0]);
	}
#ifdef USE_CC_E
	if (!cpp)
	{
		AddCppArg("-E");
		cpp = DEFAULT_CC;
	}
#else
	if (!cpp)
		cpp = DEFAULT_CPP;
#endif
	cpp_argv[0] = cpp;
	AddCppArg(ImakefileC);
}

static char *
FindImakefile(char *Imakefile)
{
	if (Imakefile) {
		if (access(Imakefile, R_OK) < 0)
			LogFatal("Cannot find %s.", Imakefile);
	} else {
		if (access("Imakefile", R_OK) < 0)
			if (access("imakefile", R_OK) < 0)
				LogFatal("No description file.");
			else
				Imakefile = "imakefile";
		else
			Imakefile = "Imakefile";
	}
	return(Imakefile);
}

static void
LogFatal(const char *s, ...)
{
    static boolean entered = FALSE;
    va_list args;

    if (entered)
        return;

    entered = TRUE;

    va_start(args, s);
    Log(s, args);
    va_end(args);

    fprintf(stderr, "Stop.\n");

    wrapup();

    exit(1);
}

static void
LogMsg(const char *s, ...)
{
    va_list args;

    va_start(args, s);
    Log(s, args);
    va_end(args);
}

static void
Log(const char *s, va_list args)
{
    int error_number = errno;

    if (error_number) {
        fprintf(stderr, "%s: ", program);
        fprintf(stderr, "%s\n", strerror(error_number));
    }
    fprintf(stderr, "%s: ", program);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
}

static void
showargs(char **argv)
{
	for (; *argv; argv++)
		fprintf(stderr, "%s ", *argv);
	fprintf(stderr, "\n");
}

#define ImakefileCHeader "/* imake - temporary file */"

static void
CheckImakefileC(const char *masterc)
{
	char mkcbuf[1024];
	FILE *inFile;

	if (access(masterc, F_OK) == 0) {
		inFile = fopen(masterc, "r");
		if (inFile == NULL)
			LogFatal("Refuse to overwrite: %s", masterc);
		if ((fgets(mkcbuf, sizeof(mkcbuf), inFile) &&
		     strncmp(mkcbuf, ImakefileCHeader, 
			     sizeof(ImakefileCHeader)-1)))
		{
			fclose(inFile);
			LogFatal("Refuse to overwrite: %s", masterc);
		}
		fclose(inFile);
	}
}

#define LocalDefineFmt	"#define %s \"%s\"\n"
#define IncludeFmt	"#include %s\n"
#define ImakeDefSym	"INCLUDE_IMAKEFILE"
#define ImakeTmplSym	"IMAKE_TEMPLATE"
#define OverrideWarning	"Warning: local file \"%s\" overrides global macros."

static boolean
optional_include(FILE *inFile, const char *defsym, const char *fname)
{
	errno = 0;
	if (access(fname, R_OK) == 0) {
		LogMsg(OverrideWarning, fname);
		return (fprintf(inFile, LocalDefineFmt, defsym, fname) < 0 ||
			fprintf(inFile, IncludeFmt, defsym) < 0);
	}
	return FALSE;
}

static void
doit(FILE *outfd, const char *cmd, char **argv)
{
	int	pid;
	waitType	status;

	/*
	 * Fork and exec the command.
	 */
#ifdef WIN32
	if (outfd)
		dup2(fileno(outfd), 1);
	status = _spawnvp(_P_WAIT, cmd, argv);
	if (status < 0)
		LogFatal("Cannot spawn %s.", cmd);
	if (status > 0)
		LogFatal("Exit code %d.", status);
#else
	pid = fork();
	if (pid < 0)
		LogFatal("Cannot fork.");
	if (pid) {	/* parent... simply wait */
		while (wait(&status) > 0) {
			errno = 0;
			if (WIFSIGNALED(status))
				LogFatal("Signal %d.", waitSig(status));
			if (WIFEXITED(status) && waitCode(status))
				LogFatal("Exit code %d.", waitCode(status));
		}
	}
	else {	/* child... dup and exec cmd */
		if (verbose)
			showargs(argv);
		if (outfd)
			dup2(fileno(outfd), 1);
		execvp(cmd, argv);
		LogFatal("Cannot exec %s.", cmd);
	}
#endif
}

#ifndef WIN32

#if (defined(DEFAULT_OS_NAME) || defined(DEFAULT_OS_MAJOR_REV) || \
     defined(DEFAULT_OS_MINOR_REV) || defined(DEFAULT_OS_TEENY_REV))
static void
parse_utsname(struct utsname *name, const char *fmt, char *result, const char *msg)
{
  char buf[SYS_NMLN * 5 + 1];
  char *ptr = buf;
  int arg;

  /* Assemble all the pieces into a buffer. */
  for (arg = 0; fmt[arg] != ' '; arg++)
    {
      /* Our buffer is only guaranteed to hold 5 arguments. */
      if (arg >= 5)
	LogFatal(msg, fmt);

      switch (fmt[arg])
	{
	case 's':
	  if (arg > 0)
	    *ptr++ = ' ';
	  strcpy(ptr, name->sysname);
	  ptr += strlen(ptr);
	  break;

	case 'n':
	  if (arg > 0)
	    *ptr++ = ' ';
	  strcpy(ptr, name->nodename);
	  ptr += strlen(ptr);
	  break;

	case 'r':
	  if (arg > 0)
	    *ptr++ = ' ';
	  strcpy(ptr, name->release);
	  ptr += strlen(ptr);
	  break;

	case 'v':
	  if (arg > 0)
	    *ptr++ = ' ';
	  strcpy(ptr, name->version);
	  ptr += strlen(ptr);
	  break;

	case 'm':
	  if (arg > 0)
	    *ptr++ = ' ';
	  strcpy(ptr, name->machine);
	  ptr += strlen(ptr);
	  break;

	default:
	  LogFatal(msg, fmt);
	}
    }

  /* Just in case... */
  if (strlen(buf) >= sizeof(buf))
    LogFatal("Buffer overflow parsing uname.");

  /* Parse the buffer.  The sscanf() return value is rarely correct. */
  *result = '\0';
  (void) sscanf(buf, fmt + arg + 1, result);
}
#endif

/* Trim leading 0's and periods from version names.  The 0's cause
   the number to be interpreted as octal numbers.  Some version strings
   have the potential for different numbers of .'s in them.
 */
	
#if (defined(DEFAULT_OS_MAJOR_REV) || defined(DEFAULT_OS_MINOR_REV) || defined(DEFAULT_OS_TEENY_REV))
static const char *
trim_version(const char *p)
{

	if (p != 0 && *p != '\0')
	{
		while ((*p == '0' || *p == '.') && *(p + 1) != '\0')
			++p;
	}
	return (p);
}
#endif

#endif

#ifdef linux
static void
get_distrib(FILE *inFile)
{
  struct stat sb;

  static char* yast = "/sbin/YaST";
  static char* redhat = "/etc/redhat-release";

  fprintf (inFile, "%s\n", "#define LinuxUnknown    0");
  fprintf (inFile, "%s\n", "#define LinuxSuSE       1");
  fprintf (inFile, "%s\n", "#define LinuxCaldera    2");
  fprintf (inFile, "%s\n", "#define LinuxCraftworks 3");
  fprintf (inFile, "%s\n", "#define LinuxDebian     4");
  fprintf (inFile, "%s\n", "#define LinuxInfoMagic  5");
  fprintf (inFile, "%s\n", "#define LinuxKheops     6");
  fprintf (inFile, "%s\n", "#define LinuxPro        7");
  fprintf (inFile, "%s\n", "#define LinuxRedHat     8");
  fprintf (inFile, "%s\n", "#define LinuxSlackware  9");
  fprintf (inFile, "%s\n", "#define LinuxTurbo      10");
  fprintf (inFile, "%s\n", "#define LinuxWare       11");
  fprintf (inFile, "%s\n", "#define LinuxYggdrasil  12");

  if (lstat (yast, &sb) == 0) {
    fprintf (inFile, "%s\n", "#define DefaultLinuxDistribution LinuxSuSE");
    return;
  }
  if (lstat (redhat, &sb) == 0) {
    fprintf (inFile, "%s\n", "#define DefaultLinuxDistribution LinuxRedHat");
    return;
  }
  /* what's the definitive way to tell what any particular distribution is? */

  fprintf (inFile, "%s\n", "#define DefaultLinuxDistribution LinuxUnknown");
  /* would like to know what version of the distribution it is */
}

static const char libc_c[]=
"#include <stdio.h>\n"
"#include <ctype.h>\n"
"\n"
"#if 0\n"
"#pragma weak gnu_get_libc_version\n"
"#pragma weak __libc_version\n"
"#pragma weak __linux_C_lib_version\n"
"#else\n"
"asm (\".weak gnu_get_libc_version\");\n"
"asm (\".weak __libc_version\");\n"
"asm (\".weak __linux_C_lib_version\");\n"
"#endif\n"
"\n"
"extern const char * gnu_get_libc_version (void);\n"
"extern const char * __linux_C_lib_version;\n"
"extern const char __libc_version [];\n"
"\n"
"int\n"
"main ()\n"
"{\n"
"  int libcmajor = 0, libcminor = 0, libcteeny = 0;\n"
"\n"
"  if (((&__linux_C_lib_version != 0)\n"
"       && ((&__libc_version != 0) || (gnu_get_libc_version != 0)))\n"
"      || (!(&__linux_C_lib_version != 0) && !(&__libc_version != 0)\n"
"	  && !(gnu_get_libc_version != 0)))\n"
"  {\n"
"    libcmajor = 0;\n"
"    libcminor = 0;\n"
"    libcteeny = 0;\n"
"  }\n"
"  else\n"
"  {\n"
"    const char * ptr;\n"
"    int glibcmajor = 0;\n"
"\n"
"    if (gnu_get_libc_version != 0)\n"
"    {\n"
"      ptr = gnu_get_libc_version ();\n"
"      glibcmajor = 4;\n"
"    }\n"
"    else if (&__libc_version != 0)\n"
"    {\n"
"      ptr = __libc_version;\n"
"      glibcmajor = 4;\n"
"    }\n"
"    else\n"
"      ptr = __linux_C_lib_version;\n"
"\n"
"    while (!isdigit (*ptr))\n"
"      ptr++;\n"
"\n"
"    sscanf (ptr, \"%d.%d.%d\", &libcmajor, &libcminor, &libcteeny);\n"
"    libcmajor += glibcmajor;\n"
"  }\n"
"\n"
"  printf(\"#define DefaultLinuxCLibMajorVersion %d\\n\", libcmajor);\n"
"  printf(\"#define DefaultLinuxCLibMinorVersion %d\\n\", libcminor);\n"
"  printf(\"#define DefaultLinuxCLibTeenyVersion %d\\n\", libcteeny);\n"
"\n"
"  return 0;\n"
"}\n"
;

#define libc32path "/usr/lib/libc.so"
#define libc64path "/usr/lib64/libc.so"

static void
get_libc_version(FILE *inFile)
{
  char* libcso = NULL;
  struct stat sb;
  char buf[PATH_MAX];
  char* ptr;
  int libcmajor, libcminor, libcteeny;
  struct utsname u;

  /*
   * If we are on a 64-bit Linux system and we see /usr/lib64/libc.so,
   * we should use it.  Otherwise go with /usr/lib/libc.so.  It is entirely
   * possible that someone will be running a 32-bit userland on a 64-bit
   * system.
   */
  if (uname(&u) == -1) {
    fprintf(stderr, "%s (%d): %s\n", __func__, __LINE__, strerror(errno));
    abort();
  }

  if (!strcmp(u.sysname, "Linux") &&
      (!strcmp(u.machine, "x86_64"))) {
    if (!lstat (libc64path, &sb) && S_ISREG(sb.st_mode)) {
      libcso = libc64path;
    }
  }

  if (libcso == NULL) {
    libcso = libc32path;
  }

  if (lstat (libcso, &sb) == 0) {
    if (S_ISLNK (sb.st_mode)) {
      /* 
       * /usr/lib/libc.so is a symlink -- this is libc 5.x
       * we can do this the quick way
        */
      if (readlink (libcso, buf, PATH_MAX) >= 0) {
	for (ptr = buf; *ptr && !isdigit (*ptr); ptr++);
	  (void) sscanf (ptr, "%d.%d.%d", &libcmajor, &libcminor, &libcteeny);
	  fprintf(inFile, "#define DefaultLinuxCLibMajorVersion %d\n", libcmajor);    
	  fprintf(inFile, "#define DefaultLinuxCLibMinorVersion %d\n", libcminor);    
	  fprintf(inFile, "#define DefaultLinuxCLibTeenyVersion %d\n", libcteeny);    
      }
    } else {
      /* 
       * /usr/lib/libc.so is NOT a symlink -- this is libc 6.x / glibc 2.x
       * now we have to figure this out the hard way.
       */
      char aout[PATH_MAX];
      int fd = -1;
      FILE *fp;
      const char *format = "%s -o %s -x c -";
      char *cc;
      int len;
      char *command;

      memset(&aout, '\0', PATH_MAX);

      if (!lstat(getenv("TMPDIR"), &sb) && S_ISDIR(sb.st_mode))
	strcpy(aout, getenv("TMPDIR"));
#ifdef P_tmpdir /* defined by XPG and XOPEN, but don't assume we have it */
      else if (!lstat(P_tmpdir, &sb) && S_ISDIR(sb.st_mode))
	strcpy(aout, P_tmpdir);
#endif
      else if (!lstat("/tmp", &sb) && S_ISDIR(sb.st_mode))
	strcpy(aout, "/tmp");
      else
	abort();

      strcpy(aout+strlen(aout), "/imaketmp.XXXXXX");

      if ((fd = mkstemp(aout)) == -1)
	abort ();

      if (close(fd) == -1)
	abort ();

      cc = getenv ("CC");
      if (cc == NULL)
	cc = "gcc";
      len = strlen (aout) + strlen (format) + strlen (cc);
      if (len < 128) len = 128;
      command = alloca (len);

      if (snprintf (command , len, format, cc, aout) == len)
	abort ();

      fp = popen (command, "w");
      if (fp == NULL || fprintf (fp, "%s\n", libc_c) < 0 || pclose (fp) != 0)
	abort ();

      fp = popen (aout, "r");
      if (fp == NULL)
	abort ();

      while (fgets (command, len, fp))
	fprintf (inFile, command);
  
      len = pclose (fp);
      remove (aout);
      if (len)
	abort ();
    }
  }
}

static void
get_ld_version(FILE *inFile)
{
  FILE* ldprog = popen ("ld -v", "r");
  char c;
  int ldmajor, ldminor;

  if (ldprog) {
    do {
      c = fgetc (ldprog);
    } while (c != EOF && !isdigit (c));
    ungetc (c, ldprog);
    (void) fscanf (ldprog, "%d.%d", &ldmajor, &ldminor);
    fprintf(inFile, "#define DefaultLinuxBinUtilsMajorVersion %d\n", 
	    ldmajor * 10 + ldminor);    
    pclose (ldprog);
  }
}
#endif

#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#if defined(sun) && defined(__SVR4)
static void
get_sun_compiler_versions(FILE *inFile)
{
  char buf[PATH_MAX];
  char cmd[PATH_MAX];
  static char* sunpro_cc = "/opt/SUNWspro/bin/cc";
  static char* sunpro_CC = "/opt/SUNWspro/bin/CC";
  int cmajor, cminor;
  char* vptr;
  struct stat sb;
  FILE* ccproc;

  if (lstat (sunpro_cc, &sb) == 0) {
    strcpy (cmd, sunpro_cc);
    strcat (cmd, " -V 2>&1");
    if ((ccproc = popen (cmd, "r")) != NULL) {
      if (fgets (buf, PATH_MAX, ccproc) != NULL) {
	vptr = strrchr (buf, 'C');
	for (; !isdigit(*vptr); vptr++);
	(void) sscanf (vptr, "%d.%d", &cmajor, &cminor);
	fprintf (inFile, 
		 "#define DefaultSunProCCompilerMajorVersion %d\n",
		 cmajor);
	fprintf (inFile, 
		 "#define DefaultSunProCCompilerMinorVersion %d\n",
		 cminor);
      }
      while (fgets (buf, PATH_MAX, ccproc) != NULL) {};
      pclose (ccproc);
    }
  }
  if (lstat (sunpro_CC, &sb) == 0) {
    strcpy (cmd, sunpro_CC);
    strcat (cmd, " -V 2>&1");
    if ((ccproc = popen (cmd, "r")) != NULL) {
      if (fgets (buf, PATH_MAX, ccproc) != NULL) {
	vptr = strrchr (buf, 'C');
	for (; !isdigit(*vptr); vptr++);
	(void) sscanf (vptr, "%d.%d", &cmajor, &cminor);
	fprintf (inFile, 
		 "#define DefaultSunProCplusplusCompilerMajorVersion %d\n",
		 cmajor);
	fprintf (inFile, 
		 "#define DefaultSunProCplusplusCompilerMinorVersion %d\n",
		 cminor);
      }
      while (fgets (buf, PATH_MAX, ccproc) != NULL) {};
      pclose (ccproc);
    }
  }
}
#endif

static void
get_gcc_incdir(FILE *inFile)
{
  static char* gcc_path[] = {
#ifdef linux
    "/usr/bin/cc",	/* for Linux PostIncDir */
#endif
    "/usr/local/bin/gcc",
    "/opt/gnu/bin/gcc"
  };
  struct stat sb;
  int i;
  FILE* gccproc;
  char buf[PATH_MAX];
  char cmd[PATH_MAX];
  char* ptr;

  buf[0] = '\0';
  for (i = 0; i < sizeof gcc_path / sizeof gcc_path[0]; i++) {
    if (lstat (gcc_path[i], &sb) == 0) {
      strcpy (cmd, gcc_path[i]);
      strcat (cmd, " --print-libgcc-file-name");
      if ((gccproc = popen (cmd, "r")) != NULL) {
	if (fgets (buf, PATH_MAX, gccproc) != NULL) {
	  ptr = strstr (buf, "libgcc.a");
	  if (ptr) strcpy (ptr, "include");
	}
	(void) pclose (gccproc);
	break;
      }
    }
  }
  if (buf[0])
    fprintf (inFile, "#define DefaultGccIncludeDir %s\n", buf);
}

static boolean
define_os_defaults(FILE *inFile)
{
#ifndef WIN32
#if (defined(DEFAULT_OS_NAME) || defined(DEFAULT_OS_MAJOR_REV) || \
     defined(DEFAULT_OS_MINOR_REV) || defined(DEFAULT_OS_TEENY_REV))
	struct utsname name;
	char buf[SYS_NMLN * 5 + 1];

	/* Obtain the system information. */
	if (uname(&name) < 0)
		LogFatal("Cannot invoke uname");

# ifdef DEFAULT_OS_NAME
	parse_utsname(&name, DEFAULT_OS_NAME, buf, 
		      "Bad DEFAULT_OS_NAME syntax %s");
	if (buf[0] != '\0')
		fprintf(inFile, "#define DefaultOSName %s\n", buf);
# endif

# ifdef DEFAULT_OS_MAJOR_REV
	parse_utsname(&name, DEFAULT_OS_MAJOR_REV, buf,
		      "Bad DEFAULT_OS_MAJOR_REV syntax %s");
	fprintf(inFile, "#define DefaultOSMajorVersion %s\n", 
		*buf ? trim_version(buf) : "0");
# endif

# ifdef DEFAULT_OS_MINOR_REV
	parse_utsname(&name, DEFAULT_OS_MINOR_REV, buf,
		      "Bad DEFAULT_OS_MINOR_REV syntax %s");
	fprintf(inFile, "#define DefaultOSMinorVersion %s\n", 
		*buf ? trim_version(buf) : "0");
# endif

# ifdef DEFAULT_OS_TEENY_REV
	parse_utsname(&name, DEFAULT_OS_TEENY_REV, buf,
		      "Bad DEFAULT_OS_TEENY_REV syntax %s");
	fprintf(inFile, "#define DefaultOSTeenyVersion %s\n", 
		*buf ? trim_version(buf) : "0");
# endif
#endif
#ifdef linux
    get_distrib (inFile);
    get_libc_version (inFile);
    get_ld_version(inFile);
#endif
    get_gcc_incdir(inFile);
#if defined (sun) && defined(SVR4)
    get_sun_compiler_versions (inFile);
#endif
#else /* WIN32 */
   OSVERSIONINFO osvi;
   static char* os_names[] = { "Win32s", "Windows 95", "Windows NT" };

   memset(&osvi, 0, sizeof(OSVERSIONINFO));
   osvi.dwOSVersionInfoSize = sizeof (OSVERSIONINFO);
   GetVersionEx (&osvi);

   fprintf (inFile, "#define DefaultOSName Microsoft %s\n", 
	    os_names[osvi.dwPlatformId]);

   fprintf(inFile, "#define DefaultOSMajorVersion %d\n", osvi.dwMajorVersion);
   fprintf(inFile, "#define DefaultOSMinorVersion %d\n", osvi.dwMinorVersion);
   fprintf(inFile, "#define DefaultOSTeenyVersion %d\n", 
	   osvi.dwBuildNumber & 0xFFFF);
#endif /* WIN32 */
   return FALSE;
}

static void
cppit(const char *imakefile, const char *template, const char *masterc, FILE *outfd, const char *outfname)
{
	FILE	*inFile;

	haveImakefileC = TRUE;
	inFile = fopen(masterc, "w");
	if (inFile == NULL)
		LogFatal("Cannot open %s for output.", masterc);
	if (fprintf(inFile, "%s\n", ImakefileCHeader) < 0 ||
	    define_os_defaults(inFile) ||
	    optional_include(inFile, "IMAKE_LOCAL_DEFINES", "localdefines") ||
	    optional_include(inFile, "IMAKE_ADMIN_DEFINES", "admindefines") ||
	    fprintf(inFile, "#define %s <%s>\n", ImakeDefSym, imakefile) < 0 ||
	    fprintf(inFile, LocalDefineFmt, ImakeTmplSym, template) < 0 ||
	    fprintf(inFile, IncludeFmt, ImakeTmplSym) < 0 ||
	    optional_include(inFile, "IMAKE_ADMIN_MACROS", "adminmacros") ||
	    optional_include(inFile, "IMAKE_LOCAL_MACROS", "localmacros") ||
	    fflush(inFile) || 
	    fclose(inFile))
		LogFatal("Cannot write to %s.", masterc);
	/*
	 * Fork and exec cpp
	 */
	doit(outfd, cpp, cpp_argv);
	CleanCppOutput(outfd, outfname);
}

static void
makeit(void)
{
	doit(NULL, make_argv[0], make_argv);
}

static char *
CleanCppInput(char *imakefile)
{
	FILE	*outFile = NULL;
	FILE	*inFile;
	char	*buf,		/* buffer for file content */
		*pbuf,		/* walking pointer to buf */
		*punwritten,	/* pointer to unwritten portion of buf */
		*ptoken,	/* pointer to # token */
		*pend,		/* pointer to end of # token */
		savec;		/* temporary character holder */
	int	count;
	struct stat	st;

	/*
	 * grab the entire file.
	 */
	if (!(inFile = fopen(imakefile, "r")))
		LogFatal("Cannot open %s for input.", imakefile);
	if (fstat(fileno(inFile), &st) < 0)
		LogFatal("Cannot stat %s for size.", imakefile);
	buf = Emalloc((int)st.st_size+3);
	count = fread(buf + 2, 1, st.st_size, inFile);
	if (count == 0  &&  st.st_size != 0)
		LogFatal("Cannot read %s:", imakefile);
	fclose(inFile);
	buf[0] = '\n';
	buf[1] = '\n';
	buf[count + 2] = '\0';

	punwritten = pbuf = buf + 2;
	while (*pbuf) {
	    /* for compatibility, replace make comments for cpp */
	    if (*pbuf == '#' && pbuf[-1] == '\n' && pbuf[-2] != '\\') {
		ptoken = pbuf+1;
		while (*ptoken == ' ' || *ptoken == '\t')
			ptoken++;
		pend = ptoken;
		while (*pend && *pend != ' ' && *pend != '\t' && *pend != '\n')
			pend++;
		savec = *pend;
		*pend = '\0';
		if (strcmp(ptoken, "define") &&
		    strcmp(ptoken, "if") &&
		    strcmp(ptoken, "ifdef") &&
		    strcmp(ptoken, "ifndef") &&
		    strcmp(ptoken, "include") &&
		    strcmp(ptoken, "line") &&
		    strcmp(ptoken, "else") &&
		    strcmp(ptoken, "elif") &&
		    strcmp(ptoken, "endif") &&
		    strcmp(ptoken, "error") &&
		    strcmp(ptoken, "pragma") &&
		    strcmp(ptoken, "undef")) {
		    if (outFile == NULL) {
			tmpImakefile = Strdup(tmpImakefile);
			mkstemp(tmpImakefile);
			outFile = fopen(tmpImakefile, "w");
			if (outFile == NULL)
			    LogFatal("Cannot open %s for write.",
				tmpImakefile);
		    }
		    writetmpfile(outFile, punwritten, pbuf-punwritten,
				 tmpImakefile);
		    if (ptoken > pbuf + 1)
			writetmpfile(outFile, "XCOMM", 5, tmpImakefile);
		    else
			writetmpfile(outFile, "XCOMM ", 6, tmpImakefile);
		    punwritten = pbuf + 1;
		}
		*pend = savec;
	    }
	    pbuf++;
	}
	if (outFile) {
	    writetmpfile(outFile, punwritten, pbuf-punwritten, tmpImakefile);
	    fclose(outFile);
	    return tmpImakefile;
	}

	return(imakefile);
}

static void
CleanCppOutput(FILE *tmpfd, const char *tmpfname)
{
	char	*input;
	int	blankline = 0;

	while ((input = ReadLine(tmpfd, tmpfname))) {
		if (isempty(input)) {
			if (blankline++)
				continue;
			KludgeResetRule();
		} else {
			blankline = 0;
			KludgeOutputLine(&input);
			writetmpfile(tmpfd, input, strlen(input), tmpfname);
		}
		writetmpfile(tmpfd, "\n", 1, tmpfname);
	}
	fflush(tmpfd);
#ifdef NFS_STDOUT_BUG
	/*
	 * On some systems, NFS seems to leave a large number of nulls at
	 * the end of the file.  Ralph Swick says that this kludge makes the
	 * problem go away.
	 */
	ftruncate (fileno(tmpfd), (off_t)ftell(tmpfd));
#endif
}

/*
 * Determine if a line has nothing in it.  As a side effect, we trim white
 * space from the end of the line.  Cpp magic cookies are also thrown away.
 * "XCOMM" token is transformed to "#".
 */
static boolean
isempty(char *line)
{
	char	*pend;

	/*
	 * Check for lines of the form
	 *	# n "...
	 * or
	 *	# line n "...
	 */
	if (*line == '#') {
		pend = line+1;
		if (*pend == ' ')
			pend++;
		if (*pend == 'l' && pend[1] == 'i' && pend[2] == 'n' &&
		    pend[3] == 'e' && pend[4] == ' ')
			pend += 5;
		if (isdigit(*pend)) {
		    	do {
			    pend++;
			} while (isdigit(*pend));
			if (*pend == '\n' || *pend == '\0')
				return(TRUE);
			if (*pend++ == ' ' && *pend == '"')
				return(TRUE);
		}
		while (*pend)
		    pend++;
	} else {
	    for (pend = line; *pend; pend++) {
		if (*pend == 'X' && pend[1] == 'C' && pend[2] == 'O' &&
		    pend[3] == 'M' && pend[4] == 'M' &&
		    (pend == line || pend[-1] == ' ' || pend[-1] == '\t') &&
		    (pend[5] == ' ' || pend[5] == '\t' || pend[5] == '\0'))
		{
		    *pend = '#';
		    strcpy(pend+1, pend+5);
		}
#ifdef MAGIC_MAKE_VARS
		if (*pend == 'X' && pend[1] == 'V' && pend[2] == 'A' &&
		    pend[3] == 'R')
		{
		    char varbuf[5];
		    int i;

		    if (pend[4] == 'd' && pend[5] == 'e' && pend[6] == 'f' &&
			pend[7] >= '0' && pend[7] <= '9')
		    {
			i = pend[7] - '0';
			sprintf(varbuf, "%0.4d", xvariable);
			strncpy(pend+4, varbuf, 4);
			xvariables[i] = xvariable;
			xvariable = (xvariable + 1) % 10000;
		    }
		    else if (pend[4] == 'u' && pend[5] == 's' &&
			     pend[6] == 'e' && pend[7] >= '0' &&
			     pend[7] <= '9')
		    {
			i = pend[7] - '0';
			sprintf(varbuf, "%0.4d", xvariables[i]);
			strncpy(pend+4, varbuf, 4);
		    }
		}
#endif
	    }
	}
	while (--pend >= line && (*pend == ' ' || *pend == '\t')) ;
	pend[1] = '\0';
	return (*line == '\0');
}

/*ARGSUSED*/
static char *
ReadLine(FILE *tmpfd, const char *tmpfname)
{
	static boolean	initialized = FALSE;
	static char	*buf, *pline, *end;
	char	*p1, *p2;

	if (! initialized) {
#ifdef WIN32
		FILE *fp = tmpfd;
#endif
		int	total_red;
		struct stat	st;

		/*
		 * Slurp it all up.
		 */
		fseek(tmpfd, 0, 0);
		if (fstat(fileno(tmpfd), &st) < 0)
			LogFatal("cannot stat %s for size", tmpMakefile);
		pline = buf = Emalloc((int)st.st_size+1);
		total_red = fread(buf, 1, st.st_size, tmpfd);
		if (total_red == 0  &&  st.st_size != 0)
			LogFatal("cannot read %s", tmpMakefile);
		end = buf + total_red;
		*end = '\0';
		fseek(tmpfd, 0, 0);
#if defined(SYSV) || defined(WIN32)
		tmpfd = freopen(tmpfname, "w+", tmpfd);
#ifdef WIN32
		if (! tmpfd) /* if failed try again */
			tmpfd = freopen(tmpfname, "w+", fp);
#endif
		if (! tmpfd)
			LogFatal("cannot reopen %s.", tmpfname);
#else	/* !SYSV */
		ftruncate(fileno(tmpfd), (off_t) 0);
#endif	/* !SYSV */
		initialized = TRUE;
	    fprintf (tmpfd, "# Makefile generated by imake - do not edit!\n");
	    fprintf (tmpfd, "# %s\n",
		"$TOG: imake.c /main/104 1998/03/24 12:45:15 kaleb $");
	}

	for (p1 = pline; p1 < end; p1++) {
		if (*p1 == '@' && *(p1+1) == '@'
		    /* ignore ClearCase version-extended pathnames */
		    && !(p1 != pline && !isspace(*(p1-1)) && *(p1+2) == '/'))
		{ /* soft EOL */
			*p1++ = '\0';
			p1++; /* skip over second @ */
			break;
		}
		else if (*p1 == '\n') { /* real EOL */
#ifdef WIN32
			if (p1 > pline && p1[-1] == '\r')
				p1[-1] = '\0';
#endif
			*p1++ = '\0';
			break;
		}
	}

	/*
	 * return NULL at the end of the file.
	 */
	p2 = (pline == p1 ? NULL : pline);
	pline = p1;
	return(p2);
}

static void
writetmpfile(FILE *fd, const char *buf, int cnt, const char *fname)
{
	if (fwrite(buf, sizeof(char), cnt, fd) == -1)
		LogFatal("Cannot write to %s.", fname);
}

static char *
Emalloc(int size)
{
	char	*p;

	if ((p = malloc(size)) == NULL)
		LogFatal("Cannot allocate %d bytes.", size);
	return(p);
}

#ifdef FIXUP_CPP_WHITESPACE
static void
KludgeOutputLine(char **pline)
{
	char	*p = *pline;
	char	quotechar = '\0';

	switch (*p) {
	    case '#':	/*Comment - ignore*/
		break;
	    case '\t':	/*Already tabbed - ignore it*/
	    	break;
	    case ' ':	/*May need a tab*/
	    default:
# ifdef INLINE_SYNTAX
		if (*p == '<' && p[1] == '<') { /* inline file close */
		    InInline--;
		    InRule = TRUE;
		    break;
		}
# endif
		/*
		 * The following cases should not be treated as beginning of 
		 * rules:
		 * variable := name	(GNU make)
		 * variable = .*:.*	(':' should be allowed as value)
		 *	sed 's:/a:/b:'	(: used in quoted values)
		 */
		for (; *p; p++) {
		    if (quotechar) {
			if (quotechar == '\\' ||
			    (*p == quotechar &&
# ifdef WIN32
			     quotechar != ')' &&
# endif
			     p[-1] != '\\'))
			    quotechar = '\0';
			continue;
		    }
		    switch (*p) {
		    case '\\':
		    case '"':
		    case '\'':
			quotechar = *p;
			break;
		    case '(':
			quotechar = ')';
			break;
		    case '{':
			quotechar = '}';
			break;
		    case '[':
			quotechar = ']';
			break;
		    case '=':
# ifdef REMOVE_CPP_LEADSPACE
			if (!InRule && **pline == ' ') {
			    while (**pline == ' ')
				(*pline)++;
			}
# endif
			goto breakfor;
# ifdef INLINE_SYNTAX
		    case '<':
			if (p[1] == '<') /* inline file start */
			    InInline++;
			break;
# endif
		    case ':':
			if (p[1] == '=')
			    goto breakfor;
			while (**pline == ' ')
			    (*pline)++;
			InRule = TRUE;
			return;
		    }
		}
breakfor:
		if (InRule && **pline == ' ')
		    **pline = '\t';
		break;
	}
}

static void
KludgeResetRule(void)
{
	InRule = FALSE;
}
#endif /* FIXUP_CPP_WHITESPACE */

static char *
Strdup(const char *cp)
{
	char *new = Emalloc(strlen(cp) + 1);

	strcpy(new, cp);
	return new;
}
