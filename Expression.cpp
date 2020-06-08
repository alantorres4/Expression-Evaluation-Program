#include"Expression.h"
#include<stack>
#include<string>

#include<utility>
#include<algorithm>

vector<string> IDVector; // VECTOR OF IDENTIFIERS 
vector<string> IDValues; // VECTOR OF INT VALUES FROM THE IDENTIFIERS IN ASSIGNMENTS
int pos; // POSITION OF IDVALUE RELATIVE TO ITS IDVECTOR COUNTERPART 

   Expression::Expression() //default constructor
   {
      original = "";
      tokenized.clear();//clears all elements from tokenized vector.
      postfix.clear();//clears all elements from postfix vector
      valid = false;
      type = illegal;
   }

   // FUNCTION TO REMOVE SPACES FOR EASIER MANIPULATION OF EXPRESSIONS
   string removeSpaces(string str) 
   { 
      char space = ' ';
      str.erase(remove(str.begin(), str.end(), space), str.end()); 
      return str; 
   } 

   // BOOLEAN FUNCTION USED IN EVALUATE() METHOD 
   // USED TO "SWITCH" BETWEEN IDENTIFIERS AND THEIR INTEGER COUNTERPARTS 
   // IFF THE IDENTIFIER MATCHES ANY OF THE IDENTIFIERS IN THE IDVector 
   bool assignmentCheck(string token)
   {
      pos = 0;
      for(int i=0; i < IDVector.size(); i++)
      {
         if(token == IDVector[i])
         {
            return true; // RETURNS TRUE IF TOKEN ID WAS FOUND IN IDVector VECTOR OF STRINGS 
         }
         pos++; // POSITION IN THE IDValue WHERE THE IDVector ASSIGNED VALUE WILL BE 
      }
      return false; // RETURNS FALSE IF NONE OF THE IDENTIFIERS IN THE IDVector MATCH THE token STRING
   }

