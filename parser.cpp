#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
using namespace std;

// INSTRUCTION:  Complete all ** parts.
// You may use any method to connect this file to scanner.cpp
// that you had written.  
// You can copy scanner.cpp here by cp ../ScannerFiles/scanner.cpp .
// -----------------------------------------------------

//=================================================
// File parser.cpp written by Group Number: 10
//=================================================

// ----- Utility and Globals -----------------------------------
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
  PRONOUN,
  PRONOUN,
  PRONOUN,
  PRONOUN, 
  CONNECTOR,
  CONNECTOR,
  CONNECTOR,
  CONNECTOR,
  EOFM
};


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
  "eofm",
};


tokentype next_Token();
tokentype saved_token;
bool tokenAvailable;
string saved_lexeme;
bool error1 = false;
bool error2 = false;
void syntaxerror1();
void syntaxerror2();

void Story();
void afterSubject();
void afterNoun();
void afterObject();

void S();
void noun();
void verb();
void tense();
void be();

int scanner(tokentype& a, string& w);
bool word(string s);
bool period(string s);
ifstream fin;
// ** Need syntaxerror1 and syntaxerror2 functions (each takes 2 args)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

void syntaxerror1(tokentype p_theToken)
{
  cout << "Syntax Error: Expected  " << tokenName[p_theToken] << " but found " << saved_lexeme << endl;
  error1 = "true";
  exit(1);
}

void syntaxerror2(string p_function)
{
  cout << "Syntax Error: Unexpected " << saved_lexeme << " found in parser function " << p_function << endl; 
  error2 = true;
  exit(1);
}

// ** Need the updated match and next_token (with 2 global vars)
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:

bool match(tokentype expectedValue)
{
  if(next_Token() != expectedValue)
    {
      syntaxerror1(expectedValue);
      scanner(saved_token,saved_lexeme);
      match(saved_token);
    }
  else
    {
      tokenAvailable = false;
      return true;
    }
}

tokentype next_Token()
{
  if(!tokenAvailable)
    {
      scanner(saved_token,saved_lexeme);
      cout << "Scanner is called and using: " << saved_lexeme << endl;
      if(saved_token == ERROR)
	{
	  cout << "Lexical Error: " << saved_lexeme << " is not a valid token. " << endl;
	}
      tokenAvailable = true;
    }
  return saved_token;
}
	    

// ----- RDP functions - one per non-term -------------------

// ** Make each non-terminal into a function here
// ** Be sure to put the corresponding grammar rule above each function
// i.e. Grammar: 
// ** Be sure to put the name of the programmer above each function
// i.e. Done by:Andrew DeHaan


//Grammar: <story>  ::= <s> { <s> }                                                                                                                
//  Done by:Andrew DeHaan 
void Story()
{
  cout << "We are processing <story> here: " << endl; 
  S();
  while(next_Token() != EOFM)
    {
      switch(next_Token())
	{
	case CONNECTOR:
	case WORD1:
	case PRONOUN: S();
	  break;
	default: return;
	}      
    }
}

//Grammar:<story>  ::=  [CONNECTOR] <noun> SUBJECT <afterSubject>                                                                                                                 
// Done by:Andrew DeHaan
void S()
{
  cout << "We are processing <s> here" << endl;
  if(next_Token() == CONNECTOR)
    {
      match(CONNECTOR);
      cout << "Matched CONNECTOR" << endl;
    }
  noun();
  match(SUBJECT);
  cout << "Matched SUBJECT" << endl;
  afterSubject();
}

//Grammar:<afterSubject>  ::= <verb> <tense> PERIOD | <noun>  <afterNoun>                                                                         
// Done by:Andrew DeHaan
void afterSubject()
{
  cout << "We are processing <afterSUBJECT>  " << endl;
  switch(next_Token())
    {
    case WORD2: verb(); tense(); match(PERIOD); cout << "Matched PERIOD" << endl;
      break;
    case WORD1: noun(); afterNoun();
      break;
    case PRONOUN: noun(); afterNoun();
      break;
    default: syntaxerror2("After-Subject");
    }
}
//Grammar:<afterNoun>  ::= <be>  PERIOD | DESTINATION  <verb> <tense> PERIOD | OBJECT <afterObject>                                               
//Done by:Andrew DeHaan
void afterNoun()
{
  cout << "WE are processing <After-Noun>" << endl;
  switch (next_Token())
    {
    case IS :be(); match(PERIOD); cout << "Matched PERIOD" << endl;
      break;
    case WAS : be(); match(PERIOD); cout << "Matched PERIOD" << endl; 
      break;
    case DESTINATION : match(DESTINATION); cout << "Matched DESTINATION" << endl; verb(); tense(); match(PERIOD); cout << "Matched PERIOD" << endl; 
      break;
    case OBJECT : match(OBJECT); cout << "Matched OBJECT" << endl; afterObject(); 
      break;
    default : syntaxerror2("After-Noun");
    }
}



