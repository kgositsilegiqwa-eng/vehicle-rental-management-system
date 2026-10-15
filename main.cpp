#include <QTextStream>
#include <QList>
#include <QFile>
#include <QStringList>
#include <QApplication>
#include "VehicleRentalWindow.h"
#include "Vehicle.h"
#include "CarMotorcycle.h"

QTextStream qin(stdin);
QTextStream qout(stdout);

//qlist used to store Car and Motorcycle objects through Vehicle pointers
QList<Vehicle*> vehicleList;


//Save Vehicle objects to file function
//Everytime when saving, the contents of the car and motorcycle list overwrite the file
//everytime that the saveVehicleDataToFile function is called, it doesnt just add a new object, but actually re-adds the entire array to overwrite the pre-existing file
void saveVehicleDataToFile() {
    QFile vehicleDataFile("vehiclesLogbook.txt"); //File name
    //checks if the file was successfully opened
    if (!vehicleDataFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qout << "Could not open file." << Qt::endl;
        qout.flush();
        return;
    }

    QTextStream vehicleDataStream(&vehicleDataFile); //creates a text stream used to write vehicle data to the file

    QList<Vehicle*>::iterator vehicleIterator; //traverse the vehicle list using a Qt iterator

    //traverses vehicle list from the beginning vehicle to the end using the iterator
    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){
        Vehicle* currentVehicle = *vehicleIterator;

        //save car data
        Car* currentCar = dynamic_cast<Car*>(currentVehicle); //check if current vehicle is a car
        //checks if current vehicle is a car, then writes data to vehicle data stream,
        // using '|' to separate each piece of vehicle data in the file
        if (currentCar != nullptr){
            vehicleDataStream << "Car|"
                              << currentCar->getVehicleID() << "|"
                              << currentCar->getVehicleBrand() << "|"
                              << currentCar->getVehicleModel() << "|"
                              << currentCar->getVehiclePrice() << "|"
                              << currentCar->getDoors() << "|"
                              << currentCar->getEngine() << "|"
                              << currentCar->getIsVehicleRented()
                              << Qt::endl;
        }

        //save motorcycle data
        Motorcycle* currentMotorcycle = dynamic_cast<Motorcycle*>(currentVehicle);
        if (currentMotorcycle != nullptr){
            vehicleDataStream << "Motorcycle|"
                              << currentMotorcycle->getVehicleID() << "|"
                              << currentMotorcycle->getVehicleBrand() << "|"
                              << currentMotorcycle->getVehicleModel() << "|"
                              << currentMotorcycle->getVehiclePrice() << "|"
                              << currentMotorcycle->getEngineCC() << "|"
                              << currentMotorcycle->getIsVehicleRented()
                              << Qt::endl;
        }
    }


    vehicleDataFile.close();
}

//Load data from the text file function
//Everytime the program is ran, all the contents of the file are loaded into the vehicle list
void loadVehicleDataFromFile() {
    QFile vehicleDataFile("vehiclesLogbook.txt");

    //check if file was successfully opened
    if (!vehicleDataFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qout << "No data found." << Qt::endl;
        qout.flush();
        return;
    }

    QTextStream vehicleDataStream(&vehicleDataFile); //creates a text stream connected to the vehicle data file for reading contents
    while (!vehicleDataStream.atEnd()){  //continues reading while there are still lines remaining in the vehicle data file
        QString fileLine = vehicleDataStream.readLine(); //reads the next complete line from the vehicle data file
        QStringList vehicleData = fileLine.split("|"); //splits the line into separate vehicle data fields using "|"

        //checks whether the record stores data for a car
        if (vehicleData[0] == "Car"){
            //vehicleData temporarily stores the individual fields of the current vehicle record. These fields are then assigned to variables with the appropriate data types
            QString id = vehicleData[1];
            QString brand = vehicleData[2];
            QString model = vehicleData[3];
            double price = vehicleData[4].toDouble(); //convert QString containing number to a double
            int doors = vehicleData[5].toInt(); //convert QString containing number to a integer
            int engine = vehicleData[6].toInt();
            bool rented = vehicleData[7].toInt();

            //create new car object
            Car* loadedCar = new Car();

            //set loaded car information
            loadedCar->setCarData(id, brand, model, price, doors, engine );
            loadedCar->setRentStatus(rented);

            vehicleList.append(loadedCar);//add loaded car to the vehicle list
        }

        else if (vehicleData[0] == "Motorcycle") {
            QString id = vehicleData[1];
            QString brand = vehicleData[2];
            QString model = vehicleData[3];
            double price = vehicleData[4].toDouble();
            int engineCC = vehicleData[5].toInt();
            bool rented = vehicleData[6].toInt();

            Motorcycle* loadedMotorcycle = new Motorcycle();

            loadedMotorcycle->setMotorcycleData(id, brand, model, price, engineCC);

            loadedMotorcycle->setRentStatus(rented);

            vehicleList.append(loadedMotorcycle);

        }
    }
    vehicleDataFile.close();
}

//Function to add a new car
void addCar() {
    QString id, brand, model;
    double price;
    int doors, engine;

    qout << "Enter car ID: ";
    qout.flush();
    qin >> id;

    qout << "Enter car brand: ";
    qout.flush();
    qin >> brand;

    qout << "Enter car model: ";
    qout.flush();
    qin >> model;

    qout << "Enter daily rental price: ";
    qout.flush();
    qin >> price;

    qout << "Enter number of Doors: ";
    qout.flush();
    qin >> doors;

    qout << "Enter engine cylinders: ";
    qout.flush();
    qin >> engine;

    //create new car object
    Car* newCar = new Car();
    //set car information
    newCar->setCarData(id, brand, model, price, doors, engine);
    //add car to list
    vehicleList.append(newCar);

    qout << "Car added." << Qt::endl;
    qout.flush();

    saveVehicleDataToFile();
}

