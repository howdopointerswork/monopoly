#include <iostream>
#include <string>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;
using std::string;
using std::cout;
using std::cin;
using std::endl;



class Property{


public: 

	string name;

	int val;

	bool owned;

	int ren; //rent

	int mtg; //mortgage


private:

};



class Player{


public: 

	int cash;

	int pos;

	bool jail;

	string name;

	Property owned[28];

	int doubleCount;

	Player();

	void roll();


};




Player::Player(){


	cash = 1500;

	pos = 0;

	jail = 0;

	name = "None";


}



void Player::roll(){


	int d1 = rand() % (6+1-1) + 1;
	int d2 = rand() % (6+1-1) + 1;

	int sum = d1+d2;
	int hold = pos + sum;

	cout << "Rolled a " << sum << ", with a " << d1 << " and a " << d2 << endl;
		
	if(hold > 39){

		int diff = hold - 39;
		pos = diff; 
	}

	pos += sum;



	//handle doubles here;
		



}


Property* makeProperty(Property* p, string n, int v, int r, int m){


	p->name = n;

	p->val = v;

	p->ren = r;

	p->mtg = m;

	return p;


	
}






int main(){

	srand(time(0));

	Property board[40];

	string boardNames[40] = {"Go", "Mediterranean Avenue", "Community Chest", "Baltic Avenue", "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance", "Vermont Avenue", "Connecticut Avenue", "Jail", "St. Charles Place", "Electric Company", "States Avenue", "Virginia Avenue", "Pennsylvania Railroad", "St. James Place", "Community Chest", "Tennesse Avenue", "New York Avenue", "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue", "Illinois Avenue", "B&O Railroad", "Atlantic Avenue", "Vermont Avenue", "Water Works", "Marvin Gardens", "Go To Jail", "Pacific Avenue", "North Carolina Avenue", "Community Chest", "Pennsylvania Avenue", "Short Line Railroad", "Chance", "Park Place", "Luxury Tax", "Boardwalk"};
  
  	int boardCosts[40] = {-1, 60, -1, 60, -1, 200, 100, -1, 100, 120, -1, 140, 150, 140, 160, 200, 180, -1, 180, 200, -1, 220, -1, 220, 240, 200, 260, 260, 150, 280, -1, 300, 300, -1, 320, 200, -1, 350, -1, 400};
  
  	int boardRents[40] = {-1, 2, -1, 4, -1, 50, 6, -1, 6, 8, -1, 10, 4, 10, 12, 50, 14, -1, 14, 16, -1, 18, -1, 18, 20, 50, 22, 22, 4, 24, -1, 26, 26, -1, 28, 50, -1, 35, -1, 50};
  
  	int boardMortgages[40] = {-1, 30, -1, 30, -1, 100, 50, -1, 50, 60, -1, 70, 75, 70, 80, 100, 90, -1, 90, 100, -1, 110, -1, 110, 120, 100, 130, 130, 75, 140, -1, 150, 150, -1, 160, 100, -1, 175, -1, 200};

  	Property* p;

  	p = board;


	for(int i=0; i<40; i++){


		p = makeProperty(p,boardNames[i], boardCosts[i], boardRents[i], boardMortgages[i]);

		p++;

	}




//testing changes


	return 0;
}




