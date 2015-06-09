# Makefile for creating SWT libraries for Linux GTK

include make_common.mak

LIBNAME="SWT static"
JAVA_SOURCE_PATH = .
TARGET = target
JAVA_CLASSPATH = $(TARGET)/classes
OBJ = $(TARGET)/obj

SWT_VERSION=$(maj_ver)$(min_ver)
GTK_VERSION?=2.0

CAIROCFLAGS = `pkg-config --cflags cairo`
CAIROLIBS = `pkg-config --libs-only-L cairo` -lcairo

# Do not use pkg-config to get libs because it includes unnecessary dependencies (i.e. pangoxft-1.0)
GTKCFLAGS = `pkg-config --cflags gtk+-$(GTK_VERSION) gtk+-unix-print-$(GTK_VERSION)`
ifeq ($(GTK_VERSION), 3.0)
GTKLIBS = `pkg-config --libs-only-L gtk+-$(GTK_VERSION) gthread-2.0` $(XLIB64) -L/usr/X11R6/lib -lgtk-3 -lgdk-3 -lcairo -lgthread-2.0 -lXtst
else
GTKLIBS = `pkg-config --libs-only-L gtk+-$(GTK_VERSION) gthread-2.0` $(XLIB64) -L/usr/X11R6/lib -lgtk-x11-$(GTK_VERSION) -lgthread-2.0 -lXtst
endif

CDE_LIBS = -L$(CDE_HOME)/lib -R$(CDE_HOME)/lib -lXt -lX11 -lDtSvc

ATKCFLAGS = `pkg-config --cflags atk gtk+-$(GTK_VERSION) gtk+-unix-print-$(GTK_VERSION)`
ATKLIBS = `pkg-config --libs-only-L atk` -latk-1.0 

#GNOMECFLAGS = `pkg-config --cflags gnome-vfs-module-2.0 libgnome-2.0 libgnomeui-2.0`
#GNOMELIBS = `pkg-config --libs-only-L gnome-vfs-module-2.0 libgnome-2.0 libgnomeui-2.0` -lgnomevfs-2 -lgnome-2 -lgnomeui-2

GLXLIBS = -lGL -lGLU -lm

# Uncomment for Native Stats tool
#NATIVE_STATS = -DNATIVE_STATS

SWT_OBJECTS = $(OBJ)/swt.o $(OBJ)/c.o $(OBJ)/c_stats.o $(OBJ)/callback.o
CDE_OBJECTS = $(OBJ)/cde.o $(OBJ)/cde_structs.o $(OBJ)/cde_stats.o
SWTPI_OBJECTS = $(OBJ)/os.o $(OBJ)/os_structs.o $(OBJ)/os_custom.o $(OBJ)/os_stats.o
CAIRO_OBJECTS = $(OBJ)/cairo.o $(OBJ)/cairo_structs.o $(OBJ)/cairo_stats.o
ATK_OBJECTS = $(OBJ)/atk.o $(OBJ)/atk_structs.o $(OBJ)/atk_custom.o $(OBJ)/atk_stats.o
GNOME_OBJECTS = $(OBJ)/gnome.o $(OBJ)/gnome_structs.o $(OBJ)/gnome_stats.o
GLX_OBJECTS = $(OBJ)/glx.o $(OBJ)/glx_structs.o $(OBJ)/glx_stats.o
ALL_OBJECTS = $(SWT_OBJECTS) $(SWTPI_OBJECTS) $(CAIRO_OBJECTS) $(ATK_OBJECTS) $(GLX_OBJECTS) 
#$(GNOME_OBJECTS)$(CDE_OBJECTS)

CFLAGS = -O -Wall \
		-DSWT_VERSION=$(SWT_VERSION) \
		$(NATIVE_STATS) \
		-DLINUX -DGTK \
		-I$(JAVA_HOME)/include \
		-I$(JAVA_HOME)/include/linux \
		-fPIC

LFLAGS = -shared -fPIC $(CAIROLIBS) $(GTKLIBS) $(GNOMELIBS) $(GLXLIBS)

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

#
# SWT libs
#
swt_lib: $(ALL_OBJECTS)
	@echo [$(LIBNAME)] Linking swt...
	cc -o $(TARGET)/libswt.so $(LFLAGS) $(ALL_OBJECTS)
	ar rcs $(TARGET)/libswt.a $(ALL_OBJECTS)

$(OBJ)callback.o: callback.c callback.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) -DUSE_ASSEMBLER -c callback.c -o $@

$(OBJ)/swt.o: swt.c swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) -c swt.c -o $@
$(OBJ)/os.o: os.c os.h swt.h os_custom.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c os.c -o $@
$(OBJ)/os_structs.o: os_structs.c os_structs.h os.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c os_structs.c  -o $@
$(OBJ)/os_custom.o: os_custom.c os_structs.h os.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c os_custom.c -o $@
$(OBJ)/os_stats.o: os_stats.c os_structs.h os.h os_stats.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GTKCFLAGS) -c os_stats.c -o $@

#
# CAIRO libs
#

$(OBJ)/cairo.o: cairo.c cairo.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(CAIROCFLAGS) -c cairo.c -o $@
$(OBJ)/cairo_structs.o: cairo_structs.c cairo_structs.h cairo.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(CAIROCFLAGS) -c cairo_structs.c -o $@
$(OBJ)/cairo_stats.o: cairo_stats.c cairo_structs.h cairo.h cairo_stats.h swt.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(CAIROCFLAGS) -c cairo_stats.c -o $@

#
# CDE lib
#



#
# Atk lib
#

$(OBJ)/atk.o: atk.c atk.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(ATKCFLAGS) -c atk.c -o $@
$(OBJ)/atk_structs.o: atk_structs.c atk_structs.h atk.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(ATKCFLAGS) -c atk_structs.c -o $@
$(OBJ)/atk_custom.o: atk_custom.c atk_structs.h atk.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(ATKCFLAGS) -c atk_custom.c -o $@
$(OBJ)/atk_stats.o: atk_stats.c atk_structs.h atk_stats.h atk.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(ATKCFLAGS) -c atk_stats.c -o $@

#
# Gnome lib
#

$(OBJ)/gnome.o: gnome.c 
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GNOMECFLAGS) -c gnome.c -o $@

$(OBJ)/gnome_structs.o: gnome_structs.c 
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GNOMECFLAGS) -c gnome_structs.c -o $@
	
$(OBJ)/gnome_stats.o: gnome_stats.c gnome_stats.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GNOMECFLAGS) -c gnome_stats.c -o $@

#
# GLX lib
#

$(OBJ)/glx.o: glx.c 
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GLXCFLAGS) -c glx.c -o $@

$(OBJ)/glx_structs.o: glx_structs.c 
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GLXCFLAGS) -c glx_structs.c -o $@
	
$(OBJ)/glx_stats.o: glx_stats.c glx_stats.h
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) $(GLXCFLAGS) -c glx_stats.c -o $@

# Others

$(OBJ)/%.o: %.c
	@echo [$(LIBNAME)] Compiling $<...
	if [ ! -d "$(dir $@)" ]; then mkdir -p "$(dir $@)"; fi
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo [$(LIBNAME)] Cleaning everything...
	rm -rf $(TARGET)
	
#.SILENT:
