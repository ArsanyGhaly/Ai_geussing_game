#include "Keyboard.h"
#include <iostream>

int readInt(string prompt)
{
   cout << prompt;
   int val = 0;
   cin >> val;
   return val;
}

int getValidatedInt(string prompt, int min, int max)
{
   int validated = readInt(prompt);
   cout << validated << endl;

   while(validated < min || validated > max)
   {
      validated = readInt(prompt);
      cout << validated << endl;
   }

   return validated;
}

double readDouble(string prompt)
{
   cout << prompt;
   double val = 0;
   cin >> val;
   return val;
}

double getValidatedDouble(string prompt, double min, double max)
{
   double validated = readDouble(prompt);
   cout << validated << endl;

   while(validated < min || validated > max)
   {
      validated = readDouble(prompt);
      cout << validated << endl;
   }

   return validated;
}

String* readString(string prompt)
{
   cout << prompt;
   string text;
   getline(cin, text);

   String* str = createString(text.c_str());
   return str;
}
