/*
  This source code file contains all functions to handle the deck of cards and
  the hands of the players. It also prints out multiple versions of hands and
  the deck
____________________________________________________________________________________
 */



#include "cardHeader.h" // includes all includes / defines / prototypes



/*
  @param char *deck, const char *face, const char *suit
  This function generates a deck of cards in a two dimensional array
  storing the face value and its suit and then printing out the deck
 */
void fillDeck(Card *const deck, const char *face[], const char *suit[])
{
  int count = 0;
  /*Fills the deck with the cards*/
  for(count; count < DECK; count++)
    {
      deck[count].face = face[count % 13]; // %13 to get each face falue
      deck[count].suit = suit[count / 13];// / 13 to get each suit
    }
}



/*
  @param char *deck
  This function takes in the two dimensional deck array and shuffle the values
  in it and then prints out the deck
 */
void shuffle(Card *const deck)
{
  int count = 0;
  int random = 0;
  Card temp;

  for(count; count < DECK; count++)
    {
      random = rand() % DECK;
      temp = deck[count];
      deck[count] = deck[random];
      deck[random] = temp;
    }
}



/*
  @param char *deck, int hands, int cards
  This function takes in the user inputted values for the number
  of hands and the number of cards per hand. The function then distributes
  the allotted number of cards to each hand and prints it.
 */
void deal(Card *const deck, Player *const player, int players)
{
  int count = 0;
  int hand = 0;
  int card = 0;

  for(hand; hand < HAND; hand++)
    {
      for(count; count < players; count++)
        {
          player[count].hand[hand].face = deck[card].face;
          player[count].hand[hand].suit = deck[card++].suit;
        }
      count = 0;
    }

}


/*
  This function prints thr entire deck of cards
 */
void printDeck(Card *const deck)
{
  int count = 0;

  for(count; count < DECK; count++)
    {
      printf("%5s of %-10s\t", deck[count].face, deck[count].suit);

      if(count % 2 == 1)
        {
          printf("\n");
        }
    }

}



/*
  This function prints each players hand
 */
void printHands(Player *const player, int players)
{
  int count = 0;
  int hand = 0;

  for(count; count < players; count++)
    {
      printf("\n\nPlayer %d's hand:\n", count + 1);
      printf("--------------------\n\n");
      for(hand; hand < HAND; hand++)
        {
          printf("%5s of %-10s\n", player[count].hand[hand].face, player[count].hand[hand].suit);
        }
       printf("-------------------\n");
       hand = 0;
    }

}



/*
  This function sorts each hand by face value
 */
void sortHands(Player *const player, int players)
{
  int count = 0;
  int hand = 1;
  int card = 0;
  Card temp;

  for(count; count < players; count++)
    {
      for(card; card < HAND; card++)
        {
        for(hand; hand < HAND; hand++)
          {
            if(strcmp(player[count].hand[card].face, player[count].hand[hand].face) < 0)
              {
                temp = player[count].hand[card];
                player[count].hand[card] = player[count].hand[hand];
                player[count].hand[hand] = temp;
              }
          }
      hand = 0;
        }
      card = 0;
    }
}





/*
  this function prints each hand after its sorted as well as
  assign each hand its rank
 */
void printSortedHands(Player *const player, int players)
{
  int count = 0;
  int hand = 0;

  for(count; count < players; count++)
    {
      printf("\n\nPlayer %d's hand:\t", count + 1);
      if(straightFlush(player, count) == 1)
        {
          printf("Straight Flush");
          }
      else if(fourOfAKind(player, count) == 1)
        {
          printf("Four Of A Kind");
        }
      else if(fullHouse(player, count) == 1)
        {
          printf("Full House");
        }
      else if(flush(player, count) == 1)
        {
          printf("Flush");
        }
      else if(straight(player, count) == 1)
        {
          printf("Straight");
        }
      else if(threeOfAKind(player, count) == 1)
        {
          printf("Three Of A Kind");
        }
      else if(twoPair(player, count) == 1)
        {
          printf("Two Pair");
        }
      else if(onePair(player, count) == 1)
        {
          printf("One Pair");
        }
      else
        {
          printf("High Card");
        }
      printf("\n--------------------\n\n");
      for(hand; hand < HAND; hand++)
        {
          printf("%5s of %-10s\n", player[count].hand[hand].face, player[count].hand[hand].suit);
        }
       printf("-------------------\n");
       hand = 0;
    }

}



