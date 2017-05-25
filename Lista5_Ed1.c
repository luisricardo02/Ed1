#include <stdio.h>
#include <stdlib.h>

struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Lista;
typedef struct newNode Elem;


		//Métodos auxiliares
//VERIFICA SE A LISTA ESTÁ VAZIA
int lista_vazia(Lista* li){
	if(li == NULL){
		return 1;
	}
	if(*li == NULL){
		return 1;
	}
	return 0;
}

//RETORNA O TAMANHO DA LISTA
int tamanho_lista(Lista* li){
	if(li == NULL){
		return 0;
	}
	int cont = 0;
	Elem* aux = *li;
	while(aux != NULL){
		cont++;
		aux = aux->prox;
	}
	return cont;
}

//insere  um nó começo da lista, fazendo as alterações necessárias.
int insere_lista_inicio(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	no->prox = (*li);
	*li = no;
	return 1;
}

//Insere no meio da lista.
int insere_lista_meio(Lista* li, struct cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	if(lista_vazia(li)){
		no->prox = (*li);
		*li = no;
		return 1;
	}else{
	int cont1 = 0;
	int cont2 = 0;
	Elem* auxAnt = *li;
	Elem* auxPost = *li;
	while(cont1 != (pos-1)){
		auxAnt = auxAnt->prox;
		cont1++;
	}
	while(cont2 != (pos)){
		auxPost	= auxPost->prox;
		cont2++;
	}
	auxAnt->prox = no;
	no->prox = auxPost;
	}
	return 1;
}

//INSERIR NO FINAL SA LISTA
int insere_lista_final(Lista* li, struct  cliente c){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados= c;
	no->prox = NULL;
	if (lista_vazia(li)){
		*li = no;
	} else{
		Elem *aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
	}
	return 1;
}

//Remove um elemento do final da lista
int remove_lista_final(Lista* li){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	Elem *ant, *no = *li;
	while(no->prox != NULL){
		ant = no;
		no = no->prox;
	}
	if(no == (*li)){
		*li = no->prox;
	}else{
		ant->prox = no->prox;
	}
	free(no);
	return 1;
}

			//Métodos da lista de exercícios
//Cria a cabeça de uma lista e faz ela apontar para nulo.
Lista* Criar_lista_vazia(){
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

// 2ª QUESTÃO
//Insere um elemento em qualquer posição da lista
int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, struct cliente c, int pos){
	int x = tamanho_lista(li);
	if (pos == 0 || pos > x){
		insere_lista_inicio(li,c);
	}
	if (0 < pos && pos < x){
		insere_lista_meio(li,c,pos);
	}
	if (pos == x){
		insere_lista_final(li,c);
	}
}


// 2B - Remove um elemento qualquer da lista: desaloca uma memória e muda o prox necessários.
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int cpf){
	if(li == NULL){
		return 0;
	}
	Elem *ant = *li;
	Elem *no = *li;
	while(no != NULL && no->dados.cpf != cpf){
		ant = no;
		no = no->prox;
	}
	if(no == NULL){
		return 0;
	}
	if(no == *li){									/
		*li = no->prox;
	}else{
		ant->prox = no->prox;
	}
	int cpfRemovido = no->dados.cpf;
	free(no);
	return cpfRemovido;
}

//bUSCA E RETORNA A POSIÇÃO DO CLIENTE SE EXISTIR
int Buscar_a_posicao_de_um_elemento_na_lista(Lista* li, struct cliente c){
	if(li == NULL){
		return -1;
	}
	Elem *no = *li;
	int cont = 0;
	while(no != NULL && no->dados.cpf != c.cpf){
		cont++;
		no = no->prox;
	}
	if(no == NULL){
		return -1;
	}else{
		return cont;
	}
}


