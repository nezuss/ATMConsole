#pragma once
#include "ATM.h"
#include "ATMOperation.h"

class PrintAvailabilityOperation : public ATMOperation {
private:
    ATM& atm;

public:
    //? Print availability
    PrintAvailabilityOperation(ATM& atm) : atm(atm) {}

    void execute() override { atm.printAvailability(); }
};