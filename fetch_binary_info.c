#include "internal_functions.h"
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t fetch_binary_info(const char *pid_p_path) {
  // ============================================================
  // PERISAPAN
  // Prepare the full path to the process's cmdline file.
  // ============================================================
  char *cmdline_fp = combined_strings(pid_p_path, "/cmdline");

  // ============================================================
  // OPENING
  // Open the cmdline file for reading.
  // ============================================================
  FILE *fp = fopen(cmdline_fp, "r");
  if (fp == NULL) {
    fprintf(stderr,
            "File failed to open. Is PID exist?\n"
            "Detail: Failed to access '%s' -> %s (errno: %d)\n",
            cmdline_fp, strerror(errno), errno);
    fclose(fp);
    exit(EXIT_FAILURE);
  }

  // ============================================================
  // MAIN OPERATION
  // Read and parse the cmdline content.
  // ============================================================
  char chBuff[1024];
  unsigned int bytes = 0;
  unsigned int slashPos = 0;
  unsigned int isChildProc = 0;
  while ((chBuff[bytes] = fgetc(fp))) {
    if (chBuff[bytes] == 32) {
      chBuff[bytes] = 0x0;
      isChildProc = 1;
      break;
    }
    if (chBuff[bytes] == 47)
      slashPos = bytes;
    bytes++;
  }

  // ============================================================
  // CLOSING
  // Clean up: close the file and clear the path string.
  // ============================================================
  *cmdline_fp = 0x0;
  fclose(fp);

  // ============================================================
  // PRINTING
  // Output the process name and its full path.
  // ============================================================
  printf("Name: %s (Main Process)\n", chBuff + (slashPos + 1));

  size_t lengthOfProcName = 0;
  if (isChildProc) {
    lengthOfProcName = print_childproc_name(pid_p_path, isChildProc);
  }

  printf("Path: %s\n", chBuff);

  // ============================================================
  // RETURNING
  // Return the length of the child process name (if any).
  // ============================================================
  return lengthOfProcName;
}
