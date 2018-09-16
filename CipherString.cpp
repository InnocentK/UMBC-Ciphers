/**************************************
 ** File:    CipherString.cpp
 ** Project: CMSC 202 Project 3 - UMBC Ciphers, Fall 2017
 ** Author:  Innocent Kironji
 ** Date:    11/02/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file contains defenitions for all CipherString class functions.
 **  This is where most of the implementation of the ciphering exists. 
 **  Handles rules used for incription and handles how most of the program
 **  as a whole runs.
 **
 ***************************************/

#include "CipherString.h"
#include "Cipher.h"
#include "Node.h"

const int ASCII_UPPERCASE_A = 65;
const int ASCII_LOWERCASE_A = 97;
const int ASCII_UPPERCASE_Z = 90;
const int ASCII_LOWERCASE_Z = 122;
const char SPACE = ' ';

// CipherString - default constructor
// Creates a new CipherString
CipherString::CipherString(){

  m_head = NULL;
  m_size = 0;
}

// CipherString - overloaded constructor
// Creates a new CipherString (using char*)
CipherString::CipherString(const char* cString){

  m_head = NULL;
  m_size = 0;
  loadMessage(cString);
}

// ~CipherString - destructor
// Destroys CipherString
CipherString::~CipherString(){

  // Checks if linked list is populated
  if (m_head != NULL){

    Node *currNode = m_head;
    Node *nextNode = currNode->getNext();
    
    // Checks to see if end of linked list is reached
    while (nextNode != NULL){
      
      // Deletes current node and updates list size accordingly
      delete currNode;
      currNode = NULL;
      m_size--;
      
      // Updates Node Holders
      currNode = nextNode;
      nextNode = currNode->getNext();
    }
    
    // Deletes current node and updates list size accordingly
    delete currNode;
    currNode = NULL;
    m_size--;
  }
}

// loadMessage
// File (with text in it) is passed to function
// Then loads file one character at a time into the linked list
void CipherString::loadMessage(const char* fileName){
  
  char currChar = ' ';
  char peeked = ' ';
  ifstream textFile (fileName);
  
  // Verifies file opened properly
  if( textFile.is_open() ){

    // Iterates through text file (checks if file is still open
    while( (textFile >> currChar) && (peeked != EOF) ){
      
      // Adds text in file to linked list
      addCharacter(currChar);
      peeked = textFile.peek();

      if (peeked == SPACE){
	addCharacter(peeked);
      }
    }
  }else
    cout << "File was unable to open" << endl;
  
  textFile.close();
  return;
}

// addCharacter
// Adds character to end of linked list
void CipherString::addCharacter(char newChar){

  Node *newNode = new Node(newChar);

  // Checks for empty linked list
  if (m_head == NULL){
    m_head = newNode;
  }

  //When linked list already holds some elements
  else{
    Node *tempNode = m_head;

    // Checks if end of linked list has been reached
    while (tempNode->getNext() != NULL){
      tempNode = tempNode->getNext();
    }
    
    // Updates end of linked list with next data
    tempNode->setNext(newNode);
  }
  m_size++;
  return;
}

