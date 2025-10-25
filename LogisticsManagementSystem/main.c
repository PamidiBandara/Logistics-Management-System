#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50
#define MAX_NAME_LENGTH 50
#define FUEL_PRICE 310

typedef struct {
    int path[MAX_CITIES];
    int pathLength;
    int totalDistance;
} Route;

typedef struct{
    char name[10];
    int capacity;
    int rate_per_km;
    int speed;
    int fuel_efficiency;
}    Vehicle;



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


char cities[MAX_CITIES][MAX_NAME_LENGTH];
int distance[MAX_CITIES][MAX_CITIES];
int cityCount=0;
Delivery deliveries[MAX_DELIVERIES];
int deliveryCount = 0;

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


void findOptimalRoute();
 Route findLeastCostRoute(int start, int end);
 Route bruteForceRoute(int start, int end);
 Route dijkstraRoute(int start, int end);
int nextPermutation(int *array, int length);
void displayOptimalRoute(Route route, int start, int end);

void generatePerformanceReports();
void vehiclePerformanceReport();
void cityPerformanceReport();
void handleReportsMenu();

void saveRoutesToFile();
void loadRoutesFromFile();
void saveDeliveriesToFile();
void loadDeliveriesFromFile();
void saveAllData();
void loadAllData();
void initializeSystemWithFiles();
void exitSystemWithSave();
void handleFileOperationsMenu();

int main(){
    initializeSystemWithFiles();
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
                findOptimalRoute();
                break;
            case 6:
                handleReportsMenu();
                break;
            case 7:
                handleFileOperationsMenu();
                break;
            case 8:
                exitSystemWithSave();
                break;
            default:
                printf("Invalid choice! Please try again\n");
        }
    } while(choice!= 8);

    return 0;
}

