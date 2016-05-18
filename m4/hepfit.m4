dnl ###### MultiNest ######
AC_DEFUN([MULTINEST],
[
AC_MSG_CHECKING([for MultiNest location])

AC_ARG_WITH(multinest,
        AC_HELP_STRING([--with-multinest=DIR],[location of MultiNest installation @<:@default=system libs@:>@]),
        [],
	[with_multinest=system])

if test "x$with_multinest" = "xno"; then
AC_MSG_ERROR([libnest3 is required. Please install MultiNest.])
fi

if test "x$with_multinest" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(nest3,main,[],
			[
			AC_MSG_ERROR([Cannot find libnest3.a. Please install MultiNest or use --with-multinest=.])
			]
		     )
	multinestLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_multinest/libnest3.a"; then
		AC_MSG_RESULT([found in $with_multinest])
		multinestLIBS="-L$with_multinest -R$with_multinest -lnest3"
	elif test -e "$with_multinest/lib/libnest3.a"; then
		AC_MSG_RESULT([found in $with_multinest])
		multinestLIBS="-L$with_multinest -R$with_multinest -lnest3"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_multinest/libnest3.a])
	fi
fi

HEPfit_LIBS="$HEPfit_LIBS $multinestLIBS"

])

dnl ###### MultiNestPlugin ######
AC_DEFUN([MULTINESTPLUGIN],
[
AC_MSG_CHECKING([for MultiNestPlugin location])

AC_ARG_WITH(multinestplugin,
        AC_HELP_STRING([--with-multinestplugin=DIR],[location of MultiNestPlugin installation @<:@default=system libs@:>@]),
        [],
	[with_multinestplugin=system])

if test "x$with_multinestplugin" = "xno"; then
AC_MSG_ERROR([MultiNestPlugin-1.0 is required. Please install RootMultiNest.])
fi

if test "x$with_multinestplugin" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
   
        AC_LANG_SAVE dnl Save the current state
	AC_LANG_CPLUSPLUS
        AC_CHECK_LIB(MultiNestPlugin-1.0,main,[],
			[
			AC_MSG_ERROR([Cannot find libMultiNestPlugin-1.0.a. Please install RootMultiNest or use --with-multinestplugin=.])
			]
		    )
        AC_LANG_RESTORE
	
	multinestpluginLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_multinestplugin/lib/rootmultinestplugin/libMultiNestPlugin-1.0.a" -a -d "$with_multinestplugin/include/RooStats"; then
		AC_MSG_RESULT([found in $with_multinestplugin/lib/rootmultinestplugin])
		multinestpluginLIBS="-L$with_multinestplugin/lib/rootmultinestplugin -R$with_multinestplugin/lib/rootmultinestplugin -lMultiNestPlugin-1.0"
		multinestplugin_inc="-I$with_multinestplugin/include"	
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_multinestplugin/lib/rootmultinestplugin/libMultiNestPlugin-1.0.a or the headers in $with_multinestplugin/include/RooStats])
	fi
fi

HEPfit_LIBS="$HEPfit_LIBS $multinestpluginLIBS"
HEPfit_CFLAGS="$HEPfit_CFLAGS $multinestplugin_inc"
])

dnl ###### GSL CHECK ######
AC_DEFUN([HEPFIT_CHECK_GSL],
[
AC_MSG_CHECKING([for gsl location])
GSLINCLUDE=""
GSLLIBS=""

AC_ARG_WITH(gsl, AC_HELP_STRING([],[]),
        [],
	[with_gsl=system])

if test "x$with_gsl" = "xno"; then
AC_MSG_ERROR([libgsl is required. Please install the GNU scientific library and header files.])
fi

if test "x$with_gsl" = "xsystem"; then
	AC_MSG_RESULT([in system libraries or non-standard directory])
	oldlibs="$LIBS"
	AC_CHECK_LIB(m,main)
	AC_CHECK_LIB(gslcblas,main)
	AC_CHECK_LIB(gsl,main,[with_gsl=check],
			[
			AC_MSG_ERROR([Cannot find libgsl. Please install the GNU scientific library and header files or use --with-gsl=.])
			]
		     )
	GSLLIBS="$LIBS"
	LIBS=$oldlibs

	
else
	if test "`uname -m`" = "x86_64" -a -e "$with_gsl/lib64/libgsl.a" -a -d "$with_gsl/include/gsl"; then
		AC_MSG_RESULT([found in $with_gsl])
		GSLLIBS="-L$with_gsl/lib64 -R$with_gsl/lib64 -lgslcblas -lgsl"
		GSLINCLUDE="-I$with_gsl/include"
	elif test -e "$with_gsl/lib/libgsl.a" -a -d "$with_gsl/include/gsl"; then
		AC_MSG_RESULT([found in $with_gsl])
		GSLLIBS="-L$with_gsl/lib -R$with_gsl/lib -lgslcblas -lgsl"
		GSLINCLUDE="-I$with_gsl/include"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_gsl/lib/libgsl.a or the headers in $with_gsl/include])
	fi
fi

])

