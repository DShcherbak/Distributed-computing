#ifndef LAB_1_IO_FUNCTIONS_H
#define LAB_1_IO_FUNCTIONS_H
#define  _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int get_user_choice();

void read_string_into_array(char* array, int max_size);

void read_int(int* x);

void put_int(int x);

#endif //LAB_1_IO_FUNCTIONS_H
