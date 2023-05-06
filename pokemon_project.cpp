//Group 8 
#include <iostream>
#include <cstdlib> //necessary for random numbers
#include <ctime> 
using namespace std;

int main()
{
	int player_choice;
	int computer_choice;
	int player_attack_power = 1;
	int computer_attack_power = 1;
	int player_hp = 30;
	int computer_hp = 30;

	//setting the stage
	cout << "Welcome to fake pokemon! (press enter to continue)" << endl;
	cin >> ;
	cout << "Your next target is to attack the pc with... uh..." << endl;
	cout << "(press enter to continue)" << endl;
	cin >> ;
	cout << "You shall be using your made up \"pokemon\"" << endl;
	cout << "(press enter to continue)" << endl;
	cin >>;
	cout << "These are the moves your pokemon has:" << endl;
	cout << "1. Attack (this moves does "<< player_attack_power << " damage )" << endl;
	cout << "2. Enrage (it boosts the next attack x2 but you skip your turn; enrage stacks)" << endl;
	cout << "3. Block (it blocks all damage for the current turn)" << endl;
	cout << "Enter a number between 1-3 for your pokemon choice" << endl;
	cin >> player_choice;
	while (player_choice != 1 || player_choice != 2 || player_choice != 3 ){
		cout << "pls enter a number between 1-3..." << endl;
		cin >> player_choice;
	}
	


}