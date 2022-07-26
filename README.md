Refer to

* https://www.iecc.com/linker/linker01.html
* http://em386.blogspot.com/2006/10/resolving-elf-relocation-name-symbols.html
* https://man7.org/conf/lca2006/shared_libraries/index.html
* https://man7.org/conf/lca2006/shared_libraries/slide19a.html

Check the object file (in ELF) by `objdump` and `readelf`.

* Show assembler code by `objdump -d`, and optionally `objdump -d -M intel-mnemonic` (by default it's `att-mnemonic`).
* Show object relocation info by `objdump -d`, `objdump -R`, and `readelf -r`.
