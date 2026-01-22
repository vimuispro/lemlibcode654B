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

private:
    lemlib::Chassis* chassis;
};
