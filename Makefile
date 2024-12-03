# Set compiler
CC := gcc

# Common flags
CFLAGS := -lm

# Platform-specific settings
ifeq ($(OS),Windows_NT)
    # Windows-specific settings
    CFLAGS += -I$(USERPROFILE)/SDL2/include -L$(USERPROFILE)/SDL2/lib -lSDL2 -lSDL2_image
    RM := del /Q
    EXEC := game.exe
else
    # Linux-specific settings
    CFLAGS += `sdl2-config --cflags --libs` -lSDL2_image
    RM := rm -f
    EXEC := game
endif

# Source and object files
SRCS := main.c
OBJS := $(SRCS:.c=.o)

# Default target
all: $(EXEC)

# Build the executable
$(EXEC): $(OBJS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# Clean target
clean:
	$(RM) $(EXEC) $(OBJS)

.PHONY: all clean
