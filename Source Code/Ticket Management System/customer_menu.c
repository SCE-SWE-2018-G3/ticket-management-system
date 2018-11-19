#include "customer_menu.h"
#include "ticket_container.h"
#include "auth.h"
#include <stdio.h>

void createTicket()
{
	wchar_t title[256];
	wchar_t type[256];
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
			struct Note* note = vector_getAt(notes, i);
			wprintf(L"\tDate: %S\n", ctime(note_getDate(note)));
			wprintf(L"\tAuthor: %s\n", note_getAuthor(note));
			wprintf(L"\t%s\n", note_getContent(note));
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
	wprintf(L"Q: My computer is on but I can't see anything on the screen.\n");
	wprintf(L"A: Try moving the mouse or hitting any key on the keyboard.\nIf that fails, locate the power button on the screen and press it.\n");
	wprintf(L"\n");
	wprintf(L"Q: I sent a document to print but it doesn't do anything\n");
	wprintf(L"A: Check if the printer has enough paper. Check if the paper tray is fully engaged. If all else fails, contact technical support.\n");
	wprintf(L"\n");
	system("PAUSE");
}

void updateContactInfo()
{
	// TODO
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
