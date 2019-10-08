
#include "avl.h"

int main() { 
  root = NULL; 

  root = insere(root, 10); 
  root = insere(root, 20); 
  root = insere(root, 30); 
  root = insere(root, 40); 
  root = insere(root, 50); 
  root = insere(root, 25); 
  
  preOrder(root); 
  
  return 0; 
} 
