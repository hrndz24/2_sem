#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

struct List {
	int data;
	struct List *prev;
	struct List *next;
};
struct List* head = NULL;

void createList() {
	srand(time(0));
	//use current time as seed for random generator
	for (int i = 0; i < 10; i++) {
		struct List* newlist = new List;
		newlist->data = rand() % 100 - 49;
		newlist->prev = NULL;
		newlist->next = head;
		if (head != NULL)
			head->prev = newlist;
		head = newlist;
	}
}

void display() {
	struct List* current;
	current = head;
	while (current != NULL) {
		cout << current->data << " ";
		current = current->next;
	}
}

int findMin() {
	struct List* current;
	current = head;
	int min = head->data;

	while (current != NULL) {
		if (current->data < min) {
			min = current->data;
		}
		current = current->next;
	}
	cout << "\n\nMin element is "<< min << "\n\n";
	return min;
}

void deleteLeft(int min) {
	struct List* current;
	struct List* ghost = new List;
	current = head;

	while (current != NULL) {
		if (current->data == min) {
			if (current->prev == NULL) {
				break;
			}
			else {
				ghost = current->prev;
				if (ghost->prev != NULL) {
					ghost->prev->next = ghost->next;
					ghost->next->prev = ghost->prev;
				}
				else {
					head = current;
				}
				delete(ghost);
			}
		}
		current = current->next;
	}
}

void deleteRight(int min) {
	struct List* current;
	struct List* ghost = new List;
	current = head;

	while (current != NULL) {
		if (current->data == min) {
			if (current->next == NULL) {
				break;
			}
			else {
				ghost = current->next;
				if (ghost->next != NULL) {
					ghost->prev->next = ghost->next;
					ghost->next->prev = ghost->prev;
				}
				else {
					ghost->prev->next = NULL;
				}
				delete(ghost);
			}
		}
		current = current->next;
	}
}

void sort(){
	int swapped;
	struct List* current;
	struct List* end = NULL;

	do{
		swapped = 0;
		current = head;

		while (current->next != end){

			if (current->data > current->next->data){
				swap(current->data, current->next->data);
				swapped = 1;
			}
			current = current->next;
		}
		end = current;
	} while (swapped);
}

bool hasNumber(int number) {
	struct List* current;
	current = head;
	int index = 0;
	while (current != NULL) {
		if (current->data == number) {
			cout << "\n\nThe index of element '3' is " << index + 1 <<"\n";
			return true;
		}
		current = current->next;
		index += 1;
	}
	return false;
}

int main() {
	
	createList();
	cout << "\nThe doubly linked list is: \n";
	display();

	int min = findMin();
	deleteLeft(min);
	deleteRight(min);
	display();

	sort();
	cout << "\n\nThe sorted doubly linked list is: \n";
	display();

	if (!hasNumber(3)) {
		cout << "\n\nElement '3' is not found\n";
	}
	return 0;
}