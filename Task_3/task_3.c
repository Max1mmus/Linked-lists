#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>

typedef struct Node
{
	int val;
	struct Node* next;

}Stack, Queue, List, Node;

// Stack will push & pop items from start;
// Queue will push items to end and pop from start;

int pushStart(Stack*);
int pushEnd(Queue* head);
int popStart(List* head);

Node* createNode();
Node* freeMemory(List* head);

void insertData(List* node);
void insertNode(List* head, List* newNode);
void getListSize(List* head);

int generateRandNum(int min, int max);
int isEmpty(List* head);
int printList(List* head);

int main() {
	int selection = 0;

	//initializing random seed
	srand((unsigned int)time(NULL));

	Stack Stack1 = { 0, NULL };
	Queue Queue1 = { 0, NULL };

	printf(
		"\nMENU:\n"
		"***** STACK MANIPULATION *****\n"
		"Press 1 to push\n"
		"Press 2 to pop\n"
		"Press 3 to get size of stack\n"
		"Press 4 to print stack\n"
		"Press 5 to clear whole stack\n"

		"\n***** QUEUE MANIPULATION *****\n"
		"Press 6 to enqueue\n"
		"Press 7 to dequeue\n"
		"Press 8 to get size of queue\n"
		"Press 9 to print queue\n"
		"Press 10 to clear whole queue\n"

		"\nPress -1 to exit program\n"
	);

	while (selection != -1) {
		printf("\nSelection :\t");
		if (scanf(" %d", &selection) != 1) {
			printf("Error!\tSelection must contain only numbers\n");
			while ((selection = getchar()) != '\n' && selection != EOF) {} // Clear input buffer
			continue;
		}

		switch (selection)
		{
		case 1: // Push on stack
			if (pushStart(&Stack1) == -1) {
				freeMemory(&Stack1);
				freeMemory(&Queue1);
				return -1;
			}
			break;
		case 2: // Pop from stack
			if (popStart(&Stack1) == -1) printf("Stack is empty!\n");
			break;
		case 3: // Get size of stack
			printf("\nNumber of elements in stack:\t");
			getListSize(&Stack1);
			break;
		case 4: // Is stack empty
			if (printList(&Stack1) == -1) printf("Stack is empty!\n");
			break;
		case 5: // Clear stack
			Stack1.next = freeMemory(Stack1.next);
			break;
		case 6: // Push on queue
			if (pushEnd(&Queue1) == -1) {
				freeMemory(&Stack1);
				freeMemory(&Queue1);
				return -1;
			}
			break;
		case 7: // Pop from queue
			if (popStart(&Queue1) == -1) printf("Queue is empty!\n");
			break;
		case 8: // Get size of queue
			printf("\nNumber of elements in queue:\t");
			getListSize(&Queue1);
			break;
		case 9: // Is queue empty
			if (printList(&Queue1) == -1) printf("Queue is empty!\n");
			break;
		case 10: // Clear queue
			Queue1.next = freeMemory(Queue1.next);
			break;
		}
	}

	freeMemory(Queue1.next);
	freeMemory(Stack1.next);

	return 0;
}

int pushStart(Stack* head) {
	Stack* newNode = createNode();
	if (newNode == NULL) return -1;

	insertNode(head, newNode);
	printf("Adding node to stack...\n");
	printf("Node %d added to stack\n", newNode->val);
	return 0;
}

int pushEnd(Queue* head) {
	static Queue* tail = NULL;
	Queue* newNode = NULL;
	newNode = createNode();

	if (newNode == NULL) return -1;

	if (head->next == NULL)
		insertNode(head, newNode);
	else
		insertNode(tail, newNode);

	tail = newNode;

	printf("Adding node to queue...\n");
	printf("Node %d added to queue\n", newNode->val);
	return 0;
}

int popStart(List* head) {
	if (isEmpty(head) == -1) return -1;

	List* temp = head;

	head = head->next;
	temp->next = head->next;

	free(head);

	return 0;
}

Node* createNode() {
	Stack* newNode = NULL;
	newNode = (Node*)malloc(sizeof(Node));

	if (newNode == NULL) return NULL;

	insertData(newNode);
	return newNode;
}

void insertNode(List* head, List* newNode) {
	newNode->next = head->next;
	head->next = newNode;
}

int generateRandNum(int min, int max) {
	return rand() % (max - min + 1) + min;
}

void insertData(List* node) {
	node->val = generateRandNum(10, 100);
}

int isEmpty(List* head) {
	if (head->next == NULL) {
		return -1;
	}
}

void getListSize(List* head) {
	int size = 0;

	while (head->next != NULL) {
		head = head->next;
		size++;
	}

	printf("%d\n", size);
}

int printList(List* head) {
	if (isEmpty(head) == -1) return -1;
	printf("Printing list... \n");

	while (head->next != NULL) {
		head = head->next;
		printf("%d \n", head->val);
	}

	return 0;
}


Node* freeMemory(List* head) {
	Node* temp = head;

	while (head != NULL) {
		head = head->next;
		free(temp);
		temp = head;
	}

	return temp;
}
