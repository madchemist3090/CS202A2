// Alex Olson		CS202		Assignment 2
// comm.cpp		4/26/2017

/*
    This file contains the classes that use dynamic binding. There
    is a base class that handles data structure connections as well
    as the messages. The four class that are dynamically linked to
    it are classes for email, text, facebook, and carrier pigeons.
*/

#include "data.h"


/********************************************************************
			    class base
********************************************************************/
//Default Constructor
//INPUT: void
base::base(void):next(NULL) {}


//Copy Constructor
//INPUT: communication base to copy
base::base(const base & to_copy):next(NULL) {}


//Char Constructor
//INPUT: information to add
base::base(const char * to_add):data(to_add) {}


//[VIRTUAL] Destructor
//INPUT: void
base::~base(void) {}


//Traverse to next communication object
//INPUT: void
//OUTPUT: next object in list
base *& base::go_next(void)
{
    return next;				//Traverse next
}


//Connect object to another object
//INPUT: object to connect to
//OUTPUT: void
void base::connect_next(base * connection)
{
    next = connection;				//Connect next
    return;
}


//Clear out any existing messages
//INPUT: void
//OUTPUT: void
void base::clear_message(void)
{
    message.update(" ");			//"Clear" out any data ;-)
    return;
}


//[VIRTUAL] message display
//INPUT: void
//OUTPUT: void
void base::display(void) const 
{
    cout << "\nMESSAGE: \n";			//Identify display data
    return;
}


//[VIRTUAL] communication method display
//INPUT: void
//OUTPUT: void
void base::display_comm(void) const 
{
    cout << "\nCOMMUNICATION METHOD: \n";	//Identify comm display
    return;
}


//[VIRTUAL] send a message
//INPUT: message to send
//OUTPUT: void
void base::send(const char * message)
{    
    return;
}



/********************************************************************
			    class email
********************************************************************/
//Default Constructor
//INPUT: void
email::email(void)
{
    message.update("Example EMAIL message");
}


//Copy Constructor
//INPUT: email to copy
email::email(const email & to_copy) {}


//Char constructor
//INPUT: email to add
email::email(const char * to_add):base(to_add) 
{
    message.update("Example EMAIL message");
}


//Destructor
//INPUT: void
email::~email(void) {}


//Display message
//INPUT: void
//OUTPUT: void
void email::display(void) const
{
    return message.display();			//Display message
}


//Display communication info
//INPUT: void
//OUTPUT: void
void email::display_comm(void) const
{
    cout << "\nEmail Address: ";
    return data::display();			//Display communication method
}


//[VIRTUAL] send a message
//INPUT: message to send
//OUTPUT: void
void email::send(const char * message)
{
    cout << "\nEmail sent";			//Send email
    return;
}



/********************************************************************
			    class text
********************************************************************/
//Default Constructor
//INPUT: void
text::text(void)
{
    message.update("Example TEXT message");
}


//Copy Constructor
//INPUT: text (phone) to copy
text::text(const text & to_copy) {}


//Char Constructor
//INPUT: phone number to add
text::text(const char * to_add):base(to_add) 
{
    message.update("Example TEXT message");
}


//Destructor
//INPUT: void
text::~text(void) {}


//Display message
//INPUT: void
//OUTPUT: void
void text::display(void) const
{
    return message.display();			//Display message
}


//Display communication info
//INPUT: void
//OUTPUT: void
void text::display_comm(void) const
{
    cout << "\nPhone Number: ";
    return data::display();			//Display communication method
}


//send a message
//INPUT: message to send
//OUTPUT: void
void text::send(const char * message)
{
    cout << "\nText sent";			//Send text message
    return;
}



/********************************************************************
			    class facebook
********************************************************************/
//Default Constructor
//INPUT: void
facebook::facebook(void)
{
    message.update("Example FACEBOOK message");
}


//Copy Constructor
//INPUT: facebook account to copy
facebook::facebook(const facebook & to_copy) {}


//Char Constructor
//INPUT: facebook account to add
facebook::facebook(const char * to_add):base(to_add) 
{
    message.update("Example FACEBOOK message");
}


//Destructor
//INPUT: void
facebook::~facebook(void) {}


//Display message
//INPUT: void
//OUTPUT: void
void facebook::display(void) const
{
    return message.display();			//Display message
}


//Display communication info
//INPUT: void
//OUTPUT: void
void facebook::display_comm(void) const
{
    cout << "\nFacebook Account: ";
    return data::display();			//Display communication method
}


//send a message
//INPUT: message to send
//OUTPUT: void
void facebook::send(const char * message)
{
    cout << "\nFacebook message sent";		//Send facebook message
    return;
}



/********************************************************************
			class carrier_pigeon
********************************************************************/
//Default Constructor
//INPUT: void
carrier_pigeon::carrier_pigeon(void):number_of_pigeons(0)
{
    message.update("Example PIGEON message");
}


//Copy Constructor
//INPUT: pigeon to clone
carrier_pigeon::carrier_pigeon(const carrier_pigeon & to_copy) {}


//Char Constructor
//INPUT: friend's addresss to add
carrier_pigeon::carrier_pigeon(const char * to_add, int number_of_birds):
    base(to_add), number_of_pigeons(number_of_birds)
{
    message.update("Example PIGEON message");
}


//Destructor
//INPUT: void
carrier_pigeon::~carrier_pigeon(void) {}


//Display message
//INPUT: void
//OUTPUT: void
void carrier_pigeon::display(void) const
{
    return message.display();			//Display message
}


//Display communication info
//INPUT: void
//OUTPUT: void
void carrier_pigeon::display_comm(void) const
{
    cout << "\nPigeon's Nesting Location: ";
    return data::display();			//Display communication method
}


//send a message
//INPUT: message to send
//OUTPUT: void
void carrier_pigeon::send(const char * message)
{
    if (number_of_pigeons < 1)			//Return if not enough birds
    {
	cout << "\nYou need pigeons to send a message";
	return;
    }
    --number_of_pigeons;			//Release pigeon
    cout << "\nPigeon released";
    return;
}



