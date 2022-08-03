TARGETS=libsv.so p p2

all: $(TARGETS)

libsv.so: sv_lib.o sv_lib.map
	gcc -o $@ -Wall -shared sv_lib.o -Wl,--version-script,sv_lib.map

sv_lib.o: sv_lib.c
	gcc -o $@ -c -Wall -fpic $^

p: sv_prog.c libsv.so
	gcc -o $@ -Wall $^

p2: dl_prog.c
	gcc -o $@ -Wall $^ -ldl

clean:
	rm -f *.o $(TARGETS)
