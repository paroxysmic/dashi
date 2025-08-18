SRC_PATH := src
BIN_PATH := bin
OBJ_PATH := obj
DEBUG_PATH := debug
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.c*)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
OBJ_DEBUG := $(addprefix $(DBG_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
all:
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(OBJ_DEBUG)
	