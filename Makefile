ROM_NAME = minesweeper.gb

SRC_DIR = ./src
DIST_DIR = ./dist
OBJ_DIR = ./obj
ASSET_DIR = ./assets

CC = lcc

ROM_FILE = $(DIST_DIR)/$(ROM_NAME)

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
ASSET_FILES = $(wildcard $(ASSET_DIR)/*.c)

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)
OBJ_FILES += $(ASSET_FILES:$(ASSET_DIR)%.c=$(OBJ_DIR)%.o)

.PHONY : all
all: $(ROM_FILE)

$(ROM_FILE): $(OBJ_FILES)
	@mkdir -p $(DIST_DIR)
	$(CC) -o $@ $^

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $<

$(OBJ_DIR)/%.o : $(ASSET_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c -o $@ $<

.PHONY : clean
clean:
	@rm -rf $(DIST_DIR)
	@rm -rf $(OBJ_DIR)
