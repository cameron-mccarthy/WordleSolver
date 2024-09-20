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
bool mCase(char letter, int position, char* word);
bool nCase(char letter, int position, char* word);

// WALSI - Wordle Algorithmic Logic Solver Interface
int main(){
	FILE *file;
	const int WORDLE = 2309;
	const int ROUNDS = 6;
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
	char *buffer = (char*)malloc(7 *sizeof(char));
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
		fgets(buffer, 6, file);
		printf("buffer at %d = %s \n", i, buffer);
		buffer[5] = '\0';
		strncpy(words.words[i], buffer, 6);
		words.words[i][5] = '\0';
		//printf("word at %d = %s \n", i, words.words[i]);
	}
	fclose(file);
	
	printf("Hello, I am WALSI, Your Wordle Algorithmic Logic Solver Interface.\n");
	for(int i = 0; i < ROUNDS; i ++){
		printf("\nEnter a five letter word: ");
		fgets(buffer, 7, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		strncpy(input, buffer, 5);
		input[5] = '\0';
		
		printf("Active Wordle Results [Y, N, M]: ");
		fgets(buffer, 7, stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		strncpy(result, buffer, 5);
		result[5] = '\0';
		
		//words = compare(input, result, words);
	}

	free(buffer);
	free(words.words);
	free(input);
	free(result);
    return 0;
}



//finds all possible words
WordList compare(char *input, char *result, WordList words){
	printf("\ncompare\n");
	printf("input is %s\nresult is %s\nPossible words are:", input, result);
	int wIndex = 0;
	int pIndex = 0;
	WordList possible;
	possible.words = (char**)malloc(words.size * sizeof(char*)); 
	while(wIndex < words.size){
		
		//if (test(input, result, words.words[wIndex])){
		if(true){
			possible.words[pIndex] = (char*)malloc(6*sizeof(char));
			if (possible.words[pIndex]== NULL){
				printf("memory not allocated");
				return possible;
			}
			possible.words[pIndex] = words.words[wIndex];
			printf("\n%s", possible.words[pIndex]);
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
				if (strchr(word, input[i])&& !nCase(input[i], i, word)) {
					return false;
				}
				break;
			case 'M':
				if (!mCase(input[i], i, word)){
					return false;
				}
				break;
			default:
				//printf("invalid result");
				return false;
				break;
		}
	}
	return true;
}

//word needs to contain letter not at position.
bool mCase(char letter, int position, char* word){
	int count = 0;
	int compare = 0;
	bool check;
	for(int i = 0; i < 5; i++){
		if (word[i] == letter){
			count ++;
		}
	}
		for(int i = 0; i < 5; i++){
			if (word[i] == letter && i != position){
				if (i != position){
					check = true;
				}
				compare ++;
			}
		}
	if (check && count == compare){
		return true;
	}
	return false;
}

bool nCase(char letter, int position, char* word){
	for (int i = position +1 ; i < 5; i++){
		if (word[i] == letter){
			//return here, and it mights still be possible
			return true;
		}
	}
	//return here, word is not an option
	return false;
}
