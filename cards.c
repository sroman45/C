/*
  Source Code: cards.c && cardHandling.c
       Author: Sergio Roman
   Student ID: 3331168
   Assignment: Program #4 Stud Poker

       Course: COP 4338 Advanced Programming || Programming III
      Section: U04
   Instructor: William Feild
     Due Date: 21 February 2017, at the beginning of class

     I hereby certify that this collective work is my own
     and none of it is the work of any other person or entitiy.

     __________________________

     Language: C
  Compile/run: gcc cards.c cardHandling.c
               ./a.out
 */


#include "cardHeader.h" // contains all includes / defines / prototypes


/*
  This Source Code handles all input validation, struct initializations as well as
  performs all function calls. In addition, per assignment requirements, a function
  was made to generate a preset of cards to test each ranking runction.
*/

int main()
{
  Card deck[DECK];

  int players = 0;
  int hand = 0;
  Player player[players];
  Player test[RANKS];

  //creates an array pointer to store face values
  const char *face[] = {"A", "2", "3", "4", "5",
                 "6", "7", "8", "9", "T",
                 "J", "Q", "K"};

  //creates a pointer array to store suit values
  const char *suit[] = {"Diamonds", "Hearts", "Clubs", "Spades"};

  //gets random numbers by time
  srand(time(NULL));

  printf("Please enter the number of players (1-7):\n");
  players = getNum();

  /*Between 1 & 7 as per assignment specs*/
  while(players < 1 || players > 7)
    {
      printf("You have entered an invalid number of players, please try again:\n");
      players = getNum();
    }

  printf("\nEnter a number for the size of the hand (It will be changd to 5 regardless):\n");
  hand = getNum();

  //function calls
  fillDeck(deck, face, suit);
  printf("\n\nBefore shuffle\n-----------------------------\n");
  printDeck(deck);
  printf("\n\nAfter Shuffle\n-----------------------------\n");
  shuffle(deck);
  printDeck(deck);
  deal(deck, player, players);
  printHands(player, players);
  sortHands(player, players);
  printf("\n\n\nHANDS AFTER SORT\n--------------------------------\n\n");

  printSortedHands(player, players);

  printf("\n\nTHE WINNERS ARE:\n---------------------------------\n\n");
  winners(player, players);

  printf("\n\nWhen you are ready, press any key to run the test function:\n");
  getchar();

  testFunction(test);
  printSortedHands(test, RANKS);

  return NO_ERRORS;
}

/*
  @return num
  This function handles user input to ensure they enter proper
  numerical value
 */
int getNum()
{
  int ch = 0;
  int num = 0;

  while((ch = getchar()) != '\n')
    {
      /*'0' && '9' because those are the only real numbers in ASCII*/
      if((ch >= '0') && (ch <= '9'))
        {
          num *= 10; //*10 to get to next 10th of a number
          num += ch - '0'; // - '0' to convert character into actual number
        }
      else
        {
          printf("\nYou did not enter a proper number! please try again:\n");
          while((ch = getchar()) != '\n')
            {
          ch = getchar();
            }
        }

    }

  return num;

}

