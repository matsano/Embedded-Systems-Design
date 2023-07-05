/* *********************************************************************** */
/* File name:		 filaCircular.h							 		       */
/* File description: Header file containing the prototypes of the          */
/*                   functions used to initialize and configure a          */
/*                   circular buffer                                       */
/* Author name:      Igor B Teixeira                                       */
/*                   Matheus S Sano                                        */
/* Creation date:    12jun2022										       */
/* Revision date:    12jun2022										       */
/* *********************************************************************** */

#ifndef SOURCES_FILACIRCULAR_H_
#define SOURCES_FILACIRCULAR_H_

typedef struct fila_circular {
	float fFila[50];
	float somatoriaElementos;
	int posicaoAtual;

} fila_circular;

/* *************************************************** */
/* Method name:        inicializarFila                 */
/* Method description: Inicializa a fila circular e    */
/*                     zera a somatoria                */
/* Input params:       n/a                             */
/* Output params:      n/a                             */
/* *************************************************** */
void inicializarFila(void);

/* *************************************************** */
/* Method name:        adicionarElementoFila           */
/* Method description: Adiciona um elemento na fila    */
/*                     circular                        */
/* Input params:       float novoElemento              */
/*                     Elemento que vai ser adicionado */
/*                     na fila                         */
/* Output params:      n/a                             */
/* *************************************************** */
void adicionarElementoFila(float novoElemento);

/* *************************************************** */
/* Method name:        obterElementoAnterior           */
/* Method description: Obter o valor do elemento       */
/*                     anterior                        */
/* Input params:       n/a                             */
/* Output params:      (float) Valor do erro anterior  */
/* *************************************************** */
float obterElementoAnterior(void);

/* *************************************************** */
/* Method name:        obterSomatoriaElementos         */
/* Method description: Obter o valor da somatoria de   */
/*                     todos os elementos da lista     */
/* Input params:       n/a                             */
/* Output params:      (float) Valor da somatoria      */
/* *************************************************** */
float obterSomatoriaElementos(void);

#endif /* SOURCES_FILACIRCULAR_H_ */
