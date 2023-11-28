CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS = -lm
INCLUDE_DIR = ./include/
SRC_DIR = ./src/

all: programa-principal

programa-principal: $(SRC_DIR)programa-principal.o $(SRC_DIR)query1.o $(SRC_DIR)query3.o $(SRC_DIR)query4.o $(SRC_DIR)query7.o 
	$(CC) $(CFLAGS) -o programa-principal $(SRC_DIR)programa-principal.o $(SRC_DIR)query1.o $(SRC_DIR)query3.o $(SRC_DIR)query4.o $(SRC_DIR)query7.o $(LDFLAGS)


$(SRC_DIR)programa-principal.o: $(SRC_DIR)programa-principal.c
	$(CC) $(CFLAGS) -c $(SRC_DIR)programa-principal.c -o $(SRC_DIR)programa-principal.o -I$(INCLUDE_DIR)

$(SRC_DIR)query1.o: $(SRC_DIR)query1.c $(INCLUDE_DIR)query1.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)query1.c -o $(SRC_DIR)query1.o -I$(INCLUDE_DIR)

$(SRC_DIR)query3.o: $(SRC_DIR)query3.c $(INCLUDE_DIR)query3.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)query3.c -o $(SRC_DIR)query3.o -I$(INCLUDE_DIR)

$(SRC_DIR)query4.o: $(SRC_DIR)query4.c $(INCLUDE_DIR)query4.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)query4.c -o $(SRC_DIR)query4.o -I$(INCLUDE_DIR)

$(SRC_DIR)query7.o: $(SRC_DIR)query7.c $(INCLUDE_DIR)query7.h
	$(CC) $(CFLAGS) -c $(SRC_DIR)query7.c -o $(SRC_DIR)query7.o -I$(INCLUDE_DIR)

run: programa-principal
	./programa-principal <data-folder> <input>
	
clean:
	rm -f programa-principal $(SRC_DIR)*.o
