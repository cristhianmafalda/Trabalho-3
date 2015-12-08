#include<stdio.h>
#include<stdlib.h>

struct matriz{
    int valor;
    int col;
    struct matriz * prox;
};

struct matriz * aux;

struct matriz * aux2;

struct matriz * criacelula(int dado, int coluna){

        struct matriz * novo;
        novo = (struct matriz*)malloc(sizeof(struct matriz));
        novo->valor = dado;
        novo->col = coluna;
        novo->prox = NULL;
        return(novo);
}

void imprime(struct matriz * celula,int linha){

    if(celula==NULL){
        return;
    }
    printf("\t%d(%d)(%d)",celula->valor,linha+1,celula->col+1);
    imprime(celula->prox,linha);
}

int menu(){ //funcao que abre o menu de opções e retorna a desejada

        //imprime todas as opções na tela
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua matriz:",163,135,198);
		printf("\nOp%c%co 1: Exclus%co",135,198,198);
		printf("\nOp%c%co 2: Consulta de Valor",135,198);
		printf("\nOp%c%co 3: Soma de Linha",135,198);
		printf("\nOp%c%co 4: Soma de Coluna",135,198);
		printf("\nOp%c%co 5: Atribui%c%co de Valor",135,198,135,198);
		printf("\nOp%c%co 6: Determinante",135,198);
		printf("\nOp%c%co 7: Resolver Sistema Linear",135,198);
		printf("\nOp%c%co 8: Encerrar o Programa",135,198);
		printf("\n\nOp%c%co escolhida: ",135,198);

		int opcao;
		scanf("%d",&opcao); //le a opcao escolhida
		while(opcao<1||opcao>8){ //confere a coerencia e refaz se necessario
            printf("\n\nEscolha uma op%c%co existente",135,198);
            printf("\n\nOp%c%co escolhida: ",135,198);
            scanf("%d",&opcao);
		}
		printf("\n");
		return(opcao);    //retorna a opcao
}

void main(){

    int numl,numc,i,j,novo;
    scanf("%d %d",&numl,&numc);

    struct matriz * linha[numl];

    for(i=0;i<numl;i++){
        linha[i] = NULL;
    }

    for(i=0;i<numl;i++){
        aux2 = NULL;
        for(j=0;j<numc;j++){
                scanf("%d",&novo);
                if(novo!=0){
                    aux = criacelula(novo,j);

                    if(linha[i]==NULL){
                        linha[i] = aux;
                    }
                    else{
                        aux2 = linha[i];
                        while(aux2->prox != NULL){
                            aux2 = aux2->prox;
                        }
                        aux2->prox = aux;
                    }
                }
        }
    }

    for(i=0;i<numl;i++){
        printf("\n\nLinha %d:",i+1);
        imprime(linha[i],i);
    }
    printf("\n\n");

    int opcao;
    int fim = 1;
    while(fim!=2){
        opcao = menu();
        if (opcao == 1){

        }
        if (opcao == 2){

        }
        if (opcao == 3){

        }
        if (opcao == 4){

        }
        if (opcao == 5){

        }
        if (opcao == 6){

        }
        if (opcao == 7){

        }
        if (opcao == 8){
            fim = 2;
        }
    }
    printf("\nPROGRAMA ENCERRADO");
    getch();	            //pausa para leitura da tela
}




