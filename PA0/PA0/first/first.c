#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct blah{
	int data;
	struct blah * next;
} node;

void addNode(node ** front, int value){

node * LLnode = (node*)malloc(sizeof(node));
LLnode->data = value;

if (*front == NULL){
	*front = LLnode;
	return;
}

if ((*front)->data == value){
	return;
}

if ((*front)->data > value){
	LLnode->next = *front;
	*front = LLnode;
	return;
}

node *ptr = (*front)->next;
node *prev = *front;

while (ptr!=NULL){
	if (ptr->data >= value){
		if (ptr->data == value){
			return;
		}
		else{
			LLnode->next = ptr;
			prev->next = LLnode;
			return;
		}
	}
	prev = ptr;
	ptr = ptr->next;
}

prev->next = LLnode;
LLnode->next = NULL;

return;
}

void deleteNode(node ** front, int value){

node * ptr = (*front)->next;
node * prev = *front;

if ((*front)->data == value){
	if ((*front)->next == NULL){
		*front = NULL;
		return;
	}
	*front = ptr;
	return;
}

while (ptr != NULL){
	if (ptr->data == value){
		if (ptr->next == NULL){
			prev->next = NULL;
			return;
		}
		prev->next = prev->next->next;
		return;
	}
	prev = ptr;
	ptr = ptr->next;
}
return;
}

void output(node ** front){
node * ptr = *front;

while(ptr != NULL){
	printf("%d", ptr->data);
	if (ptr->next != NULL){
		printf("\t");
	}
	ptr = ptr->next;
}
return;
}

int main(int argc, char ** argv){
	
FILE * file;

char letterbuffer[300];
char numberbuffer[300];

node *front = NULL;

file = fopen(argv[1], "r");
if (file == NULL){
	printf("error");
	return 0;
}

if (file == NULL){
	printf("error");
	return 0;
}

while (fscanf(file,"%s	%s",letterbuffer,numberbuffer) != EOF){
	
	char * letterarr = letterbuffer;
	char letter = letterarr[0];
	char * numberchar = numberbuffer;
	int number = atoi(numberchar);

	if (letter == 'i'){
		addNode(&front, number);
	}
	else if (letter == 'd'){
		if (front == NULL){
			continue;
		}	
		deleteNode(&front, number);
	}
	else{
		printf("error\n");
		return 0;
	}
}

node * ptr = front;

int nodeCount = 0;

while (ptr!=NULL){
	nodeCount++;
	ptr = ptr->next;
}

printf("%d\n",nodeCount);
output(&front);
printf("\n");

node * tmp;
while (front !=NULL){
	tmp = front;
	front = front->next;
	free(tmp);
}

return 0;
}

