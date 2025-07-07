#ifndef header_h
#define header_h

typedef struct WordList{
	char** words;
	int size;
} WordList;

#define WORDLE 2309

WordList* build();
WordList compare(char *input, char *result, WordList words);
bool test(char* input, char* result, char* word);
bool mCase(char letter, int position, char* test, char* input, char* result);
bool nCase(char letter, int position, char* test, char* input, char* result);
int count(char letter, char* word);
bool contains(char letter, char* word);
char* generate(char* answer, char* input);

#endif