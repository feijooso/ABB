#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "testing.h"

void prueba_abb_vacio() {
    printf("%s\n","PRUEBAS ABB VACIO");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("Esta vacio", abb_cantidad(abb) == 0);
    print_test("Prueba borrar", abb_borrar(abb, "") == NULL);
    print_test("Prueba pertenece", abb_pertenece(abb, "") == false);

    abb_destruir(abb);
}

void prueba_abb_guardar() {
    printf("%s\n","PRUEBAS GUARDAR");
    abb_t* abb = abb_crear(strcmp, NULL);
    const char* menor = "1";
    const char* medio = "2";
    const char* mayor = "3";
    int valor1 = 4;
    const char* clave1 = "4";
    const char* clave2 = "-1";
    abb_guardar(abb, medio, NULL);
    abb_guardar(abb, menor, &valor1);
    abb_guardar(abb, mayor, NULL);
    abb_guardar(abb, clave1, NULL);
    abb_guardar(abb, clave2, NULL);
    print_test("Cantidad es 5", abb_cantidad(abb) == 5);
    print_test("1 pertenece", abb_pertenece(abb, menor));
    print_test("1 obtener", abb_obtener(abb, menor) == &valor1);
    print_test("No pertenece random", abb_pertenece(abb, "RANDOM") == false);
    print_test("4 pertenece", abb_pertenece(abb, clave1));

    abb_destruir(abb);
}

void prueba_abb_borrar() {
    printf("%s\n","PRUEBAS BORRAR");
    abb_t* abb = abb_crear(strcmp, NULL);
    const char* menor = "1";
    const char* medio = "2";
    const char* mayor = "3";
    const char* valor1 = "4";
    const char* valor2 = "0";
    const char* valor3 = "5";
    int valorMenor = 1;
    int valorMedio = 2;
    int valorMayor = 3;
    abb_guardar(abb, medio, &valorMedio);
    abb_guardar(abb, menor, &valorMenor);
    abb_guardar(abb, mayor, &valorMayor);
    abb_guardar(abb, valor1, &valorMenor);
    abb_guardar(abb, valor2, &valorMedio);
    abb_guardar(abb, valor3, &valorMayor);
    print_test("Cantidad es 6", abb_cantidad(abb) == 6);
    print_test("Borrar 1", abb_borrar(abb, menor) == &valorMenor);
    print_test("Cantidad es 5", abb_cantidad(abb) == 5);
    print_test("Borrar 3", abb_borrar(abb, mayor) == &valorMayor);
    print_test("Cantidad es 4", abb_cantidad(abb) == 4);
    print_test("Borrar 2", abb_borrar(abb, medio) == &valorMedio);
    print_test("Cantidad es 3", abb_cantidad(abb) == 3);
    print_test("Borrar 5 ", abb_borrar(abb, valor3) == &valorMayor);
    print_test("Cantidad es 2", abb_cantidad(abb) == 2);
    print_test("Borrar ya borrado", abb_borrar(abb, medio) == NULL);
    print_test("Cantidad sigue igual", abb_cantidad(abb) == 2);
    print_test("Borrar 0", abb_borrar(abb, valor2) == &valorMedio);
    print_test("Cantidad es 1", abb_cantidad(abb) == 1);
    print_test("Borrar 4", abb_borrar(abb, valor1) == &valorMenor);
    print_test("Cantidad es 0", abb_cantidad(abb) == 0);

    abb_destruir(abb);
}

bool visitar1(const char* clave, void* dato, void* extra) {
    if (*(int*) dato < *(int*) extra) return false;

    *(int*) extra = *(int*) dato;
    return true;
}

void pruebas_abb_iter_interno(){
    printf("%s\n", "PRUEBAS ITERADOR INTERNO");
    abb_t* abb = abb_crear(strcmp, NULL);
    int cinco = 5;
    abb_guardar(abb, "5", &cinco);
    int seis = 6;
    abb_guardar(abb, "6", &seis);
    int cero = 0;
    abb_guardar(abb, "0", &cero);
    int tres = 3;
    abb_guardar(abb, "3", &tres);
    int uno = 1;
    abb_guardar(abb, "1", &uno);
    int nueve = 9;
    abb_guardar(abb, "9", &nueve);
    int dos = 2;
    abb_guardar(abb, "2", &dos);
    int cuatro = 4;
    abb_guardar(abb, "4", &cuatro);

    int valor = -1;
    abb_in_order(abb, visitar1, &valor);
    print_test("Itera in order", valor == 9);

    abb_destruir(abb);

}