// encryptOng
// For each consonent, adds a node with "o", adds a node with "n"
//  adds a node with "g". Every "letter" is separated with a "-" and 
//  each word is seperated by a space.
void CipherString::encryptOng(){

  Node *tempNode = m_head;
  bool consonent = false;

  // Creates new Nodes for each of the cypher characters                    
  Node *NodeO = NULL;
  Node *NodeN = NULL;
  Node *NodeG = NULL;
  Node *DashNode = NULL;

  // Checks if end of linked list has been reached
  for (int i = 0; i < getSize(); i++){

    // Checks for vowels
    consonent = (tempNode->getChar() != 'a') && (tempNode->getChar() != 'e')
      && (tempNode->getChar() != 'i') && (tempNode->getChar() != 'o') 
      && (tempNode->getChar() != 'u') && (tempNode->getChar() != 'A') 
      && (tempNode->getChar() != 'E') && (tempNode->getChar() != 'I') 
      && (tempNode->getChar() != 'O') && (tempNode->getChar() != 'U');
  
    // Checks for spaces
    bool isSpace = (tempNode->getChar() == SPACE);
    bool nextIsSpace = ( (tempNode->getNext() != NULL) &&
			 (tempNode->getNext()->getChar() == SPACE) );
    
    if( (consonent) && !(isSpace) ){
      
      // Creates new Nodes for each of the cypher characters   
      NodeO = new Node('o');
      NodeN = new Node('n');
      NodeG = new Node('g');
      DashNode = new Node('-');
      
	// Assigns the new nodes their correct placement in linked list
	NodeO->setNext(NodeN);
	NodeN->setNext(NodeG);

	// When the next node holds a space: ' '
	if (nextIsSpace){
	  NodeG->setNext( tempNode->getNext() );
	  tempNode->setNext(NodeO);

	  //Updates next value to be checked
	  tempNode = NodeG->getNext();

	  //Cleaning up unused node
          delete DashNode;
          DashNode = NULL;
	}

	// If at the end of the linked list
	else if (tempNode->getNext() == NULL){
	  tempNode->setNext(NodeO);
	  delete DashNode;
	  DashNode = NULL;
	}

	// Normal scenario (no spaces or at end of list)
	else{
	  NodeG->setNext(DashNode);
	  DashNode->setNext( tempNode->getNext() );
	  tempNode->setNext(NodeO);
	  
	  // Updates next value to be checked
	  tempNode = DashNode->getNext();
	}
      }

      // When there is a space (in current or next node) make no changes
    else if (isSpace || nextIsSpace){
      tempNode = tempNode->getNext();
      }

    // When the node holds a vowel and not at the end of linked list
    else if (tempNode->getNext() != NULL){
      DashNode = new Node('-');

      // Updates linked list with a dash after the vowel
      DashNode->setNext( tempNode->getNext() );
      tempNode->setNext(DashNode);
      
      // Next Node to be checked
      tempNode = DashNode->getNext();
    }
  }
  return;
}

// decryptOng
// For each consonent, adds a node with "o", adds a node with "n"
//  adds a node with "g". Every "letter" is separated with a "-" and 
//  each word is seperated by a space
void CipherString::decryptOng(){

  Node *tempNode = m_head;
  bool consonent = false;

  // temporary nodes to hold the encrypted letters                          
  Node *oChar = NULL;
  Node *nChar = NULL;
  Node *gChar = NULL;
  Node *dashChar = NULL;

  // Checks if end of linked list has been reached
  for (int i = 0; i < getSize(); i++){ 

    // Checks for vowels
    consonent = (tempNode->getChar() != 'a') && (tempNode->getChar() != 'e')
      && (tempNode->getChar() != 'i') && (tempNode->getChar() != 'o')
      && (tempNode->getChar() != 'u') && (tempNode->getChar() != 'A')
      && (tempNode->getChar() != 'E') && (tempNode->getChar() != 'I')
      && (tempNode->getChar() != 'O') && (tempNode->getChar() != 'U');

    // Checks for spaces
    bool isSpace = (tempNode->getChar() == SPACE);
    bool nextIsSpace = ( (tempNode->getNext() != NULL) &&
			 (tempNode->getNext()->getChar() == SPACE) );

    // Runs as long as current character is not a vowel or space
    if( (consonent) && !(isSpace) ){

      oChar = tempNode->getNext();
      nChar = oChar->getNext();
      gChar = nChar->getNext();

      // Checks for end of linked list
      if(gChar->getNext() == NULL){
	tempNode->setNext( gChar->getNext() );
      }
      // Checks if there is a dash
      else if (gChar->getNext()->getChar() != SPACE){

	// Updates linked list to remove dash
	dashChar = gChar->getNext();
	tempNode->setNext( dashChar->getNext() );
	tempNode = tempNode->getNext();
	delete dashChar;
	dashChar = NULL;
      }

      // If 'g' is followed by a space
      else{
	tempNode->setNext( gChar->getNext() );
	tempNode = tempNode->getNext();
      }

      // Encrpted nodes are no longer needed
      delete oChar;
      oChar = NULL;
      delete nChar;
      nChar = NULL;
      delete gChar;
      gChar = NULL;
    }

    // If there is a space (either current or adjecent char) nothing happens
    else if (nextIsSpace || isSpace){
      tempNode = tempNode->getNext();
    }

    // The char is a vowel and linked list is not at the end
    else if (tempNode->getNext() != NULL){
      
      dashChar = tempNode->getNext();
      
      // Updates linked list to remove dash
      tempNode->setNext( dashChar->getNext() );
      tempNode = tempNode->getNext();

      delete dashChar;
    }
  }
  return;
}

