#include "avl.h"


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
TNodo* geraNodo(int id) { 
    TNodo* novo = (TNodo*)malloc(sizeof(TNodo)); 
    novo->id = id; 
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
TNodo* insere(TNodo* node, int id) { 
    /* 1.  Perform the normal BST insereion */
    if (node == NULL) 
        return(geraNodo(id)); 
  
    if (id < node->id) 
        node->esq  = insere(node->esq, id); 
    else if (id > node->id) 
        node->dir = insere(node->dir, id); 
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
        printf("%d ", root->id); 
        preOrder(root->esq); 
        preOrder(root->dir); 
    } 
} 
