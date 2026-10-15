#include "Vehicle.h"

extern QTextStream qout;  // Global output stream

Vehicle::Vehicle() {         //Constructor
    rentStatus = false;
}

//function used to access private vehicle class members
void Vehicle::setVehicleData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice) {
    id = vehicleId;
    brand = vehicleBrand;
    model = vehicleModel;
    pricePerDay = vehiclePrice;
}

//get value functions
QString Vehicle::getVehicleID() {
    return id;
}
QString Vehicle::getVehicleBrand() {
    return brand;
}
QString Vehicle::getVehicleModel() {
    return model;
}
double Vehicle::getVehiclePrice() {
    return pricePerDay;
}
bool Vehicle::getIsVehicleRented() {
    return rentStatus;
}


//function used to mark a vehicle as rented
void Vehicle::rentVehicle() {
    rentStatus = true;
}

//function used to mark a vehicle as returned
void Vehicle::returnVehicle() {
    rentStatus = false;
}

//access the "rentStatus" private bool member variable
void Vehicle::setRentStatus(bool status) {
    rentStatus = status;
}


//Display added vehicle info
void Vehicle::displayVehicleInfo() {
    qout << "ID: " << id << Qt::endl;
    qout << "Brand: " << brand << Qt::endl;
    qout << "Model: " << model << Qt::endl;
    qout << "Price Per Day: " << pricePerDay << Qt::endl;
    qout << "Rent status: ";
    if (rentStatus) {
        qout << "Not available" << Qt::endl;
    } else {
        qout << "Available" << Qt::endl;
    }
}
