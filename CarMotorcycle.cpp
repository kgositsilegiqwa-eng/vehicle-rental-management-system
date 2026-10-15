#include "CarMotorcycle.h"

extern QTextStream qout;

void Car::setCarData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice, int carDoors, int carEngine) {
    //vehicle class inherited function call
    setVehicleData(vehicleId, vehicleBrand, vehicleModel, vehiclePrice);
    numberOfDoors = carDoors;
    engine = carEngine;
}

int Car::getDoors() {
    return numberOfDoors;
}

int Car::getEngine() {
    return engine;
}

void Car::displayCar() {
    qout << Qt::endl;
    qout << "Car details: " << Qt::endl;
    displayVehicleInfo();
    qout << "Number of doors: " << numberOfDoors << Qt::endl;
    qout << "Engine Cylinders: " << engine << Qt::endl;
}

void Motorcycle::setMotorcycleData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice, int motorcycleEngineCC) {
    //vehicle class inherited function call
    setVehicleData(vehicleId, vehicleBrand, vehicleModel, vehiclePrice);
    engineCC = motorcycleEngineCC;
}

//get value functions defined
int Motorcycle::getEngineCC() {
    return engineCC;
}

void Motorcycle::displayMotorcycle() {
    qout << Qt::endl;
    qout << "Motorcycle details: " << Qt::endl;
    displayVehicleInfo();
    qout << "Engine CC: " << engineCC << Qt::endl;
}
