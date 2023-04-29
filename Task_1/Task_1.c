#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define NAMESIZE 32

typedef struct Person
{
	char name[NAMESIZE];
	char surname[NAMESIZE];
	int birthYear;
	struct Person* next;
}Person;

void addAtStart(Person*, Person*);
void addAtEnd(Person*, Person*);
void printList(Person*);
void deletePerson(Person*);
void freeMemory(Person*);
void insertNode(Person*, Person*);

Person* getPersonDataFromUser();
Person* findPersonBySurname(Person*);

int main() {
	char inputStr[NAMESIZE] = { '\0' };
	int input = 0;

	Person* foundElem_Adr = NULL;
	Person headPerson = { '\0' };

	headPerson.next = NULL;

	printf(
		"\nMENU:\n"
		"Press 1 to dinamically add an element at the beginning of your list\n"
		"Press 2 to print the list\n"
		"Press 3 to dinamically add new element at the end of your list\n"
		"Press 4 to find an element by it's surname\n"
		"Press 5 to delete a particular element from the list\n"
		"Press -1 to exit program\n"
	);

	while (input != -1) {
		printf("\nSelection :\t");
		scanf(" %s", inputStr);
		printf("\n");
		input = atoi(inputStr);

		switch (input) {
		case 1: {
			Person* newPerson = getPersonDataFromUser();
			if (newPerson == NULL) return -1;
			addAtStart(&headPerson, newPerson);
			break;
		}
		case 2:
			printList(&headPerson);
			break;
		case 3: {
			Person* newPerson = getPersonDataFromUser();
			if (newPerson == NULL) return -1;
			addAtEnd(&headPerson, newPerson);
			break;
		}
		case 4: {
			foundElem_Adr = findPersonBySurname(&headPerson);
			break;
		}
		case 5: {
			deletePerson(&headPerson);
			break;
		}
		case -1:
			printf("Exiting menu selection...\nExiting program...\n");
			break;
		default:
			printf("INVALID INPUT!\nPlease pick options from 1 - 5 or pick -1 to exit menu selection!\n");
			break;
		}
	}

	freeMemory(headPerson.next);
	return 0;
}

void addAtStart(Person* head, Person* newPerson) {
	insertNode(head, newPerson);
	printf("Adding new element at the beginning of the list...\n");
}

Person* getPersonDataFromUser() {

	Person* newPerson = (Person*)malloc(sizeof(Person));
	if (newPerson == NULL) {
		printf("Memory allocation failed\nExiting program...\n");
		return NULL;
	}

	printf("Name / Surname / Birth year\t");
	scanf(" %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

	return newPerson;
}

void addAtEnd(Person* head, Person* newPerson) {
	// Find last person
	while (head->next != NULL) {
		head = head->next;
	}

	insertNode(head, newPerson);
	printf("Adding new element at the end of the list...\n");

	return 0;
}

void printList(Person* head) {

	if (head->next == NULL) {
		printf("\nList is empty\n");
		return;
	}

	while (head->next != NULL) {
		head = head->next;
		printf("\nName: %s\t", head->name);
		printf("\nSurname: %s\t", head->surname);
		printf("\nBirth year: %d\t", head->birthYear);
		printf("\n");
	}
}

Person* findPersonBySurname(Person* head) {
	char surname[NAMESIZE] = { '\0' };
	printf("Enter surname of the person you are look for:\t");
	scanf(" %s", surname);
	int counter = 0;

	while (head->next != NULL) {

		head = head->next;
		counter++;

		if (_strcmpi(surname, head->surname) == 0) {
			printf("\nSurname %s found at index %d of list\nAdress: %p\n", surname, counter, &head);
			return head;
		}
	}

	printf("\nSurname %s NOT found!\n", surname);
	return NULL;
}

void deletePerson(Person* head) {
	char name[NAMESIZE] = { '\0' };
	char surname[NAMESIZE] = { '\0' };

	printf("Enter the name and surname of the person you wish to delete:\t");
	scanf(" %s %s", name, surname);

	Person* temp = NULL;

	while (head->next != NULL) {
		//pointing on previous
		temp = head;
		//pointing on current
		head = head->next;

		if (_strcmpi(name, head->name) == 0 && _strcmpi(surname, head->surname) == 0) {
			temp->next = head->next;
			free(head);
			printf("Deleting person from list...\n");
			return;
		}
	}

	printf("\nCannot delete person that is not in the list!\nExiting menu selection...\n");
	return;
}

void insertNode(Person* previouseNode, Person* newNode) {
	newNode->next = previouseNode->next;
	previouseNode->next = newNode;
}

void freeMemory(Person* head) {
	Person* tempPerson = head;

	while (head != NULL) {
		head = head->next;
		free(tempPerson);
		tempPerson = head;
	}
}