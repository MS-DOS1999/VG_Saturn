#ifndef RAM_TRACKING
#define RAM_TRACKING

void set_system_ram();
unsigned long get_system_ram();
unsigned long get_free_ram();
void print_ram_stats();

#endif