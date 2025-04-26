CC      = clang
CFLAGS  = -g -Wall
RM      = rm -f


default: all

all: echo_server.exe, threaded.exe

echo_server.exe: echo_server.c
	$(CC) $(CFLAGS) -o echo_server.exe echo_server.c

threaded.exe: threaded.c
	$(CC) $(CFLAGS) -o threaded.exe threaded.c

clean veryclean:
	$(RM) *.exe
	$(RM) *.ilk
	$(RM) *.pdb

echo_test: echo_server.exe
	./echo_server.exe

test: threaded.exe
	./threaded.exe