#ifndef INTERNAL_H
#define INTERNAL_H

char *combined_strings(const char *str1, const char *str2);
void pinfo(char *pid);
void fetch_binary_info(const char *procpath);
void print_childproc_name(const char *pid_p_path);

#endif
