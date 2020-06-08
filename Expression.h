#ifndef EXPRESSION_H
#define EXPRESSION_H

#include<iostream>
#include<string>
#include<vector>
#include"Token.h"

using namespace std;

enum Exp_type {assignment, arithmetic, illegal};

class Expression
{
   public:
      Expression(); //default constructor
      Expression(const string &s); //other constructor
   
      //MISC FUNCTIONS
      void set(const string &s);
      void display() const;

      //GETTER FUNCTIONS
      string get_original() const; //getter for original member
      vector<Token> get_tokenized() const; //getter for tokenized member

      //PUBLIC MEMBERS
      vector<Token> postfix;
      Exp_type type;


      void infixToPostfix();
      string parenthesize();
      void syntaxCheck();
      void output_type();
      string prefixBoi();
      int evaluate();
      void printPostfix();
      void tokenizeMethod();
      Exp_type other_get_type();

      bool check(string original)
      {
         int inputLen = original.size();
         if(original[inputLen-1] == ';')
         {
            return true;
         }
         else
         {
            return false;
         }
      }

   private: 
      string original; 
      vector<Token> tokenized;
      bool valid;

   
};
#endif //EXPRESSION_H