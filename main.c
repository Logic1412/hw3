#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sorter.h"

/* This simple main should work as follows:
   For each filename passed as a command line argument:
   
   1)  Open the file.  If the file fails to open, exit with code 42
   2)  Load the file into a loaded_file structure using load_file
   3)  When the file is loaded, sort the file with sort_file
   4)  When the file is sorted, print the file to standard output with
       print_file
   5)  Free the loaded_file structure with free_file, and close
       the FILE pointer itself

   If there are no files specified it should simply exit.
*/

int main(int argc, char **argv) {
  (void) argc;
  (void) argv;
  HERE;
  return 0;
}
