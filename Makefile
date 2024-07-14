CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -Werror

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)
TESTS = $(wildcard tests/*.c)

TARGET = libLDSC.a

TESTTARGET = test_runner
CFLAGSTEST = -Iinclude -Wall
LDFLAGS = -lcheck -lm -lsubunit

all: $(TARGET)

$(TARGET): $(OBJ)
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TARGET)
	$(CC) $(CFLAGSTEST) $(TESTS) $(TARGET) $(LDFLAGS) -o $(TESTTARGET)
	./$(TESTTARGET)

clean:
	rm -f $(OBJ) $(TARGET) $(TESTTARGET)

.PHONY: all test clean
