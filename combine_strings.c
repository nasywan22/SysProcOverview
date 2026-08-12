#include "internal_functions.h"
#include <string.h>
#include <unistd.h>

char *combined_strings(const char *str1, const char *str2) {
  static char combined_strings_storage[30];

  strcat(combined_strings_storage, str1);
  strcat(combined_strings_storage, str2);

  return combined_strings_storage;
}
