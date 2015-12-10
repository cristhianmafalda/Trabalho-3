#include<stdio.h>
#include<stdlib.h>

struct matriz{                  //declaração da estrutura de cada célula das listas encadeadas
    int valor;                  //valor é o inteiro correspondente com a matriz
    int col;                    //posição da coluna desse elemento na matriz
    struct matriz * prox;       //ponteiro para o próximo da linha
};

struct matriz * aux;            //aux,aux2,aux3 são variáveis que irão auxiliar nas atribuições de ponteiros
struct matriz * aux2;
struct matriz * aux3;

struct matriz * criacelula(int dado, int coluna){   //função que cria uma célula nova e retorna o ponteiro para ela

        struct matriz * novo;
        novo = (struct matriz*)malloc(sizeof(struct matriz));   //aloca a nova célula
        novo->valor = dado;                                     //preenche o valor e a coluna
        novo->col = coluna;
        novo->prox = NULL;                                      //deixa o ponteiro aterrado
        return(novo);
}

void imprime(struct matriz * celula,int colant, int numc){ //função que imprime a matriz esparsa

    int i;
    if(celula==NULL){                   //verifica quando chega ao ultimo valor não nulo da linha
        if (colant!=numc){              //verifica quantos zeros ainda falta imprimir
            for(i=0;i<numc-colant;i++){
                printf("0\t");          //imprime os zeros restantes
            }
        }
        return;
    }
    for(i=1;i<celula->col-colant;i++){  //verifica zeros entre o valor anterior e o atual
            printf("0\t");
    }
    printf("%d\t",celula->valor);       //imprime o valor não nulo
    imprime(celula->prox,celula->col,numc); //recursivo para a célula seguinte
}

void consulta(struct matriz * celula, int coluna, int linha){ //função que recebe uma posição e imprime o valor dela

    if(celula == NULL){             //se chegarmos ao ultimo ponteiro, o valor é zero
        printf("\nValor da posi%c%co (%d,%d) : 0",135,198,linha,coluna);
    }
    else if(celula->col > coluna){  //se passarmos da coluna da posição pedida sem te-lo achado, ele é zero
        printf("\nValor da posi%c%co (%d,%d) : 0",135,198,linha,coluna);
    }
    else if(celula->col == coluna){ //se a coluna do elemento for igual a posição pedida, imprime o valor
        printf("\nValor da posi%c%co (%d,%d) : %d",135,198,linha,coluna,celula->valor);
    }
    else{
        consulta(celula->prox,coluna,linha);    //recursivo para a célula seguinte
    }
}

int consulta2(struct matriz * celula, int coluna){   //função que recebe uma posição e retorna o valor dela

    if(celula == NULL){             //se chegarmos ao ultimo ponteiro, o valor é zero
        return(0);
    }
    else if(celula->col > coluna){  //se passarmos da coluna da posição pedida sem te-lo achado, ele é zero
        return(0);
    }
    else if(celula->col == coluna){ //se a coluna do elemento for igual a posição pedida, imprime o valor
        return(celula->valor);
    }
    else{
        return(consulta2(celula->prox,coluna));   //recursivo para a célula seguinte
    }
}

void excluir(int numlin ,struct matriz *linha[]){   //função que exclui as células de uma matriz esparsa

    int i;
    for(i=0; i<numlin; i++){
            if(linha[i] != NULL){
                aux = linha[i]->prox;           //aux armazena a prox célula
                free(linha[i]);                 //libera a célula atual
                linha[i] = NULL;                //linha deve ser aterrado
                if(aux!=NULL){
                    while(aux->prox !=NULL){    //repete até a linha não ter mais valores não nulos
                        aux2 = aux->prox;       //aux2 é quem armazena a seguinte agora
                        free(aux);              //aux é liberado e aterrado
                        aux = NULL;
                        aux = aux2;             //aux recebe a proxima célula
                    }
                }
                free(aux);
                aux = NULL;
            }
    }
}

