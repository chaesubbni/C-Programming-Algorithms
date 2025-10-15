// linked list

#include <stdio.h>
#include <stdlib.h>
struct node {
	int data;
	struct node* next;
};

struct node* head = 0;

void addToSLL(int _v) {
	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->data = _v;
	_new->next = 0;

	if (head == 0) {
		head = _new;
		return;
	}

	struct node* temp = head;
	while (temp->next != 0) {
		temp = temp->next;
	}
	temp->next = _new;
	return;

}

void displaySLL(void) {
	struct node* temp = head;
	while (temp != 0) {
		printf("%d\n", temp->data);
		temp = temp->next;
	}
	return;
}



int countSLL(void) {
	struct node* temp = head;
	int count = 0;
	while (temp != 0) {
		count++;
		temp = temp->next;
	}
	return count;
}


struct node* findSLL(int _v) {
	struct node* temp = head;
	while (temp != 0) {
		if (temp->data == _v) {
			return temp;
		}
		temp = temp->next;
	}
	return temp;
}

void destroySLL(void) {
	struct node* spear = head;
	while (head != 0) {
		head = head->next;
		free(spear);
		spear = head;
	}
	return;
}

void addToFront(int _v) {
	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->data = _v;
	_new->next = 0;

	if (head == 0) {
		head = _new;
		return;
	}

	_new->next = head;
	head = _new;
	return;
}

int delFromFront(void) {
	if (head == 0) {
		return -999;
	}

	struct node* spear = head;
	int res = head->data;
	head = head->next;
	free(spear);
	return res;
}

int delFromLast(void) {
	struct node* spear = head;
	if (head == 0) {
		return -999;
	}

	if (head->next == 0) {
		int res = head->data;
		free(head);
		head = 0;
		return res;
	}
	while (spear->next->next != 0) {
		spear = spear->next;
	}
	int res = spear->next->data;
	free(spear->next);
	spear->next = 0;
	return res;
}

void insertInto(int _v, int _addv) {
	struct node* target = findSLL(_v);
	if (target == 0) {
		return;
	}

	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->data = _addv;
	_new->next = 0;

	_new->next = target->next;
	target->next = _new;
	return;
}

int main(void) {

	addToSLL(10);
	addToSLL(20);
	addToSLL(30);
	addToSLL(40);

	addToFront(90);
	addToFront(80);

	delFromFront();
	

	delFromLast();

	insertInto(20, 99);
	// 90 10 20 99 30

	displaySLL();
}