int stringToInt(string s)
{
        int i, n=0;
        for(i=0; s[i] >= '0' && s[i]<= '9'; i++)
        {
           n = n*10 + (s[i] - '0');
        }
        return n;
}

   int Expression::evaluate()
   {
      if (postfix.empty())
         infixToPostfix();
   
      if (tokenized.empty())
         tokenizeMethod();
      
      stack<int> numbers;
      for(int i=0; i<postfix.size(); i++)
      {
         string token = postfix[i].get_token();
         if(postfix[i].get_type() == ID) 
         {
            if( assignmentCheck(postfix[i].get_token()) )
            {
               // IF THE postfix[i].get_token() Token MATCHES WITH A Token IN THE IDVector, THEN REPLACE token WITH THE
               // ASSIGNED VALUE IN THE IDValue VECTOR AT POSITION 'POS'
               token = IDValues[pos];
            }
         }


         if(postfix[i].get_type() == OP) // IF OPERATOR, TAKE TWO ELEMENTS FROM TOP OF STACK AND EVALUATE USING THE OPERATOR 
         {
            int value;
            int rightValue = numbers.top();
            numbers.pop();
            int leftValue = numbers.top();
            numbers.pop();

            if(token == "+")
               value = leftValue + rightValue;
            else if(token == "-")
               value = leftValue - rightValue;
            else if (token == "*")
               value = leftValue * rightValue;
            else if (token == "/")
            {
               if(rightValue == 0)
               {
                  cout << " no result, divide by zero error!";
                  return 0;
               }
               else
                  value = leftValue / rightValue;
            }
            else
               cout << "\nINSIDE EVALUATE, THIS SHOULD NOT OUTPUT...\n";

            numbers.push(value);
         }
         else if(postfix[i].get_type() == INT || postfix[i].get_type() == ID) // IF ID OR INT, PUSH STOI() VALUE ONTO STACK 
         {
            int number = stringToInt(token);
            numbers.push(number);
         }
      }
      // AFTER FINSIHED, RETURNS THE LAST VALUE FROM TOP OF STACK OF INTEGERS WHICH SHOULD BE THE EVALUATION OF THE WHOLE EXPRESSION
      return numbers.top(); 
   }

   void Expression::tokenizeMethod()
   {
      string infix = original;
      infix[infix.length()-1] ='\0'; // gets rid of semi-colon
      infix = removeSpaces(infix); // infix now has no spaces 
      int i = 0;
      bool eqInString = false;

      while(infix[i] != '\0')
      {
         if(infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '(' || infix[i] == ')' || infix[i] == '=') // if position holds an operator value
         {
            if(infix[i] == '=')
               eqInString = true;

            string temp;
            temp.push_back(infix[i]);

            Token other;
            other.set(temp);

            tokenized.push_back(other);
            i++;
         }
         else
         {
         //infix[i] is not an operator
            string temp;
            while(isdigit(infix[i]) || isalpha(infix[i]))
            {
               temp.push_back(infix[i]);
               i++;
            }
            Token other;
            other.set(temp);
            tokenized.push_back(other);
         }
      }
      if(eqInString)
      {
         type = assignment;
      }
      // }

   }

   void Expression::syntaxCheck()
   {
      if(tokenized.empty()) // if tokenized has not been intialized yet, call it!
         tokenizeMethod();
      if(postfix.empty())
         infixToPostfix();
      //example: a=5;
      // if(check(original))
      // {
      // update valid boolean variable
      enum States {expect_operand, expect_operator, done};
      bool eqTrue = false; 
      States state = expect_operand;
      int pCount = 0;
      valid = true;

      for(int i =0; state != done && i < tokenized.size(); i++)
      {
         Token t = tokenized[i]; // do i need to add  get_token()?
         switch(state)
         {
            case expect_operand: 
               if (t.get_type() == OpenBrace)
                  pCount++;
               else if (t.get_type() == INT || t.get_type() == ID)
               {
                  state = expect_operator;
               }
               else // invalid exp due to wrong or invalid type
               {
                  valid = false;
                  state = done;
               }
               break;
            case expect_operator: 
               if(t.get_type() == CloseBrace)
               {
                  pCount--;
                  if(pCount < 0)
                  {
                     valid = false;
                     state = done;
                  }
               }
               else if( t.get_type() == EQ)
               {
                  eqTrue = true;
                  state = expect_operand;
               }
               else if(t.get_type() == OP)
               {
                  state = expect_operand;
               }
               else // invalid exp due to wrong OR invalid type
               {
                  valid = false;
                  state = done;
               }
               break;
            default: 
               break; // we should not reach here!
         }
      }
         // after the loop making sure the braces are balanced!
         if (pCount != 0)
            valid = false;
         // missing last operand case
         if (state == expect_operand)
            valid = false;
         if (valid)
         {
            if(eqTrue)
            {// MAYBE CHANGE == 3 TO == 4  to include the semi-colon
               if (tokenized[0].get_type() == ID && tokenized[1].get_type() == EQ && tokenized[2].get_type() == INT) // took away tokenized.size() == 3
               {
                  type = assignment;
                  IDVector.push_back(tokenized[0].get_token()); // puts tokenized[0] string into the IDVector vector of strings
                  IDValues.push_back(tokenized[2].get_token()); // puts tokenized[2] number into IDValue vector of ints
               }
               else 
                  valid = false;
            }
            else
            {
               type = arithmetic;
               //may obtain postfix here or in the set method after check
            }
         }
      // }

      // }
      // else
      // {
      //    cout << "missing ; error!\n";
      // }
   }

   int priority(char n) 
   {
      int order = 0;
      if (n == '*' || n == '/')
         order = 2;
      else if (n == '(')
         order = 0;
      else if (n == '+' || n == '-')
         order  = 1;
   
      return order;
   }   
   

   void Expression::infixToPostfix()
   {
      if(check(original))
      {
         if(postfix.empty())
         {
            stack<Token> ops;
            if(tokenized.empty())
               tokenizeMethod();

   
            for(int i=0; i<tokenized.size(); i++) //For each token in the correct infix expression do
            { 
               if (tokenized[i].get_type() == ID || tokenized[i].get_type() == INT) // the token type is ID or INT
                  postfix.push_back(tokenized[i]); 
               else if (tokenized[i].get_type() == OpenBrace) // the token type is OpenBrace
                  ops.push(tokenized[i]);
               else if (tokenized[i].get_type() == CloseBrace) // the token type is CloseBrace
               {
                  while (ops.top().get_type() != OpenBrace) // the type of the top of ops is not OpenBrace do 
                  {
                     postfix.push_back(ops.top()); // add the top of ops to postfix;
                     ops.pop(); // pop the top of ops;
                  }
                  ops.pop(); // pop the top of ops; // get rid of OpenBrace
               } 
               else // operator case
               {
                  while (!ops.empty() && ops.top().get_priority() >= tokenized[i].get_priority() ) //ops is not empty and the priority of the top of ops >= the priority of the token) do
                  {
                     postfix.push_back(ops.top()); // add the top of ops to postfix;
                     ops.pop(); // pop the top of ops;
                  } 
                  ops.push(tokenized[i]); // push token to ops;
               }
            }
            // move the remaining operators to postfix 
            while(!ops.empty()) // ops is not empty do
            {
               postfix.push_back(ops.top()); // add the top of ops to postfix; 
               ops.pop(); // pop the top of ops;
            } 
         }
         else // postfix is already made
         { 
         }
      }
      else
      {
         cout << "missing ; error!\n";
      }
   }

   string Expression::prefixBoi()
   {
      if(postfix.empty()) // if postfix is empty when you call preFix
         infixToPostfix();

      if(type == assignment)
         cout << "Hello, lolol\n";

      if(type == illegal)
         cout << "THIS IS ILLEGAL BOI\n";

      stack<string> s; 
      for(int i=0; i<postfix.size(); i++)
      {
         if(postfix[i].get_type() == OP)
         {
            string firstNum = s.top();
            s.pop();
            string secondNum = s.top();
            s.pop();

            string space = " ";
            string other = postfix[i].get_token() + space + firstNum + space + secondNum + space;
            s.push(other);
         }
         else if (postfix[i].get_type() == ID || postfix[i].get_type() == INT)
         {
            // if(postfix[i].get_token() == "0")
            // {
            //    string zero = "0";
            //    s.push(zero);
            // }
            // else
               s.push(postfix[i].get_token());
         }
      }
      return s.top();
   }

   string Expression::parenthesize()
   { 
      if(tokenized.empty())
         tokenizeMethod();

      if(postfix.empty())
         infixToPostfix(); 

      stack<string> s; 

      for (int i = 0; i < postfix.size(); i++) // postfix.size()
      {
         string exp  = postfix[i].get_token();
         if (postfix[i].get_type() == ID || postfix[i].get_type() == INT)
         {    
            string op = exp;
            s.push(op); 
         }
         else if (postfix[i].get_type() == OP)
         {
            string op1 = s.top(); 
            s.pop(); 
            string op2 = s.top(); 
            s.pop();
            s.push("(" + op2 + postfix[i].get_token() + op1 + ")");
         } 
      }
      return s.top();
   }
   
   Expression::Expression(const string &s) //other constructor
   {
      set(s);
      infixToPostfix();
   }
   
   //MISC FUNCTIONS
   void Expression::set(const string &s)
   {
      original = s;

   }
   void Expression::display() const
   {
      //cout << "\nOriginal  = " << get_original() << endl;
      //cout << "\nTokenized = " << get_tokenized();
   }

   //GETTER FUNCTIONS
   string Expression::get_original() const //getter for original member
   {
      return original;
   }
   vector<Token> Expression::get_tokenized() const //getter for tokenized member
   {

      return tokenized;
   }

   void Expression::output_type()
   {
      switch(type)
      {
         case assignment: 
            cout << " not an arithmetic expression, but an assignment.\n";
            break;
         case arithmetic:
            cout << "404 HOLD ON\n";
            break;
         case illegal: 
            cout << " an invalid expression.\n";
            break;
      }
   }
   Exp_type Expression::other_get_type()
   {
      return type;
   }

   void Expression::printPostfix()
   {
      for(int i=0; i<postfix.size(); i++)
         cout << postfix[i].get_token() << " ";
      cout << endl;
   }