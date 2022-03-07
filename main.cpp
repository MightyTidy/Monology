#include <iostream>
#include <random>
#include <stdlib.h>
#include <time.h>

using namespace std;
//my comment
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

};

class player: public location{
public:
    player();
    int PID;
    int Bal = 1500;
    int location = 0;
    int DiceRoll = 0;
    bool TiedRoll = false; // bool to help determine first turn - if two players have the same dice roll before game this will be set to true
    string PlayerName;
    bool InJail = false; // bool to see if player is in jail
    int JailTurns = 0; // number of turns in jail
    int RemainingPlayers = 4; // used to determine when the game ends./// maybe the bank owns this?
    bool GOOJF = false; // GET OUT OF JAIL FREE CARD
    int DoublesCount = 0; // TO CHECK IF PLAYER HAS ROLLED 3 DOUBLES IN A ROW
    bool Bankrupt = false;

    //  3/3
    void RollDice (player PlayerArray[], class location Board[], int Player, bool FirstRoll);
    void MovePlayer (player PlayerArray[], class location Board[], int Player, bool Doubles, bool FirstRoll);
    void PayRent (player PlayerArray[], class location Board[], int Player);
    void PayRentUtility (player PlayerArray[], class location Board[], int Player);
    void BuyProperty (player PlayerArray[], class location Board[], int Player);
    void TurnInJail (player PlayerArray[], class location Board[], int Player);
    void PassedGO (player PlayerArray[], class location Board[], int Player);
    // 3/4
    void CheckMonopoly (class location Board[], int Prop); // CHECKS FOR A MONOPOLY AFTER A PLAYER GAINS A CARD
    void UtilRRMonopoly (class location Board[], int Prop, int Player); //  CHECKS FOR UTILITY OR RAILROAD MONOPOLY
    void PropDetails (class location Board[], int Prop); // DISPLAYS PROPERTY DETAILS
    void MyProperties (player PlayerArray[], class location Board[], int Player); // DISPLAYS OWNED PROPERTIES
    // 3/6
    void UpdateProp (player PlayerArray[], class location Board[], int Player);
    void BuySellHouseHotel (player PlayerArray[], class location Board[], int Player, int Prop, bool Buying);
    void MortgageProp (player PlayerArray[], class location Board[], int Player, int Prop);
    // 3/7
    void UtilRRDetails (class location Board[], int Prop);
    void Chance (player PlayerArray[], class location Board[], int Player, bool Doubles);
    void CommunityChest(player PlayerArray[], class location Board[], int Player);

};

//CLASS FUNCTIONS
//----------------------------------------------------------------------------------------------------------------------
player::player() {

}

location::location() {

}

void player::RollDice(player PlayerArray[], struct location *Board, int Player, bool FirstRoll) {
    string inplace; // JUST A TEMP STRING TO ALLOW FOR CIN TO ADD ACTION TO DICE ROLL
    int min = 1;
    int max = 6;
    cout << PlayerArray[Player].PlayerName << " press '1' to roll the dice\n";
    cin >> inplace;
    cout << PlayerArray[Player].PlayerName << " rolled ";
    int roll1 = 0, roll2 = 0, roll = 0;
    roll1 = rand() % (max - min + 1) + min;
    cout << roll1 << " + ";
    roll2 = rand() % (max - min + 1) + min;
    cout << roll2;
    roll = roll1 + roll2;
    cout << " = " << roll << "\n";
    PlayerArray[Player].DiceRoll = roll;
    bool GotDubs = false;
    if (!FirstRoll) {
        if (roll1 == roll2) { // IF PLAYER IS IN JAIL AND ROLLS DOUBLES, GETS OUT OF JAIL
            GotDubs = true;
            if (PlayerArray[Player].InJail) {
                cout << "Doubles set you free\n";
                PlayerArray[Player].InJail = false;
                PlayerArray[Player].JailTurns = 0;
                PlayerArray[Player].DiceRoll = roll;
                PlayerArray[Player].DoublesCount++;
                PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, true, false);
            } else {
                PlayerArray[Player].DiceRoll = roll;
                PlayerArray[Player].DoublesCount++;
                PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, true, FirstRoll);

            }
        }
        if (!GotDubs) { // DOUBLES WILL HAVE US CALL MOVE FUNCTION ONE TOO MNY TIMES, CHECK FOR THAT
            PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, false, FirstRoll);// move places on the board
        }
    }
}

void player::MovePlayer(player *PlayerArray, struct location *Board, int Player, bool Doubles, bool FirstRoll) { // MOVE PLAYER TO NEW LOCATION
    if (PlayerArray[Player].location + PlayerArray[Player].DiceRoll < 40) {
        PlayerArray[Player].location = PlayerArray[Player].location + PlayerArray[Player].DiceRoll;
    }
    else {
        PlayerArray[Player].PassedGO(PlayerArray, Board, Player); // PLAYER GETS 200 FOR PASSING GO
        PlayerArray[Player].location = PlayerArray[Player].location + PlayerArray[Player].DiceRoll - 40;
    }
    cout << PlayerArray[Player].PlayerName << " moved to " << Board[PlayerArray[Player].location].Name << "\n"; // CHECK IF LOCATION IS PROPERTY
    if (Board[PlayerArray[Player].location].isProperty) { // CHECK IF LOCATION IS OWNED BY ANOTHER PLAYER
        if (Board[PlayerArray[Player].location].Owned) { // IF PROPERTY IS OWNED
            cout << "ONWER" << Board[PlayerArray[Player].location].OwnerID << "  Player " << PlayerArray[Player].PID << "\n";
            if (Board[PlayerArray[Player].location].OwnerID == PlayerArray[Player].PID) { // IF PLAYER IS ON THEIR OWN PROPERTY
                cout << "\nThis property is yours\n";
            }
            else {
                if (Board[PlayerArray[Player].location].isUtility){
                    PlayerArray[Player].PayRentUtility(PlayerArray, Board, Player);
                }
                else{
                    PlayerArray[Player].PayRent(PlayerArray, Board, Player);
                }
            }
        }
        else { // IF PROPERTY IS UNOWNED
            int BuyOrNo;
            cout << "\nYou landed on " << Board[PlayerArray[Player].location].Name << "\nPress '1' to buy, '8' for property info, or '0' to skip: \n";
            cout << "Current balance: $" << PlayerArray[Player].Bal << "\n";
            cout << "Cost: $" << Board[PlayerArray[Player].location].Price << "\n";
            cin >> BuyOrNo;

            while (BuyOrNo == 8){
                if (Board[PlayerArray[Player].location].isRailroad || Board[PlayerArray[Player].location].isUtility){
                    PlayerArray[Player].UtilRRDetails(Board, PlayerArray[Player].location);
                }
                else {
                    PlayerArray[Player].PropDetails(Board, PlayerArray[Player].location);
                }
                cout << "Press '1' to buy, '8' for property info, or '0' to skip: \n";
                cin >> BuyOrNo;
            }
            if (BuyOrNo == 1){ // IF BUYING
                PlayerArray[Player].BuyProperty(PlayerArray, Board, Player);
            }
        }
    }
    else{
        if (PlayerArray[Player].location == 30){ // IF PLAYER LANDS ON GO TO JAIL SQUARE
            cout << "GO TO JAIL\n";
            PlayerArray[Player].location = 10;
            PlayerArray[Player].InJail = true;
        }
        else if (Board[PlayerArray[Player].location].Name == "Chance"){
            PlayerArray[Player].Chance(PlayerArray, Board, Player, Doubles);
        }
        else if (Board[PlayerArray[Player].location].Name == "CommunityChest"){

        }
    }
    if (!Doubles){
        PlayerArray[Player].DoublesCount = 0;
    }
    if (!FirstRoll) {
        if (Doubles) {
            if (PlayerArray[Player].DoublesCount == 3) {
                cout << "3 doubles in a row!\nGO TO JAIL\n";
                PlayerArray[Player].InJail = true;
                PlayerArray[Player].location = 10;
            } else {
                cout << "Rolled doubles! \n";
                PlayerArray[Player].RollDice(PlayerArray, Board, Player, false);
            }
        }
    }
}

