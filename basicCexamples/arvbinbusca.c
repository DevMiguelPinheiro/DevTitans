#include <stdio.h>
#include <stdlib.h>

struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* busca(Arv* r, int v) {
  if (r == NULL) return NULL;
  else if (r->info > v) return busca(r->esq, v);
  else if (r->info < v) return busca(r->dir, v);
  else return r;
}

Arv* insere(Arv* a, int v) {
  if (a == NULL) {
    a = (Arv*)malloc(sizeof(Arv));
    a->info = v;
    a->esq = a->dir = NULL;
  } else if (v < a->info)
    a->esq = insere(a->esq, v);
  else
    a->dir = insere(a->dir, v);
  return a;
}

Arv* libera(Arv* a) {
  if (a != NULL) {
    libera(a->esq);
    libera(a->dir);
    free(a);
  }
  return NULL;
}

void imprime_in(Arv* r) {
  if (r != NULL) {
    imprime_in(r->esq);
    printf("%d ", r->info);
    imprime_in(r->dir);
  }
}

int main(void) {
  Arv* a = NULL;
  int valores[] = {1, 2, 3, 5, 15, 7};
  int n = sizeof(valores) / sizeof(valores[0]);

  
  for (int i = 0; i < n; i++) {
    a = insere(a, valores[i]);
    printf("Tree after inserting %d: ", valores[i]);
    imprime_in(a);
    printf("\n");
  }

  int encontrar[] = {2, 8};
  int m = sizeof(encontrar) / sizeof(encontrar[0]);

  for (int i = 0; i < m; i++) {
    int v = encontrar[i];
    if (busca(a, v) != NULL)
      printf("item %d encontrado.\n", v);
    else
      printf("item %d nao foi encontrado.\n", v);
  }

  
  a = libera(a);

  return 0;
}
