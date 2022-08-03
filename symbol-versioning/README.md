# Symbol Versioning

## libsv.so v1

Build libsv.so v1

```bash
gcc -g -c -fpic -Wall sv_lib_v1.c
gcc -g -shared -o libsv.so sv_lib_v1.o -Wl,--version-script,sv_v1.map
```

Then check its exported symbols by `readelf --dyn-syms libsv.so`. The result is like

```bash
Symbol table '.dynsym' contains 8 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND puts@GLIBC_2.2.5 (3)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (3)
     6: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS VER_1
     7: 00000000000005aa    19 FUNC    GLOBAL DEFAULT   13 xyz@@VER_1
```

Note the exported symbol `xyz@@VER_1`.

Link `p1` against libsv.so v1 and run it

```bash
gcc -g -o p1 sv_prog.c libsv.so
LD_LIBRARY_PATH=. ./p1
```

The result is

```bash
v1 xyz
```

Then check the imported symbols by `readelf --dyn-syms p1`. The result is like

```bash
Symbol table '.dynsym' contains 8 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (2)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND xyz@VER_1 (3)
     5: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND exit@GLIBC_2.2.5 (2)
     6: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     7: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (2)
```

Note the imported symbol `xyz@@VER_1`.

## libsv.so v2

Build libsv.so v2

```bash
gcc -g -c -fpic -Wall sv_lib_v2.c
gcc -g -shared -o libsv.so sv_lib_v2.o -Wl,--version-script,sv_v2.map
```

Then check its exported symbols again by `readelf --dyn-syms libsv.so`. The result is like

```bash
Symbol table '.dynsym' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
     2: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND puts@GLIBC_2.2.5 (4)
     3: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     5: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (4)
     6: 0000000000000660    19 FUNC    GLOBAL DEFAULT   13 pqr@@VER_2
     7: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS VER_1
     8: 0000000000000000     0 OBJECT  GLOBAL DEFAULT  ABS VER_2
     9: 000000000000064d    19 FUNC    GLOBAL DEFAULT   13 xyz@@VER_2
    10: 000000000000063a    19 FUNC    GLOBAL DEFAULT   13 xyz@VER_1
```

Note the exported symbols `xyz@@VER_1`, `xyz@@VER_2` and `pqr@@VER_2`.

Run `p1` again without rebuilding

```bash
LD_LIBRARY_PATH=. ./p1
```

The result is still

```bash
v1 xyz
```

Then link `p2` against libsv.so v2 and run it

```bash
gcc -g -o p2 sv_prog.c libsv.so
LD_LIBRARY_PATH=. ./p2
```

The result is

```bash
v2 xyz
```

Then check the imported symbols by `readelf --dyn-syms p2`. The result is like

```bash
Symbol table '.dynsym' contains 8 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND xyz@VER_2 (2)
     2: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_deregisterTMCloneTab
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __libc_start_main@GLIBC_2.2.5 (3)
     4: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     5: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND exit@GLIBC_2.2.5 (3)
     6: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND _ITM_registerTMCloneTable
     7: 0000000000000000     0 FUNC    WEAK   DEFAULT  UND __cxa_finalize@GLIBC_2.2.5 (3)
```

Note the imported symbol `xyz@@VER_2`.

## Conclusion

libsv.so v1 and libsv.so v2 show that

* A client program doesn't need to know the version of the imported symbols. It links against a shared library (.so file) as usual.
* The version of an imported symbol is determined at the (static) link time.

## Questions

* Can a client program specify a specific version of a symbol to link against?
* How about dynamic linking by dlsym? Can it specify a versioned symbol, like `xyz@@VER_2`?

## Refereneces

* https://gcc.gnu.org/wiki/SymbolVersioning
* http://sourceware.org/binutils/docs/ld/VERSION.html
* http://web.mit.edu/rhel-doc/3/rhel-as-en-3/symver.html
* https://man7.org/conf/lca2006/shared_libraries/slide19a.html
