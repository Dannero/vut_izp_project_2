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




        //LOADING LINE FROM FILE//
char *load_line(FILE **fp) {
    char *line_str = malloc(sizeof(char));
    if (line_str == NULL) 
       return NULL;
    line_str[0] = '\0';
    char c;

    while (1) {
        c = fgetc(*fp);

        if (c == '\n'  || c == EOF) 
            break;

        line_str = (char*) realloc(line_str, strlen(line_str) + sizeof(char)*2);  //2 --> One for new character, one for trailing zero 
        if (line_str == NULL) 
            return NULL;
        strncat(line_str, &c, 1);
    }
    return line_str;
    free(line_str);
}




int second_char_check(char **str_line) {        //Checking if the second char in line is SPACE and passes through                    
    if (*str_line[1] != ' ') {                  //it to make input loading easier
        fprintf(stderr, "Error: Incorrect input syntax\n");
        return 0;
    }    
    return 1;
}

 
        //LOADING UNIVERSE//
void load_universe(char *str_line[], int *uni_mem_count, bool *uni_load_fail, char ***uni_array) {
    char c;
    int str_count = 0;
    int str_len = strlen(*str_line);
    char *buffer = malloc(sizeof(char));
    uni_array[str_count] = malloc(sizeof(char));
    if (buffer == NULL  || **uni_array == NULL) {
        fprintf(stderr, "Error occured during memory allocation");
        *uni_load_fail = true;
    }


    for (int i = 0; i < str_len; i++) {       //i from 2, since string[0] is the function and string[1] is a SPACE char
        c = *str_line[i];
        printf("%s\n", *str_line);
        printf("%c\n", c);
        if (i >= 2) {
            if (c != ' ' && c != EOF) {
                buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
                if (buffer == NULL) {
                    fprintf(stderr, "Error occured during memory allocation");
                    *uni_load_fail = true;
                }
                strncat(buffer, &c, 1);
                printf("%s\n", buffer);
            }

            if (c == ' ' || c == '\0') {
                str_count++;
                *uni_array = (char **) realloc(uni_array, str_count * strlen(buffer));
                strcpy(*uni_array[str_count - 1], buffer);

                for (int i = 0; i < str_count - 1; i++) {       //Comparing strings with previous strings saved into the array
                    if (strcmp(*uni_array[str_count], *uni_array[i]) == 0) {
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

                printf("%s\n", buffer);
                
            }
        }     
        free(buffer);
        *uni_mem_count = str_count;
    }
}
    

        //////MAIN//////

int main(int argc, char* argv[])   {

    if (argc != argument_count) {   //Checking the correct number of arguments
        fprintf(stderr,"Error: Wrong argument count!\n");
        return EXIT_FAILURE;
    }

    FILE *fp; 
    fp = fopen(argv[1],"r");
    //File opening check
    if (fp == NULL) {
        return EXIT_FAILURE;
        fprintf(stderr,"Error: Opening file not successful\n");
    }

    (void) argc;
    (void) argv;
    int line_count = 0;  //Number of lines
    int uni_mem_count = 0;   //Number of members in universe
    bool uni_load_fail = false;

    while (! (feof(fp))) {
        char *str_line = load_line(&fp);
        printf("%s\n", str_line);
        line_count++;

        //if (! (second_char_check(&str_line))) 
            //return EXIT_FAILURE;

        
        
        switch(str_line[0]) {
            case 'U':
                if (line_count == 1) {
                    load_universe(&str_line, &uni_mem_count, &uni_load_fail, &uni_array); //Loading line into Universe arrays
                    if (uni_load_fail == true) 
                        return EXIT_FAILURE;
                    
                }

                else {
                    fprintf(stderr,"Error: Universe not declared at line 1");
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
                        return EXIT_FAILURE;
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


    fclose(fp);


    return 0;
}