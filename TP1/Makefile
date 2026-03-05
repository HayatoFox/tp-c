CC       = gcc
CFLAGS   = -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion \
           -Wshadow -Wformat=2 -Wundef -O2 -g
LDFLAGS  = -lm

SRC_DIR  = src
BIN_DIR  = bin

SRCS     = $(wildcard $(SRC_DIR)/*.c)
TARGETS  = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(TARGETS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf $(BIN_DIR)/*
