CFLAGS = -g -Wall
srcs != ls *.c
prgs := $(srcs:.c=)

all : $(prgs)

clean:
	rm $(prgs)
