#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


//Funcion main la cual debe tener la funcionaliad de leer el archivo csv
//Funcion para decidir el valor mas repetido/menos repetido (Pizza mas y
//menos vendida)

//Funcion para extraer la fecha con mas y menos ganancias junto a la cantidad

//Fechas con mas y menos ventas en terminos de cantidad junto a la cantidad

//Funcion para calcular el promedio de una columna (promedio pizzas por orden y dia)

//Funcion para obtener el mayor valor dentro de una columna (Ingrediente mas vendido)

//Funcion para sumar la cant de pizzas por categoria

