CC=x86_64-w64-mingw32-gcc




implant.exe: 
	$(CC) bin/http.o bin/exec.o command.c main.c -lwinhttp -ladvapi32 -lkernel32 -o bin/implant.exe
