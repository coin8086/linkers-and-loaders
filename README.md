Refer to https://www.iecc.com/linker/linker01.html and http://em386.blogspot.com/2006/10/resolving-elf-relocation-name-symbols.html

Show object relocation info by `objdump -d m`, `objdump -R m`, and `readelf -r m`.

Also, `objdump -d a.o` and `objdump -d m.o` show the relocation at (static) linking stage.

