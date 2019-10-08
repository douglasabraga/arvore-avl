#include<stdio.h> 
#include<stdlib.h> 

typedef struct Node { 
	int id;
	char nome[50];
	float saldo; 
	struct Node *esq; 
	struct Node *dir; 
	int altura; 
}TNodo; 

TNodo *root;

int altura(TNodo *N);
int max(int a, int b);
TNodo* geraNodo(int id);
TNodo *direitaRotate(TNodo *y);
TNodo *esquerdaRotate(TNodo *x);
int getBalance(TNodo *N);
TNodo* insere(TNodo* node, int id);
void preOrder(TNodo *root);
