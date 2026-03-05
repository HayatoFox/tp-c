CC       = gcc
CFLAGS   = -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion \
           -Wshadow -Wformat=2 -Wundef -O2 -g
LDFLAGS  = -lm

SRC_DIR  = src
BIN_DIR  = bin

SRCS     = $(wildcard $(SRC_DIR)/*.c)
OBJS     = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.o, $(SRCS))
TARGET   = $(BIN_DIR)/$(notdir $(CURDIR))

.PHONY: all clean

all: $(BIN_DIR) $(TARGET)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN_DIR)/*