void pruebas_abb_iter_externo(){
    printf("%s\n", "PRUEBAS ITERADOR EXTERNO");

    abb_t* abb = abb_crear(strcmp, NULL);
    printf("%s\n","Se creo una arbol vacio");
    abb_iter_t* iter1 = abb_iter_in_crear(abb);
    print_test("El iterador esta al final", abb_iter_in_al_final(iter1));
    abb_iter_in_destruir(iter1);

    int uno = 1;
    abb_guardar(abb, "1", &uno);
    int cinco = 5;
    abb_guardar(abb, "5", &cinco);
    int nueve = 9;
    abb_guardar(abb, "9", &nueve);
    int tres = 3;
    abb_guardar(abb, "3", &tres);
    int dos = 2;
    abb_guardar(abb, "2", &dos);
    int seis = 6;
    abb_guardar(abb, "6", &seis);

    abb_iter_t* iter2 = abb_iter_in_crear(abb);
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter2));
    print_test("El iterador esta en el primer elemento", strcmp(abb_iter_in_ver_actual(iter2),"1") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Avanzo correctamente",strcmp(abb_iter_in_ver_actual(iter2),"2") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter2),"3") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter2),"5") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter2),"6") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter2),"9") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter2));
    print_test("Iter esta al final", abb_iter_in_al_final(iter2));

    abb_iter_in_destruir(iter2);

    abb_destruir(abb);

}

void pruebas_abb_volumen(size_t largo, bool debug){
    printf("%s\n","PRUEBAS VOLUMEN" );
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    unsigned* valores[largo];

    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        valores[i] = malloc(sizeof(int));
        sprintf(claves[i], "%08d", i);
        *valores[i] = i;
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    if (debug) print_test("Guardar muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es la correcta", abb_cantidad(abb) == largo);

    for (size_t i = 0; i < largo; i++) {
        ok = abb_pertenece(abb, claves[i]);
        if (!ok) break;
        ok = abb_obtener(abb, claves[i]) == valores[i];
        if (!ok) break;
    }

    if (debug) print_test("Pertenece y obtener con muchos elementos", ok);
    if (debug) print_test("La cantidad de elementos es la correcta", abb_cantidad(abb) == largo);
    for (size_t i = 0; i < largo; i++){
        ok = abb_borrar(abb, claves[i]) == valores[i];
        if (! ok) break;
    }

    if (debug) print_test("Borrar muchos elementos", ok);
    if (debug) print_test("El arbol esta vacio", abb_cantidad(abb) == 0);

    abb_destruir(abb);
    abb = abb_crear(strcmp,free);

    ok = true;
    for (size_t i = 0; i < largo; i++) {
        ok = abb_guardar(abb, claves[i], valores[i]);
        if (!ok) break;
    }

    for (unsigned i = 0; i < largo; i++) {
        free(valores[i]);
    }
    free(claves);
    abb_destruir(abb);
}

void pruebas_abb_iterar_volumen(size_t largo){
    printf("%s\n","PRUEBAS ITERAR VOLUMEN" );
    abb_t* abb = abb_crear(strcmp,NULL);

    const size_t largo_clave = 10;
    char (*claves)[largo_clave] = malloc(largo * largo_clave);

    size_t valores[largo];

    /* Inserta 'largo' parejas en el abb */
    bool ok = true;
    for (unsigned i = 0; i < largo; i++) {
        sprintf(claves[i], "%08d", i);
        valores[i] = i;
        ok = abb_guardar(abb, claves[i], &valores[i]);
        if (!ok) break;
    }

    // Prueba de iteración sobre las claves almacenadas.
    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("Iterador no esta al final", !abb_iter_in_al_final(iter));

    ok = true;
    unsigned i;
    const char *clave;
    size_t *valor;

    for (i = 0; i < largo; i++) {
        if ( abb_iter_in_al_final(iter) ) {
            ok = false;
            break;
        }
        clave = abb_iter_in_ver_actual(iter);
        if ( clave == NULL ) {
            ok = false;
            break;
        }
        valor = abb_obtener(abb, clave);
        if ( valor == NULL ) {
            ok = false;
            break;
        }
        *valor = largo;
        abb_iter_in_avanzar(iter);
    }
    print_test("Iteracion en volumen", ok);
    print_test("Iteracion en volumen, recorrio todo el largo", i == largo);
    print_test("Iter esta al final", abb_iter_in_al_final(iter));

    ok = true;
    for (i = 0; i < largo; i++) {
        if ( valores[i] != largo ) {
            ok = false;
            break;
        }
    }
    print_test("Se cambiaron todo los elementos", ok);

    free(claves);
    abb_iter_in_destruir(iter);
    abb_destruir(abb);
}


void pruebas_abb_alumno() {
    prueba_abb_vacio();
    prueba_abb_guardar();
    prueba_abb_borrar();
    pruebas_abb_iter_interno();
    pruebas_abb_iter_externo();
    pruebas_abb_volumen(50, true);
    pruebas_abb_iterar_volumen(50);
}