#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FLIGHTS 1000
#define MAX_AIRPORTS 100

struct Flight {
    char name[11];
    char airline[256];
    char plane_model[256];
    int total_seats;
    char origin[4];
    char destination[4];
    char schedule_departure_date[20];
    char schedule_arrival_date[20];
    char real_departure_date[20];
    char real_arrival_date[20];
    char pilot[256];
    char copilot[256];
    char notes[256];
};

long long calculateDelayInSeconds(char *schedule, char *real) {
    struct tm tm_schedule = {0};
    struct tm tm_real = {0};

    // Converte as datas de string para estruturas tm
    sscanf(schedule, "%4d/%2d/%2d %2d:%2d:%2d",
           &tm_schedule.tm_year, &tm_schedule.tm_mon, &tm_schedule.tm_mday,
           &tm_schedule.tm_hour, &tm_schedule.tm_min, &tm_schedule.tm_sec);
    tm_schedule.tm_year -= 1900;  // Ano é contado a partir de 1900
    tm_schedule.tm_mon -= 1;      // Meses são contados de 0 a 11

    sscanf(real, "%4d/%2d/%2d %2d:%2d:%2d",
           &tm_real.tm_year, &tm_real.tm_mon, &tm_real.tm_mday,
           &tm_real.tm_hour, &tm_real.tm_min, &tm_real.tm_sec);
    tm_real.tm_year -= 1900;  // Ano é contado a partir de 1900
    tm_real.tm_mon -= 1;      // Meses são contados de 0 a 11

    // Converte as estruturas tm para time_t
    time_t schedule_time = mktime(&tm_schedule);
    time_t real_time = mktime(&tm_real);

    // Calcula o atraso em segundos
    long long delay = difftime(real_time, schedule_time);

    return delay;
}

// Função para comparar os atrasos para qsort
int compareDelays(const void *a, const void *b) {
    const long long *delayA = (const long long *)a;
    const long long *delayB = (const long long *)b;

    if (*delayA > *delayB) {
        return 1;
    } else if (*delayA < *delayB) {
        return -1;
    } else {
        return 0;
    }
}

int compareAeroportos(const void *a, const void *b, void *medians) {
    const struct Flight *flightA = (const struct Flight *)a;
    const struct Flight *flightB = (const struct Flight *)b;

    // Converte medians para long long*
    long long *airportMedians = (long long *)medians;

    // Converte códigos de aeroporto para índices
    int indexA = atoi(flightA->origin);
    int indexB = atoi(flightB->origin);

    // Verifica se os índices estão dentro dos limites do array medians
    if (indexA < 0 || indexA >= MAX_AIRPORTS || indexB < 0 || indexB >= MAX_AIRPORTS) {
        // Trate aqui o caso em que os índices estão fora dos limites
        // Pode ser útil imprimir uma mensagem de erro ou retornar um valor especial
        return 0; // ou outro valor apropriado
    }

    // Compara as medianas
    if (airportMedians[indexA] > airportMedians[indexB]) {
        return -1;
    } else if (airportMedians[indexA] < airportMedians[indexB]) {
        return 1;
    } else {
        // Se as medianas forem iguais, usa o nome do aeroporto como critério de desempate
        return strcmp(flightA->origin, flightB->origin);
    }
}




// Função para calcular a mediana dos atrasos para um aeroporto específico
long long calculateMedian(const char *airportCode, char *real_departure_date, struct Flight *flights, int numFlights) {
    long long delays[MAX_FLIGHTS];
    int count = 0;

    // Calcula os atrasos para voos com origem no aeroporto específico
    for (int i = 0; i < numFlights; i++) {
        if (strcmp(flights[i].origin, airportCode) == 0) {
            delays[count++] = calculateDelayInSeconds(flights[i].schedule_departure_date, flights[i].real_departure_date);
        }
    }

    // Ordena os atrasos para calcular a mediana
    qsort(delays, count, sizeof(long long), compareDelays);

    // Calcula a mediana
    if (count % 2 == 0) {
        // Se o número de atrasos for par, calcula a média dos dois valores centrais
        return (delays[count / 2 - 1] + delays[count / 2]) / 2;
    } else {
        // Se o número de atrasos for ímpar, retorna o valor central
        return delays[count / 2];
    }
}

