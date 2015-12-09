#include<stdio.h>
#include<stdlib.h>

//Não esquecer de tirar a funcao imprime da main do while da main

struct matriz{
    int valor;
    int col;
    struct matriz * prox;
};

struct matriz * aux;
struct matriz * aux2;
struct matriz * aux3;

struct matriz * criacelula(int dado, int coluna){

        struct matriz * novo;
        novo = (struct matriz*)malloc(sizeof(struct matriz));
        novo->valor = dado;
        novo->col = coluna;
        novo->prox = NULL;
        return(novo);
}

void imprime(struct matriz * celula,int colant, int numc){

    int i;
    if(celula==NULL){
        if (colant!=numc){
            for(i=0;i<numc-colant;i++){
                printf("0\t");
            }
        }
        return;
    }
    for(i=1;i<celula->col-colant;i++){
            printf("0\t");
    }
    printf("%d\t",celula->valor);
    imprime(celula->prox,celula->col,numc);
}

void consulta(struct matriz * celula, int coluna, int linha){

    if(celula == NULL){
        printf("\nValor da posi%c%co (%d,%d) : 0",135,198,linha,coluna);
    }
    else if(celula->col > coluna){
        printf("\nValor da posi%c%co (%d,%d) : 0",135,198,linha,coluna);
    }
    else if(celula->col == coluna){
        printf("\nValor da posi%c%co (%d,%d) : %d",135,198,linha,coluna,celula->valor);
    }
    else{
        consulta(celula->prox,coluna,linha);
    }
}

void excluir(int numlin ,struct matriz *linha[]){

    int i;
    for(i=0; i<numlin; i++){
            if(linha[i] == NULL){
                continue;
            }
            else{
                aux = linha[i]->prox;
                free(linha[i]);
                linha[i] = NULL;
                if(aux!=NULL){
                    while(aux->prox !=NULL){
                        aux2 = aux->prox;
                        free(aux);
                        aux = NULL;
                        aux = aux2;
                    }
                }
                free(aux);
                aux = NULL;
            }
    }
}

void somalinha(struct matriz*linha,int soma){

    if(linha==NULL){
        printf("\nSoma = %d",soma);
        return;
    }
    else{
        soma = soma + linha->valor;
        return(somalinha(linha->prox,soma));
    }
}

int buscacol(struct matriz * celula, int coluna){

    if(celula == NULL){
        return (0);
    }
    else if(celula->col > coluna){
        return (0);
    }
    else if(celula->col == coluna){
        return (celula->valor);
    }
    else{
        return (buscacol(celula->prox,coluna));
    }
}

struct matriz * buscacel(struct matriz * celula, int coluna){

    if(celula == NULL){
        return (celula);
    }
    else if(celula->col >= coluna){
        return (celula);
    }
    else{
        aux3 = celula;
        return (buscacel(celula->prox,coluna));
    }
}

float gauss(struct matriz * celula , int numc, int i, float x[],int quociente,float soma){

    if(celula == NULL){
        return(soma/quociente);
    }
    else if(celula->col == i+1){
        quociente = celula->valor;
    }
    else if (celula->col == numc){
        soma = soma + celula->valor;
    }
    else{
        soma = soma - (celula->valor*x[celula->col-1]);
    }
    return(gauss(celula->prox,numc,i,x,quociente,soma));
}

int somalinha2(struct matriz * linha,int soma){

    if(linha==NULL){
        return(soma);
    }
    else{
        if(linha->valor<0){
            soma = soma - linha->valor;
        }
        else{
            soma = soma + linha->valor;
        }
        return(somalinha2(linha->prox,soma));
    }
}

