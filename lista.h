typedef enum {
    ELEM1_MAYOR_QUE_ELEM2,
    ELEM1_IGUAL_QUE_ELEM2,
    ELEM1_MENOR_QUE_ELEM2
} comparacion_resultado_t;

struct elemento {
    int a;
    char *b;
};
typedef struct elemento elemento_t;

typedef comparacion_resultado_t (funcion_comparacion_t) (
    elemento_t *elem1, elemento_t *elem2
);

typedef struct lista lista_t;

lista_t *lista_crear();

int lista_insertar(lista_t *l, elemento_t elem, unsigned int pos);

elemento_t *lista_eliminar(lista_t *l, unsigned int pos);

elemento_t *lista_elemento(lista_t *l, unsigned int pos);

int lista_ordenar(lista_t *l, funcion_comparacion_t comparar);

unsigned int lista_cantidad(lista_t *l);

int lista_vacia(lista_t lista);
