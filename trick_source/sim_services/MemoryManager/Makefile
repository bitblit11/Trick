
# $Id: Makefile 3737 2014-11-06 23:26:46Z jpenn1 $

include ${TRICK_HOME}/makefiles/Makefile.common
include ${TRICK_HOME}/makefiles/Makefile.tricklib
-include Makefile_deps

$(L_OBJS) : TRICK_CXXFLAGS += -Wno-unused-parameter -Wno-unused-function -Wno-sign-compare -x c++
$(Y_OBJS) : TRICK_CXXFLAGS += -Wno-unused-parameter -Wno-unused -x c++

ifeq ($(IS_CC_CLANG), 1)
$(Y_OBJS) : TRICK_CXXFLAGS += -Wno-parentheses-equality
endif

# suppress warnings files with shadowing.
$(CPP_OBJS) : TRICK_CXXFLAGS += -Wno-shadow

docs: MM.doxygen
	doxygen MM.doxygen
