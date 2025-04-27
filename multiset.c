#include "multiset.h"
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>


struct trie{
int cantidad; // Cantidad de veces que aparece esa palabra en el multiset
struct trie *siguiente[26];
};

multiset_t *multiset_crear(){
    multiset_t *multi = (multiset_t*)malloc(sizeof(multiset_t));
    multi -> cantidad = 0;
    for(int i = 0; i < 26; i++){
        multi -> siguiente[i] = NULL;
    };
    return multi;
};

void multiset_insertar(multiset_t *m, char *s){
    multiset_t *cursor=m;
    for(int k=0;s[k] != '\0';k++){
        int indice = s[k]-'a';
        if(cursor->siguiente[indice] == NULL)
            cursor->siguiente[indice] = multiset_crear();
        cursor=cursor->siguiente[indice];
    }
    cursor->cantidad++;
};

int multiset_cantidad(multiset_t *m, char *s){
    multiset_t *cursor=m;
    for(int k=0;k<strlen(s);k++){
        int indice = s[k]-'a';
        if(cursor->siguiente[indice] == NULL)
            return 0;
        cursor=cursor->siguiente[indice];
    }
    return cursor->cantidad;
};

void multiset_elementosRec(multiset_t *m, lista_t *l,char *p){
    if(m->cantidad>0){
        elemento_t elem;
        elem.a = m->cantidad;
        elem.b= strdup(p);
        lista_insertar(l, elem, 0);
    }
    for(int i = 0;i<26;i++){
        if(m->siguiente[i] != NULL){
            char *nueva_cadena = malloc(strlen(p) + 2);
            strcpy(nueva_cadena, p);
            nueva_cadena[strlen(p)] = i + 'a';
            nueva_cadena[strlen(p) + 1] = '\0';
            multiset_elementosRec(m->siguiente[i], l, nueva_cadena);
            free(nueva_cadena);
        }
    }
}

lista_t multiset_elementos(multiset_t *m, int (*f)(elemento_t, elemento_t)){
    lista_t *retorno=lista_crear();
    char c[50] = "\0";
    multiset_elementosRec(m,retorno, c);
    lista_ordenar(retorno,(comparacion_resultado_t(*)(elemento_t*,elemento_t*))f);
    return *retorno;
};

void multiset_eliminar(multiset_t **m){
    for(int i = 0;i<26;i++){
        if((*m)->siguiente[i] != NULL){
            multiset_t **mRec=&((*m)->siguiente[i]);
            multiset_eliminar(mRec);
        }
    }
    free(*m);
    *m = NULL;
}

