
#include "binary_files.h"

void insert_movie_to_file(Database* database, Movie movie) {
    FILE* movie_file = fopen(database->movies_file, "r+b");
    unsigned movie_size = sizeof(Movie) + 2 * sizeof(int);
    unsigned offset = movie_size * (database->movies_count - 1);
    fseek(movie_file, offset, SEEK_SET);
    fwrite(&movie, sizeof(Movie), 1, movie_file);
    int additional_info[2] = {-1, 0}; // position of first s, and cnt of sons
    fwrite(additional_info, sizeof(int), 2, movie_file);
    fclose(movie_file);
}

void insert_role_to_file(Database* database, Role member, int cur_cnt_members, int additional_info) {
    FILE* member_file_pointer = fopen(database->roles_file, "r+b");
    cur_cnt_members++;
    fwrite(&cur_cnt_members, sizeof(int), 1, member_file_pointer);
    fclose(member_file_pointer);
    member_file_pointer = fopen(database->roles_file, "r+b");
    unsigned size_of_one_item = sizeof(Role) + sizeof(int);
    unsigned offset = sizeof(int) + size_of_one_item * (cur_cnt_members - 1);
    fseek(member_file_pointer, offset, SEEK_SET);
    fwrite(&member, sizeof(Role), 1, member_file_pointer);
    fwrite(&additional_info, sizeof(int), 1, member_file_pointer);
    fclose(member_file_pointer);
}

void get_additional_info_by_movie_row(Database* database, int movie_row,
                                      int* first_role_position, int* cnt_roleships) {
    FILE* movie_file_pointer = fopen(database->movies_file, "rb");
    unsigned size_of_one_item = sizeof(Movie) + 2 * sizeof(int);
    unsigned offset = size_of_one_item * (movie_row) + sizeof(Movie);
    fseek(movie_file_pointer, offset, SEEK_SET);
    fread(first_role_position, sizeof(int), 1, movie_file_pointer);
    fread(cnt_roleships, sizeof(int), 1, movie_file_pointer);
    fclose(movie_file_pointer);
}

void update_additional_movie_info(Database* database, int movie_row,
                                  int first_role_position, int cnt_roleships) {
    FILE* movie_file_pointer = fopen(database->movies_file, "r+b");
    int size_of_one_item = sizeof(Movie) + 2 * sizeof(int);
    unsigned offset = size_of_one_item * (movie_row) + sizeof(Movie);
    fseek(movie_file_pointer, offset, SEEK_SET);
    fwrite(&first_role_position, sizeof(int), 1, movie_file_pointer);
    fwrite(&cnt_roleships, sizeof(int), 1, movie_file_pointer);
    fclose(movie_file_pointer);
}

int update_movie_after_insertion(Database* database, int movie_row, int role_row) {
    int position, cnt_roleships;
    get_additional_info_by_movie_row(database, movie_row, &position, &cnt_roleships);
    ++cnt_roleships;
    update_additional_movie_info(database, movie_row, role_row, cnt_roleships);
    return position;
}

void get_all_movie_roles(Database* database, int movie_id, Role roles[]){
    int i = 0;
    FILE* role_file_pointer = fopen(database->roles_file, "rb");
    Role role;
    int previous_row;
    while(role.id > 0 && role.movie_id == movie_id) {
        roles[i] = role;
        i++;
        fread(&role, sizeof(Role), 1, role_file_pointer);
    }
    fclose(role_file_pointer);
}

void update_movie_in_file(Database* database, int row, Movie movie){
    FILE* movies_file = fopen(database->movies_file, "r+b");
    unsigned movie_size = sizeof(Movie) + 2 * sizeof(int);
    unsigned offset = movie_size * row;
    fseek(movies_file, offset, SEEK_SET);
    fwrite(&movie, sizeof(Movie), 1, movies_file);
    fclose(movies_file);
}

int update_role_in_file(Database* database, int start_row, Role role){
    FILE* roles_file = fopen(database->roles_file, "r+b");
    int cur_row = start_row;
    int size_of_one_row = sizeof(Role) + sizeof(int);
    while (cur_row != -1) {
        unsigned offset = size_of_one_row * cur_row + sizeof(int);
        fseek(roles_file, offset, SEEK_SET);
        Role cur_role;
        fread(&cur_role, sizeof(Role), 1, roles_file);
        if (cur_role.id == role.id){
            fseek(roles_file, offset, SEEK_SET);
            fwrite(&role, sizeof(Role), 1, roles_file);
            fclose(roles_file);
            return 0;
        }
        fread(&cur_row, sizeof(int), 1, roles_file);
    }
    fclose(roles_file);
    return -1;
}