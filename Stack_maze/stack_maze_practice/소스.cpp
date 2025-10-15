#include <stdio.h>

#define MAZE_SZ 6
#define STACK_SZ (MAZE_SZ*MAZE_SZ)

typedef struct {
	int r; // 행
	int c; // 열
}LOC;

LOC stack[STACK_SZ];
int top = -1;

char maze[MAZE_SZ][MAZE_SZ] =
{
   {'1','1','1','1','1','1',},
   {'e','0','1','0','0','x',},   // e : entrance
   {'1','0','0','0','1','1',},
   {'1','0','1','0','1','1',},
   {'1','0','1','0','0','1',},   // x : exit
   {'1','1','1','1','1','1',}
};


int isFull() {
	return ((top == STACK_SZ - 1));
}

int isEmpty() {
	return (top == -1);
}

void push(int _r, int _c) {

	if (isFull()) {
		return;
	}

	if ((_r < 0) || (_c < 0)) {
		return;
	}

	if ((maze[_r][_c] == '1') || (maze[_r][_c] == '.')) {
		return;
	}

	top++;
	stack[top] = { _r,_c };
	return;
}

LOC pop(void) {

	if (isEmpty()) {
		return { -1,-1 };
	}

	LOC result = stack[top];
	top--;
	return result;
}


void printfMaze(void) {
	for (int i = 0; i < MAZE_SZ; i++) {
		for (int j= 0; j < MAZE_SZ; j++) {
			printf("%c ", maze[i][j]);
		}
		printf("\n");
    }
}

int main(void) {

	LOC cur = { 1,0 };

	while (1) {

		if (maze[cur.r][cur.c] == 'x') {
			printf("도착했습니다.");
			return 0;
		}

		maze[cur.r][cur.c] = '.';
		printfMaze();
		printf("\n");
		push(cur.r - 1, cur.c);
		push(cur.r + 1, cur.c);
		push(cur.r, cur.c - 1);
		push(cur.r, cur.c + 1);

		cur = pop();

		if ((cur.r == -1) && (cur.c == -1)) {
			printf("길이 없습니다.");
			return -1;
		}
	}





	return 0;
}








