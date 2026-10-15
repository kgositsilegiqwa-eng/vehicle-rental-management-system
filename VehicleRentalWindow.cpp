#include "VehicleRentalWindow.h"
#include "Vehicle.h"
#include "CarMotorcycle.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QAbstractItemView>

extern QList<Vehicle*> vehicleList;
void saveVehicleDataToFile();

VehicleRentalWindow::VehicleRentalWindow(){
    setupVehicleRentalInterface();
    populateVehicleTable();
}

void VehicleRentalWindow::setupVehicleRentalInterface(){
    setWindowTitle("Vehicle Rental Management System (Student number:27613658_Kgositsile_Khanyisa_Giqwa_COS2614_Assignment_3)");
    resize(1000, 700);

    //central widget that holds the application interface
    QWidget* centralWidget = new QWidget(this);

    //main vertical layout for the interface
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    //central widget for the main window
    setCentralWidget(centralWidget);

    //create vehicle information input fields
    QGridLayout* vehicleInformationLayout = new QGridLayout();

    QLabel* vehicleTypeLabel = new QLabel("Vehicle Type:"); //Create label for vehicle type selection
    vehicleTypeSelector = new QComboBox(); //Create dropdown for selecting vehicle type

    vehicleTypeSelector->addItem("Car"); //Add Car as a vehicle type option
    vehicleTypeSelector->addItem("Motorcycle"); //Add Motorcycle as a vehicle type option

    //connect vehicle type selection toe vehicle type update slot
    connect(vehicleTypeSelector, &QComboBox::currentTextChanged, this, &VehicleRentalWindow::updateVehicleTypeFields);

    QLabel* vehicleIDLabel = new QLabel("Vehicle ID:");
    vehicleIDInput = new QLineEdit();

    QLabel* vehicleBrandLabel = new QLabel("Brand:");
    vehicleBrandInput = new QLineEdit();

    QLabel* vehicleModelLabel = new QLabel("Model:");
    vehicleModelInput = new QLineEdit();

    QLabel* vehiclePriceLabel = new QLabel("Price Per Day:");
    vehiclePriceInput = new QLineEdit();

    carDoorsLabel = new QLabel("Number of Doors:");
    carDoorsInput = new QLineEdit();

    carEngineLabel = new QLabel("Engine Cylinders:");
    carEngineInput = new QLineEdit();

    motorcycleEngineCCLabel = new QLabel("Engine CC:");
    motorcycleEngineCCInput = new QLineEdit();

    //Set Car as the initial vehicle type
    updateVehicleTypeFields("Car");

    //Add labels and input fields to the grid layout

    vehicleInformationLayout->addWidget(vehicleTypeLabel, 0, 0); //Add vehicle type label to the first row
    vehicleInformationLayout->addWidget(vehicleTypeSelector, 0, 1); //Add vehicle type selector to the first row

    vehicleInformationLayout->addWidget(vehicleIDLabel, 1, 0);
    vehicleInformationLayout->addWidget(vehicleIDInput, 1, 1);

    vehicleInformationLayout->addWidget(vehicleBrandLabel, 2, 0);
    vehicleInformationLayout->addWidget(vehicleBrandInput, 2, 1);

    vehicleInformationLayout->addWidget(vehicleModelLabel, 3, 0);
    vehicleInformationLayout->addWidget(vehicleModelInput, 3, 1);

    vehicleInformationLayout->addWidget(vehiclePriceLabel, 4, 0);
    vehicleInformationLayout->addWidget(vehiclePriceInput, 4, 1);

    vehicleInformationLayout->addWidget(carDoorsLabel, 5, 0);
    vehicleInformationLayout->addWidget(carDoorsInput, 5, 1);

    vehicleInformationLayout->addWidget(carEngineLabel, 6, 0);
    vehicleInformationLayout->addWidget(carEngineInput, 6, 1);

    vehicleInformationLayout->addWidget(motorcycleEngineCCLabel, 7, 0);
    vehicleInformationLayout->addWidget(motorcycleEngineCCInput, 7, 1);

    //add vehicle information section to the main layout
    mainLayout->addLayout(vehicleInformationLayout);

    QPushButton* addVehicleButton = new QPushButton("Add Vehicle");
    connect(addVehicleButton, &QPushButton::clicked, this, &VehicleRentalWindow::addVehicle);
    mainLayout->addWidget(addVehicleButton);

    vehicleTable = new QTableWidget();

    //Button to rent the currently selected vehicle
    QPushButton* rentVehicleButton = new QPushButton("Rent Selected Vehicle");
    connect(rentVehicleButton, &QPushButton::clicked, this, &VehicleRentalWindow::rentSelectedVehicle);
    mainLayout->addWidget(rentVehicleButton);

    //Button to return the currently selected vehicle
    QPushButton* returnVehicleButton = new QPushButton("Return Selected Vehicle");
    connect(returnVehicleButton, &QPushButton::clicked, this, &VehicleRentalWindow::returnSelectedVehicle);
    mainLayout->addWidget(returnVehicleButton);

    //Button to remove currently selected vehicle
    QPushButton* removeVehicleButton = new QPushButton("Delete Selected Vehicle");
    connect(removeVehicleButton, &QPushButton::clicked, this, &VehicleRentalWindow::removeSelectedVehicle);
    mainLayout->addWidget(removeVehicleButton);

    //Search vehicle by Vehicle ID
    vehicleSearchInput = new QLineEdit();
    vehicleSearchInput->setPlaceholderText("Enter Vehicle ID to search");

    QPushButton* searchVehicleButton = new QPushButton("Search Vehicle");
    connect(searchVehicleButton, &QPushButton::clicked, this, &VehicleRentalWindow::searchVehicle);

    mainLayout->addWidget(vehicleSearchInput);
    mainLayout->addWidget(searchVehicleButton);

    vehicleTable->setColumnCount(9);
    vehicleTable->setHorizontalHeaderLabels({"Type", "Vehicle ID", "Brand", "Model", "Price Per Day(ZAR)", "Doors", "Motorcycle Engine CC", "Car Engine Cylinders", "Rent Status"});
    vehicleTable->resizeColumnsToContents();
    vehicleTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    vehicleTable->horizontalHeader()->setStretchLastSection(false);
    vehicleTable->setAlternatingRowColors(true);
    vehicleTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    vehicleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    mainLayout->addWidget(vehicleTable);
}

