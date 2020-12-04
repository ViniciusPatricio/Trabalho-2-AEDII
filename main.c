/*
Al: VINICIUS PATRICIO MEDEIROS DA SILVA
Nº: 21951799
Curso: ENGENHARIA DA COMPUTAÇÃO
*/

#include "stdio.h"
#include "stdlib.h"

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
    NO *novo_no = malloc(sizeof(NO));
    novo_no->num_chaves = 0;
    novo_no->filhos[MAX+1] = malloc((MAX+1)*sizeof(NO));
    // 


    for(int i = 0; i < MAX;i++){ // como ele é um novo nó, então ele não tem filhos, dessa forma os elementos do vetor de filhos recebem NULL;
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

// ***********************    Rotações    *********************** //
NO *split1(NO *no){ // ira dividir o nó em outras duas ramificações quando o nó estiver cheio de chaves   
     
    NO *novo_no = criarNo();  // criando o novo nó depois de efetuar a divisão/quebra
    inserirNo(novo_no,no->chaves[1]);

    NO *filho_esq = criarNo(); // criando o filho esquerdo do novo no
    inserirNo(filho_esq,no->chaves[0]);
    filho_esq->filhos[0] = no->filhos[0]; // atualizando os filhos
    filho_esq->filhos[1] = no->filhos[1];

    NO *filho_dir = criarNo(); // criando o filho direito do novo no
    inserirNo(filho_dir,no->chaves[2]);
    filho_dir->filhos[0] = no->filhos[2];
    filho_dir->filhos[1] = no->filhos[3];

    novo_no->filhos[0] = filho_esq;
    novo_no->filhos[1] = filho_dir;    

    free(no);

    return novo_no;  
}







NO *inserirArvore(NO *raiz, int num){

    if(raiz == NULL){  // caso a raíz seja nula, como será uma chamada recursiva, irá verificar também se a sub-árvore é nula também
        NO *novo_no = criarNo(); // criando um novo nó     
        inserirNo(novo_no,num); // inserindo o elemento no novo nó           
        return novo_no;  // retornando o nó
    }
    else if(raiz->num_chaves < MAX){ // irá preencher  a raiz/ nó enquanto ele não estiver cheio
        
        if(numeroRepetido(raiz->chaves,raiz->num_chaves,num) == false){  // ele só vai inserir um elemento caso ele não esteja no nó 
            inserirNo(raiz,num); 
        }
        if(raiz->num_chaves == MAX){
            raiz = split1(raiz);
        }
        return raiz;

    }else{
       
       
        int contador = 0; // esse variável irá nos dizer em que filho devemos inserir o novo número após o nó pai ficar cheio 
        
        while(num > raiz->chaves[contador] && contador<=MAX){
            contador++;
        }
        return raiz;
    }

}


int main(){
    NO *raiz = NULL; // raiz da árvore
    
    raiz = inserirArvore(raiz,3);
    raiz = inserirArvore(raiz,5);
    raiz = inserirArvore(raiz,2);
    
    
    for(int i = 0 ; i < raiz->num_chaves;i++){
        printf("%d ",raiz->chaves[i]);
    };
   
}  
