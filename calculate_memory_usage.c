#include <stdio.h>
void calculate_memory_usage(unsigned int total_page) {
  unsigned int total_page_byte = total_page * 4096;
  int total_page_kilo = total_page_byte / 1024;
  int total_page_mega = total_page_kilo / 1024;

  printf("Memory Usage: %iMB / ", total_page_mega);
  printf("%iKB / ", total_page_kilo);
  printf("%i bytes ", total_page_byte);
}
