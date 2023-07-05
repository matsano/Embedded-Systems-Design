/* *********************************************************************** */
/* File name:		 filaCircularTam50.h				    		       */
/* File description: Header file containing the prototypes of the          */
/*                   functions used to initialize and configure a          */
/*                   circular buffer with length 50                        */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    12jun2022										       */
/* Revision date:    12jun2022										       */
/* *********************************************************************** */

#ifndef SOURCES_FILACIRCULARTAM50_H_
#define SOURCES_FILACIRCULARTAM50_H_

typedef struct fila_circular_50 {
	float fFila[50];
	float somatoriaElementos;
	int posicaoAtual;

} fila_circular_50;

/* *************************************************** */
/* Method name:        inicializarFilaTam50            */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFilaTam50(void);

/* *************************************************** */
/* Method name:        adicionarElementoFilaTam50      */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFilaTam50(float novoElemento);

/* *************************************************** */
/* Method name:        obterElementoAnteriorTam50      */
/* Method description: Obter o valor do elemento       */
/*                     anterior                        */
/* Input params:       n/a                             */
/* Output params:      (float) Valor do erro anterior  */
/* *************************************************** */
float obterElementoAnteriorTam50(void);

/* *************************************************** */
/* Method name:        obterSomatoriaElementosTam50    */
/* Method description: Obter o valor da somatoria de   */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da somatoria      */
/* *************************************************** */
float obterSomatoriaElementosTam50(void);

#endif /* SOURCES_FILACIRCULARTAM50_H_ */
