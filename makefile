NAME = rpg_game

# --- DIRECTORIES --- #
SRC_DIRS = srcs/srcs_aux srcs/srcs_game srcs/srcs_server srcs/srcs_hashtable srcs/srcs_processes
HDR_DIRS = hdrs/hdrs_aux hdrs/hdrs_hashtable hdrs/hdrs_server hdrs/hdrs_structs hdrs/hdrs_processes

INCLUDE_HDRS = $(addprefix -I, $(HDR_DIRS)) -Ihdrs

OBJ_DIR = obj

# --- COMPILER AND FLAGS --- #
CC = gcc
CFLAGS = -Wall -Wextra $(INCLUDE_HDRS) -lpthread 

# --- SOURCES AND OBJECTS --- #
SRC = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))
OBJ = $(patsubst %.c, $(OBJ_DIR)/%.o, $(notdir $(SRC)))
vpath %.c $(SRC_DIRS)

# --- COMMANDS --- #
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(NAME)

.PHONY: all clean