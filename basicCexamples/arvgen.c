#include <stdio.h>
#include <stdlib.h>

struct arvgen {
  int info;
  struct arvgen *prim;
  struct arvgen *prox;
};
typedef struct arvgen ArvGen;

ArvGen* cria(int info) {
  ArvGen *a = (ArvGen *)malloc(sizeof(ArvGen));
  a->info = info;
  a->prim = NULL;
  a->prox = NULL;
  return a;
}

void insere(ArvGen* a, ArvGen* f) {
  f->prox = a->prim;
  a->prim = f;
}

void libera(ArvGen* a) {
  ArvGen* p = a->prim;
  while (p != NULL) {
    ArvGen* t = p->prox;
    libera(p);
    p = t;
  }
  free(a);
}

void imprime(ArvGen* a) {
  ArvGen* p;
  printf("%d\n", a->info);
  for (p = a->prim; p != NULL; p = p->prox)
    imprime(p);
}

int busca(ArvGen* a, int c) {
  ArvGen* p;
  if (a->info == c)
    return 1;
  else {
    for (p = a->prim; p != NULL; p = p->prox) {
      if (busca(p, c))
        return 1;
    }
  }
  return 0;
}

int main() {
  ArvGen* a = cria(43);
  
  ArvGen* noh22 = cria(22);
  ArvGen* noh21 = cria(21);
  ArvGen* noh58 = cria(58);
  ArvGen* noh45 = cria(45);
  
  ArvGen* noh66 = cria(66);
  ArvGen* noh31 = cria(31);
  
  ArvGen* noh71 = cria(71);
  ArvGen* noh59 = cria(59);
  ArvGen* noh12 = cria(12);
  
  ArvGen* noh35 = cria(35);

  
  // 22
  insere(noh22, noh31);  
  insere(noh22, noh66);  
  //58
  insere(noh58, noh12);  
  insere(noh58, noh59);  
  insere(noh58, noh71);  
  //45
  insere(noh45, noh35);  
  
  insere(a, noh45);
  insere(a, noh58);
  insere(a, noh21);
  insere(a, noh22);  
  
  printf("Arvore:");
  imprime(a);
  
  int doze = busca(a, 12);
  int oitenta = busca(a, 88);


  printf("Verificando os numeros na arvore");
  if (doze) {
    printf("12 esta na arvore.\n");
  } else {
    printf("12 NAO esta na arvore.\n");
  }

  if (oitenta) {
    printf("88 esta na arvore.\n");
  } else {
    printf("88 NAO esta na arvore.\n");
  }
  
  libera(a);

  return 0;
}