void player::PayRent(player *PlayerArray, struct location *Board, int Player) {
    //------------------------------------------------------------------------------------------------------------------
    //NEED TO ADD CHECKS FOR AVAILABLE FUNDS IN ALL NESTED IF STATEMENTS BELOW,
    // IF NO AVAILABLE FUNDS USERS SHOULD HAVE THE OPTION TO
    //SELL MORTGAGE, AND TRADE PROPERTIES OR DECLARE BANKRUPTCY
    //------------------------------------------------------------------------------------------------------------------
    if (Board[PlayerArray[Player].location].isMonopoly){ // CHECK IF MONOPOLY
        if (Board[PlayerArray[Player].location].Hotel){ //CHECK IF HOTEL
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].RentH << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[PlayerArray[Player].location].RentH; //subtract hotel rent
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + Board[PlayerArray[Player].location].RentH; // add hotel rent to owner
        }
        else if(Board[PlayerArray[Player].location].numHouse == 0){ // CHECK HOUSE AMOUNTS
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent * 2 << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - (Board[PlayerArray[Player].location].Rent * 2); //subtract double rent from payee
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + (Board[PlayerArray[Player].location].Rent * 2); // add double rent to owner
        }
        else if(Board[PlayerArray[Player].location].numHouse == 1){
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent1H << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[PlayerArray[Player].location].Rent1H;
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + Board[PlayerArray[Player].location].Rent1H;
        }
        else if(Board[PlayerArray[Player].location].numHouse == 2){
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent2H << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[PlayerArray[Player].location].Rent2H;
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + Board[PlayerArray[Player].location].Rent2H;
        }
        else if(Board[PlayerArray[Player].location].numHouse == 3){
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent3H << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[PlayerArray[Player].location].Rent3H;
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + Board[PlayerArray[Player].location].Rent3H;
        }
        else if(Board[PlayerArray[Player].location].numHouse == 4){
            cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent4H << "\n";
            PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[PlayerArray[Player].location].Rent4H;
            PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + Board[PlayerArray[Player].location].Rent4H;
        }
    }
    else{
        cout << PlayerArray[Player].PlayerName << " has to pay " << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $" << Board[PlayerArray[Player].location].Rent << "\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - (Board[PlayerArray[Player].location].Rent);
        PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + (Board[PlayerArray[Player].location].Rent);
    }
    cout << "\n" << PlayerArray[Player].PlayerName << " now has $" << PlayerArray[Player].Bal;
    cout << "\n" << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " now has $" << PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal << "\n";
}

void player::BuyProperty(player *PlayerArray, struct location *Board, int Player) {
    int CurrProp = PlayerArray[Player].location; // CURRENT LOCATION
    cout << PlayerArray[Player].PlayerName << " bought " << Board[CurrProp].Name << " for $" << Board[CurrProp].Price;
    Board[CurrProp].Owned = true;// SET PROPERTY TO OWNED
    Board[CurrProp].OwnerID = Player; // SET OWNER ID TO PLAYER ID
    PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[CurrProp].Price;
    cout << "\nYou now have $" << PlayerArray[Player].Bal << "\n";
    if (Board[CurrProp].isRailroad || Board[CurrProp].isUtility){
        PlayerArray[Player].UtilRRMonopoly(Board, PlayerArray[Player].location, Player);
    }
    else {
        PlayerArray[Player].CheckMonopoly(Board, CurrProp);
    }
}

void player::TurnInJail(player PlayerArray[], class location Board[], int Player) { // JAILFUNCTION
    PlayerArray[Player].JailTurns++; //ADD 1 TO COUNT OF TURNS IN JAIL
    if (PlayerArray[Player].JailTurns == 3){ // PLAYER CAN LEAVE IF THERE FOR 3 TURNS
        PlayerArray[Player].InJail = false;
        PlayerArray[Player].JailTurns = 0;
        PlayerArray[Player].RollDice(PlayerArray, Board, Player, false);
    }
    int Choice;
    cout << PlayerArray[Player].PlayerName << " is in jail\nPress '1' to pay $50 and leave, '0' to roll for doubles, or '8' to play a get out of jail free card\n";
    cin >> Choice;
    while (Choice == 8){ // WHILE LOOP TO MAKE AA GOOJF CARD PLAYABLE ONLY IF YOU OWN ONE
        if (PlayerArray[Player].GOOJF) { // PLAYER USES GOOJF CARD
            PlayerArray[Player].GOOJF = false;
            PlayerArray[Player].InJail = false;
            PlayerArray[Player].JailTurns = 0;
            break;
        }
        else{
            cout << "You don't have a get out of jail free card\nPress '1' to pay $50 and leave or '0' to roll for doubles\n";
            cin >> Choice;
        }
    }
    if (Choice == 1){ //PLAYER PAYS 50 TO LEAVE
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - 50;
        PlayerArray[Player].InJail = false;
        PlayerArray[Player].JailTurns = 0;
        PlayerArray[Player].RollDice(PlayerArray, Board, Player, false);
    }
    else if (Choice == 0){
        PlayerArray[Player].RollDice(PlayerArray, Board, Player, false);
    }
}

void player::PassedGO(player *PlayerArray, struct location *Board, int Player) {
    cout << "You've Passed GO!\nCollect $200\n";
    PlayerArray[Player].Bal = PlayerArray[Player].Bal + 200;
    cout << "You now have: $" << PlayerArray[Player].Bal << "\n";
}

