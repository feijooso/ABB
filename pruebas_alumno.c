#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "abb.h"
#include "testing.h"

bool visitar_imprimir(const char *clave, void *valor, void *extra){

    printf("%s\n",clave);
    return true;

}

/*bool visitar_vector(const char *clave, void *valor, void *extra){
    extra = clave;
    return true;

}*/
void prueba_abb_vacio() {
    printf("%s\n","PRUEBAS ABB VACIO");
    abb_t* abb = abb_crear(strcmp, NULL);
    print_test("cantidad = 0", abb_cantidad(abb) == 0);
    print_test("borrar = NULL", abb_borrar(abb, "") == NULL);
    print_test("pertenece = NULL", abb_pertenece(abb, "") == false);
    
    abb_destruir(abb);
}

void prueba_abb_guardar() {
    printf("%s\n","PRUEBAS GUARDAR");
    abb_t* abb = abb_crear(strcmp, NULL);
    const char* menor = "1";
    const char* medio = "2";
    const char* mayor = "3";
    int valor1 = 4;
    int valor2 = 5;
    const char* clave1 = "4";
    const char* clave2 = "-1";
    abb_guardar(abb, medio, NULL);
    abb_guardar(abb, menor, &valor1);
    abb_guardar(abb, mayor, NULL);
    abb_guardar(abb, clave1, NULL);
    abb_guardar(abb, clave2, NULL);
    print_test("cantidad == 3", abb_cantidad(abb) == 5);
    print_test("menor pertenece", abb_pertenece(abb, menor));
    print_test("menor obtener", abb_obtener(abb, menor) == &valor1);
    print_test("no pertenece random", abb_pertenece(abb, "RANDOM") == false);
    print_test("menor obtener", abb_pertenece(abb, clave1));
    print_test("menor obtener", abb_pertenece(abb, clave1));
    abb_guardar(abb, clave2, &valor2);
    print_test("reemplazado valor clave2", abb_obtener(abb, clave2) == &valor2);
    print_test("cantidad sigue igual", abb_cantidad(abb) == 5);

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
    print_test("cantidad == 6", abb_cantidad(abb) == 6);
    print_test("borrar 1 (1 hijo)", abb_borrar(abb, menor) == &valorMenor);
    print_test("cantidad == 5", abb_cantidad(abb) == 5);
    print_test("borrar 3 (1 hijo)", abb_borrar(abb, mayor) == &valorMayor);
    print_test("cantidad == 4", abb_cantidad(abb) == 4);
    print_test("borrar 2 (2 hijos)", abb_borrar(abb, medio) == &valorMedio);
    print_test("cantidad == 3", abb_cantidad(abb) == 3);
    print_test("borrar 5 (0 hijos)", abb_borrar(abb, valor3) == &valorMayor);
    print_test("cantidad == 2", abb_cantidad(abb) == 2);
    print_test("borrar ya borrado", abb_borrar(abb, medio) == NULL);
    print_test("cantidad sigue igual", abb_cantidad(abb) == 2);
    print_test("borrar 0(0 hijo)", abb_borrar(abb, valor2) == &valorMedio);
    print_test("cantidad == 1", abb_cantidad(abb) == 1);
    print_test("borrar 4(raiz)", abb_borrar(abb, valor1) == &valorMenor);
    print_test("cantidad == 0", abb_cantidad(abb) == 0);
    abb_destruir(abb);
}

void pruebas_abb_iter_externo(){
    printf("%s\n", "PRUEBAS ITERADOR EXTERNO");
    abb_t* abb = abb_crear(strcmp, NULL);
    int uno = 1;
    abb_guardar(abb, "1", &uno);
    int seis = 6;
    abb_guardar(abb, "6", &seis);
    int cero = 0;
    abb_guardar(abb, "0", &cero);
    int tres = 3;
    abb_guardar(abb, "3", &tres);
    int menosuno = -1;
    abb_guardar(abb, "-1", &menosuno);
    int diez = 10;
    abb_guardar(abb, "10", &diez);
    int menosdos = -2;
    abb_guardar(abb, "-2", &menosdos);
    int cuatro = 4;
    abb_guardar(abb, "4", &cuatro);
    //char** vector = ["-2", "-1", "0", "1", "3", "4", "6", "10"];
    //char* abb_inorder[8];
    //void* extra = abb_inorder; 
    abb_in_order(abb, visitar_imprimir, NULL);

    abb_destruir(abb);

}

void pruebas_abb_iter_interno(){
    printf("%s\n", "PRUEBAS ITERADOR INTERNO");
    abb_t* abb = abb_crear(strcmp, NULL);
    int uno = 1;
    abb_guardar(abb, "1", &uno);
    int cinco = 5;
    abb_guardar(abb, "5", &cinco);
    int veinte = 20;
    abb_guardar(abb, "20", &veinte);
    int tres = 3;
    abb_guardar(abb, "3", &tres);
    int menosuno = -1;
    abb_guardar(abb, "-1", &menosuno);
    int seis = 6;
    abb_guardar(abb, "6", &seis);

    abb_iter_t* iter = abb_iter_in_crear(abb);
    print_test("El iterador no esta al final", !abb_iter_in_al_final(iter));
    print_test("El iterador esta en el primer elemento", strcmp(abb_iter_in_ver_actual(iter),"-1") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Avanzo correctamente",strcmp(abb_iter_in_ver_actual(iter),"1") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter),"3") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter),"5") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter),"6") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Avanzo correctamente", strcmp(abb_iter_in_ver_actual(iter),"20") == 0);
    print_test("Puede avanzar", abb_iter_in_avanzar(iter));
    print_test("Iter esta al final", abb_iter_in_al_final(iter));

    abb_iter_in_destruir(iter);

}



void pruebas_abb_alumno() {
    //prueba_abb_vacio();
    //prueba_abb_guardar();
    //prueba_abb_borrar();
    pruebas_abb_iter_externo();
    pruebas_abb_iter_interno();
}