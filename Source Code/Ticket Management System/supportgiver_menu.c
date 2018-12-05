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
bool filterByTier(void* ticket1, void* tier)
{
	return wcscmp(ticket_getTier(ticket1), tier) != 0;
}
bool filterByType(void* ticket1, void* type)
{
	return wcscmp(ticket_getType(ticket1), type) != 0;

}
bool sortByTitle(void* ticket1, void* ticket2)
{
	return wcscmp(ticket_getTitle(ticket1), ticket_getTitle(ticket2)) > 0;
}
bool filterByStakeholders(void* ticket1, void* stakeholders)
{
	struct Vector* ticket_stakeholders = ticket_getStakeholders(ticket1);
	struct Vector* desired_stakeholders = stakeholders;

	bool found_matching_stakeholders = false;
	for (unsigned int i = 0; i < vector_getSize(ticket_stakeholders) && !found_matching_stakeholders; ++i)
	{
		for (unsigned int j = 0; j < vector_getSize(desired_stakeholders) && !found_matching_stakeholders; ++j)
		{
			if (wcscmp(vector_getAt(ticket_stakeholders, i), vector_getAt(desired_stakeholders, j)) == 0)
			{
				found_matching_stakeholders = true;
			}
		}
	}

	return !found_matching_stakeholders;
}
bool searchByCustomerEmail(void* ticket1, void* customer_email)
{
	return strcmp(ticket_getCustomerEmail(ticket1), customer_email) != 0;

}
bool searchByTags(void* ticket, void* tag)
{
	struct Vector* ticket_tags = ticket_getTags(ticket);

	bool found_tag = false;
	for (unsigned int i = 0; i < vector_getSize(ticket_tags); ++i)
	{
		if (wcscmp(vector_getAt(ticket_tags, i), tag) == 0)
		{
			found_tag = true;
		}
	}

	return found_tag;
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
						wcstok(status, L"\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, filterByStatus, status);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('2'): // Filter by tier
					{
						wchar_t* ctx;
						wchar_t tier[32];
						wprintf(L"%s\n", L"please input tier");
						wscanf(L"%s", tier);
						wcstok(tier, L"\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, filterByTier, tier);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('3'): // Filter by type
					{
						wchar_t* ctx;
						wchar_t type[32];
						wprintf(L"%s\n", L"please input type");
						wscanf(L"%s", type);
						wcstok(type, L"\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, filterByType, type);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('4'): // Filter by stakeholders
					{
						wchar_t* ctx;
						wchar_t stakeholders[32];
						wprintf(L"%s\n", L"please input stakeholders");
						wscanf(L"%s", stakeholders);
						wcstok(stakeholders, L"\n", &ctx);
						struct Vector* stakeholders_vector = vector_create();
						vector_push(stakeholders_vector, stakeholders);
						struct Vector* filtered_vector = vector_filter(tickets, filterByStakeholders, stakeholders);
						printTicketsArray(filtered_vector);
						vector_destroy(stakeholders_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('5'): // Search by customer email
					{
						wchar_t* ctx;
						wchar_t customer_email[32];
						wprintf(L"%s\n", L"please input Customer Email");
						wscanf(L"%s", customer_email);
						wcstok(customer_email, L"\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, searchByCustomerEmail, customer_email);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
						break;
					}
					case('6'): // Search by tags
					{
						wchar_t* ctx;
						wchar_t tags[32];
						wprintf(L"%s\n", L"please input tags");
						wscanf(L"%s", tags);
						wcstok(tags, L"\n", &ctx);
						struct Vector* filtered_vector = vector_filter(tickets, searchByTags, tags);
						printTicketsArray(filtered_vector);
						vector_destroy(filtered_vector);
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

void openTickets()
{
		char customer_email[256];
		wchar_t title[256];
		wchar_t type_support[256];
		wchar_t* severity[] = { L"Medium", L"High", L"Critical", L"Urgent" };
		wchar_t description_support[512];
		int severity_num;

		system("CLS");
		wprintf(L"Please input customer email\n");
		wscanf(L"%S", customer_email);
		wprintf(L"Creating a ticket\n");
		wprintf(L"===============\n");
		wprintf(L"Please input description\n");
		wscanf(L"%s", description_support);
		wprintf(L"Please input title\n");
		wscanf(L"%s", title);
		wprintf(L"Please input type\n");
		wscanf(L"%s", type_support);
		wprintf(L"Please input severity.\n1. Medium\n2. High\n3. Critical\n4. Urgent\n");
		do
		{
			wscanf(L"%d", &severity_num);
			if(severity_num < 1 || severity_num > 4)
			{
				wprintf(L"Invaild severity. Try again.\n");
			}
		} while(severity_num < 1 || severity_num > 4);
		
		struct Ticket* ticket = ticket_create(title, type_support, description_support, customer_email);
		if (ticket != NULL)
		{
			ticket_setSeverity(ticket, severity[severity_num - 1]);

			ticketContainer_update(ticket);

			system("CLS");
			wprintf(L"Ticket saved\n");
			wprintf(L"==================\n");
			wprintf(L"The ticket was saved in the system.\n");
			wprintf(L"The ticket ID is:\n");
			wprintf(L"%s\n", ticket_getId(ticket));
			wprintf(L"Please save this ID for future reference.\n");
			system("PAUSE");
		}
		else
		{
			fwprintf(stderr, L"Failed to create ticket\n");
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
		menu_addOption(menu, menuOption_create(L"Open Ticket", openTickets));
		menu_addOption(menu, menuOption_create(L"View / Update Ticket", doNothing2));
		menu_addOption(menu, menuOption_create(L"Browse Tickets", browseTickets));
		menu_addOption(menu, menuOption_create(L"Create User", doNothing2));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback));
	}
	return menu;
}
