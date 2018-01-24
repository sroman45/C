#include <stdio.h>
#include <time.h> /*used for the srand to generate different random numbers at different times */
#include <string.h> /* used for strcmp in the srt function*/
#include <stdlib.h> /*Used for the rand() function*/
//defines
#define NO_ERRORS 0
#define DECK 52
#define HAND 5
#define RANKS 9

/*creates a struct for a deck of cards*/
struct card
{
  const char *face;
  const char *suit;
};

typedef struct card Card;

/*Creates a struct for each player which contains a ahnd each*/
struct player
{
  Card hand[HAND];
};

typedef struct player Player;

//Function Prototypes
void fillDeck(Card *const deck, const char *face[], const char *suit[]);
void shuffle(Card *const deck);
void deal(Card *const deck, Player *const player, int players);
void printDeck(Card *const deck);
void printHands(Player *const player, int players);
void printSortedHands(Player *const player, int players);
void sortHands(Player *const player, int players);
void sortHelper(const char *face);
int straightFlush(Player *const player, int num);
int fourOfAKind(Player *const player, int num);
int fullHouse(Player *const player, int num);
int flush(Player *const player, int num);
int straight(Player *const player, int num);
int threeOfAKind(Player *const player, int num);
int twoPair(Player *const player, int num);
int onePair(Player *const player, int num);
void winners(Player *const player, int players);
void testFunction(Player *const player);