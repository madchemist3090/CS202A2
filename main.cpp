// Alex Olson		CS202		Assignment 2
// main.cpp		4/21/2017

/*
    This file contains a basic example of how an application
    program to monitor messages. The application has been
    left available for futher funcitonality when the need to
    actually "send" messages arises.
*/

#include "data.h"

int main()
{
    int i;					//Loop counter
    int selection = 10;				//User menu selection 
    char response;				//User communicaton choice
    char temp[TEMPSIZE];			//Temp description array
    contactBST contacts;			//User contacts
    commCLL methods;				//User communication methods

    welcome();					//Welcome user and clear screen
    
    //Create inital contact list
    cout << "\n Let's add some contacts to your contacts list\n";
    do						//Start adding contact
    {
	cout << "\nEnter a last name to add: ";
	cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
	contacts.add(temp);			//Add contact to list
	cout << "\nAdd another last name?";
    } while (again());				//Repeat until finished
    cout << "\nGreat! Now onto the main program...\n\n";

    //Main Menu
    do
    {
	selection = menu();
	switch (selection)
	{
	    //Add a contact
	    case 1: cout << "\nEnter a last name to add: ";
		cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
		contacts.add(temp);
		cout << "\n *** New contact added ***";
		break;

	    //Remove a contact
	    case 2: cout << "\nEnter a last name to remove: ";
		cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
		contacts.remove(temp);
		cout << "\n *** Contact removed ***";
		break;

	    //Display all contacts
	    case 3: contacts.display_all();
		break;

	    //Add communication method
	    case 4: methods.add();
		cout << "\n *** Communication method added ***";
		break;

	    //Remove communication method
	    case 5: cout << "\nEnter a communication method to remove: ";
		cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
		methods.remove_comm(temp);
		cout << "\n *** Communication method removed ***\n";
		break;

	    //Display all communication methods
	    case 6: methods.display_comm();
		break;

	    //Clear all messages
	    case 7: methods.clear_messages();
		    cout << "\n *** Messages Cleared *** \n";
		break;

	    //Display all messages
	    case 8: methods.display_messages();
		break;

	    //Send a message
	    case 9: cout << "\nWho do you want to send a message to?\n";
		contacts.display_all();
		cout << "\n\n Contact to send message to: ";
		cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
		cout << "\nWhich method do you want to use?"
		     << " (E)mail, (C)ell phone, (F)acebook, (P)igeon: ";
		cin >> response; cin.ignore(MAX, '\n');
		response = toupper(response);
		cout << "\nEnter your message:  ";
		cin.get(temp, MAX, '\n'); cin.ignore(MAX, '\n');
		switch (response)
		{   //Note: I would improve on this section if I had the time
		    case 'E': cout << "\nEmail sent";
			break;
		    
		    case 'C': cout << "\nText message sent";
			break;
		    
		    case 'F': cout << "\nFacebook message sent";
			break;
		    
		    case 'P': cout << "\nCarrier pigeon sent";
			break;
		    
		    default: cout <<"\nYou must pick a valid option\n";
			break;
		}
		break;
	    
	    //Default
	    default: cout << "\n Exiting program..."; 
		break;
	}
    } while (selection);			//Repeat until time to quit
    
    for (i = 0; i < 50; ++i) cout << endl;
    cout << "\t\tGoodbye\n\n\n\n\n";
    return 0;
}