//IMPRIMIR TODOS OS ELEMENTOS DA LISTA
void Imprimir_todos_os_elementos_da_lista(Lista* li){
	if(li == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}


//Desaloca a memória de cada no que essa lista possui, um por um.
void Deletar_lista(Lista* li){
	if(li != NULL){
		Elem* no;
		while((*li) != NULL){
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}

		//Main
int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};
	struct cliente isa = {"isa", 102};
	struct cliente lar = {"lar", 103};
	struct cliente Elias = {"Eli", 104};

	Lista* li = Criar_lista_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere ana	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, ana, 3);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere lar na pos 1-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, lar, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Busca pos da ana    -----\n");
	int x = Buscar_a_posicao_de_um_elemento_na_lista(li, ana);
	printf("Posicao: %d\n", x);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remove lar da lista -----\n");
	int y = Remover_um_elemento_de_qualquer_posicao_da_lista(li, 103);
	printf("cpf removido: %d\n", y);
	Imprimir_todos_os_elementos_da_lista(li);
	Deletar_lista(li);

}



//3 QUESTÃO

struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Pilha;
typedef struct  newNode Elem;

		// Métodos Auxiliares
//Nos informa o tamanho da pilha
int tamanho_pilha(Pilha* pi){
	if(pi == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = *pi;
	while (no != NULL){
		cont ++;
		no = no->prox;
	}
	return cont;
}

//Verifica se a pilha está vazia.
int pilha_vazia(Pilha* pi){
	if(pi == NULL){
		return 1;
	}
	if(*pi = NULL){
		return 1;
	}
	return 0;
}

//Imprime a pilha

void Imprimir_pilha(Pilha* pi){
	if(pi == NULL){
		return;
	}
	Elem* aux = *pi;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}

		//Métdos dos exercícios,
//Cria uma pilha apenas com a cabeça.
Pilha*	Criar_pilha_vazia(){
	Pilha *pi = (Pilha*) malloc(sizeof(Pilha));
		*pi = NULL;
	return pi;
}

//Insere um elemento no início da pilha.
int Inserir_um_elemento_em_qualquer_na_pilha(Pilha* pi, struct cliente c){
	if(pi == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = (*pi);
	*pi = no;

}

//Remove um elemento no início da pilha
int Remover_um_elemento_da_pilha(Pilha* pi){
	if(pi == NULL){
		return 0;
	}
	if((*pi) == NULL){
		return 0;
	}
	Elem *no = *pi;
	int cpfRemovido = no->dados.cpf;
	*pi = no->prox;
	free(no);
	return cpfRemovido;
}

//Deleta um a um os nós da lista
void Deletar_pilha(Pilha*pi){
	if(pi != NULL){
		Elem* no;
		while((*pi) != NULL){
			no = *pi;
			*pi = (*pi) ->prox;
			free(no);
		}
		free(pi);
	}
}

int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};

	Pilha *pi = Criar_pilha_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, ana);
	Imprimir_pilha(pi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_pilha(pi, bia);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remover	-----	-----\n");
	int x = Remover_um_elemento_da_pilha(pi);
	printf("Cpf Removido: %d\n", x);
	Imprimir_pilha(pi);
}



//4ª QUESTÃO

struct cliente{
	char nome[30];
	int cpf;
};

struct fila{						//Duas cabeças.
	struct newNode* inicio;
	struct newNode* final;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};

typedef struct fila Fila;
typedef struct  newNode Elem;

    //Métodos auxiliares
