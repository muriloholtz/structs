#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX_PILHA 100

/* Murilo Holtz Foltran, 133770, Turma IB */

/* nesse programa, será lido uma expressão infixa e 
 impressa a mesma impressão de forma pósfixa, depois disso,
 será realizado o cálculo do resultado */

char novapilha[MAX_PILHA];
int topo=-1;

void push(char item){
    if (topo>=MAX_PILHA-1){
        printf("\nPilha cheia. Empilhamento não foi possível."); //verificação de erro
    }
    else {
        topo++;
        novapilha[topo] = item;
    }
}
char pop(){
    char item;
    item = novapilha[topo];
    topo--;
    return(item);
}

int isOperador(char simbolo){
    
    // função que verifica se char é operando;
    
    if(simbolo == '^' || simbolo=='*' || simbolo == '/' || simbolo == '-' || simbolo == '+'){
        return 1;
    }
    else{
        return 0;
    }
}
int prioridade(char simbolo){
    
    // função de condiciona os operandos em ordem de prioridade;
    
    if(simbolo == '^'){
        return 3;
    }
    else if(simbolo == '*' || simbolo == '/'){
        return 2;
    }
    else if(simbolo == '-' || simbolo == '+'){
        return 1;
    }
    else
        return 0;
}

int main() {
    char infix[40], posfix[40], item, t;
    int i=0, j=0, o1, o2, resultado;
    printf("Expressao aritmetica em notacao infixa:\n");
    gets(infix);
    
    // PARTE 1: expressao infixa -> posfixa;
    
    while(infix[i]|='\0'){ //varrer a expressão infixa da esquerda para a direita;
        item = infix[i];
        // apresenta as condições:
        if(item == '('){
            push(item);
        }
        else if(item>='1' && item<='9'){
            posfix[j]=item;
            j++;
        }
        else if(isOperador(item)==1){
            t = pop();
            while(isOperador(t)==1 && prioridade(t)>=prioridade(item)){
                posfix[j] = t;
                j++;
                t = pop();
            }
            push(t);
            push(item);
        }
        else if(item == ')'){
            t = pop();
            while(t != '('){
                posfix[j] = t;
                j++;
                t=pop();
            }
        }
        else{
            printf("\nExpressão invalida!\n"); //verificação de erro
            exit(0);
        }
        i++;
    }
    
    while(topo>-1){
        posfix[j] = pop();
        j++;
    }
    posfix[j]='\0';
    printf("\nExpressao aritmetica em notacao posfixa: ");
    puts(posfix);
    
    // PARTE 2: cálculo da expressão;
    
    i=0; j=0;
    //varrer a expressão posfixa da esquerda para a direita;
    while(posfix[i]|='\0'){ 
        item = posfix[i];
        if(item>='1' && item<='9'){
            push(item); //se for numero, empilha item;
        }
        else if(isOperador(item)==1){
            // caso seja um operador, desempilha os dois ultimos numeros
            // e realiza o calculo;
            o1 = pop()-'0';
            o2 = pop()-'0';
            if(item == '+'){
                push(o2+o1+'0');
            }
            else if(item == '-'){
                push(o2-o1+'0');
            }
            else if(item == '*'){
                push(o2*o1+'0');
            }
            else if(item == '/'){
                push(o2/o1+'0');
            }
            else if(item == '^'){
                push(pow(o2,o1)+'0');
            }
        }
        i++;
    }
    resultado = pop()-'0';
    printf("Resultado da expressao: %d", resultado);
    
    return 0;
}

