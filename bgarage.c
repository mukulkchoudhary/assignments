#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define MAX 10

typedef struct
{
    char plate[MAX];
    int mvcount;
} Car;

typedef struct
{
    Car cars[MAX];
    int size;
} Garage;

void initializeaGrage();
void processArrival();
void processDeparture();

int findCarFromExit();
void moveBlockingCars();
void removeTargetCar();
void restoreCars();

void initializeGarage(Garage *garage)
{
    garage->size = 0;
    for (int i=0; i<MAX; i++)
    {
        garage->cars[i].plate[0] = '\0';
        garage->cars[i].mvcount = 0;

    }
}

void processArrival(Garage *garage, char *plate)
{
    if (garage->size < MAX)
    {
        strcpy(garage->cars[garage->size].plate, plate);
        garage->cars[garage->size].mvcount = 0;
        garage->size++;
        printf("ARRIVAL:  %s\n",plate);
        printf("POSITION: %d\n\n", garage->size);
    }
    else
    {
        printf("REFUSAL: %s   [No Room!]\n\n", plate);
    }
}

void processDeparture(Garage *garage, char *plate)
{
    Car temp[MAX];
    int tempCount = 0;
    int targetIndex;

    targetIndex = findCarFromExit(garage, plate);
    if(targetIndex == -1)
    {
        printf("REGRET: Car Not Found!\n\n");
        return;
    }

    moveBlockingCars(garage, targetIndex, temp, &tempCount);
    removeTargetCar(garage, targetIndex, plate);
    restoreCars(garage, temp, tempCount);
}

int findCarFromExit(Garage *garage, char *plate)
{
    for (int i= garage->size -1; i >= 0; i--)
    {
        if(strcmp(garage->cars[i].plate, plate) == 0)
        {
            return i;
        }
    }
    return -1;
}

void moveBlockingCars(Garage *garage, int targetIndex, Car temp[], int *tempCount)
{
    Car movedCar;

    while (garage->size > targetIndex + 1)
    {
        garage->size--;
        movedCar = garage->cars[garage->size];
        movedCar.mvcount++;
        temp[*tempCount] = movedCar;
        (*tempCount)++;
    }
}

void removeTargetCar(Garage *garage, int targetIndex, char *plate)
{
    Car departingCar;
    departingCar = garage->cars[targetIndex];
    garage->size--;

    printf("DEPARTURE: %s\nMOVE COUNT: %d\n\n", departingCar.plate, departingCar.mvcount);
}

void restoreCars(Garage *garage, Car temp[], int tempCount)
{
    while(tempCount > 0)
    {
        tempCount--;
        garage->cars[garage->size] = temp[tempCount];
        garage->size++;
    }
}

int main()
{
    Garage garage;
    char command;
    char plate[MAX];
    int lineNumber = 0;

    initializeGarage(&garage);
    
    while (scanf(" %c %9s", &command, plate) == 2)
    {
        lineNumber++;
        if (command == 'A' || command == 'a')
        {
            processArrival(&garage, plate);
        }
        else if (command == 'D' || command == 'd')
        {
            processDeparture(&garage, plate);
        }
        else
        {
            printf("INVALID INPUT!\n\n");
        }
        sleep(1);
    }
}