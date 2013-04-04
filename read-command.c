// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"

#include <error.h>

/* FIXME: You may need to add #include directives, macro definitions,
   static function definitions, etc.  */

struct command_stream {
  int size;
  int iterator;
  command_t* next;
};

typedef enum {
  WORD_TOKEN,
  SEMICOLON_TOKEN,
  PIPE_TOKEN,
  AND_TOKEN,
  OR_TOKEN,
  LEFT_PAREN_TOKEN,
  RIGHT_PAREN_TOKEN,
  GREATER_TOKEN,
  LESS_TOKEN,
  COMMENTS_TOKEN,
  NEWLINE_TOKEN,
  MISC_TOKEN
} token_type;

typedef struct{
  token_type type;
  char* words;
} token;

command_stream_t
make_command_stream (int (*get_next_byte) (void *),
		     void *get_next_byte_argument)
{
  //Let's just try to read the input in first.
  
  
  /* FIXME: Replace this with your implementation.  You may need to
     add auxiliary functions and otherwise modify the source code.
     You can also use external functions defined in the GNU C Library.  */
  

  //error (1, 0, "command reading not yet implemented");
  return 0;
}

command_t
read_command_stream (command_stream_t s)
{
  /* FIXME: Replace this with your implementation too.  */
  error (1, 0, "command reading not yet implemented");
  return 0;
}