dnl ###### LOOPTOOLS PATH ######
AC_DEFUN([HEPFIT_LOOPTOOLS_PATH],
[
AC_MSG_CHECKING([for looptools location])

AC_ARG_WITH(looptools,
        AC_HELP_STRING([--with-looptools=DIR],[location of looptools installation @<:@default=system libs@:>@]),
        [],
	[with_looptools=system])

if test "x$with_looptools" = "xno"; then
AC_MSG_ERROR([liblooptools is required. Please install LoopTools.])
fi

if test "x$with_looptools" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(ooptools,main,[],
			[
			AC_MSG_ERROR([Cannot find liblooptools. Please install LoopTools or use --with-looptools=.])
			]
		     )
	LTLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_looptools/lib64/libooptools.a" -a -d "$with_looptools/include/"; then
		AC_MSG_RESULT([found in $with_looptools])
		LTLIBS="-L$with_looptools/lib64 -R$with_looptools/lib64 -looptools"
		LTINCLUDE="-I$with_looptools/include"
	elif test -e "$with_looptools/lib/libooptools.a" -a -d "$with_looptools/include/"; then
		AC_MSG_RESULT([found in $with_looptools])
		LTLIBS="-L$with_looptools/lib -R$with_looptools/lib -looptools"
		LTINCLUDE="-I$with_looptools/include"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_looptools/lib/libooptools.a or the headers in $with_looptools/include])
	fi
fi

HEPfit_LIBS="$HEPfit_LIBS $LTLIBS"
HEPfit_CFLAGS="$HEPfit_CFLAGS $LTINCLUDE"
])


dnl ##### LOOPTOOLS #####
AC_DEFUN([HEPFIT_LOOPTOOLS],
[


AC_MSG_CHECKING([if Looptools build works])
enable_looptools=yes

if test "x$GCC" = "xyes"; then
   case "${host}" in
      x86_64-*|*-darwin1*)
	AM_FCFLAGS="$AM_FCFLAGS -fdefault-integer-8"
      	;;
   esac

   	oldFCFLAGS="$FCFLAGS"
   	FCFLAGS="$AM_FCFLAGS"
   	AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],[      print *[,]"Hello"])],
		[],
		[AC_MSG_RESULT([no])
 		 AC_MSG_ERROR([needs gfortran on 64bit machines])]
	)
	FCFLAGS="$oldFCFLAGS"
fi
AC_MSG_RESULT([$enable_looptools])

])

dnl ###### BAT PATH ######
AC_DEFUN([HEPFIT_BAT_PATH],
[
AC_MSG_CHECKING([for BAT location])

AC_ARG_WITH(bat,
        AC_HELP_STRING([--with-bat=DIR],[location of BAT installation @<:@default=system libs@:>@]),
        [],
	[with_bat=system])

if test "x$with_bat" = "xno"; then
AC_MSG_ERROR([libBAT is required. Please install BAT.])
fi

if test "x$with_bat" = "xsystem"; then
	AC_MSG_RESULT([in system libraries])
	oldlibs="$LIBS"
	AC_CHECK_LIB(BAT,main,[],
			[
			AC_MSG_ERROR([Cannot find libBAT. Please install BAT or use --with-bat=.])
			]
		     )
	BATLIBS="$LIBS"
	LIBS=$oldlibs
else
	if test "`uname -m`" = "x86_64" -a -e "$with_bat/lib64/libBAT.a" -a -d "$with_bat/include/BAT"; then
		AC_MSG_RESULT([found in $with_bat])
		BATLIBS="-L$with_bat/lib64 -R$with_bat/lib64 -lBATmodels -lBAT"
		BATINCLUDE="-I$with_bat/include"
	elif test -e "$with_bat/lib/libBAT.a" -a -d "$with_bat/include/BAT"; then
		AC_MSG_RESULT([found in $with_bat])
		BATLIBS="-L$with_bat/lib -R$with_bat/lib -lBATmodels -lBAT"
		BATINCLUDE="-I$with_bat/include"
	else
		AC_MSG_RESULT([not found])
		AC_MSG_ERROR([Can't find $with_bat/lib/libBAT.a or the headers in $with_bat/include])
	fi
fi

HEPfit_LIBS="$HEPfit_LIBS $BATLIBS"
HEPfit_CFLAGS="$HEPfit_CFLAGS $BATINCLUDE"
])

dnl ## HEPFIT overview
AC_DEFUN([HEPFIT_OVERVIEW],
[
FCSTRING=`$FC --version | head -1`
CXXSTRING=`$CXX --version | head -1`
CCSTRING=`$CC --version | head -1`
if test "x$PYTHON" != "x:"
then
   python_was_found="yes, using Python $PYTHON_VERSION"
else
   python_was_found="no, requires Python >= 2.6"
fi
cat << _HEPFIT_EOF_ > config.hepfit
*****************************************************
*** $PACKAGE_STRING configuration summary
*** Please include this information in bug reports!
***--------------------------------------------------
*** Prefix:		$prefix
***
*** MultiNest:		$with_multinest
***
*** RootMultiNestPlugin:$with_multinestplugin
#***
#*** BAT:		$with_bat
***
*** GSL:		`$GSL_CONFIG --prefix`
*** root:   		${ROOTCFLAGS} (root-version: $ROOTVERSION)
*** boost:              ${BOOST_CPPFLAGS}
***
*** Host:		$host
*** CC:			$CCSTRING
*** CXX:		$CXXSTRING
*** FC:			$FCSTRING
***
*** CXXFLAGS:		$CXXFLAGS
*****************************************************
_HEPFIT_EOF_
])
