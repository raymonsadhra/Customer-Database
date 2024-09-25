CC = clang
CFLAGS = -Wall -Wpedantic -Werror -Wextra


OBJS = businessdb.o

TARGET = businessdb

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)


businessdb.o: businessdb.c
	$(CC) $(CFLAGS) -c businessdb.c

clean:
	rm -f businessdb.o $(TARGET)

format:
	clang-format -i -style=file *.[ch]
