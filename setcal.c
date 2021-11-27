#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define member_len 30
#define argument_count 2
#define illegal_str_count 6

char illegal_strings[6][5] = {"U", "S", "R", "c", "true", "false"};  //Strings unable to be used as universe members


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

typedef struct {        //Array of relation arrays
    Rel_t *relation;
    int rel_number;
} Rel_arrs;



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

typedef struct {        //Array of set arrays
    Set_t *set;
    int set_number;
} Set_arrs;

/*                                                      //NEED FIX
int illegal_parse(char *llegal_strings, char *str) {
    for (int i = 0; i < illegal_str_count; i++) {
        if (strcmp(str, illegal_strings[i]) == 0)
            return 0;
    }
    return 1;
} */

        //LOADING THE UNIVERSE LINE//
int load_uni_line(char *c, FILE **fp) {        
    char *buffer = malloc(sizeof(char));
    int str_size = 0;                                                  
    int str_count = 0;                                                                       

    uni_array = NULL;

    *c = fgetc(*fp);
    if (*c != ' ') {     //Checks if there's a non-space character after the U character
        fprintf(stderr, "Error: Incorrect input syntax\n");       //Also gets rid of the space :)
        return -1;
    }

    while (*c != '\n') {
        *c = fgetc(*fp);
        printf("%c\n", c);
        /*
        if ( (*c < 'A') || ((*c > 'Z') && (*c < 'a')) || (*c > 'z') ) {     //Parses non-alphabetical characters
            fprintf(stderr, "Error: Non-alphabetical character used\n");    //NEED_FIX
            return -1;
            break;
        } */
        if (*c != ' ') {        //Loading chars into buffer while the char in file isn't a SPACE char
            ++str_size;
            buffer = (char *) realloc(buffer, str_size * sizeof(char));
            buffer[str_size - 1] = *c;
        }

        if (*c == ' ') {        //Loading string into the Universe member structure, resetting buffer
            uni_array = (Universe_t *) realloc(uni_array, str_count * sizeof(Universe_t));
            uni_array[str_count].member = malloc(str_size * sizeof(char));
            strcpy(uni_array[str_count].member, buffer);
            uni_array[str_count].member_num = str_count;

            for (int i = 0; i < str_count; i++) {       //Comparing strings with previous strings saved into the array
                if (strcmp(uni_array[str_count].member, uni_array[i].member) == 0) {
                    fprintf(stderr, "Error: Multiple equal universe members\n");
                    return -1;
                    break;
                }        
            }

            //NEED FIX
            //if (illegal_parse(illegal_strings, buffer) == 0) {
            for (int i = 0; i < illegal_str_count; i++) {
                if (strcmp(buffer, illegal_strings[i]) == 0) {
            
                    fprintf(stderr, "Error: Illegal strings used\n");
                    return -1;
                    break;
                }
            }

            ++str_count;
            str_size  = 0;
            buffer = NULL;
        }

    }
    free(buffer);

    return str_count;
}

/*                                          //SET LINE LOADING WIP
int load_set_line(char *c, FILE **fp) {

} */
    

        //////MAIN//////

int main(int argc, char* argv[])   {

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
    int uni_mem_count;   //Number of members in universe

    while( ! (feof(fp)) )  {
        char c = fgetc(fp);
        ++line_pos;

        if (line_pos == 1) {

            switch (c) {

                case 'U':               //Universe Function
                    if (line_count == 1) {
                        if (load_uni_line(&c, &fp) == -1)
                            return EXIT_FAILURE;
                        
                        else uni_mem_count = (load_uni_line(&c, &fp));
                        
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
    }

    for (int i = 0; i <= uni_mem_count; i++) {
        printf("%s, ",uni_array[i].member);
    }

    return 0;
}