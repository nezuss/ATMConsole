#pragma once
#include <iostream>
#include <map>

class ATM {
private:
    //? Box structure
    struct Box {
        int nominal;
        int banknotes;

        Box() : nominal(0), banknotes(0) {}
        Box(int n, int b) : nominal(n), banknotes(b) {}

        int getTotalAmount() const { return nominal * banknotes; }
    };

    std::map<int, Box> boxes;
    const int maxBanknotesPerBox = 100;
    const int maxWithdrawalAmount = 3000;

public:
    //? Load boxs with banknotes
    //    BOX    NOMINAL   COUNT
    // L#1-6#10/20/50/100#1-100
    void loadBox(int boxNumber, int nominal, int numberOfBanknotes) {
        if (boxNumber < 1 || boxNumber > 6)
            throw std::invalid_argument("Invalid box number. Must be between 1 and 6");
        if (nominal != 100 && nominal != 50 && nominal != 20 && nominal != 10)
            throw std::invalid_argument("Invalid nominal. Allowed values are 100, 50, 20, and 10");
        if (numberOfBanknotes < 1 || numberOfBanknotes > maxBanknotesPerBox)
            throw std::invalid_argument("Invalid number of banknotes. Must be between 1 and 100");

        boxes[boxNumber] = Box(nominal, numberOfBanknotes);
    }

    //? Withdraw money from boxes
    // L#COUNT
    //? Output
    // BOX#NOMINAL#COUNT#AMOUNT
    void withdrawMoney(int amount) {
        if (amount <= 0 || amount > maxWithdrawalAmount)
            throw std::invalid_argument("Invalid withdrawal amount. Must be between 1 and 3000 EUR");

        std::map<int, int> withdrawalPlan;
        int remainingAmount = amount;

        for (auto& box : boxes) {
            if (remainingAmount == 0) break;
            int boxNumber = box.first;
            int nominal = box.second.nominal;
            int banknotesAvailable = box.second.banknotes;

            if (nominal > 0 && banknotesAvailable > 0) {
                int banknotesNeeded = remainingAmount / nominal;
                int banknotesToWithdraw = std::min(banknotesNeeded, banknotesAvailable);

                if (banknotesToWithdraw > 0) {
                    withdrawalPlan[boxNumber] = banknotesToWithdraw;
                    remainingAmount -= banknotesToWithdraw * nominal;
                }
            }
        }

        if (remainingAmount > 0)
            throw std::runtime_error("Insufficient funds or denominations to fulfill the withdrawal request");

        for (auto& withdrawal : withdrawalPlan) {
            int boxNumber = withdrawal.first;
            int banknotesToWithdraw = withdrawal.second;
            boxes[boxNumber].banknotes -= banknotesToWithdraw;

            std::cout << boxNumber << "#" << boxes[boxNumber].nominal << "#" << banknotesToWithdraw
                << "#" << (banknotesToWithdraw * boxes[boxNumber].nominal) << std::endl;
        }
    }

    //? Print availability of boxes
    // P
    void printAvailability() const {
        int totalAmount = 0;

        for (const auto& box : boxes) {
            int boxNumber = box.first;
            int nominal = box.second.nominal;
            int banknotes = box.second.banknotes;
            int amount = box.second.getTotalAmount();

            std::cout << boxNumber << "#" << nominal << "#" <<
                banknotes << "#" << amount << std::endl;
            totalAmount += amount;
        }

        std::cout << "Total -> " << totalAmount << std::endl;
    }
};