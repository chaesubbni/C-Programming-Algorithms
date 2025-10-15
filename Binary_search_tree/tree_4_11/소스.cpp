#include <stdio.h>
#include <stdlib.h>
// BST�� ��带 ǥ��

#define stack_SZ 10
#define que_SZ 10


struct node {
	int data;
	struct node* left;
	struct node* right;
};
// root node�� ����Ű�� ������
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
		return 0; // ����ִ�.
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

// p. �ܸ���� ���� ���ϱ�. -> �ڽ��� ���� ��� ������ ���ϱ�. ��, �� ������ level ������ ���.

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
// Ʈ���� ����-> ���� Ʈ�� ó��
// �׸� 8-32









int get_height(struct node* _cur) {
	if (_cur == 0) { // null
		return 0; // Ű�� 0
	}
	return (1 + which_is_bigger(get_height(_cur->left), get_height(_cur->right)));
}

// que�� �̿��ؼ�  ���� ��ȸ (�� level�� ���ʿ��� ���������� ������� �����鼭 �����´�.) ����
void level_order(struct node* _cur) {
	if (_cur == 0) { // bst�� �ƹ� �͵� ������ ���
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

// recursion ���� �ʰ� inorder ����, ����Լ��� �ʹ� ������!!!!

void nonrecurvise_inorder(struct node* _cur) {
	while (1) {
		while (1) { // �������� �������鼭 push
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

// _v���� ������ ��带 ���� BST�� �߰�
void addToBST(int _v) {
	struct node* _new = (struct node*)malloc(sizeof(struct node));
	_new->left = 0;
	_new->right = 0;
	_new->data = _v;
	// BST�� ��帣 �߰�
	// 1. BST�� ���� ����ִ� ���
	if (root == 0) {
		root = _new;
		return;
	}

	// 2. BST�� ���� �ִ� ���, �� ���� �ڱ� ��ġ�� ã�� ���� �Ѵ�. ��𰡼� �پ�� �ϴ���. root�� ������ �� ������, ������ ������ �ʿ�
	struct node* spear = root;
	while (1) {
		if (spear->data < _new->data) { // ���������� �����ϴµ�...
			// �ڸ��� �����
			if (spear->right == 0) {
				spear->right = _new;
				return;
			}
			else {
				// ������ �� �ڸ��� �����ϰ� �־�, �� ������ ���� �ϴ� ��Ȳ
				spear = spear->right;

			}
		}

		else { // �������� �����ϴµ�,...
				// �ڸ��� �����
			if (spear->left == 0) {
				spear->left = _new;
				return;
			}
			else {
				// ������ �� �ڸ��� �����ϰ� �־�, �� ������ ���� �ϴ� ��Ȳ
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


// BT�� �׳� ��縸 ���̳ʸ� Ʈ��                  BST�� ���� ���� ������.
//BST�� ��� ����
// 1. ���ڽ� ���(terminal node) ������ ����. �ٸ�, �θ� ��常 ������ �޴´�. �ش� link = null�� ����
//   ���ܻ�Ȳ -> ���ڽ� ��� == root�� ��� -> root�� null�� ��ȯ

// 2. Ȭ(1��)�ڽ�, �ڽĿ��� �ڱ� �ڸ��� �����ְ�, ���� �θ𿡰� �� �ڽ��� ��������ش�.
// ���� �θ��� � �ڽ����� �� ����ߴٰ�, �׷��� �� �ڽ��� �������ش�.
// Ȧ�ڽ� ��� == root -> root�� �Ͽ��� ���� �ڽ��� ����Ű�� �Ѵ�.



//3.  ���ڽ�. ���� ���ȿ��� ���� ū ��尡 �ö���ų�, ������ ���ȿ��� ���� ���� ��尡 �ö�´�..
// ���� ������ �� ������ ������ �ٲٴ��� �ƴϸ� ������ �׷쿡 �� ���� ������ �ٲ۴�. ��, ���ʿ��� ���� ū ģ���� ���� �Ʒ� �������̰�, �����ʿ��� ���� ���� ģ���� ���� �Ʒ� �����̴�.
// ���ڽ� ��� == root

// ���ڽ� ��� �����. ���ﶧ �׻� ������ 2�� �ʿ�-> �ش� �θ��� ���� �����͸� �˾ƾ� �ϱ� ������

// �� _v�� ���� ���� parent ��带 ã�Ƽ�, ������ ���� �����͸� struct combo�� ���� ��ȯ�Ѵ�. 
// parent: _v�� ���� ����� �θ� ��� (�θ� ������ null)
// me: _v�� ���� ��� (_v�� ���� ��尡 ���� ���, null)
struct combo findNodeCombo(int _v) {
	struct node* spear = root;
	struct node* parent = 0; // ���� �θ�

	while (1) {
		
		if (spear == 0) {
			struct combo res = { 0,0 };
			return res;
		}
		
		
		if (spear->data == _v) { // _v�� ���� ��带 ã�����
			struct combo res = { parent, spear };
			return res;
		}

		else if (spear->data < _v) { // ���������� Ÿ�� �������� �ϴµ�
			parent = spear;
			spear = spear->right;
		}
		else { // �������� Ÿ�� ���� ���� ���
			parent = spear;
			spear = spear->left;
		}

	}

}

// �� _v�� ���� ��带 ����
void delFromBST(int _v) {

	struct combo res = findNodeCombo(_v); // _v�� ���� ��� ã��
	if (res.me == 0) { // _v�� �����Ƿ� ����
		return;
	}

	// 1. ���ڽ�

	if (res.me->left == 0 && res.me->right == 0) {
		// ����, root���� �Ǻ�
		if (res.parent == 0) { // ���� root
			root = 0;
			free(res.me);
			return;
		}
		else {
			if (res.parent->left == res.me) { // ���� �θ��� �����ڽ�
				res.parent->left = 0;
			}
			else { // ���� �θ��� ���� �ڽ�
				res.parent->right = 0;
			}
			free(res.me);
			return;
		}
	}
	
    // 3. ���ڽ�
	else if (res.me->left != 0 && res.me->right != 0) {
		//�İ��ڸ� ã��
		struct node* spear = res.me->right;
		while (1) {
			if (spear->left == 0) {
				break;
			}
			spear = spear->left;
		}
		// �� ��Ȳ���� spear�� �İ��ڸ� ����Ű�� �ִ�.
		//�ް��� ���� �ӽ� ������ ���´�.
		int temp = spear->data;
		delFromBST(temp); // �İ��ڸ� ����������.
		res.me->data = temp;// �ӽ� ���尪�� me�ڸ��� ä���.
		return;
	}


	// 2. Ȭ�ڽ�
	else {
		// �ϴ�, ���� ���ڽ� ������ �ִ��� Ȯ��
		if (res.me->left != 0) { // ���� �ڽ� �ϳ��� ������ ����
			// ���� root�� ���
			if (res.parent == 0) { // root�� ����, res.me == root
				root = res.me->left;
				free(res.me);
				return;
			}
			else { // ���� root�� �ƴ�
				if (res.parent->left == res.me) {// me�� parent�� left
					res.parent->left = res.me->left;
				}
				else { // me�� parent�� right
					res.parent->right = res.me->left;
				}
				free(res.me);
				return;
			}
		}
		else { // ���� �ڽ� �ϳ��� ������ ����.

			if (res.parent == 0) { // root�� ����, res.me == root
				root = res.me->right;
				free(res.me);
				return;
			}
			else { // ���� root�� �ƴ�
				if (res.parent->left == res.me) {// me�� parent�� left
					res.parent->left = res.me->right;
				}
				else { // me�� parent�� right
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

	// �ϳ��ϳ� ã�� �ʹ� �����.... �������� ������ �˰� �������� �̷��� ����� �� ����
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