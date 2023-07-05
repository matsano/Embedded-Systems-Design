/* *********************************************************************** */
/* File name:		 filaCircularTam5.h				     		           */
/* File description: Header file containing the prototypes of the          */
/*                   functions used to initialize and configure a          */
/*                   circular buffer with length 5                         */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    12jun2022										       */
/* Revision date:    12jun2022										       */
/* *********************************************************************** */

#ifndef SOURCES_FILACIRCULARTAM5_H_
#define SOURCES_FILACIRCULARTAM5_H_

typedef struct fila_circular_5 {
	float fFila[5];
	float somatoriaElementos;
	float mediaElementos;
	int posicaoAtual;

} fila_circular_5;

/* *************************************************** */
/* Method name:        inicializarFilaTam5             */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFilaTam5(void);

/* *************************************************** */
/* Method name:        adicionarElementoFilaTam5       */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFilaTam5(float novoElemento);

/* *************************************************** */
/* Method name:        obterMediaElementosTam5         */
/* Method description: Obter o valor da media de       */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da media          */
/* *************************************************** */
float obterMediaElementosTam5(void);

#endif /* SOURCES_FILACIRCULARTAM5_H_ */
