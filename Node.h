/**************************************
 ** File:    Node.h
 ** Project: CMSC 202 Project 3 - UMBC Ciphers, Fall 2017
 ** Author:  Jermey Dixion
 ** User:    Innocent Kironji
 ** Date:    11/02/17
 ** Section: 0107
 ** E-mail:  wambugu1@umbc.edu
 **
 ** This file contains both declaration and implementation for all members
 **  pertaining to the Node class. Manages Nodes and how they operate
 **  as well as handeling how the linked list is linked (using private 
 **  member variables as pointers to themselves).
 **
 ** This is a file by professor Dixon that remains unedited from his 
 **  original version outside from these comments.
 ***************************************/

#ifndef NODE_H //Include/Header Guard
#define NODE_H //Include/Header Guard

class Node{
 public:
  // Name: Node - Default Constructor
  // Desc - Used to build a new node
  // Preconditions - None
  // Postconditions - Creates a new node
  Node(){
    m_data = 0;
    m_next = NULL;
  }
  // Name: Node - Overloaded Constructor
  // Desc - Used to build a new node with a passed character
  // Preconditions - Have a character
  // Postconditions - Creates a new node with the data populated
  Node(char c){
    m_data = c;
    m_next = NULL;
  }
  // Name: ~Node - Destructor
  // Preconditions - Have a node
  // Postconditions - Empties the node
  ~Node(){
    m_data = 0;
    m_next = NULL;
  }
  // Name: getChar()
  // Preconditions - Have a node
  // Postconditions - Returns the char in the data   
  char getChar(){
    return m_data;
  }
  // Name: setChar()
  // Preconditions - Have a node
  // Postconditions - Sets the char in the data
  void setChar(char c){
    m_data = c;
  }
  // Name: getNext()
  // Preconditions - Have a node
  // Postconditions - Returns the pointer
  Node* getNext(){
    return m_next;
  }
  // Name: setNext()
  // Preconditions - Have a node
  // Postconditions - Sets the target of the next pointer 
  void setNext(Node* next){
    m_next = next;
  }
 private:
  char m_data; //data for node
  Node* m_next; //Node pointer for node
};

#endif //Include Guard
