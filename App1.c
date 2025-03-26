#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define _CRT_SECURE_NO_WARNINGS

//Funcion encargada de Parsear el texto del csv, se debe ingresar el Num, el  cual es la
//columna de informacion que se desea extraer
char NombreArchivo[80];

struct Registro {
    int pizza_id;
    int order_id;
    char* pizza_name_id;
    int quantity;
    char* order_date;
    char* order_time;
    int unit_price;
    int total_price;
    char* pizza_size;
    char* pizza_category;
    char* pizza_ingredients;
    char* pizza_name;
};

// Variables globales
struct Registro *aRegistros; // Crear puntero para almacenar datos
// Es un arreglo de iRegistros posiciones, cada una del tipo Registro
int iRegistros;              // Cantidad de registros del archivo
char *sCabecera;             // Para salvar registro de cabecera

// Rutina para contar cantidad de registro de un archivo de texto
int CuentaRegistros(char* filename) {
    int iRegistros = 0;
    FILE *file = fopen(filename, "r");
    struct stat stStatusFile;  // Para capturar las características del archivo, en particular propiedad st_size
    stat(filename, &stStatusFile);
    char *sRegistro = malloc(stStatusFile.st_size);  // Reservar memoria por el tamaño total (peor caso)

    // Se recorre hasta EOF para contar
    while (fscanf(file, "%[^\n] ", sRegistro) != EOF) {
        iRegistros++;
    }
    fclose(file);
    iRegistros--; // Se resta uno para no considerar los encabezados
    return iRegistros;
}

// Rutina para cargar el archivo en el puntero de estructura Registro
void CargaRegistros(char* filename, int iRegistros) {
    aRegistros = (struct Registro*)malloc(iRegistros * sizeof(struct Registro));
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("No se pudo abrir el archivo");
        return;
    }
    struct stat stStatusFile;  // Para capturar las características del archivo, en particular propiedad st_size
    stat(filename, &stStatusFile);
    char *sRegistro = malloc(stStatusFile.st_size);  // Reservar memoria por el tamaño total (peor caso)
    int iPosRegistro = 0;

    char *token;

    // Salvamos el primer registro de cabecera
    sCabecera = malloc(stStatusFile.st_size);
    fgets(sCabecera, stStatusFile.st_size, file);

    // Se recorre hasta EOF para cargar
    while (fgets(sRegistro, stStatusFile.st_size, file)) {
        // Remover el salto de línea si lo hay
        sRegistro[strcspn(sRegistro, "\n")] = 0;

        // pizza_id
        token = strtok(sRegistro, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_id = atoi(token);
        }

        // order_id
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].order_id = atoi(token);
        }

        // pizza_name_id
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_name_id = strdup(token);
        }

        // quantity
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].quantity = atoi(token);
        }

        // order_date
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].order_date = strdup(token);
        }

        // order_time
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].order_time = strdup(token);
        }

        // unit_price
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].unit_price = atoi(token);
        }

        // total_price
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].total_price = atoi(token);
        }

        // pizza_size
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_size = strdup(token);
        }

        // pizza_category
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_category = strdup(token);
        }

        // pizza_ingredients
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_ingredients = strdup(token);
        }

        // pizza_name
        token = strtok(NULL, ",");
        if (token) {
            aRegistros[iPosRegistro].pizza_name = strdup(token);
        }

        iPosRegistro++;
    }
    fclose(file);
    return;
}

void MostrarDatos() {
    printf("Reg. 0: cabecera: %s\n", sCabecera);
    for (int iPosRegistro = 0; iPosRegistro < iRegistros; iPosRegistro++) {
        printf("Reg. %i: %i | %i | %s | %i | %s | %s | %i | %i | %s | %s | %s | %s|\n",
            iPosRegistro + 1,
            aRegistros[iPosRegistro].pizza_id,
            aRegistros[iPosRegistro].order_id,
            aRegistros[iPosRegistro].pizza_name_id,
            aRegistros[iPosRegistro].quantity,
            aRegistros[iPosRegistro].order_date,
            aRegistros[iPosRegistro].order_time,
            aRegistros[iPosRegistro].unit_price,
            aRegistros[iPosRegistro].total_price,
            aRegistros[iPosRegistro].pizza_size,
            aRegistros[iPosRegistro].pizza_category,
            aRegistros[iPosRegistro].pizza_ingredients,
            aRegistros[iPosRegistro].pizza_name);
    }
    return;
}

void orchestrator() {
    char *filename = NombreArchivo;
    printf("Debug:Nombre recibido de archivo es: %s\n", filename);
    iRegistros = CuentaRegistros(filename);
    printf("Cantidad de registros: %i\n\n", iRegistros);
    CargaRegistros(filename, iRegistros);
    MostrarDatos();
    return;
}

int main(void) {
    printf("Ingrese el nombre del archivo CSV: ");
    fgets(NombreArchivo, sizeof(NombreArchivo), stdin);
    NombreArchivo[strcspn(NombreArchivo, "\n")] = '\0';
    orchestrator();
    return 0;
}
//Funcion main la cual debe tener la funcionaliad de leer el archivo csv
//Funcion para decidir el valor mas repetido/menos repetido (Pizza mas y
//menos vendida)

//Funcion para extraer la fecha con mas y menos ganancias junto a la cantidad

//Fechas con mas y menos ventas en terminos de cantidad junto a la cantidad

//Funcion para calcular el promedio de una columna (promedio pizzas por orden y dia)

//Funcion para obtener el mayor valor dentro de una columna (Ingrediente mas vendido)

//Funcion para sumar la cant de pizzas por categoria

