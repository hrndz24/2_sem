#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

int cyclic(int number) {
	int amount = 0;
	while ((number / pow(10, amount)) >= 1) {
		amount += 1;
	}
	return amount;
}

int recursive(int number, int power) {
	if ((number / pow(10, power)) < 1) {
		return power;
	}
	else {
		recursive(number, power + 1);
	}
}

int main() {
	int number, amount;
	cout << "Enter number: ";
	cin >> number;

	cout << "\nNumber of digits calculated:";
	amount = cyclic(number);
	cout <<"\n\nwithout recursion: " <<amount;

	amount = recursive(number, 0);
	cout <<"\nwith recursion: " <<amount;
	cout << "\n";
	return 0;
}