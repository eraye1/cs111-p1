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


typedef struct token{
  token_type type;
  char* words;
} token;

typedef struct token_stream{
 token m_token;
 struct token_stream* next;
 struct token_stream* prev;
} token_stream;

/*
struct token{
  token_type type;
  char* words;
};

struct token_stream{
 token m_token;
 struct token_stream* next;
 struct token_stream* prev;
};
*/

//could never get this piece of shit working
/*token_stream_t insert_token (token_stream_t root, token_t target_token){
 //traverse to the end of the token_stream_t, insert the token, fix the pointers
 struct token_stream iterator = *root;
 while (&root.next != NULL){
   iterator = (iterator->next);
 }  
 struct token_stream temp = (*token_stream) checked_malloc(sizeof(token_stream));
 temp->m_token = target_token;
 temp->next = NULL;
 temp->prev = iterator;
 iterator->next = &temp;
 return root;
 }*/

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
  //Could never get the outside function working due to all that referential bullshit.  Let's just do it inline.

  
  token_stream_t tstream = (token_stream_t) checked_malloc(sizeof(token_stream_t));
  int bufferIteratorT = 0;
  int comment = 0;
  
  token_type type;
  
  //do a dual parsing here where we handle two characters at the same time. This makes the && and || and comments easy
  //Need to check if the buffer is completely empty (has '\0' as the only character).  Then we don't do anything so we  //can just return

  

  if (buffer[bufferIteratorT] == '\0')
  {  
    command_stream_t empty = (command_stream_t) checked_malloc(sizeof(command_stream_t));
    empty->size = 0;
    return empty;
  }
  char first;
  char second;
  while (buffer[bufferIteratorT+1] != '\0')
  {
    first = buffer[bufferIteratorT];
    second = buffer[bufferIteratorT+1];

    //Check for &&
    if (first == '&')
      {
        if (second == '&')
          { 
     	    type = AND_TOKEN;
	    bufferIteratorT++;//deals with the fact that && is two chars
          }
        else
          {
	    type = MISC_TOKEN;  //We can test for MISC_TOKEN later, this is an invalid input, only 1 &
          }
	  //TODO:  insert token here
      }
    
    //Check for ||
    else if (first == '|')
      {
	if (second == '|')
	  {
	    type = OR_TOKEN;
	    bufferIteratorT++;
          }
	else
	  {
	    type = PIPE_TOKEN;	    
	  }
	//TODO:  insert token here
      }

    else if (first == ';')
      {
	type = SEMICOLON_TOKEN;
	//TODO:  insert token here
      }

    else if (first == '(')
      {
	type = LEFT_PAREN_TOKEN;
      }

    else if (first == ')')
      {
	type = RIGHT_PAREN_TOKEN;
      }

    else if (first == '<')
      {
	type = LESS_TOKEN;
      }

    else if (first == '>')
      {
	type = GREATER_TOKEN;
      }

    else if (first == '\n')
      {
	type = NEWLINE_TOKEN;
      }

    else if ()
      {

      }

    else //unknown character 
      {
	type = MISC_TOKEN;
      }

    //token insertion here.
    if (first == ' ' || first == '\t')
      {
	//Don't insert
      }
    else 
      {
	//insert token here
      }

    bufferIteratorT++;
  }
  
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
