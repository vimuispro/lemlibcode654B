#pragma once
#include "lemlib/api.hpp"
#include "pros/misc.hpp"

class Autons {
public:
    Autons(lemlib::Chassis* chassis);

    void testAuton();      
    void skillsAuton(); 

    void M3L4Right();
    void Push7Left();
    void AWPleft();

    void collect();
    void load();
    void middle_score();
    void long_score();
    void wing();

private:
    lemlib::Chassis* chassis;
};
