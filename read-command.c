// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include "alloc.h"
#include <error.h>
#include <stdio.h>

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

typedef struct{
	token m_token;
	token_stream* next;
	token_stream* prev;
} token_stream;

token_stream_t insert_token (token_stream_t root, token_t target_token){
	//traverse to the end of the token_stream_t, insert the token, fix the pointers
	token_stream *iterator = root;
	while (root->next != NULL)
		iterator = iterator->
	
	
}

command_stream_t
make_command_stream (int (*get_next_byte) (void *), void *get_next_byte_argument)
{
  //=========Let's just try to read the input in first.============//
  
  size_t bufferSize = 1024;
  size_t bufferIterator = 0;
  char value;
  char* buffer = (char*) checked_malloc(bufferSize);

  while ((value = get_next_byte(get_next_byte_argument)) != EOF) //store into value while it isn't EOF
  {
    buffer[bufferIterator++] = value;
    //    printf("looped once: %c \n", value);
    //    printf("bufferSize: %d \n", (int) bufferSize);
    if (bufferSize == bufferIterator){
      buffer =  (char*) checked_grow_alloc(buffer, &bufferSize);
      //printf("called checked_realloc: %d\n", (int) bufferSize);
    }
  }
  if (bufferSize == bufferIterator){
    buffer =  (char*) checked_grow_alloc(buffer, &bufferSize);
    //printf("called checked_realloc: %d\n", (int) bufferSize);
  }
  buffer[bufferIterator] = '\0';

  //printf("bufferIterator: %d \n", (int) bufferIterator);
  //puts(buffer);  //will output to stdout
  
  //=========Let's tokenize the stream============//
  //we need to do the same thing as before, except instead of taking from the filestream and putting it into the array.
  //Now take the array and put it into a token stream.


  
  
  //=========Let's return a command stream============//
  command_stream_t fake = (command_stream_t) checked_malloc(sizeof(command_stream_t));
  fake->size = 1;
  fake->iterator = 0;
  return fake;
  
  

  //error (1, 0, "command reading not yet implemented");
  return 0;
}

command_t
read_command_stream (command_stream_t s)
{
  s->size = 1;
  
  /* FIXME: Replace this with your implementation too.  */
  error (1, 0, "command reading not yet implemented");
  return 0;
}
