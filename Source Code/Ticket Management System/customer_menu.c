#include "customer_menu.h"
#include "ticket.h"
#include "auth.h"
#include <stdio.h>

void createTicket()
{
	wchar_t title[128];
	wchar_t type[128];
	wchar_t description[512];

	system("CLS");
	wprintf(L"Contact Support\n");
	wprintf(L"===============\n");
	wprintf(L"Please describe what happened.\n");
	wscanf(L"%s", description);
	wprintf(L"Please give a short title to the incident.\n");
	wscanf(L"%s", title);
	wprintf(L"Please list the type(s) related to this incident.\n");
	wscanf(L"%s", type);

	struct Ticket* ticket = ticket_create(title, type, description, auth_getEmail());
	if (ticket != NULL)
	{
		ticket_save(ticket);

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

void viewFAQ()
{
	wprintf(L"Q: My computer is on but I can't see anything on the screen.\n");
	wprintf(L"A: Try moving the mouse or hitting any key on the keyboard.\nIf that fails, locate the power button on the screen and press it.\n");
	wprintf(L"\n");
	wprintf(L"Q: I sent a document to print but it doesn't do anything\n");
	wprintf(L"A: Check if the printer has enough paper. Check if the paper tray is fully engaged. If all else fails, contact technical support.\n");
	wprintf(L"\n");
	system("PAUSE");
}

void doNothing1()
{
}

struct Menu* createCustomerMenu(void(*onLogOutCallback)())
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Contact Support", createTicket));
		menu_addOption(menu, menuOption_create(L"View Support Call Status", doNothing1));
		menu_addOption(menu, menuOption_create(L"List My Support Calls", doNothing1));
		menu_addOption(menu, menuOption_create(L"Update Contact Information", doNothing1));
		menu_addOption(menu, menuOption_create(L"FAQ / Q&A", viewFAQ));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback));
	}
	return menu;
}
