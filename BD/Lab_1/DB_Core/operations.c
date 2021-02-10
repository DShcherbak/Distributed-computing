#include "operations.h"


int get_movie_row(Database* database, int movie_id);
Movie get_movie_by_row(Database* database, int row);

Movie get_movie_by_id(Database* database, int movie_id);
Role get_role_by_id(Database* database, int movie_id, int role_id);

char* get_film_name_by_id_U(int id);

void delete_movie_roles(Database* database, int movie_id);
void move_last_movie_to_deleted_row(Database* database, int deleted_movie_id);
void delete_role_by_id(Database* database, int movie_id, int role_id);

/////////////////////////////////////////////
/*
 *
 * MAIN FUNCTIONS
 *
 */
/////////////////////////////////////////////


void insert_movie(Database* database){
    char name[101];
    int year = 2000;
    printf("Insert movie name: ");
    read_string_into_array(name, 100);
    printf("Insert movie release year: ");
    read_int(&year);
    //insert_movie(name, year);
    Movie new_movie;
    new_movie.id = database->max_movie_id++;
    new_movie.name = name;
    new_movie.year = year;
    insert_movie_to_index_table(new_movie.id, &database->movies_count, database->index_table);
    update_index_file(0, NULL, NULL);
    insert_movie_to_file(database, new_movie);
    printf("New movie : %s will be aired in the year %d\n", name, year);
    printf("-----------------------\n");
}

void insert_role(Database* database){
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

    Role role;
    role.id = database->max_role_id++;
    role.name = name;
    role.age = age;
    role.movie_id = film_id;
    int cnt_roles = database->roles_count;
    int row = get_movie_row(database, role.movie_id);
    int prev_position = update_movie_after_insertion(database, row, cnt_roles);
    insert_role_to_file(database, role, cnt_roles, prev_position);
    free(film_name);

    printf("-----------------------\n");
}

void get_movie(Database* database){
    int id;
    printf("Insert movie id: ");
    read_int(&id);
    Movie movie = get_movie_by_id(database, id);
    print_movie(movie);
}

void get_role(Database* database){
    int movie_id, role_id;
    printf("Insert movie id: ");
    read_int(&movie_id);
    printf("Insert role id: ");
    read_int(&role_id);
    Role role = get_role_by_id(database, movie_id, role_id);
    print_role(role);
}

void delete_movie(Database* database){
    char name[101];
    int id = -1;
    printf("Insert movie id");
    read_int(&id);
    int year = 0;
    delete_movie_roles(database, id);
    move_last_movie_to_deleted_row(database, id);

    printf("New movie : %s will be aired in the year %d\n", name, year);
    printf("-----------------------\n");
}

void delete_role(Database* database){
    int movie_id, role_id;
    printf("Insert movie id: ");
    read_int(&movie_id);
    printf("Insert role id: ");
    read_int(&role_id);

    Role role = get_role_by_id(database, movie_id, role_id);
    delete_role_by_id(database, movie_id, role_id);

    if(role.id > 0){
        printf("Deleted role: ");
        print_role(role);
    } else {
        printf("No such element!");
    }

}

void update_movie(Database* database){
    int id;
    printf("Insert movie id: ");
    read_int(&id);
    int row = get_movie_row(database, id);
    if (row == -1){
        printf("No such element!");
        return;
    }
    char name[101];
    int year = 2000;
    printf("Insert movie new name: ");
    read_string_into_array(name, 100);
    printf("Insert movie new release year: ");
    read_int(&year);
    //insert_movie(name, year);
    Movie updated_movie;
    updated_movie.id = id++;
    updated_movie.name = name;
    updated_movie.year = year;
    update_movie_in_file(database, row, updated_movie);
}

void update_role(Database* database){
    int movie_id;
    printf("Insert movie id: ");
    read_int(&movie_id);
    int row = get_movie_row(database, movie_id);
    if (row == -1){
        printf("No such element!");
        return;
    }
    int role_id;
    printf("Insert role id: ");
    read_int(&role_id);
    Role role = get_role_by_id(database, movie_id, role_id);
    int starting_position = 0, cnt_roles = 0;
    get_additional_info_by_movie_row(database, row, &starting_position, &cnt_roles);
    if (get_role_by_id(database, movie_id, role_id).id < 0){
        printf("No such element!");
        return;
    }
    char name[101];
    int film_id;
    int age;
    printf("Insert characters name: ");
    read_string_into_array(name, 100);
    printf("Insert characters age: ");
    read_int(&age);
    printf("Insert characters film id: ");
    read_int(&film_id);
    role.age = age;
    role.name = name;
    role.movie_id = film_id;
    update_role_in_file(database, starting_position, role);
}

