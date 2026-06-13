CC= gcc
CFLAGS= -Wall -Wextra -pedantic
LDFLAGS= -L../ -Wl,-rpath=../ -lSDL3 -linput

EXEC= demo_input
DEMO_SRC= demo.c
LIBSO= ../libinput.so

run: $(EXEC)
	@./$(EXEC)

all: $(EXEC)

$(EXEC): $(LIBSO) $(DEMO_SRC)
	$(CC) $(CFLAGS) -o $@ $(DEMO_SRC) $(LDFLAGS)

clean:
	@rm -f $(EXEC)
