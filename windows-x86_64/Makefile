# Makefile for SWT libraries on mingw-w64

# External variables that should be set:
#	JAVA_HOME

maj_ver=4
min_ver=430
comma_ver=4,4,3,0

LIBNAME="SWT static"
JAVA_SOURCE_PATH = .
TARGET = target
JAVA_CLASSPATH = $(TARGET)/classes
OBJ = $(TARGET)/obj

SWT_LIBS   = -lcomctl32 -lshell32 -limm32 -loleacc -lusp10 -lwininet -lcrypt32 -lshlwapi
GDIP_LIBS  = -lgdiplus
WGL_LIBS   = -lopengl32
SWT_OBJS   = $(OBJ)/swt.o $(OBJ)/callback.o $(OBJ)/c.o $(OBJ)/c_stats.o $(OBJ)/os.o $(OBJ)/os_structs.o $(OBJ)/os_custom.o $(OBJ)/os_stats.o $(OBJ)/com_structs.o $(OBJ)/com.o $(OBJ)/com_stats.o $(OBJ)/com_custom.o $(OBJ)/os_ext.o
GDIP_OBJS  = $(OBJ)/gdip.o $(OBJ)/gdip_structs.o $(OBJ)/gdip_stats.o $(OBJ)/gdip_custom.o
WGL_OBJS   = $(OBJ)/wgl.o $(OBJ)/wgl_structs.o $(OBJ)/wgl_stats.o

#AWT_PREFIX = swt-awt
#AWT_LIB    = $(AWT_PREFIX)-$(WS_PREFIX)-$(SWT_VERSION).lib
#AWT_LIBS   = "$(JAVA_HOME)\jre\bin\jawt.lib"
#AWT_OBJS   = swt_awt.o


# Uncomment for Native Stats tool
#NATIVE_STATS = -DNATIVE_STATS

SWT_VERSION = $(maj_ver)$(min_ver)
NMAKE_WINVER := 0x0502
WFLAGS := -D_WINNT -D_WIN32_WINNT=$(NMAKE_WINVER) -D_WIN32_IE=0x0600 -DNTDDI_VERSION=$(NMAKE_WINVER)0000 -D_AMD64_=1 -DWIN64 -D_WIN64 -DWIN32 -D_WIN32
WGUILIBS := -lkernel32 -ladvapi32 -luser32 -lgdi32 -lcomdlg32 -lwinspool
WOLELIBS := -lole32 -luuid -loleaut32

CFLAGS := $(WFLAGS) -c -O2 -DJNI64 -DNDEBUG $(CFLAGS) -DSWT_VERSION=$(SWT_VERSION) $(NATIVE_STATS) -DUSE_ASSEMBLER -I"$(JAVA_HOME)/include" -I"$(JAVA_HOME)/include/win32" -I.
RCFLAGS := -DSWT_FILE_VERSION=\"$(maj_ver).$(min_ver)\" -DSWT_COMMA_VERSION=$(comma_ver)

JAVA_FILES = $(shell cd $(JAVA_SOURCE_PATH); find . -type f -name \*.java | awk '{ sub(/.\//,"") }; 1')
JAVA_PROPS_SRC = $(shell cd $(JAVA_SOURCE_PATH); find . -type f -name \*.properties | awk '{ sub(/.\//,"") }; 1')
JAVA_CLASSES = $(addprefix $(JAVA_CLASSPATH)/,$(addsuffix .class,$(basename $(JAVA_FILES))))
JAVA_PROPS = $(addprefix $(JAVA_CLASSPATH)/,$(addsuffix .properties,$(basename $(JAVA_PROPS_SRC))))

all: swt_lib $(JAVA_CLASSES) $(JAVA_PROPS)

$(JAVA_CLASSPATH)/%.properties: $(JAVA_SOURCE_PATH)/%.properties
	@echo [$(LIBNAME)] Copying $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	cp -f $< $@

$(JAVA_CLASSPATH)/%.class: $(JAVA_SOURCE_PATH)/%.java
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	"$(JAVA_HOME)/bin/javac" -encoding utf8 -sourcepath "$(JAVA_SOURCE_PATH)" -classpath "$(JAVA_CLASSPATH)" -d "$(JAVA_CLASSPATH)" $<

$(OBJ)/%.o: %.c
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	gcc $(CFLAGS) $< -o $@

$(OBJ)/%.o: %.cpp
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	g++ $(CFLAGS) $< -o $@

swt_lib: $(SWT_OBJS) $(GDIP_OBJS) $(WGL_OBJS)
	@echo [$(LIBNAME)] Linking swt...
	echo > templrf
	echo $(SWT_OBJS) >>templrf
	echo $(GDIP_OBJS) >>templrf
	echo $(WGL_OBJS) >>templrf
	echo $(WGUILIBS) $(WOLELIBS) >>templrf
	echo $(SWT_LIBS) >>templrf
	echo $(GDIP_LIBS) >>templrf
	echo $(WGL_LIBS) >>templrf
	g++ -static -mdll -mwindows -o $(TARGET)/swt.dll @templrf
	ar rs $(TARGET)/libswt.a $(SWT_OBJS) $(GDIP_OBJS) $(WGL_OBJS)
	rm templrf

#make_awt: $(AWT_OBJS) swt_awt.res
#	echo $(ldebug) $(dlllflags) $(guilibsmt) >templrf
#	echo $(AWT_LIBS) >>templrf
#	echo $(AWT_OBJS) >>templrf
#	echo swt_awt.res >>templrf
#	echo -out:$(AWT_LIB) >>templrf
#	"$(VC_PATH)"/bin/lib $(API_LINKS) @templrf
#	rm templrf


#$(OBJ)/swt.rc: swt.res
#	windres $(RCFLAGS) -DSWT_ORG_FILENAME=\"$(SWT_LIB)\" -i $< -o $@

#swt_gdip.res:
#	rc $(RCFLAGS) -DSWT_ORG_FILENAME=\"$(GDIP_LIB)\" -r -fo swt_gdip.res swt_gdip.rc

#swt_awt.res:
#	rc $(RCFLAGS) -DSWT_ORG_FILENAME=\"$(AWT_LIB)\" -r -fo swt_awt.res swt_awt.rc

#swt_wgl.res:
#	rc $(RCFLAGS) -DSWT_ORG_FILENAME=\"$(WGL_LIB)\" -r -fo swt_wgl.res swt_wgl.rc

clean:
	@echo [$(LIBNAME)] Cleaning everything...
	rm -rf $(TARGET)
	
.SILENT: