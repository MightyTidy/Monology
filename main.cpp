#include <iostream>
#include "JACKO.h"

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
    IncomeTax.isProperty = false;
    IncomeTax.Rent = 200;
    IncomeTax.Owned = true; // rent tiles are "owned" so they can be deducted as rent easily
    IncomeTax.OwnerID = 4; // ownerID 5 is the bank, going to have function Pay to deduct/add to and from player accounts
    Board[4] = IncomeTax;


    location LuxuryTax;
    LuxuryTax.Name = "LuxuryTax";
    LuxuryTax.isProperty = false;
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
    Chase.Rent1H = 25;
    Chase.Rent2H = 50;
    Chase.Rent3H = 100;
    Chase.Rent4H = 200;
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

    location Clark;
    Clark.Name = "Clark";
    Clark.Price = 120;
    Clark.Rent = 8;
    Clark.Rent1H = 40;
    Clark.Rent2H = 100;
    Clark.Rent3H = 300;
    Clark.Rent4H = 450;
    Clark.RentH = 600;
    Clark.MortgageVal = 60;
    Clark.HouseP = 50;
    Clark.Color = "LightBlue";
    Board[9] = Clark;

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
    SpencerDavisCafe.Rent1H = 25;
    SpencerDavisCafe.Rent2H = 50;
    SpencerDavisCafe.Rent3H = 100;
    SpencerDavisCafe.Rent4H = 200;
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
    Emerson.Rent1H = 25; // in this case 1 house refers to 1 owned railroad
    Emerson.Rent2H = 50;
    Emerson.Rent3H = 100;
    Emerson.Rent4H = 200;
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
    HoodCafe.Rent1H = 25; // in this case 1 house refers to 1 owned railroad
    HoodCafe.Rent2H = 50;
    HoodCafe.Rent3H = 100;
    HoodCafe.Rent4H = 200;
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

    //------------------------------------------------------------------------------------------------------------------
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
        PLayerArray[1].Bot = true;
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
        PLayerArray[2].Bot = true;
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
        PLayerArray[3].Bot = true;
    }


    //------------------------------------------------------------------------------------------------------------------

    srand(time(0));

    // CHOOSE WHO GETS TO GO FIRST BY ROLLING DICE
    int PlayerTurn = 0; // start on player 1's turn - all players roll dice and the highest roll starts the game
    int numTied = 4; // start with all 4 players 'tied' just so they all have to roll
    int HighRoll = 0; // variable to store player rolls and find the highest
    while (numTied > 1){
        numTied = 1;
        HighRoll = 0;
        for (int i = 0; i < 4; i++){
            if (PLayerArray[i].TiedRoll) {
                PLayerArray[i].RollDice(PLayerArray, Board, i, true);
            }
            else {
                PLayerArray[i].DiceRoll = 0;
            }
        }
        for (int i = 0; i < 4; i++){
            if (PLayerArray[i].DiceRoll > HighRoll){
                HighRoll = PLayerArray[i].DiceRoll;
                numTied = 1;
                for (int j = 0; j < 4; j++){
                    if (PLayerArray[j].DiceRoll < HighRoll){
                        PLayerArray[j].TiedRoll = false;
                    }
                }
            }
            else if (PLayerArray[i].DiceRoll == HighRoll){
                numTied++;
                PLayerArray[i].TiedRoll = true;
            }
        }
    }
    for (int i = 0; i < 4; i++){
        if (PLayerArray[i].DiceRoll == HighRoll){
            PlayerTurn = i;
        }
    }
    sleep_for(1s);
    cout << "\n" << PLayerArray[PlayerTurn].PlayerName << " starts the game!\n\n";
    // -----------------------------------------------------------------------------------------------------------------
    // GAME BEGINS
    // -----------------------------------------------------------------------------------------------------------------
    while (PLayerArray[0].RemainingPlayers > 2){ // while two players are still playing
        PlayerTurn = PlayerTurn % 4; // KEEP TURN ORDER MOVING
        cout << "\n------------" << PLayerArray[PlayerTurn].PlayerName << "'s turn------------\n\n";
        if (!PLayerArray[PlayerTurn].Bot) {
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
                        } else if (NextAction == 3) {
                            PLayerArray[PlayerTurn].Trade(PLayerArray, Board, PlayerTurn);
                        } else if (NextAction == 4) {
                            PLayerArray[PlayerTurn].UpdateProp(PLayerArray, Board, PlayerTurn);
                        } else if (NextAction == 5) {
                            // DISPLAY BOARD FUNCTION HERE
                        }
                        if (NextAction == 1) {
                            PlayerTurn++;
                        }
                    }
                } else {
                    PlayerTurn++;
                }
            } else {
                PlayerTurn++;
            }
        }
        else {
            // BOT CODE HERE
            // =========================================================================================================
            // =========================================================================================================
            PlayerTurn = PlayerTurn % 4; // KEEP TURN ORDER MOVING
            if (!PLayerArray[PlayerTurn].Bankrupt) {
                if (PLayerArray[PlayerTurn].InJail) { // CHECK IF PLAYER IS IN JAIL
                    PLayerArray[PlayerTurn].TurnInJail(PLayerArray, Board, PlayerTurn);
                    PlayerTurn++;
                }
                PLayerArray[PlayerTurn].RollDice(PLayerArray, Board, PlayerTurn, false); // ROLL DICE FOR TURN

                // FOR BOT BANKRUPT CODE HAVE THE BOT CHECK NONMONOPOLIES TO MORTGAGE BEFORE MONOPOLIES
                for (int i = 39; i > 0; i--){ // UNMORTGAGE MONOPOLY PROPS FIRST
                    if (Board[i].isMonopoly && Board[i].OwnerID == PlayerTurn){
                        if (Board[i].isMortgaged && PLayerArray[PlayerTurn].Bal > Board[i].MortgageVal * 2){
                            PLayerArray[PlayerTurn].BOTMortgage(PLayerArray, Board, PlayerTurn, i, false);
                        }
                    }
                }
                for (int i = 39; i > 0; i--){ // UNMORTGAGE REGULAR PROPS AFTER
                    if (Board[i].isMortgaged && PLayerArray[PlayerTurn].Bal > Board[i].MortgageVal * 2){
                        PLayerArray[PlayerTurn].BOTMortgage(PLayerArray, Board, PlayerTurn, i, false);
                    }
                }
                int Scan = 39;
                while (Scan > 0){ // CHECK FOR ANY HOUSES BOT CAN BUY - START WITH HOUSES THAT PLAYERS ARE MOST LIKELY TO LAND ON
                    if (Board[Scan].isMonopoly && Board[Scan].OwnerID == PlayerTurn){
                        Scan = PLayerArray[PlayerTurn].BOTChooseHouseProp(PLayerArray, Board, PlayerTurn);
                        if (Scan == 39){ // IF DARK BLUE
                            if (PLayerArray[PlayerTurn].Bal > 449){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[39].numHouse > Board[37].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 37, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 39, false);
                                }
                            }
                        } // DARK BLUE
                        else if (Scan == 34){ // ELSE IF GREEN
                            if (PLayerArray[PlayerTurn].Bal > 649){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 449){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[34].numHouse > Board[32].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 32, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 31, false);

                                }
                                else if (Board[32].numHouse == Board[31].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 34, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 32, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 31, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 34, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[34].numHouse > Board[32].numHouse){
                                    if (Board[32].numHouse > Board[31].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 31, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 32, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 34, false);
                                }
                            }
                        } // GREEN
                        else if (Scan == 29){ // ELSE IF YELLOW
                            if (PLayerArray[PlayerTurn].Bal > 499){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 349){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[29].numHouse > Board[27].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 27, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 26, false);

                                }
                                else if (Board[27].numHouse == Board[26].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 29, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 27, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 26, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 29, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[29].numHouse > Board[27].numHouse){
                                    if (Board[27].numHouse > Board[26].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 26, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 27, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 29, false);
                                }
                            }
                        } // YELLOW
                        else if (Scan == 24){ // ELSE IF RED
                            if (PLayerArray[PlayerTurn].Bal > 499){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 349){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[24].numHouse > Board[23].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 23, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 21, false);

                                }
                                else if (Board[23].numHouse == Board[21].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 24, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 23, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 21, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 24, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[24].numHouse > Board[23].numHouse){
                                    if (Board[23].numHouse > Board[21].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 21, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 23, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 24, false);
                                }
                            }
                        } // RED
                        else if (Scan == 19){ // ELSE IF ORANGE
                            if (PLayerArray[PlayerTurn].Bal > 349){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[19].numHouse > Board[18].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 18, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 16, false);

                                }
                                else if (Board[18].numHouse == Board[16].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 19, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 18, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 16, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 19, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 159) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[19].numHouse > Board[18].numHouse){
                                    if (Board[18].numHouse > Board[16].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 16, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 18, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 19, false);
                                }
                            }
                        } // ORANGE
                        else if (Scan == 14){ // ELSE IF PINK
                            if (PLayerArray[PlayerTurn].Bal > 349){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 249){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[14].numHouse > Board[13].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 13, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 11, false);

                                }
                                else if (Board[13].numHouse == Board[11].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 14, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 13, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 11, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 14, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 159) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[14].numHouse > Board[13].numHouse){
                                    if (Board[13].numHouse > Board[11].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 11, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 13, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 14, false);
                                }
                            }
                        } // PINK
                        else if (Scan == 9){ // ELSE IF LIGHT BLUE
                            if (PLayerArray[PlayerTurn].Bal > 199){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 149){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD TWO
                                if (Board[9].numHouse > Board[8].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 8, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 6, false);

                                }
                                else if (Board[8].numHouse == Board[6].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 9, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 8, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 6, false);
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 9, false);
                                }
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 99) { // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[9].numHouse > Board[8].numHouse){
                                    if (Board[8].numHouse > Board[6].numHouse) {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 6, false);
                                    }
                                    else {
                                        PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 8, false);
                                    }
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 9, false);
                                }
                            }
                        } // LIGHT BLUE
                        else if (Scan == 3){ // IF PURPLE
                            if (PLayerArray[PlayerTurn].Bal > 149){ // IF ABLE TO AFFORD SET BUY SET
                                PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, Scan, true);
                            }
                            else if (PLayerArray[PlayerTurn].Bal > 99){ // IF NOT CHECK TO SEE IF BOT CAN AFFORD ONE
                                if (Board[3].numHouse > Board[1].numHouse){
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 1, false);
                                }
                                else {
                                    PLayerArray[PlayerTurn].BOTBuyHouse(PLayerArray, Board, PlayerTurn, 3, false);
                                }
                            }
                        } // PURPLE
                    }
                    Scan--;
                }

                /*
                int PropGive; // After turn check if there are any favorable trades for bot to make
                int PropGet;
                bool Traded = false; // Only want bots trading once per turn
                for (int i = 0; i < 40; i++){
                    if (PLayerArray[PlayerTurn].PossibleMonopoly(PLayerArray, Board, PlayerTurn, i, 1) && !Traded && Board[i].Owned){ // IF A BOT WILL GET A MONOPOLY FROM ANOTHER PLAYER'S PROPERTY
                        PLayerArray[PlayerTurn].BOTTrade(PLayerArray, Board, PlayerTurn, i);
                        // BOT TRADE OFFER CODE HERE
                    }
                }*/


                // ADD CHECKS FOR TRADE POSSIBILITIES AND WHATNOT
                // ADD CHECK FOR MONOPOLIES FOR HOUSE BUYING, MAKE FOR LOOP IN REVERSE ORDER TO BUY MOST EXPENSIVE HOUSES FIRST
                sleep_for(1.5s);
                PlayerTurn++;
            } else { // SKIP BANKRUPT PLAYERS TURN
                PlayerTurn++;
            }
            // =========================================================================================================
            // =========================================================================================================
        }
    }


    return 0;
}
