// Alex Olson		CS202		Assignment 2
// dataModules.cpp	4/21/2017

/*
    This file contains the building blocks needed for the data structures.
    The core of most of the program is the data class which basically acts
    as a specialized string class. Next is a node class which is derived
    from the data class. This class contains the connective pieces of a 
    LLL which happens to be the list class which is a standard, unordered
    LLL. The BSTnode class is the last class in this file and it is a 
    compound data structure where it has inherited the data class (for last
    names) but it has a list of first names attached to it. The BSTnode
    also has the connective pieces of a binary search tree.
*/

#include "data.h"


/********************************************************************
			Application Functions
********************************************************************/
//Determines if a user wishes to reapeat an action
//INPUT: void
//OUTPUT: true = repeat, false = no repeat
bool again(void)
{
    char selection;				//User selection

    cout << "\n Again? (y|n): ";
    cin >> selection;				//Get user selection
    cin.ignore(MAX, '\n');
    selection = toupper(selection);		//Refine user selection
    if (selection == 'Y')			//If user wants to repeat
	return true;				//Return true
    else					//Otherwise
	return false;				//Return false
}


//Clear screen and explain the program to the user
//INPUT:void
//OUTPUT: void
void welcome(void)
{
    for (int i = 0; i < 50; ++i) 
	cout << endl;				//Clear screen
    cout << "******************************************************************"
	 << "\n\n\t\tWelcome to communication hub\n"
	 << "\n   This program brings all of your communication to one place"
	 << "\n   You first need to create a list of contacts, then you can"
	 << "\n   add a contact method you control for keeping track of"
	 << "\n   messages recieved as well as the ability to send messages"
	 << "\n   to any of your contacts\n\n"
	 << "******************************************************************"
         << "\n\n\n";
    return;
}


//Display the menu and get the user's selection
//INPUT: void
//OUTPUT: user selection
int menu(void)
{
    int selection = -1;				//User seleciton
    do
    {
	cout << "\n\nWhat would you like to do?\n"
	     << "\n  (1) Add contacts"
	     << "\n  (2) Remove contacts"
	     << "\n  (3) Display contacts\n"
	     << "\n  (4) Add communication method"
	     << "\n  (5) Remove communication method"
	     << "\n  (6) Display communication methods\n"
	     << "\n  (7) Clear all messages"
	     << "\n  (8) Display messages"
	     << "\n  (9) Send message\n"
	     << "\n  (0) Quit\n"
	     << "\n\n Enter corresponding number: ";
	cin >> selection; cin.ignore(MAX, '\n');//Get user's selection
    } while (selection < 0 || selection > 9);	//Repeat until valid seleciton
    return selection;
}



/********************************************************************
			    class data
********************************************************************/
//Default Constructor
//INPUT: void
data::data(void):info(NULL){}


//Copy Constructor
//INPUT: data object to copy
data::data(const data & to_copy)
{
    data(to_copy.retrieve());
}


//Char Constructor
//INPUT: char array to add
data::data(const char * data_to_add)
{
    if (data_to_add)
    {
	info = new char [strlen(data_to_add) + 1];
	strcpy(info, data_to_add);
    }
    else
	info = NULL;
}
		

//Data destructor
//INPUT: void
data::~data(void)
{
    clear();
}


//Clears out info stored in object
//INPUT: void
//OUTPUT: void
void data::clear(void)
{
    if (info) delete [] info;			//Clear out any garbage
    info = NULL;				//Set the data to NULL
    return;
}


//Update stored data
//INPUT: new data to add
//OUTPUT: void
void data::update(const char * to_add)
{
    if (info) delete [] info; info = NULL;	//Clear out any garbage
    info = new char [strlen(to_add) + 1];	//Allocate new dynamic array
    strcpy(info, to_add);			//Read in new data
    return;
}


//Display data
//INPUT: void
//OUTPUT: void
void data::display(void) const
{
    if (info)					//If there is info
	cout << info << " ";			//Output info
    return;					//Return
}


//Compare data
//INPUT: data to compare
//OUTPUT: positive if match is larger, negative if match is smaller
int data::compare(const char * match) const
{
    return strcmp(match, info);			//Return comparison
}


//Retrieve data
//INPUT: void
//OUTPUT: returns a pointer to the stored data
char * data::retrieve(void) const
{
    return info;				//Return stored data
}


//Finds the string length
//INPUT: void
//OUTPUT: length of info string
int data::length(void) const
{
    return strlen(info);			//Return string length
}


/********************************************************************
			    class node
********************************************************************/
//Default Constructor
//INPUT: void
node::node(void):next(NULL) {}


//Copy Constructor
//INPUT: node to copy
node::node(const node & to_copy):data(to_copy.retrieve()), next(NULL) {}


//Char Construct
//INPUT: char to create a node for
node::node(const char * to_add):data(to_add), next(NULL) {}


//Traversal helper that gives access to protected data
//INPUT: void
//OUTPUT: node connected to next pointer
node *& node::go_next(void)
{
    return next;				//Return next node
}


//Connect a node's next pointer to another node
//INPUT: node to connect to
//OUTPUT: void
void node::connect_next(node * connection)
{
    next = connection;				//Make connection
    return;
}


/********************************************************************
			    class list
********************************************************************/
//Default Constructor
//INPUT: void
list::list(void):head(NULL) {}