//Informa o tamanho da Fila
int tamanho_fila(Fila* fi){
	if(fi == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = fi->inicio;
	while(no != NULL){
		cont++;
		no = no->prox;
	}
	return cont;
}


//verificar se a fila está vazia
int fila_vazia(Fila* fi){
	if(fi == NULL){
		return 1;
	}
	if(fi->inicio == NULL){
		return 1;
	}
	return 0;
}


//imprimir a fila
void Imprimir_fila(fila* fi){
	if(fi == NULL){
		return;
	}
	Elem* aux = fi->inicio;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}


//Métodos da lista de exercícios
//Cria uma Fila vazia
Fila* Criar_fila_vazia(){
	Fila* fi = (Fila*) malloc(sizeof(Fila));
	if(fi != NULL){
		fi->final = NULL;
		fi->inicio = NULL;
	}
	return fi;
}

//Insere um elemento no final da fila.
int Inserir_um_elemento_em_qualquer_na_fila(Fila* fi, struct cliente c){
	if(fi == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = NULL;
	if(fi->final == NULL){
		fi->inicio = no;
	} else{
		fi->final->prox = no;
	}
	fi->final = no;
	return 1;
}

//Remove um elemento de uma pilha.
int Remover_um_elemento_da_fila(Fila* fi){
	if(fi == NULL){
		return 0;
	}
	if(fi->inicio == NULL){
		return 0;
	}
	Elem *no = fi->inicio;
	fi->inicio = fi->inicio->prox;
	int cpfRemovido = no->dados.cpf;
	if(fi->inicio == NULL){
		fi->final = NULL;
	}
	free(no);
	return cpfRemovido;
}

//Deleta uma Fila
void Deletar_fila(Fila* fi){
	if(fi != NULL){
		Elem* no;
		while(fi->inicio != NULL){
			no = fi->inicio;
			fi->inicio = fi->inicio->prox;
			free(no);
		}
		free(fi);
	}
}

int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};

	Fila *fi = Criar_fila_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi, ana);
	Imprimir_fila(fi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Inserir	-----	-----\n");
	Inserir_um_elemento_em_qualquer_na_fila(fi, bia);
	Imprimir_fila(fi);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remover	-----	-----\n");
	int x = Remover_um_elemento_da_fila(fi);
	printf("Cpf Removido: %d\n", x);
	Imprimir_fila(fi);

}

//5ª QUESTÃO

struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct newNode *ant;
	struct cliente dados;
	struct newNode *prox;
};
typedef struct newNode* Lista;
typedef struct  newNode Elem;


//Métodos auxiliares
//Informa o tamanho da lista
int tamanho_lista(Lista* li){
	if(li == NULL){
		return 0;
	}
	int cont = 0;
	Elem*no = *li;
	while(no != NULL){
		cont++;
		no = no->prox;
	}
	return cont;
}

//Verifica se a lista está vazia
int lista_vazia(Lista *li){
	if(li == NULL){
		return 1;
	}
	if(*li == NULL){
		return 1;
	}
	return 0;
}

//Insere no inicio da lista duplamente encadeada
int insere_lista_inicio(Lista *li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = (*li);
	no->ant = NULL;
	if(*li != NULL){
		(*li)->ant = no;
	}
	*li = no;
	return 1;
}


//Insere no final da lista duplamente encadeada
int insere_lista_final(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	no->prox = NULL;
	if((*li) == NULL){
		no->ant = NULL;
		*li = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != NULL){
			aux = aux->prox;
		}
		aux->prox = no;
		no->ant = aux;
	}
	return 1;
}

//Insere no meio da lista
int insere_lista_meio(Lista* li, struct cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	if(lista_vazia(li)){
		no->ant = NULL;
		*li = no;
		return 1;
	}else{
	int cont1 = 0;
	int cont2 = 0;
	Elem* auxAnt = *li;
	Elem* auxPost = *li;
	while(cont1 != (pos-1)){
		auxAnt = auxAnt->prox;
		cont1++;
	}
	while(cont2 != (pos)){
		auxPost	= auxPost->prox;
		cont2++;
	}
	auxAnt->prox = no;
	no->ant = auxAnt;
	no->prox = auxPost;
	auxPost->ant = no;
	}
	return 1;
}


    //Métodos da lista de exercícios
//Cria uma lista duplamente encadeada.
Lista*	Criar_lista_vazia(){
	Lista* li = (Lista*) malloc (sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Insere um cliente em qualquer posição da lista.
int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, struct cliente c, int pos){
	int x = tamanho_lista(li);
	if (pos == 0 || pos > x){
		insere_lista_inicio(li,c);
	}
	if (0 < pos && pos < x){
		insere_lista_meio(li,c,pos);
	}
	if (pos == x){
		insere_lista_final(li,c);
	}
}

//Remove um elemento de qualquer posição da lista duplamente encadeada
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista* li, int cpf){
	if(li == NULL){
		return 0;
	}
	Elem *ant = *li;
	Elem *no = *li;
	while(no != NULL && no->dados.cpf != cpf){
		ant = no;
		no = no->prox;
	}
	if(no == NULL){
		return 0;
	}
	if(no == *li){
		*li = no->prox;
	}else{
		ant->prox = no->prox;
		if(no->prox != NULL){
			no->prox->ant = ant;
		}
	}
	int cpfRemovido = no->dados.cpf;
	free(no);
	return cpfRemovido;
}


