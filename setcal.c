#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

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

//BITFIELD//

// Represents an array of bytes where each bit is supposed to be addressable individually
typedef struct {
    uint8_t* bytes;
    int bit_len;
    int byte_len;
} Bitfield_t;

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

 
        //LOADING UNIVERSE//
void load_universe(char *str_line, bool *uni_load_fail, Universe_t *uni_array) {
    char c;
    char *buffer = malloc(sizeof(char));
    buffer[0] = '\0';
    uni_array->member_count  = 0;
    uni_array->uni_member = malloc(sizeof(char));  //1 row * 1 column = 1 char
    if (buffer == NULL) {
        fprintf(stderr, "Error occured during buffer memory allocation\n");
        *uni_load_fail = true;
    }

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
            if (buffer == NULL) {
                fprintf(stderr, "Error occured during buffer memory allocation\n");
                *uni_load_fail = true;
            }
            if (strlen(buffer) > max_member_len) {
                fprintf(stderr, "Error: Universe member exceeding max. length of 30\n");
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
    if (buffer == NULL) {
        fprintf(stderr, "Error occured during buffer memory allocation\n");
        *set_load_fail = true;
    }

    if (set_array->member == NULL) {
        fprintf(stderr, "Error occured during set array memory allocation\n");
        *set_load_fail = true;
    }

    for (unsigned i = 2; i <= strlen(str_line); i++) {
        c = str_line[i];
        //printf("%c\n", c);
        if (c != ' ') {
            buffer = (char*) realloc(buffer, strlen(buffer) + sizeof(char)*2);
            if (buffer == NULL) {
                fprintf(stderr, "Error occured during buffer memory allocation\n");
                *set_load_fail = true;
            }
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
    int set_count = 0;   //Number of set lines

    bool uni_load_fail = false;
    bool set_load_fail = false;
    Universe_t uni_array;
    //Set_t *sets_array = malloc(sizeof(Set_t));
    Set_t *sets_array;

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

void relation_ctor(Rel_t* relation) {
    relation->member = NULL;
    relation-> rel_size = 0;
    relation->rel_index = 0;
}



// BITFIELD STUFF--------------------------------------------------

void rel_to_bitfield(Rel_t* rel_p, Universe_t* uni_p, Bitfield_t* field_p) {
    
    field_p->bit_len = uni_p->member_count * uni_p->member_count;
    field_p->byte_len = (int) ceil(field_p->bit_len / 8.0);
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





