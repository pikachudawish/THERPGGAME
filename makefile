NAME = rpg_game

CC = gcc
CFLAGS = -Wall -Wextra -Ihdrs -lSDL2 -lpthread $(shell mysql_config --cflags) 
LDFLAGS = $(shell mysql_config --libs)

SRC_DIR = srcs
OBJ_DIR = obj
HDR_DIR = hdrs

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

.PHONY: all clean