//Retorna a posição de um elemento na lista duplamente encadeada.
int Buscar_a_posicao_de_um_elemento_na_lista(Lista* li, struct cliente c){
	if(li == NULL){
		return -1;
	}
	Elem *no = *li;
	int cont = 0;
	while(no != NULL && no->dados.cpf != c.cpf){
		cont++;
		no = no->prox;
	}
	if(no == NULL){
		return -1;
	}else{
		return cont;
	}
}

//Imprime todos os elementos da lista
void Imprimir_todos_os_elementos_da_lista(Lista* li){
	if(li == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	while(aux != NULL){
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	}
}

//Deleta uma lista duplamente encadeada
void Deletar_lista(Lista *li){
	if(li != NULL){
		Elem* no;
		while((*li) != NULL){
			no = *li;
			*li = (*li)->prox;
			free(no);
		}
		free(li);
	}
}


int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};


	Lista* li = Criar_lista_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere ana	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, ana, 3);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere bia	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, bia, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Busca pos da ana    -----\n");
	int x = Buscar_a_posicao_de_um_elemento_na_lista(li, ana);
	printf("Posicao: %d\n", x);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remove bia da lista -----\n");
	int y = Remover_um_elemento_de_qualquer_posicao_da_lista(li, 101);
	printf("cpf removido: %d\n", y);
	Imprimir_todos_os_elementos_da_lista(li);
	Deletar_lista(li);
}

//6ª QUESTÃO


struct cliente{
	char nome[30];
	int cpf;
};

struct newNode{
	struct cliente dados;
	struct newNode *prox;
};

typedef struct newNode* Lista;
typedef struct  newNode Elem;

    //Métodos auxiliares
//Informa o tamanho da lista circular
int tamanho_lista(Lista* li){
	if(li == NULL || (*li) == NULL){
		return 0;
	}
	int cont = 0;
	Elem* no = *li;
	do{
		cont++;
		no = no->prox;
	} while(no != (*li));
	return cont;
}

//Insere na lista circular
int lista_vazia(Lista* li){
	if(li == NULL && (*li) == NULL){
		return 1;
	}
	else {
		return 0;
	}
}

//insere no inicio da lista circular.
int insere_lista_inicio(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	if((*li) == NULL){
		*li = no;
		no->prox = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != (*li)){
			aux = aux->prox;
		}
		aux->prox = no;
		no->prox = *li;
		*li = no;
	}
	return 1;
}

//insere no final da lista circular
int insere_lista_final(Lista* li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	Elem* no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL){
		return 0;
	}
	no->dados = c;
	if((*li) == NULL){
		*li = no;
		no->prox = no;
	}else{
		Elem *aux = *li;
		while(aux->prox != (*li)){
			aux = aux->prox;
		}
		aux->prox = no;
		no->prox = *li;
	}
	return 1;
}

//Insere no meio da lista.
int insere_lista_meio(Lista* li, struct cliente c, int pos){
	if(li == NULL){
		return 0;
	}
	Elem *no = (Elem*) malloc(sizeof(Elem));
	if(no == NULL) {
		return 0;
	}
	no->dados = c;
	if(lista_vazia(li)){
		*li = no;
		no->prox = no;
		return 1;
	}else{
	int cont1 = 0;
	int cont2 = 0;
	Elem* auxAnt = *li;
	Elem* auxPost = *li;
	while(cont1 != (pos-1)){
		auxAnt = auxAnt->prox;
		cont1++;
	}
	while(cont2 != (pos)){
		auxPost	= auxPost->prox;
		cont2++;
	}
	auxAnt->prox = no;
	no->prox = auxPost;
	}
	return 1;
}

