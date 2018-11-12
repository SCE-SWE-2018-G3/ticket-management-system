#include "supportgiver_menu.h"
#include "ticket_container.h"
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
		wprintf(L"Tickets that answer the criteria: %d\n", vector_getSize(tickets));
	}
	else
	{
		wprintf(L"Tickets that answer the criteria: 0\n");
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
	wprintf(L"Browse Tickets\n");
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
			wprintf(L"Would you like to search/filter/sort the results?\n");
			wprintf(L"1: Filter by status\n");
			wprintf(L"2: Filter by tier\n");
			wprintf(L"3: Filter by type\n");
			wprintf(L"4: Filter by stakeholders\n");
			wprintf(L"5: Search by customer email\n");
			wprintf(L"6: Search by tags\n");
			wprintf(L"7: Sort by title\n");
			wprintf(L"Press Q to go back.\n");
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
						wprintf(L"Please input status.\n");
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
						wprintf(L"Input is invalid. Try again.\n");
					}
				}
			} while (!input_is_valid);
		}
	}
	else
	{
		wprintf(L"No tickets in the system.\n");
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
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Open Ticket", doNothing2));
		menu_addOption(menu, menuOption_create(L"View / Update Ticket", doNothing2));
		menu_addOption(menu, menuOption_create(L"Browse Tickets", browseTickets));
		menu_addOption(menu, menuOption_create(L"Create User", doNothing2));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback));
	}
	return menu;
}
