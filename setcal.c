#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define argument_count 2
#define max_member_len 30
#define illegal_str_count 6
#define max_line_count 1000

char illegal_strings[6][5] = {"U", "S", "R", "c", "true", "false"};  //Strings illegal to be used as universe members


//UNIVERSE STRUCTURES//  
typedef struct {        //Array of universe members
    char **uni_member;
    int member_count;
} Universe_t;



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


//RELATION STRUCTURES//
typedef struct {     //Structure for a relation member
    char *rel_x;
    int rel_x_index;
    char *rel_y;
    int rel_y_index;
} Rel_member_t;

typedef struct {        //Relation array
    Rel_member_t *member;
    int rel_size;
    int rel_index;
} Rel_t;




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




int second_char_check(char *str_line) {        //Checking if the second char in line is SPACE                    
    if (str_line[1] != ' ') {                 
        fprintf(stderr, "Error: Incorrect input syntax\n");
        return 0;
    }    
    return 1;
}

int char_check (char c) {                   //Checks if char is alphabetical
    if ( ( (c < 'A') || ((c > 'Z') && (c < 'a')) || (c > 'z') ) && (c != ' ') && (c !='\0') ) {        //Error z nejakeho dovodu lol xd
        fprintf(stderr, "Error: Non-alphabetical character used\n"); 
        return 0;
    }
    return 1;
}

void buffer_alloc_check (bool *alloc_fail, char *buffer) {  //Checking buffer allocation success
    if (buffer == NULL) {
        fprintf(stderr, "Error occured during buffer memory allocation\n");
        *alloc_fail = true;        
    }
}

 
        //LOADING UNIVERSE//
void load_universe(char *str_line, bool *uni_load_fail, Universe_t *uni_array) {
    char c;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    uni_array->member_count  = 0;
    uni_array->uni_member = malloc(sizeof(char));  //1 row * 1 column = 1 char
    buffer_alloc_check(&uni_load_fail, &buffer);


    if (uni_array->uni_member == NULL) {
        fprintf(stderr, "Error occured during universe array memory allocation\n");
        *uni_load_fail = true;
    }


    for (unsigned int i = 2; i <= strlen(str_line); i++) {     //i from 2, since string[0] is the function and string[1] is a SPACE char  
        c = str_line[i];
        if (! char_check(c)) {    //Checking for non-alphabetical characters
            *uni_load_fail = true;  
            break;            
        }

        if (c != ' ') {             //Loading char into buffer is char is not SPACE
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            buffer_alloc_check(&uni_load_fail, &buffer);
            
            if (strlen(buffer) > max_member_len) {
                fprintf(stderr, "Error: Universe member exceeding max. length of 30\n");
                *uni_load_fail = true;
            }
            strncat(buffer, &c, 1);
        }

        if (c == ' ' || c == '\0') {    //if char is SPACE, loading into buffer ends and buffer is loaded into the universe structure
            uni_array->member_count++;
            uni_array->uni_member = realloc(uni_array->uni_member, uni_array->member_count * sizeof(char));            
            uni_array->uni_member[uni_array->member_count - 1] = malloc(strlen(buffer) * sizeof(char));   
                if (uni_array->uni_member == NULL) {
                    fprintf(stderr, "Error occured during universe array memory allocation\n");
                    *uni_load_fail = true;
                }
                
                if ((uni_array->uni_member[uni_array->member_count - 1]) == NULL) {
                    fprintf(stderr, "Error occured during universe member memory allocation\n");
                    *uni_load_fail = true;    
                }

            strcpy(uni_array->uni_member[uni_array->member_count - 1], buffer);//Copy buffer into the structure array 

            

            for (int i = 0; i < uni_array->member_count - 1; i++) {   //Comparing strings with previous strings saved into the array
                if (strcmp(uni_array->uni_member[uni_array->member_count - 1], uni_array->uni_member[i]) == 0) {
                    fprintf(stderr, "Error: Multiple equal universe members\n");
                    *uni_load_fail = true;
                    break;
                }        
            }
            
            for (int i = 0; i < illegal_str_count; i++) {        //Parsing through illegal strings
                if (strcmp(buffer, illegal_strings[i]) == 0) {
            
                    fprintf(stderr, "Error: Illegal strings used\n");
                    *uni_load_fail = true;
                    break;
                }
            }
            buffer = realloc(buffer, sizeof(char));
            buffer[0] = '\0';    
        }
    }     
    free(buffer);   
}