void displayMainMenu(){
    printf("\n== Logistics Management System ==\n");
    printf("1.City Management\n");
    printf("2.Distance Management\n");
    printf("3.Vehicle Management\n");
    printf("4.Delivery Request\n");
    printf("5.Route Optimization\n");
    printf("6.Performance Reports\n");
    printf("7.File Operations\n");
    printf("8.Exit\n");
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
        printf("3.Auto Complete Missing Distances\n");
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
        handleDeliveryStorage();
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


void handleDeliveryStorage() {
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



void findOptimalRoute(){
    if(cityCount<2){
        printf("Need at least 2 cities for route optimization\n");
        return;
    }

    viewAllCities();

    int startCity, endCity;
    printf("Enter start city number: ");
    scanf("%d", &startCity);
    printf("Enter end city number: ");
    scanf("%d", &endCity);

    if(startCity < 1  || startCity > cityCount || endCity < 1 || endCity > cityCount) {
        printf("Invalid city numbers\n");
        return;
    }

    if(startCity == endCity){
        printf("Start and end cities cannot be the same\n");
        return;
    }


    int directDistance = distance[startCity-1][endCity-1];
    if(directDistance != -1){
        printf("\nDirect route available: %s → %s (%d km)\n",
               cities[startCity-1], cities[endCity-1], directDistance);
    } else {
        printf("\nNo direct route between %s and %s\n", cities[startCity-1], cities[endCity-1]);
    }


    Route optimalRoute = findLeastCostRoute(startCity-1, endCity-1);

    if(optimalRoute.totalDistance == -1){
        printf("No route found between %s and %s!\n", cities[startCity-1], cities[endCity-1]);
        return;
    }


    displayOptimalRoute(optimalRoute, startCity-1, endCity-1);
}

Route findLeastCostRoute(int start, int end){
    Route bestRoute;
    bestRoute.totalDistance = -1;

    if(cityCount <= 4) {
        bestRoute = bruteForceRoute(start, end);
    } else {
        bestRoute = dijkstraRoute(start, end);
    }

    return bestRoute;
}

Route bruteForceRoute(int start, int end){
    Route bestRoute;
    bestRoute.totalDistance = -1;


    int intermediate[MAX_CITIES-2];
    int interCount = 0;

    for(int i = 0; i < cityCount; i++) {
        if(i != start && i != end) {
            intermediate[interCount++] = i;
        }
    }


    if(interCount <= 2){
        int permutation[4];
        permutation[0] = start;


        if(interCount == 0){

            if(distance[start][end] != -1){
                bestRoute.path[0] = start;
                bestRoute.path[1] = end;
                bestRoute.pathLength = 2;
                bestRoute.totalDistance = distance[start][end];
            }
        } else {

            do {

                permutation[0] = start;
                for(int i = 0; i < interCount; i++) {
                    permutation[i+1] = intermediate[i];
                }
                permutation[interCount+1] = end;


                int totalDist = 0;
                int valid = 1;

                for(int i = 0; i < interCount+1; i++) {
                    int from = permutation[i];
                    int to = permutation[i+1];

                    if(distance[from][to] == -1) {
                        valid = 0;
                        break;
                    }
                    totalDist += distance[from][to];
                }


                if(valid && (bestRoute.totalDistance == -1 || totalDist < bestRoute.totalDistance)) {
                    bestRoute.totalDistance = totalDist;
                    bestRoute.pathLength = interCount + 2;
                    for(int i = 0; i < bestRoute.pathLength; i++) {
                        bestRoute.
      path[i] = permutation[i];
                    }
                }

            } while(nextPermutation(intermediate, interCount));
        }
    }

    return bestRoute;
}


int nextPermutation(int *array, int length){
    if(length < 2) return 0;

    int i = length - 2;
    while(i >= 0 && array[i] >= array[i+1]) i--;
    if(i < 0) return 0;

    int j = length - 1;
    while(array[j] <= array[i]) j--;


    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;


    int left = i + 1, right = length - 1;
    while(left < right) {
        temp = array[left];
        array[left] = array[right];
        array[right] = temp;
        left++;
        right--;
    }

    return 1;
}

Route dijkstraRoute(int start, int end){
    Route route;
    route.totalDistance = -1;

    int dist[MAX_CITIES];
    int prev[MAX_CITIES];
    int visited[MAX_CITIES] = {0};


    for(int i=0; i<MAX_CITIES; i++){
        dist[i] = -1;
        prev[i] = -1;
    }
    dist[start] = 0;

    for(int count=0; count<cityCount; count++){

        int minDist = -1;
        int current = -1;

        for(int i=0; i<cityCount; i++){
            if(!visited[i] && dist[i] != -1 && (minDist == -1 || dist[i] < minDist)) {
                minDist = dist[i];
                current = i;
            }
        }

        if(current == -1 || current == end) break;
        visited[current] = 1;


        for(int neighbor = 0; neighbor < cityCount; neighbor++){
            if(!visited[neighbor] && distance[current][neighbor] != -1){
                int newDist = dist[current] + distance[current][neighbor];
                if(dist[neighbor] == -1 || newDist < dist[neighbor]){
                    dist[neighbor] = newDist;
                    prev[neighbor] = current;
                }
                    }
                    }
    }


    if(dist[end] != -1){
        route.totalDistance = dist[end];


        int path[MAX_CITIES];
        int current = end;
        route.pathLength = 0;

        while(current != -1){
            path[route.pathLength++] = current;
            current = prev[current];
        }


        for(int i=0; i<route.pathLength; i++){
            route.path[i] = path[route.pathLength - 1 - i];
        }
    }

    return route;
}

void displayOptimalRoute(Route route, int start, int end){
    printf("\n== OPTIMAL ROUTE FOUND ==\n");
    printf("From: %s\n", cities[start]);
    printf("To: %s\n", cities[end]);
    printf("Total Distance: %d km\n", route.totalDistance);
    printf("Route: ");

    for(int i=0; i<route.pathLength; i++){
        printf("%s", cities[route.path[i]]);
        if(i < route.pathLength - 1) {
            printf(" -> ");
        }
    }
    printf("\n");


    printf("Segment Breakdown:\n");
    for(int i=0; i<route.pathLength-1; i++){
        int from=route.path[i];
        int to=route.path[i+1];
        printf("  %s → %s: %d km\n", cities[from], cities[to], distance[from][to]);
    }
    printf("===========================\n");
}


void generatePerformanceReports(){
    if(deliveryCount == 0){
        printf("No delivery data available for reports\n");
        return;
    }

    int completedCount = 0;
    double totalDistance = 0;
    double totalDeliveryTime = 0;
    double totalRevenue = 0;
    double totalProfit = 0;
    int longestRoute = 0;
    int shortestRoute = -1;


    for(int i=0; i<deliveryCount; i++){
        if(deliveries[i].completed){
            completedCount++;
            totalDistance += deliveries[i].distance;
            totalDeliveryTime += deliveries[i].deliveryTime;
            totalRevenue += deliveries[i].customerCharge;
            totalProfit += deliveries[i].profit;


            if(deliveries[i].distance>longestRoute){
                longestRoute = deliveries[i].distance;
            }


            if(shortestRoute == -1 || deliveries[i].distance < shortestRoute){
                shortestRoute = deliveries[i].distance;
            }
        }
    }


    printf("\n==============================================\n");
    printf("          PERFORMANCE REPORTS\n");
    printf("==============================================\n");

    printf("a. Total Deliveries Completed: %d\n", completedCount);
    printf("   Pending Deliveries: %d\n", deliveryCount - completedCount);
    printf("   Completion Rate: %.1f%%\n", (double)completedCount/deliveryCount*100);

    printf("b. Total Distance Covered: %.0f km\n", totalDistance);
    printf("   Average per Delivery: %.1f km\n", completedCount > 0 ? totalDistance/completedCount : 0);


    printf("c. Average Delivery Time: %.2f hours\n", completedCount > 0 ? totalDeliveryTime/completedCount : 0);
    printf("   Total Delivery Time: %.1f hours\n", totalDeliveryTime);


    printf("d. Financial Summary:\n");
    printf("   Total Revenue: %.2f LKR\n", totalRevenue);
    printf("   Total Profit: %.2f LKR\n", totalProfit);
    printf("   Profit Margin: %.1f%%\n", totalRevenue > 0 ? (totalProfit/totalRevenue)*100 : 0);


    printf("e. Route Statistics:\n");
    printf("   Longest Route: %d km\n", longestRoute);
    printf("   Shortest Route: %d km\n", shortestRoute);
    printf("   Route Length Range: %d km\n", longestRoute - shortestRoute);

    printf("==============================================\n");
}

void vehiclePerformanceReport(){
    printf("\n== VEHICLE PERFORMANCE REPORT ==\n");

    int vanDeliveries = 0, truckDeliveries = 0, lorryDeliveries = 0;
    double vanRevenue = 0, truckRevenue = 0, lorryRevenue = 0;
    double vanDistance = 0, truckDistance = 0, lorryDistance = 0;

    for(int i = 0; i < deliveryCount; i++){
        if(deliveries[i].completed) {
            if(strcmp(deliveries[i].vehicleType, "Van") == 0){
                vanDeliveries++;
                vanRevenue += deliveries[i].customerCharge;
                vanDistance += deliveries[i].distance;
            } else if(strcmp(deliveries[i].vehicleType, "Truck") == 0){
                truckDeliveries++;
                truckRevenue += deliveries[i].customerCharge;
                truckDistance += deliveries[i].distance;
            } else if(strcmp(deliveries[i].vehicleType, "Lorry") == 0){
                lorryDeliveries++;
                lorryRevenue += deliveries[i].customerCharge;
                lorryDistance += deliveries[i].distance;
            }
        }
    }

    printf("+----------+------------+-------------+----------------+----------------+\n");
    printf("| Vehicle  | Deliveries | Total Revenue | Total Distance | Avg Revenue/Del |\n");
    printf("+----------+------------+-------------+----------------+----------------+\n");

    printf("| %-8s | %-10d | %11.2f | %14.0f | %14.2f |\n",
           "Van", vanDeliveries, vanRevenue, vanDistance,
           vanDeliveries > 0 ? vanRevenue/vanDeliveries : 0);

    printf("| %-8s | %-10d | %11.2f | %14.0f | %14.2f |\n",
           "Truck", truckDeliveries, truckRevenue, truckDistance,
           truckDeliveries > 0 ? truckRevenue/truckDeliveries : 0);

    printf("| %-8s | %-10d | %11.2f | %14.0f | %14.2f |\n",
           "Lorry", lorryDeliveries, lorryRevenue, lorryDistance,
           lorryDeliveries > 0 ? lorryRevenue/lorryDeliveries : 0);

    printf("+----------+------------+-------------+----------------+----------------+\n");
}

void cityPerformanceReport(){
    printf("\n== CITY PERFORMANCE REPORT ==\n");

    int cityStats[MAX_CITIES] = {0};
    double cityRevenue[MAX_CITIES] = {0};


    for(int i=0; i<deliveryCount; i++){
        if(deliveries[i].completed){
            for(int j = 0; j < cityCount; j++){
                if(strcmp(deliveries[i].fromCity, cities[j]) == 0){
                    cityStats[j]++;
                    cityRevenue[j] += deliveries[i].customerCharge;
                    break;
                }
            }
        }
    }

    printf("Most Active Cities (by deliveries):\n");
    printf("+----------+------------------+------------+-------------+\n");
    printf("| Rank     | City Name        | Deliveries | Total Revenue|\n");
    printf("+----------+------------------+------------+-------------+\n");


    for(int i = 0; i < cityCount - 1; i++) {
        for(int j = i + 1; j < cityCount; j++) {
            if(cityStats[j] > cityStats[i]) {

                int tempCount = cityStats[i];
                cityStats[i] = cityStats[j];
                cityStats[j] = tempCount;

                double tempRevenue = cityRevenue[i];
                cityRevenue[i] = cityRevenue[j];
                cityRevenue[j] = tempRevenue;


                char tempName[MAX_NAME_LENGTH];
                strcpy(tempName, cities[i]);
                strcpy(cities[i], cities[j]);
                strcpy(cities[j], tempName);
            }
        }
    }


    int displayCount = cityCount < 5 ? cityCount : 5;
    for(int i = 0; i < displayCount; i++) {
        if(cityStats[i] > 0) {
            printf("| %-8d | %-16s | %-10d | %11.2f |\n",
                   i + 1, cities[i], cityStats[i], cityRevenue[i]);
        }
    }
    printf("+----------+------------------+------------+-------------+\n");
}

void handleReportsMenu() {
    int choice;
    do {
        printf("\n=== PERFORMANCE REPORTS ===\n");
        printf("1. Overall Performance Summary\n");
        printf("2. Vehicle Performance Report\n");
        printf("3. City Performance Report\n");
        printf("4. All Reports\n");
        printf("5. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                generatePerformanceReports();
                break;
            case 2:
                vehiclePerformanceReport();
                break;
            case 3:
                cityPerformanceReport();
                break;
            case 4:
                generatePerformanceReports();
                vehiclePerformanceReport();
                cityPerformanceReport();
                break;
            case 5:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 5);
}


void saveRoutesToFile(){
    FILE *file = fopen("routes.txt", "w");
    if(file == NULL){
        printf("Error creating routes file!\n");
        return;
    }


    fprintf(file, "Cities:%d\n", cityCount);
    for(int i=0; i < cityCount; i++){
        fprintf(file, "%s\n", cities[i]);
    }


    fprintf(file, "DistanceMatrix\n");
    for(int i=0; i<cityCount; i++){
        for(int j=0; j<cityCount; j++){
            fprintf(file, "%d", distance[i][j]);
            if(j < cityCount - 1) fprintf(file, ",");
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Routes data saved to routes.txt\n");
}

void loadRoutesFromFile(){
    FILE *file = fopen("routes.txt", "r");
    if(file == NULL){
        printf("No existing routes data found.\n");
        return;
    }

    char line[200];

    if(fscanf(file, "Cities:%d\n", &cityCount) != 1) {
        printf("Error reading cities from file.\n");
        fclose(file);
        return;
    }

    for(int i=0; i<cityCount; i++){
        if(fgets(line, sizeof(line), file) == NULL){
            printf("Error reading city data.\n");
            break;
        }
        line[strcspn(line, "\n")] = 0;
        strcpy(cities[i], line);
    }


    if(fgets(line, sizeof(line), file) == NULL){
        printf("Error reading distance matrix header.\n");
        fclose(file);
        return;
    }


    for(int i = 0; i < cityCount; i++){
        for(int j = 0; j < cityCount; j++){
            if(fscanf(file, "%d", &distance[i][j]) != 1){
                printf("Error reading distance matrix.\n");
                fclose(file);
                return;
            }
            if(j < cityCount - 1) fgetc(file);
        }
        fgetc(file);
    }

    fclose(file);
    printf("Loaded %d cities and distance matrix from routes.txt\n", cityCount);
}

void saveDeliveriesToFile() {
    FILE *file = fopen("deliveries.txt", "w");
    if(file == NULL) {
        printf("Error creating deliveries file!\n");
        return;
    }

    fprintf(file, "DeliveryCount:%d\n", deliveryCount);

    for(int i = 0; i < deliveryCount; i++){
        fprintf(file, "%d|%s|%s|%d|%s|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%d\n",
                deliveries[i].id,
                deliveries[i].fromCity,
                deliveries[i].toCity,
                deliveries[i].distance,
                deliveries[i].vehicleType,
                deliveries[i].weight,
                deliveries[i].baseCost,
                deliveries[i].fuelCost,
                deliveries[i].totalCost,
                deliveries[i].profit,
                deliveries[i].customerCharge,
                deliveries[i].deliveryTime,
                deliveries[i].completed);
    }

    fclose(file);
    printf("Delivery records saved to deliveries.txt\n");
}

void loadDeliveriesFromFile(){
    FILE *file = fopen("deliveries.txt", "r");
    if(file == NULL){
        printf("No existing delivery records found.\n");
        return;
    }


    if(fscanf(file, "DeliveryCount:%d\n", &deliveryCount) != 1){
        printf("Error reading delivery count from file.\n");
        fclose(file);
        return;
    }


    for(int i = 0; i < deliveryCount; i++){
        Delivery *d = &deliveries[i];
        char line[500];

        if(fgets(line, sizeof(line), file) == NULL){
            printf("Error reading delivery record %d.\n", i);
            break;
        }

        char *token = strtok(line, "|");
        if(token) d->id = atoi(token);

        token = strtok(NULL, "|");
        if(token) strcpy(d->fromCity, token);

        token = strtok(NULL, "|");
        if(token) strcpy(d->toCity, token);

        token = strtok(NULL, "|");
        if(token) d->distance = atoi(token);

        token = strtok(NULL, "|");
        if(token) strcpy(d->vehicleType, token);

        token = strtok(NULL, "|");
        if(token) d->weight = atoi(token);

        token = strtok(NULL, "|");
        if(token) d->baseCost = atof(token);

        token = strtok(NULL, "|");
        if(token) d->fuelCost = atof(token);

        token = strtok(NULL, "|");
        if(token) d->totalCost = atof(token);

        token = strtok(NULL, "|");
        if(token) d->profit = atof(token);

        token = strtok(NULL, "|");
        if(token) d->customerCharge = atof(token);

        token = strtok(NULL, "|");
        if(token) d->deliveryTime = atof(token);

        token = strtok(NULL, "|");
        if(token) d->completed = atoi(token);
    }

    fclose(file);
    printf("Loaded %d delivery records from deliveries.txt\n", deliveryCount);
}

void saveAllData() {
    saveRoutesToFile();
    saveDeliveriesToFile();
    printf("All data saved successfully!\n");
}

void loadAllData() {
    loadRoutesFromFile();
    loadDeliveriesFromFile();
    printf("All data loaded successfully!\n");
}

void initializeSystemWithFiles(){
    for(int i = 0; i < MAX_CITIES; i++){
        for(int j = 0; j < MAX_CITIES; j++){
            if(i == j)
                distance[i][j] = 0;
            else
                distance[i][j] = -1;
        }
    }

    loadAllData();

    if(cityCount == 0){
        initializeSampleData();
        printf("Sample data initialized for testing.\n");
    }

    printf("System initialized with file handling!\n");
}

void exitSystemWithSave(){
    saveAllData();
    printf("All data saved to files. Thank you for using Logistics Management System!\n");
}

void handleFileOperationsMenu(){
    int choice;
    do {
        printf("\n=== FILE OPERATIONS ===\n");
        printf("1.Save All Data to Files\n");
        printf("2.Load All Data from Files\n");
        printf("3.Save Routes Only\n");
        printf("4.Save Deliveries Only\n");
        printf("5.Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                saveAllData();
                break;
            case 2:
                loadAllData();
                break;
            case 3:
                saveRoutesToFile();
                break;
            case 4:
                saveDeliveriesToFile();
                break;
            case 5:
                printf("Returning to main menu\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while(choice != 5);
}
