NAME = rpg_game

# --- DIRECTORIES --- #
SRC_DIRS = srcs/srcs_aux srcs/srcs_game srcs/srcs_server srcs/srcs_hashtable srcs/srcs_processes
HDR_DIRS = hdrs/hdrs_aux hdrs/hdrs_hashtable hdrs/hdrs_server hdrs/hdrs_structs

INCLUDE_HDRS = $(addprefix -I, $(HDR_DIRS)) -Ihdrs

OBJ_DIR = obj

# --- COMPILER AND FLAGS --- #
CC = gcc
CFLAGS = -Wall -Wextra -Ihdrs -lpthread 

# --- SOURCES AND OBJECTS --- #
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))
vpath %.c $(SRC_DIRS)

# --- COMMANDS --- #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

.PHONY: all clean
