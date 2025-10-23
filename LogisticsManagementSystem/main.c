#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50

typedef struct{
    char name[10];
    int capacity;
    int rate_per_km;
    int speed;
    int fuel_efficiency;
}    Vehicle;

char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;

Vehicle vehicles[3] ={
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
            };


void displayMainMenu();
void initializeSystem();
void manageCities();
void manageDistances();

int main(){
    initializeSystem();
    int choice;

    do{
        displayMainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                manageCities();
                break;
            case 2:
                manageDistances();
                break;
            case 3:
                printf("Vehicle Management - To be implemented\n");
                break;
            case 4:
                printf("Delivery Request - To be implemented\n");
                break;
            case 5:
                printf("Reports - To be implemented\n");
                break;
            case 6:
                printf("Thank you for using Logistics Management System!\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice!= 6);

    return 0;
}

void displayMainMenu(){
    printf("\n== Logistics Management System ==\n");
    printf("1.City Management\n");
    printf("2.Distance Management\n");
    printf("3.Vehicle Management\n");
    printf("4.Delivery Request\n");
    printf("5.Reports\n");
    printf("6.Exit\n");
}

void initializeSystem(){

    for(int i=0; i<MAX_CITIES; i++){
        for(int j=0; j<MAX_CITIES; j++){
            if(i == j)
            distance[i][j] = 0;
            else
            distance[i][j] = -1;
        }
}
    printf("System initialized successfully\n");
}

void manageCities(){
    printf("City Management - To be implemented\n");
}

void manageDistances(){
    printf("Distance Management - To be implemented\n");
}
