TARGET_LIB=libsv.so
TARGET_BIN=p

all: $(TARGET_LIB) $(TARGET_BIN)

libsv.so: sv_lib.o sv_lib.map
	gcc -o $@ -Wall -shared sv_lib.o -Wl,--version-script,sv_lib.map

sv_lib.o: sv_lib.c
	gcc -o $@ -c -Wall -fpic $^

p: sv_prog.c libsv.so
	gcc -o $@ -Wall $^

clean:
	rm -f *.o $(TARGET_LIB) $(TARGET_BIN)
