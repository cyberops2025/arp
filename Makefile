# I initially used this resource, but modified it a lot based on research:
# https://web.stanford.edu/class/archive/cs/cs107/cs107.1174/guide_make.html

CC =		gcc
# Will include debug info and not optimize so I can look at the assembly, etc.
CFLAGS =	-g -Wall -O0
TARGET =	arp-request

SRC_DIR =	./src
SOURCES = 	$(wildcard $(SRC_DIR)/*.c)

BLD_DIR =	./build
TEMP =		$(subst $(SRC_DIR),$(BLD_DIR),$(SOURCES))
OBJECTS =	$(TEMP:.c=.o)

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

$(BLD_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(BLD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -f $(TARGET) $(OBJECTS) 
