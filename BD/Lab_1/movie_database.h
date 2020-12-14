#ifndef LAB_1_MOVIE_DATABASE_H
#define LAB_1_MOVIE_DATABASE_H

#include <stdlib.h>
#include <stdio.h>

const int maxMovieId = 100;
const int maxRoleId = 100;

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
} database;

database init_database(){
    Movie* movies = (Movie*) malloc(maxMovieId * sizeof(char));
}

void insert_movie_into_database(database* db, const char* name, int year){
    if(db->movies_count == maxMovieId){
        printf("Movies table overflow.");
    }
    int id = db->movies_count++;
    Movie movie = {
            id, name, year
    };
    db->movies[id] = movie;

}




#endif //LAB_1_MOVIE_DATABASE_H
