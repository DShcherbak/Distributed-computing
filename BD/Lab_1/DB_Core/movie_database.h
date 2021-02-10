#ifndef LAB_1_MOVIE_DATABASE_H
#define LAB_1_MOVIE_DATABASE_H

#include <stdlib.h>
#include <stdio.h>


typedef struct element_movie{
    int id;
    char* name;
    int year;
} Movie;

typedef struct element_role{
    int id;
    char* name;
    int age;
    int movie_id;
} Role;

typedef struct movie_database{
    Movie* movies;
    Role* roles;
    int movies_count;
    int roles_count;
    int index_table[200];
    int max_movie_id;
    int max_role_id;

    char * movies_index_file;
    char * movies_file;
    char * roles_file;
} Database;

Database upload_database();

void read_index_file(Database* database);

void create_movie_index_file(Database* database);

void create_movie_file(Database* database);

void create_role_file(Database* database);

void init_database(Database* database);

void print_movie(Movie movie);

void print_role(Role role);




#endif //LAB_1_MOVIE_DATABASE_H
