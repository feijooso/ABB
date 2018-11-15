#include "pila.h"
#include <stdlib.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

#define TINICIAL 4
#define TREDIMENSION 2


/* *****************************************************************
 *                    AUXILIARES DE LA PILA
 * *****************************************************************/

bool pila_redimensionar(pila_t* pila, size_t tam) {

	void** datos_nuevo = realloc(pila->datos, tam * sizeof(void*));

	if (datos_nuevo == NULL) return false;

	pila->capacidad = tam;
	pila->datos = datos_nuevo;
	return true;

}

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


pila_t* pila_crear(void) {

	pila_t* pila = malloc(sizeof(pila_t));

	if (pila == NULL) {
        return NULL;
    }

    void** datos_nuevo = malloc(TINICIAL * sizeof(void*));

    if (datos_nuevo == NULL) {
    	free(pila);
        return NULL;
    }

    pila->datos = datos_nuevo;
    pila->cantidad = 0;
    pila->capacidad = TINICIAL; 

	return pila;

}

void pila_destruir(pila_t* pila) {

	free(pila->datos);
	free(pila);

}

bool pila_esta_vacia(const pila_t *pila) {

	return (pila->cantidad == 0);
}


bool pila_apilar(pila_t* pila, void* valor) {

	if (pila->cantidad == pila->capacidad){

		size_t tam =  (pila->capacidad) * TREDIMENSION;

		if (!pila_redimensionar(pila, tam)) return false;
	}

	pila->datos[pila->cantidad]  = valor;
	pila->cantidad ++;
	return true;

}

void* pila_ver_tope(const pila_t* pila){

	if (pila_esta_vacia(pila)) return NULL;

	return pila->datos[pila->cantidad-1];

}

void* pila_desapilar(pila_t* pila){

	if (pila_esta_vacia(pila)) return NULL;

	void* valor = pila->datos[pila->cantidad-1];
	pila->cantidad --;

	if ((pila->cantidad)/4 == pila->capacidad && pila->capacidad > TREDIMENSION * TINICIAL){

		size_t tam =  (pila->capacidad) / TREDIMENSION;

		pila_redimensionar(pila, tam);

	}

	return valor;


}