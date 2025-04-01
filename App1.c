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




// Variables globales CORREGIDAS (manteniendo tu estructura)
// Primero define las estructuras
typedef struct {
    char pizza_name[100];
    int total_quantity;
} Pizza;

typedef struct {
    char date[11];
    float total_price;
    int total_quantity;
} OrderDate;

typedef struct {
    char ingredient[100];
    int total_quantity;
} PizzaIngredient;

typedef struct {
    char category[50];
    int total_quantity;
} PizzaCategory;

Pizza *pizzas = NULL;
OrderDate *order_date = NULL;
PizzaIngredient *pizza_ingredients = NULL;
PizzaCategory *pizza_category = NULL;
int *order_id = NULL;

int total_pizzas_registradas = 0;
int total_order_date = 0;
int total_pizza_ingredients = 0;
int total_pizza_category = 0;
int total_order_id = 0;

// Funciones auxiliares CORREGIDAS
void cargarDatosParaMetricas() {
    // 1. Cargar datos de pizzas
    total_pizzas_registradas = iRegistros;
    pizzas = (Pizza*)malloc(total_pizzas_registradas * sizeof(Pizza));
    for(int i = 0; i < iRegistros; i++) {
        strncpy(pizzas[i].pizza_name, aRegistros[i].pizza_name, 100);
        pizzas[i].total_quantity = aRegistros[i].quantity;
    }

    // 2. Cargar datos por fecha
    total_order_date = iRegistros;
    order_date = (OrderDate*)malloc(total_order_date * sizeof(OrderDate));
    for(int i = 0; i < iRegistros; i++) {
        strncpy(order_date[i].date, aRegistros[i].order_date, 11);
        order_date[i].total_price = aRegistros[i].total_price;
    }

    // 3. Cargar datos de ingredientes
    total_pizza_ingredients = iRegistros;
    pizza_ingredients = (PizzaIngredient*)malloc(total_pizza_ingredients * sizeof(PizzaIngredient));
    for(int i = 0; i < iRegistros; i++) {
        strncpy(pizza_ingredients[i].ingredient, aRegistros[i].pizza_ingredients, 100);
        pizza_ingredients[i].total_quantity = aRegistros[i].quantity;

    }

    // 4. Cargar datos por categoría
    total_pizza_category = iRegistros;
    pizza_category = (PizzaCategory*)malloc(total_pizza_category * sizeof(PizzaCategory));
    for(int i = 0; i < iRegistros; i++) {
        strncpy(pizza_category[i].category, aRegistros[i].pizza_category, 50);
        pizza_category[i].total_quantity = aRegistros[i].quantity;

    }

    // 5. Cargar order_ids
    total_order_id = iRegistros;
    order_id = (int*)malloc(total_order_id * sizeof(int));
    for(int i = 0; i < iRegistros; i++) {
        order_id[i] = aRegistros[i].order_id;
    }
}








//Metricas a pedir (generales)


//pms: Pizza más vendida

void pms() {
   // Verifica si no hay pizzas registradas
   if (total_pizzas_registradas == 0) {
      printf("No hay datos de pizzas.\n");  // Mensaje de error
      return;  // Sale de la función temprano
   }

   // Inicializa las variables con los datos de la primera pizza
   int max_ventas = pizzas[0].total_quantity;  // Toma la cantidad de la primera pizza como máximo inicial
   char pizza_nombre[100];  // Crea un buffer para almacenar el nombre de la pizza
   strcpy(pizza_nombre, pizzas[0].pizza_name);  // Copia el nombre de la primera pizza

   // Recorre todas las pizzas registradas empezando por la segunda (índice 1)
   for (int i = 1; i < total_pizzas_registradas; i++) {
      // Compara si la pizza actual tiene más ventas que el máximo registrado
      if (pizzas[i].total_quantity > max_ventas) {
         max_ventas = pizzas[i].total_quantity;  // Actualiza el máximo de ventas
         strcpy(pizza_nombre, pizzas[i].pizza_name);  // Actualiza el nombre de la pizza líder
      }
      // Si no es mayor, continúa con la siguiente pizza sin hacer cambios
   }

   // Al final del bucle, imprime la pizza con mayor cantidad de ventas
   printf("Pizza más vendida: %s (%d ventas)\n", pizza_nombre, max_ventas);
   // %s se reemplaza por el nombre de la pizza
   // %d se reemplaza por la cantidad de ventas
}