void VehicleRentalWindow::populateVehicleTable()
{
    for (Vehicle* currentVehicle : vehicleList)
    {
        Car* currentCar = dynamic_cast<Car*>(currentVehicle);

        if (currentCar != nullptr)
        {
            int newRow = vehicleTable->rowCount();
            vehicleTable->insertRow(newRow);

            vehicleTable->setItem(newRow, 0, new QTableWidgetItem("Car"));
            vehicleTable->setItem(newRow, 1, new QTableWidgetItem(currentCar->getVehicleID()));
            vehicleTable->setItem(newRow, 2, new QTableWidgetItem(currentCar->getVehicleBrand()));
            vehicleTable->setItem(newRow, 3, new QTableWidgetItem(currentCar->getVehicleModel()));
            vehicleTable->setItem(newRow, 4, new QTableWidgetItem( QString::number(currentCar->getVehiclePrice(), 'f', 2)));
            vehicleTable->setItem(newRow, 5, new QTableWidgetItem( QString::number(currentCar->getDoors())));
            vehicleTable->setItem(newRow, 6, new QTableWidgetItem("-"));
            vehicleTable->setItem(newRow, 7, new QTableWidgetItem( QString::number(currentCar->getEngine())));
            vehicleTable->setItem(newRow, 8, new QTableWidgetItem(currentCar->getIsVehicleRented() ? "Rented" : "Available"));

        }

        Motorcycle* currentMotorcycle =dynamic_cast<Motorcycle*>(currentVehicle);

        if (currentMotorcycle != nullptr)
        {
            int newRow = vehicleTable->rowCount();
            vehicleTable->insertRow(newRow);

            vehicleTable->setItem(newRow, 0, new QTableWidgetItem("Motorcycle"));
            vehicleTable->setItem(newRow, 1, new QTableWidgetItem(currentMotorcycle->getVehicleID()));
            vehicleTable->setItem(newRow, 2, new QTableWidgetItem(currentMotorcycle->getVehicleBrand()));
            vehicleTable->setItem(newRow, 3, new QTableWidgetItem(currentMotorcycle->getVehicleModel()));
            vehicleTable->setItem(newRow, 4, new QTableWidgetItem( QString::number(currentMotorcycle->getVehiclePrice(), 'f', 2)));
            vehicleTable->setItem(newRow, 5, new QTableWidgetItem("-"));
            vehicleTable->setItem(newRow, 6, new QTableWidgetItem( QString::number(currentMotorcycle->getEngineCC())));
            vehicleTable->setItem(newRow, 7, new QTableWidgetItem("-"));
            vehicleTable->setItem(newRow, 8, new QTableWidgetItem(currentMotorcycle->getIsVehicleRented() ? "Rented" : "Available"));

        }
    }
    vehicleTable->resizeColumnsToContents();

    for (int columnIndex = 0;
         columnIndex < vehicleTable->columnCount();
         ++columnIndex)
    {
        vehicleTable->setColumnWidth(
            columnIndex,
            vehicleTable->columnWidth(columnIndex) + 20);
    }
}

