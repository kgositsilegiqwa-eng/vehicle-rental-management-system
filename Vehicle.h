#ifndef VEHICLE_H
#define VEHICLE_H
#include <QString>
#include <QTextStream>

// Vehicle(Parent class)
class Vehicle {
private:
    QString brand;
    QString model;
    QString id;
    double pricePerDay;
    bool rentStatus;

public:
    Vehicle();

    //function used to access private vehicle class members
    void setVehicleData(QString vehicleId, QString vehicleBrand, QString vehicleModel, double vehiclePrice);

    //get value functions
    QString getVehicleID();
    QString getVehicleBrand();
    QString getVehicleModel();
    double getVehiclePrice();
    bool getIsVehicleRented();

    //function used to mark a vehicle as rented
    void rentVehicle();

    //function used to mark a vehicle as returned->returned
    void returnVehicle();

    //access the "rentStatus" private bool member variable
    void setRentStatus(bool status);

    //function to display vehicle details
    void displayVehicleInfo();

    // Virtual destructor used to properly destroy vehicles removed from the list
    virtual ~Vehicle() = default;
};

#endif // VEHICLE_H
