#include<string>
#include<iostream>
#include<cctype>
#include<cstring>
#include"Token.h"

using namespace std;

//CONSTRUCTORS

      Token::Token() // default constructor bc it has no parameters
      {
         type = INVALID;
         token = "";
         priority = -1;
      }

      Token::Token(string s) //other constructor
      {
         priority = -1; // i need to test with and without this line commented out
         set(s);
      }

//MISC FUNCTIONS
      void Token::set(string s)
      {
         priority = -1; // sets priority to -1 for now
         token = s; // treats s as a token, so token = s;
         // OpenBrace? Priority = 0
         // + or - ? Priority = 1
         // * or / ? Priority = 2
         // IGNORED ClosedBrace

         if (isalpha(s[0])) // if first char is a letter, s is an identifier (ID)
            type = ID;
         else if (isdigit(s[0]) && s[0] != '0') // if the first char is a number and it isn't 0, it is either an INT or INVALID, depending on the length
            {
               bool currentIsDigit;

               for (int i=0; i<s.length(); i++)// goes through each character of 's' to see if that char is a number
               {
                  if (isdigit(s[i]))
                     currentIsDigit = true;
                  else
                  {
                     currentIsDigit = false; // if there is a char that is NOT a number, the bool turns to false and the for loop breaks
                     break;
                  }
               }

               if (currentIsDigit) // if all characters in the string 's' are numbers, the type is an INT
                  type = INT;
               else
                  type = INVALID; // if there is a non-number character in the string 's', the type is INVALID
            }
         else if( (s == "+") || (s == "-") || (s == "*") || (s == "/") ) // if string 's' is a single char of any of these operations, the type is OP
            {
               type = OP;
               if(s == "+" || s == "-")
                  priority = 1;
               else if(s == "(")
                  priority = 0;
               else if(s == "*" || s == "/")
                  priority = 2;
            }
         else if (s == "=") // if the string 's' is the single character '=', the type is EQ
            type = EQ;
         else if (s == "(") // if the string 's' is the single character '(', the type is OpenBrace
            type = OpenBrace;
         else if (s == ")") // if the string 's' is the single character ')', the type is CloseBrace
            type = CloseBrace;
         else if (s == "0") // if the string 's' is the single character '0', then the type is INT
            type = INT;
         else
            type = INVALID; // if none of the above situations are true, the type is INVALID
      }

int ToInt(string s)
{
        int i, n=0;
        for(i=0; s[i] >= '0' && s[i]<= '9'; i++)
        {
           n = n*10 + (s[i] - '0');
        }
        return n;
}


      int Token::value() const
      {
         if (type == INT)
         {
            int int1 = ToInt(token);
            return int1;
         }
         else if (type == ID)
            return -1;
         else
            return -2;
      }

      void Token::display() const
      {
         cout << endl;
         cout << "Type = " << get_type() << endl;
         cout << "Token = " << get_token() << endl;
         cout << "Priority = " << get_priority() << endl;
      }

//GETTER FUNCTIONS
      Token_type Token::get_type() const //getter for type member
      {
         return type;
      }

      string Token::get_token() const //getter for token member
      {
         return token;
      }

      int Token::get_priority() const //getter for priority member
      {
         return priority;
      }

