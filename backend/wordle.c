#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "header.h"

// WALSI - Wordle Algorithmic Logic Solver Interface
int rounds(){
	
	const int ROUNDS = 5;
	
	char *input = malloc(6*sizeof(char));
	char *result = malloc(6*sizeof(char));
	char *buffer = malloc(8*sizeof(char));
	WordList words = *build();

	if (input == NULL || result == NULL || buffer == NULL || words.words == NULL){
		printf("memory not allocated");
		return 1;
	}
	
	WordList currentwords;
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
		
		//This is currently not right, 
		currentwords = compare(input, result, words);
		printf("Curr = %d, words = %d", currentwords.size, words.size);
		if (words.size < 2)
			break;
	}
	
	free(words.words);
	free(input);
	free(result);
	free(buffer);
    return 0;
}

WordList* build(){
	FILE *file;
	WordList* words = malloc(sizeof(WordList));
	words->words = malloc(WORDLE * sizeof(char*));
	words->size = WORDLE;
	char *buffer = malloc(8 *sizeof(char));

	if (buffer == NULL || words->words == NULL){
		printf("memory not allocated");
		return NULL;
	}

	file = fopen("wordle.txt", "r");
	for(int i = 0; i < WORDLE; i++) {
		words->words[i] = malloc(6*sizeof(char));
		if (words->words[i] == NULL){
			printf("memory not allocated");
			return NULL;
		}
		fgets(buffer, 8, file);
		strncpy(words->words[i], buffer, 5);	
	}
	fclose(file);
	free(buffer);
	return words;
}

//finds all possible words
WordList compare(char *input, char *result, WordList words){
	int wIndex = 0;
	int pIndex = 0;
	WordList possible;
	possible.words = malloc(words.size * sizeof(char*)); 
	while(wIndex < words.size){
		if (test(input, result, words.words[wIndex])){
			possible.words[pIndex] = malloc(6*sizeof(char));
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
				if (!nCase(input[i], i, word, input, result)) {
					return false;
				}
				break;
				
			case 'M':
				if (!mCase(input[i], i, word, input, result)){
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
bool mCase(char letter, int position, char* test, char* input, char* result){
	int amount = count(letter, input);
	if (amount > 1){
		int actual = 0;
		for (int i = 0; i < 5; i++){
			if(input[i] == letter && result[i]!='N'){
				actual++;
			}
		}
		return (count(letter, test) >= actual && test[position] != letter);   
	}
	//assuming one instance
	return (contains(letter, test) && test[position] != letter); 
}

//return true if word is still possible
//return false if word is not possible
bool nCase(char letter, int position, char* test, char* input, char* result){
	int amount = count(letter, input);
	if (amount > 1){
		int null = 0;
		for (int i = 0; i < 5; i++){
			if(input[i] == letter && result[i]=='N'){
				null++;
			}
		}
		//mystery word has 'actual' number of letters.
		//amount in guess - amount in mystery = null
		//null will always be at least one. 
		return (count(letter, test) == amount-null && test[position] != letter);   
	}
	
	//assuming one letter
	return(!contains(letter, test));

}

//counts occurances of a single letter in a word
int count(char letter, char* word){
	int count = 0;
	for(int i = 0; i < 5; i++){
		if (word[i] == letter)
			count++;
	}
	return count;
}

//sees if a word contains a letter
bool contains(char letter, char* word){
	for (int i = 0; i < 5; i++){
		if (word[i] == letter){
			return true;
		}		
	}
	return false;
}

//takes an input and generates the wordle colors based on the correct answer
char* generate(char* answer, char* input){
	char* result = malloc(6*sizeof(char)); 
	if (result == NULL){
			printf("memory not allocated");
			return NULL;
		}
	result[5] = '\0';
	for (int i = 0; i < 5; i ++){
		if (answer[i] == input[i]){
			result[i] = 'Y';
			//this section overrides previous 'M' if there is a green letter match
			for (int j = 0; j < i; j++){
				if (input[i] == input[j] && result[j] == 'M'){
					result[j] = 'N';
					break;
				}
			}
		}
		else if (contains(input[i], answer)){
			//check which occurance of the letter we are at, and where the last one was
			int occurance = 1;
			int index = i;
			for (int j = 0; j < i; j++){
				if (input[i] == input[j]){
					occurance++;
					index == j;
				}
			}
			result[i] = (occurance > count(input[i], answer)) ? 'N' : 'M';
		}
		else{
			result[i] = 'N';
		}
	}
	return result;
}