void VehicleRentalWindow::updateVehicleTypeFields(const QString& selectedVehicleType){
    bool carSelected = (selectedVehicleType == "Car");

    carDoorsLabel->setVisible(carSelected);
    carDoorsInput->setVisible(carSelected);

    carEngineLabel->setVisible(carSelected);
    carEngineInput->setVisible(carSelected);

    motorcycleEngineCCLabel->setVisible(!carSelected);
    motorcycleEngineCCInput->setVisible(!carSelected);
}

void VehicleRentalWindow::addVehicle(){
    QString selectedVehicleType = vehicleTypeSelector->currentText();

    QString vehicleID = vehicleIDInput->text();
    QString vehicleBrand = vehicleBrandInput->text();
    QString vehicleModel = vehicleModelInput->text();


    if (vehicleID.isEmpty() || vehicleBrand.isEmpty() || vehicleModel.isEmpty() || vehiclePriceInput->text().isEmpty()) {

        QMessageBox::warning(this, "Invalid entries", "Enter relevant data correctly.");
        return;
    }

    bool priceValid;
    double vehiclePrice = vehiclePriceInput->text().toDouble(&priceValid);

    if (!priceValid || vehiclePrice <= 0) {
        QMessageBox::warning(this, "Invalid Vehicle Price", "Enter a valid price per day.");
        return;
    }

    if (selectedVehicleType == "Car") {

        if (carDoorsInput->text().isEmpty() || carEngineInput->text().isEmpty()) {
            QMessageBox::warning(this, "Incomplete Car Information", "Enter the number of doors and engine cylinders.");
            return;
        }

        bool doorsValid;
        int numberOfDoors = carDoorsInput->text().toInt(&doorsValid);

        bool engineValid;
        int engineCylinders = carEngineInput->text().toInt(&engineValid);

        if (!doorsValid || numberOfDoors <= 0 || !engineValid || engineCylinders <= 0) {

            QMessageBox::warning(this, "Invalid Car Information", "Enter valid numbers for doors and engine cylinders.");
            return;
        }

        Car* newCar = new Car();
        newCar->setCarData(vehicleID, vehicleBrand, vehicleModel, vehiclePrice, numberOfDoors, engineCylinders);

        vehicleList.append(newCar);

        int newRow = vehicleTable->rowCount();
        vehicleTable->insertRow(newRow);

        vehicleTable->setItem(newRow, 0, new QTableWidgetItem("Car"));
        vehicleTable->setItem(newRow, 1, new QTableWidgetItem(vehicleID));
        vehicleTable->setItem(newRow, 2, new QTableWidgetItem(vehicleBrand));
        vehicleTable->setItem(newRow, 3, new QTableWidgetItem(vehicleModel));
        vehicleTable->setItem(newRow, 4, new QTableWidgetItem(QString::number(vehiclePrice, 'f', 2)));
        vehicleTable->setItem(newRow, 5, new QTableWidgetItem(QString::number(numberOfDoors)));
        vehicleTable->setItem(newRow, 6, new QTableWidgetItem("-"));
        vehicleTable->setItem(newRow, 7, new QTableWidgetItem(QString::number(engineCylinders)));
        vehicleTable->setItem(newRow, 8, new QTableWidgetItem("Available"));


        saveVehicleDataToFile();
        QMessageBox::information(this, "Vehicle Added", "Car added to the vehicle database.");
    }
    else if (selectedVehicleType == "Motorcycle") {

        if (motorcycleEngineCCInput->text().isEmpty()) {
            QMessageBox::warning(this, "Incomplete Motorcycle Information", "Enter the motorcycle engine CC.");
            return;
        }

        bool engineCCValid;
        int engineCC = motorcycleEngineCCInput->text().toInt(&engineCCValid);

        if (!engineCCValid || engineCC <= 0) {
            QMessageBox::warning(this, "Invalid Motorcycle Information", "Enter a valid engine CC greater than zero.");
            return;
        }

        Motorcycle* newMotorcycle = new Motorcycle();
        newMotorcycle->setMotorcycleData(vehicleID, vehicleBrand, vehicleModel, vehiclePrice, engineCC);

        vehicleList.append(newMotorcycle);

        int newRow = vehicleTable->rowCount();
        vehicleTable->insertRow(newRow);

        vehicleTable->setItem(newRow, 0, new QTableWidgetItem("Motorcycle"));
        vehicleTable->setItem(newRow, 1, new QTableWidgetItem(vehicleID));
        vehicleTable->setItem(newRow, 2, new QTableWidgetItem(vehicleBrand));
        vehicleTable->setItem(newRow, 3, new QTableWidgetItem(vehicleModel));
        vehicleTable->setItem(newRow, 4, new QTableWidgetItem(QString::number(vehiclePrice, 'f', 2)));
        vehicleTable->setItem(newRow, 5, new QTableWidgetItem("-"));
        vehicleTable->setItem(newRow, 6, new QTableWidgetItem(QString::number(engineCC)));
        vehicleTable->setItem(newRow, 7, new QTableWidgetItem("-"));
        vehicleTable->setItem(newRow, 8, new QTableWidgetItem("Available"));


        saveVehicleDataToFile();
        QMessageBox::information(this, "Vehicle Added", "Motorcycle added to the vehicle database.");
    }

    vehicleIDInput->clear();
    vehicleBrandInput->clear();
    vehicleModelInput->clear();
    vehiclePriceInput->clear();

    carDoorsInput->clear();
    carEngineInput->clear();
    motorcycleEngineCCInput->clear();
}

