/* ***************************************************************** */
/* File name:        filaCircularTam5.c                              */
/* File description: Este arquivo tem as funcoes da inicializacao    */
/*                   e do manuseio de uma fila circular estatica     */
/*                   de tamanho 5                                    */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    12jun2022                                       */
/* Revision date:    12jun2022                                       */
/* ***************************************************************** */

#include "filaCircularTam5.h"

#define PRIMEIRA_POSICAO 0
#define ULTIMA_POSICAO 4

fila_circular_5 fila_5;


/* *************************************************** */
/* Method name:        inicializarFilaTam5             */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFilaTam5(void){
	for (int i = 0; i < (ULTIMA_POSICAO+1); i++){
		fila_5.fFila[i] = 0;
	}
	fila_5.somatoriaElementos = 0;
	fila_5.posicaoAtual = PRIMEIRA_POSICAO;
	fila_5.mediaElementos = 0;
}

/* *************************************************** */
/* Method name:        adicionarElementoFilaTam5       */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFilaTam5(float novoElemento){
	fila_5.somatoriaElementos += novoElemento;
	fila_5.somatoriaElementos -= fila_5.fFila[fila_5.posicaoAtual];
	fila_5.fFila[fila_5.posicaoAtual] = novoElemento;
	if (ULTIMA_POSICAO > fila_5.posicaoAtual){
		fila_5.posicaoAtual += 1;
	} else {
		fila_5.posicaoAtual = PRIMEIRA_POSICAO;
	}
	fila_5.mediaElementos = fila_5.somatoriaElementos / (ULTIMA_POSICAO+1);
}


/* *************************************************** */
/* Method name:        obterMediaElementosTam5         */
/* Method description: Obter o valor da media de       */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da media          */
/* *************************************************** */
float obterMediaElementosTam5(void){
	return fila_5.mediaElementos;
}
