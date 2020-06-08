#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include"Expression.h"
using namespace std;


//BOOLEAN FUNCTION TO CHECK IF THERE IS A MISSING SEMI-COLON AT THE END OF THE EXPRESSION
//RETURNS TRUE IF THERE IS A SEMI-COLON
//RETURN FALSE IF THERE IS NOT
bool check(string original)
{
   int inputLen = original.size();
   if(original[inputLen-1] == ';')
      return true;
   else
      return false;
}

//VOID FUNCTION TO ALLOW FOR MULTIPLE EXPRESSIONS TO BE INPUT
//USE THE SEMI-COLON AS A DELIMITER OF SORTS
void separate(string inputString, vector<Expression> &inputVector) // to allow for multiple expressions to be input at once
{
   if(inputString[inputString.length() - 1] != ';') // IF THERE IS A SEMI-COLON AT END OF INPUT EXPRESSION, ADD TO inputVector
   {
      cout << "missing ; at the end error!\n";
      string temp;
      int i=0;
      while(inputString[i] != '\0')
      {
         temp.push_back(inputString[i]);
         i++;
      }
      Expression other;
      temp.push_back(';');
      other.set(temp);
      other.syntaxCheck();
      inputVector.push_back(other);

   }
   else // IF THERE IS NOT A SEMI-COLON, SPIT OUT ERROR
   {
      int i=0;
      while(inputString[i] != '\0')
      {
         if(inputString[i] == ';') // if position holds a ';' value
         {
           //DO NOTHING
         }
         else // inputString[i] is not a semi-colon (;)
         {
            string temp;
            //temp.push_back(inputString[i]);
            while(inputString[i] != ';')
            {
               temp.push_back(inputString[i]);
               i++;
            }
            Expression other; // Expression other;
            temp.push_back(';');
            other.set(temp);
            other.syntaxCheck();
            inputVector.push_back(other);
         }
         i++;
      }
   }
}

