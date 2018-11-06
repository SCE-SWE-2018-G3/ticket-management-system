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
		wscanf(L"%s");
	}
	else
	{
		fwprintf(stderr, L"Failed to create ticket\n");
	}
}

void doNothing1()
{
}

struct Menu* createCustomerMenu()
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Contact Support", createTicket));
		menu_addOption(menu, menuOption_create(L"View Support Call Status", doNothing1));
		menu_addOption(menu, menuOption_create(L"List My Support Calls", doNothing1));
		menu_addOption(menu, menuOption_create(L"Update Contact Information", doNothing1));
		menu_addOption(menu, menuOption_create(L"FAQ / Q&A", doNothing1));
		menu_addOption(menu, menuOption_create(L"Log Out", doNothing1));
	}
	return menu;
}
