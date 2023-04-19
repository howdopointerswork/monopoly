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

	bool owned = 0;

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

	int doubleCount = 0;

	Player();

	void roll(Property arr[]);

  void addCash(int n);

  void remCash(int n);

  void setCash(int n);

  void buyProperty(Property arr[]);

  void checkJail();

  void checkLT();

  void checkIT();

  void checkRent(Property arr[]); //first check owned array, then check if bool is owned in general. if so, pay

  void checks(Property arr[]);



};




Player::Player(){


	cash = 1500;

	pos = 0;

	jail = 0;

	name = "None";

  for(int i=0; i<28; i++){

    owned[i].name = "None";

    
  }


}




void Player::roll(Property arr[]){


  if(doubleCount == 3){

    jail = true;

    return;
    
  }


	int d1 = rand() % (6+1-1) + 1; 
	int d2 = rand() % (6+1-1) + 1;

	int sum = d1+d2;
	int hold = pos + sum;

	cout << "Rolled a " << sum << ", with a " << d1 << " and a " << d2 << endl;
	
	if(hold > 39){ 

		int diff = hold - 40; 
		pos = diff; 
    cash += 200; //Go
    
	}
  else{

	pos += sum;

  }

  cout << "You landed on: " << arr[pos].name << endl;







 if(d1 == d2){


  doubleCount++;

  roll(arr);


  
}
		



}




void Player::addCash(int n){


  cash += n;
  
}




void Player::remCash(int n){


  cash -= n;
  
}




void Player::setCash(int n){


  cash = n;

  
}




void Player::checkJail(){


  if(pos == 30 || jail == 1){

    cout << "Go to jail!" << endl;

    jail = true;
    
  }

  
}





void Player::checkLT(){


  if(pos == 38){

    cout << "Pay Luxury Tax of $75" << endl;
    cash -= 75;

    
  }



  
}



void Player::checkIT(){


  //add lines for buildings

  int subMtg;
  int subVal;
//  int subBui;
  int sum;
  int i = 0;
  int tp;
 
  if(pos == 4){

    cout << "Pay Income Tax of the lesser of 10% of your worth or $200" << endl;
    
    while(owned[i].name != "None"){



      subMtg += owned[i].mtg;
      subVal += owned[i].val;
 
      //subBui += number of buildings

      
    

    
    }

    sum = subMtg + subVal + cash; //+subBui

    tp = sum/10;


    if(tp < 200){


      cash -= tp;

    
    }
    else{


      cash -= 200;

     
    }

  }
}




void Player::checkRent(Property arr[]){

  bool byYou;
 

  for(int i=0; i<28; i++){


    if(arr[pos].name != owned[i].name){

      byYou = false;
      
    }

    else{

      byYou = true;
      
    }

    
  }

  if(byYou){

    return;
    
  }
  else{


    if(arr[pos].owned){

      cash -= arr[pos].ren;
      
    }
    else{

      return;
       
    }

    
  }
  


  

}






void Player::checks(Property arr[]){


    checkJail();
    checkLT();
    checkIT();
    checkRent(arr);




  
}



Property* makeProperty(Property* p, string n, int v, int r, int m){


	p->name = n;

	p->val = v;

	p->ren = r;

	p->mtg = m;

	return p;


	
}




void Player::buyProperty(Property arr[]){


  int i = 0;
  
  if(arr[pos].owned == 0 && arr[pos].val > 0 && cash >= arr[pos].val){

    while(owned[i].name != "None"){

      i++;


       
    }

    owned[i] = arr[pos];
    cash -= arr[pos].val;
    cout << "You purchased " << owned[i].name << " for " << owned[i].val << ". You now have " << cash << endl;

    
  }
  else{

    cout << "Property could not be purchased. Either it is already owned or you are attempting to purchase a special space such as Chance" << endl;
  }

  
}






int main(){

	srand(time(0));

	Property board[40];

	string boardNames[40] = {"Go", "Mediterranean Avenue", "Community Chest", "Baltic Avenue", "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance", "Vermont Avenue", "Connecticut Avenue", "Jail", "St. Charles Place", "Electric Company", "States Avenue", "Virginia Avenue", "Pennsylvania Railroad", "St. James Place", "Community Chest", "Tennesse Avenue", "New York Avenue", "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue", "Illinois Avenue", "B&O Railroad", "Atlantic Avenue", "Vermont Avenue", "Water Works", "Marvin Gardens", "Go To Jail", "Pacific Avenue", "North Carolina Avenue", "Community Chest", "Pennsylvania Avenue", "Short Line Railroad", "Chance", "Park Place", "Luxury Tax", "Boardwalk"};
  
  int boardCosts[40] = {-1, 60, -1, 60, -1, 200, 100, -1, 100, 120, -1, 140, 150, 140, 160, 200, 180, -1, 180, 200, -1, 220, -1, 220, 240, 200, 260, 260, 150, 280, -1, 300, 300, -1, 320, 200, -1, 350, -1, 400};
  
  	
  int boardRents[40] = {-1, 2, -1, 4, -1, 50, 6, -1, 6, 8, -1, 10, 4, 10, 12, 50, 14, -1, 14, 16, -1, 18, -1, 18, 20, 50, 22, 22, 4, 24, -1, 26, 26, -1, 28, 50, -1, 35, -1, 50};
  
  int boardMortgages[40] = {-1, 30, -1, 30, -1, 100, 50, -1, 50, 60, -1, 70, 75, 70, 80, 100, 90, -1, 90, 100, -1, 110, -1, 110, 120, 100, 130, 130, 75, 140, -1, 150, 150, -1, 160, 100, -1, 175, -1, 200};

  Property* p;
  Property* o;

  Player me;
  me.name = "Dev";

  p = board;
  o = me.owned;


	for(int i=0; i<40; i++){


		p = makeProperty(p,boardNames[i], boardCosts[i], boardRents[i], boardMortgages[i]);

		p++;

	}

  p = board;

  

   me.roll(p);
   me.buyProperty(p); //refactor into roll so that property may be purchased upon rolling doubles
  cout << me.owned[0].name << endl;


  me.checks(p);

	return 0;
  
}




