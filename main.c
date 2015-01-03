/* Simple version of hangman game.
    Copyright (C) 2015 Carla Shearer

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 
*/

#include <stdio.h>
#include <limits.h>
#include <string.h>

char s[LINE_MAX];
int mask[LINE_MAX];
int blind[93];
int guesses = 11;
char* hang = "__________\n|  /     |\n| /      |\n|/       O\n|       /|\\\n|        |\n|       / \\\n|\n|_________\n";
int hangmask[93] = {3,3,3,3,3,3,3,3,3,3,0,2,0,0,4,0,0,0,0,0,5,0,2,0,4,0,0,0,0,0,0,5,0,2,4,0,0,0,0,0,0,0,6,0,2,0,0,0,0,0,0,0,7,7,7,0,2,0,0,0,0,0,0,0,0,8,0,2,0,0,0,0,0,0,0,9,0,10,0,2,1,1,1,1,1,1,1,1,1,1,1,0};

int uncover_word(char l) ;

int hangman()
{
	int i = 0;
	for(i = 0; i < 93; i++){
		if((10 - guesses) >= hangmask[i]){
			printf("%c", hang[i]);
		}
		else {
			printf(" ");
		}
	}
}

char input() 
{
	char l[LINE_MAX];
	int ret;
	uncover_word(' ');
	for (;;) {
		fgets(l, LINE_MAX, stdin);
		//printf("You typed %c\n", l[0]);
		if (ret = uncover_word(l[0])) {
			if(ret == 1){
				printf("\nWell done\n");
			}
			else {
				printf("You are a failure\n");
				hangman();
			}
			guesses = 11;
			word();
			uncover_word(' ');
		}
		hangman();
	}
}

int main() 
{
	if (word() == 1){
		return 1;
	}
	printf("Welcome to Hangman! Enter your guess\n");
	hangman();
	input();
}

int uncover_word(char l) 
{
	int i = 0;
	int finished = 1;
	int new = 0;
	for(i = 0; i < strlen(s) - 1; i++){
		if(s[i] == l){
			if(mask[i] == 0){
				new = 1;
			}
			mask[i] = 1;
		}
		if(mask[i] == 0){
			finished = 0;
			printf("_ ");
		}
		else {
			printf("%c ", s[i]);
		}
	}
	printf("\n");
	if(!new){
		printf("You have %i guesses remaining\n", --guesses);
		if(guesses < 1){
			printf("You have lost\n");
			return -1;
		}
	}
	return finished;
}

int word() 
{
	FILE *fd;
	int i = 0;
	int r;
	memset(mask, 0, LINE_MAX);
	fd = fopen("words", "r");
	if (fd == NULL) {
		printf("File not found\n");
		return 1;
	}
	while (fgets(s, LINE_MAX, fd) != NULL){
		i++;
	}
	//printf("I found %i words\n", i);
	r = random(i);
	rewind(fd);
	for (i = 0; i <= r; i++){
		fgets(s, LINE_MAX, fd);
	}
	//printf("My random word is %s\n", s);
	fclose(fd);
	return 0;
}

int random(int i) 
{
	srand(time(NULL));
	return rand()%i;
}
