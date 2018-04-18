// Alex Olson		CS202		Assignment 2
// data.h		4/21/2017

/*
    This is the general header file covering all of the .cpp files
    in one place. It contains the declarations and relationships of 
    the libraries, namespace, constants, misc. functions, and all 
    of the classes needed to run the communication program.
*/

#include <cstdlib>
#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

const int MAX = 1000;				//Primary usage in ignore()
const int TEMPSIZE = 100;			//Temp used for dynamic memory
bool again(void);				//Choice to repeat
void welcome(void);				//Welcome user
int menu(void);					//Display menu, get selection

/********************************************************************
			    dataModules
********************************************************************/
//Dynamic character array class
class data
{
    public:
	data(void);				//Constructor
	data(const data & to_copy);		//Copy Constructor
	explicit data(const char * data_to_add);//Char Constructor
	~data(void);				//Destructor
	void clear(void);			//Clears data
	void update(const char * to_add);	//Updates info
	void display(void) const;		//Displays info
	int compare(const char * match) const;	//Compares info
	char * retrieve(void) const;		//Retrieve info
	int length(void) const;			//Finds the string length

    protected:
	char * info;				//Dynamic char array
};


//Class for node object, used in a LLL
//Inherits --> string/naming functionality
class node: public data
{
    public:
	node(void);				//Constructor
	node(const node & to_copy);		//Copy Constructor
	explicit node (const char * to_add);	//Char Constructor
	node *& go_next(void);			//Traverse to next node
	void connect_next(node * connection);	//Connect next node
    
    protected:
	node * next;				//Next node in LLL
};


//Linear linked list of nodes
class list
{
    public:
	list(void);				//Constructor
	list(const list & to_copy);		//Copy Constructor
	~list(void);				//Destructor
	void add(const char * to_add);		//Add an item
	void remove(const char * to_remove);	//Remove an item
	void display_list(void) const;		//Displays the entire list
	node *& retrieve(void);			//Retrieve head of LLL	
	void copy(node *& dest, node * source);	//Recursively copies a LLL

    protected:
	node * head;				//Head of LLL
	void clear(node *& to_destroy);		//REcursively clears a LLL
	void remove(const char * to_remove,
		    node *& head);		//Recursive item removal
	void display_list(node * head) const;	//Recursive list display
};


//Building block object for BST, sorted by last name
//Inherits --> last name
class BSTnode: public data
{
    public:
	BSTnode(void);				//Constructor
	BSTnode(BSTnode & to_copy);		//Copy constructor
	explicit BSTnode(const char * to_add);	//Char constructor
	BSTnode *& go_left(void);		//Traverse left
	BSTnode *& go_right(void);		//Traverse right
	void connect_left(BSTnode * connection);//Connect left side
	void connect_right(BSTnode * connection);//Connect right side
	void add_first_name(const char * to_add);//Add a first name
	void remove_first_name(const char * to_remove);//Remove a first name
	void display_first_names(void) const;	//Display first names
	list & retrieve_list(void);		//List copy helper

    protected:
	BSTnode * left;				//Left node
	BSTnode * right;			//Right node
	list first_names;			//List of first names
};


/********************************************************************
			  dataStructures
********************************************************************/

//Contact list, sorted by last name, stored in a binary search tree
class contactBST
{
    public:
	contactBST(void);			//Constructor
	contactBST(const contactBST & to_copy);	//Copy Constructor
	~contactBST(void);			//Destructor

	void add(const char * last_name);	//Add a leaf
	void remove(const char * last_name);	//Remove a BSTnode
	void display_all(void) const;		//Display all contacts

    protected:
	BSTnode * root;					//Root of BST
	void copy(BSTnode *& dest, BSTnode * source);	//Copy a BST
	void clear(BSTnode *& to_destroy);		//Clear a BST
	void remove(const char * name, BSTnode *& root);//Recursive removal
	BSTnode * IOShelper(BSTnode *& root);		//Finds IOS
	void display_family(const BSTnode * last_name) const;//Display family
	void display_all(BSTnode * root) const;		//Recursive display
	void insert(BSTnode * to_insert, BSTnode *& root);//Insert into BST
};


//Class for a circular linked list of different communication objects
//Performs dynamic binding
class commCLL
{
    public:
	commCLL(void);				//Constructor
	commCLL(const commCLL & to_copy);	//Copy Constructor
	~commCLL(void);				//Destructor
	void add(void);				//Add a communication method
	void display_comm(void) const;		//Display all communication
	void display_messages(void) const;	//Display all messages
	void clear_messages(void);		//Clear all messages
	void remove_comm(const char * to_remove);//Remove an item from the CLL

    protected:
	class base * rear;			//CLL of communication objects
	base * find_tail(base * head) const;	//Find tail for reconnecting CLL
	void clear(base *& head);		//Clears out the CLL
	void display_comm(base * head) const;	//Display all communication
	void display_messages(base * head) const;//Display all messages
	void clear_messages(base *& head);	//Clear all messages
	void remove_comm(const char * to_remove,
			 base *& head);		//Remove an item from the CLL
};



/********************************************************************
      			        comm
********************************************************************/
//Basics of communicating
//Inherits --> communication info (e.g. phone number, account name, etc.)
class base: public data
{
    public:
	base(void);				//Constructor
	base(const base & to_copy);		//Copy Constructor
	base(const char * to_add);		//Char Constructor
	virtual ~base(void);			//Virtual destructor
	base *& go_next(void);			//Traverse to next object
	void connect_next(base * connection);	//Connect to next object
	void clear_message(void);		//Clear out a message
	virtual void display(void) const;	//Display message
	virtual void display_comm(void) const;	//Display communication info
	virtual void send(const char * message);//Send a message	
    
    protected:
	base * next;				//Next communication method
	data message;				//Message
};


//Email communication
//Inherits --> name of email address
class email: public base
{
    public:
	email(void);				//Constructor
	email(const email & to_copy);		//Copy Constructor
	email(const char * to_add);		//Char constructor
	~email(void);				//Destructor
	void display(void) const;		//Display message
	void display_comm(void) const;		//Display communication info
	void send(const char * message);	//Send a message
};


//Text message communication
//Inherits --> Phone number
class text: public base
{
    public:
	text(void);				//Constructor
	text(const text & to_copy);		//Copy Constructor
	text(const char * to_add);		//Char Constructor
	~text(void);				//Destructor
	void display(void) const;		//Display message
	void display_comm(void) const;		//Display communication info  
	void send(const char * message);	//Send a message
};


//Facebook communication
//Inherits --> Account login
class facebook: public base
{
    public:
	facebook(void);				//Constructor
	facebook(const facebook & to_copy);	//Copy Constructor
	facebook(const char * to_add);		//Char Constructor
	~facebook(void);			//Destructor
	void display(void) const;		//Display message
	void display_comm(void) const;		//Display communication info 
	void send(const char * message);	//Send a message
};


//Carrier pigeon communication
//Inherits --> Pigeon's nesting location (i.e. friend's address)
class carrier_pigeon: public base
{
    public:
	carrier_pigeon(void);			//Constructor
	carrier_pigeon(const carrier_pigeon & to_copy);//Copy Constructor
	carrier_pigeon(const char * to_add,
		       int number_of_birds);	//Char constructor
	~carrier_pigeon(void);			//Destructor	
	void display(void) const;		//Display message
	void display_comm(void) const;		//Display communication info
	void send(const char * message);	//Send a message

    protected:
	int number_of_pigeons;
};



