#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>

#define NAMESIZE 32
#define BUFFSIZE 255

typedef struct Person
{
	char name[NAMESIZE];
	char surname[NAMESIZE];
	int birthYear;
	struct Person* next;
}Person;

void printList(Person*);
void deleteElement(Person*);
void freeMemory(Person*);
void sortBySurname(Person*);
void insertNode(Person* head, Person* newNode);

int addAtStart(Person*);
int addAtEnd(Person*);
int addAfterElement(Person*);
int addBeforeElement(Person*);
int writeToFile(Person*);
int readListFromFile(Person*);

char* getFileName();

Person* addPersonData();
Person* findElementBySurname(Person*);

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
		"Press 6 to add element after particular element\n"
		"Press 7 to add element before particular element\n"
		"Press 8 to sort list by surnames\n"
		"Press 9 to write list to file\n"
		"Press 10 to read list from file\n"
		"Press -1 to exit program\n"
	);

	while (input != -1) {
		printf("\nSelection :\t");
		scanf(" %s", inputStr);
		printf("\n");
		input = atoi(inputStr);

		switch (input)
		{
		case 1:
			if (addAtStart(&headPerson) == -1) return -1;
			break;
		case 2:
			printList(&headPerson);
			break;
		case 3:
			if (addAtEnd(&headPerson) == -1) return -1;
			break;
		case 4:
			foundElem_Adr = findElementBySurname(&headPerson);
			break;
		case 5:
			deleteElement(&headPerson);
			break;
		case 6:
			if (addAfterElement(&headPerson) == -1) return -1;
			break;
		case 7:
			if (addBeforeElement(&headPerson) == -1) return -1;
			break;
		case 8:
			sortBySurname(&headPerson);
			printf(" *** SORTED LIST *** \n");
			printList(&headPerson);
			break;
		case 9:
			if (writeToFile(&headPerson) == -1) return -1;
			break;
		case 10:
			if (readListFromFile(&headPerson) == -1) return -1;
			break;
		case -1:
			printf("Exiting menu selection...\nExiting program...\n");
			break;
		default:
			printf("INVALID INPUT!\nPlease pick options from 1 - 10 or pick -1 to exit menu selection!\n");
			break;
		}
	}

	freeMemory(headPerson.next);
	return 0;
}

int addAtStart(Person* head) {

	Person* newPerson = NULL;
	newPerson = addPersonData();

	if (newPerson == NULL) return -1;

	insertNode(head, newPerson);
	printf("Adding new element at the beginning of the list...\n");

	return 0;
}

