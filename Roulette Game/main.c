//
//  main.c
//  Roulette Game
//
//  Created by Ibraheem Nadeem on 11/6/14.
//  This is the roulette program. This game will have a user enter bet information and then a random number will be rolled, and if it corresponds with the bet options, they either win or lose
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Prototypes:
void displayInstructions ();
float getBetAmount ();
int makeBet (int *);
int spinWheel ();
float figureWinnings (float, int, int, int);



int main(int argc, const char * argv[])
{
    
    //Variables
    
    float betamount, winningAmount;
    int makeBetChoice;
    int numberBet, randomNumber;
    char playAgain;
    //---------------------------------------------
    
    // Call function to display the instructions
    displayInstructions();
    
    // Do loop the repeats if user wants to play again. Contains functions to get the bet type and other bet information along with the winnings
    do {
        
        betamount = getBetAmount();
        numberBet = makeBet(&makeBetChoice);
        randomNumber = spinWheel();
        printf("\n***********************************************\n");
        printf("\nThe Number that it landed on is... %d\n", randomNumber);
        winningAmount = figureWinnings(betamount,numberBet,randomNumber,makeBetChoice);
        printf("\n\n***********************************************");

        printf("\n\nWould you like to play again? Enter: \nY\nN");
        scanf("\n%c", &playAgain);


    } while (playAgain =='Y' || playAgain =='y');
    
    //End thank you message if they decide not to play again.
    printf("\nThank you for playing!");
    
    return 0;
}

// Functions:

// ---------------------------------------------------------------------------------------
// Function that displays Welcome message along with Instructions
void displayInstructions ()

{
    printf("--------------------------------------------------------------------     \n");
    printf("*******  ******   *      *  *      ****** ******* *******  ****** \n");
    printf("*     * *      *  *      *  *      *         *       *     *        \n");
    printf("******* *      *  *      *  *      *         *       *     *        \n");
    printf("*   *   *      *  *      *  *      ****      *       *     ****        \n");
    printf("*    *  *      *  *      *  *      *         *       *     *        \n");
    printf("*     *  ******    ******   ****** ******    *       *     ******        \n");
    printf("---------------------------------------------------------------------     \n");
    printf("\n");
    
    printf("Welcome to Roulette!\n\n");
    printf("You can place your bet in one of three ways:\n\n");
    printf("\t\t i.   Bet on a number (payout is 36 times the bet amount)\n");
    printf("\t\t ii.  Bet on an odd or even (payout is 2 times the bet)\n");
    printf("\t\t iii. Bet on a dozen ~ first 1-12, second 13-24, third 25-36 (payout is 3 times the bet)\n\n");
    
    printf("** The number ZERO does not count for odd or even, but counts as a number bet **\n");

    printf("---------------------------------------------------------------------     \n");

}

// ---------------------------------------------------------------------------------------
// Function to get the bet amount from the user
float getBetAmount ()

{
    float betamount;
    
    printf("\n\nPlease enter the amount of money you would like to bet: $");
    scanf("%f", &betamount);
    
// Keeps asking the user if the bet amount entered is below or equal 0 --> While loop
    
    while (betamount <=0)
    {
        printf("Invalid amount");
        printf("\n\nPlease enter the amount of money you would like to bet: $");
        scanf("%f", &betamount);
    }
    
    return betamount;

}

// ---------------------------------------------------------------------------------------
//Function that while ask user all the relevant information in regards to their bet choice

int makeBet (int *makeBetChoice)

