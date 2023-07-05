/* ***************************************************************** */
/* File name:        filaCircular.c                                  */
/* File description: Este arquivo tem as funcoes da inicializacao    */
/*                   e do manuseio de uma fila circular estatica     */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    12jun2022                                       */
/* Revision date:    12jun2022                                       */
/* ***************************************************************** */

#include "filaCircular.h"

#define PRIMEIRA_POSICAO 0
#define ULTIMA_POSICAO 49

fila_circular fila;


/* *************************************************** */
/* Method name:        inicializarFila                 */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFila(void){
	for (int i = 0; i < 50; i++){
		fila.fFila[i] = 0;
	}
	fila.somatoriaElementos = 0;
	fila.posicaoAtual = PRIMEIRA_POSICAO;
}

/* *************************************************** */
/* Method name:        adicionarElementoFila           */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFila(float novoElemento){
	fila.somatoriaElementos += novoElemento;
	fila.somatoriaElementos -= fila.fFila[fila.posicaoAtual];
	fila.fFila[fila.posicaoAtual] = novoElemento;
	if (ULTIMA_POSICAO > fila.posicaoAtual){
		fila.posicaoAtual += 1;
	} else {
		fila.posicaoAtual = PRIMEIRA_POSICAO;
	}
}

/* *************************************************** */
/* Method name:        obterElementoAnterior           */
/* Method description: Obter o valor do elemento       */
/*                     anterior                        */
/* Input params:       n/a                             */
/* Output params:      (float) Valor do erro anterior  */
/* *************************************************** */
float obterElementoAnterior(void){
	if (PRIMEIRA_POSICAO == fila.posicaoAtual){
		return fila.fFila[ULTIMA_POSICAO];
	}
	return fila.fFila[fila.posicaoAtual-1];
}

/* *************************************************** */
/* Method name:        obterSomatoriaElementos         */
/* Method description: Obter o valor da somatoria de   */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da somatoria      */
/* *************************************************** */
float obterSomatoriaElementos(void){
	return fila.somatoriaElementos;
}
