#include <iostream>
#include <string>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stack>

using namespace std; //fix
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::stack;



class Property{


public: 

	string name;

  string colour;

	int val;

	bool owned;

	int ren; //rent

	int mtg; //mortgage

  int hos; //houses

  int hot; //hotels

  bool isMortgaged;

 	Property();


private:

};





class Card{


public:

  int id;

  string desc;





};






class Player{


public: 

	int cash; //money

	int pos; //position

	bool jail; //checks for player being in jail

  bool inGame; //checks if player is destitute

  bool gjf; //get out of jail free

	string name; //name of player

	Property owned[28]; //properties owned

	int doubleCount; //how many doubles you have rolled in a row

  int jailCount; 

  int houses;

  int hotels;

  int ut = 4; //for utilities

  int rr = 1; //for railroads

	Player(); //constructor

	void roll(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc); //roll function - rolls 2 dice via randomizing ints and checks for doubles

  void addCash(int n); //adds cash, to be used soon

  void remCash(int n); //removes cash, to be used soon

  void setCash(int n); //sets the amount of cash you have

  void buyProperty(Property arr[]); //function to buy property

//check functions

  void checkJail(); 

  void checkLT();

  void checkIT();

  void checkRent(Property arr[], Player arr2[], int size); //first check owned array, then check if bool is owned in general. If so, pay

  void checkLose();

  void checkChanceCC(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc);

  void checkRentDbl();

  void mortgage(Property arr[]);

  void checks(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc);

  void trade(Player t);

  int easyRoll();



	};



 Property::Property(){



  owned  = 0; //defaulted as vacant
  name = "None"; //used for exclusions



}




Player::Player(){


	cash = 1500; //starting cash

	pos = 0; //begin at Go

	jail = 0; //default not in jail

  doubleCount = 0; //no doubles

	name = "None"; //default name

  for(int i=0; i<28; i++){ 

    owned[i].name = "None";
    //likely this loop will be removed - redundant
    
  }


}