//Copy Constructor
//INPUT: list to copy
list::list(const list & to_copy)
{
    if (head) clear(head);			//Clear pre-existing list
    copy(head, to_copy.head);			//Copy list
}


//Destructor
//INPUT: void
list::~list(void)
{
    clear(head);				//Clear the list
}


//Add a person to the list
//INPUT: The contact's first name
//OUTPUT: void
void list::add(const char * name_to_add)
{
    if (!strlen(name_to_add))			//Return if nothing to add
	return;  
    cout << "\n *** Adding " << name_to_add << " to the list\n";
    node * temp = new node(name_to_add);	//Create a new node
    temp->connect_next(head);			//Point next at head
    head = temp;				//Shift temp into list
    return;
}


//[WRAPPER] Remove a person from the list
//INPUT: First name passed in from contactBST, which holds the full name
//OUTPUT: void
void list::remove(const char * first_name)
{
    if (!strlen(first_name))			//Return if nothing to remove
	return;
    return remove(first_name, head);		//Recursively search for match
}


//[WRAPPER] Displays the entire list
//INPUT: void
//OUTPUT: void
void list::display_list(void) const
{
    cout << "\n    First Name(s): ";
    return display_list(head);			//Display the list
}


//Retrieve the head of the list
//INPUT: void
//OUTPUT: head of list
node *& list::retrieve(void)
{
    return head;				//Return the head of the list
}


//Makes a deep copy of a list
//INPUT: list to copy
//OUTPUT: void
void list::copy(node *& dest, node * source)
{
    if (!source)				//Base case: nothing to copy
    {
	source = dest = NULL;			//Set both to NULL
	return;
    }
    dest = new node(*source);			//Node copy constructor
    return copy(dest->go_next(), source->go_next());//Recursive traversal
}


//////////////////////////////PROTECTED//////////////////////////////

//Clears the dynamic memory of a LLL
//INPUT: list to destroy
//OUTPUT: void
void list::clear(node *& to_destroy)
{
    if (!to_destroy)				//Base case: nothing to delete
	return;
    clear(to_destroy->go_next());		//Traverse to end
    if (to_destroy)				//Delete on the way back
	delete to_destroy;
    to_destroy = NULL;				//Set all to NULL
    return;
}


//Recursively removes an instance of an item from the list
//INPUT: item to remove
//OUTPUT: void
void list::remove(const char * to_remove, node *& head)
{
    if (!head)					//Base case: nothing to remove
	return;
    remove(to_remove, head->go_next());		//Recursively traverse list
    if (!head->compare(to_remove))		//If matching
    {
	node * temp = head;			//Set temp to head
	head = head->go_next();			//Recursion is awesome
	delete temp;				//Delete temp
	temp = NULL;				//Set temp to NULL
    }
    return;
}


//Recursively display the list
//INPUT: head of list to display
//OUTPUT: void
void list::display_list(node * head) const
{
    if (!head)					//Base case: nothing to display
	return;
    cout << "\n\t";				//Add output separation
    head->display();				//Display data
    return display_list(head->go_next());	//Traverse
}



/********************************************************************
			  class BSTnode
********************************************************************/
//Default Constructor
//INPUT: void
BSTnode::BSTnode(void):left(NULL), right(NULL) {}


//Copy Constructor
//INPUT: BST node to copy
BSTnode::BSTnode(BSTnode & to_copy):data(to_copy.retrieve()),
    left(NULL), right(NULL), first_names(to_copy.retrieve_list()) {}


//Char Constructor
//INPUT: Last name to construct BSTnode for
BSTnode::BSTnode(const char * to_add):data(to_add), left(NULL), right(NULL) {}


//Traverse to the left node
//INPUT: void
//OUTPUT: left child node
BSTnode *& BSTnode::go_left(void)
{
    return left;				//Return left node
}


//Traverse to the right node
//INPUT: void
//OUTPUT: right child node
BSTnode *& BSTnode::go_right(void)
{
    return right;				//Return right node
}


//Connects node to a left child
//INPUT: child to connect
//OUTPUT: void
void BSTnode::connect_left(BSTnode * connection)
{
    left = connection;				//Connect left child
    return;
}


//Connects node to a right child
//INPUT: child to connect
//OUTPUT: void
void BSTnode::connect_right(BSTnode * connection)
{
    right = connection;				//Connect right child
    return;
}


//Add a first name to associate with the BSTnode last name
//INPUT: first name to add
//OUTPUT: void
void BSTnode::add_first_name(const char * to_add)
{
    if (!strlen(to_add))			//Return if nothing to add
	return;
    return first_names.add(to_add);		//Add a first name
}


//Remove a first name from the list
//INPUT: first name to remove
//OUTPUT: void
void BSTnode::remove_first_name(const char * to_remove)
{
    if (!strlen(to_remove))			//Return if nothing to remove
	return;
    return first_names.remove(to_remove);	//Remove a name
}


//Display the first names associated with the node's last name
//INPUT: void
//OUTPUT: void
void BSTnode::display_first_names(void) const
{
    return first_names.display_list();		//Display first names
}


//Retrieves the head of a linear linked list for copying
//INPUT: void
//OUTPUT: list of first names
list & BSTnode::retrieve_list()
{
    return first_names;				//Return list of first names
}



