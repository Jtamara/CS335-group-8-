#include <ctime>
#include <iostream>
#include <set>
#include "pokemon/pokemon_factory.hpp"
#include "pokemon/attack_factory.hpp"

// This function is used to allocate random Effort Values (EVs) to a player's Pokemon.
void allocate_pokemon_random_evs(std::unique_ptr<Pokemon> & pokemon) {
    int total_evs = 508;
    std::set<int> maxed_stats;
    while (total_evs > 0) {
        // let EV be random from 50-100
        int rand_ev = rand() % 51 + 50; // Generate a random number of EVs between 1 and the remaining total.
        int rand_stat = rand() % 5; // Choose a random stat (out of 5 possible: health, base power, base special power, defense, special defense).

        if (maxed_stats.find(rand_stat) != maxed_stats.end()) {
            // found in set => already maxed => skip this iteration, to increase spread
            maxed_stats.erase(rand_stat);
            continue;
        }
        
        if (rand_ev > total_evs)  // cap total EVs at 508
            rand_ev = total_evs;
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
        maxed_stats.insert(rand_stat);
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

    // Get user input for difficulty level
    std::cout << std::endl << "Available difficulty levels: ";
    std::cout << std::endl << "    1. Junior" << std::endl << "    2. Senior" << std::endl << "    3. Masters" << std::endl;
    std::cout << std::endl << "Please select a difficulty level: ";
    int difficulty;
    while (true) {
        std::cin >> difficulty;
        if (difficulty >= 1 && difficulty <= 3) {
            break;
        }
        std::cout << "Invalid selection. Please try again." << std::endl;
    }
    int minimax_depth = (difficulty == 1) ? 1 : ((difficulty == 2) ? 4 : 6);

    // Randomly select opponent's pokemon
    srand(time(NULL)); // Seed
    int opponent_selection = (rand() % 8) + 1;  // note: this is a biased selection; to be replaced post-MVP
    
    // Only the player & opponent pokemon will be instantiated
    auto players_pokemon = PokemonFactory::build(PokemonOptions::kOptions.at(selection), false);
    auto opponents_pokemon = PokemonFactory::build(PokemonOptions::kOptions.at(opponent_selection), ((difficulty == 3) ? true : false));
    
    // Higher difficulty => player lower ATT/SP ATT, and opponent higher ATT/SP ATT
    if (difficulty > 1) {
        allocate_pokemon_random_evs(players_pokemon);  // random player stats
        if (difficulty == 2) {
            allocate_pokemon_random_evs(opponents_pokemon);  // random opponent stats
        }
        else {
            // Set opponents EVs manually
            opponents_pokemon->add_health(252);
            if (players_pokemon->get_def() > players_pokemon->get_spdef()) {
                opponents_pokemon->add_base_special_power(252);
            }
            else {
                opponents_pokemon->add_base_power(252);
            }
            if (players_pokemon->get_base_power() > players_pokemon->get_base_special_power()) {
                opponents_pokemon->add_def(4);
            }
            else {
                opponents_pokemon->add_spdef(4);
            }
        }
    }
    else {
        allocate_pokemon_random_evs(opponents_pokemon);  // random opponent stats
        // Set players EVs manually
        players_pokemon->add_health(252);
        if (opponents_pokemon->get_def() > opponents_pokemon->get_spdef()) {
            players_pokemon->add_base_special_power(252);
        }
        else {
            players_pokemon->add_base_power(252);
        }
        if (opponents_pokemon->get_base_power() > opponents_pokemon->get_base_special_power()) {
            players_pokemon->add_def(4);
        }
        else {
            players_pokemon->add_spdef(4);
        }
    }

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "You have selected " << players_pokemon->get_name() << "!" << std::endl;
    std::cout << "Your opponent has chosen " << opponents_pokemon->get_name() << "!" << std::endl;
    // TODO: Print stats

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

        // Print Attack Options
        std::cout << std::endl
                  << "--------------------------------------------" << std::endl;
        for (int i = 0; i < players_pokemon->get_attacks().size(); i++)
        {
            std::cout << "\t" << i + 1 << ". " << players_pokemon->get_attack(i)->get_name();

            // new line every 2 elements.
            // 1 2
            // 3 4
            if (i % 2 != 0)
            {
                std::cout << std::endl;
            }
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
        // TODO: Status effects

        // Terminal condition
        if (opponents_pokemon->has_fainted()) {
            has_not_ended = false;
            player_won = true;
            break;
        }

        std::cout << std::endl;

        // Calculate how much damage opponent is dealing to player.
        auto minimax = opponents_pokemon->MinimaxDecision(players_pokemon, minimax_depth, 1); // Use minimax to determine best move to use with a ply of 4
        int opponent_move_selection = minimax.second;

        std::cout << "Opponent's " << opponents_pokemon->get_name() << " has used " << opponents_pokemon->get_attack(opponent_move_selection)->get_name() << "!" << std::endl;
        int damage_to_take = opponents_pokemon->CalcDamage(players_pokemon.get(), opponent_move_selection);
        std::cout << damage_to_take << " damage dealt!" << std::endl;
        players_pokemon->TakeDamage(damage_to_take);
        // TODO: Status effects
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
