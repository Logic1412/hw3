#include "sorter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* This loads the specified file into a new loaded_file
 * structure.  In particular it breaks up each line (by '\n')
 * and loads it into a line_struct, storing it in the
 * newly allocated file struct.
 * 
 * It is OK to reallocate for each character and each line
 * (as realloc under
 * the hood won't actually move things except on a power-of-two
 * type boundary), but you need to read things in a character
 * at a time for this to work with binary data.
*/
loaded_file *load_file(FILE *f)
{
  (void) f;
  HERE;
  return NULL;
}

/*
*/
void free_file(loaded_file *f)
{
  (void) f;
  HERE;
}

/*
 * the C qsort() utility takes a comparison function that
 * is a little different.  Becaues it wants to work on data that
 * can be of arbitrary sized (so, eg, an array of structures) rather
 * than just void* items, it wants pointers-to-pointers.
 * 
 * Similarly we can't use strcmp in this because we actually need
 * to evaluate strings that can contain null pointers.  But we will
 * just do strict character comparison:  
 * 
 * for i from 0 to length of min(a/b), if a[i] < b[i] then its -1,
 * if a[i] > b[i] its +1, and if a[i] = b[i] we increment i.
 * Then its the shorter string is before, and 0 if the
 * strings are fully equal.
*/
int sorter_comp(const void *a, const void *b){
  (void) a;
  (void) b;
  HERE;
  return 0;
}

/* You probably want to use qsort */
void sort_file(loaded_file *f)
{
  (void) f;
  HERE;
}

/*
 * As a reminder the lines can include nulls, so C printing of string
 * routines can't work.  Instead we need to print the string a character
 * at a time to standard output using putchar()
*/
void print_file(loaded_file *f)
{
  (void) f;
  HERE;
}
