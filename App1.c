#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define _CRT_SECURE_NO_WARNINGS

//Funcion encargada de Parsear el texto del csv, se debe ingresar el Num, el  cual es la
//columna de informacion que se desea extraer
struct Registro{
   int pizza_id;
   int order_id;
   char pizza_name_id;
   int quantity;
   char order_date;
   char order_time;
   int unit_price;
   int total_price;
   char pizza_size;
   char pizza_category;
   char pizza_ingredients;
   char pizza_name;
};

// Variables globales
struct Registro *aRegistros; // Crear puntero para almacenar datos
// Es un arreglo de iRegistros posiciones, cada una  del tipo Registro
int iRegistros;              // Cantidad de registros del archivo
char *sCabecera;             // Para salvar registro de cabecera

//
// Rutina para contar cantidad de registro de un archivo de texto
//
int CuentaRegistros(char* filename){
   int iRegistros = 0;
   FILE *file = fopen(filename, "r");
   struct stat stStatusFile;  // Para capturar las característica del archivo, en particular propiedad st_size
   stat(filename, &stStatusFile);
   char *sRegistro = malloc(stStatusFile.st_size);  // Reservar memoria por el tamaño total (peor caso)

   // Se recorre hasta EOF para contar
   while (fscanf(file, "%[^\n] ", sRegistro) != EOF) {
      //printf("Largo registro %i: %s\n", (int)strlen(sRegistro), sRegistro);
      iRegistros++;
   }
   fclose(file);
   iRegistros--; // Se resta uno para no considerar los encabezados
   return iRegistros;
}

//
// Rutina para cargar el archivo en el puntero de estructura Registro
//
void CargaRegistros(char* filename, int iRegistros)
{
   aRegistros = (struct Registro*)malloc(iRegistros * sizeof(struct Registro));
   FILE* file = fopen(filename, "r");
   struct stat stStatusFile;  // Para capturar las característica del archivo, en particular propiedad st_size
   stat(filename, &stStatusFile);
   char *sRegistro = malloc(stStatusFile.st_size);  // Reservar memoria por el tamaño total (peor caso)
   int iPosRegistro = 0;

   char *token;

   // Salvamos el primer registro de cabecera
   sCabecera = malloc(stStatusFile.st_size);
   fscanf(file, "%[^\n] ", sCabecera);

   // Se recorre hasta EOF para cargar
   while (fscanf(file, "%[^\n] ", sRegistro) != EOF) {
      //printf("%s\n", sRegistro);

      // pizza_id
      token = strtok(sRegistro, "\"");
      //printf("libro: %s\n", token);
      aRegistros[iPosRegistro].pizza_id = atoi(_strdup(token));

      // coma, se ignora
      token = strtok(NULL, "\"");
      //printf("coma1: %s\n", token);

      // order_id
      token = strtok(NULL, "\"");
      //printf("autor: %s\n", token);
      aRegistros[iPosRegistro].order_id = atoi(_strdup(token));

      // pizza_name_id
      token = strtok(NULL, ",");
      //printf("año: %s\n", token);
      aRegistros[iPosRegistro].pizza_name_id = atoi(_strdup(token));

      // quantity
      token = strtok(NULL, ",");
      //printf("estante: %s\n", token);
      aRegistros[iPosRegistro].quantity = atoi(_strdup(token));

      // order_date
      token = strtok(NULL, "\"");
      //printf("sección: %s\n", token);
      aRegistros[iPosRegistro].order_date = atoi(_strdup(token));

      // order_time
      token = strtok(NULL, ",");
      //printf("piso: %s\n", token);
      aRegistros[iPosRegistro].order_time = atoi(_strdup(token));

      // unit_price
      token = strtok(NULL, "\"");
      //printf("edificio: %s\n", token);
      aRegistros[iPosRegistro].unit_price = atoi(_strdup(token));

      // coma, se ignora
      token = strtok(NULL, "\"");
      //printf("coma: %s\n", token);

      // total_price
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].total_price = atoi(_strdup(token));

      // pizza_size
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].pizza_size = atoi(_strdup(token));


      // pizza_category
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].pizza_category = atoi(_strdup(token));


      // total_price
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].total_price = atoi(_strdup(token));


      // pizza_ingredients
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].pizza_ingredients = atoi(_strdup(token));


      // pizza_name
      token = strtok(NULL, "\"");
      //printf("sede: %s\n", token);
      aRegistros[iPosRegistro].pizza_name = atoi(_strdup(token));



      iPosRegistro++;
   }
   fclose(file);
   return;

}


//Funcion main la cual debe tener la funcionaliad de leer el archivo csv
//Funcion para decidir el valor mas repetido/menos repetido (Pizza mas y
//menos vendida)

//Funcion para extraer la fecha con mas y menos ganancias junto a la cantidad

//Fechas con mas y menos ventas en terminos de cantidad junto a la cantidad

//Funcion para calcular el promedio de una columna (promedio pizzas por orden y dia)

//Funcion para obtener el mayor valor dentro de una columna (Ingrediente mas vendido)

//Funcion para sumar la cant de pizzas por categoria

