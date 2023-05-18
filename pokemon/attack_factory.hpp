#pragma once
#ifndef ATTACK_FACTORY_H
#define ATTACK_FACTORY_H

#include <memory>
#include "attack.hpp"

class AttackFactory {
public:
	static std::shared_ptr<Attack> build(std::string move_name) {
		// Blastoise
		if (move_name == "Hydro Pump")
			return std::make_shared<Attack>(move_name, Category::Special, 110, 0.8, Types::Water);
		else if (move_name == "Mega Kick")
			return std::make_shared<Attack>(move_name, Category::Physical, 120, 0.75, Types::Normal);
		else if (move_name == "Ice Beam")
			return std::make_shared<Attack>(move_name, Category::Special, 90, 1.0, Types::Ice);
		else if (move_name == "Earthquake")  // Also for Charizard
			return std::make_shared<Attack>(move_name, Category::Physical, 100, 1.0, Types::Ground);
		// Charizard
		else if (move_name == "Fire Blast")
			return std::make_shared<Attack>(move_name, Category::Special, 110, 0.85, Types::Fire);
		else if (move_name == "Focus Blast")
			return std::make_shared<Attack>(move_name, Category::Special, 120, 0.7, Types::Fighting);
		else if (move_name == "Thunder Punch")
			return std::make_shared<Attack>(move_name, Category::Physical, 75, 1.0, Types::Electric);
		else
			return nullptr;
	}
};

#endif // !ATTACK_FACTORY_H
