#include "customer_menu.h"
#include "ticket_container.h"
#include "auth.h"
#include "i18n.h"
#include <stdio.h>

void createTicket()
{
	wchar_t title[128];
	wchar_t type[128];
	wchar_t description[512];

	system("CLS");
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT, I18N_LOCALE_CURRENT));
	wprintf(L"===============\n");
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_DESCRIPTION, I18N_LOCALE_CURRENT));
	wscanf(L"%s", description);
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_TITLE, I18N_LOCALE_CURRENT));
	wscanf(L"%s", title);
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_TYPE, I18N_LOCALE_CURRENT));
	wscanf(L"%s", type);

	struct Ticket* ticket = ticket_create(title, type, description, auth_getEmail());
	if (ticket != NULL)
	{
		ticketContainer_update(ticket);

		system("CLS");
		wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS, I18N_LOCALE_CURRENT));
		wprintf(L"==================\n");
		wprintf(L"%s", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_ELABORATION, I18N_LOCALE_CURRENT));
		wprintf(L"%s\n%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_TICKETID, I18N_LOCALE_CURRENT), ticket_getId(ticket));
		wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_PLEASESAVE, I18N_LOCALE_CURRENT));
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
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_VIEWTICKET, I18N_LOCALE_CURRENT));
	wprintf(L"========================\n");
	wprintf(L"%s\n", i18n_getString(I18N_STRING_CUSTOMER_VIEWTICKET_DESCRIPTION, I18N_LOCALE_CURRENT));
	wscanf(L"%s", ticket_id);
	struct Ticket* ticket = ticketContainer_getById(ticket_id);
	if (ticket != NULL)
	{
		time_t date = ticket_getDate(ticket);

		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_ID, I18N_LOCALE_CURRENT), ticket_getId(ticket));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_TITLE, I18N_LOCALE_CURRENT), ticket_getTitle(ticket));
		wprintf(L"%s: %S\n", i18n_getString(I18N_STRING_TICKET_DATE, I18N_LOCALE_CURRENT), ctime(&date));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_STATUS, I18N_LOCALE_CURRENT), ticket_getStatus(ticket));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_TIER, I18N_LOCALE_CURRENT), ticket_getTier(ticket));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_TYPE, I18N_LOCALE_CURRENT), ticket_getType(ticket));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_SEVERITY, I18N_LOCALE_CURRENT), ticket_getSeverity(ticket));
		wprintf(L"%s: %s\n", i18n_getString(I18N_STRING_TICKET_DESCRIPTION, I18N_LOCALE_CURRENT), ticket_getDescription(ticket));
		wprintf(L"%s:\n", i18n_getString(I18N_STRING_TICKET_NOTES, I18N_LOCALE_CURRENT));

		struct Vector* notes = ticket_getNotes(ticket);
		for (unsigned int i = 0; i < vector_getSize(notes); ++i)
		{
			struct Note* note = vector_getAt(notes, i);
			wprintf(L"\t%s: %S\n", i18n_getString(I18N_STRING_NOTE_DATE, I18N_LOCALE_CURRENT), ctime(note_getDate(note)));
			wprintf(L"\t%s: %s\n", i18n_getString(I18N_STRING_NOTE_AUTHOR, I18N_LOCALE_CURRENT), note_getAuthor(note));
			wprintf(L"\t%s\n", note_getContent(note));
		}
	}
	else
	{
		wprintf(L"%s\n", i18n_getString(I18N_STRING_NO_TICKET_BY_ID, I18N_LOCALE_CURRENT));
	}
	system("PAUSE");
}

void listTickets()
{
	// TODO
}

void viewFAQ()
{
	switch (i18n_getCurrentLocale())
	{
		case(I18N_LOCALE_ENGLISH):
		{
			wprintf(L"Q: My computer is on but I can't see anything on the screen.\n");
			wprintf(L"A: Try moving the mouse or hitting any key on the keyboard.\nIf that fails, locate the power button on the screen and press it.\n");
			wprintf(L"\n");
			wprintf(L"Q: I sent a document to print but it doesn't do anything\n");
			wprintf(L"A: Check if the printer has enough paper. Check if the paper tray is fully engaged. If all else fails, contact technical support.\n");
			wprintf(L"\n");
			break;
		}
	}
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
		menu_setTitle(menu, i18n_getString(I18N_STRING_CUSTOMER_WELCOME, I18N_LOCALE_CURRENT));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_CUSTOMER_CONTACTSUPPORT, I18N_LOCALE_CURRENT), createTicket));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_CUSTOMER_VIEWTICKET, I18N_LOCALE_CURRENT), viewTicket));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_CUSTOMER_LISTTICKETS, I18N_LOCALE_CURRENT), listTickets));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_CUSTOMER_UPDATECONTACTINFO, I18N_LOCALE_CURRENT), updateContactInfo));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_CUSTOMER_FAQ, I18N_LOCALE_CURRENT), viewFAQ));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_LOG_OUT, I18N_LOCALE_CURRENT), onLogOutCallback));
	}
	return menu;
}
