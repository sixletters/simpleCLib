# configs
CC = gcc
LD = gcc
AR = AR
CFLAGS		= -g -std=gnu99 -Wall -Iinclude -fPIC
LDFLAGS		= -Llib
LIBS		= -lm
# ar -rcs is the most likely command you would use 
# when using a Makefile to compile a library. 
# r means that if the library already exists, replace the old files within the library with your new files. c means create the library if it did not exist.
ARFLAGS		= rcs

# Variables
LIB_HDRS = $(wildcard src/include/*.h)
LIB_SRCS = $(wildcard src/library/*.c)
LIB_OBJS = $(LIB_SRCS:.c=.o)
LIBRARY = lib/lib.a

ENTRY_SRCS = src/main.c
ENTRY_OBJS = $(ENTRY_SRCS:.c=.o)
ENTRY = bin/main

TEST_SRCS = $(wildcard src/unittest/*.c)
TEST_OBJS = $(TEST_SRCS:.c=.o)
# path patsubst follows the following form (patsubst pattern,replacement,text)
# the following returns the bin/{test_binaries} from src/unittest, by doing wildcard matching
UNIT_TESTS	= $(patsubst src/unittest/%,bin/%,$(patsubst %.c,%,$(wildcard src/unittest/test_*.c)))

all: $(LIBRARY) $(ENTRY) $(UNIT_TESTS)
# This means that all files ending in .o will be recompiled when the .c file corresponding or library headers have changed
# notice that $< is used here instead of $^
# this means that only one value here is used, which is the first dependant
%.o:		%.c $(LIB_HDRS)
	@echo "Compiling $@ with $^"
	@$(CC) $(CFLAGS) -c -o $@ $<

# This links the library form the lib object files when sfs_lib_objects are recompiled
$(LIBRARY):	$(LIB_OBJS)
	@echo "Linking   $@ with $^"
	@$(AR) $(ARFLAGS) $@ $^

$(ENTRY): $(ENTRY_OBJS) $(LIBRARY)
	@echo "Linking $@ with $^"
	@$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)

bin/test_%: src/unittest/test_%.o $(LIBRARY)
	@echo "Linking $@ with $^"
	@$(LD) $(LDFLAGS) -o $@ $^

sort_tests: bin/test_sort
	@for i in $$(seq 0 3); do \
		echo "running testcase $$i"; \
		./bin/test_sort $$i; \
	done




# gcc -S main.c to produce assembly code 