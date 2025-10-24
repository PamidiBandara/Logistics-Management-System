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

void addCity();
void renameCity();
void removeCity();
void viewAllCities();

void addEditDistance();
void viewDistanceTable();

void initializeSampleData();
void findAndCompleteDistances();

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
                manageVehicles();
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
    initializeSampleData();
    printf("System initialized successfully\n");
}

void manageCities(){
    int choice;
    do{
        printf("\n==City Management==\n");
        printf("1.Add new city\n");
        printf("2.Rename city\n");
        printf("3.Remove city\n");
        printf("4.View all cities\n");
        printf("5.Back to main menu\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

            switch(choice){
                case 1:
                    addCity();
                    break;
                case 2:
                    renameCity();
                    break;
                case 3:
                    removeCity();
                    break;
                case 4:
                    viewAllCities();
                    break;
                case 5:
                    printf("Returning to main menu\n");
            }
    }
    while(choice!=5);
}
void addCity(){
    if(cityCount>=MAX_CITIES){
        printf("Maximum number of cities reached.");
        return;
    }
    char cityName[MAX_NAME_LENGTH];
    printf("Enter city name: ");
    scanf("%s", cityName);
    int i=0;
     for(i=0; i<cityCount; i++){
        if(strcmp(cities[i], cityName) ==0){
            printf("City already exist");
            return;
        }
     }
     strcpy(cities[cityCount], cityName);
     cityCount++;
     printf("City added successfully\n");
}

void renameCity(){
    if(cityCount == 0){
        printf("No cities available to rename!\n");
        return;
    }

    viewAllCities();
    int index;
    printf("Enter city number to rename: ");
    scanf("%d", &index);

    if(index<1 || index>cityCount){
        printf("Invalid city number!\n");
        return;
    }

    char newName[MAX_NAME_LENGTH];
    printf("Enter new name for %s: ", cities[index-1]);
    scanf(" %[^\n]", newName);


    for(int i = 0; i < cityCount; i++){
        if(i != index-1 && strcmp(cities[i], newName) == 0){
            printf("City '%s' already exists!\n", newName);
            return;
        }
    }

    printf("City '%s' renamed to '%s'\n", cities[index-1], newName);
    strcpy(cities[index-1], newName);
}

void removeCity(){
    if(cityCount == 0){
        printf("No cities available to remove!\n");
        return;
    }
    viewAllCities();
    int index;
    printf("Enter city number to remove: ");
    scanf("%d", &index);

    if(index<1 || index>cityCount){
        printf("Invalid city number!\n");
        return;
    }
    printf("Removing city: %s\n", cities[index-1]);


    for(int i=index-1; i<cityCount-1; i++){
        strcpy(cities[i], cities[i+1]);
    }
    cityCount--;
    printf("City removed successfully!\n");
}

void viewAllCities(){
    if(cityCount == 0){
        printf("No cities available!\n");
        return;
    }

    printf("\n== Available Cities ==\n");
    for(int i=0; i<cityCount; i++){
        printf("%d. %s\n", i+1, cities[i]);
    }
}

void manageDistances(){

    int choice;
    do{
        printf("\n== Distance Management ==\n");
        printf("1.Add/Edit Distance\n");
        printf("2.View Distance Table\n");
        printf("3.Back to Main Menu\n");
        printf("4.Initialize Sample Data\n");
        printf("5.Back To Main Menu");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                addEditDistance();
                break;
            case 2:
                viewDistanceTable();
                break;
            case 3:
                findAndCompleteDistances();
                break;
            case 4:
                initializeSampleData();
                break;
            case 5:
                printf("\nReturning To Main Menu");
                break;
            default:
                printf("Invalid choice\n");
        }
        }       while(choice!=5);
}

void addEditDistance(){
    if(cityCount<2){
        printf("Need at least 2 cities to manage distances\n");
        return;
    }

    viewAllCities();

    int city1, city2, dist;
    printf("Enter first city number: ");
    scanf("%d", &city1);

    printf("Enter second city number: ");
    scanf("%d", &city2);

    if(city1 < 1 || city1 > cityCount || city2 < 1 || city2 > cityCount){
        printf("Invalid city numbers!\n");
        return;
    }

    if(city1==city2){
        printf("Distance from city to itself is always 0\n");
        distance[city1-1][city2-1] = 0;
        return;
    }

    printf("Enter distance between %s and %s (km): ", cities[city1-1], cities[city2-1]);
    scanf("%d", &dist);

    if(dist<0){
        printf("Distance cannot be negative!\n");
        return;
    }
    distance[city1-1][city2-1] = dist;
    distance[city2-1][city1-1] = dist;
    printf("Distance between %s and %s set to %d km\n", cities[city1-1], cities[city2-1], dist);

}

