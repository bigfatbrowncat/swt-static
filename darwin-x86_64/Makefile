# Makefile for SWT libraries on Cocoa/Mac

include make_common.mak

LIBNAME="SWT static"
JAVA_SOURCE_PATH = .
TARGET = target
JAVA_CLASSPATH = $(TARGET)/classes
OBJ = $(TARGET)/obj
JAVA_HOME = $(shell /usr/libexec/java_home)

SWT_VERSION=$(maj_ver)$(min_ver)

# Uncomment for Native Stats tool
#NATIVE_STATS = -DNATIVE_STATS

CFLAGS = -c -xobjective-c -Wall $(ARCHS) -DSWT_VERSION=$(SWT_VERSION) $(NATIVE_STATS) $(SWT_DEBUG) -DUSE_ASSEMBLER -DCOCOA -DATOMIC \
	-I /System/Library/Frameworks/JavaVM.framework/Headers \
	-I /System/Library/Frameworks/Cocoa.framework/Headers \
	-I /System/Library/Frameworks/JavaScriptCore.framework/Headers
LFLAGS = -bundle $(ARCHS) -framework Cocoa -framework WebKit -framework CoreServices -framework JavaScriptCore -framework Security -framework SecurityInterface

SWT_OBJECTS = $(OBJ)/swt.o $(OBJ)/c.o $(OBJ)/c_stats.o $(OBJ)/callback.o
SWTPI_OBJECTS = $(OBJ)/os.o $(OBJ)/os_structs.o $(OBJ)/os_stats.o $(OBJ)/os_custom.o

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

swt_lib: $(SWT_OBJECTS) $(SWTPI_OBJECTS)
	@echo [$(LIBNAME)] Linking swt...
	cc -o $(TARGET)/libswt.dylib $(LFLAGS) $(SWT_OBJECTS) $(SWTPI_OBJECTS)
	ar rcs $(TARGET)/libswt.a $(SWT_OBJECTS) $(SWTPI_OBJECTS)

clean:
	@echo [$(LIBNAME)] Cleaning everything...
	rm -rf $(TARGET)
	
.SILENT: