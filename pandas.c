#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PANDAS 100

typedef struct {
    int dia;
    int mes;
    int anyo;
} Fecha;

typedef struct {
    char *nombre;
    float peso;
    int a_nac;
    char sexo;
    Fecha *ingreso;
} Panda;

/* Regresa la edad aproximada usando el año actual. */
int edad_Panda(Panda *p) {
    time_t ahora = time(NULL);
    struct tm *fechaActual = localtime(&ahora);
    int anioActual = fechaActual->tm_year + 1900;

    return anioActual - p->a_nac;
}

/* Una hembra puede entrar al programa cuando tiene más de 5 años. */
int tenerBebe(Panda *p) {
    if ((p->sexo == 'F' || p->sexo == 'f') && edad_Panda(p) > 5) {
        return 1;
    }
    return 0;
}

void imprimePanda(Panda *p) {
    printf("\nNombre: %s", p->nombre);
    printf("\nPeso: %.2f kg", p->peso);
    printf("\nAnio de nacimiento: %d", p->a_nac);
    printf("\nSexo: %c", p->sexo);
    printf("\nFecha de ingreso: %02d/%02d/%d\n",
           p->ingreso->dia, p->ingreso->mes, p->ingreso->anyo);
}

Panda *buscaPanda(Panda poblacion[], int total, char *nom) {
    int i;

    for (i = 0; i < total; i++) {
        if (strcmp(poblacion[i].nombre, nom) == 0) {
            return &poblacion[i];
        }
    }
    return NULL;
}

/* tp indica la posicion donde se guardara el nuevo panda. */
void agregarPanda(Panda poblacion[], int tp) {
    char nombreTemp[50];

    printf("\nNombre (sin espacios): ");
    scanf("%49s", nombreTemp);

    poblacion[tp].nombre = (char *)malloc(strlen(nombreTemp) + 1);
    poblacion[tp].ingreso = (Fecha *)malloc(sizeof(Fecha));

    if (poblacion[tp].nombre == NULL || poblacion[tp].ingreso == NULL) {
        printf("No hay memoria suficiente.\n");
        exit(1);
    }

    strcpy(poblacion[tp].nombre, nombreTemp);

    printf("Peso en kg: ");
    scanf("%f", &poblacion[tp].peso);

    printf("Anio de nacimiento: ");
    scanf("%d", &poblacion[tp].a_nac);

    printf("Sexo (F = hembra, M = macho): ");
    scanf(" %c", &poblacion[tp].sexo);

    printf("Dia de ingreso: ");
    scanf("%d", &poblacion[tp].ingreso->dia);

    printf("Mes de ingreso: ");
    scanf("%d", &poblacion[tp].ingreso->mes);

    printf("Anio de ingreso: ");
    scanf("%d", &poblacion[tp].ingreso->anyo);

    printf("\nPanda registrado correctamente.\n");
}

void listarPandas(Panda poblacion[], int total) {
    int i;

    if (total == 0) {
        printf("\nTodavia no hay pandas registrados.\n");
        return;
    }

    for (i = 0; i < total; i++) {
        printf("\n--- Panda %d ---", i + 1);
        imprimePanda(&poblacion[i]);
    }
}

void contarPorAnio(Panda poblacion[], int total, int anio) {
    int i, contador = 0;

    for (i = 0; i < total; i++) {
        if (poblacion[i].ingreso->anyo == anio) {
            contador++;
        }
    }

    printf("\nIngresaron %d panda(s) en %d.\n", contador, anio);
}

void mostrarReproductoras(Panda poblacion[], int total) {
    int i, hay = 0;

    printf("\nHembras candidatas al programa de reproduccion:\n");
    for (i = 0; i < total; i++) {
        if (tenerBebe(&poblacion[i]) == 1) {
            imprimePanda(&poblacion[i]);
            hay = 1;
        }
    }

    if (hay == 0) {
        printf("No hay candidatas registradas.\n");
    }
}

