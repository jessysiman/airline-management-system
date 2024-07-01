/* Jessalyne Desiree R S (2206822521)
Satria Wibawa Hadiwijaya (2206043536)
Final Project: Airline Management System Program
Verion 2.0  */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Dynamic Data Structure: Linked List
typedef struct Flight {
    char airlineName[100];
    char flightNumber[10];
    char origin[50];
    char destination[50];
    char departureTime[10];
    struct Flight* next;
} Flight;

Flight* flightList = NULL; // Head of the linked list

// Parameter Passing
void addFlight(char airlineName[], char flightNumber[], char origin[], char destination[], char departureTime[]) {
    Flight* newFlight = (Flight*)malloc(sizeof(Flight));
    strcpy(newFlight->airlineName, airlineName);
    strcpy(newFlight->flightNumber, flightNumber);
    strcpy(newFlight->origin, origin);
    strcpy(newFlight->destination, destination);
    strcpy(newFlight->departureTime, departureTime);
    newFlight->next = flightList;
    flightList = newFlight;
}

void displayFlights() {
    Flight* current = flightList;
    if (current == NULL) {
        // Open flights.txt and read flights from the file
        FILE* file = fopen("flights.txt", "r");
        if (file == NULL) {
            printf("No flights available in memory and no flights file found.\n");
            return;
        }

        printf("Flights from file:\n");
        printf("%-20s %-10s %-20s %-20s %-10s\n", "Airline Name", "Flight No", "Origin", "Destination", "Dep. Time");
        printf("----------------------------------------------------------------------\n");

        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char airlineName[100], flightNumber[10], origin[50], destination[50], departureTime[10];
            sscanf(line, "%[^,],%[^,],%[^,],%[^,],%s", airlineName, flightNumber, origin, destination, departureTime);
            printf("%-20s %-10s %-20s %-20s %-10s\n", airlineName, flightNumber, origin, destination, departureTime);
        }

        fclose(file);
        printf("----------------------------------------------------------------------\n");
        return;
    }

    printf("Flights from memory:\n");
    printf("%-20s %-10s %-20s %-20s %-10s\n", "Airline Name", "Flight No", "Origin", "Destination", "Dep. Time");
    printf("----------------------------------------------------------------------\n");
    while (current != NULL) {
        printf("%-20s %-10s %-20s %-20s %-10s\n", current->airlineName, current->flightNumber, current->origin, current->destination, current->departureTime);
        current = current->next;
    }
    printf("----------------------------------------------------------------------\n");
}

// Reservation Management Module

// Dynamic Data Structure: Linked List
typedef struct Reservation {
    char passengerName[50];
    char airlineName[100];
    char flightNumber[10];
    char seatClass[20];
    int price;
    struct Reservation* next;
} Reservation;

Reservation* reservationList = NULL; // Head of the linked list

// Parameter Passing
void makeReservation() {
    char passengerName[50], airlineName[100], flightNumber[10];
    int choice;
    char seatClass[20];
    int price;

    printf("Enter Passenger Name: ");
    scanf("%s", passengerName);
    printf("Enter Airline Name: ");
    scanf(" %[^\n]", airlineName); // Read airline name with spaces
    printf("Enter Flight Number: ");
    scanf("%s", flightNumber);

    printf("Select Seat Class:\n");
    printf("1. First Class (Rp10,000,000)\n");
    printf("2. Business Class (Rp5,000,000)\n");
    printf("3. Economy Class (Rp1,000,000)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(seatClass, "First Class");
            price = 10000000;
            break;
        case 2:
            strcpy(seatClass, "Business Class");
            price = 5000000;
            break;
        case 3:
            strcpy(seatClass, "Economy Class");
            price = 1000000;
            break;
        default:
            printf("Invalid choice\n");
            return;
    }

    int payment, change;
    printf("Price: Rp%d\n", price);
    printf("Enter payment amount: Rp");
    scanf("%d", &payment);

    if (payment >= price) {
        change = payment - price;
        printf("Change: Rp%d\n", change);

        Reservation* newReservation = (Reservation*)malloc(sizeof(Reservation));
        strcpy(newReservation->passengerName, passengerName);
        strcpy(newReservation->airlineName, airlineName);
        strcpy(newReservation->flightNumber, flightNumber);
        strcpy(newReservation->seatClass, seatClass);
        newReservation->price = price;
        newReservation->next = reservationList;
        reservationList = newReservation;

        printf("Reservation made successfully\n");
    } else {
        printf("Insufficient payment\n");
    }
}

void displayReservations() {
    Reservation* current = reservationList;
    if (current == NULL) {
        printf("No reservations found in memory.\n");
        
        // Open reservations.txt and read reservations from the file
        FILE* file = fopen("reservations.txt", "r");
        if (file == NULL) {
            printf("No reservations file found.\n");
            return;
        }
        
        printf("Reservations from file:\n");
        printf("%-20s %-20s %-10s\n", "Passenger Name", "Airline Name", "Flight No");
        printf("----------------------------------------------\n");
        
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char passengerName[50], airlineName[100], flightNumber[10];
            sscanf(line, "%[^,],%[^,],%s", passengerName, airlineName, flightNumber);
            printf("%-20s %-20s %-10s\n", passengerName, airlineName, flightNumber);
        }
        
        fclose(file);
        printf("----------------------------------------------\n");
        return;
    }
    
    printf("Reservations from memory:\n");
    printf("%-20s %-20s %-10s\n", "Passenger Name", "Airline Name", "Flight No");
    printf("----------------------------------------------\n");
    while (current != NULL) {
        printf("%-20s %-20s %-10s\n", current->passengerName, current->airlineName, current->flightNumber);
        current = current->next;
    }
    printf("----------------------------------------------\n");
}

