#include <ctime>
#include <iostream>
#include "pokemon/pokemon_factory.hpp"
#include "pokemon/attack_factory.hpp"

int main() {
    std::cout << "Welcome to Pokemon (Fake) Battle Simulator." << std::endl;
    std::cout << "The following Pokemon are available: " << std::endl;
    // Use pokemon factory to get list of options
    std::map<int, std::string>::const_iterator it = PokemonOptions::kOptions.begin();
    while (it != PokemonOptions::kOptions.end()) {
        std::cout << "\tOption " << it->first << ": " << it->second << std::endl;
        ++it;
    }

    // Get user input for pokemon choice
    std::cout << std::endl << "Please select your Pokemon: ";
    int selection;
    while (true) {
        std::cin >> selection;
        if (selection >= 1 && selection <= 8) {
            break;
        }
        std::cout << "Invalid selection. Please try again." << std::endl;
    }

    // Randomly select opponent's pokemon
    srand(time(NULL)); // Seed
    // int opponent_selection = (rand() % 7) + 1;  // note: this is a biased selection; to be replaced post-MVP
    int opponent_selection = 2;  // temporarily hard code Charizard for testing

    // Only the player & opponent pokemon will be instantiated
    auto players_pokemon = PokemonFactory::build(PokemonOptions::kOptions.at(selection));

    // TODO: Randomly allocate 508 EVs, with a max of 252 per stat to add variance to game

    // Hardcoded moves for testing
    players_pokemon->add_attack(AttackFactory::build("Hydro Pump"));
    players_pokemon->add_attack(AttackFactory::build("Mega Kick"));
    players_pokemon->add_attack(AttackFactory::build("Ice Beam"));
    players_pokemon->add_attack(AttackFactory::build("Earthquake"));


    auto opponents_pokemon = PokemonFactory::build(PokemonOptions::kOptions.at(opponent_selection));

    // TODO: Hardcoded moves for testing
    opponents_pokemon->add_attack(AttackFactory::build("Fire Blast"));
    opponents_pokemon->add_attack(AttackFactory::build("Focus Blast"));
    opponents_pokemon->add_attack(AttackFactory::build("Thunder Punch"));
    opponents_pokemon->add_attack(AttackFactory::build("Earthquake"));

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "You have selected " << players_pokemon->get_name() << "!" << std::endl;
    std::cout << "Your opponent has chosen " << opponents_pokemon->get_name() << "!" << std::endl;

    // TODO: Battle Sequence Below
    bool has_not_ended = true;
    bool player_won;
    while (has_not_ended) {
        // Battle Sequence logic goes here
        // WARNING: CURRENTLY FORMS AN INFINITE LOOP!

        // Terminal condition
        if (Pokemon::has_fainted(players_pokemon, opponents_pokemon)) {
            has_not_ended = false;
            player_won = players_pokemon->has_fainted() ? false : true;
        }

        // Print out current game information, HP, etc
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Your Pokemon: " << players_pokemon->get_name() << std::endl;
        std::cout << "HP: " << players_pokemon->get_health() << std::endl << std::endl;
        std::cout << "Opponent's Pokemon: " << opponents_pokemon->get_name() << std::endl;
        std::cout << "HP: " << opponents_pokemon->get_health();

        // TODO: Draw a box around attack selections like actual pokemon game
        // 1 2
        // 3 4
        std::cout << std::endl << "--------------------------------------------" << std::endl;
        std::cout << "\t1. " << players_pokemon->get_attack(0)->get_name() << std::endl;
        std::cout << "\t2. " << players_pokemon->get_attack(1)->get_name() << std::endl;
        std::cout << "\t3. " << players_pokemon->get_attack(2)->get_name() << std::endl;
        std::cout << "\t4. " << players_pokemon->get_attack(3)->get_name() << std::endl;
        std::cout << "Please select an attack: ";
        int move_selection;
        while (true) {
            std::cin >> move_selection;
            if (move_selection >= 1 && move_selection <= 4) {
                break;
            }
            std::cout << "Invalid selection. Please try again." << std::endl;
        }
        std::cout << std::endl << "--------------------------------------------" << std::endl;
        std::cout << players_pokemon->get_name() << " has used " << players_pokemon->get_attack(move_selection - 1)->get_name() << "!" << std::endl;
        int damage_to_deal = players_pokemon->CalcDamage(opponents_pokemon, move_selection - 1);
        std::cout << damage_to_deal << " damage dealt!" << std::endl;
    }

    if (player_won) {
        std::cout << std::endl << "Congratulations!" << std::endl;
        std::cout << "You have won the battle against " << opponents_pokemon->get_name() << "." << std::endl;
    }
    else {
        std::cout << std::endl << "Aww, you lost! Better luck next time!" << std::endl;
    }

    return 0;
}