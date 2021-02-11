CSCI_DIR=.
LIB=libcrc.a
PRG=crctest
SRC_DIR=$(CSCI_DIR)/src
INC_DIR=$(CSCI_DIR)/inc
OBJ_DIR=$(CSCI_DIR)/obj
LIB_DIR=$(CSCI_DIR)/lib
EXE_DIR=$(CSCI_DIR)/bin
DEP_DIR=$(CSCI_DIR)/.dep

INCLUDE=-I$(INC_DIR) -I$(NTF_ROOT)/ntfp/inc -I$(NTF_ROOT)/nlog/inc -I$(NTF_ROOT)/mpack/inc

SRC_FILES= \
crc_16.c \
main.c

SRC=$(patsubst %.c, $(SRC_DIR)/%.c, $(SRC_FILES))
OBJ=$(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

CFLAGS=-g -Wall -std=gnu99 
DFLAGS=-MT $@ -MMD -MP -MF $(DEP_DIR)/$*.Td
LFLAGS=

all: create_dir $(LIB) $(PRG)

$(LIB): $(OBJ)
	ar ruv $(LIB_DIR)/$(LIB) $(OBJ)
	ranlib $(LIB_DIR)/$(LIB)
	chmod 755 $(LIB_DIR)/$(LIB)

$(PRG): $(OBJ)
	$(CC) -o $(EXE_DIR)/$(PRG) $(OBJ) $(CFLAGS) $(LFLAGS)

clean:
	rm -f $(PRG) $(OBJ) $(LIB_DIR)/$(LIB) *~ $(LIB_DIR)/*~ $(SRC_DIR)/*~ $(INC_DIR)/*~

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEP_DIR)/$*.d
	$(CC) -c -o $@ $< $(DFLAGS) $(CFLAGS) $(INCLUDE)
	@mv -f $(DEP_DIR)/$*.Td $(DEP_DIR)/$*.d && touch $@

$(DEP_DIR)/$*.d: ;
.PRECIOUS: $(DEP_DIR)/$*.d

.PHONY: create_dir
create_dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(EXE_DIR)
	mkdir -p $(LIB_DIR)
	mkdir -p $(DEP_DIR)

#include dependencies
include $(wildcard $(patsubst %,$(DEP_DIR)/%,$(basename $(SRC))))

