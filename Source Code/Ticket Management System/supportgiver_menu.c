#include "supportgiver_menu.h"
#include "ticket_container.h"
#include "i18n.h"
#include <stdio.h>
#include <string.h>

void printTicketsArray(struct Vector* tickets)
{
	if (tickets != NULL)
	{
		for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			struct Ticket* ticket = vector_getAt(tickets, i);
			wprintf(L"%s: %s\n", ticket_getId(ticket), ticket_getTitle(ticket));
		}
		wprintf(L"%s: %d\n", i18n_getString(I18N_STRING_TICKETS_THAT_ANSWER_CRITERIA, I18N_LOCALE_CURRENT), vector_getSize(tickets));
	}
	else
	{
		wprintf(L"%s: 0\n", i18n_getString(I18N_STRING_TICKETS_THAT_ANSWER_CRITERIA, I18N_LOCALE_CURRENT));
	}
}

bool filterByStatus(void* ticket, void* status)
{
	return wcscmp(ticket_getStatus(ticket), status) != 0;
}

bool sortByTitle(void* ticket1, void* ticket2)
{
	return wcscmp(ticket_getTitle(ticket1), ticket_getTitle(ticket2)) > 0;
}

void browseTickets()
{
	wprintf(L"%s\n", i18n_getString(I18N_STRING_BROWSE_TICKETS, I18N_LOCALE_CURRENT));
	wprintf(L"==============\n");
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets != NULL)
	{
		printTicketsArray(tickets);

		bool go_back = false;
		while (!go_back)
		{
			// TODO: Rewrite this function using the Menu and MenuOption system
			wprintf(L"\n");
			wprintf(L"%s\n", i18n_getString(I18N_STRING_TICKETS_FILTER_QUESTION, I18N_LOCALE_CURRENT));
			wprintf(L"1: %s\n", i18n_getString(I18N_STRING_FILTER_BY_STATUS, I18N_LOCALE_CURRENT));
			wprintf(L"2: %s\n", i18n_getString(I18N_STRING_FILTER_BY_TIER, I18N_LOCALE_CURRENT));
			wprintf(L"3: %s\n", i18n_getString(I18N_STRING_FILTER_BY_TYPE, I18N_LOCALE_CURRENT));
			wprintf(L"4: %s\n", i18n_getString(I18N_STRING_FILTER_BY_STAKEHOLDERS, I18N_LOCALE_CURRENT));
			wprintf(L"5: %s\n", i18n_getString(I18N_STRING_SEARCH_BY_CUSTOMER_EMAIL, I18N_LOCALE_CURRENT));
			wprintf(L"6: %s\n", i18n_getString(I18N_STRING_SEARCH_BY_TAGS, I18N_LOCALE_CURRENT));
			wprintf(L"7: %s\n", i18n_getString(I18N_STRING_SORT_BY_TITLE, I18N_LOCALE_CURRENT));
			wprintf(L"%s\n", i18n_getString(I18N_STRING_GO_BACK, I18N_LOCALE_CURRENT));
			char input[2];
			bool input_is_valid;
			do
			{
				input_is_valid = true;
				fgets(input, 2, stdin);
				wchar_t input_as_char = input[0];
				switch (input_as_char)
				{
					case('1'): // Filter by status
					{
						wchar_t* ctx;
						wchar_t status[32];
						wprintf(L"%s\n", i18n_getString(I18N_STRING_PLEASE_INPUT_STATUS, I18N_LOCALE_CURRENT));
						wscanf(L"%s", status);
						wcstok(status, "\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, filterByStatus, status);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('2'): // Filter by tier
					{
						// TODO
						break;
					}
					case('3'): // Filter by type
					{
						// TODO
						break;
					}
					case('4'): // Filter by stakeholders
					{
						// TODO
						break;
					}
					case('5'): // Search by customer email
					{
						// TODO
						break;
					}
					case('6'): // Search by tags
					{
						// TODO
						break;
					}
					case('7'): // Sort by title
					{
						struct Vector* sorted_vector = vector_sort(tickets, sortByTitle);
						printTicketsArray(sorted_vector);
						vector_destroy(sorted_vector);
						break;
					}
					case('q'):
					case('Q'):
					{
						go_back = true;
						break;
					}
					default:
					{
						input_is_valid = false;
						wprintf(L"%s.\n", i18n_getString(I18N_STRING_INVALID_INPUT, I18N_LOCALE_CURRENT));
					}
				}
			} while (!input_is_valid);
		}
	}
	else
	{
		wprintf(L"%s\n", i18n_getString(I18N_STRING_NO_TICKETS, I18N_LOCALE_CURRENT));
		system("PAUSE");
	}
}

void doNothing2()
{
}

struct Menu* createSupportGiverMenu(void(*onLogOutCallback)())
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, i18n_getString(I18N_STRING_SUPPORTGIVER_WELCOME, I18N_LOCALE_CURRENT));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_SUPPORTGIVER_OPENTICKET, I18N_LOCALE_CURRENT), doNothing2));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_SUPPORTGIVER_VIEWTICKET, I18N_LOCALE_CURRENT), doNothing2));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_SUPPORTGIVER_BROWSETICKETS, I18N_LOCALE_CURRENT), browseTickets));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_SUPPORTGIVER_CREATEUSER, I18N_LOCALE_CURRENT), doNothing2));
		menu_addOption(menu, menuOption_create(i18n_getString(I18N_STRING_LOG_OUT, I18N_LOCALE_CURRENT), onLogOutCallback));
	}
	return menu;
}
