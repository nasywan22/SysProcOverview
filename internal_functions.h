#ifndef INTERNAL_H
#define INTERNAL_H
#include <stddef.h>

char *combined_strings(const char *str1, const char *str2);
void pinfo(char *pid);
size_t fetch_binary_info(const char *procpath);
size_t print_childproc_name(const char *pid_p_pathd);
void calculate_cpu_usage(char *pid_proc_path, unsigned int lengthOfProcName);

#endif