Person* addPersonData() {
	Person* newPerson = NULL;
	newPerson = (Person*)malloc(sizeof(Person));

	if (newPerson == NULL) {
		printf("\nMemory allocation failed\nExiting program...\n");
		return NULL;
	}

	printf("Name / Surname / Birth year\t");
	scanf(" %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);

	return newPerson;
}


int addAtEnd(Person* head) {

	Person* newPerson = NULL;
	newPerson = addPersonData();

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

Person* findElementBySurname(Person* head) {
	char surname[NAMESIZE] = { '\0' };
	int counter = 0;

	printf("\nEnter surname :\t");
	scanf(" %s", surname);

	while (head->next != NULL) {

		head = head->next;
		counter++;

		if (_strcmpi(surname, head->surname) == 0) {
			printf("\nSurname %s found at %d index of list\nAdress: %p\n", surname, counter, &head);
			return head;
		}
	}

	printf("\nSurname %s NOT found!\n", surname);
	return NULL;
}

void deleteElement(Person* head) {
	char name[NAMESIZE] = { '\0' };
	char surname[NAMESIZE] = { '\0' };
	Person* temp = NULL;

	printf("\nEnter name & surname of person you wish to delete from the list\nUse format {Name} {Surname}\t");
	scanf(" %s %s", name, surname);

	while (head->next != NULL) {
		//pointing on previous
		temp = head;
		//pointing on current
		head = head->next;

		if (_strcmpi(name, head->name) == 0 && _strcmpi(surname, head->surname) == 0) {
			temp->next = head->next;
			free(head);

			return;
		}
	}

	printf("\nCannot delete person that is not in the list!\nExiting menu selection...\n");
	return;
}

int addAfterElement(Person* head) {
	char name[NAMESIZE] = { '\0' };
	char surname[NAMESIZE] = { '\0' };
	int position = 0; // variable for testing purposes

	printf("ADD NEW PERSON DATA:\n");

	Person* newPerson = NULL;
	newPerson = addPersonData();

	if (newPerson == NULL) return -1;

	printf("\n ***** PRINTING LIST OF AVAILABLE PEOPLE *****\n");
	printList(head);
	printf("\nTo add new person after an element please type name & surname of person you wish to add it after\n\nUse format {Name} {Surname}\t");
	scanf(" %s %s", name, surname);

	while (head->next != NULL) {

		head = head->next;
		position++;

		if (_strcmpi(head->name, name) == 0 && _strcmpi(head->surname, surname) == 0) {
			printf("Position: %d\n", position);
			// we found person we wish to insert it after and we set that person's next pointer to point on new person
			insertNode(head, newPerson);
			return 0;
		}
	}

	printf("\nCannot add after person that is not in the list!\nExiting menu selection...\n");
	return 0;
}

int addBeforeElement(Person* head) {
	char name[NAMESIZE] = { '\0' };
	char surname[NAMESIZE] = { '\0' };

	printf("ADD NEW PERSON DATA:\n");

	Person* newPerson = NULL;
	newPerson = addPersonData();

	if (newPerson == NULL) return -1;

	printf("\n ***** PRINTING LIST OF AVAILABLE PEOPLE *****\n");
	printList(head);
	printf("\nTo add new person before an element please type name & surname of person you wish to add it before.\n\nUse format {Name} {Surname}\t");
	scanf(" %s %s", name, surname);

	while (head->next != NULL) {

		if (_strcmpi(head->next->name, name) == 0 && _strcmpi(head->next->surname, surname) == 0) {
			insertNode(head, newPerson);
			return 0;
		}
		head = head->next;
	}

	printf("\nCannot add before person that is not in the list!\nExiting menu selection...\n");
	return 0;
}

void sortBySurname(Person* head) {

	if (head->next == NULL) {
		printf("List is empty!\n");
		return;
	}
	else {

		Person* current = NULL;
		Person* previous = NULL;
		Person* temp = NULL;
		Person* end = NULL;

		while (head->next != end) {

			previous = head;
			current = head->next;

			while (current->next != end) {

				if (_strcmpi(current->surname, current->next->surname) > 0) {

					temp = current->next;
					previous->next = temp;
					current->next = temp->next;
					temp->next = current;
					current = temp;
				}

				previous = current;
				current = current->next;
			}
			end = current;
		}
	}
}

int writeToFile(Person* head) {
	char fileName[NAMESIZE] = { '\0' };
	FILE* fp = NULL;

	printf("\nType in the name of file you wish to create! Use format name_of_file.txt\t");
	scanf(" %s", fileName);
	fp = fopen(fileName, "w");

	if (fp == NULL) {
		printf("\nERROR opening file! Exiting program...\n");
		return -1;
	}
	else {
		while (head->next != NULL) {
			head = head->next;
			fprintf(fp, "%s %s %d\n", head->name, head->surname, head->birthYear);
		}
	}

	fclose(fp);
	return 0;
}

int readListFromFile(Person* head) {
	char buffer[BUFFSIZE] = { '\0' };
	FILE* fp = NULL;

	fp = fopen(getFileName(), "r");

	if (fp == NULL) {
		printf("\nError opening file!\nExiting program!\n");
		return -1;
	}
	else {
		printf("\nFile opened successfully\n\n");

		while (!feof(fp)) {
			Person* newPerson = NULL;
			newPerson = (Person*)malloc(sizeof(Person));
			if (newPerson == NULL) return -1;

			//reads to buffer
			fgets(buffer, BUFFSIZE, fp);
			//greater than 1 because there can be an empty line between
			if (strlen(buffer) > 1) {
				// sscanf reads formatted input from string and stores to location specified
				sscanf(buffer, " %s %s %d", newPerson->name, newPerson->surname, &newPerson->birthYear);
				insertNode(head, newPerson);
			}
			strcpy(buffer, "\0");
		}
	}
	printList(head);
	fclose(fp);
	return 0;
}

char* getFileName() {
	static char fileName[NAMESIZE] = { '\0' };

	printf("Enter file name! \n(file name is students.txt /winkwink)\n\nPlease use format: file_name.txt\t");
	scanf(" %s", fileName);

	return fileName;
}

void insertNode(Person* head, Person* newNode) {
	newNode->next = head->next;
	head->next = newNode;
}

void freeMemory(Person* head) {
	Person* tempPerson = head;

	while (head != NULL) {
		head = head->next;
		free(tempPerson);
		tempPerson = head;
	}
}