// pls: Pizza menos vendida
void pls() {
   // Verificamos si no hay pizzas registradas
   if (total_pizzas_registradas == 0) {
      printf("No hay datos de pizzas.\n");  // Mensaje de error
      return;  // Sale de la función temprano
   }

   // Inicializamos las variables con los datos de la primera pizza
   int min_ventas = pizzas[0].total_quantity;  // Toma la cantidad de la primera pizza como mínimo inicial
   char pizza_nombre[100];  // Crea un buffer para almacenar el nombre de la pizza
   strcpy(pizza_nombre, pizzas[0].pizza_name);  // Copia el nombre de la primera pizza

   // Recorre todas las pizzas registradas empezando por la segunda (índice 1)
   for (int i = 1; i < total_pizzas_registradas; i++) {
      // Compara si la pizza actual tiene menos ventas que el mínimo registrado
      if (pizzas[i].total_quantity < min_ventas) {
         min_ventas = pizzas[i].total_quantity;  // Actualiza el mínimo de ventas
         strcpy(pizza_nombre, pizzas[i].pizza_name);  // Corregí: faltaba cerrar paréntesis
      }
      // Si no es menor, continúa con la siguiente pizza sin hacer cambios
   }

   // Al final del bucle, imprime la pizza con menor cantidad de ventas
   printf("Pizza menos vendida: %s (%d ventas)\n", pizza_nombre, min_ventas);  // Corregí: cambié max_ventas por min_ventas
}



// dms: Fecha con más ventas en términos de dinero (junto a la cantidad de dinero recaudado)
void dms() {
   // Verificación de seguridad
   if (total_order_date == 0) {
      printf("No hay datos de ventas registradas.\n");
      return;
   }

   // Inicialización con los datos de la primera fecha
   float max_dinero = order_date[0].total_price;  // Usamos total_price en lugar de quantity
   char fecha_max[11];  // Buffer para fecha (formato YYYY-MM-DD usa 11 caracteres)
   strcpy(fecha_max, order_date[0].date);  // Copiamos la fecha

   // Recorremos todas las fechas registradas
   for (int i = 1; i < total_order_date; i++) {
      // Comparamos por dinero recaudado (total_price)
      if (order_date[i].total_price > max_dinero) {
         max_dinero = order_date[i].total_price;
         strcpy(fecha_max, order_date[i].date);  // Corregido: usamos el campo date
      }
   }

   // Mostramos el resultado
   printf("Fecha con más ventas (dinero): %s (Total recaudado: %.2f)\n", fecha_max, max_dinero);
}

// dls: Fecha con menos ventas en términos de dinero (junto a la cantidad de dinero recaudado)
void dls() {
  //Iniciamos con los datos de la primera fecha
  float min_dinero = order_date[0].total_price;  // Usamos total_price en lugar de quantity
  char fecha_min[11]; // Buffer para fecha (formato YYYY-MM-DD usa 11 caracteres)
  strcpy(fecha_min, order_date[0].date); // Copiamos la fecha

  //recorremos todas las fechas registradas
  for (int i = 1; i < total_order_date; i++) {
    //comparamos por dinero recaudado (total_price)
    if (order_date[i].total_price < min_dinero) {
      min_dinero = order_date[i].total_price;
      strcpy(fecha_min, order_date[i].date);
    }
  }
  //mostramos el resultado
  printf("Fecha con menos ventas (dinero): %s (Total recaudado: %.2f)\n", fecha_min, min_dinero);
}

// dmsp: Fecha con más ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)void dmsp() {
void dmsp() {
   int max_pizzas = order_date[0].total_quantity;  // Usamos int, no float (cantidades enteras)
   char fecha_max[11];  // Suficiente para formato YYYY-MM-DD
   strcpy(fecha_max, order_date[0].date);

   // Recorrido optimizado
   for (int i = 1; i < total_order_date; i++) {
      if (order_date[i].total_quantity > max_pizzas) {
         max_pizzas = order_date[i].total_quantity;
         strcpy(fecha_max, order_date[i].date);
   }
}

// Salida mejor formateada
printf("Fecha con más ventas (pizzas): %s (%d pizzas)\n", fecha_max, max_pizzas);
}

