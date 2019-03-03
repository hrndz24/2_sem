#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <iostream>
using namespace std;

int enterCode() {
	int code;
	printf("\nWhat do you want to do: \n");
	printf("\nExit - 0 \n");
	printf("Change case of letters - 1 \n");
	printf("Delete words - 2 \n");
	printf("Replace words - 3 \n");
	printf("Enter code : ");
	scanf_s("%i", &code);
	return code;
}

char* cutPieceFromLine(char *line, int start, int end) {
	char *piece = (char *)malloc(sizeof(char) * 40);
	int p, l;
	for (p = 0, l = start; l < end; l++, p++) {
		piece[p] = line[l];
	}
	piece[p] = '\0';
	return piece;
}

void changeCase(FILE* f2, FILE* output) {
	int ch;	
	while ((ch = fgetc(f2)) != EOF) {
		if (ch >= 65 && ch <= 90) {
			fprintf(output, "%c", ch + 32);
		}
		else if (ch >= 97 && ch <= 122) {
			fprintf(output, "%c", ch - 32);
		}
		else {
			fprintf(output, "%c", ch);
		}
	}	
}

void deleteWords(FILE* f2, FILE* output, char* Dword) {
	char line[256];
	while (fgets(line, 256, f2) != NULL) {
		int start = 0, end = 0;
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] == 32 || line[i] == 44 || line[i] == 13 || line[i] == 46) {
				end = i;
				char* word = cutPieceFromLine(line, start, end);
				start = i + 1;
				if (strcmp(word, Dword) != 0) {
					fprintf(output, "%s", word);
				}
				else {
					fprintf(output, "%c", line[i]);
				}
			}
		}
		fprintf(output, "\r\n");
	}
}

void replaceWords(FILE* f2, FILE* output, char* Dword, char* Rword) {
	char line[256];
	while (fgets(line, 256, f2) != NULL) {
		int start = 0, end = 0;
		for (int i = 0; i < strlen(line); i++) {
			if (line[i] == 32 || line[i] == 44 || line[i] == 13 || line[i] == 46) {
				end = i;
				char* word = cutPieceFromLine(line, start, end);
				start = i + 1;
				if (strcmp(word, Dword) != 0) {
					fprintf(output, "%s%C", word, line[i]);
				}
				else {
					fprintf(output, "%s%c", Rword, line[i]);
				}
			}
		}
		fprintf(output, "\r\n");
	}
}

int main() {
	FILE *f2, *output;
	if (!(f2 = fopen("e:\\work\\another_level.txt", "r + b"))) {
		puts("\n File not found!");
		return 0;
	}
	if (!(output = fopen("e:\\work\\output.txt", "w + b"))) {
		puts("\n File not found!");
		return 0;
	}
	int code = enterCode();
	char Dword[20];
	switch(code){
	case 0:
		return 0;
	case 1: 
		changeCase(f2, output);
		break;
	case 2:		
		cout << "\nEnter the word you want to delete: ";
		cin >> Dword;
		deleteWords(f2, output, Dword);
		break;
	case 3:
		char Rword[20];
		cout << "\nEnter the word you want to replace: ";
		cin >> Dword;
		cout << "\nEnter the word you want to replace with: ";
		cin >> Rword;
		replaceWords(f2, output, Dword, Rword);
	}
	fclose(f2);
	fclose(output);
	return 0;
}