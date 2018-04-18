// Alex Olson		CS202		Assignment 2
// dataStructures.cpp	4/21/2017

/*
    This is file that contains the definitions of classes that
    have/manage the two main data structures of the program. The
    first data structure is a binary search tree of last names
    with the possibility of multiple first names. The second
    data structure is a circular linked list of base (communication)
    objects which are created dynamically at run-time;
*/

#include "data.h"


/********************************************************************
			class contactBST
********************************************************************/
//Default Constructor
//INPUT: void
contactBST::contactBST(void):root(NULL) {}


//Copy Constructor
//INPUT: conatactBST to copy
contactBST::contactBST(const contactBST & to_copy)
{
    if (root) clear (root);			//Clear out any garbage
    copy(root, to_copy.root);			//Copy tree
}


//Destructor
//INPUT: void
contactBST::~contactBST(void)
{
    clear(root);				//Recursively clear tree
}


//Add a leaf to the tree (sorted by last name)
//INPUT: last name to add
//OUTPUT: void
void contactBST::add(const char * last_name)
{
    if (!strlen(last_name))			//Exit if nothing to add
	return;
    
    //Build BSTnode
    BSTnode * temp = new BSTnode(last_name);	//Allocate new BSTnode
    char temp_first [50];			//Temp first name array
    do
    {
	cout << "Enter a first name to add: ";
	cin.get(temp_first, MAX, '\n'); cin.ignore(MAX, '\n');
	temp->add_first_name(temp_first);	//Add name to list
	cin.clear();	    //Clear input buffer in case of empty entry
	cout << "\nAdd another first name?";
    } while (again());				//Repeat until done
    
    
    //Insert BSTnode into tree
    if (!root)					//If the tree is empty
	root = temp;				//temp is the new root 
    else					//If not an empty tree
	insert(temp, root);			//Insert into the tree
    return;
}


//Remove a last name (and corresponding first names) from the tree
//INPUT: last name to remove
//OUTPUT: void
void contactBST::remove(const char * last_name)
{
    if(!strlen(last_name) || !root)		//Return if nothing to remove
	return;
    remove(last_name, root);			//Remove last name
    return;
}


//[WRAPPER] Display entire list of contacts
//INPUT: void
//OUTPUT: void
void contactBST::display_all(void) const
{
    return display_all(root);			//Display BST recursively
}


//////////////////////////////PROTECTED//////////////////////////////

//Makes a deep copy of a BST for the copy constructor
//INPUT: destination BSTnode, source BSTnode
//OUTPUT: void
void contactBST::copy(BSTnode *& dest, BSTnode * source)
{
    if (!source)				//Base case: nothing to copy
    {
	source = dest = NULL;			//Set everyhing to NULL
	return;
    }
    copy(dest->go_left(), source->go_left());	//Travese left
    dest = new BSTnode(*source);		//Copy in order
    copy(dest->go_right(), source->go_right());	//Traverse right
    return;
}


//Clears out a BST
//INPUT: tree to destroy
//OUTPUT: void
void contactBST::clear(BSTnode *& to_destroy)
{
    if (!to_destroy)				//Base case: nothing to delete
	return;
    clear(to_destroy->go_left());		//Traverse all the way left
    clear(to_destroy->go_right());		//Traverse all the way right
    if (to_destroy) delete to_destroy;		//Remove any data
    to_destroy = NULL;				//Reset to NULL
    return;
}


//Removes a node from the tree recursively
//INPUT: last name to remove, root of tree to search
//OUTPUT: void
void contactBST::remove(const char * last_name, BSTnode *& root)
{
    if (!root)					//Base case: nothing to delete
	return;
    remove(last_name, root->go_left());		//Recurse left
    remove(last_name, root->go_right());	//Recurse right

    if (!root->compare(last_name))		//If a match is found
    {						//Check the removal condition
	BSTnode * temp;				//For holding data to remove/replace
	//Case 1: No children
	if (!root->go_left() && !root->go_right())
	{
	    if (root) delete root;			//Remove leaf
	    root = NULL;
	}
	//Case 2: Two children
	else if (root->go_left() && root->go_right())
	{
	    temp = IOShelper(root->go_right());	    //Find IOS
	    temp->connect_left(root->go_left());  //Connect to BST
	    temp->connect_right(root->go_right());//Connect to BST
	    if (root) delete root;
	    root = temp;
	}
	//Case 3: Only one child
	else
	{
	    if (!root->go_right())		//If node has left child
	    {
		temp = root;			//Hold onto node to delete
		root = root->go_left();		//Reconnect tree
		if (temp) delete temp;		//Delete node
		temp = NULL;
	    }
	    else				//If node has right child
	    {
		temp = IOShelper(root->go_right());	//Find IOS
		temp->connect_right(root->go_right());	//Connect to BST
		if (root) delete root;		//Delete node
		root = temp;			//Replace root's data
	    }
	}
    }

    return;
}