void Player::roll(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc){

  int n;


  if(doubleCount == 3){

    jail = true;
    //call jail function here

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

  checks(arr, arr2, size, toCheck, ch, cc);

  cout << "You landed on: " << arr[pos].name << endl;







 if(d1 == d2){


  doubleCount++;

  cout << "Buy or keep rolling?" << endl << "1. Buy" << endl << "2. Roll" << endl;

  cin >> n;

  cout << endl;

  if(n%2 == 0){
  
    roll(arr, arr2, size, toCheck, ch, cc);

  }
  else{

    buyProperty(arr);
    roll(arr, arr2, size, toCheck, ch, cc);
    
  }


  
}
		



}



int Player::easyRoll(){

  int d1 = rand() % (6+1-1) + 1; 
  int d2 = rand() % (6+1-1) + 1;

  int sum = d1+d2;

  cout << "Rolled a: " << d1 << " and a: " << d2 << " for a sum of: " << sum << endl;


  return sum;

  
}




void Player::trade(Player t){


  int givP;
  int givC;
  int reqP;
  int reqC;
  int i = 0;
  int opt;
  

  cout << "To begin the trade, select what you are going to offer. First, enter the amount of properties you wish to trade, and then enter the amount of cash that you wish to trade. Then, do the same with what you wish to receive in return." << endl << endl << endl;


  cout << "Properties to give: ";

  cin >> givP;

  cout << endl;
  
  cout << "Cash to give: ";

  cin >> givC;

  cout << endl;


//do requests here

  
  cout << "Properties to get: ";

  cin >> reqP;

  cout << endl;
  
  cout << "Cash to get: ";

  cin >> reqC;

  cout << endl;



  cout << "Now choose which Properties to give by inputting a legal number from the list below: " << endl;


  //while loop with the properties listed
  //a dynamic array of size givP to hold the selected properties
  //for loop of givP to enter numbers for properties to select
  //In for loop, put each int, after assignment, into array
  //another while loop to list tradee properties
  //a dynamic array of size givC to hold the requested properties
  //for loop of givC to enter numbers for properties to select
  //In for loop, put each int, after assignment, into array

  //do cash: += to give, += to get 

  Property temp;


  while(owned[i].name != "None"){


    cout << i << ". " << owned[i].name << endl;

    i++;

    
    

    
  }
  
  
  i = 0;

 

  for(int j = 0; j < givP; j++){


      cin >> opt;
      cout << endl;

      temp = owned[opt];
      

      while(t.owned[i].name != "None"){


        i++;

        
      }

      t.owned[i] = temp;
      i = 0;

      for(int k = 0; k < 28; k++){
      //make these while loops

        owned[k] = owned[k+1];

        
      }
      
         

    
  }


 cout << "Now choose which Properties to receive by inputting a legal number from the list below: " << endl;


  while(t.owned[i].name != "None"){


    cout << i << ". " << t.owned[i].name << endl;

    i++;


    
  }


  i = 0;



  for(int j = 0; j < reqP; j++){


      cin >> opt;
      cout << endl;

      temp = t.owned[opt];
      

      while(owned[i].name != "None"){


        i++;

        
      }

      owned[i] = temp;
      i = 0;

      for(int k = 0; k < 28; k++){


        t.owned[k] = t.owned[k+1];

        
      }
      
         

    
  }


  
  
  
  addCash(reqC);
  t.addCash(givC);


  

  
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

  if(jail){

    return; //add jail rules here
    
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

      
      i++;

    
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




void Player::checkRent(Property arr[], Player arr2[], int size){

  bool byYou;
  Player p; // convert to pointer same as others
  
  //give rent to player that owns it

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


    if(arr[pos].owned && arr[pos].isMortgaged == 0){

      for(int i=0; i<size; i++){

        for(int j=0; j<28; j++){


          if(arr2[i].owned[j].name == arr[pos].name){

            p = arr2[i];
          }
        }
        
      }

      

      
  
      if(arr[pos].colour == "Utility"){

        int hold = easyRoll()*4;

        remCash(hold);
        p.addCash(hold);
        
      }
      else if(arr[pos].colour == "Railroad"){

        remCash(50*rr);
        p.addCash(50*rr);
        
      }
      else{

      remCash(arr[pos].ren);
      p.addCash(arr[pos].ren);

      }
        

      
      
    }
    else{

      return;
       
    }

    
  }
  


  

}





void Player::checkLose(){


  if(cash <= 0){

    inGame = 0;

    
  }

  if(inGame == 0){

    return;
    //handle losses here

    
  }


  
}



void Player::checkRentDbl(){



  int clrCount;

  int j = 0;
  int k = 0;

  int arr[4] = {0, 0, 0, 0};


//purple: 2  blue: 2  utilities: 2
//railroads: 4  
//everything else is 3


  string clr[11] = {"Purple", "Railroad", "LightBlue", "Pink", "Utility", "Orange", "Red", "Yellow", "Green", "Railroad", "Blue"}; 

  


 for(int i=0; i<11; i++){

    while(owned[j].name != "None"){

      if(owned[j].colour == clr[i]){

        clrCount++;
        arr[k] = j;
        k++;
        
        
      }//if

      j++;
      
    }//while

   
    switch(clrCount){

      case 2:

        if(i == 0 || i == 10){

            for(int l=0; l<2; l++){

              owned[arr[l]].ren *= 2;
              
            } 
          
        }
        else if(i == 4){

          //utilities
          ut = 10;
          
        }
        else if(i == 1){

          rr = 2;
        }

        break;

     
      case 3:

        if(i == 1){

          rr = 3;
          
        }
        else{

          for(int l=0; l<3; l++){

            owned[arr[l]].ren *= 2;
          }
          
        }
        break;

      
      
      case 4:

        rr = 4;
        break;
        

      
    }
   



   j = 0;
   k = 0;
  
   
   
 }//for


  
}




void Player::checkChanceCC(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc){


  Card temp;
   
  cout << toCheck.desc << endl;

  
  
  //make this not garbage

  if(toCheck.id < 16){

    ch.pop();
    ch.push(toCheck);

    
  }
  else{

    cc.pop();
    cc.push(toCheck);
    
  }

  
  switch(toCheck.id){

    case 1:
      pos = 0;
      addCash(200);
      break;

    case 2:
      addCash(45);
      break;

    case 3:
      addCash(100);
      break;

    case 4:
      remCash(100);
      break;

    case 5:
      for(int i=0; i<size; i++){

        arr2[i].remCash(50);
        addCash(50);
        
      }
      break;

    case 6: 
      addCash(20);
      break;

    case 7:
      addCash(20);
      break;

    case 8:
      remCash(50);
      break;

    case 9:
      jail = 1; //will handle jail later
      break;

    case 10:
      addCash(200);
      break;

    case 11:
      addCash(100);
      break;

    case 12:
      addCash(100);
      break;

    case 13:
      gjf = 1;
      break;

    case 14:
      remCash(150);
      break;

    case 15:
      addCash(10);
      break;

    case 16:
      addCash(45*houses);
      addCash(115*hotels);
      break;
      

    case 17:
      if(pos >= 5){

        addCash(200);
        
      }
      pos = 5;
      break;

    case 18:
      cout << "WIP" << endl; //12, 28
      break;

    case 19:
      pos -= 3;
      break;

    case 20:
      pos = 0;
      addCash(200);
      break;

    case 21:
      addCash(50);
      break;

    case 22:
      
      if(pos >= 24){

        addCash(200);
        
      }
      pos = 24;
      break;

    case 23:
      remCash(25*houses);
      remCash(100*hotels);
      break;

    case 24:
      gjf = 1;
      break;

    case 25:
      remCash(15);
      break;

    case 26:
      if(pos == 39){

        addCash(200);
        
      }
      pos = 39;
      break;

    case 27:
      cout << "WIP" << endl; //must do rents first
      break;

    case 28:
      jail = 1;
      break;

    case 29:
      for(int i=0; i<size; i++){

        arr2[i].addCash(50);
        remCash(50);
         
      }
      break;

    case 30:
      if(pos >= 11){

        addCash(200);
        
      }
      pos = 11;
      break;

    case 31:
      addCash(150);
      break;

    case 32:
      cout << "WIP" << endl; //rents first
      break;
      
    
  }
  

  //check id here with actual conditions



  
}




void Player::mortgage(Property arr[]){

  int i = 0;

  int j = 0;

  int n;

  int count = 0;

  if(owned[0].name == "None"){

    cout << "No properties to mortgage" << endl;
    return;

  }
  else{

    while(owned[i].name != "None"){

      cout << i << ". " << owned[i].name << endl;
     
      i++;
      
    }

    cout << "What would you like to mortgage or unmortgage?" << endl;
    cin >> n;

    if(n > i-1 || n<0){

      cout << "Invalid input" << endl;
      return;
    }
    else{

      if(owned[n].isMortgaged == 0){

        owned[n].isMortgaged = 1;
        cash += (owned[n].mtg)/2;


        while(arr[j].name != owned[n].name){


          j++;

        }

        arr[j].isMortgaged = 1;

      }  
      else{

        owned[n].isMortgaged = 0;
        cash -= owned[n].mtg;
        //and 10% on top

        
        while(arr[j].name !=         owned[n].name){


          j++;

        }

        arr[j].isMortgaged = 0;

        
        
      }

      
      
    }

    
    
  }



  
}





void Player::checks(Property arr[], Player arr2[], int size, Card toCheck, stack<Card> ch, stack<Card> cc){


    checkJail();
    checkLT();
    checkIT();
    checkRent(arr, arr2, size);
    checkLose();

    if(pos == 7 || pos == 22 || pos == 36){

       checkChanceCC(arr, arr2, size, ch.top(), ch, cc);

      
    }
    else if(pos == 2 || pos == 17 || pos == 24){


             checkChanceCC(arr, arr2, size, cc.top(), ch, cc);


      
    }

  
}





void Player::buyProperty(Property arr[]){


  int i = 0;
  
  if(arr[pos].owned == 0 && arr[pos].val > 0 && cash >= arr[pos].val){

    while(owned[i].name != "None"){

      i++;


       
    }

    arr[pos].owned = 1;
    owned[i] = arr[pos];
    cash -= arr[pos].val;
    cout << "You purchased " << owned[i].name << " for " << owned[i].val << ". You now have " << cash << endl;

    
  }
  else{

    cout << "Property could not be purchased. Either it is already owned or you are attempting to purchase a special space such as Chance" << endl;
  }

  
}



/*void menu(Player arr[], int n){





}*/



Property* makeProperty(Property* p, string n, int v, int r, int m, string c){


	p->name = n;

	p->val = v;

	p->ren = r;

	p->mtg = m;

  p->colour = c;

	return p;


	
}











int main(){

  //organize - variables first, then arrays, then code

	srand(time(0));

	Property board[40];

  int pplPlaying;

  int opt;

  string name;

  bool endGame;

  int n = 0;

  Card empty;
  empty.id = 0;

  //put in main up to after else
  stack<Card> chance;
  stack<Card> chest;


  Card decks[32];

  //put in txt file
  string descs[32] = {"Advance To Go (Collect $200)", "From Sale of Stock You Get $45", "You Inherit $100", "Pay Hospital $100", "Grand Opera Opening - Collect $50 From Every Player", "Income Tax Refund - Collect $20", "Receive For Services $20", "Doctor's Fee - Pay $50", "Go To Jail - Go Directly To Jail - Do Not Pass Go - Do Not Collect $200", "Bank Error In Your Favor - Collect $200", "Xmas Fund Matures - Collect $100", "Life Insurance Matures - $100", "Get Out Of Jail Free - This Card May Be Kept Until Needed Or Sold", "Pay School Tax Of $150", "You Have Won Second Prize In A Beauty Contest - Collect $10", "You Are Assessed For Street Repairs - $40 Per House, $115 Per Hotel", "Take A Ride On The Reading - If You Pass Go, Collect $200", "Advance Token To Nearest Utility - If Unowned, You May Buy It From The Bank - If Owned, Throw Dice And Pay Owner A Total Ten Times The Amount Thrown", "Go Back 3 Spaces", "Advance To Go (Collect $200)", "Bank Pays You Dividend Of $50", "Advance To Illinois Ave.", "Make General Repairs On All Your Property - For Each House Pay $25 - For Each Hotel Pay $100", "This Card May Be Kept Until Needed Or Sold - Get Out Of Jail Free", "Pay Poor Tax Of $15", "Take A Walk On The Boardwalk - Advance Token To Boardwalk", "Advance Token To The Nearest Railroad And Pay Owner Twice The Rental To Which He Is Entitled. If Railroad Is Unowned, You May Buy It From The Bank", "Go Directly To Jail - Do Not Pass Go - Do Not Collect $200", "You Have Been Elected Chairman Of The Board - Pay Each Player $50", "Advance To St.Charles Place - If You Pass Go, Collect $200", "Your Building And Loan Matures - Collect $150", "Advance Token To The Nearest Railroad And Pay Owner Twice The Rental To Which He Is Entitled. If Railroad Is Unowned, You May Buy It From The Bank"};

  for(int i=0; i<32; i++){



    decks[i].desc = descs[i];
    decks[i].id = i+1;


    if(i<16){

      chest.push(decks[i]);


    }
    else{

      chance.push(decks[i]);
    
    }

  //randomize then push
  //just push for now however

  }
  //put in txt file
	string boardNames[40] = {"Go", "Mediterranean Avenue", "Community Chest", "Baltic Avenue", "Income Tax", "Reading Railroad", "Oriental Avenue", "Chance", "Vermont Avenue", "Connecticut Avenue", "Jail", "St. Charles Place", "Electric Company", "States Avenue", "Virginia Avenue", "Pennsylvania Railroad", "St. James Place", "Community Chest", "Tennesse Avenue", "New York Avenue", "Free Parking", "Kentucky Avenue", "Chance", "Indiana Avenue", "Illinois Avenue", "B&O Railroad", "Atlantic Avenue", "Vermont Avenue", "Water Works", "Marvin Gardens", "Go To Jail", "Pacific Avenue", "North Carolina Avenue", "Community Chest", "Pennsylvania Avenue", "Short Line Railroad", "Chance", "Park Place", "Luxury Tax", "Boardwalk"};
  
  int boardCosts[40] = {-1, 60, -1, 60, -1, 200, 100, -1, 100, 120, -1, 140, 150, 140, 160, 200, 180, -1, 180, 200, -1, 220, -1, 220, 240, 200, 260, 260, 150, 280, -1, 300, 300, -1, 320, 200, -1, 350, -1, 400};
  	
  int boardRents[40] = {-1, 2, -1, 4, -1, 50, 6, -1, 6, 8, -1, 10, 4, 10, 12, 50, 14, -1, 14, 16, -1, 18, -1, 18, 20, 50, 22, 22, 4, 24, -1, 26, 26, -1, 28, 50, -1, 35, -1, 50};
  
  int boardMortgages[40] = {-1, 30, -1, 30, -1, 100, 50, -1, 50, 60, -1, 70, 75, 70, 80, 100, 90, -1, 90, 100, -1, 110, -1, 110, 120, 100, 130, 130, 75, 140, -1, 150, 150, -1, 160, 100, -1, 175, -1, 200};

  string boardColours[40] = {"None", "Purple", "None", "Purple", "None", "Railroad", "LightBlue", "None", "LightBlue", "LightBlue", "None", "Pink", "Utility", "Pink", "Pink", "Railroad", "Orange", "None", "Orange", "Orange", "None", "Red", "None", "Red", "Red", "Railroad", "Yellow", "Yellow", "Utility", "Yellow", "None", "Green", "Green", "None", "Green", "Railroad", "None", "Blue", "None", "Blue"};

  //string colours[40] = {}

  Property* p;
  Property* o;

  Player me;
  me.name = "Dev";

  p = board;
  o = me.owned;


	for(int i=0; i<40; i++){


		p = makeProperty(p,boardNames[i], boardCosts[i], boardRents[i], boardMortgages[i], boardColours[i]); //add colours

		p++;

	}

  p = board;

  

  /* me.roll(p);
   me.buyProperty(p); //refactor into roll so that property may be purchased upon rolling doubles
  cout << me.owned[0].name << endl;


  me.checks(p);*/


  cout << "Welcome to Monopoly! To begin, enter how many people will be playing" << endl;

  cin >> pplPlaying; //must be valid range (1-6 maybe?)

  cout << endl;

  Player* game = new Player[pplPlaying];

  cout << "Good. And what are their names? Starting with P1, and ending with Pn" << endl;


  for(int i=0; i<pplPlaying; i++){


    cin >> name;

    cout << endl;

    game[i].name = name;

  }


  cout << "Now that that is done, we may begin the game" << endl;


  


  while( endGame == 0){


    if(n == pplPlaying){


      n = 0;

    }


    cout << "It is " << game[n].name << "'s turn" << endl;


    cout << "1. Roll" << endl;

    cout << "2. Buy" << endl;

    cout << "3. End turn" << endl;


    cin >> opt;

    cout << endl;

    if(opt == 1){

      if(game[n].pos == 7 || game[n].pos == 22 || game[n].pos == 36){
        game[n].roll(p, game, pplPlaying, chance.top(), chance, chest);
      n++;

      }
      else if(game[n].pos == 2 || game[n].pos == 17 || game[n].pos == 24){

        game[n].roll(p, game, pplPlaying, chest.top(), chance, chest);
      n++;
        
      }
      else{

        game[n].roll(p, game, pplPlaying, empty, chance, chest);
      n++;
        
      }


    }
    else if(opt == 2){


      game[n].buyProperty(p);
      n++;

    }

    else if(opt == 3){


      n++;


    }

    else{


      cout << "Invalid input" << endl;


    }




  }








	return 0;
  
}




