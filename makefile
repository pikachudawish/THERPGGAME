SRV = server
CLI = client

# --- DIRECTORIES --- #
SRV_SRC_DIRS = server_codesrcs/srcs_processes server_codesrcs/srcs/srcs_db server_codesrcs/srcs/srcs_server server_codesrcs/srcs/srcs_aux
SRV_HDR_DIRS = server_codesrcs/hdrs/hdrs_aux server_codesrcs/hdrs/hdrs_db server_codesrcs/hdrs/hdrs_server server_codesrcs/hdrs/hdrs_thread

CLI_SRC_DIRS = game_code/srcs/srcs_aux game_code/srcs/srcs_game game_code/srcs/srcs_server game_code/srcs/srcs_hashtable game_code/srcs/srcs_processes
CLI_HDR_DIRS = game_code/hdrs/hdrs_aux game_code/hdrs/hdrs_hashtable game_code/hdrs/hdrs_server game_code/hdrs/hdrs_structs game_code/hdrs/hdrs_processes

SRV_INCLUDE_HDRS = $(addprefix -I, $(SRV_HDR_DIRS)) -Ihdrs
SRV_OBJ_DIR = srv_obj

CLI_INCLUDE_HDRS = $(addprefix -I, $(CLI_HDR_DIRS)) -Ihdrs
CLI_OBJ_DIR = cli_obj

# --- COMPILER AND FLAGS --- #
CC = gcc
SRV_CFLAGS = -Wall -lpthread $(SRV_INCLUDE_HDRS) $(shell mysql_config --cflags)
CLI_CFLAGS = -Wall -lpthread $(CLI_INCLUDE_HDRS) $(shell mysql_config --cflags)

LDFLAGS = $(shell mysql_config --libs)

# --- SOURCES AND OBJECTS --- #
SRV_SRC = $(foreach dir, $(SRV_SRC_DIRS), $(wildcard $(dir)/*.c))
SRV_OBJ = $(addprefix $(SRV_OBJ_DIR)/, $(notdir $(SRV_SRC:.c=.o)))
vpath %.c $(SRV_SRC_DIRS)

CLI_SRC = $(foreach dir, $(CLI_SRC_DIRS), $(wildcard $(dir)/*.c))
CLI_OBJ = $(addprefix $(CLI_OBJ_DIR)/, $(notdir $(CLI_SRC:.c=.o)))
vpath %.c $(CLI_SRC_DIRS)

# --- COMMANDS --- #
all: server client

#<-- server -->#
server: $(SRV_OBJ)
	$(CC) $(SRV_CFLAGS) $(SRV_OBJ) -o $(SRV) $(LDFLAGS)

$(SRV_OBJ_DIR)/%.o: %.c | $(SRV_OBJ_DIR)
	$(CC) $(SRV_CFLAGS) -c $< -o $@

$(SRV_OBJ_DIR):
	mkdir -p $(SRV_OBJ_DIR)


#<-- client -->#
client: $(CLI_OBJ)
	$(CC) $(CLI_CFLAGS) $(CLI_OBJ) -o $(GAME) $(LDFLAGS)

$(CLI_OBJ_DIR)/%.o: %.c | $(CLI_OBJ_DIR)
	$(CC) $(CLI_CFLAGS) -c $< -o $@

$(CLI_OBJ_DIR):
	mkdir -p $(CLI_OBJ_DIR)


#<-- clean -->#
clean: clean_client clean_server

clean_server:
	rm -rf $(SRV_OBJ_DIR)
	rm -f $(SRV)

clean_client:
	rm -rf $(CLI_OBJ_DIR)
	rm -f $(CLI)

.PHONY: all server client clean clean_server clean_client 
