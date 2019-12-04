// http://bbs.nicklib.com/algorithm/2011

#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct _Tree Tree;
struct _Tree {
	char data;
	Tree *left;
	Tree *right;
};

Tree *stack[100];
unsigned int pos=0;

Tree *pop(void){
	if(pos==0) return NULL;
	pos--;
	return stack[pos];
}

void push(Tree *data){
	stack[pos]=data;
	pos++;
}

void stackinit(void){
	pos=0;
}

int isemptystack(void){
	return !(pos);
}

Tree *queue[100];
unsigned int qpos=0;

Tree *dequeue(void){
	unsigned int i;
	Tree *out;

	if(qpos==0) return NULL;

	out=queue[0];

	for(i=0; i<qpos; i++) {
		queue[i]=queue[i+1];
	}
	qpos--;
  
	return out;
}

void enqueue(Tree *data){
	queue[qpos]=data;
	qpos++;
}

void queueinit(void){
	qpos=0;
}

int isemptyqueue(void){
	return !(qpos);
}



void inorder_r(Tree *root){
	if(root == NULL) return;

	inorder_r(root->left);
	printf("%c ", root->data);
	inorder_r(root->right);
}

void inorder(Tree *root){
	Tree *node=root;

	if(root==NULL) return;

	stackinit();

	while(node->left) {
		push(node);
		node = node->left;
	}

	do {
		printf("%c ", node->data);
		if (node->right) {
			node = node->right;
			while(node->left){
				push(node);
				node = node->left;
			}
		}else{
			node=pop();
		}
	}while (node);

	return;
}

void postorder_r(Tree *root){
	if(root==NULL) return;

	postorder_r(root->left);
	postorder_r(root->right);
	printf("%c ", root->data);
}

void postorder(Tree *root){
	Tree *store = root;
	Tree *node = root;

	if(root==NULL) return;

	stackinit();
	while(node || !isemptystack()) {
		if(node){
			push(node);
			node=node->left;
		} else {
			node=pop();
			while(node->right == NULL || node->right == store) {
				printf("%c ",node->data);
				store = node;
				if(isemptystack()) return;
				node=pop();
			}
		push(node);
		store=node=node->right; 
		}
	}

	return;
}

void preorder_r(Tree *root){
	if(root == NULL) return;

	printf("%c ", root->data);
	preorder_r(root->left);
	preorder_r(root->right);
}

void preorder(Tree *root){
	Tree *store = root;
	Tree *node = root;

	if(root==NULL) return;

	stackinit();
	while(node || !isemptystack()) {
		if(node){
			printf("%c ",node->data);
			push(node);
			node=node->left;
		} else {
			node=pop();
			while(node->right == NULL || node->right == store) {
				store = node;
				if(isemptystack()) return;
				node=pop();
			}
			push(node);
			store=node=node->right; 
		}
	}

	return;
}


void levelorder(Tree *root){
	Tree *node=root;

	if(root == NULL) return;

	queueinit();
	enqueue(root);
	while (!isemptyqueue()){
		node = dequeue();
		printf("%c ", node->data);
		if(node->left)
			enqueue(node->left);
		if(node->right)
			enqueue(node->right);
	}
}


int main(int argc, char *argv[]){
	Tree *root, *node;

	Tree nodearr[7]={{0x00,},};

  
	root=nodearr+0;
	node=root;
	node->data='A';
	node->left = nodearr+1;
	node->left->data='B';
	node->left->left = nodearr+2;
	node->left->left->data='D';
	node->left->right = nodearr+3;
	node->left->right->data='E';
	node->right = nodearr+4;
	node->right->data='C';
	node->right->left = nodearr+5;
	node->right->left->data='F';
	node->right->right = nodearr+6;
	node->right->right->data='G';

	printf("**************************************************************\n");
	printf(" IN ORDER TRAVERSAL\n");
	printf("**************************************************************\n");
	inorder_r(root); printf("\n");
	inorder(root);
	printf("\n**************************************************************\n");
	printf(" POST ORDER TRAVERSAL\n");
	printf("**************************************************************\n");
	postorder_r(root); printf("\n");
	postorder(root);
	printf("\n**************************************************************\n");
	printf(" PRE ORDER TRAVERSAL\n");
	printf("**************************************************************\n");
	preorder_r(root); printf("\n");
	preorder(root);

	printf("\n**************************************************************\n");
	printf(" LEVEL ORDER TRAVERSAL\n");
	printf("**************************************************************\n");
	levelorder(root);

	printf("\n");

	return 0;
}