void print_all_movies(Database* database){
    int cnt = database->movies_count;
    printf("Total number of films: %d", &cnt);
    for (int i = 0; i < cnt; ++i) {
        int row = database->index_table[i * 2 + 1];
        print_movie(get_movie_by_row(database, row));
    }    
}

void print_all_roles(Database* database){
    int cnt_roles = database->roles_count;
    printf("Total number of roles: %d", cnt_roles);
    Role roles[20];

    int movies_cnt = database->movies_count;
    for (int movie_id = 0; movie_id < movies_cnt; ++movie_id) {
        int starting_position = 0;
        int row = database->index_table[movie_id * 2 + 1];
        get_additional_info_by_movie_row(database, get_movie_row(database, movie_id), &starting_position, &cnt_roles);
        get_all_movie_roles(database, movie_id, cnt_roles);
        for(int role_id = 0; role_id < cnt_roles; role_id++){
            print_role(roles[role_id]);
        }
    }
}


/////////////////////////////////////////////
/*
 *
 * ADDITIONAL FUNCTIONS
 *
 */
/////////////////////////////////////////////

int get_movie_row(Database* database, int movie_id) {
    int left = 0;
    int right = database->movies_count - 1;
    while (right - left > 1) {
        int middle = (right + left) / 2;
        if (database->index_table[middle * 2] < movie_id)
            left = middle;
        else
            right = middle;
    }
    if (database->index_table[left * 2] == movie_id)
        return database->index_table[left * 2 + 1];
    if (database->index_table[right * 2] == movie_id)
        return database->index_table[right * 2 + 1];
    return -1;
}


Movie get_movie_by_row(Database* database, int row) {
    FILE* movie_file_pointer = fopen(database->movies_file, "rb");
    unsigned size_of_one_item = sizeof(Movie) + 2 * sizeof(int);
    unsigned offset = size_of_one_item * row;
    fseek(movie_file_pointer, offset, SEEK_SET);
    Movie movie;
    fread(&movie, sizeof(Movie), 1, movie_file_pointer);
    fclose(movie_file_pointer);
    return movie;
}

Movie get_movie_by_id(Database* database, int movie_id) {
    for (int i = 0; i < database->movies_count; ++i) {
        if (database->index_table[i * 2] == movie_id) {
            int row = database->index_table[i * 2 + 1];
            return get_movie_by_row(database, row);
        }
    }
    Movie movie = {-1, 0, 0, ""};
    return movie;
}

Role get_role_from_file(Database* database, int start_row, int role_id) {
    FILE* role_file_pointer = fopen(database->roles_file, "rb");
    int cur_row = start_row;
    int size_of_one_row = sizeof(Role) + sizeof(int);
    while (cur_row != -1) {
        unsigned offset = size_of_one_row * cur_row + sizeof(int);
        fseek(role_file_pointer, offset, SEEK_SET);
        Role cur_role;
        fread(&cur_role, sizeof(cur_role), 1, role_file_pointer);
        if (cur_role.id == role_id)
            return cur_role;
        fread(&cur_row, sizeof(int), 1, role_file_pointer);
    }
    Role role = {-1, -1, "", ""};
    return role;
}

Role get_role_by_id(Database* database, int movie_id, int role_id) {
    int row = get_movie_row(database, movie_id);
    if (row == -1) {
        Role role = {-1, -1, "", ""};
        return role;
    }
    int position, cnt_roles;
    get_additional_info_by_movie_row(database, row, &position, &cnt_roles);
    return get_role_from_file(database, position, role_id);
}

int get_role_id_by_row(Database* database, int row){
    FILE* role_file_pointer = fopen(database->roles_file, "rb");
    int size_of_one_item = sizeof(int) + sizeof(Role);
    unsigned offset = size_of_one_item * row + sizeof(int);
    Role role;
    fseek(role_file_pointer, offset, SEEK_SET);
    fread(&role, sizeof(Role), 1, role_file_pointer);
    return role.id;
}

