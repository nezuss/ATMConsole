#pragma once
#include "ATM.h"
#include "ATMOperation.h"

class WithdrawMoneyOperation : public ATMOperation {
private:
    ATM& atm;
    int amount;

public:
    //? Withdraw money
    WithdrawMoneyOperation(ATM& atm, int amount)
        : atm(atm), amount(amount) {
    }

    void execute() override { atm.withdrawMoney(amount); }
};