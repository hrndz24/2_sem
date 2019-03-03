#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#define LENGTH 7
#define KEY 3
using namespace std;

struct Route {
	int number;
	const char* type;
	const char* destination;
	double departureTime;
	double arrivalTime;
}routes[LENGTH];

struct HashRoute {
	int hashCode;
	Route route;
} hashRoutes[LENGTH];

void createRoutes() {
	routes[0] = { 3673, "plane", "Pinsk", 12.45, 13.43 };
	routes[1] = { 2345, "car", "Bonn", 06.45, 23.14 };
	routes[2] = { 9139, "bus", "London", 13.16, 23.59 };
	routes[3] = { 1947, "train", "New York", 01.16, 18.34 };
	routes[4] = { 2038, "minibus", "Paris", 07.18, 22.47 };
	routes[5] = { 1111, "plane", "Madrid", 18.45, 21.38 };
	routes[6] = { 8645, "car", "Minsk", 22.22, 23.59 };
}

void display(int index) {
		cout << routes[index].number << " ";
		cout << routes[index].type << " ";
		cout << routes[index].destination << " ";
		cout << routes[index].departureTime << " ";
		cout << routes[index].arrivalTime << " ";
		cout << "\n";
}

int findDigitsNumber(double number, int power) {
	if ((number / pow(10, power)) < 1) {
		return power;
	}
	else {
		findDigitsNumber(number, power + 1);
	}
}

int* toArray(double departureTime, int digitsNumber) {
	int* array = new int[5];
	if (digitsNumber == 5) {
		array[0] = departureTime / 10;
		array[1] = (int)departureTime % 10;
		array[2] = 46;
		array[3] = (int)(departureTime * 10) % 10;
		array[4] = (int)(departureTime * 100) % 100;
	}
	else {
		array[0] = (int)departureTime % 10;
		array[1] = 46;
		array[2] = (int)(departureTime * 10) % 10;
		array[3] = (int)(departureTime * 100) % 100;
	}
	return array;
}

int calculateHashCode(const char* destination, double departureTime) {
	int hashCode = 0, i = 0;
	int length = strlen(destination);
	int digitsNumber = findDigitsNumber(departureTime, 0)+3;
	int* convertedDT = toArray(departureTime, digitsNumber);
	for (i = 0; i < length; i++) {
		hashCode += (int)destination[i] * pow(KEY, i);
	}
	for (int j = 0; j < digitsNumber; j++, i++) {
		hashCode += convertedDT[j] * pow(KEY, i);
	}
	return hashCode;
}

void checkHash(int inputHashCode) {
	for (int i = 0; i < LENGTH; i++) {
		if (hashRoutes[i].hashCode == inputHashCode) {
			cout << "\nThe route is:\n";
			display(i);
		}
	}
}

int main() {
	createRoutes();
	for (int i = 0; i < LENGTH; i++) {
		hashRoutes[i].hashCode = calculateHashCode(routes[i].destination, routes[i].departureTime);
		hashRoutes[i].route = routes[i];
	}
	char destination_needed[20];
	double time_needed;
	cout<<("\nEnter departure time: ");	
	cin >> time_needed;
	cout << ("\nEnter destination: ");
	cin >> destination_needed;
	int inputHashCode = calculateHashCode(destination_needed, time_needed);
	checkHash(inputHashCode);
	return 0;
}