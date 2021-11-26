#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define member_len 30
#define argument_count 2

//UNIVERSE STRUCTURES//
typedef struct {      //Structure for a universe member
    char *member;
    int member_num;
} Universe_t;

Universe_t *uni_array;   //Array of universe members


//RELATION STRUCTURES//
typedef struct {     //Structure for a relation member
    char *rel_x;
    char *rel_y;
} Rel_member_t;

typedef struct {
    Rel_member_t *member;
    int rel_size;
} Rel_t;

Rel_t *multi_rel_arrays; //Array of relation arrays


//SET STRUCTURES//

typedef struct {        //Structure for a set member
    char *set_mem;
    int set_mem_num;
} Set_member_t;

typedef struct {
    Set_member_t *member;
    int set_size;
    int set_index;
} Set_t;

Set_t *multi_sets;      //Array of set arrays

void empty(Set_t * set){
    if(!set->set_size){
        printf("True\n");
    }
    else{
        printf("False\n");
    }
}

void card(Set_t * set){

}

int main(int argc, char* argv[])
{
    char universe[3][30]={"apple", "banana", "orange"};
    char universe_2[3][30]={"apple", "banana", "mango"};
    char* new;
    int len;

    multi_sets = NULL;
    multi_sets = realloc(multi_sets,2 * sizeof(Set_t));
    if(multi_sets == NULL) return EXIT_FAILURE;
    multi_sets[0].member = NULL;
    multi_sets[0].member = realloc(multi_sets[0].member, 3 * sizeof(Set_member_t));
    if (multi_sets[0].member == NULL) {
        return EXIT_FAILURE;
    }
    multi_sets[0].set_size = 0;
    for (int i = 0; i < 3; i++) {
        len = strlen(universe[i]);
        new = malloc(len + 1);
        multi_sets[0].member[i].set_mem = malloc(len+1);
        strcpy(new, universe[i]);
        memcpy(multi_sets[0].member[i].set_mem, new, len + 1);
        multi_sets[0].member[i].set_mem_num = i;
        free(new);
        multi_sets[0].set_size++;
    }
    for (int i = 0; i < 3; i++) {
        //free(multi_sets[0].member[i].set_mem);
        printf("%s ", multi_sets[0].member[i].set_mem);
    }
    printf("\n");

    multi_sets[1].member = NULL;
    multi_sets[1].member = realloc(multi_sets[1].member, 3 * sizeof(Set_member_t));
    if (multi_sets[1].member == NULL) {
        return EXIT_FAILURE;
    }
    multi_sets[1].set_size = 0;
    for (int i = 0; i < 3; i++) {
        len = strlen(universe_2[i]);
        new = malloc(len + 1);
        multi_sets[1].member[i].set_mem = malloc(len+1);
        strcpy(new, universe_2[i]);
        memcpy(multi_sets[1].member[i].set_mem, new, len + 1);
        multi_sets[1].member[i].set_mem_num = i;
        free(new);
        multi_sets[1].set_size++;
    }
    for (int i = 0; i < 3; i++) {
        //free(multi_sets[1].member[i].set_mem);
        printf("%s ", multi_sets[1].member[i].set_mem);
    }
    printf("\n");

    empty(&multi_sets[0]);

    if (argc != argument_count) {   //Checking the correct number of arguments
        fprintf(stderr,"Error: Wrong argument count!\n");
        return EXIT_FAILURE;
    }

    FILE *fp = fopen(argv[1],"r");
    //File opening check
    if (fp == NULL) {
        return EXIT_FAILURE;
        fprintf(stderr,"Error: Opening file not successful\n");
    }

    (void) argc;
    (void) argv;
    int line_count = 1;  //Number of lines
    int line_pos = 0;    //Position in a line

    while( ! (feof(fp)) )  {
        char c = fgetc(fp);
        ++line_pos;

        if (line_pos == 1) {

            switch (c) {

                case 'U':               //Universe Function
                    if (line_count == 1) {
                        //universe_load_function
                    }

                    else {
                        fprintf(stderr, "Error: Universe not at line 1\n");
                        return EXIT_FAILURE;
                    }
                    break;

                case 'S':               //Set Function
                    if (line_count != 1) {
                        //set_load_function
                    }

                    else {
                        fprintf(stderr, "Error: Set at line 1\n");
                        return EXIT_FAILURE;
                    }
                    break;

                case 'R':               //Relation Function
                    if (line_count != 1) {
                        //relation_load_function
                    }

                    else {
                        fprintf(stderr, "Error: Relation at line 1\n");
                        return EXIT_FAILURE;
                    }
                    break;

                case 'C':               //Command Function
                    if (line_count !=1) {
                        //find_and_do_command
                    }

                    else {
                        fprintf(stderr, "Error: Command at line 1\n");
                        return EXIT_FAILURE;
                    }
                    break;

                default:                //Invalid function
                    fprintf(stderr, "Error: Invalid Function at line %d\n", line_count);
                    return EXIT_FAILURE;
                    break;
            }


        }

        if (c == '\n') {
            line_count++;
            line_pos = 0;
        }

        printf("%c", c);

    }

    printf("\n%d",line_count);

    return 0;
}