#pragma once
#include "ATM.h"
#include "ATMOperation.h"

class LoadBoxOperation : public ATMOperation {
private:
    ATM& atm;
    int boxNumber;
    int nominal;
    int numberOfBanknotes;

public:
    //? Load boxe
    LoadBoxOperation(ATM& atm, int boxNumber,
        int nominal, int numberOfBanknotes)
        : atm(atm), boxNumber(boxNumber),
        nominal(nominal), numberOfBanknotes(numberOfBanknotes) {
    }

    void execute() override
    {
        atm.loadBox(boxNumber, nominal, numberOfBanknotes);
    }
};