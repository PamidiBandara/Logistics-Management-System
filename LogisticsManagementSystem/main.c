#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310

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

int deliveryCount = 0;

Vehicle vehicles[3] ={
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
            };

typedef struct{
    int id;
    char fromCity[MAX_NAME_LENGTH];
    char toCity[MAX_NAME_LENGTH];
    int distance;
    char vehicleType[10];
    int weight;
    double baseCost;
    double fuelCost;
    double totalCost;
    double profit;
    double customerCharge;
    double deliveryTime;
    int completed;

}
    Delivery;


void displayMainMenu();
void initializeSystem();
void manageCities();
void manageDistances();

void addCity();
void renameCity();
void removeCity();
void viewAllCities();
void manageVehicles();

void addEditDistance();
void viewDistanceTable();

void initializeSampleData();
void findAndCompleteDistances();
void viewVehicleDetails();
void selectVehicle();
void compareVehicles();

void handleDeliveryMenu();
void handleDeliveryRequestEnhanced();
void viewPendingDeliveries();
void calculateDeliveryCost();
void displayDeliverySummary(Delivery *delivery, Vehicle *vehicle, double fuelUsed);
void viewCompletedDeliveries();

void viewAllDeliveryRecords();
int isDeliveryStorageFull();
void handleDeliveryStorage();


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
                handleDeliveryMenu();
                break;
            case 5:
                printf("Reports - To be implemented\n");
                break;
            case 6:
                printf("Thank you for using Logistics Management System\n");
                break;
            default:
                printf("Invalid choice! Please try again\n");
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
        scanf("%d", &choice);



        switch(choice){
            case 1:
                viewVehicleDetails();
                break;
            case 2:
                selectVehicle();
                break;
            case 3:
                compareVehicles();
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

void compareVehicles(){
    printf("\n== Vehicle Comparison ==\n");

    int sampleDistance, weight;
    printf("Enter sample distance (km): ");
    scanf("%d", &sampleDistance);
    printf("Enter sample weight (kg): ");
    scanf("%d", &weight);

    if(sampleDistance<=0 || weight<=0){
        printf("Invalid input! Distance and weight must be positive\n");
        return;
    }

    printf("\nComparison for %d km with %d kg:\n", sampleDistance, weight);
    printf("+----------+------------+-----------+-------------+--------------+\n");
    printf("| Vehicle  | Time (hrs) | Fuel (L)  | Cost (LKR)  | Suitable     |\n");
    printf("+----------+------------+-----------+-------------+--------------+\n");

    for(int i=0; i<3; i++){
        double time = (double)sampleDistance / vehicles[i].speed;
        double fuel = (double)sampleDistance / vehicles[i].fuel_efficiency;
        double cost = sampleDistance * vehicles[i].rate_per_km * (1 + (double)weight / 10000);
        char suitable[10];

        if(weight<=vehicles[i].capacity){
            strcpy(suitable, "Yes");
        }       else{
            strcpy(suitable, "No");
        }

        printf("| %-8s | %-10.2f | %-9.2f | %-11.2f | %-12s |\n",
               vehicles[i].name, time, fuel, cost, suitable);
    }
    printf("+----------+------------+-----------+-------------+--------------+\n");
}

void handleDeliveryMenu(){
    int choice;
    do      {
        printf("\n== Delivery Management ==\n");
        printf("1.New Delivery Request\n");
        printf("2.View Pending Deliveries\n");
        printf("3.Calculate Delivery Cost\n");
        printf("4.View Completed Deliveries\n");
        printf("5.View All Delivery Records\n");
        printf("6.Check Storage Status\n");
        printf("7.Back to Main Menu\n");


        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
               handleDeliveryRequestEnhanced();
                break;
            case 2:
                viewPendingDeliveries();
                                break;
            case 3:
                calculateDeliveryCost();
                break;
            case 4:
               viewCompletedDeliveries();
                break;
            case 5:
               viewAllDeliveryRecords();
                break;
            case 6:
               printf("Delivery Storage: %d/%d used (%.1f%% full)\n", deliveryCount, MAX_DELIVERIES, (double)deliveryCount/MAX_DELIVERIES*100);
                break;
            case 7:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice!=7);
}



Delivery deliveries[MAX_DELIVERIES];



void handleDeliveryRequestEnhanced(){
    if(isDeliveryStorageFull()){
        manageDeliveryStorage();
    }

    if(cityCount<2){
        printf("Need at least 2 cities for delivery!\n");
        return;
    }

    printf("\n== New Delivery Request ==\n");
    viewAllCities();

    int fromCity, toCity, weight, vehicleChoice;


    printf("Enter source city number: ");
    scanf("%d", &fromCity);
    if(fromCity < 1 || fromCity>cityCount) {
        printf("Invalid source city!\n");
        return;
    }


    printf("Enter destination city number: ");
    scanf("%d", &toCity);
    if(toCity<1 || toCity>cityCount){
        printf("Invalid destination city\n");
        return;
    }

    if(fromCity==toCity){
        printf("Source and destination cannot be the same\n");
        return;
    }


    int dist=distance[fromCity-1][toCity-1];
    if(dist ==-1){
        printf("No route exists between %s and %s!\n", cities[fromCity-1], cities[toCity-1]);
        return;
    }


    printf("Enter package weight (kg): ");
    scanf("%d", &weight);
    if(weight<=0){
        printf("Weight must be positive\n");
        return;
    }


    viewVehicleDetails();
    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vehicleChoice);

    if(vehicleChoice<1 || vehicleChoice>3){
        printf("Invalid vehicle selection!\n");
        return;
    }


    if(weight > vehicles[vehicleChoice-1].capacity){
        printf("Weight exceeds %s capacity (%d kg)! Please select another vehicle.\n",
               vehicles[vehicleChoice-1].name, vehicles[vehicleChoice-1].capacity);
        return;
    }

    deliveries[deliveryCount].id = deliveryCount + 1;
    strcpy(deliveries[deliveryCount].fromCity, cities[fromCity-1]);
    strcpy(deliveries[deliveryCount].toCity, cities[toCity-1]);
    deliveries[deliveryCount].distance = dist;
    strcpy(deliveries[deliveryCount].vehicleType, vehicles[vehicleChoice-1].name);
    deliveries[deliveryCount].weight = weight;
    deliveries[deliveryCount].completed = 0;

    printf("Delivery request stored (ID: %d)\n", deliveries[deliveryCount].id);
    printf("Storage: %d/%d deliveries used\n", deliveryCount + 1, MAX_DELIVERIES);
    deliveryCount++;
}



