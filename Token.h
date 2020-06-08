#include<iostream>
#include<string>
using namespace std;

enum Token_type {ID, INT, OP, EQ, OpenBrace, CloseBrace, INVALID};

#ifndef TOKEN_H
#define TOKEN_H
class Token
{
   public:
      Token(); // default constructor
      Token(string s); //other constructor

      //MISC FUNCTIONS
      void set(string s);
      int value() const;
      void display() const;


      //GETTER FUNCTIONS
      Token_type get_type() const; //getter for type member
      string get_token() const; //getter for token member
      int get_priority() const; //getter for priority member

   private:
      Token_type type;
      string token;
      int priority;
};
#endif //TOKEN_H

