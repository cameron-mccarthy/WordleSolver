#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//current logic problem = yellow and gray or green
//yellow case is broken
typedef struct WordList{
	char** words;
	int size;
} WordList;

WordList compare(char *input, char *result, WordList words);
bool test(char* input, char* result, char* word);
bool mCase(char letter, int position, char* word, char* result);
bool nCase(char letter, int position, char* word, char* result);
bool count(char letter, char* word);
bool contains(char letter, char* word);
// WALSI - Wordle Algorithmic Logic Solver Interface
int main(){
	FILE *file;
	const int WORDLE = 2309;
	const int ROUNDS = 1;
	WordList words;
	
	words.words = (char**)malloc(WORDLE * sizeof(char*));
	words.size = WORDLE;
	if (words.words == NULL){
		printf("memory not allocated");
		return 1;
	}
	char *input = (char*)malloc(6*sizeof(char));
	if (input == NULL){
		printf("memory not allocated");
		return 1;
	}
	char *result = (char*)malloc(6*sizeof(char));
	if (result == NULL){
		printf("memory not allocated");
		return 1;
	}
	char *buffer = (char*)malloc(8 *sizeof(char));
	if (buffer == NULL){
		printf("memory not allocated");
		return 1;
	}
	
	file = fopen("wordle.txt", "r");
	for(int i = 0; i< WORDLE; i++) {
		words.words[i] = (char*)malloc(6*sizeof(char));
		if (words.words[i]== NULL){
			printf("memory not allocated");
			return 1;
		}
		fgets(buffer, 8, file);
		strncpy(words.words[i], buffer, 5);	
	}
	fclose(file);
	
	printf("Hello, I am WALSI, Your Wordle Algorithmic Logic Solver Interface.\n");
	for(int i = 0; i < ROUNDS; i ++){
		printf("\nEnter a five letter word: ");
		fgets(buffer, 8, stdin);
		strncpy(input, buffer, 5);
		input[5] = '\0';
		
		printf("Active Wordle Results [Y, N, M]: ");
		fgets(buffer, 8, stdin);
		strncpy(result, buffer, 5);
		result[5] = '\0';
		
		words = compare(input, result, words);
	}
	
	free(buffer);
	free(words.words);
	free(input);
	free(result);
    return 0;
}



//finds all possible words
WordList compare(char *input, char *result, WordList words){
	int wIndex = 0;
	int pIndex = 0;
	WordList possible;
	possible.words = (char**)malloc(words.size * sizeof(char*)); 
	while(wIndex < words.size){
		if (test(input, result, words.words[wIndex])){
			possible.words[pIndex] = (char*)malloc(6*sizeof(char));
			if (possible.words[pIndex]== NULL){
				printf("memory not allocated");
				return possible;
			}
			possible.words[pIndex] = words.words[wIndex];
			printf("word possible: %s\n", possible.words[pIndex]);
			pIndex++;
		}

			wIndex++;
	}
	possible.size = pIndex;
	return possible;
}

//takes a singe word and sees if it is a possible result
bool test(char* input, char* result, char* word){

	for (int i = 0; i < 5; i++){
		switch(result[i]){
			case 'Y': 
				if (input[i] != word[i]){
					return false;
				}
				break;
				
			case 'N':
				if (!nCase(input[i], i, word, result)) {
					return false;
				}
				break;
				
			case 'M':
				if (!mCase(input[i], i, word, result)){
					return false;
				}
				break;
			default:
				printf("invalid result");
				return false;
				break;
				
		}
	}
	return true;
}

//word needs to contain letter not at position.
bool mCase(char letter, int position, char* word, char* result){
	/*
	if (checkfor2(letter, word)){
		for(int i = 0; i < 5; i ++){
			if( i< position && word[i] == letter && word[position] != letter){
				//dup letter came before. return true if word contains 2 letters not at i
				return true;
			}
			else if ( i > position && word[i] == letter && result[i] != 'N'){
				return true;
			}
		}
		return false;
	}
	*/
	//assuming one instance
	return (contains(letter, word) && word[position] != letter); 
}

//return true if word is still possible
//return false if word is not possible
bool nCase(char letter, int position, char* word, char* result){
	int count = count()
	for (int i = 0; i < 5; i++){
		if (i != position && word[i] == letter && (result[i] == 'Y' || result[i] == 'M')){
			return(!checkfor2(letter, word));
		}
	}
	
	//assuming one letter
	return(!contains(letter, word));

}

bool count(char letter, char* word){
	int count = 0;
	for(int i = 0; i < 5; i++){
		if (word[i] == letter)
			count++;
	}
	return count;
}

bool contains(char letter, char* word){
	for (int i = 0; i < 5; i++){
		if (word[i] == letter){
			return true;
		}		
	}
	return false;
}
