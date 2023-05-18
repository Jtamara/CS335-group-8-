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

    void set_attacks(std::vector<std::shared_ptr<Attack>> attacks) {
        this->attacks_ = attacks;
    };

    std::shared_ptr<Attack> get_attack(int index) {
        return this->attacks_[index];
    };

    // The ratio of effective attack to effective defense, used by CalcDamage
    double CalcADRatio(int other_spdef, int other_def, const std::shared_ptr<Attack> & move_used) {
        if (move_used->get_category() == Category::Special) {
            // (Power x A/D)
            return (double)this->get_base_special_power() / other_spdef;
        }
        else {
            return (double)this->get_base_power() / other_def;
        }
    };

    // Damage calculation for use in altering game state
    int CalcDamage(Pokemon * other, int move_selection, bool print = true) {
        // damage calculations used from formula: https://bulbapedia.bulbagarden.net/wiki/Damage for Generation 1
        // Damage = (((2 x Level x Critical) / 5) + 2) * Power * (A/D) / 50) x STAB x Type x RAND(0.85, 1.0)

        auto move_used = this->attacks_[move_selection];

        // Check for accuracy
        if (move_used->get_accuracy() < ((double)rand() / (RAND_MAX))) {
            if (print) {
                std::cout << "The attack missed!" << std::endl;
            }
            return 0;
        }

        // Use double for internal calculation before rounding down at the end to reduce precision loss
        // Pokemon Gen 1 used various tricks in interal calculations to increase the precision of 8-bit integer representations
        // We approximate this by using doubles and then truncating at the final step
        double total_damage = 0;
        int critical_hit = 1;

        // Check for critical hits with a 6.25% chance
        if (rand() % 16 == 0) {
            if (print) {
                std::cout << "Critical hit!" << std::endl;
            }
            critical_hit = 2;
        }

        // (((2*Level*Critical) / 5) + 2) * Power
        total_damage = (((2 * 100 * critical_hit) / 5) + 2) * move_used->get_power(); // Assume all pokemon are level 100

        // Calculate Special/Physical attacks with opponent's defense stat
        // (Power x A/D)
        total_damage *= CalcADRatio(other->get_spdef(), other->get_def(), move_used);

        // Normalize
        total_damage /= 50;
        total_damage += 2;

        // Calculate STAB bonus
        if (move_used->get_type() == this->get_type()) {
            total_damage *= 1.5;
        }

        // Check for type coverage
        if (is_super_effective(move_used->get_type(), other->get_type())) {
            if (print) {
                std::cout << "It's super effective!" << std::endl;
            }
            total_damage *= 2;
        }
        else if (is_not_very_effective(move_used->get_type(), other->get_type())) {
            if (print) {
                std::cout << "It's not very effective..." << std::endl;
            }
            total_damage /= 2;
        }

        // Randomize damage by 15%
        total_damage *= ((double)rand() / (RAND_MAX)) * 0.15 + 0.85;

        return (int)total_damage;
    };

    // Estimated damage outout, which provides expected outcome when number of turns grow large,
    // based on law of large numbers.
    // This is used by MinimaxDecision for determining the best move to use.
    int CalcExpectedDamage(Pokemon* other, int move_selection) {
        auto move_used = this->attacks_[move_selection];
        // Raw power
        double total_damage = move_used->get_power();
        // apply accuracy modifier
        // get_accuracy returns double representing % change to hit => expected value tends towards power * accuracy
        total_damage *= move_used->get_accuracy();

        // apply crit modifier
        // 6.25% of 2, and 93.75% of 1 => expected value 1.0625 when n grows large
        // (((2 * 100 * 1.0625) / 5) + 2) = 44.5
        total_damage *= 44.5;

        // defense modifier
        total_damage *= CalcADRatio(other->get_spdef(), other->get_def(), move_used);

        // Normalize
        total_damage /= 50;
        total_damage += 2;

        // Calculate STAB bonus
        total_damage *= (move_used->get_type() == this->get_type()) ? 1.5 : 1;

        // Type modifier
        total_damage *= (is_super_effective(move_used->get_type(), other->get_type())) ? 2 : ((is_not_very_effective(move_used->get_type(), other->get_type())) ? 0.5 : 1);

        return (int)total_damage;
    };

    std::pair<int, int> MinimaxDecision(const std::unique_ptr<Pokemon> & opponent, int depth, int whose_turn) {
        // Algorithm inspiration from https://github.com/GeorgeSeif/Tic-Tac-Toe-AI/blob/master/Source.cpp#L201 with no alpha beta pruning

        int best_move = 0; // the index of the best attack to make
        int best_score = 0; // the score of the best attack to make

        if (depth == 0) {
            return std::make_pair(0, 0);
        }

        // If we hit a terminal state, return the best score and move
        if (this->has_fainted()) {
            return std::make_pair(-1000, 0);
        }
        else if (opponent->has_fainted()) {
            return std::make_pair(1000, 0);
        }

        // Maximizing player's turn
        if (whose_turn == 1) { // 1 is AI's turn, 0 is player's turn
            best_score = -1000;
            int score = 0;
            for (int i = 0; i < this->get_attacks().size(); i++) {
                score = this->CalcExpectedDamage(opponent.get(), i);
                if (score > best_score) {
                    best_score = score;
                    best_move = i;
                }
            }

            // Deal damage
            this->TakeDamage(score);
            auto pair = std::make_pair(best_score + MinimaxDecision(opponent, depth - 1, 0).first, best_move);
            this->add_health(score);

            return pair;
        }
        else { // Minimizing opponent's turn
            best_score = 1000;
            int score = 0;
            for (int i = 0; i < opponent->get_attacks().size(); i++) {
                score = opponent->CalcExpectedDamage(this, i);
                if (score < best_score) {
                    best_score = score;
                    best_move = i;
                }
            }
            // Deal damage
            opponent->TakeDamage(score);
            auto pair = std::make_pair(best_score + MinimaxDecision(opponent, depth - 1, 1).first, best_move);
            opponent->add_health(score);

            return pair;
        }
        return std::make_pair(best_score, best_move);
    };
};

#endif // POKEMON_H