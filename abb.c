#include "abb.h"
#include <stdlib.h>

typedef struct abb_nodo {
	struct abb_nodo_t* izq;
	struct abb_nodo_t* der;
	char* clave;
	void* dato;
} abb_nodo_t;

struct abb {
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;
};

/* FUNCIONES AUXILIARES */

void destruir_dato(void* dato) {

	free(dato);
}

abb_nodo_t* buscar_nodo(abb_t* arbol, abb_nodo_t* nodo, char* clave) {

	if (nodo == NULL) return NULL;
	if (arbol->cmp(clave, nodo->clave) == 0) return nodo;
	if (arbol->cmp(clave, nodo->clave) > 0) return buscar_nodo(arbol, nodo->der, clave);
	if (arbol->cmp(clave, nodo->clave) < 0) return buscar_nodo(arbol, nodo->izq, clave);

}

/* PRIMITIVAS ABB*/


abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){

	abb_t* arbol = malloc(sizeof(abb_t));
	if (arbol == NULL) return NULL;
	arbol->raiz = NULL;
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	return arbol;

}

bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
	

}

void *abb_borrar(abb_t *arbol, const char *clave){

}

void *abb_obtener(const abb_t *arbol, const char *clave){

	return buscar_nodo(arbol, arbol->raiz, clave);

}

bool abb_pertenece(const abb_t *arbol, const char *clave){

	return (buscar_nodo(arbol, arbol->raiz, clave));

}

size_t abb_cantidad(abb_t *arbol){

	return arbol->cantidad;

}

void abb_destruir(abb_t *arbol){

 }


/* PRIMITIVAS ITERADOR */
