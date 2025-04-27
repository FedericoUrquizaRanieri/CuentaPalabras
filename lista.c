
#include <stdio.h>
#include <stddef.h>
#include "lista.h"

typedef struct celda {
    elemento_t elem;
    struct celda *siguiente;
} celda_t;

typedef struct celda celda_t;

struct lista {
    celda_t *primera; //puntero a la primera celda de la lista
    int cantidad; // cantidad de elementos de la lista
};

lista_t *lista_crear(){
    lista_t *lista = (lista_t*)malloc(sizeof(lista_t));
    lista -> primera = NULL;
    lista -> cantidad = 0;
    return lista;
};

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos){
    if(l!=NULL && (l->cantidad)+1>pos){
        celda_t *nodo = (celda_t*) malloc(sizeof(celda_t));
        nodo->elem = elem;
        nodo->siguiente=NULL;
        if(l->cantidad==0){
            l->primera=nodo;
        }
        else{
            celda_t *puntero=l->primera;
            if(pos==0){
                nodo->siguiente=l->primera;
                l->primera=nodo;
            }
            else{
                for(int k=0;k<pos-1;k++)
                    puntero=puntero->siguiente;
                if(pos==l->cantidad)
                    puntero->siguiente=nodo;
                else{
                    nodo->siguiente=puntero->siguiente;
                    puntero->siguiente=nodo;
                }
            }
        }
        l->cantidad++;
        return 1;
    }
    else
        return 0;
}

elemento_t *lista_eliminar(lista_t *l, unsigned int pos){
    if(l->cantidad>pos){
        elemento_t *retorno;
        celda_t *aux;
        celda_t* puntero=l->primera;
        if(pos==0){
            aux=l->primera;
            l->primera=aux->siguiente;
            retorno=&(aux->elem);
        }
        else{
            for(int i=0;i<pos-1;i++)
                puntero=puntero->siguiente;
            aux=puntero->siguiente;
            retorno=&(aux->elem);
            if(pos==(l->cantidad)-1){
                puntero->siguiente=NULL;
            }
            else{
                puntero->siguiente=aux->siguiente;
            }
        }
        free(aux);
        l->cantidad--;
        return retorno;
    }
    else
        return NULL;
}

elemento_t *lista_elemento(lista_t *l, unsigned int pos){
    if(pos<lista_cantidad(l)){
        celda_t *puntero=l->primera;
        if(pos>0){
            for(int k=0;k<pos;k++)
                puntero=puntero->siguiente;
        }
        elemento_t *retorno=&(puntero->elem);
        return retorno;
    }
    else
        return NULL;
}

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar){
    if(l == NULL){
        return 0;
    }
    else{
        elemento_t aux;
        celda_t *puntero;
        for (int i=0; i<l->cantidad; i++){
            puntero=l->primera;
            for (int j=0 ; j<l->cantidad-1; j++){
                if (comparar(&puntero->elem, &puntero->siguiente->elem) == ELEM1_MAYOR_QUE_ELEM2){
                    aux = puntero->elem;
                    puntero->elem =puntero->siguiente->elem;
                    puntero->siguiente->elem = aux;
                }
                else{
                    if(comparar(&puntero->elem, &puntero->siguiente->elem) == ELEM1_IGUAL_QUE_ELEM2){
                        char *s1=puntero->elem.b;
                        char *s2=puntero->siguiente->elem.b;
                        if(strcmp(s1,s2)>0){
                            aux = puntero->elem;
                            puntero->elem =puntero->siguiente->elem;
                            puntero->siguiente->elem = aux;
                        }
                    }
                }
                puntero=puntero->siguiente;
            }
        }
        return 1;
    }

};

unsigned int lista_cantidad(lista_t *l){
    if(l == NULL){
        return 0;
    }
    return l->cantidad;
};

int lista_vacia(lista_t lista){
    if(lista.cantidad==0){
        return 1;
    }
    return 0;
};
