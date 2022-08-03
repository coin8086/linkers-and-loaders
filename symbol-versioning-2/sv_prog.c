
//A version of symbol can be explicitly referenced like this
__asm__(".symver old_foo,foo@v1.0");
void old_foo();

void foo();
void bar();

int main() {
  old_foo();

  foo();
  bar();
}