void somalinha(struct matriz*linha,int soma){       //função que recebe uma linha, e soma os valores dela

    if(linha==NULL){                                //quando chegar no ponteiro aterrado, todos oa valores foram somados
        printf("\nSoma = %d",soma);
        return;
    }
    else{
        soma = soma + linha->valor;                 //senão, soma o valor atual a variável soma
        return(somalinha(linha->prox,soma));        //e segue para a célula seguinte
    }
}

struct matriz * buscacel(struct matriz * celula, int coluna){ //função de busca que retorna o ponteiro da célula

    if(celula == NULL){                 //se chegarmos ao ultimo ponteiro, ele mesmo retorna
        return (celula);
    }
    else if(celula->col >= coluna){     //se ce passarmos da coluna desejada, ou chegarmos nela, retorna o ponteiro dela
        return (celula);
    }
    else{
        aux3 = celula;                  //aux3 será usado como anterior a célula
        return (buscacel(celula->prox,coluna));     //recursivo para a sequencia
    }
}

float gauss(struct matriz * celula , int numc, int i, float x[],int quociente,float soma){  //função soma de linha para gauss-seidel

    if(celula == NULL){                 //quando chegar ao fim da linha, retorna a soma dividida pelo quociente
        return(soma/quociente);
    }
    else if(celula->col == i+1){
        quociente = celula->valor;      //o quociente será o coeficiente da solução isolada nessa equação
    }
    else if (celula->col == numc){      //soma o valor final sem multiplicar por nenhuma solução
        soma = soma + celula->valor;
    }
    else{
        soma = soma - (celula->valor*x[celula->col-1]); //soma os demais valores multiplicados porsuas respectivas soluções
    }
    return(gauss(celula->prox,numc,i,x,quociente,soma));    //chama a célula seguinte
}

int somalinha2(struct matriz * linha,int soma){ //função que soma os módulos dos valores de uma linha

    if(linha==NULL){    //chegando no último ponteiro, a soma ja foi feita
        return(soma);
    }
    else{
        if(linha->valor<0){
            soma = soma - linha->valor; //se o valor for negativo, subtrai
        }
        else{
            soma = soma + linha->valor; //senão, soma
        }
        return(somalinha2(linha->prox,soma));       //chama a célula seguinte
    }
}

float ** criamatriz(int numl, int numc){    //função que aloca uma matriz dinamicamente
      float **novo;                         //cria a matriz
      int i;
      novo=(float **)malloc(numl*sizeof(float*));       //aloca os espaço para as linhas
      for (i=0;i<numl;i++){
          novo[i]=(float*)malloc(numc*sizeof(float));   //aloca espaço para as colunas em cada linha
      }
  return(novo); //retorna o ponteiro inicial
}

float ** liberamatriz(int numl, int numc, float ** auxdet){ //função que libera uma matriz alocada dinamicamente
  int i;
  for(i=0;i<numc;i++){
        free(auxdet[i]);    //libera as colunas de cada linhas
  }
  free(auxdet);             //libera as linhas
  return(NULL);             //deixa o ponteiro da main aterrado caso precise usar outra vez
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
		while(opcao<1||opcao>9){ //confere a coerencia e refaz se necessario
            printf("\n\nEscolha uma op%c%co existente",135,198);
            printf("\n\nOp%c%co escolhida: ",135,198);
            scanf("%d",&opcao);
		}
		printf("\n");
		return(opcao);    //retorna a opcao
}

