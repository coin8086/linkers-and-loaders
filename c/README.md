# Experiments in C

## Multiple Definitions for the Same Symbol

Try this

```bash
gcc -c *.c
ar rcs libw2.a w2.o
```

Then

```bash
gcc a.o m.o w.o libw2.a -o x2
./x2
```

output:

```
My Write!
```

Then

```bash
gcc a.o m.o libw2.a -o x2
./x2
```

output:

```
My Write, 2!
```

Then

```bash
gcc a.o m.o -o x2
./x2
```

output:

```
Hello, world!
```

However, this

```bash
gcc a.o m.o w.o w2.o -o x2
```

produces an error:

```
w2.o: In function `write':
w2.c:(.text+0x0): multiple definition of `write'
w.o:w.c:(.text+0x0): first defined here
collect2: error: ld returned 1 exit status
```

This means a "private" version of `write` can "hide" the definition in a lib. But you can not have multiple definitions for the same symbol in input .o files!

## Symbols are Resolved only by Matching Names

Try this

```bash
gcc -c *.c
gcc m.o a2.o -o x
./x
```

output:

```
This is a!
```

This means linker resolves symbols only by matching names and doesn't care a function's signature. However, since C++'s name mangling, linker can thus match the signature by simply matching names.

This

```bash
g++ -c *.c
gcc m.o a2.o -x x
```

failed with error

```
m.o: In function `main':
m.c:(.text+0x17): undefined reference to `a(char*)'
collect2: error: ld returned 1 exit status
```

However a function's signature doesn't take the return type into count. So it's possible to do

```bash
gcc m.o a3.o -x x
./x
```

Producing

```
This is a, too!
```

This means linker time type checking is still meaningful.

## Static Linked libc

Try this

```bash
gcc -c *.c
gcc -o x2 a.o m.o -lc -static
```

Then check the binary with `readelf -a x2`. No dynamic secion will be found.

## Shared Library

```bash
gcc -c -fpic a.c
gcc -shared -o liba.so a.o
gcc -o x m.c liba.so
```
Then `gcc -o x m.c liba.so` or `gcc -o x m.c -L. -la`

Run it by

```bash
LD_LIBRARY_PATH=. ./x
```

### Versioning by soname

Naming convension:
  * real/file name: libxyz.so.{major}.{minor}.{patch}, e.g. libxyz.so.1.0.1
  * soname: libxyz.so.{major}, e.g. libxyz.so.1, typically a soft link to real/file name.
  * linker name: libxyz.so, e.g. libxyz.so, typically a soft link to soname.

Specify a soname when linking a shared library, while having the full version ({major}.{minor}.{patch}) in the real/file name:

```bash
gcc -c -fpic a.c
gcc -shared -o liba.so.1.0.0 -Wl,-soname,liba.so.1 a.o
```

See the embedded soname in the library by `readelf -d ...| grep SONAME`.

Then any binary linked with liba.so.1.0.0 will look for a library named liba.so.1 at run time. This can be checked by `readelf -d ... | grep NEEDED`. So a soft link of soname is required:

```bash
ln -s liba.so.1.0.0 liba.so.1
```

Besides, to link with the lib by `-la` (instead of `... liba.so.1.0.0 ...`), a soft link of linker name is required:

```bash
ln -s liba.so.1 liba.so
```
