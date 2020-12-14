#include "io_functions.h"

int get_length(const char* buffer){
    int length = 0;
    while(buffer[length] != '\0' && buffer[length] != '\n')
        length++;
    return length;
}

int get_user_choice(){
    int choice;
    char *buffer;
    size_t bufsize = 1;
    size_t characters;

    scanf("%d", &choice);

    if(choice < 0 || choice > 9)
        return -1;
    else
        return choice;
}

void read_string_into_array(char* array, int max_size){
    char choice;
    char *buffer;
    size_t bufsize = 99;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }

    scanf("%s", &buffer);
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    printf("%d", strlen(buffer));
    characters = 5;
    printf("len: %d\n", characters);
    if(max_size < characters){
        characters = max_size;
    }
    printf("len: %d\n", characters);
    for(int i = 0; i < characters; i++){
        printf("a");
        char c = buffer[i];
        printf("b");
        array[i] = c;
    }
    printf("len: %d\n", characters);
    fflush(NULL);
    array[5] = '\0';
    printf("len: %d\n", characters);
    free(buffer);
}

void read_int(int* x){
    char choice;
    char *buffer;
    size_t bufsize = 10;
    size_t characters;

    buffer = (char *)malloc(bufsize * sizeof(char));
    if( buffer == NULL)
    {
        perror("Unable to allocate buffer");
        exit(1);
    }
    characters = get_length(fgets(buffer,bufsize,stdin));

    *x = 0;
    int c = 0;
    for(int i = 0; i < characters; i++){
        *x *= 10;
        c = (int) (buffer[i] - '0');
        if(c < 0 || c > 9){
            *x = -1;
            break;
        } else {
            *x += c;
        }
    }
    free(buffer);
}

char* int_to_string(int a){
    int b = a;
    int length = 0;
    while(b > 0) {
        b /= 10;
        length++;
    }
    if(length == 0) length++;
    char* result = (char *)malloc(length * sizeof(char));
    for(int i = length - 1; i >= 0; i--){
        result[i] = (char) ('0' + (a % 10));
        a /= 10;
    }
    return result;
}

void put_int(int x){
    char* string_id = int_to_string(x);
    puts(string_id);
    free(string_id);
}
