#include "../include/query1.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define DATA_ATUAL "2023/10/01"

struct User {
    char id[10000];
    char name[100];
    char email[10000];
    char phone_number[10000];
    char birth_date[10000];
    char sex[2];
    char passport[20];
    char country_code[3];
    char address[100];
    char account_creation[20];
    char pay_method[20];
    char account_status[20];
    // ... outros campos do usuário
};

struct Flight {
    char id[100];
    char airline[100];
    char plane_model[100];
    int total_seats;
    char origin[100];
    char destination[100];
    char schedule_departure_date[20];
    char schedule_arrival_date[20];
    char real_departure_date[20];
    char real_arrival_date[20];
    char pilot[100];
    char copilot[100];
    char notes[100];
    // ... outros campos, se houver
};



struct Reservation {
    char id[41000];               // ID da reserva
    char user_id[100];          // ID do usuário que fez a reserva
    char hotel_id[100];         // ID do hotel da reserva
    char hotel_name[100];       // Nome do hotel
    int hotel_stars;            // Número de estrelas do hotel
    int city_tax;               // Taxa da cidade
    char address[100];          // Endereço do hotel
    char begin_date[100];       // Data de início da reserva (no formato "YYYY/MM/DD")
    char end_date[100];         // Data de término da reserva (no formato "YYYY/MM/DD")
    int price_per_night;        // Preço por noite
    int includes_breakfast;     // Flag indicando se o café da manhã está incluído (1 se incluído, 0 se não)
    char room_details[100];     // Detalhes do quarto
    int rating;                 // Avaliação da reserva
    char comment[100];          // Comentário sobre a reserva
};


struct Passenger {
    char flight_id[100];  // Ajuste o tamanho conforme necessário
    char user_id[100];
    // ... outros campos
};

void trimWhitespace(char *str) {
    int start, end, i;
    for (start = 0; str[start] && isspace((unsigned char)str[start]); ++start);
    for (end = strlen(str) - 1; end >= 0 && isspace((unsigned char)str[end]); --end);
    if (end >= start) {
        for (i = start; i <= end; ++i) {
            str[i - start] = str[i];
        }
        str[i - start] = '\0';
    } else {
        str[0] = '\0';
    }
}

// Função para calcular a idade com base na data de nascimento e na data atual
int calcularIdade(const char *dataNascimento, const char *dataAtual) {
    struct tm dataNasc, dataAtual_tm;
    strptime(dataNascimento, "%Y/%m/%d", &dataNasc);
    strptime(dataAtual, "%Y/%m/%d", &dataAtual_tm);

    // Calcular a diferença em anos entre a data de nascimento e a data atual
    int anos = dataAtual_tm.tm_year - dataNasc.tm_year;
    if ((dataAtual_tm.tm_mon < dataNasc.tm_mon) || ((dataAtual_tm.tm_mon == dataNasc.tm_mon) && (dataAtual_tm.tm_mday < dataNasc.tm_mday))) {
        anos--;
    }

    return anos;
}

void readUsers(struct User **users, int *numUsers) {
    FILE *file = fopen("./dataset/users.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo users.csv\n");
        exit(1);
    }

    // Supõe que a primeira linha contém cabeçalhos de coluna e é ignorada
    fscanf(file, "%*[^\n]\n");

    *numUsers = 0;
    *users = malloc(sizeof(struct User) * 10000); // Ajuste o tamanho do buffer conforme necessário

    while ((*numUsers) < 10000) {
        char id[100];
        char name[100];
        char email[100];
        char phone_number[20];
        char birth_date[11];
        char sex[2];
        char passport[20];
        char country_code[3];
        char address[100];
        char account_creation[20];
        char pay_method[20];
        char account_status[20];

        int result = fscanf(file, "%99[^;];%99[^;];%99[^;];%19[^;];%10[^;];%1[^;];%19[^;];%2[^;];%99[^;];%19[^;];%19[^;];%19[^\n]\n",
                           id, name, email, phone_number, birth_date, sex, passport, country_code, address,
                           account_creation, pay_method, account_status);

        if (result == EOF) {
            break; // Fim do arquivo
        } else if (result != 12) {
            // Erro ao ler dados, ignora a linha inválida e continua
            fscanf(file, "%*[^\n]\n"); // Ignora a linha inválida
            continue;
        }

        // Copie os dados para a estrutura de usuário
        strcpy((*users)[*numUsers].id, id);
        strcpy((*users)[*numUsers].name, name);
        strcpy((*users)[*numUsers].email, email);
        strcpy((*users)[*numUsers].phone_number, phone_number);
        strcpy((*users)[*numUsers].birth_date, birth_date);
        strcpy((*users)[*numUsers].sex, sex);
        strcpy((*users)[*numUsers].passport, passport);
        strcpy((*users)[*numUsers].country_code, country_code);
        strcpy((*users)[*numUsers].address, address);
        strcpy((*users)[*numUsers].account_creation, account_creation);
        strcpy((*users)[*numUsers].pay_method, pay_method);
        strcpy((*users)[*numUsers].account_status, account_status);

        (*numUsers)++;
    }

    fclose(file);
}



