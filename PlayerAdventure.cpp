#include <iostream>
#include <memory>
#include <cstdlib>
#include<time.h>
using namespace std;

class PlayerInterface{
  public:

  virtual void BaseDamage()=0;
  virtual void AdditionalDamage()=0;
  virtual void Heal()=0;
};

int RandomValue(int min, int max){

  srand(time(0));
  int range = max - min +1;
  int randomNum = (rand() % range) +min;
  return randomNum;
}

class BasePlayer: public PlayerInterface{
  protected:
  int currentHealth, maxHealth, damage, minAddDmg, maxAddDmg, minHeal, maxHeal;
  bool playerAlive;

  public:
  void SetHealth(){
    currentHealth = maxHealth;
    playerAlive = true;
  }

  void Damage(int dmg){
    currentHealth -= damage;
    if(currentHealth <= 0){
      cout << GetPlayerType() << "died" << endl;
      playerAlive = false;
    }
    else{
      cout << GetPlayerType() << "was damaged by: "<< dmg << endl;
    }
  }

  void BaseDamage(){
    Damage(damage);
    AdditionalDamage();
  }

  void AdditionalDamage(){
    int randomDmg = RandomValue(minAddDmg, maxAddDmg);
    Damage(randomDmg);
  }

  void Heal(){
    int heal = RandomValue(minHeal, maxHeal);
    currentHealth += heal;

    if(currentHealth > 0){
      currentHealth = maxHealth;
      cout << GetPlayerType() << "is at Full Health"<< endl;
    }
    else{
      cout << GetPlayerType() << " is Healed by: "<< heal<< endl;
    }
  }

  virtual string GetPlayerType(){
    return "Base Player: ";
  }

  bool PlayerAlive(){
    return playerAlive;
  }
  public:
  void DisplayInfo(){
    if(currentHealth > 0){
    cout << GetPlayerType() << "Current Health is: " << currentHealth << endl;
    }
  }
};

class StrongPlayer : public BasePlayer{
  public:
  StrongPlayer(){
    maxHealth = 150;
    damage = 20;
    minAddDmg = 5;
    maxAddDmg = 10;
    minHeal = 10;
    maxHeal = 15;
    SetHealth();
  }
  string GetPlayerType(){
    return "Strong Player: ";
  }
};

class TacticalPlayer : public BasePlayer{
  public:
  TacticalPlayer(){
    maxHealth = 100;
    damage = 20;
    minAddDmg = 10;
    maxAddDmg = 20;
    minHeal = 10;
    maxHeal = 15;
    SetHealth();
  }
  string GetPlayerType(){
    return "Tactical Player ";
  }
};

class HealerPlayer : public BasePlayer{
  public:
  HealerPlayer(){
    maxHealth = 150;
    damage = 20;
    minAddDmg = 2;
    maxAddDmg = 8;
    minHeal = 15;
    maxHeal = 20;
    SetHealth();
  }
  string GetPlayerType(){
    return "HealerPlayer ";
  }
};

BasePlayer* Selectplayer(){
  cout << "Select a Player : 1, 2, 3: "<< endl;
  BasePlayer* p;
  int num;
  cin >> num;
  switch (num) {
  case 2:
    p = new HealerPlayer();
    break;
  case 3:
    p = new TacticalPlayer();
    break;
  default:
    p = new StrongPlayer();
    break;
}
return p;
}

void PlayerChance(BasePlayer* self, BasePlayer* opponent){
  char input;
  cout << "Enter 'd' for damage or 'h' for Heal: ";
  cin>> input;
  switch (input) {
  case 'd':
    opponent->BaseDamage();
    opponent->DisplayInfo();
    break;
  case 'h':
    self->Heal();
    self->DisplayInfo();
    break;
  default:
    cout << "Invalid input."<<endl;
    break;
}
}

int main() {
  cout << "\n Battle Adventure Game: \n \n";
  cout << "Player 1: "<<endl;
  BasePlayer* player1 = Selectplayer();
  player1->DisplayInfo();

  cout << "\nPlayer 2: "<<endl;
  BasePlayer* player2 = Selectplayer();
  player2->DisplayInfo();

  int playerTurn = 1;
  bool gameContinue = true;

  do{
    if(playerTurn == 1){
      cout << "\n" << player1->GetPlayerType() << "Player 1 its your turn"<< endl;
      PlayerChance(player1, player2);
    }
    else{
      cout << "\n" << player2->GetPlayerType() << "Player 2 its your turn"<< endl;
      PlayerChance(player2, player1);
    }

    playerTurn = (playerTurn == 1) ? 2:1;

    if(player1->PlayerAlive() && player2->PlayerAlive()){
      gameContinue = true;
    }
    else if(!player2->PlayerAlive()){
      cout << player1->GetPlayerType() << "Player 1 Wins !!"<< endl;
      gameContinue = false;
    }
    else if(!player1->PlayerAlive()){
      cout << player2->GetPlayerType() << "Player 2 Wins !!"<< endl;
      gameContinue = false;
    }
    
  }
  while(gameContinue);

  delete player1;
  delete player2;
}