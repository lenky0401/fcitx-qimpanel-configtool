#############################################################################
# Makefile for building: fcitx-qimpanel-configtool
# Generated by qmake (2.01a) (Qt 4.8.4) on: Tue Nov 12 12:46:58 2013
# Project:  fcitx-qimpanel-configtool.pro
# Template: app
# Command: /usr/lib/i386-linux-gnu/qt4/bin/qmake -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile fcitx-qimpanel-configtool.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_DECLARATIVE_DEBUG -DQT_DECLARATIVE_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtDeclarative -I/usr/include/qt4 -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -lfcitx-qt -lfcitx-config -lfcitx-utils -lQtDeclarative -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/i386-linux-gnu/qt4/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = main.cpp \
		mainwindow.cpp \
		main_model.cpp \
		skin/skinbase.cpp \
		skin/skinfcitx.cpp \
		candidate_word.cpp \
		editingskindialog.cpp moc_mainwindow.cpp \
		moc_main_model.cpp \
		moc_skinbase.cpp \
		moc_candidate_word.cpp \
		moc_editingskindialog.cpp \
		qrc_main.cpp
OBJECTS       = main.o \
		mainwindow.o \
		main_model.o \
		skinbase.o \
		skinfcitx.o \
		candidate_word.o \
		editingskindialog.o \
		moc_mainwindow.o \
		moc_main_model.o \
		moc_skinbase.o \
		moc_candidate_word.o \
		moc_editingskindialog.o \
		qrc_main.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		fcitx-qimpanel-configtool.pro
QMAKE_TARGET  = fcitx-qimpanel-configtool
DESTDIR       = 
TARGET        = fcitx-qimpanel-configtool

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h ui_editingskindialog.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)
	{ test -n "$(DESTDIR)" && DESTDIR="$(DESTDIR)" || DESTDIR=.; } && test $$(gdb --version | sed -e 's,[^0-9]\+\([0-9]\)\.\([0-9]\).*,\1\2,;q') -gt 72 && gdb --nx --batch --quiet -ex 'set confirm off' -ex "save gdb-index $$DESTDIR" -ex quit '$(TARGET)' && test -f $(TARGET).gdb-index && objcopy --add-section '.gdb_index=$(TARGET).gdb-index' --set-section-flags '.gdb_index=readonly' '$(TARGET)' '$(TARGET)' && rm -f $(TARGET).gdb-index || true

Makefile: fcitx-qimpanel-configtool.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/declarative_debug.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/i386-linux-gnu/libQtDeclarative.prl \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile fcitx-qimpanel-configtool.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/declarative_debug.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/i386-linux-gnu/libQtDeclarative.prl:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ CONFIG+=debug CONFIG+=declarative_debug -o Makefile fcitx-qimpanel-configtool.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/fcitx-qimpanel-configtool1.0.0 || $(MKDIR) .tmp/fcitx-qimpanel-configtool1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/fcitx-qimpanel-configtool1.0.0/ && $(COPY_FILE) --parents mainwindow.h main_model.h skin/skinbase.h kimpanelagenttype.h candidate_word.h editingskindialog.h skin/skinfcitx.h .tmp/fcitx-qimpanel-configtool1.0.0/ && $(COPY_FILE) --parents main.qrc .tmp/fcitx-qimpanel-configtool1.0.0/ && $(COPY_FILE) --parents main.cpp mainwindow.cpp main_model.cpp skin/skinbase.cpp skin/skinfcitx.cpp candidate_word.cpp editingskindialog.cpp .tmp/fcitx-qimpanel-configtool1.0.0/ && $(COPY_FILE) --parents mainwindow.ui editingskindialog.ui .tmp/fcitx-qimpanel-configtool1.0.0/ && (cd `dirname .tmp/fcitx-qimpanel-configtool1.0.0` && $(TAR) fcitx-qimpanel-configtool1.0.0.tar fcitx-qimpanel-configtool1.0.0 && $(COMPRESS) fcitx-qimpanel-configtool1.0.0.tar) && $(MOVE) `dirname .tmp/fcitx-qimpanel-configtool1.0.0`/fcitx-qimpanel-configtool1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/fcitx-qimpanel-configtool1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_mainwindow.cpp moc_main_model.cpp moc_skinbase.cpp moc_candidate_word.cpp moc_editingskindialog.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_mainwindow.cpp moc_main_model.cpp moc_skinbase.cpp moc_candidate_word.cpp moc_editingskindialog.cpp
moc_mainwindow.cpp: skin/skinbase.h \
		skin/skinfcitx.h \
		main_model.h \
		kimpanelagenttype.h \
		candidate_word.h \
		editingskindialog.h \
		mainwindow.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) mainwindow.h -o moc_mainwindow.cpp

moc_main_model.cpp: kimpanelagenttype.h \
		candidate_word.h \
		main_model.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) main_model.h -o moc_main_model.cpp

moc_skinbase.cpp: skin/skinbase.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) skin/skinbase.h -o moc_skinbase.cpp

moc_candidate_word.cpp: candidate_word.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) candidate_word.h -o moc_candidate_word.cpp

moc_editingskindialog.cpp: skin/skinfcitx.h \
		skin/skinbase.h \
		editingskindialog.h
	/usr/lib/i386-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) editingskindialog.h -o moc_editingskindialog.cpp

compiler_rcc_make_all: qrc_main.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_main.cpp
qrc_main.cpp: main.qrc \
		main.qml
	/usr/lib/i386-linux-gnu/qt4/bin/rcc -name main main.qrc -o qrc_main.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_editingskindialog.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_editingskindialog.h
ui_mainwindow.h: mainwindow.ui
	/usr/lib/i386-linux-gnu/qt4/bin/uic mainwindow.ui -o ui_mainwindow.h

ui_editingskindialog.h: editingskindialog.ui
	/usr/lib/i386-linux-gnu/qt4/bin/uic editingskindialog.ui -o ui_editingskindialog.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

main.o: main.cpp mainwindow.h \
		skin/skinbase.h \
		skin/skinfcitx.h \
		main_model.h \
		kimpanelagenttype.h \
		candidate_word.h \
		editingskindialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.h \
		skin/skinbase.h \
		skin/skinfcitx.h \
		main_model.h \
		kimpanelagenttype.h \
		candidate_word.h \
		editingskindialog.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

main_model.o: main_model.cpp main_model.h \
		kimpanelagenttype.h \
		candidate_word.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main_model.o main_model.cpp

skinbase.o: skin/skinbase.cpp skin/skinbase.h \
		main_model.h \
		kimpanelagenttype.h \
		candidate_word.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o skinbase.o skin/skinbase.cpp

skinfcitx.o: skin/skinfcitx.cpp skin/skinfcitx.h \
		skin/skinbase.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o skinfcitx.o skin/skinfcitx.cpp

candidate_word.o: candidate_word.cpp candidate_word.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o candidate_word.o candidate_word.cpp

editingskindialog.o: editingskindialog.cpp editingskindialog.h \
		skin/skinfcitx.h \
		skin/skinbase.h \
		ui_editingskindialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o editingskindialog.o editingskindialog.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

moc_main_model.o: moc_main_model.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_main_model.o moc_main_model.cpp

moc_skinbase.o: moc_skinbase.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_skinbase.o moc_skinbase.cpp

moc_candidate_word.o: moc_candidate_word.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_candidate_word.o moc_candidate_word.cpp

moc_editingskindialog.o: moc_editingskindialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_editingskindialog.o moc_editingskindialog.cpp

qrc_main.o: qrc_main.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_main.o qrc_main.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

