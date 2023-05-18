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
        return player->has_fainted() || opponent->has_fainted();
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
        auto move_used = this->attacks_[move_selection];
        int total_damage = move_used->get_power();
        // Check for accuracy
        if (move_used->get_accuracy() < ((double)rand() / (RAND_MAX))) {
            std::cout << "The attack missed!" << std::endl;
            return 0;
        }
        // Check for type coverage
        if (is_super_effective(move_used->get_type(), other->get_type())) {
            std::cout << "It's super effective!" << std::endl;
            total_damage *= 2;
        }
        else if (is_not_very_effective(move_used->get_type(), other->get_type())) {
            std::cout << "It's not very effective..." << std::endl;
            total_damage /= 2;
        }

        // Check for critical hits with a 6.25% chance
        if (rand() % 16 == 0) {
            std::cout << "Critical hit!" << std::endl;
            total_damage *= 2;
        }

        // TODO: Calculate Special/Physical attacks with opponent's defense stat

        return total_damage;
    };
};

#endif // POKEMON_H