//remove no inicio da lista duplamente encadeada.
int remove_lista_inicio(Lista *li){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	if((*li) == (*li)->prox){
		free(*li);
		*li = NULL;
		return 1;
	}
	Elem *atual = *li;
	while(atual->prox != (*li)){
		atual = atual->prox;
	}
	Elem *no = *li;
	int cpfRemovido = no->dados.cpf;
	atual->prox = no->prox;
	*li = no->prox;
	free(no);
	return cpfRemovido;
}


    //Métodos da lista de exercícios
//Cria uma lista vazia
Lista* Criar_lista_vazia(){
	Lista* li = (Lista*) malloc(sizeof(Lista));
	if(li != NULL){
		*li = NULL;
	}
	return li;
}

//Insere um elemento em qualquer posição da lista circular
int Inserir_um_elemento_em_qualquer_posicao_da_lista(Lista* li, struct cliente c, int pos){
	int x = tamanho_lista(li);
	if (pos == 0 || pos > x){
		insere_lista_inicio(li,c);
	}
	if (0 < pos && pos < x){
		insere_lista_meio(li,c,pos);
	}
	if (pos == x){
		insere_lista_final(li,c);
	}
}

//Remove um elemento em qualquer posição da lista.
int Remover_um_elemento_de_qualquer_posicao_da_lista(Lista*li, struct cliente c){
	if(li == NULL){
		return 0;
	}
	if((*li) == NULL){
		return 0;
	}
	Elem* no = *li;
	int cpfRemovido = no->dados.cpf;
	if(no->dados.cpf == c.cpf){
		remove_lista_inicio(li);
	}
	Elem *ant = no;
	no = no->prox;
	while(no != (*li) && no->dados.cpf != c.cpf){
		ant = no;
		no = no->prox;
	}
	if(no == *li){
		return 0;
	}
	ant->prox = no->prox;
	free(no);
	return cpfRemovido;
}

//Faz uma busca na lista retornando a posição do cliente, caso exista na lista.
int Buscar_a_posicao_de_um_elemento_na_lista(Lista* li, struct cliente c){
	if(li == NULL){
		return -1;
	}
	Elem *no = *li;
	int cont = 0;
	while(no->prox != (*li) && no->dados.cpf != c.cpf){
		cont++;
		no = no->prox;
	}
	if(no == NULL){
		return -1;
	}else{
		return cont;
	}
}

//Imprime todos os elementos da lista.
void Imprimir_todos_os_elementos_da_lista(Lista* li){
	if(li == NULL || (*li) == NULL){
		return;
	}
	Elem* aux = *li;
	int i = 0;
	do{
		printf("Nome do cliente %d: %s\n", (i+1), aux->dados.nome);
		i++;
		aux = aux->prox;
	} while(aux != (*li));
}

//Deleta uma lista circular encadeada.
void Deletar_lista(Lista* li){
	if(li != NULL && (*li) != NULL){
		Elem *aux, *no = *li;
		while((*li) != no->prox){
			aux = no;
			no = no->prox;
			free(aux);
		}
		free(no);
		free(li);
	}
}

int main(){
	struct cliente ana = {"ana", 100};
	struct cliente bia = {"bia", 101};
	struct cliente isa = {"isa", 102};
	struct cliente lar = {"lar", 103};
	struct cliente Elias = {"Eli", 104};

	Lista* li = Criar_lista_vazia();
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere ana	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, ana, 3);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere bia	-----	-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, bia, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere isa no inicio-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, isa, 0);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Insere lar na pos 1-----\n");
	Inserir_um_elemento_em_qualquer_posicao_da_lista(li, lar, 1);
	Imprimir_todos_os_elementos_da_lista(li);
	printf("-----------------------------------------\n");
	printf("-----	-----	Busca pos da ana    -----\n");
	int x = Buscar_a_posicao_de_um_elemento_na_lista(li, ana);
	printf("Posicao: %d\n", x);
	printf("-----------------------------------------\n");
	printf("-----	-----	Remove lar da lista -----\n");
	int y = Remover_um_elemento_de_qualquer_posicao_da_lista(li, lar);
	printf("cpf removido: %d\n", y);
	Imprimir_todos_os_elementos_da_lista(li);
	Deletar_lista(li);
}
