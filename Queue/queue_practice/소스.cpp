// queue �����ϱ�.

#include <stdio.h>

#define Q_SZ 8

int queue[Q_SZ];
int front = 0;
int rear = 0;

int isFull() {
	return ((rear + 1) % Q_SZ == front);
}


int isEmpty() {
	return (rear == front);
}

void enqueue(int _v) {
	if (isFull()) {
		printf("�� ã���ϴ�.");
		return;
	}

	queue[rear] = _v;
	rear = (rear + 1) % Q_SZ;
	return;
}

int dequeue(void) {
	if (isEmpty()) {
		printf("�� ������ϴ�.");
		return -999;
	}

	int result = queue[front];
	front = (front + 1) % Q_SZ;
	return result;
}

void add_to_front(int _v) {
	if (isFull()) {
		printf("��ҷ�");
		return;
	}

	front = (((front - 1) + Q_SZ) % Q_SZ);
	queue[front] = _v;
}


int del_to_rear() {
	if (isEmpty()) {
		printf("�����");
		return -999;
	}

	rear = (((rear - 1) + Q_SZ) % Q_SZ);
	int result = queue[rear];
	return result;
}



int main(void) {

	enqueue(10);
	enqueue(20);
	enqueue(30);
	enqueue(40);
	enqueue(50);
	add_to_front(90);
	while (!isEmpty()) {
		printf("%d\n", del_to_rear());
	}
	return 0;
}










