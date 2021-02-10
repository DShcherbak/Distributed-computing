#include <zconf.h>
#include "movie_database.h"


const int maxMovieId = 100;
const int maxRoleId = 100;

Database upload_database(){
    Movie* movies = (Movie*) malloc(maxMovieId * sizeof(char));
}

void insert_movie_into_database(Database* db, const char* name, int year){
    if(db->movies_count == maxMovieId){
        printf("Movies table overflow.");
    }
    int id = db->movies_count++;
    Movie movie = {
            id, name, year
    };
    db->movies[id] = movie;

}

void read_index_file(Database* database) {
    printf("reading...\n");
    FILE* movie_index_file_pointer = fopen(database->movies_index_file, "rb");
    fread(&database->movies_count, sizeof(int), 1, movie_index_file_pointer);
    if (database->movies_count != 0) {
        fread(&database->index_table, sizeof(int), database->movies_count * 2, movie_index_file_pointer);
    }
    fclose(movie_index_file_pointer);
}

void create_movie_index_file(Database* database) {
    FILE* movie_index_file_pointer = fopen(database->movies_index_file, "wb");
    int movies_count = 0;
    fwrite(&movies_count, sizeof(int), 1, movie_index_file_pointer);
    fclose(movie_index_file_pointer);
}

void create_movie_file(Database* database) {
    FILE* movie_index_file_pointer = fopen(database->movies_file, "wb");
    fclose(movie_index_file_pointer);
}

void create_role_file(Database* database) {
    FILE* role_file_pointer = fopen(database->roles_file, "wb");
    int movies_count = 0;
    fwrite(&movies_count, sizeof(int), 1, role_file_pointer);
    fclose(role_file_pointer);
}


void init_database(Database* database) {
    if( access(database->movies_file, F_OK ) == -1 )
        create_movie_file(database);

    if( access(database->movies_index_file, F_OK ) == -1 )
        create_movie_index_file(database);

    if( access(database->roles_file, F_OK ) == -1 )
        create_role_file(database);

    read_index_file(database);
}

void print_movie(Movie movie){

}


void print_role(Role role){

}