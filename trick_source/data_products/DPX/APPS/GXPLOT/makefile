
# $Id: makefile 3163 2013-08-16 22:30:39Z tdowlen $

include ${TRICK_HOME}/makefiles/Makefile.common

RM = rm -rf
CC = cc
CPP = c++

DPX_DIR = ../..

INCDIRS = -I${DPX_DIR} -I../../.. -I/usr/include/libxml2 $(MOTIF_INCDIR)

CFLAGS = -g -Wall

OBJDIR = object_${TRICK_HOST_CPU}
LIBDIR = ${DPX_DIR}/lib_${TRICK_HOST_CPU}

ifeq ($(TRICK_HOST_TYPE), Linux)
    LIBRTDEF = -lrt
else
    LIBRTDEF =
endif

ifeq ($(TRICK_HOST_TYPE), Darwin)
     INCDIRS += -I/usr/X11/include
     MOTIF_INCDIR = -I/sw/include
     XLIBS = -L/sw/lib -lXm -L/usr/X11R6/lib -lXt -lX11 ${LIBXML}
else
     XLIBS = -L/usr/X11R6/lib64 -L/usr/X11R6/lib -lXm -lXt -lX11 ${LIBXML}
endif

ifneq ($(HDF5),)
ifneq ($(HDF5),/usr)
 HDF5_LIB = -L$(HDF5)/lib -L$(HDF5)/lib64 -lhdf5_hl -lhdf5 -lsz
else
 HDF5_LIB = -lhdf5_hl -lhdf5
endif
endif

DP_LIBS         = -L../../../lib_${TRICK_HOST_CPU} -llog -lvar -leqparse -L${TRICK_HOME}/lib_${TRICK_HOST_CPU} -ltrick_units
MODEL_LIBS      = -L${DPX_DIR}/lib_${TRICK_HOST_CPU} -lDPM
CONTROLLER_LIBS = -L${DPX_DIR}/lib_${TRICK_HOST_CPU} -lDPC

ALL_LIBS = $(CONTROLLER_LIBS) $(MODEL_LIBS) ${DP_LIBS} ${TRICK_UNIT_LIBS} ${HDF5_LIB} -ldl

#############################################################################
##                            MODEL TARGETS                                ##
#############################################################################

C_OBJECT_FILES = $(OBJDIR)/parse_format.o \
    $(OBJDIR)/post_dialog.o

CXX_OBJECT_FILES = $(OBJDIR)/gp_view.o \
    $(OBJDIR)/gp_colors.o \
    $(OBJDIR)/gp_utilities.o \
    $(OBJDIR)/gp_version.o \
    $(OBJDIR)/gxplot.o \
    $(OBJDIR)/gp_view_curve_node.o \
    $(OBJDIR)/gp_view_plot_node.o \
    $(OBJDIR)/table_view_node.o \
    $(OBJDIR)/gp_view_page_node.o \
    $(OBJDIR)/gp_view_product_node.o

OBJECT_FILES = $(C_OBJECT_FILES) $(CXX_OBJECT_FILES)

all: $(OBJDIR)/gxplot

$(OBJDIR)/gxplot: ${LIBDIR}/libDPM.a ${LIBDIR}/libDPC.a ${LIBDIR}/libDPV.a $(OBJECT_FILES)
	@echo "===== Making gxplot ====="
	${CPP} ${CFLAGS} ${INCDIRS} -o $@ $(OBJECT_FILES) $(ALL_LIBS) ${XLIBS} ${LIBRTDEF} ${CONTROLLER_LIBS} -lDPV

$(C_OBJECT_FILES) : $(OBJDIR)/%.o : %.c
	${CC} ${CFLAGS} ${INCDIRS} -c $< -o $@

$(CXX_OBJECT_FILES) : $(OBJDIR)/%.o : %.cpp
	${CPP} ${CFLAGS} ${INCDIRS} -c $< -o $@

$(OBJECT_FILES) : | $(OBJDIR)

$(OBJDIR) :
	@ mkdir $@

${LIBDIR}/libDPM.a:
	@echo "===== Making libDPM.a ====="
	$(MAKE) -C ${DPX_DIR}/DPM

${LIBDIR}/libDPC.a:
	@echo "===== Making libDPC.a ====="
	$(MAKE) -C ${DPX_DIR}/DPC

${LIBDIR}/libDPV.a:
	@echo "===== Making libDPV.a ====="
	$(MAKE) -C ${DPX_DIR}/DPV/UTILS

clean:
	${RM} $(OBJDIR)

spotless: clean

gxplot: ../../../lib_${TRICK_HOST_CPU}/liblog.a \
  ../../../lib_${TRICK_HOST_CPU}/libvar.a \
  ../../../lib_${TRICK_HOST_CPU}/libeqparse.a


# Dependencies

#######################################################################
# To update dependencies:
# - Save changes (if any)
# - run "make depend"
#######################################################################
# DO NOT DELETE
