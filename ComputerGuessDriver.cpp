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

//------------------------------------------------------------------
//Get the name of the text file and read the range from the file 
//(range is an int array of size 2 )
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
//------------------------------------------------------------------
//obtain a randomly genrated secret number inside the ranage 
//
//------------------------------------------------------------------
int getSecret(int* range){
   randomInit();
   //get the random number from the max and min in the ranage
  int secret= getRandomInt(range[0],range[1]);
  return secret;
}


//-----------------------------------------------------------
//obtin the guess and ask again if it out of the range
//------------------------------------------------------------
int getGuess(int min,int max){

    //convert the string to int 
    int uGuess=(max + min) / 2;   
   return uGuess;
   
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
   int max =range[1];
   int min =range[0]; 
   int guess;
   while (result != EXACT  && max >= min) 
   {
      guess=getGuess(min,max);
     result= processGuess(guess,secret);
         if (result == TOO_HIGH)
         {
           String* m = createString("Too hight\n");
           displayString(m);  
           destroyString(m);
           max  = guess - 1;
   
          }
         else if (result == TOO_LOW)
         {
            String* m = createString("Too low\n");
            displayString(m);
            destroyString(m);
            min  = guess + 1;
        
         }
         else {
            break;
         }
      //increase the guesses
       flag+=1;
        
   }
  cout<<"THE compter right guess was :" << guess <<endl;
   return flag;
}


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
     

      cout << "The computer  got it in " << total_guess << " guesses!" << endl;
    
      ready_str = readString("Are you ready to play? (y/n) ");
   }

   destroyString(ready_str);
   destroyString(n);
   return 0;
}
