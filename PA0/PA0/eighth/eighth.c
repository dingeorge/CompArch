#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct blah{
	int data;
	int height;
	struct blah * left;
	struct blah * right;
} treeNode;

void addNodeTree(treeNode ** root, int value){
treeNode *temp = *root;

int counter = 1;

treeNode *newNode = (treeNode*)malloc(sizeof(treeNode));
newNode->data = value;
newNode->left = NULL;
newNode->right = NULL;
newNode->height = counter;

if (*root == NULL){
	*root = newNode;
	(*root)->left = NULL;
	(*root)->right = NULL;
	printf("inserted %d\n",newNode->height);
	return;
}

if ((*root)->data == value){
	printf("duplicate\n");
	return;
}

treeNode *lesser = (*root)->left;
treeNode *greater = (*root)->right;

while(lesser != NULL || greater != NULL){
	if (temp->data == value){
		printf("duplicate\n");
		return;
	}
	if (value <= temp->data){
		if (lesser == NULL){
			counter++;
			temp->left = newNode;
			newNode->height = counter;
			printf("inserted %d\n", newNode->height);
			return;
		}
		temp = temp->left;
		lesser = temp->left;
		greater = temp->right;
		counter++;
	}
	else if (value >= temp->data){
		if (greater == NULL){
			counter++;
			temp->right = newNode;
			newNode->height = counter;
			printf("inserted %d\n",newNode->height);
			return;
		}
		temp = temp->right;
		lesser = temp->left;
		greater = temp->right;
		counter++;
	}
}
if (value > temp->data){
	counter++;
	newNode->height = counter;
	temp->right = newNode;
	printf("inserted %d\n",newNode->height);
	return;
}
else if (value < temp->data){
	counter++;
	newNode->height = counter;
	temp->left = newNode;
	printf("inserted %d\n",newNode->height);
	return;
}
printf("duplicate\n");
return;		
}

void searchTree(treeNode ** head, int value){
treeNode * temp = *head;

if (value == temp->data){
	printf("present %d\n", temp->height);
	return;
}

while (temp != NULL){
	if (value > temp->data){
		temp = temp->right;
	}
	else if (value < temp->data){
		temp = temp->left;
	}
	else {
		printf("present %d\n", temp->height);
		return;
	}
}

printf("absent\n");

return;

}

int main(int argc, char ** argv){

if (argc < 2){
	printf("error\n");
	return 0;
}

FILE * file;

file = fopen(argv[1],"r");

char ibuffer[300];
char numberbuffer[300];

treeNode * root = NULL;

while (fscanf(file,"%s	%s",ibuffer,numberbuffer) != EOF){
	char * letterarr = ibuffer;
	char letter = letterarr[0];
	char * numberarr = numberbuffer;
	int number = atoi(numberarr);

	if (letter == 'i'){
		addNodeTree(&root, number);
	}
	else if(letter == 's'){
		if (root == NULL){
			printf("absent\n");
			continue;
		}
		searchTree(&root, number);
	}
	else{
		printf("error\n");
		return 0;
	}
}

return 0;
}