void viewPendingDeliveries(){
    if(deliveryCount==0){
        printf("No delivery requests pending\n");
        return;
    }

    printf("\n== Pending Delivery Requests ==\n");
    printf("+----+------------------+------------------+----------+----------+----------+\n");
    printf("| ID | From             | To               | Distance | Weight   | Vehicle  |\n");
    printf("+----+------------------+------------------+----------+----------+----------+\n");

    for(int i=0; i<deliveryCount; i++){
        if(!deliveries[i].completed){
            printf("| %-2d | %-16s | %-16s | %-8d | %-8d | %-8s |\n",
                   deliveries[i].id,
                   deliveries[i].fromCity,
                   deliveries[i].toCity,
                   deliveries[i].distance,
                   deliveries[i].weight,
                   deliveries[i].vehicleType);
                   }
                    }
    printf("+----+------------------+------------------+----------+----------+----------+\n");
}

void calculateDeliveryCost(){
    if(deliveryCount==0){
        printf("No delivery requests to calculate\n");
        return;
            }

    viewPendingDeliveries();

    int deliveryId;
    printf("Enter delivery ID to calculate cost: ");
    scanf("%d", &deliveryId);

    if(deliveryId<1 || deliveryId>deliveryCount){
        printf("Invalid delivery ID\n");
        return;
    }

    Delivery *delivery = &deliveries[deliveryId-1];

    if(delivery->completed){
        printf("Delivery already calculated\n");
        return;
    }


    Vehicle *vehicle = NULL;
    for(int i = 0; i < 3; i++){
        if(strcmp(vehicles[i].name, delivery->vehicleType)==0){
            vehicle = &vehicles[i];
            break;
        }
    }

    if(vehicle == NULL){
        printf("Vehicle type not found!\n");
        return;
    }

    double D = delivery->distance;
    double W = delivery->weight;
    double R = vehicle->rate_per_km;
    double S = vehicle->speed;
    double E = vehicle->fuel_efficiency;
    double F = FUEL_PRICE;


    delivery->baseCost = D * R * (1 + W / 10000);

    delivery->deliveryTime = D / S;

    double fuelUsed = D / E;

    delivery->fuelCost = fuelUsed * F;

    delivery->totalCost = delivery->baseCost + delivery->fuelCost;

    delivery->profit = delivery->baseCost * 0.25;

    delivery->customerCharge = delivery->totalCost + delivery->profit;

    delivery->completed = 1;

    displayDeliverySummary(delivery, vehicle, fuelUsed);
}

