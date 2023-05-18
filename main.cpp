#include <ctime>
#include <iostream>
#include "pokemon/pokemon_factory.hpp"
#include "pokemon/attack_factory.hpp"

// This function is used to allocate random Effort Values (EVs) to a player's Pokemon.
void allocate_pokemon_random_evs(std::unique_ptr<Pokemon> & pokemon) {
    int total_evs = 508;
    while (total_evs > 0) {
        int rand_ev = rand() % 200 + 1; // Generate a random number of EVs between 1 and the remaining total.
        int rand_stat = rand() % 5; // Choose a random stat (out of 5 possible: health, base power, base special power, defense, special defense).
        switch (rand_stat) {
            case 0:
                pokemon->add_health(rand_ev);
                break;
            case 1:
                pokemon->add_base_power(rand_ev);
                break;
            case 2:
                pokemon->add_base_special_power(rand_ev);
                break;
            case 3:
                pokemon->add_def(rand_ev);
                break;
            case 4:
                pokemon->add_spdef(rand_ev);
                break;
            default:
                break;
        }
        total_evs -= rand_ev;
    }
}

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
    allocate_pokemon_random_evs(players_pokemon);

    // Hardcoded moves for testing
    players_pokemon->add_attack(AttackFactory::build("Hydro Pump"));
    players_pokemon->add_attack(AttackFactory::build("Mega Kick"));
    players_pokemon->add_attack(AttackFactory::build("Ice Beam"));
    players_pokemon->add_attack(AttackFactory::build("Earthquake"));


    auto opponents_pokemon = PokemonFactory::build(PokemonOptions::kOptions.at(opponent_selection));
    allocate_pokemon_random_evs(opponents_pokemon);

    // TODO: Hardcoded moves for testing
    opponents_pokemon->add_attack(AttackFactory::build("Fire Blast"));
    opponents_pokemon->add_attack(AttackFactory::build("Focus Blast"));
    opponents_pokemon->add_attack(AttackFactory::build("Thunder Punch"));
    opponents_pokemon->add_attack(AttackFactory::build("Earthquake"));

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "You have selected " << players_pokemon->get_name() << "!" << std::endl;
    std::cout << "Your opponent has chosen " << opponents_pokemon->get_name() << "!" << std::endl;

    // Battle Sequence
    bool has_not_ended = true;
    bool player_won;
    while (has_not_ended) {
        // Terminal condition
        if (Pokemon::has_fainted(players_pokemon, opponents_pokemon)) {
            has_not_ended = false;
            player_won = players_pokemon->has_fainted() ? false : true;
            break;
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
        for (int i = 0; i < players_pokemon->get_attacks().size(); i++) {
            std::cout << "\t" << i + 1 << ". " << players_pokemon->get_attack(i)->get_name() << std::endl;
        }
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

        // Calculate how much damage the player is dealing to the opponent
        int damage_to_deal = players_pokemon->CalcDamage(opponents_pokemon.get(), move_selection - 1);
        std::cout << damage_to_deal << " damage dealt!" << std::endl;
        opponents_pokemon->TakeDamage(damage_to_deal);

        // Terminal condition
        if (Pokemon::has_fainted(players_pokemon, opponents_pokemon)) {
            has_not_ended = false;
            player_won = players_pokemon->has_fainted() ? false : true;
            continue;
        }

        std::cout << std::endl;

        // Calculate how much damage opponent is dealing to player.
        auto minimax = opponents_pokemon->MinimaxDecision(players_pokemon, 4, 1); // Use minimax to determine best move to use with a ply of 4
        int opponent_move_selection = minimax.second;

        std::cout << "Opponent's " << opponents_pokemon->get_name() << " has used " << opponents_pokemon->get_attack(opponent_move_selection)->get_name() << "!" << std::endl;
        int damage_to_take = opponents_pokemon->CalcDamage(players_pokemon.get(), opponent_move_selection);
        std::cout << damage_to_take << " damage dealt!" << std::endl;
        players_pokemon->TakeDamage(damage_to_take);
    }

    if (player_won) {
        std::cout << std::endl << "Congratulations!" << std::endl;
        std::cout << "You have won the battle against your Opponent's " << opponents_pokemon->get_name() << "." << std::endl;
    }
    else {
        std::cout << std::endl << "Aww, you lost! Better luck next time!" << std::endl;
    }

    return 0;
}
