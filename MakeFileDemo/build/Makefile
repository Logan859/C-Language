# Fazal Mirza DEMO 2
# My Makefile

ifdef INCLUDE_MAKEFILE
	include $(INCLUDE_MAKEFILE)
endif	

COMPLIER ?= gcc
LINKER   ?= gcc
ARCHIVE  ?= ar

ARCHIVE_EXTENSION ?= .a

CC = $(COMPLIER)
LD = $(LINKER)
SHELL = /bin/sh

.PHONY: clean

ifneq ($(CURDIR), $(shell dirname $(abspath $(lastword $(MAKEFILE_LIST)))))
$(error... This make file should be invoked in its current directory ($(shell dirname $(abspath $(lastword $(MAKEFILE_LIST)))))
endif

COMPLIER_INCLUDES ?=

INCLUDE = \
  $(COMPLIER_INCLUDES)\
  -I./.. \
  -I./../functions \
  -I./../main \

BUILD_OUTPUT_DIR =.
BUILD_CONFIG_FILE = $(BUILD_OUTPUT_DIR)/
BUILD_MAIN_FILE ?= \"../main/mainapp.h\" 

DEFINES = \
  $(COMPILER_DEFINES) \
  -DUNIX \
  -DFORTEST \
  -DMAINHEADER=$(BUILD_MAIN_FILE) \
  
COMPILER_FLAG ?= \
  -Wall \
  -ggdb \
  -O0
 
APPLICATION_FILES = \
  ../functions/add.c \
  ../functions/sub.c \
  ../functions/div.c \
  ../functions/mul.c \
  ../main/mainapp.c
  
LIBRARIES = \
  \
  
OUTPUT_DIR = $(BUILD_OUTPUT_DIR)/output
OUTPUT_DIR_CREATED = $(OUTPUT_DIR)/created
EXE_DIR = $(OUTPUT_DIR)/exe



APPLICATION_OBJECTS = $(shell echo $(APPLICATION_FILES) | xargs -n1 echo | sed -e 's^.*/\(.*\)\.c^$(OUTPUT_DIR)/\1\.o^')


ifdef GENERATE_LIBRARY
TARGET_FILE= $(EXE_DIR)/myapp$(ARCHIVE_EXTENSION)
else
TARGET_FILE= $(EXE_DIR)/myapp
endif


# -MMD and -MF generates Makefile dependencies while at the same time compiling.
# -MP notes to add a dummy 'build' rule for each header file.  This 
# prevent a problem where a removed header file will generate an error because a
# dependency references it but it can't be found anymore.
DEPENDENCY_FLAGS ?= -MMD -MP -MF $(@D)/$*.d


# Dependency post process is a way to massage generated dependencies.
# This is necessary for example when using Make under Cygwin but compiling
# using a native Windows compiler that generates native Windows paths
# that Cygwin will choke on.  Or if compiling on Linux using Wine to run a 
# Windows compiler, a similar problem can occur.  
DEPENDENCY_POST_PROCESS ?=


CPPFLAGS= $(INCLUDES) $(DEFINES) $(COMPILER_FLAGS) $(DEPENDENCY_FLAGS)

LINKER_FLAGS ?=

ifdef NO_READLINE
  CPPFLAGS += -DNO_READLINE
else
  LINKER_FLAGS += -lreadline \
	-lncurses \
	-lrt
endif

ARCHIVE_FLAGS ?= rus


# Rules

all: $(TARGET_FILE)


ifneq ($(MAKECMDGOALS),clean)
-include $(APPLICATION_OBJECTS:.o=.d)
endif


ifdef GENERATE_LIBRARY
$(TARGET_FILE): $(APPLICATION_OBJECTS) $(LIBRARIES)
	$(ARCHIVE) $(ARCHIVE_FLAGS) $(TARGET_FILE) $^
	@echo -e '\n$@ build success'
else
$(TARGET_FILE): $(APPLICATION_OBJECTS) $(LIBRARIES)
	$(LD) $^ $(LINKER_FLAGS) -o $(TARGET_FILE)
	@echo -e '\n$@ build success'
endif


clean:
	rm -rf $(OUTPUT_DIR)
	
$(OUTPUT_DIR_CREATED):
	mkdir -p $(OUTPUT_DIR)
	mkdir -p $(EXE_DIR)
	touch $(OUTPUT_DIR_CREATED)
	
# To facilitate generating all output files in a single output directory, we
# must create separate .o and .d rules for all the different sub-directories
# used by the source files.
# If additional directories are added that are not already in the
# $(APPLICATION_FILES) above, new rules will have to be created below.

# Object File rules

VPATH += $(dir $(APPLICATION_FILES))

$(OUTPUT_DIR)/%.o: %.c $(OUTPUT_DIR_CREATED)
	$(CC) $(CPPFLAGS) -c $< -o $(OUTPUT_DIR)/$(@F)
	$(DEPENDENCY_POST_PROCESS)

# Dependency rules
# No explicit rules.  Dependencies are generated as part of the compile step.