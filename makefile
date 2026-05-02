SRV = server_code/server
GAME = game_code/game

# <--- DIRECTORIES ---> #
SRV_SRC_DIRS = server_code/srcs/srcs_processes server_code/srcs/srcs_db server_code/srcs/srcs_server server_code/srcs/srcs_aux
SRV_HDR_DIRS = server_code/hdrs/hdrs_aux server_code/hdrs/hdrs_db server_code/hdrs/hdrs_server server_code/hdrs/hdrs_thread

GAME_SRC_DIRS = game_code/srcs/srcs_aux game_code/srcs/srcs_game game_code/srcs/srcs_server game_code/srcs/srcs_hashtable game_code/srcs/srcs_processes
GAME_HDR_DIRS = game_code/hdrs/hdrs_aux game_code/hdrs/hdrs_hashtable game_code/hdrs/hdrs_server game_code/hdrs/hdrs_structs game_code/hdrs/hdrs_processes

SRV_INCLUDE_HDRS = $(addprefix -I, $(SRV_HDR_DIRS)) -Ihdrs
SRV_OBJ_DIR = server_code/obj

GAME_INCLUDE_HDRS = $(addprefix -I, $(GAME_HDR_DIRS)) -Ihdrs
GAME_OBJ_DIR = game_code/obj

# <--- COMPILER AND FLAGS ---> #
CC = gcc
SRV_CFLAGS = -Wall -lpthread $(SRV_INCLUDE_HDRS) $(shell mysql_config --cflags)
GAME_CFLAGS = -Wall -lpthread $(GAME_INCLUDE_HDRS) $(shell mysql_config --cflags)

LDFLAGS = $(shell mysql_config --libs)

# <--- SOURCES AND OBJECTS ---> #
SRV_SRC = $(foreach dir, $(SRV_SRC_DIRS), $(wildcard $(dir)/*.c))
SRV_OBJ = $(addprefix $(SRV_OBJ_DIR)/, $(notdir $(SRV_SRC:.c=.o)))
vpath %.c $(SRV_SRC_DIRS)

GAME_SRC = $(foreach dir, $(GAME_SRC_DIRS), $(wildcard $(dir)/*.c))
GAME_OBJ = $(addprefix $(GAME_OBJ_DIR)/, $(notdir $(GAME_SRC:.c=.o)))
vpath %.c $(GAME_SRC_DIRS)

# <--- ALL ---> #
all: server game

# <--- SERVER ---> #
server: $(SRV_OBJ)
	$(CC) $(SRV_CFLAGS) $(SRV_OBJ) -o $(SRV) $(LDFLAGS)

$(SRV_OBJ_DIR)/%.o: %.c | $(SRV_OBJ_DIR)
	$(CC) $(SRV_CFLAGS) -c $< -o $@

$(SRV_OBJ_DIR):
	mkdir -p $(SRV_OBJ_DIR)


# <--- GAME ---> #
game: $(GAME_OBJ)
	$(CC) $(GAME_CFLAGS) $(GAME_OBJ) -o $(GAME) $(LDFLAGS)

$(GAME_OBJ_DIR)/%.o: %.c | $(GAME_OBJ_DIR)
	$(CC) $(GAME_CFLAGS) -c $< -o $@

$(GAME_OBJ_DIR):
	mkdir -p $(GAME_OBJ_DIR)


# <--- CLEAN ---> #
clean: clean_game clean_server

clean_server:
	rm -rf $(SRV_OBJ_DIR)
	rm -f $(SRV)

clean_game:
	rm -rf $(GAME_OBJ_DIR)
	rm -f $(GAME)

.PHONY: all server game clean clean_server clean_game 