void main(){

    int numl,numc,i,j,novo;                 //decalração do numeor de linhas e contadores
    printf("\nDigite a quantidade de linhas, da colunas, em seguida, entre com a matriz: \n\n");
    scanf("%d %d",&numl,&numc);             //le o numero de linhas e colunas
    while(numl<=0 || numc<=0){              //confere e refaz se necessário
        printf("\nValores incoerentes para quantidade de linhas e colunas\nEntre com novos valores ambos maiores que zero, depois a matriz:\n\n");
        scanf("%d %d",&numl,&numc);
    }

    struct matriz ** linha;                 //aloca o ponteiro principal da matriz
    linha = (struct matriz **)malloc(numl*sizeof(struct matriz*));

    for(i=0;i<numl;i++){                    //garantimos que todos os ponteiros de linha iniciem aterrados
        linha[i] = NULL;
    }

    for(i=0;i<numl;i++){                    //vamos adicionar os valores não nulos para cada linha
        aux2 = NULL;
        for(j=0;j<numc;j++){                //e cada coluna
                scanf("%d",&novo);
                if(novo!=0){                //só serão adicionados valores diferentes de zero
                    aux = criacelula(novo,j+1);     //nova célula é criada

                    if(linha[i]==NULL){
                        linha[i] = aux;     //linha irá apontar para o novo valor se ela estiver aterrada
                    }
                    else{
                        aux2 = linha[i];    //senão, nós buscaremos o ultimo ponteiro da linha para adicionar...
                        while(aux2->prox != NULL){  //... visto que a entrada está ordenada por coluna dentro de cada linha
                            aux2 = aux2->prox;
                        }
                        aux2->prox = aux;   //aux2 é o anterior e aponta para aux, que é o novo
                    }
                }
        }
    }

    int pl,pc,busca,k=0,det,cont=0,opcao,fim = 1;
    float dif,y,troca,fator;                //todas variáveis declaradas serão necessárias para execução das funções abaixo
    float ** auxdet;

    while(fim!=2){  //condição para encerrar programa

        printf("\n\n");
        opcao = menu(); //recebe a opção do usuário

        if (opcao == 1){                    //impressão
            for(i=0;i<numl;i++){            //imprime cada linha de uma vez chamando a função imprime
                imprime(linha[i],0,numc);
                printf("\n");
            }
        }

        if (opcao == 2){                    //exclusão
            excluir(numl,linha);            //chama a função que exclui as celulas
            free(linha);                    //libera as linhas

            printf("\nA matriz foi apagada");   //necessita entrar com uma nova matriz para continuar
            printf("\nDigite a quantidade de linhas, da colunas, em seguida, entre com a matriz: \n\n");

            scanf("%d %d",&numl,&numc);     //repete todo o processo de adicionar matriz descrito no inicio da main, logo, não será comentado
            while(numl<=0 || numc<=0){
                printf("\nValores incoerentes para quantidade de linhas e colunas\nEntre com novos valores ambos maiores que zero, depois a matriz:\n\n");
                scanf("%d %d",&numl,&numc);
            }

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

        if (opcao == 3){                    //consulta
            printf("\nDigite as posi%c%ces da linha e da coluna: ",135,198);
            scanf("%d %d",&pl,&pc);         //le a posicao desejada
            aux = linha[pl-1];
            if(pl<=numl && pl>0 && pc>0 && pc<=numc){   //avalia a coerencia da posição
                consulta(linha[pl-1],pc,pl);    //chama a posição que imprime o valor da célula de posição pedida
            }
            else {
                printf("\nA posi%c%co escolhida n%co est%c definida nessa matriz",135,198,198,160);
            }
        }

        if (opcao == 4){                    //soma linha
            printf("\nDigite a linha que deseja somar: ");
            scanf("%d",&pl);                // le a linha desejada
            if(pl>0 && pl<=numl){           //avalia coerencia
                somalinha(linha[pl-1],0);   //chama a função que realiza a soma
            }
            else {
                printf("\nA linha escolhida n%co existe nessa matriz",198);
            }
        }

        if (opcao == 5){                    //soma coluna
            printf("\nDigite a coluna que deseja somar: ");
            scanf("%d",&pc);                //le a coluna
            busca = 0;
            if(pc>0 && pc<=numc){           //avalia coerencia
                 for(i=0;i<numl;i++){       //em cada linha, procuramos a coluna
                        busca = busca + consulta2(linha[i],pc);//acumulamos o valor em busca
                 }
                 printf("\nSoma = %d",busca);   //imprime a soma
            }
            else {
                printf("\nA coluna escolhida n%co existe nessa matriz",198);
            }
        }

        if (opcao == 6){                    //atribuição
            printf("\nDigite as posi%c%ces da linha, da coluna, e o valor a ser atribuido: ",135,198);
            scanf("%d %d %d",&pl,&pc,&busca);           //le a posição e o valor novo
            if(pl<=numl && pl>0 && pc>0 && pc<=numc){   //verifica a posição
                if(busca==0){                           //caso em que vamos adicioanr um 0 a matriz
                    aux = NULL;
                    aux2 = NULL;
                    if(linha[pl-1]!=NULL){              //so precisa fazer alguma coisa se a linha não for toda nula
                        aux = linha[pl-1];
                        aux2 = linha[pl-1];
                        if(linha[pl-1]->col == pc){     //checa se o primeiro valor não nulo é o que vai ser trocado
                            linha[pl-1] = linha[pl-1]->prox;    //se for, a linha aponta pro seguinte
                            free(aux);                  //a posição é apagada da matriz e aux aterrado
                            aux = NULL;
                        }
                        while(aux != NULL){             //se não for o primeiro valor, vamos buscar o valor na matriz
                            aux2 = aux;
                            aux = aux->prox;            //aux2 é o anterior
                            if(aux!=NULL){
                                if(aux->col == pc){     //quando achar a posição
                                    aux2->prox = aux->prox; //aux2 aponta pra quem aux aponta
                                    free(aux);              //libera aux a aterra
                                    aux=NULL;
                                }
                            }
                        }
                    }
                }
                else{                                   //caso em que vamos adiconar um valor não nulo
                    aux = NULL;
                    aux3 = linha[pl-1];
                    aux = buscacel(linha[pl-1],pc);
                    if(aux!=NULL){
                        if(aux->col==pc){               //se a posição ja esta preenchida, apenas substituimos o valor
                            aux->valor = busca;
                        }
                        else if (aux!=aux3){            //se não, temos que encontrar a posição que ele ocuparia
                            aux2 = criacelula(busca,pc);    //criar uma nova celula
                            aux2->prox = aux;               //fazer o anterior apontar
                            aux3->prox = aux2;
                        }
                        else {                          //caso em que a nova celula é inserida entre a linha e o primeiro não nulo da linha
                            aux2 = criacelula(busca,pc);
                            aux2->prox = aux;
                            linha[pl-1] = aux2;
                        }
                    }
                    else if (aux != aux3){              //caso em que a buscacel retorna NULL para o meio da matriz
                        aux2 = criacelula(busca,pc);
                        aux2->prox = aux;
                        aux3->prox = aux2;
                    }
                    else{                               //caso em que buscacel retorna NULL e a celula será o primeiro nao nulo da linha
                        aux2 = criacelula(busca,pc);
                        aux2->prox = aux;
                        linha[pl-1] = aux2;
                    }
                }
            }
        }

        if (opcao == 7){                    //determinante

            if(numc==numl){                 // checa se a matriz é quadrada
                auxdet = criamatriz(numl,numc); //aloca uma matriz quadrada
                cont = 0;                       //se não reinicializar, inverte o sinal do determinante em alguns casos
                for(i=0;i<numl;i++){        // este ciclo for preenche um vetor bidimensional da matriz armazenada em linha
                    for(j=0;j<numl;j++){
                            auxdet[i][j] = consulta2(linha[i],j+1);
                    }
                }
                for(i=0;i< numl-1;i++){     // tranforma a matriz em uma matriz triangular superior de determinante equivalente ao da matriz original
                    if(auxdet[i][i]==0){    // neste caso, não é possível encontrar o fator, pois não há divisão por zero
                        for(k=i;k<numl;k++){
                            if(auxdet[k][i] != 0){  //realiza apenas quando a posição não for nula
                                for(j=0;j<numl;j++){
                                    troca = auxdet[i][j];   //inverte as posições
                                    auxdet[i][j] = auxdet[k][j];
                                    auxdet[k][j] = troca;
                                }
                                k = numl;
                            }
                        }
                        cont = cont +1;
                    }
                    if(auxdet[i][i] != 0){  // neste caso é possível encontrar o fator
                        for(k=i+1;k <numl;k++){
                            fator = -auxdet[k][i]/auxdet[i][i];
                            for(j=i;j<numl;j++){
                                auxdet[k][j] = auxdet[k][j]+(fator*auxdet[i][j]);
                            }
                        }
                    }
                }
                                        // nesta parte, a matriz já é triangular superior, logo, seu determinante é o produto da diagonal principal
                troca = 1.0;            //troca deve ser inicalizado como 1 para não dar erro
                for(i=0;i<numl;i++){
                    troca = troca*auxdet[i][i];     //o determinante é o produto dos valores da diagonal principal
                }
                printf("\nDeterminante : ");    // imprime o valor do determinante
                if(troca!=0.0){                 //condição pra evitar sinal desnecessário
                    if(cont % 2 == 0){          //define o sinal do determinante
                        printf("%g\n",troca);
                    }
                    else{
                        printf("%g\n",-troca);
                    }
                }
                else{
                    printf("0\n");
                }
                auxdet = liberamatriz(numl,numc,auxdet);    ;// a memória ocupada pela matriz é liberada
            }
            else{                               // caso a matriz não seja quadrada, não existe determinante
             printf("\nEssa matriz n%co possui determinante",198);
            }
        }

        if (opcao == 8){                    //sistema linear
            det = 0;
            for(i=0;i<numl;i++){            //primeiro vamos fazer o teste de diagonal dominante na matriz
                if(consulta2(linha[i],i+1)>=0){ //em toda linha, a soma da linha menos duas vezes o coeficeinte da solução menos o resultado deve ser menor que 0
                        if(consulta2(linha[i],numc)>=0){    //as condições são feitas para acertar o sinal dos coeficiente da solução e do resultado
                            det = somalinha2(linha[i],0) - 2*consulta2(linha[i],i+1) - consulta2(linha[i],numc);
                        }
                        else{
                            det = somalinha2(linha[i],0) - 2*consulta2(linha[i],i+1) + consulta2(linha[i],numc);
                        }
                }
                else{
                        if(consulta2(linha[i],numc)>=0){
                            det = somalinha2(linha[i],0) + 2*consulta2(linha[i],i+1) - consulta2(linha[i],numc);
                        }
                        else{
                            det = somalinha2(linha[i],0) + 2*consulta2(linha[i],i+1) + consulta2(linha[i],numc);
                        }
                }
            }

            if(det<=0){                     //agora sabemos se podemos ou não aplicar Gauss-Seidel
                if(numc!=numl+1){           //teste dimensional da matriz
                    printf("\nEssa matriz n%co pode ser resolvida por Gauss-Seidel",198);
                }
                else{
                    float * x;              //x é o vetor das soluções, alocado dinamicamente
                    x = (float*)malloc(numc*sizeof(float));
                    for(i=0;i<numc;i++){
                        x[i] = 0;           //todas as soluções são incializadas com zero
                    }
                    for(j=0;j<100;j++){     //caso a solução não alcance a diferença minima, ela para após 100 processos
                        dif = 0;            //diferenca maxima entre as soluções antigas e novas
                        y = 0;              //auxilia o cálculo da diferenca maxima
                        for(i=0;i<numl;i++){
                            y = x[i];
                            x[i] = gauss(linha[i],numc,i,x,1,0); // a solução recebe seu novo valor
                            if(x[i]<0.000001 && x[i]> -0.000001){   //para evitar exponenciais
                                x[i] = 0.0;
                            }
                            y = x[i] - y;                       //y é a diferença entre o valor antigo e novo
                            if(y<0){                            // módulo de y
                                y = -y;
                            }
                            if(y > dif){                        //dif recebe a maior entre as diferenças
                                dif = y;
                            }
                            if(dif<0.000001){                   //se a diferença maxima for menor que a menor unidade do float(dif minima), para o processo
                                j = 100;                        //o processo somente repete 100 vezes se a solução não estiver convergindo
                            }
                        }
                    }
                    for(i=0;i<numl;i++){                        //imprime as soluções
                            printf("\nx[%d] = %g",i+1,x[i]);
                    }
                    free(x);                                    //libera o vetor
                }
            }
            else{
                printf("\nEssa matriz n%co pode ser resolvida por Gauss-Seidel",198);
            }
        }

        if (opcao == 9){                    //encerrar
            fim = 2;                        // muda condição do while
            excluir(numl,linha);            //exclui as celulas
            free(linha);                    //libera linhas
        }
    }
    printf("\nPROGRAMA ENCERRADO");
    getch();	            //pausa para leitura da tela
}