int main()
{

   cout << "\n=== expression evaluation program starts === \n";

   vector<Expression> inputVector;
   string inputString;
   string action;
   Expression inputExpression;

   //USER INPUT
   //IF MORE THAN ONE EXPRESSION AT ONCE, SEPARATE FUNCTION TAKES CARE OF TURNING EACH INPUT EXPRESSION INTO
   //AN EXPRESSION OBJECT AND THEN ADDED TO THE inputVector VECTOR OF EXPRESSIONS
   cout << "input: ";
   getline(cin, inputString);
   separate(inputString, inputVector);


   cout << "action: ";
   cin >> action;
   cin.ignore();

   //ACTION INPUT
   //IF ACTION IS NOT ONE OF THE ONES GIVEN BELOW, THIS WHILE LOOP WILL KEEP ASKING FOR A SUITABLE ACTION INPUT
   while(action[0] != '=' && action[0] != '<' && action[0] != '>' && action[0] != 'q' && action[0] != 'Q' && action[0] != 'f' && action[0] != 'F' && action[0] != 'c' && action[0] != 'C' && action[0] != 's' && action[0] != 'S')
   {
      cout << "Wrong input for the action! Please type one of =, <, >, f(F), q(Q), c(C), s(S)\n";
      cout << "action: ";
      cin >> action;
   }

   //MAIN PROGRAM
   //WHILE THE ACTION IS SOMETHING OTHER THAN q or Q, THIS WHILE LOOP WILL KEEP RUNNING.
   //THE SWITCH(ACTION) CASES TAKE CARE OF THE ACTION INPUTS FROM USER
   while(action[0] != 'q' && action[0] != 'Q')
   {
      Expression temp;

      switch(action[0])
      {
         case '=': // EVALUATION CASE
            // IF ACTION IS '=' THEN THE PROGRAM GOES THROUGH THE inputVector VECTOR OF EXPRESSIONS AND EVALUATES EACH ONE INDIVIDUALLY.
            // PROVIDED IT IS OF TYPE ARITHMETIC
            for(int i=0; i<inputVector.size(); i++)
            {
               inputVector[i].syntaxCheck(); // CHECKS THE SYNTAX OF EACH EXPRESSION, TELLS WHETHER IT IS ILLEGAL, ASSIGNMENT, OR ARITHMETIC
               string temp = inputVector[i].get_original();
               temp.pop_back();
               if(inputVector[i].other_get_type() == arithmetic) // IF ARITHMETIC, EVALUATES
               {
                  cout << temp << " = " << inputVector[i].evaluate() << endl;
               }
               else // IF NOT ARITHMETIC, CANNOT EVALUATE
               {
                  cout << "cannot evaluate " << temp  << " which is";
                  inputVector[i].output_type();
               }
            }
         break;

         case '<': // POSTFIX CASE
            // IF ACTION IS '<' THEN THE PROGRAM GOES THROUGH THE inputVector VECTOR OF EXPRESSIONS AND TURNS INFIX TO POSTFIX FOR EACH
            // EXPRESSION INDIVIDUALLY, PROVIDED IT IS OF TYPE ARITHMETIC.
            for(int i=0; i<inputVector.size(); i++)
            {
               inputVector[i].syntaxCheck();
               string temp = inputVector[i].get_original();
               temp.pop_back();
               if(inputVector[i].other_get_type() == arithmetic) // IF TYPE IS ARTIHMETIC, POSTFIX EXPRESSION
               {
                  cout << "postfix of " << temp  << " is: ";
                  inputVector[i].infixToPostfix();
                  inputVector[i].printPostfix();
               }
               else // IF NOT ARITHMETIC, CANNOT POSTFIX EXPRESSION
               {
                  cout << "no postfix for " << temp << " which is";
                  inputVector[i].output_type();
               }
            }
         break;

         case '>': // PREFIX CASE
            // IF ACTION IS '>' THEN THE PROGRAM GOES THROUGH THE inputVector VECTOR OF EXPRESSIONS AND TURNS INFIX TO PREFIX FOR EACH
            // EXPRESSION INDIVIDUALLY, PROVIDED IT IS OF TYPE ARITHMETIC
            for(int i=0; i<inputVector.size(); i++)
            {
               inputVector[i].syntaxCheck();
               string temp = inputVector[i].get_original();
               temp.pop_back();
               if(inputVector[i].other_get_type() == arithmetic) // IF TYPE IS ARITHMETIC, PREFIX EXPRESSION
               {
                  cout << "prefix of " << temp << " is: ";
                  cout << inputVector[i].prefixBoi() << endl;
               }
               else // IF NOT ARITHMETIC, CANNOT PREFIX EXPRESION
               {
                  cout << "no prefix for " << temp << " which is";
                  inputVector[i].output_type();
               }
            }
         break;

         case 'f':case 'F': // FULLY PARENTHESIZING CASE
            // IF ACTION IS 'f' or 'F' THEN THE PROGRAM GOES THROUGH THE inputVector VECTOR OF EXPRESSIONS AND FULLY PARENTHESIZES
            // EACH EXPRESSION INDIVIDUALLY, PROVIDED IT IS OF TYPE ARITHMETIC
            for(int i=0; i<inputVector.size(); i++)
            {
               inputVector[i].syntaxCheck();
               string temp = inputVector[i].get_original();
               temp.pop_back();
               if (inputVector[i].other_get_type() == arithmetic) // IF TYPE IS ARITHMETIC, FULLY PARENTHEISZE EXPRESSION
               {
                  cout << "fully parenthesizing "<< temp  << " is: ";
                  cout << inputVector[i].parenthesize() << endl;
               }
               else // IF NOT ARITHMETIC, CANNOT FULLY PARENTHESIZE
               {
                  cout << "no fully parenthesizing of " << temp << " which is";
                  inputVector[i].output_type();
               }
            }
         break;

         case 'c':case 'C': // CONTINUE CASE
            // IF ACTION IS 'c' or 'C' THEN THE PROGRAM ASKS FOR ANOTHER INPUT EXPRESSION FROM THE USER
            // THE SEPARATE FUNCTION IS CALLED IN CASE THERE ARE MORE THAN ONE EXPRESSIONS BEING INPUT AT ONCE
            // THE SEPARATE FUNCTION ALSO TAKES CARE OF INSERTING EACH EXPRESSION INDIVIDUALLY INTO THE inputVector
            cout << "input: ";
            getline(cin, inputString);
            separate(inputString, inputVector);
         break;

         case 's':case 'S': // START OVER CASE
            // IF ACTION IS 's' or 'S' THEN THE PROGRAM CLEARS THE WHOLE inputVector VECTOR OF EXPRESSIONS
            // THEN THE PROGRAM ASKS FOR ANOTHER INPUT EXPRESSION(S) FROM THE USER AND ADDS IT TO THE inputVector
            inputVector.clear();
            cout << "input: ";
            getline(cin, inputString);
            separate(inputString, inputVector);
         break;

         default: // DEFAULT CASE
            // IF THE USER INPUTS AN ACTION THAT IS NOT VALID, THEN THE PROGRAM KEEPS ASKING FOR A VALID ACTION FOR ANY OF THE OTHER CASES TO WORK
            cout << "Wrong input for the action! Please type one of =, <, >, f(F), q(Q), c(C), s(S)\n";
         break;

      }
      // LAST CALL FOR ACTION INPUT
      // IF ACTION IS 'q' or 'Q' THEN THE WHILE LOOP WILL END AND THE PROGRAM WILL TERMINATE
      cout << "action: ";
      cin >> action;
      cin.ignore();
   }
   cout << "\n=== expression evaluation program ends ===\n";

   return 0;
}