/*
  This function generates preset hands to test all ranking functions.
  EACH HAND GOES FROM 0-4 BECACUSE THERE ARE 5 CARDS IN EACH HAND,
  EACH PLAYER GOES FROM 0 - 8 BECAUSE 9 PLAYERS WERE NEEDED TO TEST
  EACH RANKING FUNCTION.
*/
void testFunction(Player *const player)
{
  /*Straight Flush*/
  player[0].hand[0].face = "5";
  player[0].hand[0].suit = "Clubs";
  player[0].hand[1].face = "6";
  player[0].hand[1].suit = "Clubs";
  player[0].hand[2].face = "7";
  player[0].hand[2].suit = "Clubs";
  player[0].hand[3].face = "8";
  player[0].hand[3].suit = "Clubs";
  player[0].hand[4].face = "9";
  player[0].hand[4].suit = "Clubs";

  /* Four of a Kind*/
  player[1].hand[0].face = "5";
  player[1].hand[0].suit = "Clubs";
  player[1].hand[1].face = "5";
  player[1].hand[1].suit = "Diamonds";
  player[1].hand[2].face = "5";
  player[1].hand[2].suit = "Hearts";
  player[1].hand[3].face = "5";
  player[1].hand[3].suit = "Spades";
  player[1].hand[4].face = "9";
  player[1].hand[4].suit = "Clubs";

  /*Full House*/
  player[2].hand[0].face = "K";
  player[2].hand[0].suit = "Clubs";
  player[2].hand[1].face = "K";
  player[2].hand[1].suit = "Hearts";
  player[2].hand[2].face = "K";
  player[2].hand[2].suit = "Spades";
  player[2].hand[3].face = "T";
  player[2].hand[3].suit = "Clubs";
  player[2].hand[4].face = "T";
  player[2].hand[4].suit = "Hearts";

  /*Flush*/
  player[3].hand[0].face = "5";
  player[3].hand[0].suit = "Clubs";
  player[3].hand[1].face = "T";
  player[3].hand[1].suit = "Clubs";
  player[3].hand[2].face = "K";
  player[3].hand[2].suit = "Clubs";
  player[3].hand[3].face = "A";
  player[3].hand[3].suit = "Clubs";
  player[3].hand[4].face = "9";
  player[3].hand[4].suit = "Clubs";

  /*Straight*/
  player[4].hand[0].face = "5";
  player[4].hand[0].suit = "Clubs";
  player[4].hand[1].face = "6";
  player[4].hand[1].suit = "Hearts";
  player[4].hand[2].face = "7";
  player[4].hand[2].suit = "Diamonds";
  player[4].hand[3].face = "8";
  player[4].hand[3].suit = "Spades";
  player[4].hand[4].face = "9";
  player[4].hand[4].suit = "Clubs";

  /*Three of a Kind*/
  player[5].hand[0].face = "5";
  player[5].hand[0].suit = "Clubs";
  player[5].hand[1].face = "5";
  player[5].hand[1].suit = "Hearts";
  player[5].hand[2].face = "5";
  player[5].hand[2].suit = "Diamonds";
  player[5].hand[3].face = "8";
  player[5].hand[3].suit = "Clubs";
  player[5].hand[4].face = "9";
  player[5].hand[4].suit = "Clubs";

  /*Two Pair*/
  player[6].hand[0].face = "5";
  player[6].hand[0].suit = "Clubs";
  player[6].hand[1].face = "5";
  player[6].hand[1].suit = "Diamonds";
  player[6].hand[2].face = "7";
  player[6].hand[2].suit = "Hearts";
  player[6].hand[3].face = "K";
  player[6].hand[3].suit = "Spades";
  player[6].hand[4].face = "K";
  player[6].hand[4].suit = "Clubs";

  /*One Pair*/
  player[7].hand[0].face = "T";
  player[7].hand[0].suit = "Clubs";
  player[7].hand[1].face = "6";
  player[7].hand[1].suit = "Hearts";
  player[7].hand[2].face = "J";
  player[7].hand[2].suit = "Clubs";
  player[7].hand[3].face = "9";
  player[7].hand[3].suit = "Diamonds";
  player[7].hand[4].face = "9";
  player[7].hand[4].suit = "Clubs";

  /*High Card*/
  player[8].hand[0].face = "5";
  player[8].hand[0].suit = "Clubs";
  player[8].hand[1].face = "K";
  player[8].hand[1].suit = "Hearts";
  player[8].hand[2].face = "Q";
  player[8].hand[2].suit = "Hearts";
  player[8].hand[3].face = "2";
  player[8].hand[3].suit = "Diamonds";
  player[8].hand[4].face = "9";
  player[8].hand[4].suit = "Clubs";
}