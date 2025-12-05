TARGET  = libt9.so

CFLAGS  = $(INC) -fPIC -Wall -Wextra
ifneq ($(SEARCH),)
	CFLAGS += -D$(SEARCH)
endif
LDFLAGS = -shared
SRCS    = t9.c
OBJS    = $(SRCS:.c=.o)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

fclean:
	rm -f $(TARGET)

test:
	$(CC) $(CFLAGS) t9.c ./tests/test.c -o ./tests/test

testrun:
	./tests/test

install:
	sudo install $(TARGET) /usr/lib
	sudo \cp t9.h /usr/include
	sudo chmod 644 /usr/include/t9.h
	sudo ldconfig

$(TARGET): t9.h $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: all clean fclean test testrun install