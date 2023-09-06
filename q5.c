#include <stdio.h>
#include <string.h>

#define MAX_TRAINS 10
#define MAX_PASSENGERS 100

struct Passenger {
    char name[50];
    int age;
};

struct Train {
    int trainNumber;
    char name[50];
    char source[50];
    char destination[50];
    int seats[50];
};

struct ReservationSystem {
    struct Train trains[MAX_TRAINS];
    struct Passenger passengers[MAX_PASSENGERS];
    int trainCount;
    int passengerCount;
};

void addTrain(struct ReservationSystem* system, int trainNumber, const char* name, const char* source, const char* destination) {
    if (system->trainCount < MAX_TRAINS) {
        struct Train* train = &system->trains[system->trainCount];
        train->trainNumber = trainNumber;
        strcpy(train->name, name);
        strcpy(train->source, source);
        strcpy(train->destination, destination);
        for (int i = 0; i < 50; i++) {
            train->seats[i] = 0; // 0 represents an available seat
        }
        system->trainCount++;
        printf("Train %d added successfully.\n", trainNumber);
    } else {
        printf("Maximum number of trains reached.\n");
    }
}

void addPassenger(struct ReservationSystem* system, const char* name, int age) {
    if (system->passengerCount < MAX_PASSENGERS) {
        struct Passenger* passenger = &system->passengers[system->passengerCount];
        strcpy(passenger->name, name);
        passenger->age = age;
        system->passengerCount++;
        printf("Passenger %s added successfully.\n", name);
    } else {
        printf("Maximum number of passengers reached.\n");
    }
}

void bookTicket(struct ReservationSystem* system, int trainNumber, int seatNumber, int passengerIndex) {
    if (trainNumber < 1 || trainNumber > system->trainCount) {
        printf("Invalid train number.\n");
        return;
    }

    struct Train* train = &system->trains[trainNumber - 1];

    if (seatNumber < 1 || seatNumber > 50) {
        printf("Invalid seat number.\n");
        return;
    }

    if (train->seats[seatNumber - 1] == 1) {
        printf("Seat %d on Train %d is already booked.\n", seatNumber, trainNumber);
        return;
    }

    if (passengerIndex < 0 || passengerIndex >= system->passengerCount) {
        printf("Invalid passenger index.\n");
        return;
    }

    train->seats[seatNumber - 1] = 1; // 1 represents a booked seat
    printf("Ticket booked for %s on Train %s (Seat %d).\n", system->passengers[passengerIndex].name, train->name, seatNumber);
}

int main() {
    struct ReservationSystem system;
    system.trainCount = 0;
    system.passengerCount = 0;

    int choice;
    while (1) {
        printf("\nEnter your choice (1=Add Train, 2=Add Passenger, 3=Book Ticket, 0=Quit): ");
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }

        switch (choice) {
            case 1:
                int trainNumber;
                char name[50];
                char source[50];
                char destination[50];
                printf("Enter train number: ");
                scanf("%d", &trainNumber);
                printf("Enter train name: ");
                scanf("%s", name);
                printf("Enter source: ");
                scanf("%s", source);
                printf("Enter destination: ");
                scanf("%s", destination);
                addTrain(&system, trainNumber, name, source, destination);
                break;

            case 2:
                char passengerName[50];
                int age;
                printf("Enter passenger name: ");
                scanf("%s", passengerName);
                printf("Enter age: ");
                scanf("%d", &age);
                addPassenger(&system, passengerName, age);
                break;

            case 3:
                int trainNum;
                int seatNum;
                int passengerNum;
                printf("Enter train number: ");
                scanf("%d", &trainNum);
                printf("Enter seat number: ");
                scanf("%d", &seatNum);
                printf("Enter passenger number: ");
                scanf("%d", &passengerNum);
                bookTicket(&system, trainNum, seatNum, passengerNum);
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    }

    return 0;
}