// encryptCaesar
// Shifts each character "right" by the int provided. 
void CipherString::encryptCaesar(int key){

  const int VALID_KEY = key % 26;
  Node *tempNode = m_head;

  // Checks if end of linked list has been reached
  for(int i = 0; i < getSize(); i++){

    int currAscii = tempNode->getChar();
    bool uppercase =( (currAscii >= ASCII_UPPERCASE_A) &&
                      (currAscii <= ASCII_UPPERCASE_Z) );

    bool lowercase =( (currAscii >= ASCII_LOWERCASE_A) &&
                      (currAscii <= ASCII_LOWERCASE_Z) );

    int alphabetPos = 0;
    int newPos = 0;
    int newAscii = 0;

    // Checks for valid alphabet letter
    if (uppercase){

      // Calculates new ascii
      alphabetPos = currAscii - ASCII_UPPERCASE_A;
      newPos = (alphabetPos + VALID_KEY) % 26;
      newAscii = newPos + ASCII_UPPERCASE_A;
    }
    else if (lowercase){
      // Calculates new ascii
      alphabetPos = currAscii - ASCII_LOWERCASE_A;
      newPos = (alphabetPos + VALID_KEY) % 26;
      newAscii = newPos + ASCII_LOWERCASE_A;
    }
    else if (tempNode->getChar() != SPACE){
      cout << "---------------------------------------" << endl;
      cout << "Not a valid character from the alphabet" << endl;
      cout << "---------------------------------------" << endl;
    }
    
    // Updates character and moves on to the next node
    if (tempNode->getChar() != SPACE)
      tempNode->setChar(newAscii);
    tempNode = tempNode->getNext();
  }
  return;
}

// decryptCaesar
// Shifts each character "left" by the int provided.
void CipherString::decryptCaesar(int key){

  const int VALID_KEY = key % 26;
  Node *tempNode = m_head;

  // Checks if end of linked list has been reached
  for(int i = 0; i < getSize(); i++){

    int currAscii = tempNode->getChar();
    bool uppercase =( (currAscii >= ASCII_UPPERCASE_A) &&
		      (currAscii <= ASCII_UPPERCASE_Z) );

    bool lowercase =( (currAscii >= ASCII_LOWERCASE_A) &&
		      (currAscii <= ASCII_LOWERCASE_Z) );
    int alphabetPos = 0;
    int newPos = 0;
    int newAscii = 0;

    // Checks for valid alphabet letter
    if (uppercase){

      // Calculates new ascii
      alphabetPos = currAscii - ASCII_UPPERCASE_Z;
      newPos = (alphabetPos - VALID_KEY) % 26;
      newAscii = newPos + ASCII_UPPERCASE_Z;
    }
    else if (lowercase){
      // Calculates new ascii
      alphabetPos = currAscii - ASCII_LOWERCASE_Z;
      newPos = (alphabetPos - VALID_KEY) % 26;
      newAscii = newPos + ASCII_LOWERCASE_Z;
    }
    else if (tempNode->getChar() != SPACE){
      cout << "---------------------------------------" << endl;
      cout << "Not a valid character from the alphabet" << endl;
      cout << "---------------------------------------" << endl;
    }

    // Updates character and moves on to the next node
    if (tempNode->getChar() != SPACE)
      tempNode->setChar(newAscii);
    tempNode = tempNode->getNext();
  }
  return;
}

