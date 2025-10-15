#include <stdio.h>
#define STACK_SZ 20 
int stack[STACK_SZ];
int top = -1;

int isFull(void) {
	return (top == STACK_SZ - 1);
}

int isEmpty() {
	return (top == -1);
}

void push(int _v) {
	if (isFull()) {
		printf("stack�� ���� ã���ϴ�.");
		return;
	}
	top++;
	stack[top] = _v;
	return;
}

int pop() {
	if (isEmpty()) {
		printf("stack�� ����ֽ��ϴ�.");
		return -999;
    }
	int result = 0;
	result = stack[top];
	top--;
	return result;
}



int main(void) {

	int input = 0;
	while (1) {
		scanf_s("%d", &input);

		if (input == 0) {
			break;
		}

		else if (input == -1) {
			pop();
		}

		else {
			push(input);
		}
	}

	// 0�� �Էµ� ���
	if (top == -1) {
		printf("-999");
	}

	else {
		printf("%d", stack[top] + stack[0]);
	}

	return 0;
}