#include <stdio.h>
#define Q_SZ 10

int queue[Q_SZ];
int front = 0;
int rear = 0;

int isFull() {
	return (((rear + 1) % Q_SZ) == front );
}


int isEmpty() {
	return (front == rear);
}

void enqueue(int _v) {
	if (isFull()) {
		printf("배불러");
		return;
	}

	queue[rear] = _v;
	rear = (rear + 1) % Q_SZ;
}

int dequeue() {
	if (isEmpty()) {
		printf("배고파");
		return -999;
	}

	int result = queue[front];
	front = (front + 1) % Q_SZ;
	return result;
}


int main(void) {
	enqueue(10);
	enqueue(20);
	enqueue(30);
	enqueue(40);

	while (!isEmpty()) {
		printf("%d\n", dequeue());
	}
	return 0;
}