void print_universe (Universe_t *uni_array) {
    printf("U ");
    for (int i = 0; i < uni_array->member_count; i++) {
        printf("%s ", uni_array->uni_member[i]);
    }
    printf("\n");
}


void load_set (char *str_line, bool *set_load_fail, Set_t *set_array, Universe_t *uni_array) {
    char c;
    bool uni_cmp_success;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    set_array->set_size = 0;
    set_array->member = malloc(sizeof(Set_member_t));
    buffer_alloc_check(&set_load_fail, &buffer);

    if (set_array->member == NULL) {
        fprintf(stderr, "Error occured during set array memory allocation\n");
        *set_load_fail = true;
    }

    for (unsigned int i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];

        if (c != ' ') {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            buffer_alloc_check(&set_load_fail, &buffer);
            strncat(buffer, &c, 1);
        }

        if (c == ' ' || c == '\0') {
            set_array->set_size++;
            set_array->member = realloc(set_array->member, set_array->set_size * sizeof(Set_member_t));
            set_array->member[set_array->set_size - 1].set_mem = malloc(strlen(buffer) * sizeof(char));

            if (set_array->member == NULL) {
                fprintf(stderr, "Error occured during set array memory allocation\n");
                *set_load_fail = true;
            }
            if (set_array->member[set_array->set_size - 1].set_mem == NULL) {
                fprintf(stderr, "Error occured during set member memory allocation\n");
                *set_load_fail = true;
            }


            strcpy(set_array->member[set_array->set_size - 1].set_mem, buffer);     

            
            for (int i = 0; i < set_array->set_size - 1; i++) {  //Comparing strings with previous strings saved into the array
                if (strcmp(set_array->member[set_array->set_size - 1].set_mem, set_array->member[i].set_mem) == 0) {
                    fprintf(stderr, "Error: Multiple equal set members\n");
                    *set_load_fail = true;
                    break;
                }
            }
            
            for (int i = 0; i < uni_array->member_count; i++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[i]) == 0) {
                    set_array->member[set_array->set_size - 1].set_mem_num = i;
                    uni_cmp_success = true;
                    break;
                }            
            }
            if (uni_cmp_success == false) {
                fprintf(stderr, "Error: Set member not declared in universe\n");
                *set_load_fail = true;
                break;
            }
            buffer = realloc(buffer, sizeof(char));
            buffer[0] = '\0';
        }
    }
    free(buffer);
}


void print_set(Set_t *set_array) {
    printf("S ");
    for (int i = 0; i < set_array->set_size; i++) {
        printf("%s ", set_array->member[i].set_mem);
    }
    printf("\n");
}


