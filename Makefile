CC = g++
CFLAGS = -g -Wall -std=c++17 
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
LIB_DIR := lib

EXE := $(BIN_DIR)/nokuplayer

SRC := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/**/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_image -lz -ltag -ltag_c

MKDIR_P = mkdir -p
CP = cp

ifeq ($(OS),Windows_NT)
	RM = rm -rv
	COPY = xcopy /t /e
else
	RM = rm -rf
	COPY = cp -r
endif

.PHONY: all clean

all: copyc $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ -g

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -I include -c $< -o $@ -g

$(BIN_DIR) $(OBJ_DIR):
	$(MKDIR_P) $@

copyc:
	$(COPY) "$(SRC_DIR)" "$(OBJ_DIR)\\"

clean:
	@$(RM) $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)