void delete_movie_roles(Database* database, int movie_id) {
    int movie_row = get_movie_row(database, movie_id);
    int cnt_roles, role_row;
    get_additional_info_by_movie_row(database, movie_row, &role_row, &cnt_roles);
    if (role_row == - 1) {
        return;
    }
    int role_id = get_role_id_by_row(database, role_row);
    while(role_row != - 1) {
        delete_role_by_id(database, movie_id, role_id);
        get_additional_info_by_movie_row(database, movie_row, &role_row, &cnt_roles);
        if (role_row == - 1) {
            return;
        }
        role_id = get_role_id_by_row(database, role_row);
    }
}

void update_row_in_index_file(Database* database, int movie_id, int new_row) {
    for (int i = 0; i < database->movies_count; ++i) {
        if (database->index_table[i * 2] == movie_id) {
            database->index_table[i * 2 + 1] = new_row;
        }
    }
}

void update_movie_after_role_deleted(Database* database, int movie_id, int role_row) {
    int position, cnt;
    int row = get_movie_row(database, movie_id);
    get_additional_info_by_movie_row(database, row, &position, &cnt);
    update_additional_movie_info(database, row, role_row, cnt);
}

void move_last_item_after_role_deleted(Database* database, int deleted_row) {
    int cnt_roles = database->roles_count;
    if (cnt_roles == deleted_row)
        return;
    FILE* role_file_pointer = fopen(database->roles_file, "r+b");
    int size_of_one_item = sizeof(Role) + sizeof(int);
    unsigned offset = size_of_one_item * (cnt_roles - 1) + sizeof(int);
    fseek(role_file_pointer, offset, SEEK_SET);
    Role role;
    int next_role;
    fread(&role, sizeof(Role), 1, role_file_pointer);
    fread(&next_role, sizeof(int), 1, role_file_pointer);
    offset = size_of_one_item * (deleted_row) + sizeof(int);
    fseek(role_file_pointer, offset, SEEK_SET);
    fwrite(&role, sizeof(Role), 1, role_file_pointer);
    fwrite(&next_role, sizeof(int), 1, role_file_pointer);
    fclose(role_file_pointer);
    update_movie_after_role_deleted(database, role.movie_id, deleted_row);
}

void dec_cnt_sons(Database* database, int movie_id) {
    int position, cnt;
    int row = get_movie_row(database, movie_id);
    get_additional_info_by_movie_row(database, row, &position, &cnt);
    if (cnt == 1)
        position = -1;
    update_additional_movie_info(database, row, position, cnt - 1);
}

void delete_role_from_file(Database* database, int movie_id, int role_id, int start_row) {
    FILE* role_file_pointer = fopen(database->roles_file, "r+b");
    int cur_row = start_row;
    int prev_row = -1;
    int size_of_one_row = sizeof(Role) + sizeof(int);
    int k = 0;
    while (cur_row != -1 && k++ < 10) {
        unsigned offset = size_of_one_row * cur_row + sizeof(int);
        fseek(role_file_pointer, offset, SEEK_SET);
        Role cur_role;
        fread(&cur_role, sizeof(Role), 1, role_file_pointer);
        if (cur_role.id == role_id){
            int next_row;
            fread(&next_row, sizeof(int), 1, role_file_pointer);
            if (prev_row == -1) {
                //update movie field;
                update_movie_after_role_deleted(database, movie_id, next_row);
            }
            else {
                // update prev role ptr
                offset = size_of_one_row * prev_row + sizeof(int) + sizeof(Role);
                fseek(role_file_pointer, offset, SEEK_SET);
                fwrite(&next_row, sizeof(int), 1, role_file_pointer);
            }
            fclose(role_file_pointer);
            move_last_item_after_role_deleted(database, cur_row);
            return;
        }
        prev_row = cur_row;
        fread(&cur_row, sizeof(int), 1, role_file_pointer);
    }
    fclose(role_file_pointer);
}

void set_cnt_roles(Database* database, int value) {
    FILE* role_file_pointer = fopen(database->roles_file, "r+b");
    fwrite(&value, sizeof(int), 1, role_file_pointer);
    fclose(role_file_pointer);
}

