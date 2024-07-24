CFLAGS += -Wall

all: main

dirs:
	@mkdir build


main: src/main.c
	$(CC) $(CFLAGS) -o build/main $<