int query7(char* inputPath) {


   char n[2][4];
  // Abrir o arquivo de entrada para os IDs dos hotéis
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s.\n", inputPath);
        return 1;
    }
 // Pular as primeiras 36 linhas do arquivo
    for (int i = 0; i < 36; ++i) {
        char buffer[255];
        if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
            printf("Erro ao ler o arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    
    
    for ( int j = 0; j < 2; ++j) {
        if (fscanf(inputFile, "%*s %s", n[j]) != 1) {
            printf("Erro ao ler os IDs dos hotéis do arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    fclose(inputFile);

    // Abrir o arquivo CSV para leitura
    FILE* file = fopen("./dataset/flights.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo CSV.\n");
        return 1;
    }

     // Caminho para a pasta de resultados
    char outputPath[20] = "Resultados/";

    // Criar nomes de arquivos temporários
    char outputFile37Name[20];
    char outputFile38Name[20];
    
    

    // Copiar o caminho da pasta de resultados para os nomes dos arquivos temporários
    strcpy(outputFile37Name, outputPath);
    strcpy(outputFile38Name, outputPath);
   
   

    // Concatenar nomes de arquivos temporários com os nomes de arquivo específicos
    strcat(outputFile37Name, "command37_output.txt");
    strcat(outputFile38Name, "command38_output.txt");
   

    // Criar e escrever nos arquivos de saída na pasta "Resultados"
    FILE *outputFile37 = fopen(outputFile37Name, "w");
    FILE *outputFile38 = fopen(outputFile38Name, "w");
   

  
    //int N;
   // printf("Digite o valor de N: ");
   // scanf("%d", &N);

    // Lê o cabeçalho do arquivo CSV
    char header[1024];
    fgets(header, sizeof(header), file);

    // Array para armazenar informações de voo
    struct Flight flights[MAX_FLIGHTS];
    int numFlights = 0;  // Adicionado para rastrear o número de voos

    // Lê os dados do arquivo CSV
    while (fgets(header, sizeof(header), file)) {
        sscanf(header, "%10[^;];%255[^;];%255[^;];%d;%3[^;];%3[^;];%19[^;];%19[^;];%19[^;];%19[^;];%255[^;];%255[^;];%255[^\n]",
               flights[numFlights].name, flights[numFlights].airline, flights[numFlights].plane_model,
               &flights[numFlights].total_seats, flights[numFlights].origin, flights[numFlights].destination,
               flights[numFlights].schedule_departure_date, flights[numFlights].schedule_arrival_date,
               flights[numFlights].real_departure_date, flights[numFlights].real_arrival_date,
               flights[numFlights].pilot, flights[numFlights].copilot, flights[numFlights].notes);

        numFlights++;
    }

    fclose(file);

    // Array para armazenar medianas de atraso para cada aeroporto
    long long medians[MAX_AIRPORTS] = {0};  // Inicializa todos os valores com zero

        // Calcula os atrasos e as medianas de atraso para cada aeroporto
        for (int i = 0; i < numFlights; i++) {
            long long delay = calculateDelayInSeconds(flights[i].schedule_departure_date, flights[i].real_departure_date);
            // Adiciona o atraso ao aeroporto correspondente
            medians[atoi(flights[i].origin)] += delay;
        }



    // Divide a soma dos atrasos pelo número de voos para obter a mediana para cada aeroporto
    for (int i = 0; i < MAX_AIRPORTS; i++) {
        if (medians[i] != 0) {
            // Verifica se o número de voos para o aeroporto é maior que zero antes de calcular a mediana
            int numFlightsForAirport = 0;  // Inicializa com zero
            for (int j = 0; j < numFlights; j++) {
                if (atoi(flights[j].origin) == i) {
                    numFlightsForAirport++;
                }
            }

        if (numFlightsForAirport > 0) {
            // Corrige para calcular a mediana, não a média
            long long *delaysForAirport = malloc(sizeof(long long) * numFlightsForAirport);
            if (delaysForAirport == NULL) {
                perror("Erro ao alocar memória");
                return 1;
            }

            int count = 0;
            for (int j = 0; j < numFlights; j++) {
                if (atoi(flights[j].origin) == i) {
                    delaysForAirport[count++] = calculateDelayInSeconds(flights[j].schedule_departure_date, flights[j].real_departure_date);
                }
            }

            qsort(delaysForAirport, numFlightsForAirport, sizeof(long long), compareDelays);

            int middleIndex = numFlightsForAirport / 2;
            if (numFlightsForAirport % 2 == 0) {
                // Se o número de voos for par, calcula a média dos dois valores centrais
                medians[i] = (delaysForAirport[middleIndex - 1] + delaysForAirport[middleIndex]) / 2;
            } else {
                // Se o número de voos for ímpar, retorna o valor central
                medians[i] = delaysForAirport[middleIndex];
            }

            free(delaysForAirport);
        }
    }
}





// ...

// Imprime os top N aeroportos no arquivo de resultados
for (int i = 0; i < numFlights; i++) {
    // Imprima os detalhes do aeroporto, como nome e mediana, nos arquivos
    fprintf(outputFile37, "%s;%lld\n", flights[i].origin, medians[atoi(flights[i].origin)]);

    // Ajuste para imprimir em outputFile38 apenas se i for menor que 20
    if (i < 20) {
        // Correção para garantir que a origem seja impressa corretamente
        fprintf(outputFile38, "%s;%lld\n", flights[i].origin, medians[atoi(flights[i].origin)]);
    }
}

fclose(outputFile37);
fclose(outputFile38);


    return 0;
}