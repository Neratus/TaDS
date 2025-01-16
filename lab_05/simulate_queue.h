#ifndef SIMULATE_QUEUE_H
#define SIMULATE_QUEUE_H

#include "static_queue.h"
#include "dynamic_queue.h"
#include "list_queue.h"

#define MAX_REQ 1000
#define PRINT_REQ 100

void simulate_static(void);

void simulate_dynamic(void);

void simulate_list(void);

void simulate_static_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability);

size_t simulate_dynamic_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability);

size_t simulate_list_silent(double t1_start, double t1_finish, double t2_start, double t2_finish, double probability);


#endif
