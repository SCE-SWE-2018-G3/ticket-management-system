#include "customer_menu.h"
#include "ticket_container.h"
#include "auth.h"
#include <stdio.h>
#include <stdbool.h>
#include "Input_manip.h"

void createTicket()
{
	wchar_t title[256];
	wchar_t type[256];
	wchar_t description[512];

	system("CLS");
	wprintf(L"Contact Support\n");
	wprintf(L"===============\n");
	wprintf(L"Please describe what happened.\n");
	input_wchar(description,512);		
	wprintf(L"Please give a short title to the incident.\n");
	input_wchar(title, 256);
	wprintf(L"Please list the type(s) related to this incident.\n");
	input_wchar(type, 256);

	struct Ticket* ticket = ticket_create(title, type, description, auth_getEmail());
	if (ticket != NULL)
	{
		ticketContainer_update(ticket);

		system("CLS");
		wprintf(L"Support Call Saved\n");
		wprintf(L"==================\n");
		wprintf(L"Your support call was saved in the system.");
		wprintf(L"Your ticket ID is:\n%s\n", ticket_getId(ticket));
		wprintf(L"Please save this ID for future reference.\n");
		system("PAUSE");
	}
	else
	{
		fwprintf(stderr, L"Failed to create ticket\n");
	}
}

void viewTicket()
{
	wchar_t ticket_id[128];

	system("CLS");
	wprintf(L"View Support Call Status\n");
	wprintf(L"========================\n");
	wprintf(L"Please input the ticket ID given to you when contacting support.\n");
	wprintf(L"Alternatively, find the ticket ID by going back and selecting 'List My Support Calls'.\n");
	wscanf(L"%s", ticket_id);
	struct Ticket* ticket = ticketContainer_getById(ticket_id);
	if (ticket != NULL)
	{
		time_t date = ticket_getDate(ticket);

		wprintf(L"Ticket ID: %s\n", ticket_getId(ticket));
		wprintf(L"Title: %s\n", ticket_getTitle(ticket));
		wprintf(L"Date opened: %S\n", ctime(&date));
		wprintf(L"Status: %s\n", ticket_getStatus(ticket));
		wprintf(L"Tier: %s\n", ticket_getTier(ticket));
		wprintf(L"Type: %s\n", ticket_getType(ticket));
		wprintf(L"Severity: %s\n", ticket_getSeverity(ticket));
		wprintf(L"Description: %s\n", ticket_getDescription(ticket));
		wprintf(L"Notes:\n");

		struct Vector* notes = ticket_getNotes(ticket);
		for (unsigned int i = 0; i < vector_getSize(notes); ++i)
		{
			wprintf(L"%s\n", vector_getAt(notes, i));
		}
	}
	else
	{
		wprintf(L"Could not find ticket with this ID.\n");
	}
	system("PAUSE");
}

void listTickets()
{
	// TODO
}

void viewFAQ()
{
	system("CLS");
	wprintf(L"Frequently Asked Questions\n");
	wprintf(L"========================\n");
	wprintf(L"Q: My computer is on but I can't see anything on the screen.\n");
	wprintf(L"A: Try moving the mouse or hitting any key on the keyboard.\nIf that fails, locate the power button on the screen and press it./nCheck the connectivity of the screen monitor to the computer, and check if the screen is on.\n");
	wprintf(L"\n");
	wprintf(L"Q: I sent a document to print but it doesn't do anything.\n");
	wprintf(L"A: Check if the printer has enough paper. Check if the paper tray is fully engaged. Check for paper jams. If all else fails, contact technical support.\n");
	wprintf(L"\n");
	wprintf(L"Q: I can't turn on my computer.\n");
	wprintf(L"A: First of all check the electric supply, and if the switch behind the computer is on. After that, try to disconnect the power cord from the computer, and keep the power button pressed for 10 seconds,/nthen reinsert the power cord and try to turn on the computer.\n");
	wprintf(L"\n");
	wprintf(L"Q: My network doesn't work (there's an X symbol over the internet symbol).\n");
	wprintf(L"A: Check if there is light coming from the ethernet cable (it's on the lower side behind the computer). It looks like a phones connection to the wall. Check connectivity of said cable. Try right clicking that icon, and making sure the internet isn't disabled. if using netstick, try to reinsert the netstick.\n");
	wprintf(L"\n");
	wprintf(L"Q: My computer works slowly.\n");
	wprintf(L"A: Try to close programs to reduce work stress on the computer. If you didn't restart the computer in a while, do so. If that doesn't help then delete temporary files from the computer; you can find them by seraching %%temp%% in the search bar in the start menu. Check if the C: drive is full, and if it is then clean it up.\n");
	wprintf(L"\n");
	wprintf(L"Q: A program doesn't start no matter how many times I try to open it.\n");
	wprintf(L"A: Try pressing CTRL + ALT + DEL or ctrl + shift + esc to open the task manager. There search for the programs name, right click it, and then on \"end process\". Now try to open the program again.\n");
	wprintf(L"\n");
	system("PAUSE");
}

void updateContactInfo()
{	
	system("CLS");
	char email[512];
	wchar_t password[50];
	wchar_t name[50];
	wchar_t phone_number[20];	
	struct User* logged_user=auth_getUser(); //fetchs the user from the container
	wprintf(L"Contact Info update\n");
	wprintf(L"===============\n");
	wprintf(L"enter 'no' every field you wish to not update.\n");
	wprintf(L"Update email:\n");
	input_char(email, 512);
	wprintf(L"Update password:\n");
	input_wchar(password, 50);
	wprintf(L"Update name:\n");
	input_wchar(name, 50);
	wprintf(L"Update Phone number:.\n");
	input_wchar(phone_number, 50);
	if (!input_valid_email(email))
		wprintf(L"invalid Email, email won't be updated:.\n");
	else if (!strcmp(email,"no"))
		wprintf(L"email won't be updated:.\n");
	else
		user_setEmail(logged_user,email);
	if (wcscmp(password,L"no"))
		user_setPassword(logged_user, password, false); //The initial state of a password is that it's not hashed yet.
	if (wcscmp(name, L"no"))
		user_setName(logged_user, name);
	if (wcscmp(phone_number, L"no"))
		user_setPhone(logged_user, phone_number);		
	system("PAUSE");
	
}

struct Menu* createCustomerMenu(void(*onLogOutCallback)())
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Contact Support", createTicket));
		menu_addOption(menu, menuOption_create(L"View Support Call Status", viewTicket));
		menu_addOption(menu, menuOption_create(L"List My Support Calls", listTickets));
		menu_addOption(menu, menuOption_create(L"Update Contact Information", updateContactInfo));
		menu_addOption(menu, menuOption_create(L"FAQ / Q&A", viewFAQ));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback));
	}
	return menu;
}