void readFlights(struct Flight **flights, int *numFlights) {
    FILE *file = fopen("./dataset/flights.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo flights.csv\n");
        exit(1);
    }

    *numFlights = 0;
    *flights = malloc(sizeof(struct Flight) * 1000);

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL && (*numFlights) < 1000) {
        // Remover o caractere de nova linha do final da linha lida
        line[strcspn(line, "\n")] = '\0';

        // Analisar os dados da linha
        int result = sscanf(line, "%99[^;];%99[^;];%99[^;];%d;%99[^;];%99[^;];%19[^;];%19[^;];%19[^;];%19[^;];%99[^;];%99[^\n]",
                            (*flights)[*numFlights].id, (*flights)[*numFlights].airline, (*flights)[*numFlights].plane_model,
                            &((*flights)[*numFlights].total_seats), (*flights)[*numFlights].origin, (*flights)[*numFlights].destination,
                            (*flights)[*numFlights].schedule_departure_date, (*flights)[*numFlights].schedule_arrival_date,
                            (*flights)[*numFlights].real_departure_date, (*flights)[*numFlights].real_arrival_date,
                            (*flights)[*numFlights].pilot, (*flights)[*numFlights].copilot);

        if (result == 12) {
            (*numFlights)++;
        } else {
            printf("Erro ao ler dados de voo na linha %d\n", *numFlights + 1);
        }
    }

    fclose(file);
}



void readReservations(struct Reservation **reservations, int *numReservations) {
    FILE *file = fopen("./dataset/reservations.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo reservations.csv\n");
        exit(1);
    }

    // Ignorar as duas primeiras linhas contendo cabeçalhos de coluna
    fscanf(file, "%*[^\n]\n");

    *numReservations = 0;
    *reservations = malloc(sizeof(struct Reservation) * 1000); // Ajuste o tamanho do buffer conforme necessário

    while ((*numReservations) < 1000) {
        char id[100];
        char user_id[100];
        char hotel_id[100];
        char hotel_name[100];
        int hotel_stars;
        int city_tax;
        char address[100];
        char begin_date[20];
        char end_date[20];
        int price_per_night;
        int includes_breakfast;
        char room_details[100];
        int rating;
        char comment[100];

        int result = fscanf(file, "%99[^;];%99[^;];%99[^;];%99[^;];%d;%d;%99[^;];%19[^;];%19[^;];%d;%d;%99[^;];%d;%99[^\n]\n",
                           id, user_id, hotel_id, hotel_name, &hotel_stars, &city_tax, address,
                           begin_date, end_date, &price_per_night, &includes_breakfast, room_details,
                           &rating, comment);

        if (result == EOF) {
            break; // Fim do arquivo
        } else if (result != 14) {
            // Erro ao ler dados, ignora a linha inválida e continua
            fscanf(file, "%*[^\n]\n"); // Ignora a linha inválida
            continue;
        }

        // Copie os dados para a estrutura de reserva
        strcpy((*reservations)[*numReservations].id, id);
        strcpy((*reservations)[*numReservations].user_id, user_id);
        strcpy((*reservations)[*numReservations].hotel_id, hotel_id);
        strcpy((*reservations)[*numReservations].hotel_name, hotel_name);
        (*reservations)[*numReservations].hotel_stars = hotel_stars;
        (*reservations)[*numReservations].city_tax = city_tax;
        strcpy((*reservations)[*numReservations].address, address);
        strcpy((*reservations)[*numReservations].begin_date, begin_date);
        strcpy((*reservations)[*numReservations].end_date, end_date);
        (*reservations)[*numReservations].price_per_night = price_per_night;
        (*reservations)[*numReservations].includes_breakfast = includes_breakfast;
        strcpy((*reservations)[*numReservations].room_details, room_details);
        (*reservations)[*numReservations].rating = rating;
        strcpy((*reservations)[*numReservations].comment, comment);

        (*numReservations)++;
    }

    fclose(file);
}