//dlsp: Fecha con menos ventas en términos de cantidad de pizzas (junto a la cantidad de pizzas)
void dlsp() {
  int min_pizzas = order_date[0].total_quantity;  // Usamos int, no float (cantidades enteras)
  char fecha_min[11];  // Suficiente para formato YYYY-MM-DD
  strcpy(fecha_min, order_date[0].date);

  //Recorremos las fechas
  for (int i = 1; i < total_order_date; i++) {
    if (order_date[i].total_quantity < min_pizzas) {
      min_pizzas = order_date[i].total_quantity;
      strcpy(fecha_min, order_date[i].date);
    }
  }

//Imprimos
printf("Fecha con menos ventas (pizzas): %s (%d pizzas)\n", fecha_min, min_pizzas);
}

// apo: Promedio de pizzas por orden
void apo() {
   // Verificación básica
   if (total_order_id == 0) {
      printf("Error: No hay órdenes registradas\n");
      return;
   }

   // Variables para acumular
   int total_pizzas = 0;
   int total_orders = total_order_id; // Asumiendo que cada order_id es una orden única

   // Calcular total de pizzas
   for (int i = 0; i < total_order_id; i++) {
      total_pizzas += order_id[i];
      // Corrección del bucle y la lógica que estaba errónea.
      for (int i = 0; i < total_order_id; i++) {
          total_pizzas += order_id[i]; // Se elimina la referencia a order_id[i].total_pizzas, ya que no corresponde.
      }
   }
   // Calcular total de ordenes
   for (int i = 0; i < total_order_id; i++) {
     total_orders += order_id[i];
   }

   // Calcular promedio (con conversión a float para decimales)
   float promedio = (float)total_pizzas / total_orders;

   // Mostrar resultados
   printf("\nEstadísticas de órdenes:\n");
   printf("-----------------------\n");
   printf("Total de pizzas vendidas: %d\n", total_pizzas);
   printf("Total de órdenes: %d\n", total_orders);
   printf("Promedio de pizzas por orden: %.2f\n\n", promedio);
}

//apd: Promedio de pizzas por día
void apd() {
   // Verificación básica
   if (total_order_id == 0) {
      printf("Error: No hay órdenes registradas\n");
      return;
   }
   // Variables para acumular
   int total_pizzas = 0;
   int total_dias = 0;

   // Calcular total de pizzas
   for (int i = 0; i < total_order_id; i++) {
      total_pizzas += order_id[i];
   }
   // Calcular total de dias
   for (int i = 0; i < total_order_id; i++) {
     total_dias += order_id[i];
   }
   //Calcular promedio
   float promedio = (float)total_pizzas / total_dias;

   //Mostrar resultados
   printf("Promedio de pizzas por dia: %.2f\n", promedio);

}
// ims: Ingrediente más vendido
void ims() {
  //Recorremos los ingredientes de pizza
  for (int i = 0; i < total_pizza_ingredients; i++) {
    //Comparamos por cantidad de pizzas
    if (pizza_ingredients[i].total_quantity > total_pizzas_registradas) {
      total_pizzas_registradas = pizza_ingredients[i].total_quantity;
      strcpy(total_pizza_ingredients, pizza_ingredients[i].ingredient);

    }

  printf("El ingrediente mas vendido es %s y tiene %d pizzas\n", total_pizza_ingredients, total_pizzas_registradas);

  }
}
// hp: Cantidad de pizzas por categoría vendidas
void hp() {
  //Recorremos las categorias vendidas
  for (int i = 0; i < total_pizza_category; i++) {
    //Comparamos por cantidad de pizzas
    if (pizza_category[i].total_quantity > total_pizzas_registradas) {
      total_pizzas_registradas = pizza_category[i].total_quantity;
      strcpy(total_pizza_category, pizza_category[i].category);
    }
  printf("La categoria mas vendida es %s y tiene %d pizzas\n", total_pizza_category, total_pizzas_registradas);
  }
}

int main(void) {
    printf("Ingrese el nombre del archivo CSV: ");
    fgets(NombreArchivo, sizeof(NombreArchivo), stdin);
    NombreArchivo[strcspn(NombreArchivo, "\n")] = '\0';
    orchestrator();
    cargarDatosParaMetricas();
    //ingrese el comando/funcion a evaluar();
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