void viewDistanceTable(){
    if(cityCount == 0){
        printf("No cities available\n");
        return;}

    printf("\n== Distance Matrix (km) ==\n");
    printf("%-15s", "");
    int i;
    for(i=0; i<cityCount; i++) {
        printf("%-15s", cities[i]);
    }
    printf("\n");

    for(int i=0; i<cityCount; i++) {
        printf("%-15s", cities[i]);
        for(int j=0; j<cityCount; j++) {
            if(distance[i][j] == -1)
                printf("%-15s", "No Route");
            else
                printf("%-15d", distance[i][j]);
        }
        printf("\n");
    }
}

void initializeSampleData(){

    if(cityCount == 0){
        strcpy(cities[cityCount++], "Colombo");
        strcpy(cities[cityCount++], "Kandy");
        strcpy(cities[cityCount++], "Galle");
        strcpy(cities[cityCount++], "Jaffna");
        printf("Sample cities added for testing\n");
          }
           if(distance[0][1] == -1){
              distance[0][1] = 120; distance[1][0] = 120;
              distance[0][2] = 115; distance[2][0] = 115;
              distance[0][3] = 400; distance[3][0] = 400;
              distance[1][2] = 200; distance[2][1] = 200;
              distance[1][3] = 350; distance[3][1] = 350;
                    printf("Sample distances initialized\n");
                }
            }

void findAndCompleteDistances(){
    if(cityCount<3){
        printf("Need at least 3 cities for distance completion\n");
        return;
}

    int completed=0;

    for(int i=0; i<cityCount; i++){
            for(int j=i+1; j<cityCount; j++){
            if(distance[i][j] == -1){

                for(int k=0; k<cityCount; k++){
                    if(k!=i && k!=j && distance[i][k] != -1 && distance[k][j] != -1){
                        int estimated = distance[i][k] + distance[k][j];
                        distance[i][j] = estimated;
                        distance[j][i] = estimated;
                        printf("Estimated distance %s-%s via %s: %d km\n",
                               cities[i], cities[j], cities[k], estimated);
                        completed++;
                        break;
                        }
                        }
                            }
                                }
    }

    if(completed>0){
        printf("Completed %d missing distances using estimation\n", completed);
    } else{
        printf("No missing distances could be estimated\n");
    }
}


void manageVehicles()
{
    int choice;
    do{
        printf("\n== Vehicle Management==\n");
        printf("1.View Vehicle Details\n");
        printf("2.Select Vehicle For Delivery\n");
        printf("3.Compare Vehicles\n");
        printf("4.Back To Main Menu\n");
        printf("Enter your choice: \n");
        scanf("%d, &choice");



        switch(choice){
            case 1:
                viewVehicleDetails();
                break;
            case 2:
                selectVehicle();
                break;
            case 3:
                printf("Not added yet");
                break;
            case 4:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 4);

}

void viewVehicleDetails(){
    printf("\n== Vehicle Details ==\n");
    printf("+----------+------------+-------------+----------+-----------------+\n");
    printf("| Type     | Capacity   | Rate per km | Speed    | Fuel Efficiency |\n");
    printf("|          | (kg)       | (LKR)       | (km/h)   | (km/l)          |\n");
    printf("+----------+------------+-------------+----------+-----------------+\n");

    for(int i=0; i<3; i++){
        printf("| %-8s | %-10d | %-11d | %-8d | %-15d |\n",
               vehicles[i].name,
               vehicles[i].capacity,
               vehicles[i].rate_per_km,
               vehicles[i].speed,
               vehicles[i].fuel_efficiency);
    }
    printf("+----------+------------+-------------+----------+-----------------+\n");
}

void selectVehicle(){
    printf("\n== Select Vehicle ==\n");
    viewVehicleDetails();

    int choice;
    printf("\nChoose vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &choice);

            if(choice>=1 && choice<=3){
        printf("Selected vehicle: %s\n", vehicles[choice-1].name);
        printf("Capacity: %d kg\n", vehicles[choice-1].capacity);
        printf("Rate: %d LKR/km\n", vehicles[choice-1].rate_per_km);
        printf("Speed: %d km/h\n", vehicles[choice-1].speed);
        printf("Fuel Efficiency: %d km/l\n", vehicles[choice-1].fuel_efficiency);
    }
    else{
        printf("Invalid vehicle selection\n");
    }
}