void load_relation(char *str_line, bool *rel_load_fail, Rel_t *rel_array, Universe_t *uni_array) {
    char c;
    bool bracket = false;       //Strings can only be loaded if they are inside of brackets in input
    char *buffer = malloc(sizeof(char));    
    buffer[0] = '\0';
    rel_array->rel_size = 0;
    rel_array->member = malloc(sizeof(Rel_member_t));
    buffer_alloc_check(&rel_load_fail, &buffer);

    if (rel_array->member == NULL) {
        fprintf(stderr, "Error occured during relation array memory allocation\n");
        *rel_load_fail = true;
    }

    for (unsigned int i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];

        if (c == '(') 
            bracket = true;

        if (c != ' ' && bracket == true) {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(int)*2);
            buffer_alloc_check(&rel_load_fail, &buffer);
            strncat(buffer, &c, 1);
        }

        if (c == ' ' || bracket == true) {
            rel_array->rel_size++;
            rel_array->member = realloc(rel_array->member, rel_array->rel_size * sizeof(Rel_member_t));
            rel_array->member[rel_array->rel_size - 1].rel_x = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL) {
                fprintf(stderr, "Error occured during relation array memory allocation\n");
                *rel_load_fail;
                break;
            }    
            if (rel_array->member[rel_array->rel_size - 1].rel_x == NULL) {
                fprintf(stderr, "Error occured during relation member memory allocation\n");
                *rel_load_fail = true;
                break;
            }

            strcpy(rel_array->member[rel_array->rel_size - 1].rel_x, buffer);
        }

        if (c == ')') {
            rel_array->rel_size++;
            //rel_array->member = realloc(rel_array->member, rel_array->rel_size * sizeof(Rel_member_t));
            rel_array->member[rel_array->rel_size - 1].rel_y = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL) {
                fprintf(stderr, "Error occured during relation array memory allocation\n");
                *rel_load_fail;
                break;
            }    
            if (rel_array->member[rel_array->rel_size - 1].rel_y == NULL) {
                fprintf(stderr, "Error occured during relation member memory allocation\n");
                *rel_load_fail = true;
                break;
            }
            strcpy(rel_array->member[rel_array->rel_size - 1].rel_y, buffer);
            bracket = false;
        }

        if (c != ' ' && bracket == false) {
            fprintf(stderr, "Error: incorrect relation input syntax\n");
            *rel_load_fail = true;
            break;
        }

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

    int line_count = 0;  //Number of all lines
    int set_count = 0;   //Number of set lines
    int rel_count = 0;   //Number of relation lines

    bool uni_load_fail = false;
    bool set_load_fail = false;
    bool rel_load_fail = false;
    
    Universe_t uni_array;
    Set_t *sets_array;
    Rel_t *rels_array;

    while (! (feof(fp))) {
        char *str_line = load_line(&fp);
        //printf("%s\n", str_line);
        line_count++;

        if (line_count > max_line_count) {      //Checking the number of lines in file
            fprintf(stderr, "Error: Max number of lines surpassed\n");
            return EXIT_FAILURE;
        }

        if (! (second_char_check(str_line))) 
            return EXIT_FAILURE;

        
        switch(str_line[0]) {
            case 'U':
                if (line_count == 1) {
                    load_universe(str_line, &uni_load_fail, &uni_array); //Loading line into Universe arrays

                    if (uni_load_fail == true)                         
                        return EXIT_FAILURE; 

                    else 
                        print_universe(&uni_array); 
                }

                else {
                    fprintf(stderr,"Error: Universe not declared at line 1\n");
                    return EXIT_FAILURE;
                }
                break;

            case 'S':               //Set Function
                if (line_count != 1) {
                    set_count++;
                    sets_array = realloc(sets_array, set_count * sizeof(Set_t));
                    sets_array[set_count - 1].set_index = line_count;  //Sets the current line index as the set index
                    load_set(str_line, &set_load_fail, &sets_array[set_count-1], &uni_array);   //Loading set into set structures

                    if (set_load_fail == true) {
                        printf("pica\n"); 
                        return EXIT_FAILURE;
                    }
                    else 
                        print_set(&sets_array[set_count-1]);
                }

                else {
                    fprintf(stderr, "Error: Set at line 1\n");
                    return EXIT_FAILURE;
                }
                break;

            case 'R':               //Relation Function
                if (line_count != 1) {
                    rel_count++;
                    rels_array = realloc(rels_array, rel_count * sizeof(Rel_t));
                    rels_array[rel_count - 1].rel_index = line_count;
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