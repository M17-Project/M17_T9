TARGET  = libt9.so

CFLAGS  = $(INC) -fPIC -Wall -Wextra
LDFLAGS = -shared
SRCS    = t9.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

fclean:
	rm -f $(TARGET)

test:
	$(CC) $(CFLAGS) test.c -o test -lt9

testrun:
	./test

install:
	sudo install $(TARGET) /usr/lib
	sudo \cp t9.h /usr/include
	sudo chmod 644 /usr/include/t9.h

$(TARGET): t9.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: all clean test testrun install