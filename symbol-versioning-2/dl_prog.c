#define _GNU_SOURCE //To use dlvsym
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char *argv[]) {
  void *libHandle;            /* Handle for shared library */
  void (*funcp)(void);        /* Pointer to function with no args */
  char *err;

  if (argc < 3) {            /* Check command line arguments */
    fprintf(stderr, "Usage: %s lib-path func-name [version]\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  /* Load the shared library and get a handle for later use */

  libHandle = dlopen(argv[1], RTLD_NOW);
  if (libHandle == NULL) {
    fprintf(stderr, "Error on dlopen: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }

  /* Get a pointer to named function inside library */

  (void) dlerror();           /* Clear dlerror() */

  /* The strange cast below is required by C99, which	forbids
      assignment between a function pointer and void * */

  if (argc == 3) {
    *(void **) (&funcp) = dlsym(libHandle, argv[2]);
  }
  else {
    *(void **) (&funcp) = dlvsym(libHandle, argv[2], argv[3]);
  }

  err = dlerror();
  if (err != NULL) {  /* Non-NULL from dlerror() means we got error */
    fprintf(stderr, "Error on dlsym: %s\n", err);
    exit(EXIT_FAILURE);
  }

  /* If the function address is non-NULL try calling it */

  if (funcp == NULL)
      printf("%s is NULL\n", argv[2]);
  else
      (*funcp)();

  /* And close the library */

  dlclose(libHandle);
  exit(EXIT_SUCCESS);
}
