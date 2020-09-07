/*
 Murilo Holtz Foltran, 133770
 */

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef int TIPOFILA;

typedef struct {
    int itens[MAX];
    int inicio;
    int n; //numero de elementos
} FILA;

typedef FILA *PFila;

PFila criarFila(){
    PFila f = (PFila)malloc(sizeof(FILA)); //alocação de memoria
    f->inicio=0;
    f->n=0; //numero de elementos
    return (f);
}

int sizeFila(PFila f){
    return f->n;
}

void exibirFila(PFila f, int v){
    int i = f->inicio;
    int j;
    for(j=0; j<v; j++){
        printf("%i ", f->itens[i]);
        i = (i+1)%MAX;
    }
}

int enfileirar(PFila f, int val){
    if (f->n>=MAX){
        printf("Fila cheia\n");
        return -1;
    }
    int posicao = (f->inicio + f->n)%MAX;
    f->itens[posicao] = val;
    f->n++;
    return 0;
}

int desenfileirar(PFila f, int* val){
    if (f->n==0)
        printf("Fila vazia\n");
        return -1;
    *val = f->itens[f->inicio];
    f->inicio = (f->inicio)%MAX;
    f->n--;
    return 0;
}

int main() {
    int n, v, i, nota, j=0, auxnotas, auxid;
    int id[100], notas[100];
    char resposta;
    PFila filanotas, filaid;
    
    printf("Quantidade de candidatos:\n");
    scanf("%d", &n);
    printf("Quantidade de vagas disponíveis:\n");
    scanf("%d", &v);
    while (j<n) {
        printf("Identificação do candidato:\n");
        scanf("%d", &id[j]);
        printf("Nota do candidato %d:\n", id[j]);
        scanf("%d", &notas[j]);
        if (notas[j]<0 || notas[j]>100){
            printf("Nota Inválida! Insira novamente a nota do candidato %d:\n", id[j]);
            scanf("%d", &notas[j]);
        }
        j++;
    }
    // vetores em ordem decrescente:
    for(i=0; i<n; i++){
        for(j=i+1; j<n; j++){
            if(notas[i]<notas[j]){
                auxnotas = notas[i];
                notas[i]=notas[j];
                notas[j] = auxnotas;
                auxid = id[i];
                id[i]=id[j];
                id[j]=auxid;
            }
        }
    }
    
    j=0;
     
    printf("\n");
    
    while (j<n) {
        printf("Candidato %d, nota: %d\n", id[j], notas[j]);
        j++;
    }
    
    //enfileirando em relação às respostas dos candidatos 
    filanotas = criarFila();
    filaid = criarFila();
    for(i=0;i<n;i++){
        j = i+1;
        printf("\nResposta do candidato %d: (s/n)\n", id[i]);
        scanf(" %c", &resposta);
        if(resposta == 's'){
            enfileirar(filanotas, notas[i]);
            enfileirar(filaid, id[i]);          
            printf("Candidato %d Enfileirado\n", id[i]);
            }
        else if(resposta == 'n')    
            printf("Candidato excluído.\n");
    }
    printf("\n\nLista de aprovados:\n ");
    exibirFila(filaid, v); //imprimindo fila
    printf("\nRespectivas notas:\n ");
    exibirFila(filanotas, v);
    
    free(filanotas);
    free(filaid);
    
    return 0;
}