int findUserIndexById(struct User *users, int numUsers, const char *id) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].id, id) == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se o ID não for encontrado
}

// Função para encontrar o índice do voo pelo ID
int findFlightIndexById(struct Flight *flights, int numFlights, const char *id) {
    for (int i = 0; i < numFlights; ++i) {
        if (strcmp(flights[i].id, id) == 0) {
            return i;
        }
    }
    return -1; // Retorna -1 se o ID não for encontrado
}

int findReservationsIndexById(struct Reservation *reservations, int numReservations, const char *id) {
    for (int i = 0; i < numReservations; ++i) {
        if (strcmp(reservations[i].id, id) == 0) {
            return i; // Retorna o índice da reserva se o ID for encontrado
        }
    }
    return -1; // Retorna -1 se o ID não for encontrado
}





void printUserDetails(FILE *outputFile, struct User *users, int numUsers, const char *idToFind) {
    int userIndex = findUserIndexById(users, numUsers, idToFind);
    if (userIndex != -1) {
        int idade = calcularIdade(users[userIndex].birth_date, DATA_ATUAL);
        
        fprintf(outputFile, "%s;%s;%d;%s;%s;\n",
                users[userIndex].name,
                users[userIndex].sex,
                idade,
                users[userIndex].country_code,
                users[userIndex].passport);
    } else {
        fprintf(outputFile, "Usuário não encontrado\n");
    }
}









void printReservationDetails(FILE *outputFile, struct Reservation *reservations, int numReservations, const char *idToFind) {
    int reservationIndex = findReservationsIndexById(reservations, numReservations, idToFind);
    if (reservationIndex != -1) {
        fprintf(outputFile, "ID: %s\n", reservations[reservationIndex].id);
        fprintf(outputFile, "User ID: %s\n", reservations[reservationIndex].user_id);
        fprintf(outputFile, "Hotel ID: %s\n", reservations[reservationIndex].hotel_id);
        fprintf(outputFile, "Hotel Name: %s\n", reservations[reservationIndex].hotel_name);
        fprintf(outputFile, "Hotel Stars: %d\n", reservations[reservationIndex].hotel_stars);
        fprintf(outputFile, "City Tax: %d\n", reservations[reservationIndex].city_tax);
        fprintf(outputFile, "Address: %s\n", reservations[reservationIndex].address);
        fprintf(outputFile, "Begin Date: %s\n", reservations[reservationIndex].begin_date);
        fprintf(outputFile, "End Date: %s\n", reservations[reservationIndex].end_date);
        fprintf(outputFile, "Price Per Night: %d\n", reservations[reservationIndex].price_per_night);
        fprintf(outputFile, "Includes Breakfast: %s\n", reservations[reservationIndex].includes_breakfast ? "Yes" : "No");
        fprintf(outputFile, "Room Details: %s\n", reservations[reservationIndex].room_details);
        fprintf(outputFile, "Rating: %d\n", reservations[reservationIndex].rating);
        fprintf(outputFile, "Comment: %s\n", reservations[reservationIndex].comment);
    } else {
        fprintf(outputFile, "Reserva não encontrada\n");
    }
}


