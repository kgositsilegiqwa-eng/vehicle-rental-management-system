#ifndef VEHICLERENTALWINDOW_H
#define VEHICLERENTALWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QString>
#include <QTableWidget>
#include <QComboBox>

class VehicleRentalWindow : public QMainWindow
{
public:
    VehicleRentalWindow();

private:
    //Sets up the graphical interface
    void setupVehicleRentalInterface();

    //Displays vehicles already loaded from the file in the table
    void populateVehicleTable();

    //Loads saved vehicle data from the text file
    void loadVehicleDataFromFile();

    //Vehicle type selection
    QComboBox* vehicleTypeSelector;

    //General vehicle data
    QLineEdit* vehicleIDInput;
    QLineEdit* vehicleBrandInput;
    QLineEdit* vehicleModelInput;
    QLineEdit* vehiclePriceInput;
    QLineEdit* vehicleSearchInput;

    //Car specific data
    QLabel* carDoorsLabel;
    QLineEdit* carDoorsInput;
    QLabel* carEngineLabel;
    QLineEdit* carEngineInput;

    //Motorcycle specific data
    QLabel* motorcycleEngineCCLabel;
    QLineEdit* motorcycleEngineCCInput;

    //vehicles display table
    QTableWidget* vehicleTable;

private slots:
    void updateVehicleTypeFields(const QString& selectedVehicleType);
    void addVehicle();
    void rentSelectedVehicle();
    void returnSelectedVehicle();
    void removeSelectedVehicle();
    void searchVehicle();
};

#endif // VEHICLERENTALWINDOW_H
