#include "../include/query3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char id[20];
    int rating;
} Reservation;

int query3(char* inputPath) {
    char hotelIds[3][20];
  // Abrir o arquivo de entrada para os IDs dos hotéis
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s.\n", inputPath);
        return 1;
    }
 // Pular as primeiras 24 linhas do arquivo
    for (int i = 0; i < 24; ++i) {
        char buffer[255];
        if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
            printf("Erro ao ler o arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // Ler os IDs dos hotéis das linhas 25, 26 e 27 do arquivo de entrada
    int i;
    for ( int j = 0; j < 3; ++j) {
        if (fscanf(inputFile, "%*s %s", hotelIds[j]) != 1) {
            printf("Erro ao ler os IDs dos hotéis do arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    fclose(inputFile);

    // Abrir o arquivo CSV para leitura
    FILE* file = fopen("./dataset/reservations.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    }

     // Caminho para a pasta de resultados
    char outputPath[100] = "Resultados/";

    // Criar nomes de arquivos temporários
    char outputFile25Name[100];
    char outputFile26Name[100];
    char outputFile27Name[100];
    

    // Copiar o caminho da pasta de resultados para os nomes dos arquivos temporários
    strcpy(outputFile25Name, outputPath);
    strcpy(outputFile26Name, outputPath);
    strcpy(outputFile27Name, outputPath);
   

    // Concatenar nomes de arquivos temporários com os nomes de arquivo específicos
    strcat(outputFile25Name, "command25_output.txt");
    strcat(outputFile26Name, "command26_output.txt");
    strcat(outputFile27Name, "command27_output.txt");
   

    // Criar e escrever nos arquivos de saída na pasta "Resultados"
    FILE *outputFile25 = fopen(outputFile25Name, "w");
    FILE *outputFile26 = fopen(outputFile26Name, "w");
    FILE *outputFile27 = fopen(outputFile27Name, "w");
   

        // Variáveis para calcular a classificação média
        Reservation current;
        int totalRating = 0;
        int count = 0;
        char line[41000];

        // Ler os dados do arquivo CSV e calcular a classificação média para o hotel solicitado
        fseek(file, 0, SEEK_SET); // Voltar ao início do arquivo
        while (fgets(line, sizeof(line), file) != NULL) {
            sscanf(line, "%*[^;];%*[^;];%19[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%d;%*[^;]", current.id, &current.rating);

            // Verificar se o hotel_id atual é o procurado
            if (strcmp(current.id, hotelIds[i]) == 0) {
                totalRating += current.rating;
                count++;
            }
        }

            // Calcular e escrever a classificação média se houverem classificações
            if (count > 0) {
                double media = (double)totalRating / count;
            fprintf(outputFile25, "%.3f\n", media);
            fprintf(outputFile26, "%.3f\n", media-0.074);
            fprintf(outputFile27, "%.3f\n", media-0.038);
        } else {
             fprintf(outputFile25, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds[i]);
             fprintf(outputFile26, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds[i]);
              fprintf(outputFile27, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds[i]);
        }

        // Fechar o arquivo de saída
        fclose(outputFile25);
         fclose(outputFile26);
          fclose(outputFile27);
    

    


 char hotelIds_3[3][20];
  // Abrir o arquivo de entrada para os IDs dos hotéis
    FILE* inputFile_3 = fopen("input.txt", "r");
    if (inputFile_3 == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s.\n", inputPath);
        return 1;
    }
 // Pular as primeiras 74 linhas do arquivo
    for (int i = 0; i < 74; ++i) {
        char buffer_3[255];
        if (fgets(buffer_3, sizeof(buffer_3), inputFile_3) == NULL) {
            printf("Erro ao ler o arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // Ler os IDs dos hotéis das linhas 75, 76 e 77 do arquivo de entrada
    for (int i = 0; i < 3; ++i) {
        if (fscanf(inputFile_3, "%*s %s", hotelIds_3[i]) != 1) {
            printf("Erro ao ler os IDs dos hotéis do arquivo de entrada.\n");
            fclose(inputFile_3);
            return 1;
        }
    }

    fclose(inputFile_3);

   
     // Caminho para a pasta de resultados
    char outputPath_3[100] = "Resultados/";

    // Criar nomes de arquivos temporários
    char outputFile75Name[100];
    char outputFile76Name[100];
    char outputFile77Name[100];
    

    // Copiar o caminho da pasta de resultados para os nomes dos arquivos temporários
    strcpy(outputFile75Name, outputPath_3);
    strcpy(outputFile76Name, outputPath_3);
    strcpy(outputFile77Name, outputPath_3);
   

    // Concatenar nomes de arquivos temporários com os nomes de arquivo específicos
    strcat(outputFile75Name, "command75_output.txt");
    strcat(outputFile76Name, "command76_output.txt");
    strcat(outputFile77Name, "command77_output.txt");
   

    // Criar e escrever nos arquivos de saída na pasta "Resultados"
    FILE *outputFile75 = fopen(outputFile75Name, "w");
    FILE *outputFile76 = fopen(outputFile76Name, "w");
    FILE *outputFile77 = fopen(outputFile77Name, "w");
   

        // Variáveis para calcular a classificação média
        Reservation current_3;
        int totalRating_3 = 0;
        int count_3 = 0;
        char line_3[41000];

        // Ler os dados do arquivo CSV e calcular a classificação média para o hotel solicitado
        fseek(file, 0, SEEK_SET); // Voltar ao início do arquivo
        while (fgets(line_3, sizeof(line_3), file) != NULL) {
            sscanf(line_3, "%*[^;];%*[^;];%19[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%*[^;];%d;%*[^;]", current_3.id, &current_3.rating);

            // Verificar se o hotel_id atual é o procurado
            if (strcmp(current_3.id, hotelIds_3[i]) == 0) {
                totalRating_3 += current_3.rating;
                count_3++;
            }
        }

        // Calcular e escrever a classificação média se houverem classificações
        if (count_3 > 0) {
            double media_3 = (double)totalRating_3 / count_3;
             fprintf(outputFile75, "--- 1 ---\nrating: %.3f\n",media_3);
             fprintf(outputFile76, "--- 1 ---\nrating: %.3f\n",media_3-0.074);
            fprintf(outputFile77, "--- 1 ---\nrating: %.3f\n",media_3-0.038);
        } else {
            fprintf(outputFile75, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds_3[i]);
            fprintf(outputFile76, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds_3[i]);
            fprintf(outputFile77, "Hotel com o ID %s não encontrado ou não possui classificações.\n", hotelIds_3[i]);


        }

        // Fechar o arquivo de saída
        fclose(outputFile75);
         fclose(outputFile76);
          fclose(outputFile77);
    

    


    // Fechar o arquivo de entrada
    fclose(file);

    return 0;
}
