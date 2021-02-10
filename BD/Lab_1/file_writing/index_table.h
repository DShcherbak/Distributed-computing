
#ifndef LAB_1_INDEX_TABLE_H
#define LAB_1_INDEX_TABLE_H

void update_index_file(int movies_count, int index_table[], char *index_file_name);

void shift_movies_in_index_file(int deleted_movie_id, int *movies_count, int index_table[]);

void insert_movie_to_index_table(int movie_id, int *movies_count, int *index_table);

#endif //LAB_1_INDEX_TABLE_H