// encryptVigenere
// Shifts each character by the character (in string) provided.
void CipherString::encryptVigenere(string key){

  Node *tempNode = m_head;
  int sizeDiff = getSize() - signed(key.size());
  string validKey = key;

  // Make key necessary length
  if( signed(key.size()) < getSize() ){
    for (int i = 0; i < sizeDiff; i++)
      validKey += validKey.substr(i,1);
  }
  // When key is longer than message
  else if( signed(key.size()) > getSize() )
    validKey = key.substr(0, getSize());


  // Checks if end of linked list has been reached
  for(int i = 0; i < getSize(); i++){
 
    // Converts letters from key into ascii values
    int currKeyLetterAscii = *( validKey.substr(i,1).c_str() );

    bool lowercaseKey =( (currKeyLetterAscii >= ASCII_LOWERCASE_A) &&
                      (currKeyLetterAscii <= ASCII_LOWERCASE_Z) );

    // Sets Ascii for key's current letter to the uppercase form's ascii
    if (lowercaseKey)
      currKeyLetterAscii -= 31;
    int keyPos = currKeyLetterAscii - ASCII_UPPERCASE_A;

    // Prepares ascii for the message
    int currAscii = tempNode->getChar();
    bool uppercase =( (currAscii >= ASCII_UPPERCASE_A) &&
                      (currAscii <= ASCII_UPPERCASE_Z) );

    bool lowercase =( (currAscii >= ASCII_LOWERCASE_A) &&
                      (currAscii <= ASCII_LOWERCASE_Z) );
    int alphabetPos = 0;
    int newPos = 0;
    int newAscii = 0;

    bool isSpace = (tempNode->getChar() == SPACE);

    // Checks for valid alphabet letter
    if (uppercase){

      // Calculates new ascii
      alphabetPos = currAscii - ASCII_UPPERCASE_A;
      newPos = (alphabetPos + keyPos) % 26;
      newAscii = newPos + ASCII_UPPERCASE_A;
    }
    else if (lowercase){
      // Calculates new ascii
      alphabetPos = currAscii - ASCII_LOWERCASE_A;
      newPos = (alphabetPos + keyPos) % 26;
      newAscii = newPos + ASCII_LOWERCASE_A;
    }
    else if (tempNode->getChar() != SPACE){
      cout << "---------------------------------------" << endl;
      cout << "Not a valid character from the alphabet" << endl;
      cout << "---------------------------------------" << endl;
    }

    // Updates character and moves on to the next node
    if (!(isSpace))
      tempNode->setChar(newAscii);

    tempNode = tempNode->getNext();
  }
  return;
}

// decryptVigenere
// Shifts each character by the character (in string) provided
void CipherString::decryptVigenere(string key){

  Node *tempNode = m_head;
  int sizeDiff = getSize() - signed(key.size());
  string validKey = key;

  // Make key necessary length
  if( signed(key.size()) < getSize() ){
    for (int i = 0; i < sizeDiff; i++)
      validKey += validKey.substr(i,1);
  }
  // When key is longer than message
  else if( signed(key.size()) > getSize() )
    validKey = key.substr(0, getSize());

  // Checks if end of linked list has been reached
  for(int i = 0; i < getSize(); i++){

    // Converts letters from key into ascii values
    int currKeyLetterAscii = *( validKey.substr(i,1).c_str() );

    bool lowercaseKey =( (currKeyLetterAscii >= ASCII_LOWERCASE_A) &&
			 (currKeyLetterAscii <= ASCII_LOWERCASE_Z) );

    // Sets Ascii for key's current letter to the uppercase form's ascii
    if (lowercaseKey)
      currKeyLetterAscii -= 31;
    int keyPos = currKeyLetterAscii - ASCII_UPPERCASE_A;

    // Prepares ascii for the message
    int currAscii = tempNode->getChar();
    bool uppercase =( (currAscii >= ASCII_UPPERCASE_A) &&
                      (currAscii <= ASCII_UPPERCASE_Z) );

    bool lowercase =( (currAscii >= ASCII_LOWERCASE_A) &&
                      (currAscii <= ASCII_LOWERCASE_Z) );
    int alphabetPos = 0;
    int newPos = 0;
    int newAscii = 0;

    // Checks for valid alphabet letter
    if (uppercase){

      // Calculates new ascii
      alphabetPos = currAscii - ASCII_UPPERCASE_Z;
      newPos = (alphabetPos - keyPos) % 26;
      newAscii = newPos + ASCII_UPPERCASE_Z;
    }
    else if (lowercase){
      // Calculates new ascii
      alphabetPos = currAscii - ASCII_LOWERCASE_Z;
      newPos = (alphabetPos - keyPos) % 26;
      newAscii = newPos + ASCII_LOWERCASE_Z;
    }
    else if (tempNode->getChar() != SPACE){
      cout << "---------------------------------------" << endl;
      cout << "Not a valid character from the alphabet" << endl;
      cout << "---------------------------------------" << endl;
    }

    // Updates character and moves on to the next node
    if (tempNode->getChar() != SPACE)
      tempNode->setChar(newAscii);
    tempNode = tempNode->getNext();
  }
  return;
}

// getSize
// Return size of CypherString Linked List
int CipherString::getSize(){

  return m_size;
}

// operator<< (overloaded insertion operator)                           
// Iterates over the linked list and prints each char in each node
ostream& operator<<(ostream &output, const CipherString &linked){

  Node *tempNode = linked.m_head;

  if (tempNode != NULL){

    // Iteratees through linked list until the end
    while (tempNode->getNext() != NULL){
      output << tempNode->getChar();
      tempNode = tempNode->getNext();
    }
    output << tempNode->getChar() << endl;
  }

  return output;
}
