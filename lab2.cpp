#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>

using namespace std;

struct Tree {
	int data;
	Tree *left, *right;
};

void show(Tree *&root)              
{
	if (root != NULL){
		show(root->left); 
		cout << root->data << " ";
		show(root->right);		              
	}
}

void addTree(int newData, Tree* &root) {
	if (root == NULL) {
		root = new Tree;
		root->data = newData;
		root->left = root->right = NULL;
	}
	if (newData < root->data) {
		if (root->left != NULL) {
			addTree(newData, root->left);
		}
		else {
			root->left = new Tree;
			root->left->left = root->left->right = NULL;
			root->left->data = newData;
		}
	}
	else if (newData > root->data) {
		if (root->right != NULL) {
			addTree(newData, root->right);
		}
		else {
			root->right = new Tree;
			root->right->left = root->right->right = NULL;
			root->right->data = newData;
		}
	}
}

int getMaxDepth(Tree* tree, int depth) {
	if (tree == NULL) {
		return depth;
	}
	if (getMaxDepth(tree->left, depth + 1) > getMaxDepth(tree->right, depth + 1)) {
		return getMaxDepth(tree->left, depth + 1);
	}
	else {
		return  getMaxDepth(tree->right, depth + 1);
	}
}

void showWay(int number, Tree *&root) {
	if (root == NULL) {
		cout << "\n\nPardon, '"<<number<<"' is not in the tree\n";
		return;
	}
	if (root->data == number) {
		cout << " there is " << number<<"\n";
		return;
	}
	else if (number < root->data) {
		cout << " left from "<<root->data;
		showWay(number, root->left);
	}
	else {
		cout << " right from " << root->data;
		showWay(number, root->right);
	}
}

void deleteMax(Tree *&root) {
	if (root->right == NULL) {
		root->left = NULL;
		root==NULL;
		return;
	}
	Tree *ghostRoot = root;
	while (ghostRoot->right->right != NULL) {
		ghostRoot = ghostRoot->right;
	}
	ghostRoot->right->left = NULL;
	ghostRoot->right = NULL;
	delete ghostRoot->right;
}

int main() {
	Tree *root = NULL;
	srand(time(0));

	cout <<"Numbers for the tree: " ;
	for (int i = 0; i < 15; i++) {
		int data = rand() % 10 + 1;
		cout << data << " ";
		addTree(data, root);
	} 
	cout << "\nPrinted tree: ";
	show(root);

	int number = 3;
	cout << "\n\nSearching for the element '"<<number<<"':\n";
	showWay(number, root);
	
	int depth = getMaxDepth(root, 0);
	cout << "\nDepth is "<< depth;

	deleteMax(root);
	cout << "\n\nThe tree after deleting the max element is: ";
	show(root);
	return 0;
}