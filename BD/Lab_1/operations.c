#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "operations.h"
#include "io_functions.h"



void insert_movie(){
    char name[101];
    int year = 2000;
    printf("Insert movie name: ");
    read_string_into_array(name, 100);
    printf("Insert movie release year: ");
    read_int(&year);
    insert_movie_in_database(name, year);
    printf("New movie : %s will be aired in the year %d\n", name, year);
    printf("-----------------------\n");
}

char* get_film_name_by_id_U(int id){
    char *str = malloc(10);
    if(id == 0){
        strcpy(str, "Godzilla");
    } else {
        strcpy(str, "Mama");
    }
    return str;
}

void insert_role(){
    char name[101];
    int film_id;
    int age;
    printf("Insert characters name: ");
    read_string_into_array(name, 100);
    printf("Insert characters age: ");
    read_int(&age);
    printf("Insert characters film id: ");
    read_int(&film_id);
    char* film_name = get_film_name_by_id_U(film_id);
    if(strcmp(film_name, "") == 0){
        printf("No film with such id: %d!\n", film_id);
    } else {
        printf("New character : (%s, %d) will appear in the %s\n", name, age, film_name);
    }
    free(film_name);

    printf("-----------------------\n");
}

void delete_movie(){
    char name[101];
    int id = -1;
    printf("Insert movie id");
    read_int(&id);
    year = 0;
    printf("New movie : %s will be aired in the year %d\n", name, year);
    printf("-----------------------\n");
}

void delete_role(){}

void get_movie(){}

void get_role(){}

void update_movie(){}

void update_role(){}

void print_all_movies(){}

void print_all_roles(){}

void test_reading(){
    char *buffer;
    size_t bufsize = 32;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    printf("Type something: ");
    gets(buffer);
    printf("%zu characters were read.\n",strlen(buffer));
    printf("You typed: '%s'\n",buffer);
}