// File Handling
void saveReservations() {
    FILE* file = fopen("reservations.txt", "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    Reservation* current = reservationList;
    while (current != NULL) {
        fprintf(file, "%s,%s,%s\n", current->passengerName, current->airlineName, current->flightNumber);
        current = current->next;
    }

    fclose(file);
    printf("Reservations saved to reservations.txt\n");
}

void searchFlight(char airlineName[], char flightNumber[]) {
    Flight* current = flightList;
    int found = 0;

    while (current != NULL) {
        if (strstr(current->airlineName, airlineName) != NULL && strstr(current->flightNumber, flightNumber) != NULL) {
            printf("Flight Details:\n");
            printf("%-20s %-10s %-20s %-20s %-10s\n", "Airline Name", "Flight No", "Origin", "Destination", "Dep. Time");
            printf("----------------------------------------------------------------------\n");
            printf("%-20s %-10s %-20s %-20s %-10s\n", current->airlineName, current->flightNumber, current->origin, current->destination, current->departureTime);
            printf("----------------------------------------------------------------------\n");
            found = 1;
            break;
        }
        current = current->next;
    }

    if (!found) {
        printf("Flight not found\n");
    }
}

void sortByAirlineName() {
    Flight* current = flightList;
    Flight* index = NULL;
    Flight* temp = NULL;

    if (current == NULL) {
        printf("No flights available to sort.\n");
        return;
    }

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->airlineName, index->airlineName) > 0) {
                temp = (Flight*)malloc(sizeof(Flight));
                strcpy(temp->airlineName, current->airlineName);
                strcpy(current->airlineName, index->airlineName);
                strcpy(index->airlineName, temp->airlineName);
                free(temp);
            }
            index = index->next;
        }
        current = current->next;
    }

    printf("Flights sorted by Airline Name:\n");
    displayFlights();
}

void sortByOrigin() {
    Flight* current = flightList;
    Flight* index = NULL;
    Flight* temp = NULL;

    if (current == NULL) {
        printf("No flights available to sort.\n");
        return;
    }

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->origin, index->origin) > 0) {
                temp = (Flight*)malloc(sizeof(Flight));
                strcpy(temp->origin, current->origin);
                strcpy(current->origin, index->origin);
                strcpy(index->origin, temp->origin);
                free(temp);
            }
            index = index->next;
        }
        current = current->next;
    }

    printf("Flights sorted by Origin:\n");
    displayFlights();
}

void sortByDepartureTime() {
    Flight* current = flightList;
    Flight* index = NULL;
    Flight* temp = NULL;

    if (current == NULL) {
        printf("No flights available to sort.\n");
        return;
    }

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (strcmp(current->departureTime, index->departureTime) > 0) {
                temp = (Flight*)malloc(sizeof(Flight));
                strcpy(temp->departureTime, current->departureTime);
                strcpy(current->departureTime, index->departureTime);
                strcpy(index->departureTime, temp->departureTime);
                free(temp);
            }
            index = index->next;
        }
        current = current->next;
    }

    printf("Flights sorted by Departure Time:\n");
    displayFlights();
}

void sortFlights() {
    int choice;
    printf("Sort Flights By:\n");
    printf("1. Airline Name (Alphabetical)\n");
    printf("2. Origin (Alphabetical)\n");
    printf("3. Departure Time\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sortByAirlineName();
            break;
        case 2:
            sortByOrigin();
            break;
        case 3:
            sortByDepartureTime();
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}

// User Interface
void airlineMenu() {
    int choice;
    char airlineName[100], flightNumber[10], origin[50], destination[50], departureTime[10];

    while (1) {
        printf("\nAirline Menu\n");
        printf("1. Add Flight\n");
        printf("2. Display Flights\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Airline Name: ");
                scanf(" %[^\n]", airlineName); // Read airline name with spaces
                printf("Enter Flight Number: ");
                scanf("%s", flightNumber);
                printf("Enter Origin: ");
                scanf("%s", origin);
                printf("Enter Destination: ");
                scanf("%s", destination);
                printf("Enter Estimated Departure Time (HH:MM): ");
                scanf("%s", departureTime);
                addFlight(airlineName, flightNumber, origin, destination, departureTime);
                printf("Flight added successfully\n");
                break;

            case 2:
                displayFlights();
                break;

            case 3:
                return;

            default:
                printf("Invalid choice\n");
                break;
        }
    }
}

void passengerMenu() {
    int choice;
    char passengerName[50], airlineName[100], flightNumber[10];
    int searchchoice;

    while (1) {
        printf("\nPassenger Menu\n");
        printf("1. Make Reservation\n");
        printf("2. Display All Flights\n");
        printf("3. Search Flight\n");
        printf("4. Display All Reservations\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                makeReservation();
                break;

            case 2:
                displayFlights();
                break;

            case 3:
                printf("Would you like to: \n");
                printf("1. Continue Searching Flights\n");
        		printf("2. Sort Flights\n");
        		printf("Enter your choice: ");
        		scanf("%d", &searchchoice);
        		switch(searchchoice){
        			case 1:
        				printf("Enter Airline Name: ");
		                scanf(" %[^\n]", airlineName);
		                printf("Enter Flight Number: ");
		                scanf("%s", flightNumber);
		                searchFlight(airlineName, flightNumber);
		                break;
		            case 2: 
		            	sortFlights();
				}
                break;

            case 4:
                displayReservations();
                break;

            case 5:
                return;

            default:
                printf("Invalid choice\n");
                break;
        }
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nAirline Reservation System\n");
        printf("1. Airline\n");
        printf("2. Passenger\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                airlineMenu();
                break;

            case 2:
                passengerMenu();
                break;

            case 3:
                saveReservations();
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice\n");
                break;
        }
    }

    return 0;
}