//Add motorcycle function
void addMotorcycle() {
    QString id, brand, model;
    double price;
    int engineCC;

    qout << "Enter motorcycle ID: ";
    qout.flush();
    qin >> id;

    qout << "Enter motorcycle brand: ";
    qout.flush();
    qin >> brand;

    qout << "Enter motorcycle model: ";
    qout.flush();
    qin >> model;

    qout << "Enter daily rental price: ";
    qout.flush();
    qin >> price;

    qout << "Enter engine CC: ";
    qout.flush();
    qin >> engineCC;

    //create new motorcycle object
    Motorcycle* newMotorcycle = new Motorcycle();
    //set motorcycle information
    newMotorcycle->setMotorcycleData(id, brand, model, price, engineCC);
    //add motorcycle to list
    vehicleList.append(newMotorcycle);

    qout << "Motorcycle added." << Qt::endl;
    qout.flush();

    saveVehicleDataToFile();
}

//Vehicle display function
void displayAllVehicles() {
    if (vehicleList.isEmpty()){
        qout << "No vehicles owned." << Qt::endl;
        qout.flush();
        return;
    }

    QList<Vehicle*>::iterator vehicleIterator;//create iterator used to traverse the vehicle list

    //prints the details of the vehicle at the current iteration using display function depending on the vehicle.
    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){
        Vehicle* currentVehicle = *vehicleIterator;
        Car* currentCar = dynamic_cast<Car*>(currentVehicle);//identifies if the current vehicle is a car
        if (currentCar != nullptr){
            currentCar->displayCar();
        }
        Motorcycle* currentMotorcycle = dynamic_cast<Motorcycle*>(currentVehicle);
        if (currentMotorcycle != nullptr){
            currentMotorcycle->displayMotorcycle();
        }
    }
    qout.flush();
}

//Display unrented vehicles function
void displayAvailableVehicles() {
    bool availability = false;
    if (vehicleList.isEmpty()){
        qout << "No vehicles owned." << Qt::endl;
        qout.flush();
        return;
    }

    //traverse vehicleList using iterator
    QList<Vehicle*>::iterator vehicleIterator;
    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){
        Vehicle* currentVehicle = *vehicleIterator;

        if(!currentVehicle -> getIsVehicleRented()){
            Car* currentCar = dynamic_cast<Car*>(currentVehicle);
            if (currentCar != nullptr){
                currentCar->displayCar();
                availability = true;
            }
            Motorcycle* currentMotorcycle = dynamic_cast<Motorcycle*>(currentVehicle);
            if (currentMotorcycle != nullptr){
                currentMotorcycle->displayMotorcycle();
                availability = true;
            }
        }

    }

    if (availability == false){
        qout << "No available vehicles." << Qt::endl;
    }
    qout.flush();
}

//Function to rent a vehicle by ID search
void rentVehicleByIDSearch() {
    QString id;
    qout << "Enter Vehicle ID: ";
    qout.flush();
    qin >> id;

    QList<Vehicle*>::iterator vehicleIterator;
    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){

        Vehicle* currentVehicle = *vehicleIterator;
        //check whether the current vehicle of the iteration has the matching ID
        if (currentVehicle->getVehicleID() == id){
            //check whether the vehicle is already rented
            if (currentVehicle->getIsVehicleRented()){
                qout << "Vehicle currently unavailable." << Qt::endl;
            }
            else {
                currentVehicle->rentVehicle();
                qout << "Vehicle rented successfully." << Qt::endl;
                // Save the updated rental status to the file
                saveVehicleDataToFile();
            }
            qout.flush();
            return;
        }
    }

    qout << "Vehicle not found" << Qt::endl;
    qout.flush();
}

//Vehicle return function using ID
void returnVehicle() {
    QString id;
    qout << "Enter Vehicle ID: ";
    qout.flush();
    qin >> id;

    QList<Vehicle*>::iterator vehicleIterator;

    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){
        Vehicle* currentVehicle = *vehicleIterator;

        //check whether the current vehicle of the iteration has the matching ID
        if (currentVehicle->getVehicleID() == id) {

            if (!currentVehicle->getIsVehicleRented()){ //check whether the vehicle is currently rented
                qout << "Vehicle not currently rented." << Qt::endl;
            }
            else{
                currentVehicle->returnVehicle();
                qout << "Vehicle returned successfully." << Qt::endl;

                saveVehicleDataToFile(); //update file
            }

            qout.flush();
            return;
        }
    }
    qout << "Vehicle matches not found" << Qt::endl;
    qout.flush();
}

//remove vehicle from database by ID
void removeVehicleByID(){
    QString id;

    qout << "Enter Vehicle ID: ";
    qout.flush();
    qin >> id;

    QList<Vehicle*>::iterator vehicleIterator;

    for (vehicleIterator = vehicleList.begin(); vehicleIterator != vehicleList.end(); ++vehicleIterator){
        Vehicle* currentVehicle = *vehicleIterator;

        if (currentVehicle->getVehicleID() == id){
            delete currentVehicle; //Delete current vehicle object from memory
            vehicleList.erase(vehicleIterator); //remove the vehicle pointer from the vehicle list

            qout << "Vehicle removed." << Qt::endl;
            qout.flush();

            saveVehicleDataToFile();
            return;
        }
    }

    qout << "Vehicle not found." << Qt::endl;
    qout.flush();

}



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    loadVehicleDataFromFile();

    VehicleRentalWindow window;
    window.show();

    return app.exec();
}
