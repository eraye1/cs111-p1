// UCLA CS 111 Lab 1 command reading

#include "command.h"
#include "command-internals.h"
#include "alloc.h"
#include <error.h>
#include <stdio.h>
#include <ctype.h>

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

//this function will return true if the character is part of a word token, else 0
int isWordChar (char input){
  if (isalnum(input))
    return 1;
  else if (input == '!' || input == '%' || input == '+' || input == ',' || input == '-' || input == '.' || input == '/' || input == ':' || input == '@' || input == '^' || input == '_')
    return 1;
  else
    return 0;
}

//this function is used to output tokens so we can see if it's actually working.
//TODO: MAYBE NOT NEEDED

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

  
  token_stream* tstream = (token_stream*) checked_malloc(sizeof(token_stream*));
  token_stream* trackend = tstream;
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
	comment = 0;
      }

    else //unknown character 
      {
	type = MISC_TOKEN;
      }
    //idea is to figure out how long the word length is and then use token adding part to figure out how far to add the words.  Also, make sure you move ahead in the outer loop.  This will also overwrite MISC_TOKEN if word is found
    int wordlength = 1;
    int placeholder = bufferIteratorT;
    if (isWordChar(first))  
      {
	type = WORD_TOKEN;
	
	while (isWordChar(buffer[bufferIteratorT+wordlength]))
	  {
	    wordlength++;
	  }
        bufferIteratorT += wordlength-1;
	printf("placeholder: %d + \n" , placeholder);
      printf("end: %d \n", bufferIteratorT);

      }

    

    //token insertion here.
    if (first == ' ' || first == '\t' || comment == 1)
      {
	//Don't insert
      }
    else 
      {
	token temp;
	temp.type = type;
	if ( type == WORD_TOKEN)
	  {
	    temp.words = (char*) checked_malloc ((sizeof(char)*wordlength)+1);
	    int i = 0;
	    for (; i != wordlength;i++)
	    {
	    	temp.words[i] = buffer[placeholder+i]; 
	    }
	    temp.words[i] = '\0';
	  }
	else
	  {
	    temp.words = NULL;	
	  }
	//now insert into token stream
	token_stream* temp_ts = (token_stream*) checked_malloc(sizeof(token_stream*));
	temp_ts->m_token = temp;  
	//might have a serious problem here because if m_token is just a copy of 
	//temp and temp gets erased because temp goes out of scope (e.g. out of this function), 
	//temp might get erased and that also deletes our character array for words, leaving a dangling pointer.
	//Honestly no clue if this part works, might need a redesign of some data structures or at least used differently
	temp_ts->next = NULL;
	temp_ts->prev = trackend;
	trackend->next = temp_ts;
	trackend = temp_ts;
      }

    bufferIteratorT++;
  }
  
  //now tstream should point to the beginning of a token stream
  //the issue is we initialize the tstream to a blank token so happens is the first token_stream in tstream is empty so we skip it.

  tstream = tstream->next;
  puts("WORD_TOKEN: 0 \nSEMICOLON_TOKEN: 1 \nPIPE_TOKEN: 2 \nAND_TOKEN: 3 \nOR_TOKEN: 4 \nLEFT_PAREN_TOKEN: 5 \nRIGHT_PAREN_TOKEN: 6 \nGREATER_TOKEN: 7 \nLESS_TOKEN: 8 \nCOMMENTS_TOKEN: 9 \nNEWLINE_TOKEN: 10 \nMISC_TOKEN: 11 \n");
  
  //puts(tstream->m_token.words);
  
  while (tstream->next != NULL)
    {
      //printf("%d \n", tstream->m_token.type);
      //the above line works to display just the tokens, the below doesn't work because there's a segfault on accessing the token words
      if (tstream->m_token.type == WORD_TOKEN)
	{
	printf("%d: ", tstream->m_token.type);
	puts(tstream->m_token.words);
	puts("\n");
	}
      else
	printf("%d \n", tstream->m_token.type);
      
      tstream = tstream->next;
    }
printf("%d \n", tstream->m_token.type);
  


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
