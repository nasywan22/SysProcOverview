#include "internal_functions.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int fetch_and_sum_total_time(FILE *statfp, int *starttime,
                             unsigned int lengthOfProcName) {
  int sum_result = 0;
  int buffer = 0;
  size_t fieldPos = 0;

  fseek(statfp, 13 + lengthOfProcName, SEEK_SET);

  while (fscanf(statfp, "%d", &buffer)) {
    if (fieldPos >= 14 && fieldPos <= 17) {
      sum_result += buffer;
    } else if (fieldPos == 22) {
      *starttime = buffer;
      break;
    } else {
      fieldPos++;
    }
  }

  return sum_result / 100;
}

int fetch_uptime_system(FILE *uptimefp) {
  int buffer = 0;
  fscanf(uptimefp, "%d", &buffer);

  return buffer;
}

int calculate_and_convert_lifetime_process_in_seconds(FILE *uptimefp,
                                                      int starttime) {
  return fetch_uptime_system(uptimefp) - (starttime / 100);
}

void calculate_cpu_usage(char *pid_proc_path, unsigned int lengthOfProcName) {
  // ============================================================
  // PREPARATION
  // Build the path to /proc/[pid]/stat and store it in a local array.
  // ============================================================
  char *statpathtemp = combined_strings(pid_proc_path, "/stat");
  char statpath[15];
  strcpy(statpath, statpathtemp);
  *statpathtemp = 0x0;

  int starttime = 0;

  // ============================================================
  // OPENING
  // Open both /proc/[pid]/stat and /proc/uptime for reading.
  // ============================================================
  FILE *statfp = fopen(statpath, "r");
  FILE *uptimefp = fopen("/proc/uptime", "r");

  // ============================================================
  // OPERATION
  // Calculate total CPU time used, process lifetime in seconds,
  // and average CPU usage percentage.
  // ============================================================
  float total_time =
      fetch_and_sum_total_time(statfp, &starttime, lengthOfProcName);

  int seconds =
      calculate_and_convert_lifetime_process_in_seconds(uptimefp, starttime);

  float cpu_usage_avarage_persentage = 100 * (total_time / seconds);

  // ============================================================
  // PRINTING
  // Display the calculated average CPU usage.
  // ============================================================
  printf("cpu usage: %f%%\n", cpu_usage_avarage_persentage);

  // ============================================================
  // CLOSING
  // Close both file handles.
  // ============================================================
  fclose(statfp);
  fclose(uptimefp);
}
