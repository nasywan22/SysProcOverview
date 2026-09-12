#include "internal_functions.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void pinfo(char *pid) {
  char *procpath = combined_strings("/proc/", pid);
  char pid_proc_path[15];
  strcpy(pid_proc_path, procpath);
  *procpath = 0x0;

  if (access(pid_proc_path, F_OK) == -1) {
    perror("PID not found");
    exit(EXIT_FAILURE);
  }

  unsigned int total_page = 0;

  size_t lengthOfProcName = fetch_binary_info(pid_proc_path);

  calculate_cpu_usage(pid_proc_path, lengthOfProcName, &total_page);

  calculate_memory_usage(total_page);
}
