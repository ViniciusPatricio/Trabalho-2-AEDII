/*
Al: VINICIUS PATRICIO MEDEIROS DA SILVA
Nº: 21951799
Curso: ENGENHARIA DA COMPUTAÇÃO
*/

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define MAX 3  // número max de chaves
#define true 1
#define false 0
// ***********************       Funções auxiliares        *********************** //
int numeroRepetido(int vetorchaves[], int numero_chaves, int entrada){
    int flag = 0;
    for(int i = 0; i< numero_chaves;i++){
        if(vetorchaves[i] == entrada){
            flag = 1;
            break;
        }
    }
    return flag;
}


// *********************** Etrutura para árvores multiway  *********************** //

typedef struct no NO;
struct no{
    int num_chaves; // numero de chaves guardadas
    int chaves[MAX]; // lista que armazena as chaves
    NO *filhos[MAX+1]; // vetor de ponteros que guarda o endereço dos filhos do nó
};

NO *criarNo(){ // criando um no pela primeira vez
    
    // alocando espaço na memoria para novo nó
    NO *novo_no = (NO*)malloc(sizeof(NO));
    novo_no->num_chaves = 0;
  
    for(int i = 0; i <= MAX;i++){ // como ele é um novo nó, então ele não tem filhos, dessa forma os elementos do vetor de filhos recebem NULL;
        novo_no->filhos[i] = NULL;
    }

    return novo_no;
}


void inserirNo(NO *no,int num){
    if(no->num_chaves == 0){ // caso ele seja o primeiro elemento do nó
        no->chaves[0] = num;
    }else{
        int cont = 0;
        while(cont < no->num_chaves && num > no->chaves[cont]){
            cont++;
        }
        for(int i = no->num_chaves; i>cont ;i--){ // empurra os elementos do vetor para pode inserir ordenado
            no->chaves[i]=no->chaves[i-1];
        }
        no->chaves[cont] = num;
    }
    
    no->num_chaves++;
}





int raizTemFilho(NO *raiz){  // verifica se a raiz tem filho 
    int flag = 0;
    for(int i = 0; i < MAX; i++){
        if(raiz->filhos[i]!=NULL){
            flag = 1;
            break;
        }   
    }
    return flag;
}

NO *split1(NO *raiz){

    NO *filho_esq = criarNo();
        inserirNo(filho_esq,raiz->chaves[0]);
        filho_esq->filhos[0] = raiz->filhos[0];
        filho_esq->filhos[1] = raiz->filhos[1];

        NO *filho_dir = criarNo();
        inserirNo(filho_dir,raiz->chaves[2]);
        filho_dir->filhos[0] = raiz->filhos[2];
        filho_dir->filhos[1] = raiz->filhos[3];

        NO *nova_raiz = criarNo();
        inserirNo(nova_raiz,raiz->chaves[1]);
        nova_raiz->filhos[0]=filho_esq;
        nova_raiz->filhos[1]=filho_dir;

        free(raiz);
        return nova_raiz;
}

NO *split2(NO *raiz){  // raiz tem um único elemento e estamos inserindo a esquerda
 


    NO *filho_esq = criarNo();          // criando o filho a esquerda
    inserirNo(filho_esq,raiz->filhos[0]->chaves[0]);
    filho_esq->filhos[0] = raiz->filhos[0]->filhos[0];
    filho_esq->filhos[1] = raiz->filhos[0]->filhos[1];

    NO *filho_meio= criarNo();          // criando o filho do meio
    inserirNo(filho_meio,raiz->filhos[0]->chaves[2]);
    filho_meio->filhos[0]=raiz->filhos[0]->filhos[2];
    filho_meio->filhos[1]=raiz->filhos[0]->filhos[3];

    inserirNo(raiz,raiz->filhos[0]->chaves[1]);
    free(raiz->filhos[0]);
    raiz->filhos[0] = filho_esq;
    raiz->filhos[2] = raiz->filhos[1];  
    raiz->filhos[1] = filho_meio;


    return raiz;
}

NO *split3(NO *raiz){ // raiz tem apenas uma unica chave e possui um filho com 3 chaves maiores que o da raiz
    NO *filho_meio = criarNo();
    inserirNo(filho_meio,raiz->filhos[1]->chaves[0]);
    filho_meio->filhos[0]=raiz->filhos[1]->filhos[0];
    filho_meio->filhos[1]=raiz->filhos[1]->filhos[1];

    NO *filho_dir = criarNo();
    inserirNo(filho_dir,raiz->filhos[1]->chaves[2]); 
    filho_dir->filhos[0]=raiz->filhos[1]->filhos[2];
    filho_dir->filhos[1]=raiz->filhos[1]->filhos[3];

    inserirNo(raiz,raiz->filhos[1]->chaves[1]);

    raiz->filhos[1] = filho_meio;
    raiz->filhos[2] = filho_dir;

    return raiz;

}


NO *split4(NO *raiz){ //raiz com duas chaves e com um filho  mais a esquerda com três chaves 

    NO *filho_esq=criarNo();
    inserirNo(filho_esq,raiz->filhos[0]->chaves[0]);
    filho_esq->filhos[0]=raiz->filhos[0]->filhos[0];
    filho_esq->filhos[1]=raiz->filhos[0]->filhos[1];

    NO *filho_esq2=criarNo();
    inserirNo(filho_esq2,raiz->filhos[0]->chaves[2]);
    filho_esq2->filhos[0]=raiz->filhos[0]->filhos[2];
    filho_esq2->filhos[1]=raiz->filhos[0]->filhos[3];

    inserirNo(raiz,raiz->filhos[0]->chaves[1]);
    raiz->filhos[3]=raiz->filhos[2];
    raiz->filhos[2]=raiz->filhos[1];
    raiz->filhos[1]=filho_esq2;
    raiz->filhos[0]=filho_esq;
    
    return raiz;
}