//Finds the in order successor of a node in a BST
//INPUT: root to find IOS for
//OUTPUT: In order successor's data
BSTnode * contactBST::IOShelper(BSTnode *& root)
{
    if (!root)
	return NULL;
    if (!root->go_left())			//Base case: found IOS
    {
	cerr << "\n Current = \n\n"; 
	    root->display();
	cerr << "\n\n\n";
	BSTnode * ret = new BSTnode(*root);	//For returning ios data
	BSTnode * to_remove = root;		//For shifting the tree
	root = root->go_right();		//Shift tree
	delete to_remove; to_remove = NULL;	//Clean up tree
	return ret;				//Return ios data
    }
    return IOShelper(root->go_left());		//Traverse tree
}


//Display all contacts sharing the same last name
//INPUT: void
//OUTPUT: void
void contactBST::display_family(const BSTnode * last_name) const
{
    cout << "\n Last Name: ";
    last_name->display();			//Display last name
    last_name->display_first_names();		//Display first names
    return;
}


//Recursively display all members of a tree
//INPUT: tree to display
//OUTPUT: void
void contactBST::display_all(BSTnode * root) const
{
    if (!root)					//Base case: nothing to display
	return;
    display_all(root->go_left());		//Traverse left
    display_family(root);			//Display in order
    display_all(root->go_right());		//Traverse right
    return;
}


//Insert a last name node into the BST (alphabetical by last name)
//INPUT: BSTnode to insert, tree to insert into
//OUTPUT: void
void contactBST::insert(BSTnode * to_insert, BSTnode *& root)
{
    if(!root)					//If the node is empty:
	root = to_insert;			//Insert at a leaf
    int result = root->compare(to_insert->retrieve());
    if (result < 0)				//If alphabetically lesser
	insert(to_insert, root->go_left());	//Traverse left
    else if (result > 0)			//If alphabetically greater
	insert(to_insert, root->go_right());	//Traverse right
    return;
}



/********************************************************************
			class commCLL
********************************************************************/
//Default Constructor
//INPUT: void
commCLL::commCLL(void):rear(NULL){}


//Copy Constructor
//INPUT: commCLL to copy
commCLL::commCLL(const commCLL & to_copy){}


//Destructor
//INPUT: void
commCLL::~commCLL(void)
{
    base * head = rear->go_next();
    rear->connect_next(NULL);
    clear(head);
}


//[WRAPPER] Display communication methods
//INPUT: void
//OUTPUT: void
void commCLL::display_comm(void) const
{ 
    base * head = rear->go_next();		//Find the head
    rear->connect_next(NULL);			//Separate the list
    display_comm(head);				//Display the list
    rear->connect_next(head);			//Reattach the list
    return;
}


//[WRAPPER] Display messages
//INPUT: void
//OUTPUT: void
void commCLL::display_messages(void) const
{
    base * head = rear->go_next();		//Find the head
    rear->connect_next(NULL);			//Separate the list
    display_messages(head);			//Display the list
    rear->connect_next(head);			//Reattach the list
    return;
}


//Add a communication method
//INPUT: void
//OUTPUT: void
void commCLL::add(void)
{
    char response;				//User's selection
    char temp[MAX];				//For naming objects
    base * to_add;				//Communication to add
    cout << "\n Are you adding (E)mail, (C)ell phone, (F)acebook, (P)igeon: ";
    cin >> response; cin.ignore(MAX, '\n');	//Get user choice
    response = toupper(response);		//Refine choice
    switch (response)
    {	
	//Add an email
	case 'E': cout << "\nPlease enter your email: ";
	    cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
	    to_add = new email(temp);
	    break;

	//Add a phone number
	case 'C': cout << "\nPlease enter your phone number: ";
	    cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
	    to_add = new text(temp);
	    break;

	//Add a facebook account
	case 'F': cout << "\nPlease enter your facebook login: ";
	    cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
	    to_add = new facebook(temp);
	    break;

	//Add a carrier pigeon
	case 'P': cout << "\nEnter the nesting address of your pigeon: ";
	    cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
	    cout << "How many nested pigeons do you have?: ";
	    int number_of_pigeons;
	    cin >> number_of_pigeons; cin.ignore(MAX, '\n');
	    to_add = new carrier_pigeon(temp, number_of_pigeons);
	    break;
	
	//Do nothing
	default: cout << "\nPlease select a valid option";
	    to_add = NULL;
	    break;
    }
    if (!rear)					//If no existing list
    {	
	rear = to_add;				//Begin a new list
	to_add->connect_next(rear);
    }
    else					//Otherwise add to list
    {
	to_add->connect_next(rear->go_next());
	rear->connect_next(to_add);
    }
    return;
}


