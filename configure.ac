#
# https://www.gnu.org/software/autoconf/manual/autoconf-2.65/autoconf.html
# https://autotools.io/autoconf/
#

AC_INIT()
AC_CONFIG_FILES(Makefile)

##########
#
# project options

AC_ARG_ENABLE([activeshuttle],
              AS_HELP_STRING([--enable-activeshuttle], [enable project "activeshuttle"]))

AC_ARG_ENABLE([devel_activeshuttle],
              AS_HELP_STRING([--enable-devel_activeshuttle], [enable project "devel_activeshuttle"]))

AC_ARG_ENABLE([standalone],
              AS_HELP_STRING([--enable-standalone], [enable project "standalone"]))


# sanity checks, so that not two projects are enabled at the same time

NUMPROJ=0

AS_IF([test "x$enable_activeshuttle"         = "xyes"], [NUMPROJ=`expr $NUMPROJ + 1`])
AS_IF([test "x$enable_devel_activeshuttle"   = "xyes"], [NUMPROJ=`expr $NUMPROJ + 1`])
AS_IF([test "x$enable_standalone"            = "xyes"], [NUMPROJ=`expr $NUMPROJ + 1`])

AS_IF([test "$NUMPROJ" -lt "1"], [AC_MSG_ERROR([no project enabled])])
AS_IF([test "$NUMPROJ" -gt "1"], [AC_MSG_ERROR([more than one project enabled])])

# export selected project as variable

project=undefined
AS_IF([test "x$enable_activeshuttle"         = "xyes"], project=activeshuttle)
AS_IF([test "x$enable_devel_activeshuttle"   = "xyes"], project=devel-activeshuttle)
AS_IF([test "x$enable_standalone"            = "xyes"], project=standalone)

##########
#
# feature options

AC_ARG_WITH([tests],
            AS_HELP_STRING([--with-tests], [enable building tests]))

tests=0
AC_ARG_WITH([debug],
            AS_HELP_STRING([--with-debug], [compile with debug code]))
AS_IF([test "x$with_tests" = "xyes"], tests=1)

debug=0
AC_ARG_WITH([licensing],
            AS_HELP_STRING([--without-licensing], [compile without licensing]))
AS_IF([test "x$with_debug" = "xyes"], debug=1)

licensing=1
AC_ARG_WITH([coverage],
            AS_HELP_STRING([--with-coverage], [compile with coverage]))
AS_IF([test "x$with_licensing" = "xno"], licensing=0)

coverage=0
AC_ARG_WITH([coverage],
            AS_HELP_STRING([--with-coverage], [compile with coverage]))
AS_IF([test "x$with_coverage" = "xyes"], coverage=1)

##########
#
# output results

AC_SUBST(project)
AC_SUBST(tests)
AC_SUBST(debug)
AC_SUBST(licensing)
AC_SUBST(coverage)

AC_OUTPUT()