int menu(){ //funcao que abre o menu de opções e retorna a desejada

        //imprime todas as opções na tela
		printf("\nDigite o n%cmero da op%c%co que deseja realizar com sua matriz:",163,135,198);
		printf("\nOp%c%co 1: Imprimir a Matriz",135,198);
		printf("\nOp%c%co 2: Exclus%co",135,198,198);
		printf("\nOp%c%co 3: Consulta de Valor",135,198);
		printf("\nOp%c%co 4: Soma de Linha",135,198);
		printf("\nOp%c%co 5: Soma de Coluna",135,198);
		printf("\nOp%c%co 6: Atribui%c%co de Valor",135,198,135,198);
		printf("\nOp%c%co 7: Determinante",135,198);
		printf("\nOp%c%co 8: Resolver Sistema Linear",135,198);
		printf("\nOp%c%co 9: Encerrar o Programa",135,198);
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

    printf("\nDigite a quantidade de linhas, da colunas, em seguida, entre com a matriz: \n\n");

    scanf("%d %d",&numl,&numc);

    struct matriz ** linha;
    linha = (struct matriz **)malloc(numl*sizeof(struct matriz*));

    for(i=0;i<numl;i++){
        linha[i] = NULL;
    }

    for(i=0;i<numl;i++){
        aux2 = NULL;
        for(j=0;j<numc;j++){
                scanf("%d",&novo);
                if(novo!=0){
                    aux = criacelula(novo,j+1);

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

    int opcao;
    int pl,pc,busca,k=0,det;
    float dif,y;
    int fim = 1;

    while(fim!=2){

        printf("\n\n");
        opcao = menu();

        if (opcao == 1){
            for(i=0;i<numl;i++){
                imprime(linha[i],0,numc);
                printf("\n");
            }
        }

        if (opcao == 2){
            excluir(numl,linha);

            free(linha);

            printf("\nA matriz foi apagada");
            printf("\nDigite a quantidade de linhas, da colunas, em seguida, entre com a matriz: \n\n");

            scanf("%d %d",&numl,&numc);

            linha = (struct matriz **)malloc(numl*sizeof(struct matriz*));

            for(i=0;i<numl;i++){
                linha[i] = NULL;
            }

            for(i=0;i<numl;i++){
                aux2 = NULL;
                for(j=0;j<numc;j++){
                        scanf("%d",&novo);
                        if(novo!=0){
                            aux = criacelula(novo,j+1);

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

        }

        if (opcao == 3){
            printf("\nDigite as posi%c%ces da linha e da coluna: ",135,198);
            scanf("%d %d",&pl,&pc);
            aux = linha[pl-1];
            if(pl<=numl && pl>0 && pc>0 && pc<=numc){
                consulta(linha[pl-1],pc,pl);
            }
            else {
                printf("\nA posi%c%co escolhida n%co est%c definida nessa matriz",135,198,198,160);
            }
        }

        if (opcao == 4){
            printf("\nDigite a linha que deseja somar: ");
            scanf("%d",&pl);
            if(pl>0 && pl<=numl){
                somalinha(linha[pl-1],0);
            }
            else {
                printf("\nA linha escolhida n%co existe nessa matriz",198);
            }
        }

        if (opcao == 5){
            printf("\nDigite a coluna que deseja somar: ");
            scanf("%d",&pc);
            busca = 0;
            if(pc>0 && pc<=numc){
                 for(i=0;i<numl;i++){
                        busca = busca + buscacol(linha[i],pc);
                 }
                 printf("\nSoma = %d",busca);
            }
            else {
                printf("\nA coluna escolhida n%co existe nessa matriz",198);
            }
        }

        if (opcao == 6){
            printf("\nDigite as posi%c%ces da linha, da coluna, e o valor a ser atribuido: ",135,198);
            scanf("%d %d %d",&pl,&pc,&busca);
            if(pl<=numl && pl>0 && pc>0 && pc<=numc){
                if(busca==0){
                    aux = NULL;
                    aux2 = NULL;
                    if(linha[pl-1]!=NULL){
                        aux = linha[pl-1];
                        aux2 = linha[pl-1];
                        if(linha[pl-1]->col == pc){
                            linha[pl-1] = linha[pl-1]->prox;
                            free(aux);
                            aux = NULL;
                        }
                        while(aux != NULL){
                            aux2 = aux;
                            aux = aux->prox;
                            if(aux!=NULL){
                                if(aux->col == pc){
                                    aux2->prox = aux->prox;
                                    free(aux);
                                    aux=NULL;
                                }
                            }
                        }
                    }
                }
                else{
                    aux = NULL;
                    aux3 = linha[pl-1];
                    aux = buscacel(linha[pl-1],pc);
                    printf("\nEndereco aux: %d",aux);
                    printf("\nEndereco aux3: %d",aux3);
                    if(aux!=NULL){
                        if(aux->col==pc){
                            aux->valor = busca;
                        }
                        else if (aux!=aux3){
                            aux2 = criacelula(busca,pc);
                            printf("\nEndereco aux2: %d",aux2);
                            aux2->prox = aux;
                            printf("\nEndereco aux2->prox: %d",aux2->prox);
                            aux3->prox = aux2;
                            printf("\nEndereco aux3->prox: %d",aux3->prox);
                        }
                        else {
                            aux2 = criacelula(busca,pc);
                            aux2->prox = aux;
                            linha[pl-1] = aux2;
                        }
                    }
                    else if (aux != aux3){
                        aux2 = criacelula(busca,pc);
                        printf("\nEndereco aux2: %d",aux2);
                        aux2->prox = aux;
                        printf("\nEndereco aux2->prox: %d",aux2->prox);
                        aux3->prox = aux2;
                        printf("\nEndereco aux3->prox: %d",aux3->prox);
                    }
                    else{
                        aux2 = criacelula(busca,pc);
                        aux2->prox = aux;
                        linha[pl-1] = aux2;
                    }
                }
            }
        }

        if (opcao == 7){ //determinante

        }

        if (opcao == 8){
            det = 0;
            for(i=0;i<numl;i++){
                if(buscacol(linha[i],i+1)>=0){
                        if(buscacol(linha[i],numc)>=0){
                            det = somalinha2(linha[i],0) - 2*buscacol(linha[i],i+1) - buscacol(linha[i],numc);
                        }
                        else{
                            det = somalinha2(linha[i],0) - 2*buscacol(linha[i],i+1) + buscacol(linha[i],numc);
                        }
                }
                else{
                        if(buscacol(linha[i],numc)>=0){
                            det = somalinha2(linha[i],0) + 2*buscacol(linha[i],i+1) - buscacol(linha[i],numc);
                        }
                        else{
                            det = somalinha2(linha[i],0) + 2*buscacol(linha[i],i+1) + buscacol(linha[i],numc);
                        }
                }
            }

            if(det<=0){
                if(numc!=numl+1){
                    printf("\nEssa matriz n%co pode ser resolvida por Gauss-Seidel",198);
                }
                else{
                    float * x;
                    x = (float*)malloc(numc*sizeof(float));
                    for(i=0;i<numc;i++){
                        x[i] = 0;
                    }
                    for(j=0;j<100;j++){
                        dif = 0;
                        y = 0;
                        for(i=0;i<numl;i++){
                            y = x[i];
                            x[i] = gauss(linha[i],numc,i,x,1,0);
                            if(x[i]<0.000001 && x[i]> -0.000001){
                                x[i] = 0.0;
                            }
                            y = x[i] - y;
                            if(y<0){
                                y = -y;
                            }
                            if(y > dif){
                                dif = y;
                            }
                            if(dif<0.000001){
                                j = 100;
                            }
                        }
                    }
                    for(i=0;i<numl;i++){
                            printf("\nx[%d] = %g",i+1,x[i]);
                    }
                    free(x);
                }
            }
            else{
                printf("\nEssa matriz n%co pode ser resolvida por Gauss-Seidel",198);
            }
        }

        if (opcao == 9){
            fim = 2;
        }
    }
    printf("\nPROGRAMA ENCERRADO");
    getch();	            //pausa para leitura da tela
}
