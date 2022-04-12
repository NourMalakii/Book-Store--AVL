/*
Student: Nour Malaki => 1181275
Instructor: Dr.Radi Jarrar
This is a simple application that reads an unspecified number of strings from a file "string.txt"
& then sort these strings by radix sort technique
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 16 //Maximum length for each string in line => 15

typedef struct listNode {
	char *word;
	int length;
	struct listNode *next;
} Node;

Node *head = NULL;;
Node *sortedHead = NULL;
FILE *fptr;
int max = 0;

Node* createNode(char *word, int length) { // node creation
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode -> word = strdup(word);
	newNode -> length = length;
	newNode -> next = NULL;
	return newNode;
}

void toLowerCase(){  //convert the inputs to lowercase.
char ch;
int ret = fscanf(fptr, "%c", &ch);
ch = tolower(ch);
}

int insert(Node **head, char *word, int length) { // node insertion functionality
	if (*head == NULL) {
		*head = createNode(word, length);
		return (*head)->length;
	}
	else {
		Node *temp = *head;
		while(temp->next != NULL)
            temp = temp->next;
		temp->next = createNode(word, length);
		return temp->length;
	}
}

void menu(){ // display menu

    printf("\n\n*******************************************************************");

		printf("\nPress [1] to read the input file \n");
		printf("\nPress [2] to print the strings before sorting \n");
		printf("\nPress [3] to sort the strings \n");
		printf("\nPress [4] to print the sorted strings \n");
		printf("\nPress [5] to Exit \n\n");
		printf("Enter your choice: ");


}

void printStrings(Node *head){ // This is used for printing strings in the input file
	Node *temp = head;
	while(temp != NULL) {
		printf("%s\n", temp->word);
		temp = temp->next;
	}
}

Node *sorting(Node *head, int pos) { // sorting technique
	Node **temp = (Node **) malloc(256 * sizeof(Node *));
for(int i = 0; i < 256; i++){
        temp[i] = NULL;
    }

	while(head != NULL) {
		insert(&temp[pos >= head->length ? 0 : head->word[pos]], head->word, head->length);
		head = head->next;
	}



	Node *newHead = NULL;
	int i;
	for(i = 0 ; i < 256 ; ++i) {
		if(temp[i] != NULL) {
			while(temp[i] != NULL) {
				insert(&newHead, temp[i]->word, temp[i]->length);
				temp[i] = temp[i]->next;
			}
		}
	}

	return newHead;
}

void LengthOfStrings(){
    // make sure that strings in file should be no more than 15 character

    char *in = (char *) malloc(sizeof(char) * MAX);
    int i = 0;
    char*word;

    while(1) {
       char ch;
       int ret = fscanf(fptr, "%c", &ch);
                ch = tolower(ch);
        if(ret == -1)
        {
            break;
        }
            if(ch == '\n' && i == 0)
                continue;

            else if(ch == '\n') {
                in[i] = '\0';
                int len = insert(&head, in, strlen(in));
                max = (len > max) ? len : max;

                i = 0;
            }
        else in[i++] = ch;

    }
}


 void radix_sort(char* a[]) { 
   const int length;
   int ALPHABET_LENGTH = 16;
   char id = 0;
   int PLATE_LENGTH = 16;
   char** aux = (char**)malloc(length * PLATE_LENGTH);
  for(int d = PLATE_LENGTH-1; d >= 0; d--) {

      int* count = (int*)calloc(ALPHABET_LENGTH+1, sizeof(int));
      // whether character or digit
    id = a[0][d] >= '0' && a[0][d] <= '9' ? '0' : 'A';
      // Compute frequency counts
      for(int i = 0; i < length; i++)
         count[a[i][d] - id + 1]++;
      // transform counts to indices
      for(int r = 0; r < ALPHABET_LENGTH; r++)
        count[r+1] += count[r];
      // distribute to temp array
      for(int i = 0; i < length; i++)
          aux[count[(a[i][d] - id)]++] = a[i];
      // copy back to original array
      for(int i = 0; i < length; i++)
        a[i] = aux[i];

      free(count);
   }
   free(aux);
}


Node *radixSort(Node *b, int max) {
	for (int digit = max; digit > 0; digit--)
        b = sorting(b, digit - 1);
	return b;
}

int main() {

    printf("\n\n*******************************************************************\n");
    printf("\nplease press [1] to read the file before trying other choices\n");
	do {

       menu();

		int ch;
		scanf("%d", &ch);

    printf("\n\n*******************************************************************");

		if(ch == 5) {

            printf("\nQuitting the program..");
            break;
		}

		switch (ch)
		{
			case 1:
				fptr = fopen("string.txt", "r"); //read the file case
				if(fptr == NULL) {
					printf("Error!\n");
					exit(1);
				}

                LengthOfStrings();

				printf("\nThe file was read successfully!");

				break;

			case 2:
				if(head == NULL) printf("\n\nStrings have not been read yet!\n");
				else {
					printf("\n\nStrings before sorting are :\n\n");
					printStrings(head);
				}
				break;

			case 3:
			   // toLowerCase();
				if(head != NULL)
                    sortedHead = radixSort(head, max);
				printf("\n\nSorting was done successfully ! ");
				break;

			case 4:

				if(sortedHead == NULL) printf("\n\nStrings not sorted yet, please press [3] first!\n");
				else {
					printf("\nSorted strings are :\n\n");
					printStrings(sortedHead);
				}
				break;

			default:
				printf("\n\nWrong choice!\n");
		}
	} while(1);
    return 0;
}



