/**************************************
 ** File:    Cipher.cpp
 ** Project: CMSC 202 Project 3 - UMBC Ciphers, Fall 2017
 ** Author:  Innocent Kironji
 ** Date:    11/02/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file contains definitions for all functions in Cipher class. It 
 ** also manages CipherString and what CipherString functions are called 
 ** to do certain tasks.
 **
 ***************************************/

#include "Cipher.h"

// Cipher(char) - Overloaded constructor for Caesar cipher
// Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher(char key){

  m_cipherString = NULL;
  m_mode = CAESAR;
  m_caesar_key = key;
}

// Cipher(string) - Overloaded constructor for Vigenere cipher
// Constructor for the Vigenere cipher (sets m_mode to VIGENERE)
Cipher::Cipher(string key){

  m_cipherString = NULL;
  m_mode = VIGENERE;
  m_vig_key = key;
}

// Cipher() - Overloaded constructor for ONG cipher
// Constructor for the Ong cipher (sets m_mode to ONG)
Cipher::Cipher(){

  m_cipherString = NULL;
  m_mode = ONG;
}

// ~Cipher() - Overloaded destructor for cipher
// Destrurctor for the cipher (deletes all dynamic var)
Cipher::~Cipher(){

  delete m_cipherString;
  m_cipherString = NULL;
}

// setPlainText
// Stores file text in m_cipherString
void Cipher::setPlainText(string fileName){

  m_cipherString = new CipherString();
  m_cipherString->loadMessage( fileName.c_str() );
}

// encrypt
// Calls correct encryption function based on the cipher chosen
void Cipher::encrypt(){

  switch(m_mode)
    {
    case CAESAR:
      m_cipherString->encryptCaesar(m_caesar_key);
      printString();
      break;
    case ONG:
      m_cipherString->encryptOng();
      printString();
    break;
    case VIGENERE:
      m_cipherString->encryptVigenere(m_vig_key);
      printString();
      break;
    default:
      cout << "--------------------------------" << endl;
      cout << "You are not using a valid Cipher" << endl;
    cout << "--------------------------------" << endl;
    }
  return;
}

// decrypt
// Calls correct decryption function based on the cipher chosen
void Cipher::decrypt(){

  switch(m_mode)
    {
    case CAESAR:
      m_cipherString->decryptCaesar(m_caesar_key);
      printString();
      break;
    case ONG:
      m_cipherString->decryptOng();
      printString();
      break;
    case VIGENERE:
      m_cipherString->decryptVigenere(m_vig_key);
      printString();
      break;
    default:
      cout << "--------------------------------" << endl;
      cout << "You are not using a valid Cipher" << endl;
      cout << "--------------------------------" << endl;
    }
  return;

}

// changeKey
// Updates Key
void Cipher::changeKey(string newKey){

  // Checks which cypher is being used
  switch(m_mode)
    {

      // Caesar cypher only takes single characters for its key
    case CAESAR:
      cout << "--------------------------------------------------" << endl;
      cout << "This Caesar Cypher only takes single character keys." 
	   << endl << "Thereby I shall only use the first character of the" 
	   << " string you provided." << endl 
	   << endl << "To be more specific I will be using that character's"
	   << " ASCII Value." << endl;
      cout << "--------------------------------------------------" << endl;

      //C-strings must be derefferenced to be converted to char
      m_caesar_key = *(newKey.substr(0,1).c_str());
      break;

      // Only catural case for change key
    case VIGENERE:
      m_vig_key = newKey;
      break;

      // In the case of Ong cypher
    default:
      cout << "----------------------------------" << endl;
      cout << "Your Cipher does not require a key" << endl;
      cout << "----------------------------------" << endl;
  }
  return;
}

// printString
// Outputs the value of m_cipherString
void Cipher::printString(){

  cout << *m_cipherString << endl;
  return;
}
