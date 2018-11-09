#include "abb.h"
#include <stdlib.h>
#include <string.h>

typedef struct abb_nodo {
	struct abb_nodo* izq;
	struct abb_nodo* der;
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

abb_nodo_t* crear_nodo(const char* clave, void* dato) {
	abb_nodo_t* nodo = malloc(sizeof(abb_nodo_t));
	if(nodo == NULL) return NULL;
	size_t largo = strlen(clave);
	char* copia_clave = malloc(sizeof(char) * largo);
	if(copia_clave == NULL) return NULL;
	for(int i=0; i<largo; i++) {
		copia_clave[i] = clave[i];
	}
	copia_clave[largo] = '\0';
	nodo->clave = copia_clave;
	nodo->dato = dato;
	nodo->izq = NULL;
	nodo->der = NULL;
	return nodo;
}

abb_nodo_t* buscar_nodo(const abb_t* arbol, abb_nodo_t* nodo, const char* clave) {
	if(nodo == NULL || arbol->cmp(clave, nodo->clave) == 0) return nodo;
	if(arbol->cmp(clave, nodo->clave) > 0) return buscar_nodo(arbol, nodo->der, clave);
	return buscar_nodo(arbol, nodo->izq, clave);
}

// si no tiene padre, se devuelve a si mismo
abb_nodo_t* buscar_padre(const abb_t* arbol, abb_nodo_t* nodo, const char* clave) {
	if(nodo == NULL || (nodo->izq == NULL && nodo->der == NULL) || (arbol->cmp(clave, nodo->clave) == 0)) return nodo;
	if(arbol->cmp(clave, nodo->clave) > 0) {
		if(nodo->der == NULL) return nodo;
		return buscar_padre(arbol, nodo->der, clave);
	} else {
		if(nodo->izq == NULL) return nodo;
		return buscar_padre(arbol, nodo->izq, clave);
	}
}

size_t cantidad_hijos(abb_nodo_t* nodo) {
	size_t cantidad = 0;
	if(!nodo->izq) cantidad++;
	if(!nodo->der) cantidad++;
	return cantidad;
}

/* PRIMITIVAS ABB*/
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	abb_t* arbol = malloc(sizeof(abb_t));
	if (arbol == NULL) return NULL;
	arbol->raiz = NULL;
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	arbol->cantidad = 0;
	return arbol;
}

bool abb_guardar(abb_t* arbol, const char* clave, void* dato) { //habria que reutilizar mas codigo, pero no se como
	abb_nodo_t* nodo_nuevo = crear_nodo(clave, dato);
	if (nodo_nuevo == NULL) return false;
	if (arbol->raiz == NULL) 
		arbol->raiz = nodo_nuevo;
	else {
		abb_nodo_t* nodo = buscar_padre(arbol, arbol->raiz, clave);
		if(arbol->cmp(clave, nodo->clave) == 0) nodo->dato = dato;
		else if(arbol->cmp(clave, nodo->clave) > 0) nodo->der = nodo_nuevo;
		else nodo->izq = nodo_nuevo;
	}
	arbol->cantidad++;
	return true;
}

void* abb_borrar(abb_t* arbol, const char* clave){
	abb_nodo_t* nodo_a_borrar = buscar_nodo(arbol, arbol->raiz, clave);
	if(nodo_a_borrar == NULL) return NULL;
	abb_nodo_t* padre = buscar_padre(arbol, arbol->raiz,clave);
	size_t cant_hijos = cantidad_hijos(nodo_a_borrar);
	//if(arbol->cmp(padre->clave, clave) == 0) // es raiz
	if(cant_hijos == 0){
		if(arbol->cmp(padre->clave, nodo_a_borrar->clave)) padre->izq = NULL;
		else padre->der = NULL;
	}

	if(cant_hijos == 1){
		if(arbol->cmp(padre->clave, nodo_a_borrar->clave)){ //el nodo esta a la izq del padre
			if(!nodo_a_borrar->izq) { //el hijo q tiene es a la izq 
				padre->izq = nodo_a_borrar->izq;
			}
			else padre->izq = nodo_a_borrar->der; //el hijo q tiene es a la der
		} else { //el nodo esta a la der del padre
			if(!nodo_a_borrar->izq) { //el hijo q tiene es a la izq 
				padre->der = nodo_a_borrar->izq;
			}
			else padre->der = nodo_a_borrar->der; //el hijo q tiene es a la der
		}
	}

	if(cant_hijos == 2){
		abb_nodo_t* nieto = nodo_a_borrar->der; //voy a la der
		while(!nieto->izq) { //avanzo a la izq hasta el fondo
			nieto = nieto->izq;
		}
		padre->der = nieto;
	}

	return nodo_a_borrar->dato;
}
//devuelve null si no esta en el arbol

void* abb_obtener(const abb_t* arbol, const char* clave) {
	abb_nodo_t* nodo = buscar_nodo(arbol, arbol->raiz, clave);
	if(nodo == NULL) return NULL;
	return nodo->dato; 
}

bool abb_pertenece(const abb_t* arbol, const char* clave){
	return buscar_nodo(arbol, arbol->raiz, clave) != NULL;
}

size_t abb_cantidad(abb_t* arbol){
	return arbol->cantidad;
}

void abb_destruir(abb_t* arbol){
	free(arbol);
}


/* PRIMITIVAS ITERADOR */