void player::CheckMonopoly(struct location *Board, int Prop) { // CHECKS IF PLAYER HAS MONOPOLY AFTER PLAYER GETS A PROPERTY
    int NumOwned = 0; // COUNTING THE NUMBER OF SAME-COLOR PROPERTIES AS PARAMETER 'PROP'
    for (int i = Prop - 3; i < Prop + 3; i++){
        if (Board[i].Color == Board[Prop].Color && Board[i].OwnerID == Board[Prop].OwnerID){ // IF COLOR IS THE SAME AS PROP AND OWNER IS THE SAME AS PROP
            NumOwned++;
        }
    }
    if (Board[Prop].Color == "Purple" || Board[Prop].Color == "DarkBlue") { // DIFFERENT CODE FOR THESE PROPERTIES - ONLY 2 OF A KIND
        if (NumOwned == 2){ // IF PLAYER OWNS BOTH PROPERTIES
            cout << "You now have a monopoly!\n";
            for (int i = Prop - 3; i < Prop + 3; i++){
                if (Board[i].Color == Board[Prop].Color && Board[i].OwnerID == Board[Prop].OwnerID){ // IF COLOR IS THE SAME AS PROP AND OWNER IS THE SAME AS PROP
                    cout << Board[i].Name << "\n";
                    Board[i].isMonopoly = true;
                }
            }
        }
        else { // SET MONOPOLY TO FALSE - THIS IS NEEDED IF A PLAYER SELLS A PROPERTY FROM A SET THEY HAVE A MONOPOLY IN
            for (int i = Prop - 3; i < Prop + 3; i++) {
                if (Board[i].Color == Board[Prop].Color && Board[i].OwnerID ==
                                                           Board[Prop].OwnerID) { // IF COLOR IS THE SAME AS PROP AND OWNER IS THE SAME AS PROP
                    Board[i].isMonopoly = false;
                }
            }
        }
    }
    else{
        if (NumOwned == 3){ // IF PLAYER OWNS ALL THREE
            cout << "You now have a monopoly!\n";
            for (int i = Prop - 3; i < Prop + 3; i++){
                if (Board[i].Color == Board[Prop].Color && Board[i].OwnerID == Board[Prop].OwnerID){ // IF COLOR IS THE SAME AS PROP AND OWNER IS THE SAME AS PROP
                    cout << Board[i].Name << "\n";
                    Board[i].isMonopoly = true;
                }
            }
        }
        else { // SET MONOPOLY TO FALSE - THIS IS NEEDED IF A PLAYER SELLS A PROPERTY FROM A SET THEY HAVE A MONOPOLY IN
            for (int i = Prop - 3; i < Prop + 3; i++) {
                if (Board[i].Color == Board[Prop].Color && Board[i].OwnerID == Board[Prop].OwnerID) { // IF COLOR IS THE SAME AS PROP AND OWNER IS THE SAME AS PROP
                    Board[i].isMonopoly = false;
                }
            }
        }
    }
}

void player::PropDetails(struct location *Board, int Prop) { // PRINTS OUT A DETAILED REPORT OF PROPERTY
    cout << "---------------------------------------------------------------------------------";
    cout << "\nProperty Name: " << Board[Prop].Name;
    cout << "\nProperty Set: " << Board[Prop].Color;
    cout << "\nProperty Price: $" << Board[Prop].Price;
    cout << "\n\nRent: $" << Board[Prop].Rent;
    cout << "\nRent (1 House): $" << Board[Prop].Rent1H;
    cout << "\nRent (2 Houses): $" << Board[Prop].Rent2H;
    cout << "\nRent (3 Houses): $" << Board[Prop].Rent3H;
    cout << "\nRent (4 Houses): $" << Board[Prop].Rent4H;
    cout << "\nRent (Hotel): $" << Board[Prop].RentH;
    cout << "\n\nMortgage Value: $" << Board[Prop].MortgageVal;
    cout << "\nHouse Cost: $" << Board[Prop].HouseP;
    cout << "\n---------------------------------------------------------------------------------\n";
}

// RENT UTILITY FUNCTIONALITY HASN'T BEEN TESTED YET
void player::PayRentUtility(player *PlayerArray, struct location *Board, int Player) {
    //------------------------------------------------------------------------------------------------------------------
    //NEED TO ADD CHECKS FOR AVAILABLE FUNDS IN ALL NESTED IF STATEMENTS BELOW,
    // IF NO AVAILABLE FUNDS USERS SHOULD HAVE THE OPTION TO
    //SELL MORTGAGE, AND TRADE PROPERTIES OR DECLARE BANKRUPTCY
    //------------------------------------------------------------------------------------------------------------------
    if (Board[PlayerArray[Player].location].isMonopoly){ // IF MONOPOLY PAY 10X DICE ROLL
        cout << PlayerArray[Player].PlayerName << " has to pay "
             << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $"
             << 10 * PlayerArray[Player].DiceRoll << "\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - 10 * PlayerArray[Player].DiceRoll;
        PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + 10 * PlayerArray[Player].DiceRoll;
    }
    else { // ELSE PAY 4X DICE ROLL
        cout << PlayerArray[Player].PlayerName << " has to pay "
             << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " $"
             << 4 * PlayerArray[Player].DiceRoll << "\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - 4 * PlayerArray[Player].DiceRoll;
        PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal = PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal + 4 * PlayerArray[Player].DiceRoll;
    }
    cout << "\n" << PlayerArray[Player].PlayerName << " now has $" << PlayerArray[Player].Bal;
    cout << "\n" << PlayerArray[Board[PlayerArray[Player].location].OwnerID].PlayerName << " now has $" << PlayerArray[Board[PlayerArray[Player].location].OwnerID].Bal << "\n";

}

// UTILRR MONOPOLY FUNCTION NOT TESTED
void player::UtilRRMonopoly(struct location *Board, int Prop, int Player) {
    int NumOwned = 0; // COUNTING THE NUMBER OF SAME-COLOR PROPERTIES AS PARAMETER 'PROP'
    if (Board[Prop].isRailroad) {
        for (int i = 0; i < 40; i++) {
            if (Board[i].isRailroad && Board[i].OwnerID == Player) {
                NumOwned++;
            }
            if (NumOwned == 4) {
                cout << "RAILROAD MONOPOLY\n";
            }
        }
        for (int i = 0; i < 40; i++) {
            if (Board[i].isRailroad && Board[i].OwnerID == Player) {
                Board[i].numHouse = NumOwned;
            }
        }
    }
    else{
        for (int i = 0; i < 40; i++) {
            if (Board[i].isUtility && Board[i].OwnerID == Player) {
                NumOwned++;
            }
        }
        if (NumOwned == 2){
            cout << "UTILITY MONOPOLY\n";
            Board[12].isMonopoly = true;
            Board[28].isMonopoly = true;
        }
    }
}