void VehicleRentalWindow::rentSelectedVehicle(){
    int selectedRow = vehicleTable->currentRow();

    if (selectedRow < 0){
        QMessageBox::warning(this, "No Vehicle Selected", "Please select a vehicle to rent.");
        return;
    }

    QString selectedVehicleID = vehicleTable->item(selectedRow, 1)->text();

    for (Vehicle* currentVehicle : vehicleList){
        if (currentVehicle->getVehicleID() == selectedVehicleID){
            if (currentVehicle->getIsVehicleRented()){
                QMessageBox::warning(this, "Vehicle Unavailable", "This vehicle is already rented.");
                return;
            }

            currentVehicle->rentVehicle();

            vehicleTable->setItem(selectedRow, 8, new QTableWidgetItem("Rented"));

            saveVehicleDataToFile();

            QMessageBox::information(this, "Vehicle Rented", "Vehicle rented successfully.");
            return;
        }
    }

    QMessageBox::warning(this, "Vehicle Not Found", "The selected vehicle could not be found.");
}

void VehicleRentalWindow::returnSelectedVehicle(){

    int selectedRow = vehicleTable->currentRow();

    if (selectedRow < 0){

        QMessageBox::warning(this, "No Vehicle Selected", "Please select a vehicle to return.");
        return;
    }

    QString selectedVehicleID = vehicleTable->item(selectedRow, 1)->text();

    for (Vehicle* currentVehicle : vehicleList){

        if (currentVehicle->getVehicleID() == selectedVehicleID){

            if (!currentVehicle->getIsVehicleRented()){

                QMessageBox::warning(this, "Vehicle Not Rented", "This vehicle is not currently rented.");
                return;
            }

            currentVehicle->returnVehicle();

            vehicleTable->setItem(selectedRow, 8, new QTableWidgetItem("Available"));


            saveVehicleDataToFile();

            QMessageBox::information(this, "Vehicle Returned", "Vehicle returned successfully.");

            return;
        }
    }

    QMessageBox::warning(this, "Vehicle Not Found", "The selected vehicle could not be found.");
}