//Grammar:<afterObject>_ ::= <verb> <tense> PERIOD | <noun> DESTINATION <verb> <tense> PERIOD                                                     
// Done by:Andrew DeHaan
void afterObject()
{
  cout << "We are processing <After-Object>" << endl;
  switch(next_Token())
    {
    case WORD2: verb(); tense(); match(PERIOD); cout << "Matched PERIOD" << endl;
      break;
    case WORD1:
    case PRONOUN: noun(); match(DESTINATION); cout << "Matched DESTINATION" << endl; verb(); tense(); match(PERIOD); cout << "Matched PERIOD" << endl; 
      break;
    default: syntaxerror2("After-Object");
    }
}

//Gramamr:<noun>  ::= WORD1 | PRONOUN                                                                                                    
//Done by:Andrew DeHaan
void noun()
{
  cout << "We are processing <Noun>" << endl;
  switch(next_Token())
    {
    case WORD1: match(WORD1); cout << "Matched WORD1" << endl;
      break;
    case PRONOUN: match(PRONOUN); cout << "Matched PRONOUN" << endl;
      break;
    default: syntaxerror2("Noun");
    }
}

//Grammar:<verb>  ::= WORD2                                                                                                                       
//Done by:Andrew DeHaan               
void verb()
{
  cout << "WE are processing <Verb>" << endl;
  match(WORD2);
  cout << "Matched WORD2" << endl;
}

//Grammar:<be>  ::= IS | WAS                                                                                                           
//Done by:Andrew DeHaan                                                                                                     
void be()
{
  cout << "We are processing <Be>" << endl;
  switch(next_Token())
    {
    case IS: match(IS); cout << "Matched IS" << endl;
      break;
    case WAS: match(WAS); cout << "Matched WAS" << endl;
      break;
    default: syntaxerror2("BE");
    }
  
}

//Grammar:<tense>  ::= VERBPAST  | VERBPASTNEG | VERB | VERBNEG                                                                       
//Done by:Andrew DeHaan
void tense()
{
  cout << "We are processing <Tense>" << endl;
  switch(next_Token())
    {
    case VERBPAST: match(VERBPAST); cout << "Matched VERBPAST" << endl;
      break;
    case VERBPASTNEG: match(VERBPASTNEG); cout << "Matched VERBPASTNEG" << endl;
      break;
    case VERB: match(VERB); cout << "Matched VERB" << endl;
      break;
    case VERBNEG: match(VERBNEG); cout << "Matched VERBNEG" << endl;
      break;
    default: syntaxerror2("TENSE");
    }
}
/**************************************************************
SCANNER FUNCTIONS
**************************************************************/

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
	      // cout << "Lexical error: " << w << " is not a valid token." << endl;
	    }  
	  return 1;
	}
    }
}//the end of scanner

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
	  // cout << "FAILED AT STATE : " << state << endl;
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
      //cout << "FAILED AT STATE : " << state << endl;
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





//---------------------------------------

// The new test driver to start the parser
// Done by:  Anthony Law
int main()
{
  tokentype theType;
  string theWord;
  string filename;
 

  cout << "Enter the input file name: ";
  cin >> filename;
  fin.open(filename.c_str());

  //** calls the <story> to start parsing
  //** closes the input file 
  Story();
  cout << endl;
  if(error1 == false && error2 == false)
    {
      cout << "We have successfully parsed <Story>." << endl; 
    }
  fin.close();
  return 0;
}// end
//** require no other input files!
//** syntax error EC requires producing errors.text of messages

