/* ***************************************************************** */
/* File name:        filaCircularTam50.c                             */
/* File description: Este arquivo tem as funcoes da inicializacao    */
/*                   e do manuseio de uma fila circular estatica     */
/*                   de tamanho 50                                   */
/* Author name:      Igor B Teixeira                                 */
/*                   Matheus S Sano                                  */
/* Creation date:    12jun2022                                       */
/* Revision date:    12jun2022                                       */
/* ***************************************************************** */

#include "filaCircularTam50.h"

#define PRIMEIRA_POSICAO 0
#define ULTIMA_POSICAO 49

fila_circular_50 fila_50;


/* *************************************************** */
/* Method name:        inicializarFilaTam50            */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFilaTam50(void){
	for (int i = 0; i < (ULTIMA_POSICAO+1); i++){
		fila_50.fFila[i] = 0;
	}
	fila_50.somatoriaElementos = 0;
	fila_50.posicaoAtual = PRIMEIRA_POSICAO;
}

/* *************************************************** */
/* Method name:        adicionarElementoFilaTam50      */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFilaTam50(float novoElemento){
	fila_50.somatoriaElementos += novoElemento;
	fila_50.somatoriaElementos -= fila_50.fFila[fila_50.posicaoAtual];
	fila_50.fFila[fila_50.posicaoAtual] = novoElemento;
	if (ULTIMA_POSICAO > fila_50.posicaoAtual){
		fila_50.posicaoAtual += 1;
	} else {
		fila_50.posicaoAtual = PRIMEIRA_POSICAO;
	}
}

/* *************************************************** */
/* Method name:        obterElementoAnteriorTam50      */
/* Method description: Obter o valor do elemento       */
/*                     anterior                        */
/* Input params:       n/a                             */
/* Output params:      (float) Valor do erro anterior  */
/* *************************************************** */
float obterElementoAnteriorTam50(void){
	if (PRIMEIRA_POSICAO == fila_50.posicaoAtual){
		return fila_50.fFila[ULTIMA_POSICAO];
	}
	return fila_50.fFila[fila_50.posicaoAtual-1];
}

/* *************************************************** */
/* Method name:        obterSomatoriaElementosTam50    */
/* Method description: Obter o valor da somatoria de   */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da somatoria      */
/* *************************************************** */
float obterSomatoriaElementosTam50(void){
	return fila_50.somatoriaElementos;
}