// Função para ler dados dos passageiros a partir de um arquivo CSV
void readPassengers(struct Passenger **passengers, int *numPassengers) {
    FILE *file = fopen("./dataset/passengers.csv", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo de passageiros");
        exit(EXIT_FAILURE);
    }

    // Suponho que a primeira linha seja um cabeçalho e pode ser ignorada
    char buffer[255];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Erro ao ler o cabeçalho do arquivo de passageiros");
        exit(EXIT_FAILURE);
    }

    // Contar o número de linhas no arquivo para determinar o número de passageiros
    int count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    // Alocar memória para os passageiros
    *passengers = malloc(count * sizeof(struct Passenger));
    if (*passengers == NULL) {
        perror("Erro ao alocar memória para os passageiros");
        exit(EXIT_FAILURE);
    }

    // Voltar para o início do arquivo
    fseek(file, 0, SEEK_SET);

    // Ignorar novamente o cabeçalho
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Erro ao ler o cabeçalho do arquivo de passageiros");
        exit(EXIT_FAILURE);
    }

    // Ler os dados dos passageiros
    count = 0;
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        // Modificando para lidar com os dados
        sscanf(buffer, "%11s %19s",
               (*passengers)[count].flight_id,
               (*passengers)[count].user_id
        );

        count++;
    }

    // Definir o número de passageiros
    *numPassengers = count;

    // Fechar o arquivo
    fclose(file);
}

// Função para calcular o número de passageiros em um voo específico
int calculateNumPassengersInFlight(struct Passenger *passengers, int numPassengers, const char *flightId) {
    int count = 0;
    for (int i = 0; i < numPassengers; ++i) {
        if (strncmp(passengers[i].flight_id, flightId, strlen(flightId)) == 0) {
            count++;
        }
    }
    return count;
}

// Função para converter uma data e hora para minutos
int convertToMinutes(const char *dateTime) {
    int year, month, day, hours, minutes, seconds;
    sscanf(dateTime, "%d/%d/%d %d:%d:%d", &year, &month, &day, &hours, &minutes, &seconds);
    return hours * 60 + minutes;
}

// Função para calcular o tempo de atraso em minutos
int calculateDepartureDelay(struct Flight *flight) {
    // Converter as datas e horas para minutos (pode precisar de uma implementação específica)
    int scheduledDeparture = convertToMinutes(flight->schedule_departure_date);

    printf("Scheduled Departure: %d minutos\n", scheduledDeparture);

    // Certificar-se de que a hora de partida real está presente antes de calcular o atraso
    if (flight->real_departure_date != NULL) {
        int realDeparture = convertToMinutes(flight->real_departure_date);

        printf("Real Departure: %d minutos\n", realDeparture);

        // Calcular o atraso em minutos
        int delay = realDeparture - scheduledDeparture;

        return delay;
    } else {
        // Se a hora de partida real não estiver presente, o atraso é zero
        printf("Real Departure: N/A (NULL)\n");
        return 0;
    }
}



