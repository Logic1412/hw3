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

  if (!f) return NULL;
  loaded_file *file = malloc(sizeof(loaded_file));
  if (!file) return NULL;
  file->lines = NULL;
  file->num_lines = 0;
  line *cur_line = NULL;
  size_t line_len = 0;
  int c;

  while ((c = fgetc(f)) != EOF) {
    if (!cur_line) {
      cur_line = malloc(sizeof(line));
      cur_line->data = NULL;
      cur_line->length = 0;
    }

    cur_line->data = realloc(cur_line->data, line_len + 1);
    cur_line->data[line_len++] = (unsigned char)c;

    if (c == '\n') {
      cur_line->length = line_len;
      file->lines = realloc(file->lines, (file->num_lines + 1) * sizeof(line *));
      file->lines[file->num_lines++] = cur_line;
      
      cur_line = NULL;
      line_len = 0;
    }
  }

  if (cur_line && line_len > 0) {
    cur_line->length = line_len;
    file->lines = realloc(file->lines, (file->num_lines + 1) * sizeof(line *));
    file->lines[file->num_lines++] = cur_line;
  }

  return file;
}

/*
*/
void free_file(loaded_file *f)
{
  (void) f;
  if (!f) return;
  for (size_t i = 0; i < f->num_lines; i++) {
    free(f->lines[i]->data);
    free(f->lines[i]);
  }
  free(f->lines);
  free(f);
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
  const line *line_a = *(const line **)a;
  const line *line_b = *(const line **)b;

  size_t min_length = line_a->length < line_b->length ? line_a->length : line_b->length;
  for (size_t i = 0; i < min_length; i++) {
    if (line_a->data[i] < line_b->data[i]) return -1;
    if (line_a->data[i] > line_b->data[i]) return 1;
  }
  if (line_a->length < line_b->length) return -1;
  if (line_a->length > line_b->length) return 1;
  
  return 0;
}

/* You probably want to use qsort */
void sort_file(loaded_file *f)
{
  (void) f;
  if (f && f->lines && f->num_lines > 0) {
    qsort(f->lines, f->num_lines, sizeof(line *), sorter_comp);
  }
}

/*
 * As a reminder the lines can include nulls, so C printing of string
 * routines can't work.  Instead we need to print the string a character
 * at a time to standard output using putchar()
*/
void print_file(loaded_file *f)
{
  if (!f) return;
  for (size_t i = 0; i < f->num_lines; i++) {
    for (size_t j = 0; j < f->lines[i]->length; j++) {
      putchar(f->lines[i]->data[j]);
    }
  }
}
