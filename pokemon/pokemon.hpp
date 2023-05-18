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
    int base_power_;
    int base_special_power_;
    int health_;
    int def_;
    int spdef_;
    Types type_;
    std::vector<std::shared_ptr<Attack>> attacks_; // While attacks are limited to 4 in the actual pokemon game, we will allow for unlimited attacks as a feature
public:
    Pokemon(std::string name, int health, int base_power, int base_special_power, int def, int spdef, Types type) 
        : name_(name), health_(health), base_power_(base_power), base_special_power_(base_special_power), def_(def), spdef_(spdef), type_(type) {};

    std::string get_name() {
        return this->name_;
    };

    int get_health() {
        return this->health_;
    };

    void add_health(int health) {
        this->health_ += health;
    };

    bool has_fainted() {
        return this->health_ <= 0;
    };

    Types get_type() {
        return this->type_;
    };

    int get_def() {
        return this->def_;
    };

    void add_def(int def) {
        this->def_ += def;
    };

    int get_spdef() {
        return this->spdef_;
    };

    void add_spdef(int spdef) {
        this->spdef_ += spdef;
    };

    int get_base_power() {
        return this->base_power_;
    };

    void add_base_power(int base_power) {
        this->base_power_ += base_power;
    };

    int get_base_special_power() {
        return this->base_special_power_;
    };

    void add_base_special_power(int base_special_power) {
        this->base_special_power_ += base_special_power;
    };

    void TakeDamage(int damage) {
        this->health_ -= damage;
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
        // damage calculations used from formula: https://bulbapedia.bulbagarden.net/wiki/Damage for Generation 1
        // Damage = (((2 x Level x Critical) / 5) + 2) * Power * (A/D) / 50) x STAB x Type x RAND(0.85, 1.0)

        auto move_used = this->attacks_[move_selection];

        // Check for accuracy
        if (move_used->get_accuracy() < ((double)rand() / (RAND_MAX))) {
            std::cout << "The attack missed!" << std::endl;
            return 0;
        }

        int total_damage = 0;
        int critical_hit = 1;

        // Check for critical hits with a 6.25% chance
        if (rand() % 16 == 0) {
            std::cout << "Critical hit!" << std::endl;
            critical_hit = 2;
        }

        // (((2*Level*Critical) / 5) + 2) * Power
        total_damage = (((2 * 100 * critical_hit) / 5) + 2) * move_used->get_power(); // Assume all pokemon are level 100

        // Calculate Special/Physical attacks with opponent's defense stat
        // (A/D)
        if (move_used->get_category() == Category::Special) {
            // (Power x A/D)
            total_damage *= this->get_base_special_power() / other->get_spdef();
        }
        else {
            total_damage *= this->get_base_power() / other->get_def();
        }

        total_damage /= 50;
        total_damage += 2;

        // Calculate STAB bonus
        if (move_used->get_type() == this->get_type()) {
            total_damage *= 1.5;
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

        // TODO: Randomize damage by 15%
        total_damage *= ((double)rand() / (RAND_MAX)) * 0.15 + 0.85;

        return total_damage;
    };
};

#endif // POKEMON_H