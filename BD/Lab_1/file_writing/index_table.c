//
// Created by sadoffnick on 14.12.20.
//

#include "index_table.h"
#include <stdio.h>

void update_index_file(int movies_count, int index_table[], char *index_file_name) {
    FILE* player_index_file_pointer = fopen(index_file_name, "wb");
    fwrite(&movies_count, sizeof(int), 1, player_index_file_pointer);
    if (movies_count != 0) {
        fwrite(index_table, sizeof(int), movies_count * 2,
               player_index_file_pointer);
    }
    fclose(player_index_file_pointer);
}

void insert_movie_to_index_table(int movie_id, int *movies_count, int *index_table) {
    (*movies_count)++;
    for (int i = (*movies_count) - 1; i >= 0; i--) {
        if (i == 0 || index_table[2 * (i - 1)] < movie_id) {
            index_table[i * 2] = movie_id;
            index_table[i * 2 + 1] = (*movies_count) - 1;
            break;
        }
        else {
            index_table[i * 2] =  index_table[2 * (i - 1)];
            index_table[i * 2 + 1] =  index_table[2 * (i - 1) + 1];
        }
    }
}

void shift_movies_in_index_file(int deleted_movie_id, int *movies_count, int index_table[]) {
    int start_row = (*movies_count);
    for (int i = 0; i < (*movies_count); ++i) {
        if (index_table[i * 2] == deleted_movie_id) {
            start_row = i;
            break;
        }
    }
    for (int i = start_row; i < (*movies_count) - 1; ++i){
        index_table[i * 2] = index_table[i * 2 + 2];
        index_table[i * 2 + 1] = index_table[i * 2 + 3];
    }
    (*movies_count)--;
}


