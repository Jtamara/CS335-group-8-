#pragma once
#ifndef ATTACK_H
#define ATTACK_H

#include <iostream>
#include "types.hpp"

enum class Category {
    Physical,
    Special
};

class Attack {
private:
    std::string name_;
    Category category_;
    int power_;
    double accuracy_;
    Types type_;
public:
    Attack(std::string name, Category category, int power, double accuracy, Types type) : name_(name), category_(category), power_(power), accuracy_(accuracy), type_(type) {};

    std::string get_name() {
        return this->name_;
    };

    Category get_category() {
        return this->category_;
    };

    int get_power() {
        return this->power_;
    };

    double get_accuracy() {
        return this->accuracy_;
    };

    Types get_type() {
        return this->type_;
    };
};

#endif // ATTACK_H