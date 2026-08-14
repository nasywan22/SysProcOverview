#include "internal_functions.h"
#include <stddef.h>
#include <stdio.h>

void print_childproc_name(const char *pid_p_path) {
  const char *status_path = combined_strings(pid_p_path, "/status");
  FILE *fp = fopen(status_path, "r");
  fseek(fp, 6, SEEK_SET);

  char childproc_name[20];
  size_t bytes = 0;
  while ((childproc_name[bytes] = fgetc(fp))) {
    if (childproc_name[bytes] == 10) {
      childproc_name[bytes] = 0x0;
      break;
    }
    bytes++;
  }

  printf("Name: %s (Child Process) \n", childproc_name);
}
