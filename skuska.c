#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define argument_count 2
#define max_member_len 30
#define illegal_str_count 6
#define max_line_count 1000

char illegal_strings[21][13] = {"true", "false", "empty", "card", "complement", "union", //Strings illegal to be used as universe members
                                "intersect", "minus", "subseteq", "subset", "equals",
                                "reflexive", "symmetric", "antisymmetric", "transitive", 
                                "domain", "codomain", "injective", "surjective", "bijective"};  


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
    long set_index;
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


////COMMAND STRUCTURE/////
typedef struct {        //Structure for command loading
    char *command_string;
    long  command_arg[3];
    int size;
 } Command_t;


    //////SET FUNCTIONS//////
//print true if set is empty
void set_empty(Set_t * set){
    if(!set->set_size){
        printf("true\n");
    }
    else{
        printf("false\n");
    }
}

//print set cardinality
void set_card(Set_t * set){
    printf("%d\n", set->set_size);
}

//print complement of set to the universe
void set_complement(Set_t * setA, Universe_t * uni){
    printf("S");
    for(int i = 0; i < uni->member_count; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            if(strcmp(uni->uni_member[i], setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            if(cmp != 1 && j == (setA->set_size - 1)) {
                printf(" %s", uni->uni_member[i]);
                break;
            }
        }
    }
    printf("\n");
}


void set_union(Set_t * setA, Set_t * setB){
    printf("S");
    for(int i = 0; i < setA->set_size; i++){
        printf(" %s ", setA->member[i].set_mem);
    }
    for(int i = 0; i < setB->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            if(strcmp(setB->member[i].set_mem, setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            if(cmp != 1 && j == (setA->set_size - 1)) {
                printf(" %s", setB->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

void set_intersect(Set_t * setA, Set_t * setB){
    printf("S");
    for(int i = 0; i < setB->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            if(strcmp(setB->member[i].set_mem, setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            if(cmp == 1 && j == (setA->set_size - 1)) {
                printf(" %s ", setB->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

void set_minus(Set_t * setA, Set_t * setB){
    printf("S");
    for(int i = 0; i < setA->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setB->set_size; j++) {
            if(strcmp(setA->member[i].set_mem, setB->member[j].set_mem) == 0){
                cmp = 1;
            }
            if(cmp != 1 && j == (setB->set_size - 1)) {
                printf(" %s", setA->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

void set_subseteq(Set_t * setA, Set_t * setB){
    if(setA->set_size > setB->set_size) {
        printf("false\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            if(strcmp(setA->member[i].set_mem, setB->member[j].set_mem) == 0){
                cmp++;
            }
            if(cmp == setA->set_size && j == (setB->set_size - 1)) {
                printf("true\n");
                return;
            }
        }
    }
    printf("false\n");
}

void set_subset(Set_t * setA, Set_t * setB){
    if(setA->set_size >= setB->set_size) {
        printf("false\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            if(strcmp(setA->member[i].set_mem, setB->member[j].set_mem) == 0){
                cmp++;
            }
            if(cmp == setA->set_size && j == (setB->set_size - 1)) {
                printf("true\n");
                return;
            }
        }
    }
    printf("false\n");
}

void set_equals(Set_t * setA, Set_t * setB){
    if(setA->set_size != setB->set_size) {
        printf("false\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            if(strcmp(setA->member[i].set_mem, setB->member[j].set_mem) == 0){
                cmp++;
            }
            if(cmp == setA->set_size && j == (setB->set_size - 1)) {
                printf("true\n");
                return;
            }
        }
    }
    printf("false\n");
}


//////RELATION FUNCTIONS//////

//RELATION FUNCTION DOMAIN
void rel_domain(Rel_t* relA)
{
    for (int n= 0; n < relA->rel_size; n++)
    {
        printf("%s",(relA->member + n)->rel_x);
    }
    printf("\n");
}

//RELATION FUNCTION CODOMAIN
void rel_codomain(Rel_t* relA)
{
    for (int n = 0; n < relA->rel_size; n++)
    {
        printf("%s",(relA->member+ n)->rel_y);
    }
    printf("\n");
}

//RELATION FUNCTION INJECTIVE
int rel_inject(Rel_t *r, Universe_t uni_array)
{
    int *pv;
    int b = 1;
    int items = uni_array.member_count;

    pv = (int*)malloc(items * sizeof(int));
    for (int n = 0; n < items; n++)
    {
        pv[n] = 0;
    }

    for (int n = 0; n < r->rel_size; n++)
    {
        ++pv[(r->member+n)->rel_y_index];
        if (pv[(r->member+n)->rel_y_index] > 1)
        {
            b = 0;
            printf("false\n");
            break;
        }
    }

    if(b != 0) printf("true\n");
    free(pv);

    return b;
}

//RELATION FUNCTION SURJECTIVE

int rel_surject(Rel_t *r, Universe_t uni_array)
{
    int *pv;
    int b = 1;
    int items = uni_array.member_count;

    pv = (int*)malloc(items * sizeof(int));
    for (int n = 0; n < items; n++)
    {
        pv[n] = 0;
    }

    for (int n = 0; n < r->rel_size; n++)
    {
        ++pv[(r->member+n)->rel_y_index];

    }
    for (int n = 0; n < r->rel_size; n++)
    {
        if (pv[(r->member + n)->rel_y_index] == 0)
        {
            b = 0;
            break;
        }
    }

    if(b != 0) printf("true\n");
    else printf("false\n");
    free(pv);

    return b;

}

//RELATION FUNCTION BIJECTIVE
void rel_biject(Rel_t *r, Universe_t uni_array)
{
    if(rel_inject(r, uni_array) && rel_surject(r, uni_array))
    {
        printf("true\n");
    }
    else
    {
        printf("false\n");
    }
}





//LOADING LINE FROM FILE//
char *load_line(FILE **fp) {
    char *line_str = malloc(sizeof(char));
    if (line_str == NULL) 
       return NULL;
    line_str[0] = '\0';
    char c;

    while (1) {
        c = fgetc(*fp);
        if (c == '\n' || c == EOF) 
            break;

        line_str = (char*) realloc(line_str, strlen(line_str) + sizeof(char)*2);  //2 --> One for new character, one for trailing zero 
        if (line_str == NULL) 
            return NULL;
        strncat(line_str, &c, 1);
    }
    if (line_str == NULL) 
        return NULL;
    return line_str;

}




int second_char_check(char *str_line) {        //Checking if the second char in line is SPACE                    
    if ((str_line[1] != ' ' && str_line[1] != '\0')) {
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

int command_arg_check (Command_t * command, int count) {    //Checking the correct number of arguments in command call
    if (command->size > count) {
        fprintf(stderr, "Error: incorrect number of arguments in command call\n");
        return 0;
    }
    return 1;
}


 
//UNIVERSE LOAD//
void load_universe(char *str_line, bool *uni_load_fail, Universe_t *uni_array) {
    char c;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    uni_array->member_count  = 0;
    uni_array->uni_member = malloc(sizeof(char));  //1 row * 1 column = 1 char
    buffer_alloc_check(uni_load_fail, buffer);


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
            buffer_alloc_check(uni_load_fail, buffer);
          
            if (strlen(buffer) > max_member_len) {
                fprintf(stderr, "Error: Universe member exceeding max. length of 30\n");
                *uni_load_fail = true;
            }
            strncat(buffer, &c, 1);
        }

        if (c == ' ' || c == '\0') {    //if char is SPACE, loading into buffer ends and buffer is loaded into the universe structure
            uni_array->member_count++;
            uni_array->uni_member = realloc(uni_array->uni_member, uni_array->member_count * sizeof(char*));
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

            

            for (int o = 0; o < uni_array->member_count - 1; o++) {   //Comparing strings with previous strings saved into the array
                if (strcmp(uni_array->uni_member[uni_array->member_count - 1], uni_array->uni_member[o]) == 0) {
                    fprintf(stderr, "Error: Multiple equal universe members\n");
                    *uni_load_fail = true;
                    break;
                }        
            }
            
            for (int o = 0; o < illegal_str_count; o++) {        //Parsing through illegal strings
                if (strcmp(buffer, illegal_strings[o]) == 0) {
            
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

//UNIVERSE PRINT//
void print_universe (Universe_t *uni_array) {
    printf("U");
    for (int i = 0; i < uni_array->member_count; i++) {
        printf(" %s", uni_array->uni_member[i]);
    }
    printf("\n");
}


//SET LOAD//
void load_set (char *str_line, bool *set_load_fail, Set_t *set_array, Universe_t *uni_array) {
    char c;
    bool uni_cmp_success;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    set_array->set_size = 0;
    set_array->member = malloc(sizeof(Set_member_t));
    buffer_alloc_check(set_load_fail, buffer);

    if (set_array->member == NULL) {
        fprintf(stderr, "Error occured during set array memory allocation\n");
        *set_load_fail = true;
    }

    for (unsigned int i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];

        if (c != ' ') {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            buffer_alloc_check(set_load_fail, buffer);
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

            
            for (int o = 0; o < set_array->set_size - 1; o++) {  //Comparing strings with previous strings saved into the array
                if (strcmp(set_array->member[set_array->set_size - 1].set_mem, set_array->member[o].set_mem) == 0) {
                    fprintf(stderr, "Error: Multiple equal set members\n");
                    *set_load_fail = true;
                    break;
                }
            }
            
            for (int o = 0; o < uni_array->member_count; o++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[o]) == 0) {
                    set_array->member[set_array->set_size - 1].set_mem_num = o;
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

//SET PRINT//
void print_set(Set_t *set_array) {
    printf("S");
    for (int i = 0; i < set_array->set_size; i++) {
        printf(" %s", set_array->member[i].set_mem);
    }
    printf("\n");
}


//RELATION LOADING//
void load_relation(char *str_line, bool *rel_load_fail, Rel_t *rel_array, Universe_t *uni_array) {
    char c;
    bool bracket = false;       //Strings can only be loaded if they are inside of brackets in input
    bool uni_cmp_success = false;
    char *buffer = malloc(sizeof(char));    
    buffer[0] = '\0';
    rel_array->rel_size = 0;
    rel_array->member = malloc(sizeof(Rel_member_t));
    buffer_alloc_check(rel_load_fail, buffer);

    if (rel_array->member == NULL) {
        fprintf(stderr, "Error occured during relation array memory allocation\n");
        *rel_load_fail = true;
    }

    //loading and parsing relations from line 
    for (unsigned int i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];
        if (c == '(') 
            bracket = true;

        if (c != ' ' && c != '(' && c != ')' && bracket == true) {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            buffer_alloc_check(rel_load_fail, buffer);
            strncat(buffer, &c, 1);
        }

        if (c == ' ' && bracket == true) {
            rel_array->rel_size++;
            rel_array->member = realloc(rel_array->member, rel_array->rel_size * sizeof(Rel_member_t));
            rel_array->member[rel_array->rel_size - 1].rel_x = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL) {
                fprintf(stderr, "Error occured during relation array memory allocation\n");
                *rel_load_fail = true;
                break;
            }    
            if (rel_array->member[rel_array->rel_size - 1].rel_x == NULL) {
                fprintf(stderr, "Error occured during relation member memory allocation\n");
                *rel_load_fail = true;
                break;
            }
            for (int o = 0; o < uni_array->member_count; o++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[o]) == 0) {
                    rel_array->member[rel_array->rel_size - 1].rel_x_index = o;
                    uni_cmp_success = true;
                    break;
                }            
            }
            if (uni_cmp_success == false) {
                fprintf(stderr, "Error: Relation member x not declared in universe\n");
                *rel_load_fail = true;
                break;
            }

            strcpy(rel_array->member[rel_array->rel_size - 1].rel_x, buffer);
            //uni_cmp_success = false;
            buffer = realloc(buffer, sizeof(char));
            buffer_alloc_check(rel_load_fail, buffer);
            buffer[0] = '\0';            
        }

        if (c == ')' && bracket == true) {
            rel_array->member[rel_array->rel_size - 1].rel_y = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL) {
                fprintf(stderr, "Error occured during relation array memory allocation\n");
                *rel_load_fail = true;
                break;
            }    
            if (rel_array->member[rel_array->rel_size - 1].rel_y == NULL) {
                fprintf(stderr, "Error occured during relation member memory allocation\n");
                *rel_load_fail = true;
                break;
            }
            for (int o = 0; o < uni_array->member_count; o++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[o]) == 0) {
                    rel_array->member[rel_array->rel_size - 1].rel_y_index = o;
                    uni_cmp_success = true;
                    break;
                }            
            }
            if (uni_cmp_success == false) {
                fprintf(stderr, "Error: Relation member y not declared in universe\n");
                *rel_load_fail = true;
                break;
            }  
            strcpy(rel_array->member[rel_array->rel_size - 1].rel_y, buffer);
            bracket = false;
            buffer = realloc(buffer, sizeof(char));
            buffer_alloc_check(rel_load_fail, buffer);
            buffer[0] = '\0';
        }

        if (c != ' ' && c != ')' && c != '\0' && bracket == false) {
            fprintf(stderr, "Error: incorrect relation input syntax\n");
            *rel_load_fail = true;
            break;
        }

    }


    for (int i = 0; i < rel_array->rel_size - 1; i++) {
        if (strcmp(rel_array->member[rel_array->rel_size - 1].rel_x, rel_array->member[i].rel_x) == 0 
        &&  strcmp(rel_array->member[rel_array->rel_size - 1].rel_y, rel_array->member[i].rel_y) == 0) {
            fprintf(stderr, "Error: multiple equal relations\n");
            *rel_load_fail = true;
        }
    }
    free(buffer);
}

//RELATION PRINT//
void print_relation (Rel_t *rel_array) {
    printf("R");
    for (int i = 0; i < rel_array->rel_size; i++) {
        printf(" (%s %s)",rel_array->member[i].rel_x, rel_array->member[i].rel_y);
    }
    printf("\n");
}


////LOADING COMMAND LINE/////
void load_command(char *str_line, bool *command_load_fail, Command_t *command) {
    char  c;
    bool command_loaded = false;
    char *ptr;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    buffer_alloc_check(command_load_fail, buffer); 
    command->size = 0;   

    for (unsigned i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];
        
        if (c != ' ' && c != '\0') {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            buffer_alloc_check(command_load_fail, buffer);
            strncat(buffer, &c, 1);
        }

        if (c == ' ' || c == '\0') {
            if (command_loaded == true) {
                command->size++;
                command->command_arg[command->size - 1] = strtol(buffer, &ptr, 10);
                if(command->command_arg[command->size - 1] == 0) {
                    fprintf(stderr, "Error: wrong syntax in command line\n");
                    *command_load_fail = true;
                }
            }

            if (command_loaded == false) {
                command->command_string = malloc(strlen(buffer) * sizeof(char));
                strcpy(command->command_string, buffer);
                command_loaded = true;
            }

            buffer = realloc(buffer, sizeof(char));
            buffer[0] = '\0';    
        }
    }
    free(buffer);
}

    
//SET AND RELATION INDEX CHECKING//
long set_index_check(Command_t command, Set_t * sets_array, long set_count, int arg_num) {
    bool success = false;
    for (long i = 0; i < set_count; i++) {
        if (command.command_arg[arg_num] == sets_array[i].set_index) {
            success = true;
            return i;
        }
    }
    if (success == false) 
        fprintf(stderr, "Error: wrong command call argument\n");
    return -1;
}


long rel_index_check(Command_t command, Rel_t * rels_array, long rel_count, int arg_num) {
    bool success = false;
    for (long i = 0; i < rel_count; i++) {
        if (command.command_arg[arg_num] == rels_array[i].rel_index) {
            success = true;
            return i;
        }
    }
    if (success == false) 
        fprintf(stderr, "Error: wrong command call argument\n");
    return -1;
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
        fprintf(stderr,"Error: Opening file not successful\n");
        return EXIT_FAILURE;
    }

    (void) argc;
    (void) argv;

    long line_count = 0;  //Number of all lines
    long set_count = 0;   //Number of set lines
    long rel_count = 0;   //Number of relation lines
    long command_count = 0;

    bool uni_load_fail = false;
    bool set_load_fail = false;
    bool rel_load_fail = false;
    bool command_load_fail = false;
    bool was_command = false;

    Universe_t uni_array;
    Set_t *sets_array = malloc(sizeof(Set_t));
    Rel_t *rels_array = malloc(sizeof(Rel_t));
    Command_t *commands = malloc(sizeof(Command_t));



    while (! (feof(fp))) {
        char *str_line = load_line(&fp);
        line_count++;

        if (line_count > max_line_count) {      //Checking the number of lines in file
            fprintf(stderr, "Error: Max number of lines surpassed\n");
            return EXIT_FAILURE;
        }
        //printf("%s h\n", str_line);

        switch(str_line[0]) {
            case 'U':
                if (line_count == 1) {
                    if (! (second_char_check(str_line))) 
                        return EXIT_FAILURE;

                    load_universe(str_line, &uni_load_fail, &uni_array); //Loading line into Universe arrays
                    set_count++;
                    sets_array = realloc(sets_array, set_count * sizeof(Set_t));
                    sets_array[set_count - 1].set_index = line_count;
                    load_set(str_line, &set_load_fail, &sets_array[set_count - 1], &uni_array);

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
                    if (was_command == true) {
                        fprintf(stderr, "Error: Set line after command line\n");
                        return EXIT_FAILURE;
                    }
                    if (! (second_char_check(str_line))) 
                        return EXIT_FAILURE;
                    set_count++;
                    sets_array = realloc(sets_array, set_count * sizeof(Set_t));
                    if (sets_array == NULL) {
                        fprintf(stderr, "Error occured during sets_array allocation\n");
                        return EXIT_FAILURE;
                    }
                    
                    sets_array[set_count - 1].set_index = line_count;  //Sets the current line index as the set index
                    load_set(str_line, &set_load_fail, &sets_array[set_count - 1], &uni_array);   //Loading set into set structures

                    if (set_load_fail == true)
                        return EXIT_FAILURE;
                    else 
                        print_set(&sets_array[set_count - 1]);
                }

                else {
                    fprintf(stderr, "Error: Set at line 1\n");
                    return EXIT_FAILURE;
                }
                break;

            case 'R':               //Relation Function
                if (line_count != 1) {
                    if (was_command == true) {
                        fprintf(stderr, "Error: Relation line after command line\n");
                        return EXIT_FAILURE;
                    }
                    if (! (second_char_check(str_line))) 
                        return EXIT_FAILURE;
                    rel_count++;
                    rels_array = realloc(rels_array, rel_count * sizeof(Rel_t));
                    rels_array[rel_count - 1].rel_index = line_count;
                    load_relation(str_line, &rel_load_fail, &rels_array[rel_count - 1], &uni_array);

                    if (rel_load_fail == true) { 
                        return EXIT_FAILURE;
                    }
                    else 
                        print_relation(&rels_array[rel_count - 1]);
                }

                else {
                    fprintf(stderr, "Error: Relation at line 1\n");
                    return EXIT_FAILURE;
                }
                break;

            case 'C':               //Command Function
                if (line_count !=1) {
                    was_command = true;
                    if (! (second_char_check(str_line))) 
                        return EXIT_FAILURE;
                    command_count++;
                    commands = realloc(commands, command_count * sizeof(Command_t));
                    load_command(str_line, &command_load_fail, &commands[command_count - 1]);

                    
                    //SET FUNCTIONS WITH 1 ARGUMENT//
                    if (strcmp("empty", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                                set_empty(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)]);
                            else return EXIT_FAILURE;                            
                        }                    
                    }

                    if (strcmp("card", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0)
                            return EXIT_FAILURE;  
                        else {
                            if (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                                set_card(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)]);
                            else return EXIT_FAILURE;
                        }  
                    }

                    if (strcmp("complement", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                                set_complement(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)], &uni_array);
                            else return EXIT_FAILURE;
                        } 
                    }

                    //SET FUNCTIONS WITH 2 ARGUMENTS//
                    if (strcmp("union", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_union(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }

                    if (strcmp("intersect", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_intersect(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }

                    if (strcmp("minus", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_minus(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }                

                    if (strcmp("subseteq", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_subseteq(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }     

                    if (strcmp("subset", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_subset(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }       

                    if (strcmp("equals", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 2) == 0)
                            return EXIT_FAILURE;
                        else {
                            if ( (set_index_check(commands[command_count - 1], sets_array, set_count, 0) != -1) 
                              && (set_index_check(commands[command_count - 1], sets_array, set_count, 1) != -1) )
                                set_equals(&sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 0)],
                                          &sets_array[set_index_check(commands[command_count - 1], sets_array, set_count, 1)]);
                            else return EXIT_FAILURE;
                        } 
                    }    

                    //////RELATIONS FUNCTIONS WITH 1 ARGUMENT////

                    if (strcmp("domain", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1] ,1) == 0)
                            return EXIT_FAILURE; 
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                rel_domain(&rels_array[commands[command_count - 1].command_arg[0]]);
                            else return EXIT_FAILURE;
                        }
                    }

                    if (strcmp("codomain", commands[command_count -1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0)
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                rel_codomain(&rels_array[commands[command_count - 1].command_arg[0]]);
                            else return EXIT_FAILURE;
                        }
                    }

                    if (strcmp("injective", commands[command_count -1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count -1], 1) == 0)
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) {
                                if (rel_inject(&rels_array[commands[command_count - 1].command_arg[0]], uni_array) != 0) 
                                    printf("true\n");
                                else printf("false\n");
                            }    
                            else return EXIT_FAILURE;
                        }
                    }

                    if (strcmp("surjective", commands[command_count -1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count -1], 1) == 0)
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) {
                                if (rel_surject(&rels_array[commands[command_count - 1].command_arg[0]], uni_array) != 0) 
                                    printf("true\n");
                                else printf("false\n");
                            }    
                            else return EXIT_FAILURE;  
                        }
                    }

                    if (strcmp("bijective", commands[command_count -1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count -1], 1) == 0)
                            return EXIT_FAILURE;
                        else rel_biject(&rels_array[commands[command_count -1].command_arg[0]], uni_array);
                    }          

                    //RELATION FUNCTIONS WITH 2 ARGUMENTS//




                    //COMBINED FUNCTIONS//
                }

                else {
                    fprintf(stderr, "Error: Command at line 1\n");
                    return EXIT_FAILURE;
                }
                break;
            
            case '\0': return 0;

            default:                //Invalid function
                fprintf(stderr, "Error: Invalid Function at line %ld\n", line_count);
                return EXIT_FAILURE;
        }
        free(str_line);
    }
    for(int i = 0; i < command_count; i++){
        free(commands[i].command_string);
    }
    for(int i = 0; i < uni_array.member_count; i++){
        free(uni_array.uni_member[i]);
    }
    for(int i = 0; i < sets_array->set_size; i++){
        free(sets_array->member[i].set_mem);
    }
    for(int i = 0; i < set_count; i++){
        free(sets_array->member);
    }
    for(int i = 0; i < rels_array->rel_size; i++){
        free(rels_array->member[i].rel_x);
        free(rels_array->member[i].rel_y);
    }
    for(int i = 0; i < rel_count; i++){
        free(rels_array[i].member);
    }
    free(rels_array);
    free(sets_array);
    free(uni_array.uni_member);
    free(commands);
    fclose(fp);
    return 0;
}