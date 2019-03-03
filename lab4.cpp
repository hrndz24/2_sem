#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<iostream>
#include <chrono>
#define LENGTH 7
using namespace std::chrono;
using namespace std;

struct Route {
	int number;
	const char* type;
	const char* destination;
	double departureTime;
	double arrivalTime;
}routes[LENGTH];

void bubbleSort() {
	for (int i = 0; i < LENGTH - 1; i++) {
		for (int j = 0; j < LENGTH; j++) {
			if (routes[j].departureTime < routes[j - 1].departureTime) {
				swap(routes[j], routes[j - 1]);
			}
		}
	}
}

void insertionSort(){
	int i, j;
	double temp;
	for (i = 1; i < LENGTH; i++){
		temp = routes[i].departureTime;
		for (j = i - 1; j >= 0 && temp < routes[j].departureTime; j--) {
			swap(routes[j + 1], routes[j]);
		}
		routes[j + 1].departureTime = temp;
	}
}

/* takes last element as pivot, places the pivot element at its correct
position in sorted array, places all smaller elements to the left of pivot 
and all greater elements to the right of pivot */
int partition(int low, int high){

	int pivot = routes[high].departureTime;    // pivot 
	int i = (low - 1);  // Index of smaller element 

	for (int j = low; j <= high - 1; j++){
		// If current element is smaller than or 
		// equal to pivot 
		if (routes[j].departureTime <= pivot){
			i++;    // increment index of smaller element 
			swap(routes[i], routes[j]);
		}
	}
	swap(routes[i + 1], routes[high]);
	return (i + 1);
}

void quickSort( int low, int high){
	if (low < high){

		/* pi is partitioning index, arr[p] is now
		   at right place */
		int pi = partition(low, high);

		// Separately sort elements before 
		// partition and after partition 
		quickSort(low, pi - 1);
		quickSort(pi + 1, high);
	}
}

void createRoutes() {
	routes[0] = { 3673, "plane", "Pinsk", 12.45, 13.43 };
	routes[1] = { 2345, "car", "Bonn", 06.45, 23.14 };
	routes[2] = { 9139, "bus", "London", 13.16, 23.59 };
	routes[3] = { 1947, "train", "New York", 01.16, 18.34 };
	routes[4] = { 2038, "minibus", "Paris", 07.18, 22.47 };
	routes[5] = { 1111, "plane", "Madrid", 18.45, 21.38 };
	routes[6] = { 8645, "car", "Minsk", 22.22, 23.59 };
}

void display() {
	for (int i = 0; i < 7; i++) {
		cout << routes[i].number << " ";
		cout << routes[i].type << " ";
		cout << routes[i].destination << " ";
		cout << routes[i].departureTime << " ";
		cout << routes[i].arrivalTime << " ";
		cout << "\n";
	}
}

int main() {
	high_resolution_clock::time_point t1, t2;

	createRoutes();	
	t1 = high_resolution_clock::now();
	bubbleSort();
	t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout <<"\nBubble sort : "<< duration<<"\n";
	display();

	createRoutes();
	t1 = high_resolution_clock::now();
	quickSort(0, 6);
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "\n\nQuick sort : " << duration << "\n";
	display();
	cout << "\n";

	createRoutes();
	t1 = high_resolution_clock::now();
	insertionSort();
	t2 = high_resolution_clock::now();
	duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "\n\nInsertion sort : " << duration << "\n";
	display();
	cout << "\n";
	return 0;
}