#include "operations.h"
#include "io_functions.h"
#include "movie_database.h"
#include <stdio.h>

int run_interface(){
    printf("Choose an option (a number from 0 to 9):\n");
    printf("1. Insert movie\n");
    printf("2. Insert character\n");
    printf("3. Delete movie\n");
    printf("4. Delete character\n");
    printf("5. Get movie\n");
    printf("6. Get character\n");
    printf("7. Update movie\n");
    printf("8. Update character\n");
    printf("9. Print all movies\n");
    printf("0. Print all characters\n");
    printf("Press any other key to exit.\n");
    printf("Your choice: ");

    int choice = get_user_choice();
    if(choice < 0 || choice > 9)
        return 0;
    else {
        if(choice == 1) {
            printf("Insert `movie`\n");
            insert_movie();
        } else if(choice == 2) {
            printf("Insert `character`\n");
            insert_role();
        } else if(choice == 3) {
            printf("Delete `movie`\n");
            delete_movie();
        } else if(choice == 4) {
            printf("Delete `character`\n");
            delete_role();
        } else if(choice == 5) {
            printf("Get `movie`\n");
            get_movie();
        } else if(choice == 6) {
            printf("Get `character`\n");
            get_role();
        } else if(choice == 7) {
            printf("Update `movie`\n");
            update_movie();
        } else if(choice == 8) {
            printf("Update `character`\n");
            update_role();
        } else if(choice == 9) {
            printf("Print all `movies`\n");
            print_all_movies();
        } else if(choice == 0) {
            printf("Print all `characters`\n");
            print_all_roles();
        } else {
            test_reading();
        }
    }
    return 1;
}

void save_databases(){
}

int main() {

    movie_database db = init_database();
    while(run_interface());
    save_databases();
    printf("Good bye!\n");
    return 0;
}
