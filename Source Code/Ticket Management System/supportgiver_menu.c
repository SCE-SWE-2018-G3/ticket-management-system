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

void filterByStatusAction() 
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	wchar_t* ctx;
	wchar_t status[32];
	wprintf(L"Please input status.\n");
	wscanf(L"%s", status);
	wcstok(status, L"\n", &ctx);
	struct Vector* filtered_vector = vector_filter(tickets, filterByStatus, status);
	printTicketsArray(filtered_vector);
	vector_destroy(filtered_vector);
}
void filterByTierAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	wchar_t* ctx;
	wchar_t tier[32];
	wprintf(L"%s\n", L"please input tier");
	wscanf(L"%s", tier);
	wcstok(tier, L"\n", &ctx);
	struct Vector* filtered_vector = vector_filter(tickets, filterByTier, tier);
	printTicketsArray(filtered_vector);
	vector_destroy(filtered_vector);
}
void filterByTypeAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	wchar_t* ctx;
	wchar_t type[32];
	wprintf(L"%s\n", L"please input type");
	wscanf(L"%s", type);
	wcstok(type, L"\n", &ctx);
	struct Vector* filtered_vector = vector_filter(tickets, filterByType, type);
	printTicketsArray(filtered_vector);
	vector_destroy(filtered_vector);
}
void filterByStakeHolderAction() 
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
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
}
void SearchByCustomerEmailAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	wchar_t* ctx;
	wchar_t customer_email[32];
	wprintf(L"%s\n", L"please input Customer Email");
	wscanf(L"%s", customer_email);
	wcstok(customer_email, L"\n", &ctx);
	struct Vector* filtered_vector = vector_filter(tickets, searchByCustomerEmail, customer_email);
	printTicketsArray(filtered_vector);
	vector_destroy(filtered_vector);
}
void SearchByTagsAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	wchar_t* ctx;
	wchar_t tags[32];
	wprintf(L"%s\n", L"please input tags");
	wscanf(L"%s", tags);
	wcstok(tags, L"\n", &ctx);
	struct Vector* filtered_vector = vector_filter(tickets, searchByTags, tags);
	printTicketsArray(filtered_vector);
	vector_destroy(filtered_vector);
}
void SortByTitleAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL) {
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	struct Vector* sorted_vector = vector_sort(tickets, sortByTitle);
	printTicketsArray(sorted_vector);
	vector_destroy(sorted_vector);
}

void browseTickets()
{
	system("@cls||clear");
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets != NULL) {
		printTicketsArray(tickets);

		//Creating the menu and giving it a title
		struct Menu* browse_tickets = menu_create();
		menu_setTitle(browse_tickets, L"Browse Tickets\n==============");

		//Creating the options and inserting them into the menu
		struct MenuOption* statusOption = menuOption_create(L"Filter by status", filterByStatusAction);
		struct MenuOption* tierOption = menuOption_create(L"Filter by tier", filterByTierAction);
		struct MenuOption* typeOption = menuOption_create(L"Filter by type", filterByTypeAction);
		struct MenuOption* stakeholdersOption = menuOption_create(L"Filter by stakeholders", filterByStakeHolderAction);
		struct MenuOption* emailOption = menuOption_create(L"Search by customer email", SearchByCustomerEmailAction);
		struct MenuOption* tagsOption = menuOption_create(L"Search by tags", SearchByTagsAction);
		struct MenuOption* titleSortOption = menuOption_create(L"Sort by title", SortByTitleAction);

		//Inserting the options into "browse_tickets" menu struct
		menu_addOption(browse_tickets, statusOption);
		menu_addOption(browse_tickets, tierOption);
		menu_addOption(browse_tickets, typeOption);
		menu_addOption(browse_tickets, stakeholdersOption);
		menu_addOption(browse_tickets, emailOption);
		menu_addOption(browse_tickets, tagsOption);
		menu_addOption(browse_tickets, titleSortOption);

		//Displaying the menu "browse_tickets"
		menu_tick(browse_tickets);
		system("PAUSE");
	}
	else 
	{
		wprintf(L"Failed to retrieve the tickets.");
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
			wprintf(L"The ticked was saved in the system.\n");
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