void player::MyProperties(player *PlayerArray, struct location *Board, int Player) { // DISPLAYS PROPERTIES OWNED BY PLAYER
    cout << "-------------- " << PlayerArray[Player].PlayerName << "'s Properties --------------\n";
    for (int i = 0; i < 40; i++){
        if (Board[i].OwnerID == Player) { //IF PROP IS OWNED BY PLAYER
            if (Board[i].isRailroad || Board[i].isUtility){ //IF PROP IS UTILITY
                cout << "-- " << Board[i].Name << " --\n";
                if (Board[i].isRailroad) {
                    cout << "Railroads Owned: " << Board[i].numHouse << "\n";
                }
                if (Board[i].isMonopoly) {
                    cout << "Monopoly: YES\n";
                }
                else{
                    cout << "Monopoly: NO\n";
                }
               \
                if (Board[i].isMortgaged){
                    cout << "Mortgaged: YES\n";
                }
                else{
                    cout << "Mortgaged: NO\n\n";
                }
            }
            else{ // ELSE NOT UTILITY PRINT
                cout << "-- " << Board[i].Name << " --\nSet: " << Board[i].Color << "\n";
                if (Board[i].isMonopoly){
                    cout << "Monopoly: YES\n";
                    if (Board[i].Hotel){
                        cout << "Hotel: YES\n";
                    }
                    else{
                        cout << "Hotel: NO\n";
                        cout << "Houses: " << Board[i].numHouse << "\n";
                    }
                }
                else{
                    cout << "Monopoly: NO\n";
                }
                if (Board[i].isMortgaged){
                    cout << "Mortgaged: YES\n";
                }
                else{
                    cout << "Mortgaged: NO\n\n";
                }
            }
        }
    }
}
// HOUSE BUY/SELL FUNCTIONALITY NOT YET TESTED
// MORTGAGE FUNCTION NOT IMPLEMENTED
// ADD PROPDETAILS FUNCTION CALL SOMEWHERE
void player::UpdateProp(player *PlayerArray, struct location *Board, int Player) {
    PlayerArray[Player].MyProperties(PlayerArray, Board, Player);
    cout << "Press '1' to go back\nPress '2' to buy/sell houses/hotels\nPress '3' to mortgage/unmortgage\n";
    int Choice;
    cin >> Choice;
    cout << "Enter a property to update or '1' to go back: \n";
    string PropUpdate;
    cin >> PropUpdate;
    bool GotProp = false;
    int WhichProp;
    while (!GotProp) { // WHILE LOOP TO VERIFY INPUT
        for (int i = 0; i < 40; i++) {
            if (Board[i].Name == PropUpdate) {
                WhichProp = i;
                GotProp = true;
            }
        }
        if (PropUpdate == "1") {
            GotProp = true;
        }
        if (!GotProp) { // CHECK IF PROPERTY ENTERED IS OWNED BY PLAYER
            cout << "You don't own that property\nEnter another property or press '1' to go back: \n";
            cin >> PropUpdate;
        }
    }
    if (PropUpdate != "1"){ // IF NOT NEXT TURN INPUT
        while (Choice != 1){
            if (Choice == 2){ // IF BUYING/SELLING HOUSES
                if (Board[WhichProp].isMonopoly) {
                    cout << "Press 'b' to buy house/hotel\nPress 's' to sell house/hotel\n";
                    char BuyOrSell;
                    cin >> BuyOrSell;
                    if (BuyOrSell == 'b') { // IF BUYING
                        if (Board[WhichProp].Hotel) {
                            cout << "You already have a hotel on this property\n";
                            PlayerArray[Player].UpdateProp(PlayerArray, Board,
                                                           Player); // GO BACK TO PROPERTY SELECTION SCREEN
                        } else {
                            PlayerArray[Player].BuySellHouseHotel(PlayerArray, Board, Player, WhichProp, true);
                        }
                    } else if (BuyOrSell == 's') { // IF SELLING
                        if (Board[WhichProp].numHouse == 0 && !Board[WhichProp].Hotel) {
                            cout << "You have no houses on this property\n";
                            PlayerArray[Player].UpdateProp(PlayerArray, Board,
                                                           Player); // GO BACK TO PROPERTY SELECTION SCREEN
                        } else {
                            PlayerArray[Player].BuySellHouseHotel(PlayerArray, Board, Player, WhichProp, false);
                        }
                    }
                }
                else {
                    cout << "You need a monopoly to buy houses\n";
                }
            }
            else if (Choice == 3){
                PlayerArray[Player].MortgageProp(PlayerArray, Board, Player, WhichProp);
            }
            cout << "Press '1' to go back\nPress '2' to buy/sell houses/hotels\nPress '3' to mortgage\n";
            cin >> Choice;
        }
    }
}

