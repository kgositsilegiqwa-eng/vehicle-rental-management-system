
cmake_minimum_required(VERSION 3.19)

project(VehicleRentalManagementSystem LANGUAGES CXX)

include(GNUInstallDirs)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(VehicleRentalManagementSystem
    main.cpp
    Vehicle.h
    Vehicle.cpp
    CarMotorcycle.h
    CarMotorcycle.cpp
    VehicleRentalWindow.h
    VehicleRentalWindow.cpp
)

target_link_libraries(VehicleRentalManagementSystem
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

install(TARGETS VehicleRentalManagementSystem
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

