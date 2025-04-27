#pragma once

class ATMOperation {
public:
    virtual void execute() = 0;
    virtual ~ATMOperation() {}
};