void mostrarMayorYMenor(Panda poblacion[], int total) {
    int i, mayor = 0, menor = 0;

    if (total == 0) {
        printf("\nNo hay pandas registrados.\n");
        return;
    }

    for (i = 1; i < total; i++) {
        if (poblacion[i].a_nac < poblacion[mayor].a_nac) {
            mayor = i;
        }
        if (poblacion[i].a_nac > poblacion[menor].a_nac) {
            menor = i;
        }
    }

    printf("\nPanda mas viejo:");
    imprimePanda(&poblacion[mayor]);

    printf("\nPanda mas joven:");
    imprimePanda(&poblacion[menor]);
}

void liberarMemoria(Panda poblacion[], int total) {
    int i;

    for (i = 0; i < total; i++) {
        free(poblacion[i].nombre);
        free(poblacion[i].ingreso);
    }
}

/* Pruebas individuales sencillas de las funciones principales. */
void pruebaEdadPanda(void) {
    time_t ahora = time(NULL);
    struct tm *fechaActual = localtime(&ahora);
    int anioActual = fechaActual->tm_year + 1900;
    Panda p;

    p.a_nac = anioActual - 7;
    printf("Prueba edad_Panda: resultado esperado 7, resultado obtenido %d\n",
           edad_Panda(&p));
}

void pruebaTenerBebe(void) {
    time_t ahora = time(NULL);
    struct tm *fechaActual = localtime(&ahora);
    int anioActual = fechaActual->tm_year + 1900;
    Panda p;

    p.a_nac = anioActual - 7;
    p.sexo = 'F';
    printf("Prueba tenerBebe (hembra de 7): resultado esperado 1, obtenido %d\n",
           tenerBebe(&p));

    p.sexo = 'M';
    printf("Prueba tenerBebe (macho de 7): resultado esperado 0, obtenido %d\n",
           tenerBebe(&p));
}

void pruebaBuscaPanda(void) {
    Panda datos[1];
    char nombre[] = "Luna";

    datos[0].nombre = nombre;
    printf("Prueba buscaPanda: ");
    if (buscaPanda(datos, 1, "Luna") != NULL) {
        printf("encontro a Luna (correcto).\n");
    } else {
        printf("no encontro el nombre (revisar).\n");
    }
}

void ejecutarPruebas(void) {
    printf("\n--- PRUEBAS INDIVIDUALES ---\n");
    pruebaEdadPanda();
    pruebaTenerBebe();
    pruebaBuscaPanda();
    printf("Para probar agregarPanda e imprimePanda, registra un panda desde el menu y revisa que sus datos aparezcan completos.\n");
}

int main(void) {
    Panda poblacion[MAX_PANDAS];
    int total = 0;
    int opcion, anio;
    char nombre[50];
    Panda *encontrado;

    do {
        printf("\n===== ZOOLOGICO: REGISTRO DE PANDAS =====\n");
        printf("1. Agregar panda\n");
        printf("2. Buscar panda por nombre\n");
        printf("3. Mostrar todos los pandas\n");
        printf("4. Contar ingresos por anio\n");
        printf("5. Mostrar hembras candidatas a reproduccion\n");
        printf("6. Mostrar panda mas viejo y mas joven\n");
        printf("7. Ejecutar pruebas\n");
        printf("0. Salir\n");
        printf("Elige una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                if (total < MAX_PANDAS) {
                    agregarPanda(poblacion, total);
                    total++;
                } else {
                    printf("\nYa se alcanzo el limite de registros.\n");
                }
                break;

            case 2:
                printf("\nNombre que deseas buscar: ");
                scanf("%49s", nombre);
                encontrado = buscaPanda(poblacion, total, nombre);
                if (encontrado != NULL) {
                    imprimePanda(encontrado);
                } else {
                    printf("\nNo se encontro ese panda.\n");
                }
                break;

            case 3:
                listarPandas(poblacion, total);
                break;

            case 4:
                printf("\nAnio que deseas consultar: ");
                scanf("%d", &anio);
                contarPorAnio(poblacion, total, anio);
                break;

            case 5:
                mostrarReproductoras(poblacion, total);
                break;

            case 6:
                mostrarMayorYMenor(poblacion, total);
                break;

            case 7:
                ejecutarPruebas();
                break;

            case 0:
                printf("\nSaliendo del programa...\n");
                break;

            default:
                printf("\nOpcion no valida. Intenta otra vez.\n");
        }
    } while (opcion != 0);

    liberarMemoria(poblacion, total);
    return 0;
}
