#include <iostream>
#include <vector>
#include <map>
#include <stdexcept>
#include <string>
#include <sstream>
//? Load ATM atributes
#include "ATM.h"
#include "LoadBoxOperation.h"
#include "WithdrawMoneyOperation.h"
#include "PrintAvailabilityOperation.h"

int main() {
    ATM atm;
    std::string input;

    std::cout << "ATM Console" << std::endl;

    while (true) {
        try {
            std::cout << "Enter command -> ";
            std::getline(std::cin, input);

            if (input.empty()) continue;

            if (input == "Q") break;

            std::istringstream iss(input);
            char command;
            iss >> command;

            if (command == 'L') {
                int boxNumber, nominal, numberOfBanknotes;
                char separator_1, separator_2, separator_3;
                if (iss >> separator_1 >> boxNumber >> separator_2 >>
                    nominal >> separator_3 >> numberOfBanknotes) {
                    if (separator_1 == '#' && separator_2 == '#' &&
                        separator_3 == '#') {
                        LoadBoxOperation op(atm, boxNumber,
                                            nominal, numberOfBanknotes);
                        op.execute();
                        continue;
                    }
                }
            }
            else if (command == 'W') {
                int amount;
                char separator;
                if (iss >> separator >> amount && separator == '#') {
                    WithdrawMoneyOperation op(atm, amount);
                    op.execute();
                    continue;
                }
            }
            else if (command == 'P') {
                PrintAvailabilityOperation op(atm);
                op.execute();
                continue;
            }

            std::cerr << "Invalid command" << std::endl;
        }
        catch (const std::exception& ex)
        { std::cerr << "Error -> " << ex.what() << std::endl; }
    }

    std::cout << "Exiting ATM Console" << std::endl;
    return 0;
}