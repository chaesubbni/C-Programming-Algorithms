#include <stdio.h>
#include <stdlib.h>
// BST의 노드를 표현

#define stack_SZ 10
#define que_SZ 10


struct node {
	int data;
	struct node* left;
	struct node* right;
};
// root node를 가리키는 포인터
struct node* root = 0;
struct node* stack[stack_SZ];
int top = -1;


struct combo {
	struct node* parent;
	struct node* me;
};

struct node* que[que_SZ];
int front = 0;
int rear = 0;
void push(struct node* _cur) {
	if (top == stack_SZ - 1) {
		return;  // stack full
	}

	top++;
	stack[top] = _cur;
	return;
}

struct node* pop(void) {
	if (top == -1) {
		return 0; // 비어있다.
	}

	struct node* temp = stack[top];
	top--;
	return temp;
}

void enque(struct node* _cur) {
	if ((rear + 1) % que_SZ == front) {
		return;
	}
	que[rear] = _cur;
	rear = (rear + 1) % que_SZ;
	return;
}

struct node* deque(void) {
	if (rear == front) {
		return 0; // null
	}

	struct node* result = que[front];
	front = (front + 1) % que_SZ;
	return result;
}

int get_node_count(struct node* _cur) {
	if (_cur == 0) {
		return 0;
	}
	return 1 + get_node_count(_cur->left) + get_node_count(_cur->right);
}

// p. 단말노드 갯수 구하기. -> 자식이 없는 노드 갯수만 구하기. 즉, 맨 마지막 level 갯수랑 비슷.

int danmalnode(struct node* _cur) {

	if (_cur == 0) {
		return 0;
	}
	else if (_cur->left == 0 && _cur->right == 0) {
		return 1;
	}

	return danmalnode(_cur->left) + danmalnode(_cur->right);
}


int which_is_bigger(int a, int b) { // p289
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}
// p. 283
// 트리의 응용-> 수식 트리 처리
// 그림 8-32









int get_height(struct node* _cur) {
	if (_cur == 0) { // null
		return 0; // 키는 0
	}
	return (1 + which_is_bigger(get_height(_cur->left), get_height(_cur->right)));
}

// que를 이용해서  레벨 순회 (각 level을 왼쪽에서 오른쪽으로 순서대로 읽으면서 내려온다.) 구현
void level_order(struct node* _cur) {
	if (_cur == 0) { // bst에 아무 것도 엇ㅂ는 경우
		return;
	}
	enque(_cur);
	while (1) {
		if (front == rear) {
			break;
		}
		_cur = deque();
		printf("%d\n", _cur->data);
		if (_cur->left != 0) {
			enque(_cur->left);
		}
		if (_cur->right != 0) {
			enque(_cur->right);
		}
	}
}

// recursion 쓰지 않고 inorder 구현, 재귀함수는 너무 위험해!!!!

void nonrecurvise_inorder(struct node* _cur) {
	while (1) {
		while (1) { // 왼쪽으로 내려가면서 push
			if (_cur != 0) {
				push(_cur);
				_cur = _cur->left;
			}
			else {
				break;
			}
		}
		_cur = pop();
		if (_cur == 0) {
			break;
		}
		printf("%d\n", _cur->data);
		_cur = _cur->right;
	}
}

// _v값을 가지는 노드를 만들어서 BST에 추가
void addToBST(int _v) {
	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->left = 0;
	_new->right = 0;
	_new->data = _v;
	// BST에 노드르 추가
	// 1. BST가 텅텅 비어있는 경우
	if (root == 0) {
		root = _new;
		return;
	}

	// 2. BST에 뭔가 있는 경우, 이 때는 자기 위치를 찾아 가야 한다. 어디가서 붙어야 하는지. root를 움직일 수 없으니, 별도의 포인터 필요
	struct node* spear = root;
	while (1) {
		if (spear->data < _new->data) { // 오른쪽으로 가야하는데...
			// 자리가 비었네
			if (spear->right == 0) {
				spear->right = _new;
				return;
			}
			else {
				// 누군가 그 자리르 차지하고 있어, 더 내려가 봐야 하는 상황
				spear = spear->right;

			}
		}

		else { // 왼쪽으로 가야하는데,...
				// 자리가 비었네
			if (spear->left == 0) {
				spear->left = _new;
				return;
			}
			else {
				// 누군가 그 자리르 차지하고 있어, 더 내려가 봐야 하는 상황
				spear = spear->left;

			}
		}
	}


}

// traversal_inorder
void traversal_inorder(struct node* _cur) {
	if (_cur == 0) {
		return;
	}

	traversal_inorder(_cur->left);
	printf("%d\n", _cur->data);
	traversal_inorder(_cur->right);
}




// preorder
void traversal_preorder(struct node* _cur) {
	if (_cur == 0) {
		return;
	}
	printf("%d\n", _cur->data);
	traversal_inorder(_cur->left);
	traversal_inorder(_cur->right);
}


// BT는 그냥 모양만 바이너리 트리                  BST는 값에 따라 나뉜다.
//BST의 노드 삭제
// 1. 무자식 노드(terminal node) 삭제는 쉽다. 다만, 부모 노드만 영향을 받는다. 해당 link = null로 설정
//   예외상황 -> 무자식 노드 == root일 경우 -> root를 null로 변환

