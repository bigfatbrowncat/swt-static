# Makefile for SWT libraries on Cocoa/Mac

include make_common.mak

LIBNAME="SWT static"
JAVA_SOURCE_PATH = .
TARGET = target
JAVA_CLASSPATH = $(TARGET)/classes
OBJ = $(TARGET)/obj

SWT_PREFIX=swt
SWTPI_PREFIX=swt-pi
#SWTXULRUNNER_PREFIX=swt-xulrunner
#SWTXULRUNNER24_PREFIX=swt-xulrunner24
WS_PREFIX=cocoa
SWT_VERSION=$(maj_ver)$(min_ver)
SWT_LIB=lib$(SWT_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION)
SWTPI_LIB=lib$(SWTPI_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION)
XULRUNNER_LIB=lib$(SWTXULRUNNER_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION)
XULRUNNER24_LIB=lib$(SWTXULRUNNER24_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION)

#AWT_PREFIX = swt-awt
#AWT_LIB    = lib$(AWT_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION).jnilib
#AWT_LIBS   = /System/Library/Frameworks/JavaVM.framework/Versions/CurrentJDK/Libraries/libjawt.dylib"
#AWT_OBJECTS   = swt_awt.o

# Uncomment for Native Stats tool
#NATIVE_STATS = -DNATIVE_STATS

#SWT_DEBUG = -g
CFLAGS = -c -xobjective-c -Wall $(ARCHS) -DSWT_VERSION=$(SWT_VERSION) $(NATIVE_STATS) $(SWT_DEBUG) -DUSE_ASSEMBLER -DCOCOA -DATOMIC \
	-I /System/Library/Frameworks/JavaVM.framework/Headers \
	-I /System/Library/Frameworks/Cocoa.framework/Headers \
	-I /System/Library/Frameworks/JavaScriptCore.framework/Headers
LFLAGS = -bundle $(ARCHS) -framework JavaVM -framework Cocoa -framework WebKit -framework CoreServices -framework JavaScriptCore -framework Security -framework SecurityInterface
SWT_OBJECTS = $(OBJ)/swt.o $(OBJ)/c.o $(OBJ)/c_stats.o $(OBJ)/callback.o
SWTPI_OBJECTS = $(OBJ)/swt.o $(OBJ)/os.o $(OBJ)/os_structs.o $(OBJ)/os_stats.o $(OBJ)/os_custom.o
#XULRUNNER_OBJECTS = swt.o xpcom.o xpcom_custom.o xpcom_structs.o xpcom_stats.o xpcominit.o xpcominit_structs.o xpcominit_stats.o
#XULRUNNER24_OBJECTS = xpcom24_custom.o

#XULRUNNERCFLAGS = -c -Wall $(ARCHS) -DSWT_VERSION=$(SWT_VERSION) $(NATIVE_STATS) $(SWT_DEBUG) -DUSE_ASSEMBLER -DCOCOA -I /System/Library/Frameworks/JavaVM.framework/Headers \
#	-Wno-non-virtual-dtor -include ${XULRUNNER_SDK}/include/mozilla-config.h -I${XULRUNNER_SDK}/include
#XULRUNNER24CFLAGS = -c -Wall $(XULRUNNER24_ARCHS) -DSWT_VERSION=$(SWT_VERSION) $(NATIVE_STATS) $(SWT_DEBUG) -DUSE_ASSEMBLER -DCOCOA -I /System/Library/Frameworks/JavaVM.framework/Headers -Wno-non-virtual-dtor
#XULRUNNERLFLAGS = $(LFLAGS)
#XULRUNNER24LFLAGS = -bundle $(XULRUNNER24_ARCHS) -framework JavaVM

JAVA_FILES = $(shell cd $(JAVA_SOURCE_PATH); find . -type f -name \*.java | awk '{ sub(/.\//,"") }; 1')
JAVA_CLASSES = $(addprefix $(JAVA_CLASSPATH)/,$(addsuffix .class,$(basename $(JAVA_FILES))))

all: swt_lib swtpi_lib $(JAVA_CLASSES)

$(JAVA_CLASSPATH)/%.class: $(JAVA_SOURCE_PATH)/%.java
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	"$(JAVA_HOME)/bin/javac" -encoding utf8 -sourcepath "$(JAVA_SOURCE_PATH)" -classpath "$(JAVA_CLASSPATH)" -d "$(JAVA_CLASSPATH)" $<

$(OBJ)/%.o: %.c
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	gcc $(CFLAGS) $< -o $@


#$(AWT_LIB): $(AWT_OBJECTS)
#	cc -o $(AWT_LIB) $(LFLAGS) $(AWT_OBJECTS)

swt_lib: $(SWT_OBJECTS)
	@echo [$(LIBNAME)] Linking swt...
	cc -o $(TARGET)/$(SWT_LIB).dylib $(LFLAGS) $(SWT_OBJECTS)
	ar rcs $(TARGET)/$(SWT_LIB).a $(SWT_OBJECTS)

swtpi_lib: $(SWTPI_OBJECTS)
	@echo [$(LIBNAME)] Linking swt...
	cc -o $(TARGET)/$(SWTPI_LIB).dylib $(LFLAGS) $(SWTPI_OBJECTS)
	ar rcs $(TARGET)/$(SWTPI_LIB).a $(SWTPI_OBJECTS)

#$(XULRUNNER_LIB): $(XULRUNNER_OBJECTS)
#	g++ -o $(XULRUNNER_LIB) $(XULRUNNERLFLAGS) $(XULRUNNER_LIBS) $(XULRUNNER_OBJECTS)

#xpcom.o: xpcom.cpp
#	g++ $(XULRUNNERCFLAGS) xpcom.cpp
#xpcom_custom.o: xpcom_custom.cpp
#	g++ $(XULRUNNERCFLAGS) xpcom_custom.cpp
#xpcom_structs.o: xpcom_structs.cpp
#	g++ $(XULRUNNERCFLAGS) xpcom_structs.cpp
#xpcom_stats.o: xpcom_stats.cpp
#	g++ $(XULRUNNERCFLAGS) xpcom_stats.cpp
#xpcominit.o: xpcominit.cpp
#	g++ $(XULRUNNERCFLAGS) xpcominit.cpp
#xpcominit_structs.o: xpcominit_structs.cpp
#	g++ $(XULRUNNERCFLAGS) xpcominit_structs.cpp
#xpcominit_stats.o: xpcominit_stats.cpp
#	g++ $(XULRUNNERCFLAGS) xpcominit_stats.cpp

#$(XULRUNNER24_LIB): $(XULRUNNER24_OBJECTS)
#	g++ -o $(XULRUNNER24_LIB) $(XULRUNNER24LFLAGS) $(XULRUNNER24_LIBS) $(XULRUNNER24_OBJECTS)

#xpcom24_custom.o: xpcom24_custom.cpp
#	g++ $(XULRUNNER24CFLAGS) xpcom24_custom.cpp

clean:
	@echo [$(LIBNAME)] Cleaning everything...
	rm -rf $(TARGET)
	
.SILENT: