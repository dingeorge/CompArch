#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct blah{
	int data;
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

if (*root == NULL){
	*root = newNode;
	(*root)->left = NULL;
	(*root)->right = NULL;
	printf("inserted %d\n", counter);
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
			printf("inserted %d\n", counter);
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
			printf("inserted %d\n", counter);
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
	temp->right = newNode;
	printf("inserted %d\n",counter);
	return;
}
else if (value < temp->data){
	counter++;
	temp->left = newNode;
	printf("inserted %d\n",counter);
	return;
}
printf("duplicate %d\n",counter);
return;		
}

void searchTree(treeNode ** head, int value){
treeNode * temp = *head;

int counter = 1;

if (value == temp->data){
	printf("present %d\n", counter);
	return;
}

while (temp != NULL){
	if (value > temp->data){
		temp = temp->right;
		counter++;
	}
	else if (value < temp->data){
		temp = temp->left;
		counter++;
	}
	else {
		printf("present %d\n", counter);
		return;
	}
}

printf("absent\n");

return;

}

void del(treeNode ** root, int value){

treeNode * roottemp = *root;
treeNode * temp = *root;

int rootb = 0;
int left = 0;

if ((*root)->data == value){
	rootb = 1;
}
else{

while (roottemp != NULL){
	if (roottemp->data < value){
		temp = roottemp;
		roottemp = roottemp->right;
		left = 0;
	}
	else if (roottemp->data > value){
		temp = roottemp;
		roottemp = roottemp->left;
		left = 1;
	}
	else if (roottemp->data == value){
		break;
	}
}
}
treeNode * tmp;

if (roottemp == NULL){
	printf("fail\n");
	return;
}
else if (roottemp->right == NULL && roottemp->left == NULL){
	if (rootb == 1){
		*root = NULL;
	}
	else{
		if (left == 1){
			temp->left = NULL;
		}
		else{
			temp->right = NULL;
		}
	}
	printf("success\n");
	return;
}
else if (roottemp-> right == NULL && roottemp->left != NULL){
	if (rootb == 1){
		(*root) = (*root)->left;
	}
	else{
		tmp = roottemp->left;
		if (left == 1){
			temp->left = tmp;
		}
		else{
			temp->right = tmp;
		}
	}
	printf("success\n");
	return;
}
else if (roottemp->left == NULL && roottemp-> right != NULL){
	if (rootb == 1){
		(*root) = (*root)->right;
	}
	else{
		tmp = roottemp->right;
		if (left == 1){
			temp->left = tmp;
		}
		else {
			temp->right = tmp;
		}
	}
	printf("success\n");
	return;
}
else if (roottemp->left != NULL && roottemp->right != NULL){
	treeNode * tmp;
	if (rootb == 1){
		treeNode * rRoot = (*root)->right;
		if (rRoot->left == NULL){
			(*root)->data = rRoot->data;
			(*root)->right = (*root)->right->right;
		}
		else{
			while (rRoot->left != NULL){
				tmp = rRoot;
				rRoot = rRoot->left;
			}
			(*root)->data = rRoot->data;
			tmp->left = rRoot->right;
		}
	}
	else{
		treeNode * smallestRight = roottemp->right;
		tmp = smallestRight;
		
		if (smallestRight->left == NULL){
			roottemp->data = smallestRight->data;
			roottemp->right = roottemp->right->right;
		}
		else{
			while (smallestRight->left != NULL){
				tmp = smallestRight;
				smallestRight = smallestRight->left;
			}
			roottemp->data = smallestRight->data;
			tmp->left = smallestRight->right;
	   	}
	}
	printf("success\n");
	return;
}
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
	else if (letter == 'd'){
		if (root == NULL){
			printf("fail\n");
			continue;
		}
		del(&root, number);
	}
	else{
		printf("error\n");
		return 0;
	}
}

return 0;
}

