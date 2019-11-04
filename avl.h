#include<stdio.h> 
#include<stdlib.h>
#include <string.h> 

typedef struct Node { 
	int id;
	char nome[50];
	float saldo; 
	struct Node *esq; 
	struct Node *dir; 
	int altura; 
}TNodo;

TNodo *raiz;

TNodo *buscar(TNodo *R, int aux);
TNodo *remover(TNodo *R, int aux);
TNodo* lerArquivoArvore(TNodo *R);
TNodo* separarDadosDaLinhaArvore(TNodo *R, char linha[50]);
int altura(TNodo *N);
int max(int a, int b);
TNodo* geraNodo(int id, char nome[50], float saldo);
TNodo *direitaRotate(TNodo *y);
TNodo *esquerdaRotate(TNodo *x);
int getBalance(TNodo *N);
TNodo* insere(TNodo* node, int id, char nome[50], float saldo);
void preOrder(TNodo *root);
TNodo * minValueNode(TNodo* node);