void displayDeliverySummary(Delivery *delivery, Vehicle *vehicle, double fuelUsed){

    printf("DELIVERY COST ESTIMATION\n");

    printf("From: %s\n", delivery->fromCity);
    printf("To: %s\n", delivery->toCity);
    printf("Minimum Distance: %d km\n", delivery->distance);
    printf("Vehicle: %s\n", delivery->vehicleType);
    printf("Weight: %d kg\n", delivery->weight);


    printf("Base Cost: %.0f × %.0f × (1 + %.0f/10000) = %8.2f LKR\n",
           (double)delivery->distance, (double)vehicle->rate_per_km,
           (double)delivery->weight, delivery->baseCost);

    printf("Fuel Used: %.2f L\n", fuelUsed);
    printf("Fuel Cost: %.2f LKR\n", delivery->fuelCost);
    printf("Operational Cost: %.2f LKR\n", delivery->totalCost);
    printf("Profit: %.2f LKR\n", delivery->profit);
    printf("Customer Charge: %.2f LKR\n", delivery->customerCharge);
    printf("Estimated Time: %.2f hours\n", delivery->deliveryTime);

}

void viewCompletedDeliveries(){
    int completedCount=0;

    printf("\n== Completed Deliveries ==\n");
    printf("+----+------------------+------------------+----------+------------+----------------+\n");
    printf("| ID | From             | To               | Distance | Total Cost | Customer Charge|\n");
    printf("+----+------------------+------------------+----------+------------+----------------+\n");

    for(int i=0; i<deliveryCount; i++){
        if(deliveries[i].completed){
            printf("| %-2d | %-16s | %-16s | %-8d | %10.2f | %14.2f |\n",
                   deliveries[i].id,
                   deliveries[i].fromCity,
                   deliveries[i].toCity,
                   deliveries[i].distance,
                   deliveries[i].totalCost,
                   deliveries[i].customerCharge);
            completedCount++;
        }
    }
    printf("+----+------------------+------------------+----------+------------+----------------+\n");

    if(completedCount==0){
        printf("No completed deliveries found\n");
    }
}



void viewAllDeliveryRecords(){
    if(deliveryCount==0){
        printf("No delivery records available\n");
        return;
    }

    printf("\n== All Delivery Records (%d/%d) ==\n", deliveryCount, MAX_DELIVERIES);
    printf("+----+----------+------------------+------------------+----------+----------+------------+----------------+\n");
    printf("| ID | Status   | From             | To               | Distance | Weight   | Total Cost | Customer Charge|\n");
    printf("+----+----------+------------------+------------------+----------+----------+------------+----------------+\n");

    for(int i=0; i<deliveryCount; i++){
        char status[10];
        if(deliveries[i].completed){
            strcpy(status, "Completed");
        } else  {
            strcpy(status, "Pending");
        }

        printf("| %-2d | %-8s | %-16s | %-16s | %-8d | %-8d | %10.2f | %14.2f |\n",
               deliveries[i].id,
               status,
               deliveries[i].fromCity,
               deliveries[i].toCity,
               deliveries[i].distance,
               deliveries[i].weight,
               deliveries[i].totalCost,
               deliveries[i].customerCharge);
    }
    printf("+----+----------+------------------+------------------+----------+----------+------------+----------------+\n");

    printf("Storage: %d/%d deliveries used (%.1f%% full)\n",
           deliveryCount, MAX_DELIVERIES, (double)deliveryCount/MAX_DELIVERIES*100);
}

int isDeliveryStorageFull() {
    return deliveryCount >= MAX_DELIVERIES;
}


void manageDeliveryStorage() {
    if(!isDeliveryStorageFull()) {
        return;
    }

    printf("\nDelivery storage full (%d/%d)! Managing storage\n", deliveryCount, MAX_DELIVERIES);


    int oldestPendingIndex = -1;
    for(int i = 0; i < deliveryCount; i++){
        if(!deliveries[i].completed){
            oldestPendingIndex = i;
            break;
        }
    }

    if(oldestPendingIndex!=-1){
        printf("Removing oldest pending delivery (ID: %d) to free space.\n", deliveries[oldestPendingIndex].id);


        for(int i = oldestPendingIndex; i < deliveryCount - 1; i++) {
            deliveries[i] = deliveries[i + 1];
            deliveries[i].id = i + 1;
        }
        deliveryCount--;
    } else{

        printf("Removing oldest completed delivery (ID: %d) to free space.\n", deliveries[0].id);
        for(int i = 0; i < deliveryCount - 1; i++){
            deliveries[i] = deliveries[i + 1];
            deliveries[i].id = i + 1;
        }
        deliveryCount--;
    }
}
