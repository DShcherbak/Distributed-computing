#ifndef LAB_1_BINARY_FILES_H
#define LAB_1_BINARY_FILES_H
#include "movie_database.h"

void insert_movie_to_file(Database* database, Movie movie);

void insert_role_to_file(Database* database, Role member, int cur_cnt_members, int additional_info);

void get_additional_info_by_movie_row(Database* database, int movie_row,
                                      int* first_role_position, int* cnt_roleships);

void update_additional_movie_info(Database* database, int movie_row,
                                  int first_role_position, int cnt_roleships);

int update_movie_after_insertion(Database* database, int movie_row, int role_row);

void get_all_movie_roles(Database* database, int movie_id, Role roles[]);

void update_movie_in_file(Database* database, int row, Movie movie);

int update_role_in_file(Database* database, int start_row, Role role);
#endif //LAB_1_BINARY_FILES_H
