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
		else if (move_name == "Flamethrower")
			return std::make_shared<Attack>(move_name, Category::Physical, 90, 1.0, Types::Fire);
		//Darkrai
		else if (move_name == "Quick Attack")
			return std::make_shared<Attack>(move_name, Category::Physical, 40, 1.0, Types::Normal);
		else if (move_name == "Feint Attack")
			return std::make_shared<Attack>(move_name, Category::Physical, 60, 1.0, Types::Dark);
		else if (move_name == "Dream Eater")
			return std::make_shared<Attack>(move_name, Category::Special, 100, 1.0, Types::Dark);
		else if (move_name == "Dark Pulse")
			return std::make_shared<Attack>(move_name, Category::Special, 80, 1.0, Types::Dark);
	    //decidueye
	    	else if (move_name == "Spirit Shackle")
			return std::make_shared<Attack>(move_name, Category::Physical, 80, 1.0, Types::Ghost);
		else if (move_name == "Leafage")
			return std::make_shared<Attack>(move_name, Category::Physical, 40, 1.0, Types::Grass);
		else if (move_name == "Phantom Force")
			return std::make_shared<Attack>(move_name, Category::Physical, 90, 1.0, Types::Ghost);
		else if (move_name == "Razor Leaf") //venasaur can also use
			return std::make_shared<Attack>(move_name, Category::Physical, 55, 0.95, Types::Grass);
        //mimikyu
        	else if (move_name == "Astonish")
			return std::make_shared<Attack>(move_name, Category::Physical, 30, 1.0, Types::Ghost);
		else if (move_name == "Scratch")
			return std::make_shared<Attack>(move_name, Category::Physical, 40, 1.0, Types::Normal);
		else if (move_name == "Shadow Claw")
			return std::make_shared<Attack>(move_name, Category::Physical, 70, 1.0, Types::Ghost);
		else if (move_name == "Play Rough")
			return std::make_shared<Attack>(move_name, Category::Physical, 90, .90, Types::Fairy);
        //snorlax
       		 else if (move_name == "Last Resort")
			return std::make_shared<Attack>(move_name, Category::Physical, 140, 1.0, Types::Normal);
		else if (move_name == "Lick")
			return std::make_shared<Attack>(move_name, Category::Physical, 30, 1.0, Types::Ghost);
		else if (move_name == "Snore")
			return std::make_shared<Attack>(move_name, Category::Special, 50, 1.0, Types::Normal);
		else if (move_name == "Crunch")
			return std::make_shared<Attack>(move_name, Category::Physical, 80, 1.0, Types::Dark);
        //weenasaur
        	else if (move_name == "Petal Blizzard")
			return std::make_shared<Attack>(move_name, Category::Physical, 90, 1.0, Types::Grass);
		else if (move_name == "Petal Dance")
			return std::make_shared<Attack>(move_name, Category::Special, 120, 1.0, Types::Grass);
		else if (move_name == "Double Edge")
			return std::make_shared<Attack>(move_name, Category::Physical, 120, 1.0, Types::Normal);
		else if (move_name == "Solar Beam")
			return std::make_shared<Attack>(move_name, Category::Special, 120, 1.0, Types::Grass);
        //zoroark
        	else if (move_name == "Night Slash")
			return std::make_shared<Attack>(move_name, Category::Physical, 70, 1.0, Types::Dark);
		else if (move_name == "Knock Off")
			return std::make_shared<Attack>(move_name, Category::Physical, 65, 1.0, Types::Dark);
		else if (move_name == "Foul Play")
			return std::make_shared<Attack>(move_name, Category::Physical, 95, 1.0, Types::Dark);
		else if (move_name == "Night Daze")
			return std::make_shared<Attack>(move_name, Category::Special, 85, 0.95, Types::Dark);
		else
			return nullptr;
	}
};

#endif // !ATTACK_FACTORY_H
