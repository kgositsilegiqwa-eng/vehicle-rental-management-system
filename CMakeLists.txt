cmake_minimum_required(VERSION 3.19)
project(27613658_Assignment_3_COS2614 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(27613658_Assignment_3_COS2614
    main.cpp
    Vehicle.h Vehicle.cpp
    CarMotorcycle.h CarMotorcycle.cpp
    VehicleRentalWindow.h
    VehicleRentalWindow.cpp
)

target_link_libraries(27613658_Assignment_3_COS2614
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS 27613658_Assignment_3_COS2614
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
