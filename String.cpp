#include "Text.h"

#include <stdlib.h>  //needed for atoi and atof
#include <cstring>   //needed for strlen and strcmp
#include <sstream>
#include <iostream>
using namespace std;

String* createString(const char* char_array)
{
   int sz = strlen(char_array);
   char* text = new char[sz+1];
   for (int i = 0; i < sz; i++)
   {
      text[i] = char_array[i];
   }
   text[sz] = 0;  //null terminator

   String* str = new String;
   str->text = text;
   str->sz = sz;
   return str;
}

int length(String* str)
{
   return str->sz;
}

const char* getText(String* str)
{
   return str->text;
}

int compare(String* str1, String* str2)
{
   return strcmp(str1->text, str2->text);
}

void displayString(String* str)
{
   const char* text = str->text;
   cout << text;
}

void destroyString(String* str)
{
   const char* text = str->text;
   delete[] text;
   delete str;
}

int find(String* str, char delimiter, int start)
{
   int sz = str->sz;
   const char* text = str->text;
   if (start >= sz || start < 0) return -1;

   int loc = sz;
   for (int i = start; i < sz; i++)
   {
      if (text[i] == delimiter)
      {
         loc = i;
         break;
      }
   }

   return loc;
}

//the substring will use the characters from start to end inclusive
String* substr(String* str, int start, int end)
{
   if (start > end || start < 0) return NULL;

   int sz = str->sz;
   if (start > sz || end > sz) return NULL;

   String* sub = new String;
   const char* text = str->text;
   int sub_len = end - start + 1;
   char* sub_text = new char[sub_len + 1];

   int count = 0;
   for (int i = start; i <= end; i++)
   {
      sub_text[count] = text[i];
      count++;
   }
   sub_text[count] = 0;

   sub->text = sub_text;
   sub->sz = sub_len;
   return sub;
}

int a_to_i(String* str)
{
   const char* text = str->text;
   return atoi(text);
}

float a_to_f(String* str)
{
   const char* text = str->text;
   return atof(text);
}

String* i_to_a(int number)
{
   stringstream out;
   out << number;
   const char* text = out.str().c_str();
   return createString(text);
}

String* f_to_a(float number)
{
   stringstream out;
   out << number;
   const char* text = out.str().c_str();
   return createString(text);
}

