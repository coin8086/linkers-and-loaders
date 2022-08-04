SONAME=libx.so.1
LINKER_NAME=libx.so
LIB_FILE_NAMES=libx.so.1.0.0 libx.so.1.0.1 libx.so.1.1.0
INSTALL_DIR=/usr/local/lib
CFLAGS=-fpic -Wall

all: $(LIB_FILE_NAMES)

libx.so.1.0.0: x_lib_v1_0_0.o
	gcc -o $@ -shared -Wl,-soname,$(SONAME) $^

libx.so.1.0.1: x_lib_v1_0_1.o
	gcc -o $@ -shared -Wl,-soname,$(SONAME) $^

libx.so.1.1.0: x_lib_v1_1_0.o
	gcc -o $@ -shared -Wl,-soname,$(SONAME) $^

x: x_prog.o
	gcc -o $@ $^ -lx

x_prog.o: x_prog.c
	gcc -o $@ -c -Wall $^

clean:
	rm -f $(LIB_FILE_NAMES) x *.o

install: $(LIB_FILE_NAMES)
	cp -f $^ $(INSTALL_DIR)
	ldconfig
	cd $(INSTALL_DIR) && ln -sf $(SONAME) $(LINKER_NAME)

uninstall:
	cd $(INSTALL_DIR) && rm -f $(LIB_FILE_NAMES) $(LINKER_NAME)
	ldconfig