{
    
    int numberBet = 0;
    int validBet;
    
    // Do loop will keep asking user if they enter a bet choice less than 0 or greater than 3
    
    do {
   
    printf("Please enter the type of bet you would like to make: \n");
    printf("1:\t Number Bet\n");
    printf("2:\t Even/Odd Bet\n");
    printf("3:\t Dozen Bet\n");
    scanf("%d", &*makeBetChoice);
    
    } while ((*makeBetChoice!=1) && (*makeBetChoice!=2)&&(*makeBetChoice!=3));

    // Switch Statement that will store relevant bet information.
    do {
        
    switch (*makeBetChoice)
    {
        case 1:
            printf("Please enter the number that you would like to place your bet on (0-36): ");
            scanf("%d", &numberBet);
            if (numberBet >=0 && numberBet <=36)
                {
                    validBet = 1;
                }
            else
                {
                    validBet = 0;
                    printf("Invalid Number!\n");
                }
            break;
            
        case 2:
            printf("Enter 1 to bet on an odd number or 2 for an even number:  ");
            scanf("%d", &numberBet);
            if (numberBet ==1 || numberBet ==2)
                {
                    validBet=1;
                }
            else
                {
                    validBet =0;
                    printf("Invalid Choice!\n");
                }
            break;
            case 3:
            // Will make it that if the user enters first dozen, then make that =3,2nd dozen = 4 and so on
                printf("Please select which dozen you would like to bet on: ");
                printf("\n1 : First dozen (1-12) \n");
                printf("2: Second dozen (13-24) \n");
                printf("3: Third dozen (25-36)\n");
                scanf("%d", &numberBet);
                if (numberBet >=1 && numberBet<=3)
                {
                    validBet =1;
                
                    if (numberBet ==1)
                    {
                        numberBet =3;
                    }
                    
                    else if (numberBet==2)
                    {
                        numberBet=4;
                    }
                    else if (numberBet ==3)
                        numberBet =5;
                
                }
                else
                {
                    validBet = 0;
                    printf("Invalid Choice!\t");
                }
            
            break;
            default: printf("You entered an invalid betting option!");
                        validBet = 0;
            break;
            
    }
    } while (validBet ==0);

    // Will return the numberBet
    return numberBet;
}
// ---------------------------------------------------------------------------------------

int spinWheel ()
// Function will generate a random number and then put that into the variable random number which will then be returned
{
    int randomNumber;
    
    srand(time(NULL));

    randomNumber = ((rand()%36)+1);
    
    return randomNumber;

}

// ---------------------------------------------------------------------------------------
// This function will calculate all of the winnings or losses
float figureWinnings (float betamount, int numberBet, int randomNumber, int makeBetChoice)

{

    float winningAmount;
    
    switch (makeBetChoice) {
        case 1: // If user enters one for a number bet. If random nmber==#bet, they win 36X amount bet
            if (randomNumber == numberBet)
            {
                winningAmount = betamount *36;
                printf("Congrats! you won! Your new balance is: $%0.2f", winningAmount);
            }
            else
            {
                winningAmount = 0;
                printf("Sorry, you lost! Your new balance is: $%0.2f", winningAmount);
            }
            break;
        case 2:
            if ((numberBet ==1 && (randomNumber%2!=0)) || (numberBet ==2 &&(randomNumber%2==0)))
            {
                winningAmount = betamount *2;
                printf("Congrats! you won! Your new balance is: $%0.2f", winningAmount);
            }
            else
            {
                winningAmount = 0;
                printf("Sorry, you lost! Your new balance is: $%0.2f", winningAmount);

            }
            break;
        case 3:
            //printf("*************%d\n", numberBet);
            
            //printf("-------------%d\n", randomNumber);
            
            if ((numberBet ==3) && ((randomNumber >=1) && (randomNumber<=12))&&(randomNumber !=0))
            {
                winningAmount = betamount *3;
                printf("Congrats! you won! Your new balance is: $%0.2f", winningAmount);
            }
            
            else if ((numberBet ==4) && ((randomNumber >=13) && (randomNumber<=24)) && (randomNumber !=0))
            {
                winningAmount = betamount *3;
                printf("Congrats! you won! Your new balance is: $%0.2f", winningAmount);
            }
            else if ((numberBet ==5) && ((randomNumber >=25) && (randomNumber<=36)) && (randomNumber !=0))
            {
                winningAmount = betamount *3;
                printf("Congrats! you won! Your new balance is: $%0.2f", winningAmount);
            }
            
            else
            {
                winningAmount = 0;
                printf("Sorry, you lost! Your new balance is: $%0.2f", winningAmount);
                
            }
        default:
            break;
    }

    return winningAmount;

}