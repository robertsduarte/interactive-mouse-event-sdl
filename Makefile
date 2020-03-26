# set the compiler
CC := clang

# set the compiler flags
CFLAGS := `sdl2-config --cflags --libs` -lSDL2_image -lm

# header files
HDRS :=

# source fil√es
SRCS := main.c

# generate names of object files
OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := game

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)

# recipe to clean the workspace
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
