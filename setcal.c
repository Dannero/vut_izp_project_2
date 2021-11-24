#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//const member_len = 30;

typedef struct {                //Structure for a universe member
    char member[30];
    int member_num;
} Universe_t;





int main(int argc, char* argv[]) 
{
    if (argc != 2) {
        return EXIT_FAILURE;
        fprintf(stderr,"Wrong argument count\n");
    }

    FILE *fp;

    fp = fopen(argv[1],"r");

    (void) argc;
    (void) argv;
    int line_count = 1;
    int line_pos = 0;
    
    while(1)
    {
      char c = fgetc(fp);
      ++line_pos;

      if (line_count == 1)&&(line_pos == 1)&&(c == 'U')) {
          printf("Preslo\n");
      }

      if (c == '\n') {
          line_count++;
          line_pos = 0;
      }

      if( feof(fp) ) {
         break ;
      }
      printf("%c", c);
    
    }

    printf("%d",line_count);

return 0;
}