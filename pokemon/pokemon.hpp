#pragma once
#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <vector>
#include <memory>
#include "types.hpp"
#include "attack.hpp"

class Pokemon {
private:
    std::string name_;
    int health_;
    Types type_;
    std::vector<std::shared_ptr<Attack>> attacks_; // While attacks are limited to 4 in the actual pokemon game, we will allow for unlimited attacks as a feature
public:
    Pokemon(std::string name, int health, Types type) : name_(name), health_(health), type_(type) {};

    std::string get_name() {
        return this->name_;
    };

    int get_health() {
        return this->health_;
    };

    bool has_fainted() {
        return this->health_ <= 0;
    };

    Types get_type() {
        return this->type_;
    };

    static bool has_fainted(const std::unique_ptr<Pokemon> & player, const std::unique_ptr<Pokemon> & opponent) {
        if (player->has_fainted() || opponent->has_fainted())
            return true;
        return false;
    };

    std::vector<std::shared_ptr<Attack>> get_attacks() {
        return this->attacks_;
    };

    void add_attack(std::shared_ptr<Attack> attack) {
        this->attacks_.push_back(attack);
    };

    std::shared_ptr<Attack> get_attack(int index) {
        return this->attacks_[index];
    };

    int CalcDamage(const std::unique_ptr<Pokemon> & other, int move_selection) {
        return 0;
    };
};

#endif // POKEMON_H