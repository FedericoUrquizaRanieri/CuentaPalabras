#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "multiset.c"

char *armar_ruta(char *directorio, char *archivo) {
    int longitud_dir = strlen(directorio);
    int longitud_arc = strlen (archivo);
    char *retorno = (char *) malloc(longitud_dir + longitud_arc + 1);
    strcpy(retorno, directorio);
    strcpy(retorno + longitud_dir, archivo);
    return retorno;
}

//Funcion comparacion
comparacion_resultado_t f(elemento_t *e1, elemento_t *e2){
    if(e1->a > e2->a){
        return ELEM1_MAYOR_QUE_ELEM2;
    }
    else{
        if(e1->a == e2->a){
            return ELEM1_IGUAL_QUE_ELEM2;
        }
        else{
            return ELEM1_MENOR_QUE_ELEM2;
        }
    }
}

void cuentoPalabras(char *directorio) {
    DIR *dir;
    struct dirent *entrada;
    printf("%s\n",directorio);
    //Agrego la ultima barra al directorio
    int directorio_len = strlen(directorio);
    directorio[directorio_len] = '/';
    directorio[directorio_len + 1] = '\0';


    //Abrir el directorio
    printf("%s\n",directorio);
    dir = opendir(directorio);
    printf("%s\n",directorio);
    if (dir == NULL) {
        printf("No se pudo abrir el directorio.\n");
        return;
    }

    //Abrir archivo totales y cadauno
    FILE *cadauno = fopen(armar_ruta(directorio,"cadauno.out"),"w");
    FILE *totales = fopen(armar_ruta(directorio,"totales.out"),"w");

    //Creo el multiset totales
    multiset_t *multi_totales = multiset_crear();

    // Leer las entradas del directorio
    while ((entrada = readdir(dir)) != NULL) {
        // Ignorar las entradas "." y ".."
        if (strcmp(entrada->d_name, ".") == 0 || strcmp(entrada->d_name, "..") == 0) {
            continue;
        }
        // Verificar si la entrada es un archivo con extensión ".txt"
        int longitud = strlen(entrada->d_name);
        if (longitud >= 4 && strcmp(entrada->d_name + longitud - 4, ".txt") == 0) {
            printf("TXT encontrado: %s\n", entrada->d_name);

            //Armar ruta del archivo
            char *ruta = armar_ruta(directorio, entrada->d_name);
            printf("La ruta al archivo es: %s\n\n", ruta);

            //Abrir archivo
            FILE *archivo = fopen(ruta, "r");
            char palabra[100];

            //Crear multiset Cadauno
            multiset_t *multi_cadauno = multiset_crear();

            while(!feof(archivo)){
                //Leer cada palabra
                fscanf(archivo, "%s", palabra);
                palabra[strlen(palabra)] = '\0';

                //Insertar cada palabra en multiset cadauno
                multiset_insertar(multi_cadauno, palabra);

                //Insertar cada palabra en multiset totales
                multiset_insertar(multi_totales, palabra);
            }

            //Escribir archivo cadauno
            lista_t lis_cadauno = multiset_elementos(multi_cadauno, (int(*)(elemento_t,elemento_t))f);
            fprintf(cadauno, "Archivo: %s\n",entrada->d_name);
            for(int i=0;i<lista_cantidad(&lis_cadauno);i++){
                fprintf(cadauno, "%i - %s\n", lista_elemento(&lis_cadauno,i)->a, lista_elemento(&lis_cadauno,i)->b);
            }

            //Salto de linea
            fprintf(cadauno, "\n");

            //Eliminar el multiset cadauno
            multiset_eliminar(&multi_cadauno);

            //Eliminar lis_cadauno
            for (int i = 0; i < lista_cantidad(&lis_cadauno); i++){
                lista_eliminar(&lis_cadauno, i);
            }

            //Liberar memoria usada para la ruta del archivo
            free(ruta);
        }
    }

    //Escribir archivo totales
    lista_t lis_totales = multiset_elementos(multi_totales, (int(*)(elemento_t,elemento_t))f);
    for(int i=0;i<lista_cantidad(&lis_totales);i++){
        fprintf(totales, "%i - %s\n", lista_elemento(&lis_totales,i)->a, lista_elemento(&lis_totales,i)->b);
    }

    //Eliminar el multiset totales
    multiset_eliminar(&multi_totales);

    //Eliminar lis_totales
    for (int i = 0; i < lista_cantidad(&lis_totales); i++){
        lista_eliminar(&lis_totales, i);
    }

    // Cerrar el directorio
    closedir(dir);
}

int main(int argc, char* argv[]) {
    if(strcmp(argv[1], "-h") == 0 || argc == 1){
        printf("Cuentapalabras es un software que permite realizar un conteo de palabras en un directorio especifico mediante el uso de un árbol Trie. Al ejecutar el programa se puede pasar el parámetro -h el cual exhibe esta breve introducción sobre el programa. Sino, por otra parte se puede ejecutar el programa pasando por parámetro el directorio en el cual se quiere realizar el conteo. De este directorio se leerán solo los archivos .txt ignorando cualquier otro formato. Con las palabras leídas se crearan dos nuevos archivos: El archivo cadauno.out que tendrá la cantidad de veces que aparece cada palabra en cada uno de los archivos y el archivo totales.out que tendrá la cantidad de veces que aparece cada palabra entre todos los archivos");
        return 0;
    }

    char *directorio = argv[1];
    printf("%s\n",directorio);
    cuentoPalabras(directorio);

    return 0;
}
