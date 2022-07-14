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

```bash
gcc a.o m.o libw2.a -o x2
./x2
```
output:

```
My Write, 2!
```

```bash
gcc a.o m.o -o x2
./x2
```

output:

```
Hello, world!
```

However, this produces a linker error:

```bash
gcc a.o m.o w.o w2.o -o x2
```
