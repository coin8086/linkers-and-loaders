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
