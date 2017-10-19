#
# Fazal Mirza DEMO 1
# Makefile

ifdef INCLUDE_MAKEFILE
	include $(INCLUDE_MAKEFILE)
endif

COMPLIER ?= gcc
LINKER   ?= gcc
ARCHIVE  ?= ar

CC=$(COMPLIER)
CFLAGS= -Wall -ggdb -O0

INCLUDE:= -Iinclude/

#SOURCE:= functions/add.c \
#         functions/div.c \
#         functions/mul.c \
#         functions/sub.c \
#         main/mainapp.c
# Or we can also use wildcard

SOURCE:= $(wildcard functions/*.c) \
         $(wildcard main/*.c)
		
EXE=mainapp            

all: $(EXE)

$(EXE):
	$(CC) $(CFLAGS) $(INCLUDE) $(SOURCE) -o $(EXE)

clean:
	rm -rf $(EXE)
	
#---------------------------------------------info -----------------------------------------------------	
#Lazy Set
#VARIABLE = value
#Normal setting of a variable - values within it are recursively expanded when the variable is used, not when it's declared

#Immediate Set
#VARIABLE := value
#Setting of a variable with simple expansion of the values inside - values within it are expanded at declaration time.

#Set If Absent
#VARIABLE ?= value
#Setting of a variable only if it doesn't have a value

#Append
#VARIABLE += value
#Appending the supplied value to the existing value (or setting to that value if the variable didn't exist)	

#-------------------- using += (append)------------------------------
#
# HELLO_WORLD = hello
#HELLO_WORLD += world!

# This echoes "hello world!"
#echo $(HELLO_WORLD)
#
#--------------------- using = (equals)-----------------------------

#HELLO = world
#HELLO_WORLD = $(HELLO) world!

# This echoes "world world!"
#echo $(HELLO_WORLD)

#HELLO = hello

# This echoes "hello world!"
#echo $(HELLO_WORLD)

#-----------------------using := ---------------------------
#HELLO = world
#HELLO_WORLD := $(HELLO) world!

# This echoes "world world!"
#echo $(HELLO_WORLD)

#HELLO = hello

# Still echoes "world world!"
#echo $(HELLO_WORLD)

#HELLO_WORLD := $(HELLO) world!

# This echoes "hello world!"
#echo $(HELLO_WORLD)
#--------------------------------------------------