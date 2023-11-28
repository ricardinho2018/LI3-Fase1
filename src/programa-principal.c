#include "query1.h"
#include "query3.h"
#include "query4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void create_results_directory() {
    // Cria o diretório "Resultados" se ele não existir
    struct stat st = {0};
    if (stat("Resultados", &st) == -1) {
        mkdir("Resultados", 0700);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso correto: %s <data-folder> <input>\n", argv[0]);
        return 1;
    }

    char data_folder[255];
    char input_file[255];
    
    // Copia o caminho para o dataset e o arquivo de input dos argumentos
    strncpy(data_folder, argv[1], sizeof(data_folder) - 1);
    strncpy(input_file, argv[2], sizeof(input_file) - 1);

    // Constrói o caminho completo para o arquivo CSV usando o caminho do dataset
    char csv_path[255];
    snprintf(csv_path, sizeof(csv_path), "%s/reservations.csv", data_folder);

    // Cria o diretório para salvar os resultados
    create_results_directory();

    // Abre o arquivo de input para leitura
    FILE *input = fopen(input_file, "r");
    if (input == NULL) {
        perror("Erro ao abrir o arquivo de input");
        return 1;
    }

    // Abre o arquivo CSV para leitura usando o caminho completo
    FILE *csv_file = fopen("./dataset/reservations.csv", "r");
    if (csv_file == NULL) {
        perror("Erro ao abrir o arquivo CSV");
        fclose(input);
        return 1;
    }

    // Chama as funções de query
     query1();
    query3();
     query4();
     query7();
     

    // Fecha os arquivos
    fclose(input);
    fclose(csv_file);

    return 0;
}
    
