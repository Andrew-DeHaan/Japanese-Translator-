#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//=====================================================
// File scanner.cpp written by: Group Number: 10
//=====================================================

// --------- DFAs ---------------------------------

// ** WORD DFA is the statement based off of our drawing for the Word DFA. 
// ** Done by: Anthony Law
// ** RE: 

bool word(string s)
{
  int state = 0;
  int charpos = 0;

  while(s[charpos] != '\0')
    {
      //This is the q0 state.
      if(state == 0 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1; //State 1 is the q0' state.
	}
      else if(state == 0 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
	{
	  state = 2; //State 2 is the pair state.
	}
      else if(state == 0 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
	{
	  state = 3; //State 3 is the conson state.
	}
      else if(state == 0 && (s[charpos] == 's'))
	{
	  state = 4; //State 4 is the s state.
	}
      else if(state == 0 && s[charpos] == 't')
	{
	  state = 5; //State 5 is the t state.
	}
      else if(state == 0 && s[charpos] == 'c')
	{
	  state = 6; //State 6 is the c state.
	}		      

      //This is for state 1 (q0')
      else if(state == 1 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1; //qo' state
	}
      else if(state == 1 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] == 'm' /*|| s[charpos] == 'n'*/ || s[charpos] == 'p' || s[charpos] == 'r'))
	{
	  state = 2; //pair state
	}
      else if(state == 1 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
	{
	  state = 3; //conson state
	}
      else if(state == 1 && s[charpos] == 's')
	{
	  state = 4;
	}
      else if(state == 1 && s[charpos] == 't')
	{
	  state = 5;
	}
      else if(state == 1 && s[charpos] == 'c')
	{
	  state = 6;
	}
      else if(state == 1 && s[charpos] == 'n')
	{
	  state = 7;
	}

      //This is the state 2 or pair.
      else if(state == 2 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1;
	}
      else if(state == 2 && s[charpos] == 'y')
	{
	  state = 3;
	}

      //This is the state 3 or conson.
      else if(state == 3 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1;
	}
      //This is the state 4 or S.
      else if(state == 4 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1;
	}
      else if(state == 4 && s[charpos] == 'h')
	{
	  state = 3; //s going to conson, state 4 going to state 3
	}
      //This is the state 5 or T.
      else if(state == 5 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1; //if vowel, and in state 5, sees a vowel, will go back to 1
	}
      else if(state == 5 && s[charpos] == 's')
	{
	  state = 3;
	}
      //This is the state 6 or C.
      else if(state == 6 && s[charpos] == 'h')
	{
	  state = 3;
	}

      //State 7 is a final state. 
      else if(state == 7 && (s[charpos] == 'a' || tolower(s[charpos]) == 'e' || tolower(s[charpos]) == 'i' || s[charpos] == 'o' || s[charpos] == 'u'))
	{
	  state = 1;
	}
      else if(state == 7 && (s[charpos] == 'b' || s[charpos] == 'g' || s[charpos] == 'h' || s[charpos] == 'k' || s[charpos] || s[charpos] == 'm' || s[charpos] == 'n' || s[charpos] == 'p' || s[charpos] == 'r'))
        {
          state = 2; //pair
        }
      else if(state == 7 && (s[charpos] == 'd' || s[charpos] == 'j' || s[charpos] == 'w' || s[charpos] == 'y' || s[charpos] == 'z'))
        {
          state = 3; //conson state
        }
      else if(state == 7 && (s[charpos] == 's'))
        {
          state = 4; //s state
        }
      else if(state == 7 && s[charpos] == 't')
        {
          state = 5; //t state
        }
      else if(state == 7 && s[charpos] == 'c')
        {
          state = 6; //c state
        }
      else 
	{
	  cout << "FAILED AT STATE : " << state << endl;
	  return false;
	}
      charpos++;
    }
  
  //state 1 or 7 are our final states
  if(state == 1 || state == 7)
    {
      return true;
    }
  else
    {
      cout << "FAILED AT STATE : " << state << endl;
      return false;
    }
}

// ** Add the PERIOD DFA here
// ** Done by: Raj Potla

bool period(string s)
{
  int state = 0;
  int charpos = 0;
  
  while(s[charpos] != '\0')
    {
      if(state == 0 && (s[charpos] == '.')) //check if period, otherwise return false
	{
	  state = 1;
	}
      else
	{
	  return false;
	}
      charpos++;
    }
  if(state == 1) //to return true or false if the s[charpos] == '.'
    {
      return true;
    }
  else
    {
      return false;
    }

}

// -----  Tables -------------------------------------

// ** Update the tokentype to be WORD1, WORD2, PERIOD, ERROR, etc.
// Feel free to add a tokentype for the end-of-file marker.
enum tokentype 
{
  
  WORD1,
  WORD2,
  PERIOD,
  ERROR,
  VERB,
  VERBNEG,
  VERBPAST,
  VERBPASTNEG,
  IS,
  WAS,
  OBJECT,
  SUBJECT,
  DESTINATION,
  PRONOUN,
  CONNECTOR,
  EOFM,
};

tokentype typereservedWords[30] =
{
    VERB,        //masu
    VERBNEG,     //masen
    VERBPAST,    //mashita
    VERBPASTNEG, //masendeshita
    IS,          //desu
    WAS,         //deshita
    OBJECT,      //o
    SUBJECT,     //wa
    DESTINATION, //ni
    PRONOUN,     //watashi
    PRONOUN,     //anata
    PRONOUN,     //kare
    PRONOUN,     //kanojo
    PRONOUN,     //sore
    CONNECTOR,   //mata
    CONNECTOR,   //soshite
    CONNECTOR,   //shikashi
    CONNECTOR,   //dakara
    EOFM
};

// ** string tokenName[30] = { }; for the display names of tokens
string tokenName[30] =
{
  "WORD1",
  "WORD2",
  "PERIOD",
  "ERROR",
  "VERB",
  "VERBNEG",
  "VERBPAST",
  "VERBPASTNEG",
  "IS",
  "WAS",
  "OBJECT",
  "SUBJECT",
  "DESTINATION",
  "PRONOUN",
  "CONNECTOR",
  "EOFM"
};

// ** Need the reservedwords table to be set up here. 
string reservedWords[30] = 
{
  "masu",
  "masen",
  "mashita",
  "masendeshita",
  "desu",
  "deshita",
  "o",
  "wa",
  "ni",
  "watashi",
  "anata",
  "kare",
  "kanojo",
  "sore",
  "mata",
  "soshite",
  "shikashi",
  "dakara",
  "eofm"
};
// ** Do not require any file input for this.
// ** a.out should work without any additional files.


// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// ** Done by: Andrew Dehaan
int scanner(tokentype& a, string& w)
{

  bool IsReserved = false;
  // ** Grab the next word from the file via fin
  fin >> w;
  cout << endl; //endline here to space out the printed statements
  cout << "The next word is: " << w << endl; //to see what word is next
  if(w == "eofm") //check if the string that comes into this function is eofm. If it is, exit the function.
    {
      return 0;
    }
  if(period(w)) //if w works with the period function, set the tokentype to PERIOD
    {
      a = PERIOD;
    }
  else
    {
      for(int i = 0; i < 30; i++) //checking all the reserved words list here 
	{
	  if(w == reservedWords[i])
	    {
	      a = typereservedWords[i];
	      IsReserved = true;
	      break;
	    }
	}
      if(IsReserved == false)
	{
	  if(w[w.length() - 1] == 'I' || w[w.length() - 1] == 'E') //this if statement checks if the string ends in a captial I or E
	    {
	    a = WORD2;
	  }
	  else if(word(w))
	    {
	      a = WORD1; //normal word ending in not an I or E
	    }
	  else
	    {
	      a = ERROR;
	      //cout << "DFA's word and period have failed." << endl; 
	      cout << "Lexical error: " << w << " is not a valid token." << endl;
	    }	  
	  return 1;
	}
    }
  /* 
     2. Call the token functions one after another (if-then-else)
     And generate a lexical error message if both DFAs failed.
     Let the token_type be ERROR in that case.
     3. Make sure WORDs are checked against the reservedwords list
     If not reserved, token_type is WORD1 or WORD2.
     4. Return the token type & string  (pass by reference)
  */
}//the end of scanner

// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner
       if (theword == "eofm") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

