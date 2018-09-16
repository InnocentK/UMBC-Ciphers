/**************************************
 ** File:    Cipher.h
 ** Project: CMSC 202 Project 3 - UMBC Ciphers, Fall 2017
 ** Author:  Jeremy Dixion
 ** User:    Innocent Kironji
 ** Date:    11/02/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file contains function declerations and private members for Cipher
 **  class. Private members deal with management of keys and of the string
 **  that is being cyphered at runtime.
 **
 ** This is a file by professor Dixon that remains unedited from his 
 **  original version outside from these comments *(with the exception of
 **  the Cipher destructor he told us to add during class)*.
 ***************************************/

#ifndef CIPHER_H
#define CIPHER_H

#include "CipherString.h"

class Cipher{
public:
  enum Mode{CAESAR=1, ONG=2, VIGENERE=3};
    // Name: Cipher(char) - Overloaded constructor for Caesar cipher
    // Preconditions - Caesar cipher is defined
    // Postconditions - Constructor for the Caesar cipher (sets m_mode to CAESAR)
    Cipher(char);
    // Name: Cipher(string) - Overloaded constructor for Vigenere cipher
    // Preconditions - Vigenere cipher is defined
    // Postconditions - Constructor for the Vigenere cipher (sets m_mode to VIGENERE)
    Cipher(string);
    // Name: Cipher() - Overloaded constructor for Vigenere cipher
    // Preconditions - Ong Cipher is defined
    // Postconditions - Constructor for the Ong cipher (sets m_mode to ONG)
    Cipher();
    // Name: ~Cipher() - Overloaded destructor for cipher
    // Preconditions - Cipher is defined
    // Postconditions - Destructor for the cipher (deletes all dynamic var)
    ~Cipher();
    // Name: setPlainText
    // Preconditions - File with text is available (in current directory)
    // Postconditions - Stores file text in m_cipherString
    void setPlainText(string);
    // Name: encrypt
    // Preconditions - m_cipherString populated
    // Postconditions - Calls correct encryption function based on the cipher chosen
    void encrypt();
    // Name: decrypt
    // Preconditions - m_cipherString populated and encrypted
    // Postconditions - Calls correct decryption function based on the cipher chosen
    void decrypt();
    // Name: changeKey
    // Preconditions - key exists
    // Postconditions - Key is updated
    void changeKey(string);
    // Name: printString
    // Preconditions - m_cipherString populated
    // Postconditions - Outputs the value of m_cipherString
    void printString();
private:
    Mode m_mode; //Uses enum to manage type of cipher
    CipherString* m_cipherString; //Linked List of the cipher string
    char m_caesar_key; //Used for Caesar ciphers as the key
    string m_vig_key; //Used for Vigenere ciphers as the key
};
#endif
