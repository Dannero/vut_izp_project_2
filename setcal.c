#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define member_len 30
#define argument_count 2
#define illegal_str_count 6

char illegal_strings[6][5] = {"U", "S", "R", "c", "true", "false"};  //Strings unable to be used as universe members


//UNIVERSE STRUCTURES//
char **uni_array;   //Array of universe members


//RELATION STRUCTURES//
typedef struct {     //Structure for a relation member
    char *rel_x;
    char *rel_y;
} Rel_member_t;

typedef struct {        //Relation array
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



int second_char_check(char *c, FILE **fp) {        //Checking if the second char in line is SPACE and passes through
    *c = fgetc(*fp);                    //it to make input loading easier
    if (*c != ' ') {
        fprintf(stderr, "Error: Incorrect input syntax\n");
        return 0;
    }    
    return 1;
}

        //LOADING THE UNIVERSE LINE//
void load_uni_line(char *c, FILE **fp, bool *uni_load_fail, int *uni_mem_count) {        
    char *buffer = malloc(sizeof(char));
    int str_size = 0;                                                  
    int str_count = 0;  
                                                                      
    uni_array = malloc(sizeof(char));


    while (*c != '\n') {
        *c = fgetc(*fp);
        printf("Nacitavany char: %c \n", *c);
        
        if ( ((*c < 'A') || ((*c > 'Z') && (*c < 'a')) || (*c > 'z')) && (*c != ' ') ) {     //Parses non-alphabetical characters
            fprintf(stderr, "Error: Non-alphabetical character used\n");   
            break;
        } 

        if (*c != ' ') {        //Loading chars into buffer while the char in file isn't a SPACE char
            ++str_size;
            buffer = (char *) realloc(buffer, str_size * sizeof(char));                              
            buffer[str_size - 1] = *c;
            printf("String size: %d\n", str_size);
            printf("Buffer: %s\n", buffer);
        }

        if (*c == ' ') {        //Loading string into the Universe member structure, resetting buffer
            uni_array = (char **) realloc(uni_array, str_count * sizeof(str_size * sizeof(char)));
            strcpy(uni_array[str_count], buffer);
            

            for (int i = 0; i < str_count; i++) {       //Comparing strings with previous strings saved into the array
                if (strcmp(uni_array[str_count], uni_array[i]) == 0) {
                    fprintf(stderr, "Error: Multiple equal universe members\n");
                    *uni_load_fail = true;
                    break;
                }        
            }
            
            for (int i = 0; i < illegal_str_count; i++) {
                if (strcmp(buffer, illegal_strings[i]) == 0) {
            
                    fprintf(stderr, "Error: Illegal strings used\n");
                    *uni_load_fail = true;
                    break;
                }
            }

            printf("%s", *buffer);

            str_count++;
            str_size  = 0;
            free(buffer);
        }

    }
    *uni_mem_count = str_count; 
} 



                //!!!!!WORK IN PROGRESS!!!!!    SET LINE LOADING
/*void load_set_line(char *c, FILE **fp, bool *set_load_fail, int uni_mem_count) {
    char *buffer = malloc(sizeof(char));
    int str_size = 0;
    int str_count = 0;
    Set_member_t set_member;
    Set_t set_array;

    while (*c != '\n') {
        *c = fgetc(*fp);

        if (*c != ' ') {
            str_size++;
            buffer = (char *) realloc (buffer, str_size * sizeof(char));
            buffer[str_size - 1] = *c;
        }

        if (*c == ' ') {
            for (int i = 0; i < uni_mem_count; i++) {
                if (strcmp(buffer, uni_array[i]) != 0) {        //Checking for members outside the Universe
                    fprintf(stderr, "Error: String does not belong into the Universe\n");
                    *set_load_fail = true;
                }
                else set_member.set_mem_num = i;
            }

            for (int i = 0; i < str_count; i++) {               //Checking for repeating members
                if (strcmp(buffer, set_array.member->set_mem[i]) == 0) {       
                    fprintf(stderr, "Error: Multiple equal set members present\n");
                    *set_load_fail = true;
                }
            }


            set_member.set_mem = (char*) realloc(set_member.set_mem, str_size * sizeof(char));
            set_array = (Set_t)realloc(set_array, ((str_count + 1) * sizeof(Set_member_t)));        //Incompatible NEED FIX
            strcpy(set_array.member[str_count], buffer);
            set_array.set_size = str_count + 1;

        str_count++;
        str_size = 0;
        free(buffer);
        }
    }
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
    bool uni_load_fail = false;

    while( ! (feof(fp)) )  {
        char c = fgetc(fp);
        ++line_pos;

        if (line_pos == 1) {

            switch (c) {

                case 'U':               //Universe Function
                    if (line_count == 1) {

                        if (! second_char_check(&c, &fp)) 
                            return EXIT_FAILURE;

                        load_uni_line(&c, &fp, &uni_load_fail, &uni_mem_count); //Loading line into Universe arrays
                        if (uni_load_fail == true) 
                            return EXIT_FAILURE;
                    }

                    else {
                        fprintf(stderr, "Error: Universe not at line 1\n");
                        return EXIT_FAILURE;
                    }
                    break;

                case 'S':               //Set Function
                    if (line_count != 1) {

                        if (! second_char_check(&c, &fp)) 
                            return EXIT_FAILURE;
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

    for (int i = 0; i < uni_mem_count; i++) {
        printf("%s, ",uni_array[i]);
    }

    printf("%d", uni_mem_count);

    return 0;
}