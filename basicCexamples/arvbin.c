#include <stdio.h>
#include <stdlib.h>

struct arv {
  int info;
  struct arv* esq;
  struct arv* dir;
};

typedef struct arv Arv;

Arv* inicializa(void)
{
  return NULL;
}

Arv* cria(int c, Arv* sae, Arv* sad)
{
  Arv* p = (Arv*)malloc(sizeof(Arv));
  p->info = c;
  p->esq = sae;
  p->dir = sad;
  return p;
}

int vazia(Arv* a)
{
  return a == NULL;
}

Arv* libera(Arv* a)
{
  if (!vazia(a)) {
    libera(a->esq);
    libera(a->dir);
    free(a);
  }
  return NULL;
}

void imprime_pre(Arv* a)
{
  if (a != NULL) {
    printf("%d ", a->info);
    imprime_pre(a->esq);
    imprime_pre(a->dir);
  }
}

void imprime_in(Arv* a)
{
  if (a != NULL) {
    imprime_in(a->esq);
    printf("%d ", a->info);
    imprime_in(a->dir);
  }
}

void imprime_pos(Arv* a)
{
  if (a != NULL) {
    imprime_pos(a->esq);
    imprime_pos(a->dir);
    printf("%d ", a->info);
  }
}

int main()
{
  // Questao 2: Create and print the initial tree
  Arv* a = cria(45,
                cria(5,
                     cria(12, NULL, NULL),
                     cria(34,
                          NULL,
                          cria(67, NULL, NULL))),
                cria(80,
                     NULL,
                     cria(40, NULL, NULL)));

  printf("Questao 2\n");
  printf("Pre-fixado: ");
  imprime_pre(a);
  printf("\n");

  printf("In-fixado: ");
  imprime_in(a);
  printf("\n");

  printf("Pos-fixado: ");
  imprime_pos(a);
  printf("\n");

  libera(a);

  // Questao 3: Create the tree again, graft the subtree, and print the updated tree
  a = cria(45,
           cria(5,
                cria(12, NULL, NULL),
                cria(34,
                     NULL,
                     cria(67, NULL, NULL))),
           cria(80,
                NULL,
                cria(40, NULL, NULL)));

  Arv* a3 = cria(3,
                 cria(66, NULL, NULL),
                 cria(31, NULL, NULL));

  a->dir->esq = a3;

  printf("Questao 3\n");
  printf("Pre-fixado: ");
  imprime_pre(a);
  printf("\n");

  printf("In-fixado: ");
  imprime_in(a);
  printf("\n");

  printf("Pos-fixado: ");
  imprime_pos(a);
  printf("\n");

  // Questao 4: Prune the subtree rooted at 34 and print the updated tree
  a->esq->dir = libera(a->esq->dir);

  printf("Questao 4\n");
  printf("Pre-fixado: ");
  imprime_pre(a);
  printf("\n");

  printf("In-fixado: ");
  imprime_in(a);
  printf("\n");

  printf("Pos-fixado: ");
  imprime_pos(a);
  printf("\n");

  libera(a);

  return 0;
}