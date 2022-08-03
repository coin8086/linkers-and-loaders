#include <stdio.h>

__asm__(".symver foo_v1_0,foo@v1.0");

void foo_v1_0()
{
  printf("foo v1.0\n");
}

//When there're multiple versions of a symbol like foo, one must be set as default by "@@".
//Or a program, like sv_prog.c, linking against it will fail at link time, with error like
//
//sv_prog.c:(.text+0xa): undefined reference to `foo'
//
__asm__(".symver foo_v1_1,foo@@v1.1");

void foo_v1_1()
{
  printf("foo v1.1\n");
}

void bar()
{
  printf("bar v1.1\n");
}

void xyz()
{
  printf("xyz\n");
}

