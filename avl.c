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
        printf("\nId: %d\t ...Nome: %s\t ...Saldo: %.2f", root->id, root->nome, root->saldo); 
        preOrder(root->esq); 
        preOrder(root->dir); 
    } 
} 

TNodo* remover(TNodo* R, int id){ 
    // PASSO 1: EXECUTAR PADRÃO BST PADRÃO
    if (R == NULL) 
        return R; 
  
    // Se a chave a ser excluída for menor que a chave da raiz,
	// ela estará na subárvore esquerda
    if ( id < R->id ) 
        R->esq = remover(R->esq, id); 
  
    // Se a chave a ser excluída for maior que a chave da raiz, 
	// ela estará na subárvore direita 
    else if( id > R->id ) 
        R->dir = remover(R->dir, id); 
  
    // se a chave for igual à chave da raiz, 
	// esse é o nó a ser excluído
    else
    { 
        // nó com apenas um filho ou nenhum filho
        if( (R->esq == NULL) || (R->dir == NULL) ) 
        { 
            TNodo *temp = R->esq ? R->esq : 
                                             R->dir; 
  
            // Nenhum caso filho 
            if (temp == NULL) 
            { 
                temp = R; 
                R = NULL; 
            } 
            else // Caso de um filho
	             *R = *temp; // Copie o conteúdo do filho não vazio
            free(temp); 
        } 
        else
        { 
            // nó com dois filhos: obter o sucessor in order (o menor na subárvore direita) 
            TNodo* temp = minValueNode(R->dir); 
  
            // Copie os dados do sucessor da ordem de entrada neste nó 
            R->id = temp->id; 
  
            // Excluir o sucessor da ordem de entrada 
            R->dir = remover(R->dir, temp->id); 
        } 
    } 
  
    // Se a árvore tiver apenas um nó, retorne
    if (R == NULL) 
      return R; 
  
    // PASSO 2: ATUALIZAÇÃO DA ALTURA DO NÓ ATUAL
    R->altura = 1 + max(altura(R->esq), 
                           altura(R->dir)); 
  
    // PASSO 3: OBTENHA O FATOR DE EQUILÍBRIO DESTE NÓ 
	// (para verificar se esse nó ficou desequilibrado) 
    int balance = getBalance(R); 
  
    // Se esse nó ficar desequilibrado, haverá 4 casos
  
    // Left Left Case 
    if (balance > 1 && getBalance(R->esq) >= 0) 
        return direitaRotate(R); 
  
    // Left Right Case 
    if (balance > 1 && getBalance(R->esq) < 0) 
    { 
        R->esq =  esquerdaRotate(R->esq); 
        return direitaRotate(R); 
    } 
  
    // Right Right Case 
    if (balance < -1 && getBalance(R->dir) <= 0) 
        return esquerdaRotate(R); 
  
    // Right Left Case 
    if (balance < -1 && getBalance(R->dir) > 0) 
    { 
        R->dir = direitaRotate(R->dir); 
        return esquerdaRotate(R); 
    } 
  
    return R; 
} 

TNodo *buscar(TNodo *R, int id){
	if(R == NULL) 
		return NULL;
	else{
		if(id > R->id){
			return buscar(R->dir, id);
		}else if (id < R->id){
			return buscar(R->esq, id);
		}else return R;
	}	
}

TNodo * minValueNode(TNodo* node){ 
    TNodo* current = node; 
  
    /* faça um loop para baixo para encontrar a folha mais à esquerda */
    while (current->esq != NULL) 
        current = current->esq; 
  
    return current; 
}
