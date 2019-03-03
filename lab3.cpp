#include<stdio.h>
#include<conio.h>
#define INFINITY 9999
#define LENGTH 5

void dijkstra(int Graph[LENGTH][LENGTH], int startnode, int endnode);

int main(){

	int start, end;
	int Graph[LENGTH][LENGTH] = {
		{0, 0, 1, 0, 10},
		{0, 0, 2, 3, 0},
		{1, 2, 0, 0, 0},
		{0, 3, 0, 0, 1},
		{10, 0, 0, 1, 0}
	};
	printf("\nEnter the starting node: ");
	scanf("%d", &start);
	if (start >= LENGTH || start<0) {
		printf("\n\There is no such vertex!!!\n");
		return 0;
	}
	printf("\nEnter the end node: ");
	scanf("%d", &end);
	if(end >= LENGTH || end<0) {
		printf("\n\There is no such vertex!!\n");
		return 0;
	}
	dijkstra(Graph, start, end);
	return 0;
}

void dijkstra(int Graph[LENGTH][LENGTH], int startnode, int endnode) {

	int cost[LENGTH][LENGTH], distance[LENGTH], pred[LENGTH], path[LENGTH];
	int visited[LENGTH], count, mindistance, nextnode, i, j;
	int n = LENGTH;

	//pred[] stores the predecessor of each node
	//count gives the number of nodes visited
	
	// creates the matrix of weights between vertices
	// if vertices are not connected sets the weight to be infinity
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (Graph[i][j] == 0) {
				cost[i][j] = INFINITY;
			}
			else {
				cost[i][j] = Graph[i][j];
			}
		}
	}

	for (i = 0; i < n; i++){
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;

	while (count < n - 1){
		mindistance = INFINITY;
		//nextnode gives the node at minimum distance
		for (i = 0; i < n; i++) {
			if (distance[i] < mindistance && !visited[i]){
				mindistance = distance[i];
				nextnode = i;
			}
		}

		//check if a better path exists through nextnode			
		visited[nextnode] = 1;
		for (i = 0; i < n; i++) {
			if (!visited[i]) {
				if (mindistance + cost[nextnode][i] < distance[i]){
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
			}
		}
		count++;
	}
	
	printf("\nDistance to node %d = %d", endnode, distance[endnode]);
	printf("\nPath: %d", startnode);
	int k = 0;
	j = endnode;
	do{
		path[k] = j;
		j = pred[j];
		k += 1;
	} while (j != startnode);

	for (; k>0; k--) {		
		printf(" -> %d", path[k-1]);
	}
}