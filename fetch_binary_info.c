#include "internal_functions.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void fetch_binary_info(const char *pid_p_path) {
  const char *cmdline_fp = combined_strings(pid_p_path, "/cmdline");

  FILE *fp = fopen(cmdline_fp, "r");
  if (fp == NULL) {
    fprintf(stderr,
            "File failed to open. Is PID exist?\n"
            "Detail: Failed to access '%s' -> %s (errno: %d)\n",
            cmdline_fp, strerror(errno), errno);
    fclose(fp);
    exit(EXIT_FAILURE);
  }

  char chBuff[1024];
  unsigned int bytes = 0;
  unsigned int slashPos = 0;
  while ((chBuff[bytes] = fgetc(fp))) {
    if (chBuff[bytes] == 32)
      break;
    if (chBuff[bytes] == 47)
      slashPos = bytes;
    bytes++;
  }

  printf("Name: %s\n", chBuff + (slashPos + 1));
  printf("Path: %s\n", chBuff);

  fclose(fp);
}