void player::BuySellHouseHotel(player *PlayerArray, struct location *Board, int Player, int Prop, bool Buying) {
    if (Buying){
        if (PlayerArray[Player].Bal <= Board[Prop].HouseP){
            cout << "You don't have the fund to buy house/hotel here\n";
        }
        else{
            cout << "Press '1' to buy one\nPress '3' to buy set";
            int OneSet;
            cin >> OneSet;
            if (OneSet == 1){
                PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[Prop].HouseP;
                if (Board[Prop].numHouse == 4){
                    Board[Prop].Hotel = true;
                }
                else {
                    Board[Prop].numHouse++;
                }
            }
            else if (OneSet == 3){
                if (PlayerArray[Player].Bal <= Board[Prop].HouseP * 3){
                    cout << "You don't have the funds to buy a set here\n";
                }
                else {
                    for (int i = 0; i < 40; i++){
                        if (Board[i].Color == Board[Prop].Color){
                            if (Board[i].numHouse == 4){
                                Board[i].Hotel = true;
                            }
                            else if (!Board[i].Hotel) {
                                Board[i].numHouse++;
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        if (Board[Prop].numHouse == 0){
            cout << "You don't have any houses on this property";
        }
        else {
            cout << "Press '1' to sell one\nPress '3' to sell set";
            int OneSet;
            cin >> OneSet;
            if (OneSet == 1) {
                PlayerArray[Player].Bal = PlayerArray[Player].Bal + Board[Prop].HouseP / 2;
                if (Board[Prop].Hotel){ // IF SELLING HOTEL
                    Board[Prop].numHouse = 4;
                    Board[Prop].Hotel = false;
                }
                else if (Board[Prop].numHouse > 0){ // ELSE SELL A HOUSE
                    Board[Prop].numHouse--;
                }
            }
            else if (OneSet == 3){
                for (int i = 0; i < 40; i++){
                    PlayerArray[Player].Bal = PlayerArray[Player].Bal + Board[Prop].HouseP / 2;
                    if (Board[Prop].Hotel){ // IF SELLING HOTEL
                        Board[Prop].numHouse = 4;
                        Board[Prop].Hotel = false;
                    }
                    else if (Board[Prop].numHouse > 0){
                        Board[Prop].numHouse--;
                    }
                }
            }
        }
    }
}
// ADD CHECK FOR HOUSES, PLAYERS CANT MORTGAGE A PROP IF IT HAS HOUSES
void player::MortgageProp(player *PlayerArray, struct location *Board, int Player, int Prop) {
    cout << "Press '1' to select a different property\nPress '2' to mortgage\nPress '3' to unmortgage\n";
    int TwoOrThree;
    string Choice;
    cin >> TwoOrThree;
    if (TwoOrThree == 2){
        PlayerArray[Player].Bal = PlayerArray[Player].Bal + Board[Prop].MortgageVal;
        Board[Prop].isMortgaged = true;
        cout << Board[Prop].Name << " is now mortgaged\nYour balance is now $" << PlayerArray[Player].Bal << "\n";
    }
    else if (TwoOrThree == 3){
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - Board[Prop].MortgageVal * 1.1; // PAY BACK 10% INTEREST
        Board[Prop].isMortgaged = false;
        cout << Board[Prop].Name << " is no longer mortgaged\nYour balance is now $" << PlayerArray[Player].Bal << "\n";
    }
}

void player::UtilRRDetails(struct location *Board, int Prop) {
    cout << "---------------------------------------------------------------------------------";
    cout << "\nProperty Name: " << Board[Prop].Name;
    if (Board[Prop].isRailroad){
        cout << "\nProperty Set: Railroad";
    }
    else {
        cout << "\nProperty Set: Utility";
    }
    cout << "\nProperty Price: $" << Board[Prop].Price;
    if (Board[Prop].isRailroad){
        cout << "\n\nRent:";
        cout << "\n1 Railroad owned: $" << Board[Prop].Rent;
        cout << "\n2 Railroads owned: $" << Board[Prop].Rent1H;
        cout << "\n3 Railroads owned: $" << Board[Prop].Rent2H;
        cout << "\nRailroad monopoly: $" << Board[Prop].Rent3H;
    }
    else {
        cout << "\nRent:\n4x dice roll if not monopoly\n10x dice roll if monopoly";
    }
    cout << "\n\nMortgage Value: $" << Board[Prop].MortgageVal;
    cout << "\n---------------------------------------------------------------------------------\n";
}

void player::Chance(player *PlayerArray, struct location *Board, int Player, bool Doubles) {
    int ChanceRoll = rand() % (16 - 1 + 1) + 1;
    if (ChanceRoll == 1){ // MOVE TO GO
        cout << "Move to GO!\n";
        PlayerArray[Player].DiceRoll = 40 - PlayerArray[Player].location + 0;
        PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, Doubles, false);
    }
    if (ChanceRoll == 2){ // GO TO FIRST RAILROAD
        cout << "Move to Chase!\n";
        PlayerArray[Player].DiceRoll = 40 - PlayerArray[Player].location + 5;
        PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, Doubles, false);
    }
    if (ChanceRoll == 3){ // GO TO FIRST PINK
        cout << "Move to Knapton!\n";
        PlayerArray[Player].DiceRoll = 40 - PlayerArray[Player].location + 11;
        PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, Doubles, false);
    }
    if (ChanceRoll == 4){ // GO TO DADDYS HOUSE
        cout << "Move to Hannos House!\n";
        PlayerArray[Player].DiceRoll = 40 - PlayerArray[Player].location + 38;
        PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, Doubles, false);
    }
    if (ChanceRoll == 5){ // GO TO LAST RED
        cout << "Move to BEARD!\n";
        PlayerArray[Player].DiceRoll = 40 - PlayerArray[Player].location + 24;
        PlayerArray[Player].MovePlayer(PlayerArray, Board, Player, Doubles, false);
    }
    if (ChanceRoll == 6){
        cout << "GO TO JAIL\n";
        PlayerArray[Player].location = 10;
        PlayerArray[Player].InJail = true;
    }
    if (ChanceRoll == 7){
        cout << "Gain $50\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal + 50;
    }
    if (ChanceRoll == 8){
        cout << "Gain $150\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal + 150;
    }
    if (ChanceRoll == 9){
        cout << "Pay $15\n";
        PlayerArray[Player].Bal = PlayerArray[Player].Bal - 15;
    }
    if (ChanceRoll == 10){
        cout << "Move back 3 spaces\n";
        PlayerArray[Player].location -= 3;
    }
    if (ChanceRoll == 11){
        cout << "Get out of jail free card!\n";
        PlayerArray[Player].GOOJF = true;
    }
    if (ChanceRoll == 12 || ChanceRoll == 13){ // ADVANCE TO NEAREST RAILROAD NEEDS TESTING
        cout << "Advance to nearest railroad\nIf owned pay double rent";
        if (PlayerArray[Player].location == 7){
            PlayerArray[Player].location = 15;
            if (Board[15].Owned){
                PlayerArray[Player].PayRent(PlayerArray, Board, Player);
                PlayerArray[Player].PayRent(PlayerArray, Board, Player);
            }
            else {
                int BuyOrNo;
                cout << "\nYou moved to " << Board[PlayerArray[Player].location].Name << "\nPress '1' to buy, '8' for property info, or '0' to skip: \n";
                cout << "Current balance: $" << PlayerArray[Player].Bal << "\n";
                cout << "Cost: $" << Board[PlayerArray[Player].location].Price << "\n";
                cin >> BuyOrNo;
                while (BuyOrNo == 8){
                    if (Board[PlayerArray[Player].location].isRailroad || Board[PlayerArray[Player].location].isUtility){
                        PlayerArray[Player].UtilRRDetails(Board, PlayerArray[Player].location);
                    }
                    else {
                        PlayerArray[Player].PropDetails(Board, PlayerArray[Player].location);
                    }
                    cout << "Press '1' to buy, '8' for property info, or '0' to skip: \n";
                    cin >> BuyOrNo;
                }
                if (BuyOrNo == 1){ // IF BUYING
                    PlayerArray[Player].BuyProperty(PlayerArray, Board, Player);
                }
            }
        }
        else if (PlayerArray[Player].location == 22){
            PlayerArray[Player].location = 25;
            if (Board[25].Owned){
                PlayerArray[Player].PayRent(PlayerArray, Board, Player);
                PlayerArray[Player].PayRent(PlayerArray, Board, Player);
            }
            else {
                int BuyOrNo;
                cout << "\nYou moved to " << Board[PlayerArray[Player].location].Name << "\nPress '1' to buy, '8' for property info, or '0' to skip: \n";
                cout << "Current balance: $" << PlayerArray[Player].Bal << "\n";
                cout << "Cost: $" << Board[PlayerArray[Player].location].Price << "\n";
                cin >> BuyOrNo;
                while (BuyOrNo == 8){
                    if (Board[PlayerArray[Player].location].isRailroad || Board[PlayerArray[Player].location].isUtility){
                        PlayerArray[Player].UtilRRDetails(Board, PlayerArray[Player].location);
                    }
                    else {
                        PlayerArray[Player].PropDetails(Board, PlayerArray[Player].location);
                    }
                    cout << "Press '1' to buy, '8' for property info, or '0' to skip: \n";
                    cin >> BuyOrNo;
                }
                if (BuyOrNo == 1){ // IF BUYING
                    PlayerArray[Player].BuyProperty(PlayerArray, Board, Player);
                }
            }
        }
        else  if (PlayerArray[Player].location == 36){
            cout << "Advance to nearest railroad\nIf owned pay double rent";
                PlayerArray[Player].location = 5;
                PlayerArray[Player].Bal += 200;
                if (Board[5].Owned){
                    PlayerArray[Player].PayRent(PlayerArray, Board, Player);
                    PlayerArray[Player].PayRent(PlayerArray, Board, Player);
                }
                else {
                    int BuyOrNo;
                    cout << "\nYou moved to " << Board[PlayerArray[Player].location].Name << "\nPress '1' to buy, '8' for property info, or '0' to skip: \n";
                    cout << "Current balance: $" << PlayerArray[Player].Bal << "\n";
                    cout << "Cost: $" << Board[PlayerArray[Player].location].Price << "\n";
                    cin >> BuyOrNo;
                    while (BuyOrNo == 8){
                        if (Board[PlayerArray[Player].location].isRailroad || Board[PlayerArray[Player].location].isUtility){
                            PlayerArray[Player].UtilRRDetails(Board, PlayerArray[Player].location);
                        }
                        else {
                            PlayerArray[Player].PropDetails(Board, PlayerArray[Player].location);
                        }
                        cout << "Press '1' to buy, '8' for property info, or '0' to skip: \n";
                        cin >> BuyOrNo;
                    }
                    if (BuyOrNo == 1){ // IF BUYING
                        PlayerArray[Player].BuyProperty(PlayerArray, Board, Player);
                    }
                }
            }
        }
    if (ChanceRoll == 14){ // PAY EACH PLAYER 50 DOLLARS
        for (int i = 0; i < 4; i++){
            if (!PlayerArray[i].Bankrupt){
                PlayerArray[Player].Bal -= 50;
                PlayerArray[i].Bal += 50;
            }
        }
    }
    if (ChanceRoll == 15){
        
    }
}





//MAIN
//----------------------------------------------------------------------------------------------------------------------
int main() {
    // CREATING ALL LOCATIONS
    location Board[40]; // ARRAY OF LOCATION OBJECTS REPRESENTING THE BOARD

    // NON-PROPERTY TILES
    // CORNER TILES
    location GO;
    GO.isProperty = false;
    GO.Name = "GO";
    Board[0] = GO;

    location JAIL;
    JAIL.isProperty = false;
    JAIL.Name = "JAIL";
    Board[10] = JAIL;

    location FREEPARKING;
    FREEPARKING.isProperty = false;
    FREEPARKING.Name = "FREEPARKING";
    Board[20] = FREEPARKING;

    location GOTOJAIL;
    GOTOJAIL.isProperty = false;
    GOTOJAIL.Name = "GOTOJAIL";
    Board[30] = GOTOJAIL;

//------------------------------------------------------------------------------------------------------------------
    // IN-BOARD TILES
    location CommunityChest;
    CommunityChest.isProperty = false;
    CommunityChest.Name = "CommunityChest";
    Board[2] = CommunityChest;
    Board[17] = CommunityChest;
    Board[33] = CommunityChest;

    location Chance;
    Chance.isProperty = false;
    Chance.Name = "Chance";
    Board[7] = Chance;
    Board[22] = Chance;
    Board[36] = Chance;

    location IncomeTax; // not a property, but acts as a property owned by the bank collecting rent
    IncomeTax.Name = "IncomeTax";
    IncomeTax.Rent = 200;
    IncomeTax.Owned = true; // rent tiles are "owned" so they can be deducted as rent easily
    IncomeTax.OwnerID = 4; // ownerID 5 is the bank, going to have function Pay to deduct/add to and from player accounts
    Board[4] = IncomeTax;

    location LuxuryTax;
    LuxuryTax.Name = "LuxuryTax";
    LuxuryTax.Rent = 75;
    LuxuryTax.Owned = true;
    LuxuryTax.OwnerID = 4;
    Board[38] = LuxuryTax;

    //----------------------------------------------------------------------------------------------------------------------
    // PROPERTY TILES
    location Meadows;
    Meadows.Name = "Meadows";
    Meadows.Price = 60;
    Meadows.Rent = 2;
    Meadows.Rent1H = 10;
    Meadows.Rent2H = 30;
    Meadows.Rent3H = 90;
    Meadows.Rent4H = 160;
    Meadows.RentH = 250;
    Meadows.MortgageVal = 30;
    Meadows.HouseP = 50;
    Meadows.Color = "Purple";
    Board[1] = Meadows;

    location Pine;
    Pine.Name = "Pine";
    Pine.Price = 60;
    Pine.Rent = 4;
    Pine.Rent1H = 20;
    Pine.Rent2H = 60;
    Pine.Rent3H = 180;
    Pine.Rent4H = 320;
    Pine.RentH = 450;
    Pine.MortgageVal = 30;
    Pine.HouseP = 50;
    Pine.Color = "Purple";
    Board[3] = Pine;

    location Chase;
    Chase.Name = "Chase";
    Chase.Price = 200;
    Chase.isRailroad = true;
    Chase.Rent = 25;
    Chase.Rent1H = 50; // in this case 1 house refers to 1 additional owned railroad
    Chase.Rent2H = 100;
    Chase.Rent3H = 200;
    Chase.MortgageVal = 100;
    Board[5] = Chase;

    location Young;
    Young.Name = "Young";
    Young.Price = 100;
    Young.Rent = 6;
    Young.Rent1H = 30;
    Young.Rent2H = 90;
    Young.Rent3H = 270;
    Young.Rent4H = 400;
    Young.RentH = 550;
    Young.HouseP = 50;
    Young.MortgageVal = 50;
    Young.Color = "LightBlue";
    Board[6] = Young;

    location Mcintire;
    Mcintire.Name = "Mcintire";
    Mcintire.Price = 100;
    Mcintire.Rent = 6;
    Mcintire.Rent1H = 30;
    Mcintire.Rent2H = 90;
    Mcintire.Rent3H = 270;
    Mcintire.Rent4H = 400;
    Mcintire.RentH = 550;
    Mcintire.HouseP = 50;
    Mcintire.MortgageVal = 50;
    Mcintire.Color = "LightBlue";
    Board[8] = Mcintire;

    location Clarke;
    Clarke.Name = "Clarke";
    Clarke.Price = 120;
    Clarke.Rent = 8;
    Clarke.Rent1H = 40;
    Clarke.Rent2H = 100;
    Clarke.Rent3H = 300;
    Clarke.Rent4H = 450;
    Clarke.RentH = 600;
    Clarke.MortgageVal = 60;
    Clarke.HouseP = 50;
    Clarke.Color = "LightBlue";
    Board[9] = Clarke;

    location Knapton;
    Knapton.Name = "Knapton";
    Knapton.Price = 140;
    Knapton.Rent = 10;
    Knapton.Rent1H = 50;
    Knapton.Rent2H = 150;
    Knapton.Rent3H = 450;
    Knapton.Rent4H = 625;
    Knapton.RentH = 750;
    Knapton.MortgageVal = 70;
    Knapton.HouseP = 100;
    Knapton.Color = "Pink";
    Board[11] = Knapton;

    location ArtHouse;
    ArtHouse.Name = "ArtHouse";
    ArtHouse.isUtility = true; // utilities accumulate rent through multiplying the dice roll
    ArtHouse.Price = 150;
    ArtHouse.MortgageVal = 75;
    Board[12] = ArtHouse;

    location Meneely;
    Meneely.Name = "Meneely";
    Meneely.Price = 140;
    Meneely.Rent = 10;
    Meneely.Rent1H = 50;
    Meneely.Rent2H = 150;
    Meneely.Rent3H = 450;
    Meneely.Rent4H = 625;
    Meneely.RentH = 750;
    Meneely.MortgageVal = 70;
    Meneely.HouseP = 100;
    Meneely.Color = "Pink";
    Board[13] = Meneely;

    location Watson;
    Watson.Name = "Watson";
    Watson.Price = 160;
    Watson.Rent = 12;
    Watson.Rent1H = 60;
    Watson.Rent2H = 180;
    Watson.Rent3H = 500;
    Watson.Rent4H = 700;
    Watson.RentH = 900;
    Watson.MortgageVal = 80;
    Watson.HouseP = 100;
    Watson.Color = "Pink";
    Board[14] = Watson;

    location SpencerDavisCafe;
    SpencerDavisCafe.Name = "SpencerDavisCafe";
    SpencerDavisCafe.Price = 200;
    SpencerDavisCafe.isRailroad = true;
    SpencerDavisCafe.Rent = 25;
    SpencerDavisCafe.Rent1H = 50; // in this case 1 house refers to 1 additional owned railroad
    SpencerDavisCafe.Rent2H = 100;
    SpencerDavisCafe.Rent3H = 200;
    SpencerDavisCafe.MortgageVal = 100;
    Board[15] = SpencerDavisCafe;

    location ScienceCenter;
    ScienceCenter.Name = "ScienceCenter";
    ScienceCenter.Price = 180;
    ScienceCenter.Rent = 14;
    ScienceCenter.Rent1H = 70;
    ScienceCenter.Rent2H = 200;
    ScienceCenter.Rent3H = 550;
    ScienceCenter.Rent4H = 750;
    ScienceCenter.RentH = 950;
    ScienceCenter.MortgageVal = 90;
    ScienceCenter.HouseP = 100;
    ScienceCenter.Color = "Orange";
    Board[16] = ScienceCenter;

    location LockSmith;
    LockSmith.Name = "LockSmith";
    LockSmith.Price = 180;
    LockSmith.Rent = 14;
    LockSmith.Rent1H = 70;
    LockSmith.Rent2H = 200;
    LockSmith.Rent3H = 550;
    LockSmith.Rent4H = 750;
    LockSmith.RentH = 950;
    LockSmith.MortgageVal = 90;
    LockSmith.HouseP = 100;
    LockSmith.Color = "Orange";
    Board[18] = LockSmith;

    location Balfour;
    Balfour.Name = "Balfour";
    Balfour.Price = 200;
    Balfour.Rent = 16;
    Balfour.Rent1H = 80;
    Balfour.Rent2H = 220;
    Balfour.Rent3H = 600;
    Balfour.Rent4H = 800;
    Balfour.RentH = 1000;
    Balfour.MortgageVal = 100;
    Balfour.HouseP = 100;
    Balfour.Color = "Orange";
    Board[19] = Balfour;

    location Gebbie;
    Gebbie.Name = "Gebbie";
    Gebbie.Price = 220;
    Gebbie.Rent = 18;
    Gebbie.Rent1H = 90;
    Gebbie.Rent2H = 250;
    Gebbie.Rent3H = 700;
    Gebbie.Rent4H = 875;
    Gebbie.RentH = 1050;
    Gebbie.MortgageVal = 110;
    Gebbie.HouseP = 150;
    Gebbie.Color = "Red";
    Board[21] = Gebbie;

    location Keefe;
    Keefe.Name = "Keefe";
    Keefe.Price = 220;
    Keefe.Rent = 18;
    Keefe.Rent1H = 90;
    Keefe.Rent2H = 250;
    Keefe.Rent3H = 700;
    Keefe.Rent4H = 875;
    Keefe.RentH = 1050;
    Keefe.MortgageVal = 110;
    Keefe.HouseP = 150;
    Keefe.Color = "Red";
    Board[23] = Keefe;

    location Beard;
    Beard.Name = "Beard";
    Beard.Price = 240;
    Beard.Rent = 20;
    Beard.Rent1H = 100;
    Beard.Rent2H = 300;
    Beard.Rent3H = 750;
    Beard.Rent4H = 925;
    Beard.RentH = 1100;
    Beard.MortgageVal = 120;
    Beard.HouseP = 150;
    Beard.Color = "Red";
    Board[24] = Beard;

    location Emerson;
    Emerson.Name = "Emerson";
    Emerson.Price = 200;
    Emerson.isRailroad = true;
    Emerson.Rent = 25;
    Emerson.Rent1H = 50; // in this case 1 house refers to 1 additional owned railroad
    Emerson.Rent2H = 100;
    Emerson.Rent3H = 200;
    Emerson.MortgageVal = 100;
    Board[25] = Emerson;

    location Firepit;
    Firepit.Name = "Firepit";
    Firepit.Price = 260;
    Firepit.Rent = 22;
    Firepit.Rent1H = 110;
    Firepit.Rent2H = 330;
    Firepit.Rent3H = 800;
    Firepit.Rent4H = 975;
    Firepit.RentH = 1150;
    Firepit.MortgageVal = 130;
    Firepit.HouseP = 150;
    Firepit.Color = "Yellow";
    Board[26] = Firepit;

    location RedRock;
    RedRock.Name = "RedRock";
    RedRock.Price = 260;
    RedRock.Rent = 22;
    RedRock.Rent1H = 110;
    RedRock.Rent2H = 330;
    RedRock.Rent3H = 800;
    RedRock.Rent4H = 975;
    RedRock.RentH = 1150;
    RedRock.MortgageVal = 130;
    RedRock.HouseP = 150;
    RedRock.Color = "Yellow";
    Board[27] = RedRock;

    location MADHouse;
    MADHouse.Name = "MADHouse";
    MADHouse.isUtility = true; // utilities accumulate rent through multiplying the dice roll
    MADHouse.Price = 150;
    MADHouse.MortgageVal = 75;
    Board[28] = MADHouse;

    location WitchesHut;
    WitchesHut.Name = "WitchesHut";
    WitchesHut.Price = 280;
    WitchesHut.Rent = 24;
    WitchesHut.Rent1H = 120;
    WitchesHut.Rent2H = 360;
    WitchesHut.Rent3H = 850;
    WitchesHut.Rent4H = 1025;
    WitchesHut.RentH = 1200;
    WitchesHut.MortgageVal = 140;
    WitchesHut.HouseP = 150;
    WitchesHut.Color = "Yellow";
    Board[29] = WitchesHut;

    location ParkHall;
    ParkHall.Name = "ParkHall";
    ParkHall.Price = 300;
    ParkHall.Rent = 26;
    ParkHall.Rent1H = 130;
    ParkHall.Rent2H = 390;
    ParkHall.Rent3H = 900;
    ParkHall.Rent4H = 1100;
    ParkHall.RentH = 1275;
    ParkHall.MortgageVal = 150;
    ParkHall.HouseP = 200;
    ParkHall.Color = "Green";
    Board[31] = ParkHall;

    location MaryLyon;
    MaryLyon.Name = "MaryLyon";
    MaryLyon.Price = 300;
    MaryLyon.Rent = 26;
    MaryLyon.Rent1H = 130;
    MaryLyon.Rent2H = 390;
    MaryLyon.Rent3H = 900;
    MaryLyon.Rent4H = 1100;
    MaryLyon.RentH = 1275;
    MaryLyon.MortgageVal = 150;
    MaryLyon.HouseP = 200;
    MaryLyon.Color = "Green";
    Board[32] = MaryLyon;

    location Chapel;
    Chapel.Name = "Chapel";
    Chapel.Price = 320;
    Chapel.Rent = 28;
    Chapel.Rent1H = 150;
    Chapel.Rent2H = 450;
    Chapel.Rent3H = 1000;
    Chapel.Rent4H = 1200;
    Chapel.RentH = 1400;
    Chapel.MortgageVal = 160;
    Chapel.HouseP = 200;
    Chapel.Color = "Green";
    Board[34] = Chapel;

    location HoodCafe;
    HoodCafe.Name = "HoodCafe";
    HoodCafe.Price = 200;
    HoodCafe.isRailroad = true;
    HoodCafe.Rent = 25;
    HoodCafe.Rent1H = 50; // in this case 1 house refers to 1 additional owned railroad
    HoodCafe.Rent2H = 100;
    HoodCafe.Rent3H = 200;
    HoodCafe.MortgageVal = 100;
    Board[35] = HoodCafe;

    location PeacockPond;
    PeacockPond.Name = "PeacockPond";
    PeacockPond.Price = 350;
    PeacockPond.Rent = 35;
    PeacockPond.Rent1H = 175;
    PeacockPond.Rent2H = 500;
    PeacockPond.Rent3H = 1100;
    PeacockPond.Rent4H = 1200;
    PeacockPond.RentH = 1500;
    PeacockPond.MortgageVal = 175;
    PeacockPond.HouseP = 200;
    PeacockPond.Color = "DarkBlue";
    Board[37] = PeacockPond;

    location HannosHouse;
    HannosHouse.Name = "HannosHouse";
    HannosHouse.Price = 400;
    HannosHouse.Rent = 40;
    HannosHouse.Rent1H = 200;
    HannosHouse.Rent2H = 600;
    HannosHouse.Rent3H = 1400;
    HannosHouse.Rent4H = 1700;
    HannosHouse.RentH = 2000;
    HannosHouse.MortgageVal = 200;
    HannosHouse.HouseP = 200;
    HannosHouse.Color = "DarkBlue";
    Board[39] = HannosHouse;

     //----------------------------------------------------------------------------------------------------------------------------------
    //-----------------------------------------------------------------------------------------------------------------------------------
    //NOW CREATING PLAYERS

    player PLayerArray[5];

    int NumRealPlayers;
    cout << "Welcome to Wheaton Monology!\n\nHow many human players? (up to 4)\n";
    cin >> NumRealPlayers;

    player Bank;
    Bank.PlayerName = "Bank";
    Bank.PID = 5;
    PLayerArray[4] = Bank;

    player P1;
    P1.PID = 0;
    PLayerArray[0] = P1;
    cout << "Player 1\nEnter your name: ";
    cin >> PLayerArray[0].PlayerName;

    player P2;
    P2.PID = 1;
    PLayerArray[1] = P2;
    if (NumRealPlayers > 1){
        cout << "Player 2\nEnter your name: ";
        cin >> PLayerArray[1].PlayerName;
    }
    else{
        PLayerArray[1].PlayerName = "BOT2";
    }

    player P3;
    P3.PID = 2;
    PLayerArray[2] = P3;
    if (NumRealPlayers > 2){
        cout << "Player 3\nEnter your name: ";
        cin >> PLayerArray[2].PlayerName;
    }
    else{
        PLayerArray[2].PlayerName = "BOT3";
    }

    player P4;
    P4.PID = 3;
    PLayerArray[3] = P4;
    if (NumRealPlayers > 3){
        cout << "Player 4\nEnter your name: ";
        cin >> PLayerArray[3].PlayerName;
    }
    else{
        PLayerArray[3].PlayerName = "BOT4";
    }


    //------------------------------------------------------------------------------------------------------------------

    srand(time(0));

    // CHOOSE WHO GETS TO GO FIRST BY ROLLING DICE
    // 2 dice rolls

    //------------------------------------------------------------------------------------------------------------------
    //NEED TO FIX TIE SCENARIO, CRASHED WHEN 3 OR 4 PLAYERS TIED
    // AND DOESNT WORK WHEN 2 PLAYERS TIE
    //------------------------------------------------------------------------------------------------------------------
    int PlayerTurn = 1; // start on player 1's turn - all players roll dice and the highest roll starts the game
    for (int i = 0; i < 4; i++) {
        PLayerArray[i].RollDice(PLayerArray, Board, i, true);
    }
    int HighRoll = 0; // check which player got highest roll
    for (int i = 0; i < 4; i++) {
        if (PLayerArray[i].DiceRoll > HighRoll) { // if higher, new highest roll
            HighRoll = PLayerArray[i].DiceRoll;
            PlayerTurn = i;
            for (int j = 0; j < 4; j++) {
                PLayerArray[j].TiedRoll = false;
            }
        }
        else if (PLayerArray[i].DiceRoll == HighRoll) { // if equal, we roll again with the players that tied
            PLayerArray[i].TiedRoll = true;
        }
        else if (PLayerArray[i].DiceRoll < HighRoll) { // if lower, set tiedroll to false. if 1 or less players have tiedroll = true, we can exit the loop
            PLayerArray[i].TiedRoll = false;
        }
    }
    int LeftToRoll = 0;
    for (int i = 0; i < 4; i++) {
        if (PLayerArray[i].TiedRoll) {
            LeftToRoll++;
        }
    }
    while (LeftToRoll > 1) {
        for (int i = 0; i < 4; i++) {
            if (PLayerArray[i].TiedRoll) {
                PLayerArray[i].RollDice(PLayerArray, Board, i, true);
                if (PLayerArray[i].DiceRoll > HighRoll) { // if higher, new highest roll
                    HighRoll = PLayerArray[i].DiceRoll;
                    PlayerTurn = i;
                }
                else if (PLayerArray[i].DiceRoll == HighRoll) { // if equal, we roll again with the players that tied
                    PLayerArray[i].TiedRoll = true;
                }
                else if (PLayerArray[i].DiceRoll < HighRoll) { // if lower, set tiedroll to false. if 1 or less players have tiedroll = true, we can exit the loop
                    PLayerArray[i].TiedRoll = false;
                }
            }
            LeftToRoll = 0;
            for (int j = 0; j < 4; j++) {
                if (PLayerArray[j].TiedRoll) {
                    LeftToRoll++;
                }
            }
        }
    }

    cout << PLayerArray[PlayerTurn].DiceRoll << "\n";
    cout << PLayerArray[PlayerTurn].PlayerName << " starts the game!\n";

    // GAME BEGINS
    while (PLayerArray[0].RemainingPlayers > 2){ // while two players are still playing
        PlayerTurn = PlayerTurn % 4; // KEEP TURN ORDER MOVING
        if (!PLayerArray[PlayerTurn].Bankrupt) {
            if (PLayerArray[PlayerTurn].InJail) { // CHECK IF PLAYER IS IN JAIL
                PLayerArray[PlayerTurn].TurnInJail(PLayerArray, Board, PlayerTurn);
                PlayerTurn++;
            }
            PLayerArray[PlayerTurn].RollDice(PLayerArray, Board, PlayerTurn, false); // ROLL DICE FOR TURN
            int NextAction;
            cout << "\nPress '1' for next turn or '0' for accounts (trading, buying houses, mortgaging)\n";
            cin >> NextAction;
            if (NextAction == 0) {
                while (NextAction != 1) {
                    cout
                            << "------------Accounts------------\nPress '1' for next turn\nPress '2' to look at your properties\nPress '3' to trade\nPress '4' to update Properties\n";
                    cin >> NextAction;
                    if (NextAction == 2) {
                        PLayerArray[PlayerTurn].MyProperties(PLayerArray, Board, PlayerTurn);
                    }
                    else if (NextAction == 3) {
                        // TRADE CODE HERE
                    }
                    else if (NextAction == 4) {
                        PLayerArray[PlayerTurn].UpdateProp(PLayerArray, Board, PlayerTurn);
                    }
                }
            }
            else {
                PlayerTurn++;
            }
        }
        else {
            PlayerTurn++;
        }
    }







    /*// 2 dice rolls
    int roll1 = 0, roll2 = 0, roll = 0;
    roll1 = rand() % (max - min + 1) + min;
    cout << roll1;
    roll2 = rand() % (max - min + 1) + min;
    cout << roll2;
    roll = roll1 + roll2;*/

    return 0;
}


