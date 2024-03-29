#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

#define argument_count 2
#define max_member_len 30
#define illegal_str_count 6
#define max_line_count 1001

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


 // Represents an array of bytes where each bit is supposed to be addressable individually
typedef struct {
    uint8_t* bytes;
    int bit_len;
    int byte_len;
} Bitfield_t; 


    //////SET FUNCTIONS//////
//function prints true if set is empty
void set_empty(Set_t * set){
    if(!set->set_size){
        printf("true\n");
    }
    else{
        printf("false\n");
    }
}

//function prints set cardinality
void set_card(Set_t * set){
    printf("%d\n", set->set_size);
}

//function prints complement of setA to the universe
void set_complement(Set_t * setA, Universe_t * uni){
    printf("S");
    //if setA is empty, prints all members of universe
    if(setA->set_size == 0){
        for(int i = 0; i < uni->member_count; i++) {
            printf(" %s", uni->uni_member[i]);
        }
    }
    for(int i = 0; i < uni->member_count; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            //compare all members of setA with all members of universe
            if(strcmp(uni->uni_member[i], setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            //print all members of universe missing from setA
            if(cmp != 1 && j == (setA->set_size - 1)) {
                printf(" %s", uni->uni_member[i]);
                break;
            }
        }
    }
    printf("\n");
}

//function prints union of 2 sets
void set_union(Set_t * setA, Set_t * setB){
    printf("S");
    //if first set is empty, prints all members of second set
    if(setA->set_size == 0){
        for(int i = 0; i < setB->set_size; i++) {
            printf(" %s", setB->member[i].set_mem);
        }
        return;
    }
    //prints all members of first set
    for(int i = 0; i < setA->set_size; i++){
        printf(" %s", setA->member[i].set_mem);
    }
    for(int i = 0; i < setB->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            //checks for unique members of setB
            if(strcmp(setB->member[i].set_mem, setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            //prints unique members of setB
            if(cmp != 1 && j == (setA->set_size - 1)) {
                printf(" %s", setB->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

//function prints intersect of 2 sets
void set_intersect(Set_t * setA, Set_t * setB){
    printf("S");
    for(int i = 0; i < setB->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setA->set_size; j++) {
            //checks for common members
            if(strcmp(setB->member[i].set_mem, setA->member[j].set_mem) == 0){
                cmp = 1;
            }
            //prints all common members of both sets
            if(cmp == 1 && j == (setA->set_size - 1)) {
                printf(" %s", setB->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

//function substracts setB from setA and prints result
void set_minus(Set_t * setA, Set_t * setB){
    printf("S");
    for(int i = 0; i < setA->set_size; i++) {
        int cmp = 0;
        for (int j = 0; j < setB->set_size; j++) {
            if(strcmp(setA->member[i].set_mem, setB->member[j].set_mem) == 0){
                cmp = 1;
            }
            //prints all unique members of setA
            if(cmp != 1 && j == (setB->set_size - 1)) {
                printf(" %s", setA->member[i].set_mem);
                break;
            }
        }
    }
    printf("\n");
}

//function prints true or false, whether setA is subset or equal to setB
void set_subseteq(Set_t * setA, Set_t * setB){
    //if setA is bigger than setB, it can't be a subset of setB
    if(setA->set_size > setB->set_size) {
        printf("false\n");
        return;
    }
    if(setA->set_size == 0){
        printf("true\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            //checks whether all members of setA are also members of setB
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

//function prints true or false, whether setA is proper subset of setB
void set_subset(Set_t * setA, Set_t * setB){
    //if setA is bigger or as big as setB, it can't be proper subset of setB
    if(setA->set_size >= setB->set_size) {
        printf("false\n");
        return;
    }
    if(setA->set_size == 0){
        printf("true\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            //checks whether all members of setA are also members of setB
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

//function compares 2 sets and prints true or false, whether they are equal or not
void set_equals(Set_t * setA, Set_t * setB){
    //if size of sets differs, they can't be equal
    if(setA->set_size != setB->set_size) {
        printf("false\n");
        return;
    }
    //if both sets are empty, they are equal
    if(setB->set_size == 0 && setA->set_size == 0){
        printf("true\n");
        return;
    }
    int cmp = 0;
    for(int i = 0; i < setA->set_size; i++) {
        for (int j = 0; j < setB->set_size; j++) {
            //compares all members of both sets
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

void is_reflexive(Rel_t* rel_p, Universe_t* uni_p);
void is_symmetric(Rel_t* rel_p, Universe_t* uni_p);
void is_antisymmetric(Rel_t* rel_p, Universe_t* uni_p);
void is_transitive(Rel_t* rel_p, Universe_t* uni_p);

void relation_ctor(Rel_t* relation);
void rel_to_bitfield(Rel_t* rel_p, Universe_t* uni_p, Bitfield_t* field_p);
uint8_t getflag(int pos, uint8_t* flags);
void setflag(int pos, bool b, uint8_t* flags);
uint8_t getflag2d(int y, int x, uint8_t* field_p, int bit_width);
void setflag2d(bool b, int y, int x, uint8_t* field_p, int bit_width);


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
int load_set (char *str_line, bool *set_load_fail, Set_t *set_array, Universe_t *uni_array) {
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
        return 0;
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
                return 0;
            }
            if (set_array->member[set_array->set_size - 1].set_mem == NULL) {
                fprintf(stderr, "Error occured during set member memory allocation\n");
                *set_load_fail = true;
                return 0;
            }


            strcpy(set_array->member[set_array->set_size - 1].set_mem, buffer);     

            
            for (int o = 0; o < set_array->set_size - 1; o++) {  //Comparing strings with previous strings saved into the array
                if (strcmp(set_array->member[set_array->set_size - 1].set_mem, set_array->member[o].set_mem) == 0) {
                    fprintf(stderr, "Error: Multiple equal set members\n");
                    *set_load_fail = true;
                    return 0;
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
                return 0;
                break;
            }
            buffer = realloc(buffer, sizeof(char));
            buffer[0] = '\0';
        }
    }
    free(buffer);
    return 1;
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
int load_relation(char *str_line, Rel_t *rel_array, Universe_t *uni_array) {
    char c;
    bool bracket = false;       //Strings can only be loaded if they are inside of brackets in input
    bool uni_cmp_success = false;
    char *buffer = malloc(sizeof(char));    
    buffer[0] = '\0';
    rel_array->rel_size = 0;
    rel_array->member = malloc(sizeof(Rel_member_t));
    //buffer_alloc_check(rel_load_fail, buffer);

    if (rel_array->member == NULL)
        return 0;

    //loading and parsing relations from line 
    for (unsigned int i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];
        if (c == '(') 
            bracket = true;

        if (c != ' ' && c != '(' && c != ')' && bracket == true) {

            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            //buffer_alloc_check(rel_load_fail, buffer);
            strncat(buffer, &c, 1);
        }


        if (c == ' ' && bracket == true) {

            rel_array->rel_size++;
            rel_array->member = realloc(rel_array->member, rel_array->rel_size * sizeof(Rel_member_t));
            rel_array->member[rel_array->rel_size - 1].rel_x = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL)
                return 0;

            if (rel_array->member[rel_array->rel_size - 1].rel_x == NULL)
                return 0;

            for (int o = 0; o < uni_array->member_count; o++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[o]) == 0) {
                    rel_array->member[rel_array->rel_size - 1].rel_x_index = o;
                    uni_cmp_success = true;
                }            
            }

            if (uni_cmp_success == false)
                return 0;


            strcpy(rel_array->member[rel_array->rel_size - 1].rel_x, buffer);
            //uni_cmp_success = false;

            buffer = realloc(buffer, sizeof(char));
            //buffer_alloc_check(rel_load_fail, buffer);
            buffer[0] = '\0';            
        }

        if (c == ')' && bracket == true) {
            rel_array->member[rel_array->rel_size - 1].rel_y = malloc(strlen(buffer) * sizeof(char));

            if (rel_array->member == NULL)
                return 0;


            if (rel_array->member[rel_array->rel_size - 1].rel_y == NULL)
                return 0;

            for (int o = 0; o < uni_array->member_count; o++) {  //Checking if set member is declared in Universe
                if (strcmp(buffer, uni_array->uni_member[o]) == 0) {
                    rel_array->member[rel_array->rel_size - 1].rel_y_index = o;
                    uni_cmp_success = true;
                }            
            }

            if (uni_cmp_success == false)
                return 0;

            strcpy(rel_array->member[rel_array->rel_size - 1].rel_y, buffer);
            bracket = false;
            buffer = realloc(buffer, sizeof(char));
            //buffer_alloc_check(rel_load_fail, buffer);
            buffer[0] = '\0';
        }

        if (c != ' ' && c != ')' && c != '\0' && bracket == false)
            return 0;

    }


    for (int i = 0; i < rel_array->rel_size - 1; i++) {
        if (strcmp(rel_array->member[rel_array->rel_size - 1].rel_x, rel_array->member[i].rel_x) == 0 
        &&  strcmp(rel_array->member[rel_array->rel_size - 1].rel_y, rel_array->member[i].rel_y) == 0)
            return 0;

    }
    free(buffer);
    return 1;
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
int load_command(char *str_line, bool *command_load_fail, Command_t *command) {
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
                    return 0;
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
    return 1;
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

bool arg_count_check(Command_t command, int right_count) {
    if (command.size != right_count) {
        fprintf(stderr, "Error: Wrong command call argument count\n");
        return false;
    }
    return true;
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
                    if (load_set(str_line, &set_load_fail, &sets_array[set_count - 1], &uni_array) == 0) {   //Loading set into set structures
                        fprintf(stderr, "Error while loading set\n");
                        return EXIT_FAILURE;
                    }
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

                    if (load_relation(str_line, &rels_array[rel_count - 1], &uni_array) == 0) {
                        fprintf(stderr, "Error while loading relation\n");
                        return EXIT_FAILURE;
                    }

                    if (load_relation(str_line, &rels_array[rel_count - 1], &uni_array) == 1)
                        print_relation(&rels_array[rel_count - 1]);
                }

                else {
                    fprintf(stderr, "Error: Relation at line 1\n");
                    return EXIT_FAILURE;
                }
                break;

            case 'C':               //Command Function
                if (rel_count == 0 && set_count == 1){
                    fprintf(stderr, "Error: No sets or relations");
                    return EXIT_FAILURE;
                }
                if (line_count != 1) {
                    was_command = true;
                    if (! (second_char_check(str_line))) 
                        return EXIT_FAILURE;
                    command_count++;
                    commands = realloc(commands, command_count * sizeof(Command_t));
                    if (load_command(str_line, &command_load_fail, &commands[command_count - 1]) == 0) {
                        fprintf(stderr, "Error while loading command\n");
                        return EXIT_FAILURE;
                    }

                    
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

                    if (strcmp("reflexive", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                is_reflexive(&rels_array[commands[command_count - 1].command_arg[0]], &uni_array);
                            else return EXIT_FAILURE;
                        }
                    }

                    if (strcmp("symmetric", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                is_symmetric(&rels_array[commands[command_count - 1].command_arg[0]], &uni_array);
                            else return EXIT_FAILURE;
                        }
                    }  

                    if (strcmp("antisymmetric", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                is_antisymmetric(&rels_array[commands[command_count - 1].command_arg[0]], &uni_array);
                            else return EXIT_FAILURE;
                        }
                    }  

                    if (strcmp("transitive", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0) 
                            return EXIT_FAILURE;
                        else {
                            if (rel_index_check(commands[command_count - 1], rels_array, rel_count, 0) != -1) 
                                is_transitive(&rels_array[commands[command_count - 1].command_arg[0]], &uni_array);
                            else return EXIT_FAILURE;
                        }
                    }                    


                    if (strcmp("domain", commands[command_count - 1].command_string) == 0) {
                        if (command_arg_check(&commands[command_count - 1], 1) == 0)
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

                    //COMBINED FUNCTIONS//
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


    ///CLEARING MEMORY///
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
        free(sets_array[i].member);
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



void is_reflexive(Rel_t* rel_p, Universe_t* uni_p) {

	// Array of bools, where each element answers the question:
	// "Is the universe member with my index related to itself?"
	bool refl_arr[uni_p->member_count];
	for (int i = 0; i < uni_p->member_count; i++) {
		refl_arr[i] = false;
	}
	
	// Loop through each relation member
	for (int i = 0; i < rel_p->rel_size; i++) {
		
		Rel_member_t* member_p = &(rel_p->member[i]);

		// If this universe member already is related to itself
		if (refl_arr[member_p->rel_x_index] == true) {
			continue;
		}
		
		// If it isn't related to itself, maybe it will be related now
		if (member_p->rel_x_index == member_p->rel_y_index) {
			
			refl_arr[member_p->rel_x_index] = (member_p->rel_x_index == member_p->rel_y_index);
		}
	}
	
	// If refl_arr is filled with only trues, it means that every universe member 
	// is related to itself
	for (int i = 0; i < uni_p->member_count; i++) {
		if (refl_arr[i] == false) { 
		    fprintf(stdout, "false\n");
		    return;
		}
	}
	fprintf(stdout, "true\n");
}

void is_symmetric(Rel_t* rel_p, Universe_t* uni_p) {
    
    Bitfield_t rel2d;
    rel_to_bitfield(rel_p, uni_p, &rel2d);
    
    // Check only the diagonal
    for (int x = 0; x < uni_p->member_count; x++) {
        for (int y = 0; y < uni_p->member_count; y++) {
            
            bool a = getflag2d(y, x, rel2d.bytes, uni_p->member_count);
            bool b = getflag2d(x, y, rel2d.bytes, uni_p->member_count);
            
            // for every a: aRa 
            if (a != b) {
                    
                    fprintf(stdout, "false");
                    free(rel2d.bytes);
                    return;
                }
        }
    }
    fprintf(stdout, "true");
    free(rel2d.bytes);
}

void is_antisymmetric(Rel_t* rel_p, Universe_t* uni_p) {
    
    Bitfield_t rel2d;
    rel_to_bitfield(rel_p, uni_p, &rel2d);
    
    
    // Check for symmetries "along a triangle"
    for (int y = 0; y < uni_p->member_count; y++) {
        for (int x = 0; x < y; x++) {
            bool a = getflag2d(y, x, rel2d.bytes, uni_p->member_count);
            bool b = getflag2d(x, y, rel2d.bytes, uni_p->member_count);
            
            // for every a, b: if aRb and bRa then a must equal b
            if ((a == true) && (b == true)) {
                free(rel2d.bytes);
                printf("false");
                return;
            } 
        }
        
    }
    free(rel2d.bytes);
    printf("true");
}

void is_transitive(Rel_t* rel_p, Universe_t* uni_p) {
    
    Bitfield_t rel2d;
    rel_to_bitfield(rel_p, uni_p, &rel2d);
    
    // For each row in the relation table
    for (int y = 0; y < uni_p->member_count; y++) {
        
        // Look for a "1" in this row. If it's there, look at the row
        // representing the 2nd component of the relation 
        // represented by this "1".
        for (int x = 0; x < uni_p->member_count; x++) {
            
            if (getflag2d(y, x, rel2d.bytes, rel_p->rel_size) != 0) {
                
                printf("found relation at %d, %d:\n", y, x);
                int b_row_y = x;
                
                for (int b_x = 0; b_x < uni_p->member_count; b_x++) {
                    
                    bool is_related = getflag2d(b_row_y, b_x, rel2d.bytes, rel_p->rel_size);
                    printf("%d,%d: %d | ", b_row_y, b_x, is_related);
                }
                printf("\n\n");
            }
            
        }
        
    }
    
}


// BITFIELD STUFF--------------------------------------------------

// How many bytes do you need to store n bits?
int min_bytes(int n) {
    int extra = (n % 8 == 0 ? 0 : 1);
    return ((int)(n / 8.0)) + extra;
}

void rel_to_bitfield(Rel_t* rel_p, Universe_t* uni_p, Bitfield_t* field_p) {
    
    field_p->bit_len = uni_p->member_count * uni_p->member_count;
    field_p->byte_len = min_bytes(field_p->bit_len);
    field_p-> bytes = malloc(field_p->byte_len);
    
    for (int i = 0; i < field_p->byte_len; i++) { // Make every bit 0
        field_p->bytes[i] = 0;
    }
    
    // set the individual bits 
    for (int i = 0; i < rel_p->rel_size; i++) {
        int x = rel_p->member[i].rel_x_index;
        int y = rel_p->member[i].rel_y_index;
        setflag2d(true, y, x, field_p->bytes, uni_p->member_count);
    }
}

uint8_t getflag(int pos, uint8_t* flags) {
	 int bindex = (int)(pos / 8.0); // Which byte from the left?
	
	// In that byte, which bit from the left
	int inbindex = pos % 8; 
	
	uint8_t onel = 128; // 128 in binary is "10000000"
	
	// Pushes that single "1" left by 'inbindex' places
	int res = flags[bindex] & (onel >> inbindex);
	return res; 
}

void setflag(int pos, bool b, uint8_t* flags) {
	int bindex = (int)(pos / 8.0);
	
	int inbindex = pos % 8; 
	
	uint8_t onel = 128; // Binary: 10000000
	
	flags[bindex] &= ~(onel >> inbindex); // Reset that bit to zero
	if (b == true) {
		flags[bindex] |= (onel >> inbindex); // Turn that bit on
	}
}

uint8_t getflag2d(int y, int x, uint8_t* field_p, int bit_width) {
    int pos = y * bit_width + x;
    
    return getflag(pos, field_p);
}

void setflag2d(bool b, int y, int x, uint8_t* field_p, int bit_width) {
    int pos = y * bit_width + x;
    setflag(pos, b, field_p);
}


