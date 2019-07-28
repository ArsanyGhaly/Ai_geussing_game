#if !defined (GUESS_ENUM)
#define GUESS_ENUM
   enum GuessEnum {EXACT, TOO_LOW, TOO_HIGH};
#endif

#include "Text.h"
#include "ReadFile.h"
#include "Random.h"
#include "Keyboard.h"

#include <iostream>
using namespace std;

//insert your methods here
int getSecret (int* range); //Obtain a randomly generated secret number inside the range
int* getRange(); //Get the name of the text file and read the range from the text file. (range is an int array of size 2, dynamically allocated using new, delete pointers when finished with them)
int getGuess (int* range); //Obtain a guess (ask again if guess is not in range)
GuessEnum processGuess (int guess, int secret); //determine whether a guess is correct. Return EXACT, TOO_HIGH or TOO_LOW
int play (int* range, int secret); //Loops until the secret number has been guessed and returns the total number of guesses required (calls getGuess and processGuess)


int main()
{
   String* n = createString("n");
   String* ready_str = readString("Are you ready to play? (y/n) ");

   while (compare(n, ready_str) != 0)
   {
      destroyString(ready_str);

      //DO THIS
     int*range= getRange();
     int secret=getSecret(range);
     int total_guess= play (range,secret);


      cout << "You got it in " << total_guess << " guesses!" << endl;
  
      ready_str = readString("Are you ready to play? (y/n) ");
   }



   destroyString(ready_str);
   destroyString(n);
   return 0;
}


//------------------------------------------------------------------
//Get the name of the text file and read the range from the file
//(range is an int array of size 2 ) and then returned as array
//------------------------------------------------------------------
int *getRange(){

     //ask for the name of the file
      String*fileName=readString("Enter the file name containing the range for the secret number: ");

      //convert the string to chars
      const char* fName=getText(fileName);

      //read the file
      ReadFile* file=createReadFile(fName);

      if (!eof(file))
      {
        //read the lins of the file
               String* min=readLine(file);
               String* max=readLine(file);
         //make a new pointer to store the array
           int *range;
           range=new int[2];
           range[0]= a_to_i(min);
           range[1]= a_to_i(max);
         //return the array adress
            destroyString(min);
            destroyString(max);
         return range;
      }
    else
      {
         destroyReadFile(file);
      }


}

//-----------------------------------------------------------
//obtin the guess and ask again if it out of the range
//ask for a guess and check if it in the ranage ask again
//then return the user geuess
//------------------------------------------------------------
int getGuess(int*	range){

    String*guess=readString("Please Enter Your Guess: ");
    //convert the string to int
    int uGuess=a_to_i(guess);

    //check if the guess is in the range or no
    while (uGuess > range[1] || uGuess < range[0]){
       String*guess=readString("Out of the range!!Please Enter Your Guess again: ");
       uGuess=a_to_i(guess);
    }


   return uGuess;

}

//------------------------------------------------------------------
//obtain a randomly genrated secret number inside the ranage
//get the max and the min from the range array where the first element
//is the min and the second element is the max
//------------------------------------------------------------------
int getSecret(int* range){
   randomInit();
   //get the random number from the max and min in the ranage
  int secret= getRandomInt(range[0],range[1]);
   return secret;
}

//-------------------------------------------------
//determine if the guess is heigher, lower or exact
//--------------------------------------------------
GuessEnum processGuess (int guess,	int secret)	{

   if (guess > secret)
   {
      return TOO_HIGH;
   }
   else if (guess < secret)
   {
      return TOO_LOW;
   }
   else
   {
     return EXACT;
   }
}

//----------------------------------------------------------------
//loop  untile the secret number has been guessed and returns the total
//number of guesses requied
//----------------------------------------------------------------------
int play	(int*	range,	int	secret)	{
 //to hold how many guess
   int flag=1;
   //hold the result of testing the guess
   int result;

   while (result != EXACT )
   {
     int guess=getGuess(range);
      result= processGuess(guess,secret);
         if (result == TOO_HIGH)
         {
           String* m = createString("Too hight\n");
           displayString(m);
           destroyString(m);

          }
         else if (result == TOO_LOW)
         {
            String* m = createString("Too low\n");
            displayString(m);
            destroyString(m);
         }
         else {
              break;
         }
      //increase the guesses
       flag+=1;
   }

   return flag;
}
