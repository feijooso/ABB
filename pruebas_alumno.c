#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "testing.h"

void prueba_abb_vacio() {
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("cantidad = 0", abb_cantidad(abb) == 0);
    print_test("borrar = NULL", abb_borrar(abb, "") == NULL);
    print_test("pertenece = NULL", abb_pertenece(abb, "") == false);
    abb_destruir(abb);
}

void prueba_abb_guardar() {
    abb_t* abb = abb_crear(strcmp, NULL);
    const char* menor = "1111";
    const char* medio = "2222";
    const char* mayor = "3333";
    int valor1 = 3;
    abb_guardar(abb, medio, NULL);
    abb_guardar(abb, menor, &valor1);
    abb_guardar(abb, mayor, NULL);
    print_test("cantidad == 3", abb_cantidad(abb) == 3);
    print_test("menor pertenece", abb_pertenece(abb, menor));
    print_test("menor obtener", abb_obtener(abb, menor) == &valor1);
    print_test("no pertenece random", abb_pertenece(abb, "RANDOM") == false);
    abb_destruir(abb);
}

void pruebas_abb_alumno() {
    //prueba_abb_vacio();
    prueba_abb_guardar();
}