/*@return 1 if it is a flush
  This function checks if a hand is a flush or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int flush(Player *const player, int num)
{
  if(player[num].hand[0].suit == player[num].hand[1].suit && player[num].hand[0].suit == player[num].hand[2].suit &&
     player[num].hand[0].suit == player[num].hand[3].suit && player[num].hand[0].suit == player[num].hand[4].suit)
    return 1;
  else
    return 0;
}



/*  @return 1 it if is a four of a kind
  This function checks if a hand has four of a kind or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int fourOfAKind(Player *const player, int num)
{
  if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[0].face == player[num].hand[2].face &&
     player[num].hand[0].face == player[num].hand[3].face)
    return 1;
  else if(player[num].hand[1].face == player[num].hand[2].face && player[num].hand[1].face == player[num].hand[3].face &&
          player[num].hand[1].face == player[num].hand[4].face)
    return 1;
  else
    return 0;
}



/*  @return 1 if it is a full house
  This function checks if a hand is a full house or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int fullHouse(Player *const player, int num)
{
  if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[0].face == player[num].hand[2].face &&
     player[num].hand[3].face == player[num].hand[4].face)
    return 1;
  else if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[2].face == player[num].hand[3].face &&
          player[num].hand[2].face == player[num].hand[4].face)
    return 1;
  else
    return 0;
}



/*  @return 1 if it is a three of a kind
  This function checks if a hand is a three of a kind or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int threeOfAKind(Player *const player, int num)
{
  if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[0].face == player[num].hand[2].face &&
     player[num].hand[3].face != player[num].hand[4].face)
    return 1;
  else if(player[num].hand[0].face != player[num].hand[1].face && player[num].hand[2].face == player[num].hand[3].face &&
          player[num].hand[2].face == player[num].hand[4].face)
    return 1;
  else
    return 0;
}




/*  @return 1 if it is a straight
  This function checks if a hand is a straight or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int straight(Player *const player, int num)
{
  char c1 = player[num].hand[0].face[0];
  char c2 = player[num].hand[1].face[0];
  char c3 = player[num].hand[2].face[0];
  char c4 = player[num].hand[3].face[0];
  char c5 = player[num].hand[4].face[0];

  if(c2 == (c1 + 1) && (c3 == (c2 + 1)) &&
     (c4 == (c3 + 1)) && (c5 == (c4 + 1)))
    return 1;
  else
    return 0;
}



/*  @return 1 if it is a straight flush
  This function checks if a hand is a straight flush or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int straightFlush(Player *const player, int num)
{
  if(straight(player, num) == 1 && flush(player, num) == 1)
    return 1;
  else
    return 0;
}



/*  @return 1 if it is a two pair
  This function checks if a hand is a two pair or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int twoPair(Player *const player, int num)
{
  if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[2].face == player[num].hand[3].face)
    return 1;
  else if(player[num].hand[1].face == player[num].hand[2].face && player[num].hand[3].face == player[num].hand[4].face)
    return 1;
   else if(player[num].hand[0].face == player[num].hand[1].face && player[num].hand[3].face == player[num].hand[4].face)
    return 1;
  else
    return 0;
}



/*  @return 1 if it is a one pair
  This function checks if a hand is a one pair or not.
  The hand ranges from 0 - 4 to check each card in the hand
 */
int onePair(Player *const player, int num)
{
  if((player[num].hand[0].face == player[num].hand[1].face && player[num].hand[2].face != player[num].hand[3].face &&
     player[num].hand[3].face != player[num].hand[4].face) ||
     (player[num].hand[1].face == player[num].hand[2].face && player[num].hand[3].face != player[num].hand[4].face) ||
     (player[num].hand[2].face == player[num].hand[3].face && player[num].hand[0].face != player[num].hand[1].face) ||
     (player[num].hand[3].face == player[num].hand[4].face && player[num].hand[0].face != player[num].hand[1].face &&
      player[num].hand[1].face != player[num].hand[2].face))
    return 1;
  else
    return 0;
}





/*
  This function checks each rank of each hand from all players
  and determines the winners
 */
void winners(Player *const player, int players)
{
  int count = 0;
  int straightF = 0;
  int fourOf = 0;
  int full = 0;
  int flsh = 0;
  int strait = 0;
  int threeOf = 0;
  int two = 0;
  int one = 0;


  for(count; count < players; count++)
    {
      if(straightFlush(player, count) == 1)
        {
          printf("Player %d", count + 1);
          straightF = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(fourOfAKind(player, count) == 1 && straightF == 0)
        {
          printf("Player %d", count + 1);
          fourOf = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(fullHouse(player, count) == 1 && fourOf == 0)
        {
          printf("Player %d", count + 1);
          full = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(flush(player, count) == 1 && full == 0)
        {
          printf("Player %d", count + 1);
          flsh = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(straight(player, count) == 1 && flsh == 0)
        {
          printf("Player %d", count + 1);
          strait = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(threeOfAKind(player, count) == 1 && strait == 0)
        {
          printf("Player %d", count + 1);
          threeOf = 1;
        }
    }
  count = 0;

    for(count; count < players; count++)
    {
      if(twoPair(player, count) == 1 && threeOf == 0)
        {
          printf("Player %d", count + 1);
          two = 1;
        }
    }
  count = 0;

 for(count; count < players; count++)
    {
      if(onePair(player, count) == 1 && two == 0)
        {
          printf("Player %d\n", count + 1);
          one = 1;
        }
    }
 count = 0;

 for(count; count < players; count++)
   {
     if(one == 0)
       {
         printf("Player %d", count + 1);
       }
   }
}