/**************************************
 ** File:    Cipher.cpp
 ** Project: CMSC 202 Project 3 - UMBC Ciphers, Fall 2017
 ** Author:  Innocent Kironji
 ** Date:    11/02/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file contains definitions for all functions in Cipher class. It also
 **  manages CipherString and what CipherString functions are called to do
 **  certain tasks.
 ***************************************/

#include "Cipher.h"

// Cipher(char) - Overloaded constructor for Caesar cipher
// Constructor for the Caesar cipher (sets m_mode to CAESAR)
Cipher::Cipher(char key){

  //  m_cipherString = new CipherString();
  m_mode = CAESAR;
  m_caesar_key = key;
}

// Cipher(string) - Overloaded constructor for Vigenere cipher
// Constructor for the Vigenere cipher (sets m_mode to VIGENERE)
Cipher::Cipher(string key){

  //  m_cipherString = new CipherString();
  m_mode = VIGENERE;
  m_vig_key = key;
}

// Cipher() - Overloaded constructor for ONG cipher
// Constructor for the Ong cipher (sets m_mode to ONG)
Cipher::Cipher(){

  //  m_cipherString = new CipherString();
  m_mode = ONG;
}

// setPlainText
// Stores file text in m_cipherString
void Cipher::setPlainText(string fileName){

  CipherString toCipher( fileName.c_str() );
  m_cipherString = &toCipher;
  //  m_cipherString->loadMessage( fileName.c_str() );

}

// encrypt
// Preconditions - m_cipherString populated
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
// Preconditions - m_cipherString populated and encrypted
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
    case CAESAR:
      // Caesar cypher only takes single characters for its key
      // Also c-strings are arrays so it needs to be derefferenced in order
      //   to be assigned to a char
      m_caesar_key = *( newKey.substr(0).c_str() );
      break;
    case VIGENERE:
      m_vig_key = newKey;
      break;
    default:
      // In the case of Ong cypher
      cout << "----------------------------------" << endl;
      cout << "Your Cipher does not require a key" << endl;
      cout << "----------------------------------" << endl;
  }
  return;
}

// printString
// Outputs the value of m_cipherString
void Cipher::printString(){

  *m_cipherString << endl;
  return;
}
