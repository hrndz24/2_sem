#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#define N 7
#define INFINITY 9999

// adjacency between two vertices
struct Edge {
	int distance;
	const char *target;
};

struct Vertex {
	const char* name;
	Edge adjacencies[N - 1];
	int minDistance = INFINITY;
	Vertex *previous = NULL;
	Vertex * next; //  needed for the queue
}graph[N];

struct Queue {
	struct Vertex *front;
	struct Vertex *last;
	unsigned int size;
}vertexQueue;

// removes an element from the queue
void remove(struct Queue *q, Vertex *vertex) {
	q->size-=1;
	if (q->front != NULL) {
		if (strcmp(q->front->name, vertex->name) == 0) {
			if (q->front->next != NULL) {
				q->front = q->front->next;
			}
			else {
				q->front = NULL;
			}
		}
		else {
			struct Vertex* current = q->front;
			while (current->next != NULL) {
				if (strcmp(current->next->name, vertex->name) == 0) {
					current->next = current->next->next;
				}
				current = current->next;
			}
		}
	}
}

// gets and removes an element from the queue
Vertex* poll(struct Queue *q) {
	q->size-=1;
	struct Vertex *temp = q->front;
	q->front = q->front->next;
	return temp;
}

// adds an element to the queue
void add(struct Queue *q, Vertex *vertex) {
	q->size+=1;
	if (q->front == NULL) {
		q->front = (struct Vertex *) malloc(sizeof(struct Vertex));
		q->front = vertex;
		q->front->next = NULL;
		q->last = q->front;
	}
	else {
		q->last->next = (struct Vertex *) malloc(sizeof(struct Vertex));
		q->last->next = vertex;
		q->last->next->next = NULL;
		q->last = q->last->next;
	}
}

void createGraph() {
	graph[0].name = "A";
	graph[1].name = "B";
	graph[2].name = "C";
	graph[3].name = "D";
	graph[4].name = "E";
	graph[5].name = "F";
	graph[6].name = "G";
	graph[0].adjacencies[0] = { 1, "B" };
	graph[1].adjacencies[0] = { 1, "C" };
	graph[1].adjacencies[1] = { 2, "D" };
	graph[3].adjacencies[0] = { 3, "E" };
	graph[3].adjacencies[1] = { 12, "F" };
	graph[3].adjacencies[2] = { 2, "B" };
	graph[4].adjacencies[0] = { 2, "G" };
	graph[6].adjacencies[0] = { 5, "F" };
}

Vertex* findVertex(char *vertexName) {
	for (int i = 0; i < N; i++) {
		if (strcmp(graph[i].name, vertexName) == 0) {
			return &graph[i];
		}
	}
	return NULL;
}

// uses Dijkstra algorithm to find the shortest paths
void computePaths(Vertex *start) {
	start->minDistance = 0;
	add(&vertexQueue, start);

	while (vertexQueue.front != NULL) {
		Vertex*u = poll(&vertexQueue);
		// looks through adjacencies of u
		if (u->adjacencies != NULL) {
			for (int i = 0; i < N - 1; i++) {
				if (u->adjacencies[i].distance != NULL) {
					// finds the target vertex of an adjacency
					const char* vName = u->adjacencies[i].target;
					Vertex* v = NULL;
					for (int j = 0; j < N; j++) {
						if (strcmp(graph[j].name, vName) == 0) {
							v = &graph[j];
						}
					}
					int distance = u->adjacencies[i].distance;
					int distanceThroughU = u->minDistance + distance;
					// checks if it is the shortest path
					if (distanceThroughU < v->minDistance) {
						remove(&vertexQueue, v);
						v->minDistance = distanceThroughU;
						v->previous = u;
						add(&vertexQueue, v);
					}
				}
			}
		}
	}
}

// prints the shortest path to a given vertex
void getShortestPathTo(Vertex* finish) {	
	int k = 0;
	const char* path[N];
	Vertex* vertex = finish;
	while (vertex != NULL) {
		path[k] =  vertex->name;
		vertex = vertex->previous;
		k += 1;
	}
	for (; k > 0; k--) {
		printf("%s ", path[k - 1]);
	}
}

int main() {
	createGraph();

	char pointA[20], pointB[20];

	printf( "Enter the starting point: ");
	gets_s(pointA);
	Vertex* start = findVertex(pointA);
	if (start == NULL) {
		printf("\nThere is no such vertex!\n");
		return 0;
	}

	printf("Enter the finishing point: ");
	gets_s(pointB);
	Vertex* finish = findVertex(pointB);
	if (finish == NULL) {
		printf("\nThere is no such vertex!\n");
		return 0;
	}

	computePaths(start);
	if (finish->minDistance == INFINITY) {
		printf("\nNo path between given points found!\n");
		return 0;
	}
	printf("\nThe path is: ");
	getShortestPathTo(finish);
	printf("\nThe distance is: %d\n", finish->minDistance );

	return 0;
}