#include "internal_functions.h"
#include <stdio.h>
#include <stdlib.h>

void arg_chk(int argc) {
  if (argc < 2) {
    const char *txtpath = "/home/gallahard/Proyek/C/sysprocoverview/"
                          "program_usage_information.txt";
    FILE *fp = fopen(txtpath, "r");

    char lineBuffer[80];
    while (fgets(lineBuffer, 80, fp)) {
      printf("%s \n", lineBuffer);
    }

    fclose(fp);
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  arg_chk(argc);

  switch (argv[1][0]) {
  case 'p':
    pinfo(argv[2]);
    break;

  case 's':
    printf("Sorry this action is not yet available");
    break;
  }

  return EXIT_SUCCESS;
}
