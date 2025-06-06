#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n)
{
  for (int i = 0; i < 9; i++) {
    int seen[10];
    for (int j = 0; j < 10; j++) seen[j] = 0;
    for (int j = 0; j < 9; j++)
    {
      int val = n->sudo[i][j];
      if (val != 0)
      {
        if (seen[val]) return 0;
        seen[val] = 1;
      }
    }
  }

  for (int j = 0; j < 9; j++) {
    int seen[10];
    for (int i = 0; i < 10; i++) seen[i] = 0;
    for (int i = 0; i < 9; i++)
    {
      int val = n->sudo[i][j];
      if (val != 0)
      {
        if (seen[val]) return 0; // Repetido en columna
        seen[val] = 1;
      }
    }
  }

  for (int k = 0; k < 9; k++)
  {
    int seen[10];
    for (int i = 0; i < 10; i++) seen[i] = 0;
    for (int p = 0; p < 9; p++)
    {
      int i = 3 * (k / 3) + (p / 3);
      int j = 3 * (k % 3) + (p % 3);
      int val = n->sudo[i][j];

      if (val != 0)
      {
        if (seen[val]) return 0; // Repetido en submatriz
        seen[val] = 1;
      }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n)
{
    List* list = createList();
    for(int i = 0 ; i < 9 ; i++)
    {
      for(int k = 0 ; k < 9 ; k++)
      {
        if(n->sudo[i][k] == 0)
        {
          for(int valor = 1 ; valor <= 9 ; valor++)
          {
            Node *newNode = copy(n);
            newNode->sudo[i][k] = valor;
            if (is_valid(newNode)) pushBack(list, newNode);
          }
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n)
{
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++) 
    {
      if(n->sudo[i][j] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack* S = createStack();
  push(S, initial);

  while(!is_empty(S))
  {
    Node* current = top(S);
    pop(S);
    (*cont)++;

    if(is_final(current))
    {
      clean(S);
      return current;
    }

    List* adj = get_adj_nodes(current);
    Node* adj_node = first(adj);
    while(adj_node)
    {
      push(S, adj_node);
      adj_node = next(adj);
    }

    free(current);
  }

  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/