void move_last_movie_to_deleted_row(Database* database, int deleted_movie_id){
    int movie_row = get_movie_row(database, deleted_movie_id);
    if (movie_row != database->movies_count - 1) {
        Movie last_movie = get_movie_by_row(database, database->movies_count - 1);
        print_movie(last_movie);
        int cnt_roles, position_first_role;
        get_additional_info_by_movie_row(database, database->movies_count - 1,
                                         &position_first_role, &cnt_roles);
        FILE *movie_file_pointer = fopen(database->movies_file, "r+b");
        int one_item_size = sizeof(Movie) + 2 * sizeof(int);
        unsigned offset = one_item_size * movie_row;
        fseek(movie_file_pointer, offset, SEEK_SET);
        fwrite(&last_movie, sizeof(Movie), 1, movie_file_pointer);
        fwrite(&position_first_role, sizeof(int), 1, movie_file_pointer);
        fwrite(&cnt_roles, sizeof(int), 1, movie_file_pointer);
        fclose(movie_file_pointer);
        update_row_in_index_file(database, last_movie.id, movie_row);
    }
    shift_movies_in_index_file(deleted_movie_id, NULL, NULL);
    update_index_file(0, NULL, NULL);
}


void delete_role_by_id(Database* database, int movie_id, int role_id) {
    if (get_role_by_id(database, movie_id, role_id).id == -1)
        return;
    int start_position, cnt_sons;
    int row = get_movie_row(database, movie_id);
    get_additional_info_by_movie_row(database, row, &start_position, &cnt_sons);
    delete_role_from_file(database,movie_id,role_id, start_position);
    int cnt_roles = database->roles_count;
    dec_cnt_sons(database, movie_id);
    set_cnt_roles(database, cnt_roles - 1);
}



int get_cnt_movie_roles(Database* database, int movie_id) {
    int position, cnt_roles;
    get_additional_info_by_movie_row(database, get_movie_row(database, movie_id), &position, &cnt_roles);
    return cnt_roles;
}
/*
void utl_movies(Database* database) {
    FILE* movie_file_pointer = fopen(database->movies_file, "rb");
    int movies_count = database->movies_count;
    for (int i = 0; i < movies_count; ++i) {
        Movie cur;
        int son_position;
        int cnt_sons;
        fread(&cur, sizeof(Movie), 1, movie_file_pointer);
        fread(&son_position, sizeof(int), 1, movie_file_pointer);
        fread(&cnt_sons, sizeof(int), 1, movie_file_pointer);
        printf("%d %s %d %d %d %d\n",
               cur.id, cur.full_name, cur.age, cur.rating, son_position, cnt_sons);
    }
    fclose(movie_file_pointer);
}

void utl_index_movies(Database* database) {
    FILE* movie_index_file_pointer = fopen(database->movies_index_file, "rb");

    int movies_count;
    fread(&movies_count, sizeof(int), 1, movie_index_file_pointer);
    int table[2*movies_count];
    if (movies_count != 0) {
        fread(table, sizeof(int), movies_count * 2, movie_index_file_pointer);
    }
    for (int i = 0; i < movies_count;++i)
        printf("%d %d\n", table[2 * i], table[2 * i + 1]);
    printf("\n");
    fclose(movie_index_file_pointer);
}

void utl_roles(Database* database) {
    FILE* role_file_pointer = fopen(database->roles_file, "rb");

    int cnt_roles;
    fread(&cnt_roles, sizeof(int), 1, role_file_pointer);
    printf("%d\n", cnt_roles);
    for (int i = 0; i < cnt_roles; ++i) {
        Role club_role;
        int previous_row;
        fread(&club_role, sizeof(Role), 1, role_file_pointer);
        fread(&previous_row, sizeof(int), 1, role_file_pointer);
        printf("%d %d %s %s %d\n", club_role.id, club_role.movie_id,
               club_role.club_name, club_role.position, previous_row);
    }
    fclose(role_file_pointer);
}

*/

void print_movies(Database *database) {
    FILE* movie_file_pointer = fopen(database->movies_file, "rb");
    int movies_count = database->movies_count;
    for (int i = 0; i < movies_count; ++i) {
        Movie cur;
        int son_position;
        int cnt_sons;
        fread(&cur, sizeof(Movie), 1, movie_file_pointer);
        fread(&son_position, sizeof(int), 1, movie_file_pointer);
        fread(&cnt_sons, sizeof(int), 1, movie_file_pointer);
        print_movie(cur);
    }
    fclose(movie_file_pointer);
}

void print_roles(Database *database) {
    FILE* role_file_pointer = fopen(database->roles_file, "rb");

    int cnt_roles;
    fread(&cnt_roles, sizeof(int), 1, role_file_pointer);

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
