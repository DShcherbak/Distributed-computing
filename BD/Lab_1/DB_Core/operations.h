#ifndef LAB_1_OPERATIONS_H
#define LAB_1_OPERATIONS_H
#include "binary_files.h"
#include "io_functions.h"
#include "index_table.h"



void insert_movie(Database* database);

void insert_role(Database* database);

void get_movie(Database* database);

void get_role(Database* database);

void delete_movie(Database* database);

void delete_role(Database* database);

void update_movie(Database* database);

void update_role(Database* database);

void print_all_movies(Database* database);

void print_all_roles(Database* database);

void test_reading();

#endif //LAB_1_OPERATIONS_H