// 2. 홑(1개)자식, 자식에게 자기 자리를 물려주고, 나의 부모에게 그 자식을 연결시켜준다.
// 내가 부모의 어떤 자식인지 잘 기억했다가, 그렇게 그 자식을 연결해준다.
// 홀자식 노드 == root -> root로 하여금 남은 자식을 가리키게 한다.



//3.  쌍자식. 왼쪽 집안에서 가장 큰 노드가 올라오거나, 오른쪽 집안에서 가장 작은 노드가 올라온다..
// 왼쪽 구룹의 젤 오른쪽 값으로 바꾸던가 아니면 오른쪽 그룹에 젤 왼쪽 값으로 바꾼다. 즉, 왼쪽에서 제일 큰 친구는 제일 아래 오른쪽이고, 오른쪽에서 제일 작은 친구는 제일 아래 왼쪽이다.
// 쌍자식 노드 == root

// 무자식 노드 지우기. 지울때 항상 포인터 2개 필요-> 해당 부모의 대한 포인터를 알아야 하기 때문에

// 값 _v를 가진 노드와 parent 노드를 찾아서, 각각에 대한 포인터를 struct combo로 만들어서 반환한다. 
// parent: _v를 가진 노드의 부모 노드 (부모가 없으면 null)
// me: _v를 가진 노드 (_v를 가진 노드가 없는 경우, null)
struct combo findNodeCombo(int _v) {
	struct node* spear = root;
	struct node* parent = 0; // 나의 부모

	while (1) {
		
		if (spear == 0) {
			struct combo res = { 0,0 };
			return res;
		}
		
		
		if (spear->data == _v) { // _v를 가진 노드를 찾은경우
			struct combo res = { parent, spear };
			return res;
		}

		else if (spear->data < _v) { // 오른쪽으로 타고 내려가야 하는데
			parent = spear;
			spear = spear->right;
		}
		else { // 왼쪽으로 타고 내려 가는 경우
			parent = spear;
			spear = spear->left;
		}

	}

}

// 값 _v를 가진 노드를 삭제
void delFromBST(int _v) {

	struct combo res = findNodeCombo(_v); // _v를 가진 노드 찾기
	if (res.me == 0) { // _v가 없으므로 종료
		return;
	}

	// 1. 무자식

	if (res.me->left == 0 && res.me->right == 0) {
		// 예외, root인지 판별
		if (res.parent == 0) { // 내가 root
			root = 0;
			free(res.me);
			return;
		}
		else {
			if (res.parent->left == res.me) { // 내가 부모의 왼쪽자식
				res.parent->left = 0;
			}
			else { // 내가 부모의 오른 자식
				res.parent->right = 0;
			}
			free(res.me);
			return;
		}
	}
	
    // 3. 쌍자식
	else if (res.me->left != 0 && res.me->right != 0) {
		//후계자를 찾자
		struct node* spear = res.me->right;
		while (1) {
			if (spear->left == 0) {
				break;
			}
			spear = spear->left;
		}
		// 이 상황에서 spear는 후계자를 가리키고 있다.
		//휴계자 값을 임시 저장해 놓는다.
		int temp = spear->data;
		delFromBST(temp); // 후계자를 날려버린다.
		res.me->data = temp;// 임시 저장값을 me자리에 채운다.
		return;
	}


	// 2. 홑자식
	else {
		// 일단, 내가 왼자식 가지고 있는지 확인
		if (res.me->left != 0) { // 왼쪽 자식 하나만 가지고 있음
			// 내가 root인 경우
			if (res.parent == 0) { // root인 조건, res.me == root
				root = res.me->left;
				free(res.me);
				return;
			}
			else { // 내가 root가 아님
				if (res.parent->left == res.me) {// me가 parent의 left
					res.parent->left = res.me->left;
				}
				else { // me가 parent의 right
					res.parent->right = res.me->left;
				}
				free(res.me);
				return;
			}
		}
		else { // 오른 자식 하나만 가지고 있음.

			if (res.parent == 0) { // root인 조건, res.me == root
				root = res.me->right;
				free(res.me);
				return;
			}
			else { // 내가 root가 아님
				if (res.parent->left == res.me) {// me가 parent의 left
					res.parent->left = res.me->right;
				}
				else { // me가 parent의 right
					res.parent->right = res.me->right;
				}
				free(res.me);
				return;
			}
		}
	}
}

void inorder_traversal(struct node* _cur) {
	
	if (_cur == 0) {
		return;
	}
	
	
	inorder_traversal(_cur->left);
	printf("%d\n", _cur->data);
	inorder_traversal(_cur->right);
}





int main(void) {

	addToBST(20);
	addToBST(10);
	addToBST(30);
	addToBST(40);
	addToBST(5);

	//delFromBST(5);
	delFromBST(100);
	inorder_traversal(root);

	// 하나하나 찾기 너무 힘들다.... 데이터의 구조를 알고 있을때만 이렇게 출력할 수 있음
	/*
	printf("%d\n", (root->data == 20));
	printf("%d\n", (root->left->data == 10));
	printf("%d\n", (root->right->data == 30));
	printf("%d\n", (root->left->left->data == 5));
	printf("%d\n", (root->right->right->data == 40));
	*/
	/*
	struct node* spear = root;
	traversal_inorder(spear);
	nonrecurvise_inorder(spear);
	level_order(spear);

	printf("%d\n", get_height(spear));
	printf("%d\n", danmalnode(spear));
	*/
/*
	struct combo res = findNodeCombo(100);
	printf("%d    %d\n", (res.me == 0), (res.parent == 0));
	*/



	return 0;
}