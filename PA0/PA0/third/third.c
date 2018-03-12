#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
typedef struct node{
    int data;
    struct node* next;
} node;
 
node *hashtable[10000];
 
int main(int argc, char ** argv) {
    if(argc != 2) {
        printf("error\n");
        return 0;
    }
    char buffer[999];
    FILE *fp;
    fp = fopen(argv[1],"r");
    if(fp) {
        while (fscanf(fp, "%s", buffer)!=EOF) {
            if(strcmp(buffer, "i") == 0) {
                fscanf(fp, "%s", buffer);
		int value = atoi(buffer);
                int bucketNumber = value%10000;
		  if (bucketNumber < 0){
		      bucketNumber = bucketNumber*-1;
		  }
                node* toInsert = hashtable[bucketNumber];
                if(hashtable[bucketNumber] == NULL) {
                    node*temp = (node*)malloc(sizeof(node));
                    temp-> data = value;
                    temp-> next = NULL;
                    hashtable[bucketNumber] = temp;
                    printf("inserted\n");
                }
                else {
                    int flag = 0;
                    toInsert = hashtable[bucketNumber];
                    if(value == toInsert->data) {
                        printf("duplicate\n");
                    }
                    else {
                        while(toInsert->next != NULL && flag == 0) {
                            if(value == toInsert->data){
			      printf("duplicate\n");
			      flag = 1;
			    }
                            toInsert = toInsert->next;
                        }
                        if(flag == 0) {
                            node* next = (node*)malloc(sizeof(node));
                            next->data = value;
                            next->next = NULL;
                            toInsert->next = next;
			    printf("inserted\n");
                        }
                    }
                }
            }
            else {
                fscanf(fp, "%s", buffer);
                int value = atoi(buffer);
		int bucketNumber = value % 10000;
		if (bucketNumber < 0){
		    bucketNumber = bucketNumber * -1;
		}
                node*toSearch = hashtable[bucketNumber];
                int flag = 0;
                while(toSearch != NULL) {
                    if(value == toSearch->data) {
                        flag = 1;
                        printf("present\n");
                        break;
                    }
                    toSearch = toSearch->next;
                }
                if(flag == 0) {
                    printf("absent\n");
                }
            }
        }
    }
    else {
        puts("error\n");
        return 1;
    }
    int i = 0;
    for(; i < 10000; i++) {
        node* toDelete = hashtable[i];
        while(toDelete) {
            node* pointer = toDelete->next;
            free(toDelete);
            toDelete = pointer;
        }
    }
    return 0;
}