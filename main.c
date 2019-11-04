
#include "avl.h"

void menu();

int main() { 
	raiz = NULL; 
	raiz = lerArquivoArvore(raiz);
	//preOrder(raiz); 
	
	menu();
	
  return 0; 
} 

void menu(){
	int op;
	int aux;
	TNodo *n = NULL;
	//float tempoArvore, tempoHash;
	//clock_t inicioArvore, fimArvore, inicioHash, fimHash;
	
	do{
		printf("\n=============================================");
		printf("\n0 - SAIR");
		printf("\n1 - Imprimir elementos da arvore ");
		printf("\n2 - Buscar um elemento pela chave");
		printf("\n3 - Remover um elemento da arvore pela chave");
		printf("\n=============================================");
		printf("\n->");
		scanf("%d", &op);
		printf("\n");
	}while(op < 0 || op > 3);
	
	switch(op){

		case 1:
			preOrder(raiz);
			menu();
			break;
		
		case 2:
			printf("\nInsira o ID:");
			scanf("%d", &aux);

			TNodo *n = buscar(raiz, aux);

			if(n == NULL){
				printf("\n\nValor Informado Nao Encontrado!");	
			}else{
				printf("\n\nRegistro Encontrado na Arvore:\nId: %d\nNome: %s\nSaldo: %.2f\n\n", n->id, n->nome, n->saldo);
			}
			
			menu();
			break;
		
		case 3:
			printf("\nInsira o ID:");
			scanf("%d", &aux);
			
			
			n = remover(raiz, aux);
			
			if(n == NULL)
				printf("\n\nValor Informado Nao Encontrado!");
			
			menu();
			break;	
	}
}
