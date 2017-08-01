NAME=lmsg
CC=gcc
OPT=-O2
ARCH=
DBG=
FLAGS=

def:
	@echo "(OS)(ARCH): L32/L64/W32/W64"
	@echo "clean/def"

L32: ARCH=-m32
L32: linux

L64: ARCH=-m64
L64: linux

W32: CC=i686-w64-mingw32-gcc
W32: win

W64: CC=x86_64-w64-mingw32-gcc
W64: win

win: all
linux: all

all: CFLAGS=$(ARCH) $(DBG) $(OPT) -Wall -c
all: $(NAME).c $(NAME).h
	$(CC) $(CFLAGS) $(NAME).c -c -o out/$(NAME).o
	ar rc out/lib$(NAME).a out/$(NAME).o
	ranlib out/lib$(NAME).a

clean:
	rm out/*.a
	rm out/*.o