void VehicleRentalWindow::removeSelectedVehicle(){

    int selectedRow = vehicleTable->currentRow();

    if (selectedRow < 0){

        QMessageBox::warning( this, "No Vehicle Selected", "Please select a vehicle to delete.");
        return;
    }

    QString selectedVehicleID = vehicleTable->item(selectedRow, 1)->text();

    QMessageBox::StandardButton confirmation = QMessageBox::question(this,"Confirm Vehicle Removal", "Are you sure you want to permanently delete this vehicle " +
        selectedVehicleID + "?", QMessageBox::Yes | QMessageBox::No);

    if (confirmation != QMessageBox::Yes){
        return;
    }

    for (int vehicleIndex = 0; vehicleIndex < vehicleList.size(); ++vehicleIndex){
        Vehicle* currentVehicle = vehicleList.at(vehicleIndex);

        if (currentVehicle->getVehicleID() == selectedVehicleID){

            delete currentVehicle;
            vehicleList.removeAt(vehicleIndex);

            vehicleTable->removeRow(selectedRow);

            saveVehicleDataToFile();

            QMessageBox::information(this,"Vehicle Removed","Vehicle permanently deleted.");

            return;
        }
    }

}

void VehicleRentalWindow::searchVehicle(){

    QString searchID = vehicleSearchInput->text().trimmed();

    if (searchID.isEmpty()){
        QMessageBox::warning(this, "Search Vehicle", "Please enter a Vehicle ID.");
        return;
    }

    for (Vehicle* currentVehicle : vehicleList){
        if (currentVehicle->getVehicleID().compare(searchID, Qt::CaseInsensitive) == 0){
            QString vehicleDetails;

            Car* currentCar = dynamic_cast<Car*>(currentVehicle);

            if (currentCar != nullptr) {
                vehicleDetails =
                    "Vehicle Type: Car\n"
                        "Vehicle ID: " + currentCar->getVehicleID() + "\n"
                                                   "Brand: " + currentCar->getVehicleBrand() + "\n"
                                                      "Model: " + currentCar->getVehicleModel() + "\n"
                                                      "Price Per Day: R" + QString::number(currentCar->getVehiclePrice(), 'f', 2) + "\n"
                                                                               "Number of Doors: " + QString::number(currentCar->getDoors()) + "\n"
                                                                "Engine Cylinders: " + QString::number(currentCar->getEngine()) + "\n"
                                                                 "Rent Status: " + QString(currentCar->getIsVehicleRented() ? "Rented" : "Available");
            }

            Motorcycle* currentMotorcycle = dynamic_cast<Motorcycle*>(currentVehicle);

            if (currentMotorcycle != nullptr){
                vehicleDetails =
                    "Vehicle Type: Motorcycle\n"
                    "Vehicle ID: " + currentMotorcycle->getVehicleID() + "\n"
                                                          "Brand: " + currentMotorcycle->getVehicleBrand() + "\n"
                                                             "Model: " + currentMotorcycle->getVehicleModel() + "\n"
                                                             "Price Per Day: R" + QString::number(currentMotorcycle->getVehiclePrice(), 'f', 2) + "\n"
                                                                                      "Engine CC: " + QString::number(currentMotorcycle->getEngineCC()) + "\n"
                                                                          "Rent Status: " + QString(currentMotorcycle->getIsVehicleRented() ? "Rented" : "Available");
            }

            QMessageBox::information(this, "Vehicle Found", vehicleDetails);

            vehicleSearchInput->clear();

            return;
        }
    }

    QMessageBox::warning(this, "Vehicle Not Found", "No vehicle with Vehicle ID \"" + searchID + "\" was found.");
}
