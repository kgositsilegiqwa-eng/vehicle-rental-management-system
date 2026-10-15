#ifndef CARMOTORCYCLE_H
#define CARMOTORCYCLE_H
#include "Vehicle.h"


// Car(child class)
class Car : public Vehicle {
private:
    int numberOfDoors;
    int engine;
public:
    void setCarData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice, int carDoors, int carEngine);

    //car get value functions
    int getDoors();
    int getEngine();
    void displayCar();
};

//Motorcycle(Child class)
class Motorcycle : public Vehicle {
private:
    int engineCC;
public:
    void setMotorcycleData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice, int motorcycleEngineCC);

    //motorcyle get valiue function
    int getEngineCC();
    void displayMotorcycle();
};

#endif // CARMOTORCYCLE_H