//[WRAPPER] Clear out all messages
//INPUT: void
//OUTPUT: void
void commCLL::clear_messages(void)
{
    base * head = rear->go_next();		//Find the head
    rear->connect_next(NULL);			//Separate the list
    clear_messages(head);			//Display the list
    rear->connect_next(head);			//Reattach the list
    return;
}


//[WRAPPER] Remove a communication method from the CLL
//INPUT: specific communication to remove
//OUTPUT: void
void commCLL::remove_comm(const char * to_remove)
{
    if (!strlen(to_remove))			//Return if not removing
	return;
    base * head = rear->go_next();		//Find the head
    rear->connect_next(NULL);			//Separate the list
    remove_comm(to_remove, head);		//Display the list
    base * tail = find_tail(head);		//Assign a tail
    tail->connect_next(head);			//Reattach the list
    rear = tail;				//Reassign rear
    return;
}


/////////////////////////////PROTECTED//////////////////////////////

//Find tail of list for reconnecting CLL
//INPUT: list to scan
//OUTPUT: tail of list
base * commCLL::find_tail(base * head) const
{
    if (!head)					//Return NULL for nothing
	return NULL;
    if (!head->go_next())			//Return end of list
	return head;
    return find_tail(head->go_next());		//Recurse through list
}


//Clear out a Circular List
//INPUT: list to clear
//OUTPUT: void
void commCLL::clear(base *& head)
{
    if (!head)				    //Base case: nothing to clear
	return;
    clear(head->go_next());			//Traverse to end
    if (head) delete head;			//Remove on the way back
    head = NULL;
    return;
}


//Recursively display communication methods via dynamic binding
//INPUT: head of the list to display
//OUTPUT: void
void commCLL::display_comm(base * head) const
{
    if (!head)				    //Return if nothing to display
	return;
    base * temp = head;				//RTTI base pointer
    email * ptr = dynamic_cast<email*> (temp);	//Check if email ptr
    if (ptr) ptr->display_comm();
    else					//Check if text ptr
    {
	text * ptr = dynamic_cast<text*> (temp);
	if (ptr) ptr->display_comm();
	else					//Check if facebook ptr
	{
	    facebook * ptr = dynamic_cast<facebook*> (temp);
	    if (ptr) ptr->display_comm();
	    else				//Check if pigeon ptr
	    {
		carrier_pigeon*ptr = dynamic_cast<carrier_pigeon*>(temp);
		if (ptr) ptr->display_comm();
		else ptr = NULL;
	    }
	}
    }
    return display_comm(head->go_next());	//Recurse list
}


//Recursively display all messages
//INPUT: head of list to display
//OUTPUT: void
void commCLL::display_messages(base * head) const
{
    if (!head)					//Return if not displaying
	return;
    cout << endl;
    head->display();				//Display message
    return display_messages(head->go_next());	//Recurse about list
}


//Recursively clear out all messages
//INPUT: head of list to clear messages from
//OUTPUT: void
void commCLL::clear_messages(base *& head)
{
    if (!head)					//Return if empty list
	return;
    head->clear_message();			//Clear message
    return clear_messages(head->go_next());	//Recurse list
}


//Recursively remove a communication method from the CLL
//INPUT: specific communication to remove, head and tail of list to search
//OUTPUT: void
void commCLL::remove_comm(const char* to_remove, base*& head)
{
    if (!head)					//Return if empty
	return;
    remove_comm(to_remove, head->go_next());	//Traverse to end
    if (!head->compare(to_remove))		//If match is found
    {
	base * temp = head;			//Set temp to head
	head = head->go_next();			//Recursion is awesome
	delete temp;				//Delete temp
	temp = NULL;				//Set temp to NULL
    }
    return;
}



