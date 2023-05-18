#pragma once
#ifndef POKEMON_FACTORY_H
#define POKEMON_FACTORY_H

#include <map>
#include <string>
#include <memory>
#include "attack.hpp"
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
	// TODO: Return vector of 4 moves, based on input pokemon name
};

class PokemonFactory {
public:
	static std::unique_ptr<Pokemon> build(std::string pokemon_name) {
		// All stats pulled from https://play.pokemonshowdown.com/teambuilder
		if (pokemon_name == "Blastoise")
			return std::make_unique<Pokemon>(pokemon_name, 299, 202, 206, 236, 246, Types::Water);
		else if (pokemon_name == "Charizard")
			return std::make_unique<Pokemon>(pokemon_name, 297, 204, 254, 192, 254, Types::Fire);
		else if (pokemon_name == "Darkrai")
			return std::make_unique<Pokemon>(pokemon_name, 281, 216, 306, 216, 301, Types::Dark);
		else if (pokemon_name == "Decidueye")
			return std::make_unique<Pokemon>(pokemon_name, 291, 250, 236, 186, 236, Types::Grass);
		else if (pokemon_name == "Mimikyu")
			return std::make_unique<Pokemon>(pokemon_name, 251, 216, 136, 196, 246, Types::Ghost);
		else if (pokemon_name == "Snorlax")
			return std::make_unique<Pokemon>(pokemon_name, 461, 256, 166, 166, 256, Types::Normal);
		else if (pokemon_name == "Venusaur")
			return std::make_unique<Pokemon>(pokemon_name, 301, 200, 236, 202, 236, Types::Grass);
		else if (pokemon_name == "Zoroark")
			return std::make_unique<Pokemon>(pokemon_name, 261, 246, 276, 156, 156, Types::Dark);
		else
			return nullptr;
	}
};

#endif // !POKEMON_FACTORY_H