NO *split5(NO *raiz){ //
  NO *filho_esq2=criarNo();
  inserirNo(filho_esq2,raiz->filhos[1]->chaves[0]);
  filho_esq2->filhos[0]=raiz->filhos[1]->filhos[0];
  filho_esq2->filhos[1]=raiz->filhos[1]->filhos[1];

  NO *filho_dir2=criarNo();
  inserirNo(filho_dir2,raiz->filhos[1]->chaves[2]);
  filho_dir2->filhos[0]=raiz->filhos[1]->filhos[2];
  filho_dir2->filhos[1]=raiz->filhos[1]->filhos[3];

  inserirNo(raiz,raiz->filhos[1]->chaves[1]);

  raiz->filhos[3]=raiz->filhos[2];
  raiz->filhos[2]=filho_dir2;
  raiz->filhos[1]=filho_esq2;

  return  raiz;
}

NO *split6(NO *raiz){ // raiz com duas chaves filho a direita cheio
  
  NO *filho_dir2=criarNo();
  inserirNo(filho_dir2,raiz->filhos[2]->chaves[0]);
  filho_dir2->filhos[0]=raiz->filhos[2]->filhos[0];
  filho_dir2->filhos[1]=raiz->filhos[2]->filhos[1];

  NO *filho_dir1=criarNo();
  inserirNo(filho_dir1,raiz->filhos[2]->chaves[2]);
  filho_dir2->filhos[0]=raiz->filhos[2]->filhos[2];
  filho_dir2->filhos[1]=raiz->filhos[2]->filhos[3];

  inserirNo(raiz,raiz->filhos[2]->chaves[1]);
  raiz->filhos[2]=filho_dir2;
  raiz->filhos[3]=filho_dir1;

  return raiz;
}

NO *inserirArvore(NO *raiz, int num){

    if(raiz == NULL){  // caso a raiz/nó for nulo, irá criar uma raiz/nó nova

        NO *raiz_nova=criarNo();
        inserirNo(raiz_nova,num);

        return raiz_nova;
    }
    if(raizTemFilho(raiz)==false && raiz->num_chaves < 3){
        if(numeroRepetido(raiz->chaves,raiz->num_chaves,num) == false){ // caso esse número não seja repetido ele será inserido
            inserirNo(raiz,num);
        }
        return raiz;
    }if(raizTemFilho(raiz)==true || raiz->num_chaves==3){ // se a raiz/nó tem filho ou já está lotado de chaves
        
        if(raiz->num_chaves == 3){ // irá fazer a divisão quando a raiz fica cheia
           raiz = split1(raiz);
        }
        
        int indice_filho = 0;
        while( indice_filho < raiz->num_chaves && num > raiz->chaves[indice_filho]){
            indice_filho++;
        }
        if(numeroRepetido(raiz->filhos[indice_filho]->chaves, raiz->filhos[indice_filho]->num_chaves, num)==false){
        if(raiz->filhos[indice_filho]->num_chaves==3 && raizTemFilho(raiz->filhos[indice_filho])==false){
            if(raiz->num_chaves == 1 && indice_filho == 1){
                raiz = split3(raiz);
                raiz = inserirArvore(raiz,num);
            }
            else if(raiz->num_chaves == 1 && indice_filho == 0){
                raiz = split2(raiz);
                raiz = inserirArvore(raiz,num);
            }
            else if(raiz->num_chaves == 2 && indice_filho == 0){
                raiz = split4(raiz);
                raiz = inserirArvore(raiz,num);

            }
            else if(raiz->num_chaves == 2 && indice_filho == 1){
                raiz = split5(raiz);
                raiz = inserirArvore(raiz,num);
            }
            else if(raiz->num_chaves == 2 && indice_filho == 2){
                raiz = split6(raiz);
                raiz = inserirArvore(raiz,num);
                
            }
      
        }else{
            raiz->filhos[indice_filho] = inserirArvore(raiz->filhos[indice_filho],num);
        }
      }else{
        return  raiz;
      }
    }

    return raiz;
}

void imprimirChaves(NO *raiz){
  for(int i = 0;i<raiz->num_chaves;i++){
    printf("%d ",raiz->chaves[i]);
  }
   printf("\n");
}
void imprimirArvore(NO *raiz, int nivel){
  if(raiz == NULL){
    return ;
  }
  for(int i=0;i<raiz->num_chaves;i++){
    imprimirArvore(raiz->filhos[i],nivel+1);
    printf("Nivel: %d|",nivel);
    printf("Pos: %d| %d \n",i,raiz->chaves[i]);
  }
  printf("\n");
  imprimirArvore((raiz->filhos[raiz->num_chaves]),nivel+1);
}

void imprimirArvore2(NO *raiz){
  if(raiz==NULL){
    return;
  }
  int i;
  for(i = 0; i<raiz->num_chaves;i++){
    imprimirArvore2(raiz->filhos[i]);
    printf("%d",raiz->chaves[i]);
  }
  imprimirArvore2(raiz->filhos[raiz->num_chaves]);
}

int main(){
  NO *raiz = criarNo(); // raiz da árvore
  srand(time(NULL));

  for(int i = 0;i<300;i++){
    int num = 1+(rand() % 9000);
    
    raiz=inserirArvore(raiz,num);
  }
  
  imprimirArvore2(raiz);
}  
