# Demo of Lib Versioning

Make versions of libx and install them

```bash
make
sudo make install
```

Note that `ldconfig` will create a symbolic link for soname (libx.so.1), but the link for linker name (libx.so) has be to created manually.

Make program x to link against libx

```bash
make x
./x
```

Uninstall libx and try x again

```bash
sudo make uninstall
./x
```

This time x will fail with error like

```
./x: error while loading shared libraries: libx.so.1: cannot open shared object file: No such file or directory
```

Clean build results

```bash
make clean
```

## References:

* https://man7.org/conf/lca2006/shared_libraries/slide6.html
