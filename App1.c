#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_LINE 1024

// Estructura principal
struct Registro {
    int pizza_id;
    int order_id;
    char* pizza_name_id;
    int quantity;
    char* order_date;
    char* order_time;
    float unit_price;
    float total_price;
    char* pizza_size;
    char* pizza_category;
    char* pizza_ingredients;
    char* pizza_name;
};

struct Registro *aRegistros;
int iRegistros;

// Contar registros (sin cabecera)
int CuentaRegistros(char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;
    int count = 0;
    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, file)) count++;
    fclose(file);
    return count - 1;
}

// Cargar archivo
void CargaRegistros(char* filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    iRegistros = CuentaRegistros(filename);
    aRegistros = malloc(sizeof(struct Registro) * iRegistros);

    char buffer[MAX_LINE];
    fgets(buffer, MAX_LINE, file); // cabecera

    for (int i = 0; i < iRegistros; i++) {
        fgets(buffer, MAX_LINE, file);
        buffer[strcspn(buffer, "\n")] = '\0';
        char *token = strtok(buffer, ",");

        aRegistros[i].pizza_id = atoi(token);
        token = strtok(NULL, ","); aRegistros[i].order_id = atoi(token);
        token = strtok(NULL, ","); aRegistros[i].pizza_name_id = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].quantity = atoi(token);
        token = strtok(NULL, ","); aRegistros[i].order_date = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].order_time = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].unit_price = atof(token);
        token = strtok(NULL, ","); aRegistros[i].total_price = atof(token);
        token = strtok(NULL, ","); aRegistros[i].pizza_size = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].pizza_category = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].pizza_ingredients = strdup(token);
        token = strtok(NULL, ","); aRegistros[i].pizza_name = strdup(token);
    }
    fclose(file);
}

// Métricas
char* pms(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int max = -1;
    char *pizza = NULL;
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0)
                total += orders[j].quantity;
        }
        if (total > max) {
            max = total;
            pizza = orders[i].pizza_name;
        }
    }
    snprintf(resultado, 256, "Pizza mas vendida: %s (%d ventas)", pizza, max);
    return resultado;
}

char* pls(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int min = 999999;
    char *pizza = NULL;
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_name, orders[j].pizza_name) == 0)
                total += orders[j].quantity;
        }
        if (total < min) {
            min = total;
            pizza = orders[i].pizza_name;
        }
    }
    snprintf(resultado, 256, "Pizza menos vendida: %s (%d ventas)", pizza, min);
    return resultado;
}

char* dms(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    float max = -1;
    char fecha[64] = "";
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0)
                total += orders[j].total_price;
        }
        if (total > max) {
            max = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    snprintf(resultado, 256, "Fecha con mas ventas (dinero): %s (%.2f)", fecha, max);
    return resultado;
}

char* dls(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    float min = 999999;
    char fecha[64] = "";
    for (int i = 0; i < *size; i++) {
        float total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0)
                total += orders[j].total_price;
        }
        if (total < min) {
            min = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    snprintf(resultado, 256, "Fecha con menos ventas (dinero): %s (%.2f)", fecha, min);
    return resultado;
}

char* dmsp(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int max = -1;
    char fecha[64] = "";
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0)
                total += orders[j].quantity;
        }
        if (total > max) {
            max = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    snprintf(resultado, 256, "Fecha con mas ventas (pizzas): %s (%d pizzas)", fecha, max);
    return resultado;
}

char* dlsp(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int min = 999999;
    char fecha[64] = "";
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0)
                total += orders[j].quantity;
        }
        if (total < min) {
            min = total;
            strcpy(fecha, orders[i].order_date);
        }
    }
    snprintf(resultado, 256, "Fecha con menos ventas (pizzas): %s (%d pizzas)", fecha, min);
    return resultado;
}

char* apo(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int total_pizzas = 0;
    int total_ordenes = 0;
    for (int i = 0; i < *size; i++) total_pizzas += orders[i].quantity;
    for (int i = 0; i < *size; i++) {
        int unique = 1;
        for (int j = 0; j < i; j++) {
            if (orders[i].order_id == orders[j].order_id) {
                unique = 0;
                break;
            }
        }
        if (unique) total_ordenes++;
    }
    float promedio = (float)total_pizzas / total_ordenes;
    snprintf(resultado, 256, "Promedio de pizzas por orden: %.2f", promedio);
    return resultado;
}

char* apd(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    int total_pizzas = 0;
    int total_dias = 0;
    for (int i = 0; i < *size; i++) total_pizzas += orders[i].quantity;
    for (int i = 0; i < *size; i++) {
        int unique = 1;
        for (int j = 0; j < i; j++) {
            if (strcmp(orders[i].order_date, orders[j].order_date) == 0) {
                unique = 0;
                break;
            }
        }
        if (unique) total_dias++;
    }
    float promedio = (float)total_pizzas / total_dias;
    snprintf(resultado, 256, "Promedio de pizzas por dia: %.2f", promedio);
    return resultado;
}

char* ims(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    char *mas_vendido = NULL;
    int max_count = 0;
    for (int i = 0; i < *size; i++) {
        char *ingredientes = strdup(orders[i].pizza_ingredients);
        char *token = strtok(ingredientes, ",");
        while (token) {
            int count = 0;
            for (int j = 0; j < *size; j++) {
                if (strstr(orders[j].pizza_ingredients, token))
                    count += orders[j].quantity;
            }
            if (count > max_count) {
                max_count = count;
                mas_vendido = token;
            }
            token = strtok(NULL, ",");
        }
        free(ingredientes);
    }
    snprintf(resultado, 256, "Ingrediente mas vendido: %s (%d usos)", mas_vendido, max_count);
    return resultado;
}

char* hp(int *size, struct Registro *orders) {
    char *resultado = malloc(256);
    char *categoria = NULL;
    int max = -1;
    for (int i = 0; i < *size; i++) {
        int total = 0;
        for (int j = 0; j < *size; j++) {
            if (strcmp(orders[i].pizza_category, orders[j].pizza_category) == 0)
                total += orders[j].quantity;
        }
        if (total > max) {
            max = total;
            categoria = orders[i].pizza_category;
        }
    }
    snprintf(resultado, 256, "Categoria con mas ventas: %s (%d pizzas)", categoria, max);
    return resultado;
}

// Tipos de métrica
typedef char* (*MetricFunction)(int*, struct Registro*);
typedef struct {
    char *nombre;
    MetricFunction funcion;
} Metrica;

Metrica metricas[] = {
    {"pms", pms}, {"pls", pls}, {"dms", dms}, {"dls", dls},
    {"dmsp", dmsp}, {"dlsp", dlsp}, {"apo", apo}, {"apd", apd},
    {"ims", ims}, {"hp", hp}
};

int NUM_METRICAS = sizeof(metricas)/sizeof(Metrica);

// Main
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Uso: %s archivo.csv metrica1 metrica2 ...\n", argv[0]);
        return 1;
    }
    CargaRegistros(argv[1]);
    for (int i = 2; i < argc; i++) {
        for (int j = 0; j < NUM_METRICAS; j++) {
            if (strcmp(argv[i], metricas[j].nombre) == 0) {
                char *res = metricas[j].funcion(&iRegistros, aRegistros);
                printf("%s\n", res);
                free(res);
                break;
            }
        }
    }
    return 0;
}