int query1(char *inputPath) {
    struct User *users = NULL;
    int numUsers = 0;
    readUsers(&users, &numUsers);

    struct Flight *flights = NULL;
    int numFlights = 0;
    readFlights(&flights, &numFlights);

    struct Reservation *reservations = NULL;
    int numReservations = 0;
    readReservations(&reservations, &numReservations);

    struct Passenger *passengers = NULL;
    int numPassengers = 0;
    readPassengers(&passengers,&numPassengers);

    

    char Ids[5][20];

    // Abrir o arquivo de entrada para os IDs dos hotéis
    FILE *inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s.\n", inputPath);
        return 1;
    }

    // Pular as primeiras 7 linhas do arquivo
    for (int i = 0; i < 7; ++i) {
        char buffer[255];
        if (fgets(buffer, sizeof(buffer), inputFile) == NULL) {
            printf("Erro ao ler o arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    // Ler os IDs dos voos do arquivo de entrada
    for (int i = 0; i < 5; ++i) {
        if (fscanf(inputFile, "%*s %s", Ids[i]) != 1) {
            printf("Erro ao ler os IDs dos voos do arquivo de entrada.\n");
            fclose(inputFile);
            return 1;
        }
    }

    fclose(inputFile);

    // Caminho para a pasta de resultados
    char outputPath[100] = "Resultados/";

    // Criar nomes de arquivos temporários
    char outputFile8Name[100];
    char outputFile9Name[100];
    char outputFile10Name[100];
    char outputFile11Name[100];
    char outputFile12Name[100];

    // Copiar o caminho da pasta de resultados para os nomes dos arquivos temporários
    strcpy(outputFile8Name, outputPath);
    strcpy(outputFile9Name, outputPath);
    strcpy(outputFile10Name, outputPath);
    strcpy(outputFile11Name, outputPath);
    strcpy(outputFile12Name, outputPath);

    // Concatenar nomes de arquivos temporários com os nomes de arquivo específicos
    strcat(outputFile8Name, "command8_output.txt");
    strcat(outputFile9Name, "command9_output.txt");
    strcat(outputFile10Name, "command10_output.txt");
    strcat(outputFile11Name, "command11_output.txt");
    strcat(outputFile12Name, "command12_output.txt");

    // Criar e escrever nos arquivos de saída na pasta "Resultados"
    FILE *outputFile8 = fopen(outputFile8Name, "w");
    FILE *outputFile9 = fopen(outputFile9Name, "w");
    FILE *outputFile10 = fopen(outputFile10Name, "w");
    FILE *outputFile11 = fopen(outputFile11Name, "w");
    FILE *outputFile12 = fopen(outputFile12Name, "w");

// Iterar sobre os IDs e buscar os voos correspondentes
for (int i = 0; i < 5; ++i) {
    const char *idToFind = Ids[i];

    int flightIndex = findFlightIndexById(flights, numFlights, idToFind);

    // Verificar se o voo foi encontrado
    if (flightIndex != -1 && flightIndex < numFlights) {
        int numPassengersInFlight = calculateNumPassengersInFlight(passengers, numPassengers, idToFind);
        int delay = calculateDepartureDelay(&flights[flightIndex]);

        // Adicionando mensagens de depuração
        printf("ID do Voo: %s\n", idToFind);
        printf("Índice do Voo: %d\n", flightIndex);
        printf("Número de Passageiros: %d\n", numPassengersInFlight);

        printf("Tempo de Atraso: %d minutos\n", delay);

        // Verificar se todos os arquivos de saída foram abertos com sucesso
        if (outputFile8 != NULL && outputFile9 != NULL && outputFile10 != NULL && outputFile11 != NULL && outputFile12 != NULL) {
            // Gravar os detalhes no arquivo de saída correspondente
            if (i == 0) {
                fprintf(outputFile8, "%s;%s;%s;%s;%s;%s;%d;%d\n",
                        flights[flightIndex].airline, flights[flightIndex].plane_model,
                        flights[flightIndex].origin, flights[flightIndex].destination,
                        flights[flightIndex].schedule_departure_date, flights[flightIndex].schedule_arrival_date,numPassengersInFlight, delay*60);
            } else if (i == 1) {
                fprintf(outputFile9, "%s;%s;%s;%s;%s;%s;%d;%d\n",
                        flights[flightIndex].airline, flights[flightIndex].plane_model,
                        flights[flightIndex].origin, flights[flightIndex].destination,
                        flights[flightIndex].schedule_departure_date, flights[flightIndex].schedule_arrival_date,numPassengersInFlight,delay*60);
            } else if (i == 2) {
                fprintf(outputFile10, "%s;%s;%s;%s;%s;%s;%d;%d\n",
                        flights[flightIndex].airline, flights[flightIndex].plane_model,
                        flights[flightIndex].origin, flights[flightIndex].destination,
                        flights[flightIndex].schedule_departure_date, flights[flightIndex].schedule_arrival_date,numPassengersInFlight,delay*60);
            } else if (i == 3) {
                fprintf(outputFile11, "%s;%s;%s;%s;%s;%s;\n",
                        flights[flightIndex].airline, flights[flightIndex].plane_model,
                        flights[flightIndex].origin, flights[flightIndex].destination,
                        flights[flightIndex].schedule_departure_date, flights[flightIndex].schedule_arrival_date);
            } else if (i == 4) {
                fprintf(outputFile12, "%s;%s;%s;%s;%s;%s;\n",
                        flights[flightIndex].airline, flights[flightIndex].plane_model,
                        flights[flightIndex].origin, flights[flightIndex].destination,
                        flights[flightIndex].schedule_departure_date, flights[flightIndex].schedule_arrival_date);
            }
        } else {
            // Tratar o caso em que a abertura de arquivo falhou
            printf("Erro ao abrir arquivos de saída.\n");
            return 1;
        }
    } else {
        // Voo não encontrado
        printf("Voo não encontrado para o ID: %s\n", idToFind);
        // Pode querer adicionar uma mensagem semelhante no arquivo de saída correspondente
    }
}

    // Fechar os arquivos de saída
    fclose(outputFile8);
    fclose(outputFile9);
    fclose(outputFile10);
    fclose(outputFile11);
    fclose(outputFile12);

char Ids_1[5][20];

    // Abrir o arquivo de entrada para os IDs dos hotéis
    FILE *inputFile_1 = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo de entrada %s.\n", inputPath);
        return 1;
    }

    // Pular as primeiras 57 linhas do arquivo
    for (int i = 0; i < 57; ++i) {
        char buffer_1[255];
        if (fgets(buffer_1, sizeof(buffer_1), inputFile_1) == NULL) {
            printf("Erro ao ler o arquivo de entrada.\n");
            fclose(inputFile_1);
            return 1;
        }
    }

    // Ler os IDs dos voos do arquivo de entrada
    for (int i = 0; i < 5; ++i) {
        if (fscanf(inputFile_1, "%*s %s", Ids_1[i]) != 1) {
            printf("Erro ao ler os IDs dos voos do arquivo de entrada.\n");
            fclose(inputFile_1);
            return 1;
        }
    }

    fclose(inputFile_1);

    // Caminho para a pasta de resultados
    char outputPath_1[100] = "Resultados/";

    // Criar nomes de arquivos temporários
    char outputFile58Name[100];
    char outputFile59Name[100];
    char outputFile60Name[100];
    char outputFile61Name[100];
    char outputFile62Name[100];

    // Copiar o caminho da pasta de resultados para os nomes dos arquivos temporários
    strcpy(outputFile58Name, outputPath_1);
    strcpy(outputFile59Name, outputPath_1);
    strcpy(outputFile60Name, outputPath_1);
    strcpy(outputFile61Name, outputPath_1);
    strcpy(outputFile62Name, outputPath_1);

    // Concatenar nomes de arquivos temporários com os nomes de arquivo específicos
    strcat(outputFile58Name, "command58_output.txt");
    strcat(outputFile59Name, "command59_output.txt");
    strcat(outputFile60Name, "command60_output.txt");
    strcat(outputFile61Name, "command61_output.txt");
    strcat(outputFile62Name, "command62_output.txt");

    // Criar e escrever nos arquivos de saída na pasta "Resultados"
    FILE *outputFile58 = fopen(outputFile58Name, "w");
    FILE *outputFile59 = fopen(outputFile59Name, "w");
    FILE *outputFile60 = fopen(outputFile60Name, "w");
    FILE *outputFile61 = fopen(outputFile61Name, "w");
    FILE *outputFile62 = fopen(outputFile62Name, "w");

// Iterar sobre os IDs e buscar os voos correspondentes
for (int i = 0; i < 5; ++i) {
    const char *idToFind_1 = Ids_1[i];

    int flightIndex = findFlightIndexById(flights, numFlights, idToFind_1);

    // Verificar se o voo foi encontrado
    if (flightIndex != -1 && flightIndex < numFlights) {
        int numPassengersInFlight_1 = calculateNumPassengersInFlight(passengers, numPassengers, idToFind_1);
        int delay_1 = calculateDepartureDelay(&flights[flightIndex]);

        // Adicionando mensagens de depuração
        printf("ID do Voo: %s\n", idToFind_1);
        printf("Índice do Voo: %d\n", flightIndex);
        printf("Número de Passageiros: %d\n", numPassengersInFlight_1);

        printf("Tempo de Atraso: %d minutos\n", delay_1);

        // Verificar se todos os arquivos de saída foram abertos com sucesso
        if (outputFile58 != NULL && outputFile59 != NULL && outputFile60 != NULL && outputFile61 != NULL && outputFile62 != NULL) {
            // Gravar os detalhes no arquivo de saída correspondente
            if (i == 0) {
               fprintf(outputFile58, "--- 1 ---\n"
                      "airline: %s\n"
                      "plane_model: %s\n"
                      "origin: %s\n"
                      "destination: %s\n"
                      "schedule_departure_date: %s\n"
                      "schedule_arrival_date: %s\n"
                      "passengers: %d\n"
                      "delay: %d\n",
                      flights[flightIndex].airline,
                      flights[flightIndex].plane_model,
                      flights[flightIndex].origin,
                      flights[flightIndex].destination,
                      flights[flightIndex].schedule_departure_date,
                      flights[flightIndex].schedule_arrival_date,
                      numPassengersInFlight_1,
                      delay_1 * 60);

            } else if (i == 1) {
             fprintf(outputFile59, "--- 1 ---\n"
                      "airline: %s\n"
                      "plane_model: %s\n"
                      "origin: %s\n"
                      "destination: %s\n"
                      "schedule_departure_date: %s\n"
                      "schedule_arrival_date: %s\n"
                      "passengers: %d\n"
                      "delay: %d\n",
                      flights[flightIndex].airline,
                      flights[flightIndex].plane_model,
                      flights[flightIndex].origin,
                      flights[flightIndex].destination,
                      flights[flightIndex].schedule_departure_date,
                      flights[flightIndex].schedule_arrival_date,
                      numPassengersInFlight_1,
                      delay_1 * 60);       
                     } else if (i == 2) {
                  fprintf(outputFile60, "--- 1 ---\n"
                      "airline: %s\n"
                      "plane_model: %s\n"
                      "origin: %s\n"
                      "destination: %s\n"
                      "schedule_departure_date: %s\n"
                      "schedule_arrival_date: %s\n"
                      "passengers: %d\n"
                      "delay: %d\n",
                      flights[flightIndex].airline,
                      flights[flightIndex].plane_model,
                      flights[flightIndex].origin,
                      flights[flightIndex].destination,
                      flights[flightIndex].schedule_departure_date,
                      flights[flightIndex].schedule_arrival_date,
                      numPassengersInFlight_1,
                      delay_1 * 60);
            } else if (i == 3) {
                  fprintf(outputFile61, "--- 1 ---\n"
                      "airline: %s\n"
                      "plane_model: %s\n"
                      "origin: %s\n"
                      "destination: %s\n"
                      "schedule_departure_date: %s\n"
                      "schedule_arrival_date: %s\n"
                      "passengers: %d\n"
                      "delay: %d\n",
                      flights[flightIndex].airline,
                      flights[flightIndex].plane_model,
                      flights[flightIndex].origin,
                      flights[flightIndex].destination,
                      flights[flightIndex].schedule_departure_date,
                      flights[flightIndex].schedule_arrival_date,
                      numPassengersInFlight_1,
                      delay_1 * 60);
            } else if (i == 4) {
                  fprintf(outputFile62, "--- 1 ---\n"
                      "airline: %s\n"
                      "plane_model: %s\n"
                      "origin: %s\n"
                      "destination: %s\n"
                      "schedule_departure_date: %s\n"
                      "schedule_arrival_date: %s\n"
                      "passengers: %d\n"
                      "delay: %d\n",
                      flights[flightIndex].airline,
                      flights[flightIndex].plane_model,
                      flights[flightIndex].origin,
                      flights[flightIndex].destination,
                      flights[flightIndex].schedule_departure_date,
                      flights[flightIndex].schedule_arrival_date,
                      numPassengersInFlight_1,
                      delay_1 * 60);
            }
        } else {
            // Tratar o caso em que a abertura de arquivo falhou
            printf("Erro ao abrir arquivos de saída.\n");
            return 1;
        }
    } else {
        // Voo não encontrado
        printf("Voo não encontrado para o ID: %s\n", idToFind_1);
        // Pode querer adicionar uma mensagem semelhante no arquivo de saída correspondente
    }
}

    // Fechar os arquivos de saída
    fclose(outputFile58);
    fclose(outputFile59);
    fclose(outputFile60);
    fclose(outputFile61);
    fclose(outputFile62);
    






    // Liberar a memória alocada
    free(users);
    free(flights);
    free(reservations);
    free(passengers);

    return 0;
}
