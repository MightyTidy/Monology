#ifndef UNTITLED14_JACKO_H
#define UNTITLED14_JACKO_H

#endif //UNTITLED14_JACKO_H

#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std;
using namespace this_thread;
using namespace chrono;

//CLASSES
//----------------------------------------------------------------------------------------------------------------------
class location{
public:
    location();
    string Name;
    bool isProperty = true; // unless specified otherwise
    bool isUtility = false; // unless specified otherwise - utilities and railroads calculate rent differently
    bool isRailroad = false; // unless specified otherwise - they also cannot have houses/hotels
    bool isMonopoly = false; // is true if all tiles of the same color are owned by the same player
    string Color = "Blank";
    int Price;
    int Rent; //rent 0 house
    int Rent1H; // rent 1 house
    int Rent2H;
    int Rent3H;
    int Rent4H;
    int RentH; //rent hotel
    int MortgageVal;
    int HouseP;
    bool Owned = false;
    int OwnerID = 4; // BANK 'OWNS' ALL PROPERTIES AT THE START OF GAME
    int numHouse = 0;
    bool Hotel = false;
    bool isMortgaged = false;
    bool inTrade = false;
    int NumSetOwned; // NUM OF SAME SET PROPS OWNED
    float PlayerRadius; // AVERAGE DISTANCE OF PLAYERS (NOT INCLUDING OWNER) FROM PROPERTY


};

class player: public location{
public:
    player();
    int PID;
    int Bal = 1500;
    int location = 0;
    int DiceRoll = 0;
    bool TiedRoll = true; // bool to help determine first turn - if two players have the same dice roll before game this will be set to true
    string PlayerName;
    bool InJail = false; // bool to see if player is in jail
    int JailTurns = 0; // number of turns in jail
    int RemainingPlayers = 4; // used to determine when the game ends./// maybe the bank owns this?
    bool GOOJF = false; // GET OUT OF JAIL FREE CARD
    int DoublesCount = 0; // TO CHECK IF PLAYER HAS ROLLED 3 DOUBLES IN A ROW
    bool Bankrupt = false;
    bool Bot = false;

    void RollDice (player PlayerArray[], class location Board[], int Player, bool FirstRoll);
    void MovePlayer (player PlayerArray[], class location Board[], int Player, bool Doubles, bool FirstRoll);
    void PayRent (player PlayerArray[], class location Board[], int Player);
    void PayRentUtility (player PlayerArray[], class location Board[], int Player);
    void BuyProperty (player PlayerArray[], class location Board[], int Player);
    void TurnInJail (player PlayerArray[], class location Board[], int Player);
    void PassedGO (player PlayerArray[], class location Board[], int Player);
    void CheckMonopoly (class location Board[], int Prop); // CHECKS FOR A MONOPOLY AFTER A PLAYER GAINS A CARD
    void UtilRRMonopoly (class location Board[], int Prop, int Player); //  CHECKS FOR UTILITY OR RAILROAD MONOPOLY
    void PropDetails (class location Board[], int Prop); // DISPLAYS PROPERTY DETAILS
    void MyProperties (player PlayerArray[], class location Board[], int Player); // DISPLAYS OWNED PROPERTIES
    void UpdateProp (player PlayerArray[], class location Board[], int Player);
    void BuySellHouseHotel (player PlayerArray[], class location Board[], int Player, int Prop, bool Buying);
    void MortgageProp (player PlayerArray[], class location Board[], int Player, int Prop);
    void UtilRRDetails (class location Board[], int Prop);
    void Chance (player PlayerArray[], class location Board[], int Player, bool Doubles);
    void CommunityChest(player PlayerArray[], class location Board[], int Player);
    bool CheckBankrupt (player PlayerArray[], class location Board[], int Player, int Amt, int Payee);
    void DisplayBoard (player PlayerArray[], class location Board[], int Prop);
    void Trade(player PlayerArray[], class location Board[], int Player);
    bool PossibleMonopoly (player PlayerArray[], class location Board[], int Player, int Prop, int ManyProps); // CHECKS IF A PLAYER RECEIVING A PROPERTY WILL RESULT IN A MONOPOLY
    void BOTTrade (player PlayerArray[], class location Board[], int Player, int Prop);
    void BOTBuyHouse (player PlayerArray[], class location Board[], int Player, int Prop, bool Set);
    void BOTMortgage (player PlayerArray[], class location Board[], int Player, int Prop, bool Mortgage);
    int BOTChooseHouseProp (player PlayerArray[], class location Board[], int Player);
    bool BOTBankrupt (player PlayerArray[], class location Board[], int Player, int Amt, int Payee);
    void BOTSellHouse (player PlayerArray[], class location Board[], int Player, int Prop, bool Set);


};
