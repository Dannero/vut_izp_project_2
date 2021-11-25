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
    int rel_x;
    int rel_y;
} Rel_mem;

Rel_mem *rel_array;  //Array of relation members

Rel_mem **multi_rel_arrays; //Array of relation arrays


    //SET STRUCTURES//

typedef struct {        //Structure for a set member
    char *set_mem;
    int set_mem_num;
} Set_member;

Set_member *set_array;  //Array of set members

Set_member **multi_set_arrays; //Array of set arrays






int main(int argc, char* argv[]) 
{
    if (argc != argument_count) {   //Checking the correct number of arguments
        return EXIT_FAILURE;
        fprintf(stderr,"Error: Wrong argument count\n");
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

    printf("%d",line_count);

return 0;
}
