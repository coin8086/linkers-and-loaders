# Symbol Versioning 2

To address [the questions in previous section](../symbol-versioning/README.md#questions):

1. How to link to a specific version of a symbol?
  By a declaration like
  
  ```c
  __asm__(".symver old_foo,foo@v1.0");
  void old_foo();
  ```

2. How to dynamically load a specific version of symbol?
  By `dlvsym`.
