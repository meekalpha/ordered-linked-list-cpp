#ifndef ORDEREDLIST_H
#define ORDEREDLIST_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class Node
{
public:
   double item; // data item
   Node *next; // pointer to next node
   Node(double);// constructor
};
// constructor
Node::Node(double value){
   item = value;
   next = NULL;
}

class OrderedList
{
   // friend operator functions
   friend ostream &operator<<(ostream &, const OrderedList &);
   friend istream &operator>>(istream &, OrderedList &);

public:
   // constructors
   OrderedList():_head(NULL),size(0) {};
   OrderedList(const OrderedList &); // copy constructor

   // destructor
   ~OrderedList();

   // operator functions
   OrderedList operator+(OrderedList&); // merges two OrderedLists
   double operator[](int) const; // subscript operator returns rvalue
     // assignment

   void insert(double); // inserts an item
   bool remove(int); // remove i th item
   void pop(); // pop the first item

private:
   Node *_head;
   int size;
};

// copy constructor ---------------------------------------------------------------
OrderedList::OrderedList(const OrderedList &inList)
{
   *this = inList;

} //end copy constructor

// destructor-----------------------------------------------------------------------
OrderedList::~OrderedList()
{
  if(_head!=0) // list is not empty
  {
     Node *currentPtr = _head;
     Node *tempPtr;

     while(currentPtr!=NULL) // delete remaining nodes
     {
        tempPtr = currentPtr;
        currentPtr=currentPtr->next;
        delete tempPtr;
     } // end while
  } // end if
} // end destructor

// merge two OrderedLists ----------------------------------------------------------------
OrderedList OrderedList::operator+(OrderedList &inList)
{

 OrderedList merged; //OrderedList to hold merged OrderedLists

 Node *current = _head; 

 while (current != NULL) { //iterate through this
    merged.insert(current->item); //add each element to merged
    current = current->next; 
 }

 current = inList._head;

 while (current != NULL) { //iterate through inList
    merged.insert(current->item); //add each value to merged
    current = current->next;
 }
 return merged;

} // end operator+ function

// return rvalue------------------------------------------------------------------
double OrderedList::operator[](int n) const
{ 
   
    Node *currentPtr;
    currentPtr = _head;

    if(n <= 0 || n > size) //requests bad position
    {
        cout << "Error: Node does not exist";
    }
    for (int i = 0; i < n - 1 ; i++) //iterates to correct element
        currentPtr = currentPtr->next;
    return currentPtr->item; //returns this[n]

} //end operator[] function

// assignment-------------------------------------------------------------------------
const OrderedList &OrderedList::operator=(const OrderedList &inList) //assignment
{

   while (_head != NULL){ // list is not empty
      pop(); //empty this list
   }
  
   Node* current = inList._head; 
   while(current != NULL) //iterate through inList
   {
      	 insert(current->item); //place each value into this
      	 current=current->next;
   }
   return *this;

}//end operator= function


// insert node----------------------------------------------------------------------------
void OrderedList::insert(double value)
{
  size++;
  Node *newPtr = new Node(value); 
  
  if (_head==NULL) //list is empty
    _head = newPtr;
  else if (value <= _head->item){ // value belongs at front
    newPtr->next=_head;
    _head = newPtr;
  } else {
    Node *currentPtr = _head;
    while (currentPtr->next!=NULL) {
      if (value > currentPtr->item && value < currentPtr->next->item || value == currentPtr->item){ 
      // value belongs somewhere in the middle
        Node *temp = currentPtr->next;
        currentPtr->next = newPtr;
        newPtr->next = temp;
        return;
      }
      currentPtr=currentPtr->next;
    }
    if (value >= currentPtr->item){ //value belongs at the end
       currentPtr->next = newPtr;
    }
  }
}

// remove node--------------------------------------------------------------------------------
bool OrderedList::remove(int pos)
{
  Node *tempPtr = _head; 
  if(pos <= 0 || pos > size) //bad position
  {
       cout << "Error: Node does not exist\n";
       return false;
  } 
  else if (size == 1) //remove only element
  {
       _head=NULL;
  }  
  else 
  {
    if(pos == 1) //remove 1st element
       _head = _head->next;
    else 
       for (int i = 1; i < pos - 1; i++) //iterate to specified element
             tempPtr = tempPtr->next;
       tempPtr->next = tempPtr->next->next; //remove specified node
  }
  size--;
  return true;
}

// pop the first item
void OrderedList::pop()
{
  remove(1);
}

#endif

//overloaded stream insertion operator
ostream &operator<<( ostream &output, const OrderedList &inList)
{ 
	cout << "The list is: "; // look pretty
   
	if (inList._head == NULL) cout << "empty"; //if empty

	for (int i = 1; i <= inList.size; i++) //iterate through
	{
		output << inList[i] << ' ';
	}
	cout << "\n";
	return output;
}

// overloaded stream extraction operator
istream &operator>>( istream &input, OrderedList &outList)
{
	double value;
	input >> value;
	outList.insert(value);

	return input;

}
