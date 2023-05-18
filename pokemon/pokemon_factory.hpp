#pragma once
#ifndef POKEMON_FACTORY_H
#define POKEMON_FACTORY_H

#include <map>
#include <string>
#include <memory>
#include "attack.hpp"
#include "attack_factory.hpp"
#include "pokemon.hpp"
#include "types.hpp"

struct PokemonOptions {
	static std::map<int, std::string> create_map() {
		std::map<int, std::string> name_map;
		name_map[1] = "Blastoise";
		name_map[2] = "Charizard";
		name_map[3] = "Darkrai";
		name_map[4] = "Decidueye";
		name_map[5] = "Mimikyu";
		name_map[6] = "Snorlax";
		name_map[7] = "Venusaur";
		name_map[8] = "Zoroark";
		return name_map;
	}

	static const std::map<int, std::string> kOptions;
};

const std::map<int, std::string> PokemonOptions::kOptions = PokemonOptions::create_map();

class MovePoolFactory {
public:
	static std::vector<std::shared_ptr<Attack>> build(std::string pokemon_name, bool is_cheating) {
		std::vector<std::shared_ptr<Attack>> attacks;
		if (pokemon_name == "Blastoise") {
			attacks.push_back(AttackFactory::build("Hydro Pump"));
			attacks.push_back(AttackFactory::build("Mega Kick"));
			attacks.push_back(AttackFactory::build("Ice Beam"));
			attacks.push_back(AttackFactory::build("Earthquake"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Charizard") {
			attacks.push_back(AttackFactory::build("Fire Blast"));
			attacks.push_back(AttackFactory::build("Focus Blast"));
			attacks.push_back(AttackFactory::build("Thunder Punch"));
			attacks.push_back(AttackFactory::build("Earthquake"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Darkrai") {
			attacks.push_back(AttackFactory::build("Quick Attack"));
			attacks.push_back(AttackFactory::build("Feint Attack"));
			attacks.push_back(AttackFactory::build("Dream Eater"));
			attacks.push_back(AttackFactory::build("Dark Pulse"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Decidueye") {
			attacks.push_back(AttackFactory::build("Spirit Shackle"));
			attacks.push_back(AttackFactory::build("Leafage"));
			attacks.push_back(AttackFactory::build("Phantom Force"));
			attacks.push_back(AttackFactory::build("Razor Leaf"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Mimikyu") {
			attacks.push_back(AttackFactory::build("Astonish"));
			attacks.push_back(AttackFactory::build("Scratch"));
			attacks.push_back(AttackFactory::build("Shadow Claw"));
			attacks.push_back(AttackFactory::build("Play Rough"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Snorlax") {
			attacks.push_back(AttackFactory::build("Last Resort"));
			attacks.push_back(AttackFactory::build("Lick"));
			attacks.push_back(AttackFactory::build("Snore"));
			attacks.push_back(AttackFactory::build("Crunch"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Venusaur") {
			attacks.push_back(AttackFactory::build("Petal Blizzard"));
			attacks.push_back(AttackFactory::build("Petal Dance"));
			attacks.push_back(AttackFactory::build("Double Edge"));
			attacks.push_back(AttackFactory::build("Solar Beam"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else if (pokemon_name == "Zoroark") {
			attacks.push_back(AttackFactory::build("Night Slash"));
			attacks.push_back(AttackFactory::build("Knock Off"));
			attacks.push_back(AttackFactory::build("Foul Play"));
			attacks.push_back(AttackFactory::build("Night Daze"));
			if (is_cheating) {
				// TODO: Hard mode has extra moves
			}
		}
		else
			attacks.push_back(AttackFactory::build("Struggle"));
		return attacks;
	}
};

class PokemonFactory {
public:
	static std::unique_ptr<Pokemon> build(std::string pokemon_name, bool is_cheating) {
		// All stats pulled from https://play.pokemonshowdown.com/teambuilder
		std::unique_ptr<Pokemon> pokemon;

		// Instantiate stats
		if (pokemon_name == "Blastoise")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 299, 202, 206, 236, 246, Types::Water);
		else if (pokemon_name == "Charizard")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 297, 204, 254, 192, 254, Types::Fire);
		else if (pokemon_name == "Darkrai")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 281, 216, 306, 216, 301, Types::Dark);
		else if (pokemon_name == "Decidueye")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 291, 250, 236, 186, 236, Types::Grass);
		else if (pokemon_name == "Mimikyu")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 251, 216, 136, 196, 246, Types::Ghost);
		else if (pokemon_name == "Snorlax")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 461, 256, 166, 166, 256, Types::Normal);
		else if (pokemon_name == "Venusaur")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 301, 200, 236, 202, 236, Types::Grass);
		else if (pokemon_name == "Zoroark")
			pokemon = std::make_unique<Pokemon>(pokemon_name, 261, 246, 276, 156, 156, Types::Dark);
		else
			return nullptr;
		
		// Add moves
		pokemon->set_attacks(MovePoolFactory::build(pokemon_name, is_cheating));
		return pokemon;
	}
};

#endif // !POKEMON_FACTORY_H
