#include "avl.h"

TNodo* lerArquivoArvore(TNodo *R){
	char linha[50]; // string armazenara a linha
    FILE *arq;

    arq = fopen("DadosBancoPulini.txt","r"); // Abre o arquivo
    if (arq == NULL){  // Se houve erro na abertura
		printf("Problemas na abertura do arquivo\n");
	}else{
		while(fgets(linha, sizeof(linha)-1, arq) != NULL) { // Loop para ler cada linha do arquivo enquanto houver linhas
			R = separarDadosDaLinhaArvore(R,linha);
		}
	}
    fclose(arq);
    return R;
}


TNodo* separarDadosDaLinhaArvore(TNodo *R, char linha[50]){
	char delimitador[] = "|"; // Caracter delimitador
    char *info; // Ponteiro para armazenar as informacoes

	int id;
	char nome[50];
	float saldo;

	info = strtok(linha, delimitador); // info recebe a primeira string antes do primeiro delimitador da primeira linha

	while(info != NULL) { // Enquanto houver linhas no arquivo

		id = atoi(info); // Copia info para id

		info = strtok(NULL, delimitador); // Separa o nome da linha
		strcpy(nome, info);

		info = strtok(NULL, delimitador); // Separa o saldo da linha
		saldo = atof(info);

		info = strtok(NULL,delimitador); // Separa o codigo da linha
		//printf("%d, %f\n", id, saldo);
		R = insere(R, id, nome, saldo);
		//insereHash(id, nome, saldo);
	}
	return R;
}

int altura(TNodo *N) { 
    if (N == NULL) 
        return 0; 
    return N->altura; 
} 
  
// A utility function to get maximum of two integers 
int max(int a, int b) { 
    return (a > b)? a : b; 
} 
  
/* Helper function that allocates a new node with the given id and 
    NULL esq and dir pointers. */
TNodo* geraNodo(int id, char nome[50], float saldo) { 
    TNodo* novo = (TNodo*)malloc(sizeof(TNodo)); 
    novo->id = id;
    strcpy(novo->nome,nome);
    novo->saldo = saldo;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->altura = 1;  // new node is initially added at leaf 
    return novo; 
} 
  
// A utility function to dir rotate subtree rooted with y 
// See the diagram given above. 
TNodo *direitaRotate(TNodo *y) { 
    TNodo *x = y->esq; 
    TNodo *T2 = x->dir; 
  
    // Perform rotation 
    x->dir = y; 
    y->esq = T2; 
  
    // Update alturas 
    y->altura = max(altura(y->esq), altura(y->dir))+1; 
    x->altura = max(altura(x->esq), altura(x->dir))+1; 
  
    // Return new root 
    return x; 
} 
  
// A utility function to esq rotate subtree rooted with x 
// See the diagram given above. 
TNodo *esquerdaRotate(TNodo *x) { 
    TNodo *y = x->dir; 
    TNodo *T2 = y->esq; 
  
    // Perform rotation 
    y->esq = x; 
    x->dir = T2; 
  
    //  Update alturas 
    x->altura = max(altura(x->esq), altura(x->dir))+1; 
    y->altura = max(altura(y->esq), altura(y->dir))+1; 
  
    // Return new root 
    return y; 
} 
  
// Get Balance factor of node N 
int getBalance(TNodo *N) { 
    if (N == NULL) 
        return 0; 
    return altura(N->esq) - altura(N->dir); 
} 
  
// Recursive function to insere a id in the subtree rooted 
// with node and returns the new root of the subtree. 
TNodo* insere(TNodo* node, int id, char nome[50], float saldo) { 
    /* 1.  Perform the normal BST insereion */
    if (node == NULL) 
        return(geraNodo(id, nome, saldo));
  
    if (id < node->id) 
        node->esq  = insere(node->esq, id, nome, saldo); 
    else if (id > node->id) 
        node->dir = insere(node->dir, id, nome, saldo); 
    else // Equal keys are not allowed in BST 
        return node; 
  
    /* 2. Update altura of this ancestor node */
    node->altura = 1 + max(altura(node->esq), 
                           altura(node->dir)); 
  
    /* 3. Get the balance factor of this ancestor 
          node to check whether this node became 
          unbalanced */
    int balance = getBalance(node); 
  
    // If this node becomes unbalanced, then 
    // there are 4 cases 
  
    // esq esq Case 
    if (balance > 1 && id < node->esq->id) 
        return direitaRotate(node); 
  
    // dir dir Case 
    if (balance < -1 && id > node->dir->id) 
        return esquerdaRotate(node); 
  
    // esq dir Case 
    if (balance > 1 && id > node->esq->id) 
    { 
        node->esq =  esquerdaRotate(node->esq); 
        return direitaRotate(node); 
    } 
  
    // dir esq Case 
    if (balance < -1 && id < node->dir->id) 
    { 
        node->dir = direitaRotate(node->dir); 
        return esquerdaRotate(node); 
    } 
  
    /* return the (unchanged) node pointer */
    return node; 
} 
  
// A utility function to print preorder traversal 
// of the tree. 
// The function also prints altura of every node 
void preOrder(TNodo *root) { 
    if(root != NULL) 
    { 
        printf("%d , %s , %.2f\n", root->id, root->nome, root->saldo); 
        preOrder(root->esq); 
        preOrder(root->dir); 
    } 
} 
