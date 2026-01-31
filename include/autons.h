#pragma once
#include "lemlib/api.hpp"
#include "pros/misc.hpp"

class Autons {
public:
    Autons(lemlib::Chassis* chassis);

    void testAuton();      
    void skillsAuton();    
    void RedLeft();
    void RedRight();
    void BlueLeft();
    void BlueRight();

private:
    lemlib::Chassis* chassis;
};
