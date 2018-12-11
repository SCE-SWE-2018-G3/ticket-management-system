#include "supportgiver_menu.h"
#include "supportgiver_menu_util.h"
#include "ticket_container.h"
#include <stdio.h>
#include <string.h>

void filterByStatusAction() 
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t status[32];
		wprintf(L"Please input status:\n");
		wscanf(L"%s", status);
		wcstok(status, L"\n", &ctx);
		struct Vector* filtered_vector = vector_filter(tickets, filterByStatus, status);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void filterByTierAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t tier[32];
		wprintf(L"Please input tier:\n");
		wscanf(L"%s", tier);
		wcstok(tier, L"\n", &ctx);
		struct Vector* filtered_vector = vector_filter(tickets, filterByTier, tier);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void filterByTypeAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t type[32];
		wprintf(L"Please input type:\n");
		wscanf(L"%s", type);
		wcstok(type, L"\n", &ctx);
		struct Vector* filtered_vector = vector_filter(tickets, filterByType, type);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void filterByStakeHolderAction() 
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t stakeholders[32];
		wprintf(L"Please input stakeholders:\n");
		wscanf(L"%s", stakeholders);
		wcstok(stakeholders, L"\n", &ctx);
		struct Vector* stakeholders_vector = vector_create();
		vector_push(stakeholders_vector, stakeholders);
		struct Vector* filtered_vector = vector_filter(tickets, filterByStakeholders, stakeholders);
		printTicketsArray(filtered_vector);
		vector_destroy(stakeholders_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void SearchByCustomerEmailAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t customer_email[32];
		wprintf(L"please input Customer Email:\n");
		wscanf(L"%s", customer_email);
		wcstok(customer_email, L"\n", &ctx);
		struct Vector* filtered_vector = vector_filter(tickets, searchByCustomerEmail, customer_email);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void SearchByTagsAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t* ctx;
		wchar_t tags[32];
		wprintf(L"Please input tags:\n");
		wscanf(L"%s", tags);
		wcstok(tags, L"\n", &ctx);
		struct Vector* filtered_vector = vector_filter(tickets, searchByTags, tags);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void SortByTitleAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else 
	{
		struct Vector* sorted_vector = vector_sort(tickets, sortByTitle);
		printTicketsArray(sorted_vector);
		vector_destroy(sorted_vector);
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
	}
	system("PAUSE");
}

void browseTickets()
{
	system("CLS");
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
		system("PAUSE");
	}
	else
	{
		//Creating the menu and giving it a title
		struct Menu* browse_tickets = menu_create();

		//Creating the options and inserting them into the menu
		struct MenuOption* status_option = menuOption_create(L"Filter by status", filterByStatusAction);
		struct MenuOption* tier_option = menuOption_create(L"Filter by tier", filterByTierAction);
		struct MenuOption* type_option = menuOption_create(L"Filter by type", filterByTypeAction);
		struct MenuOption* stakeholders_option = menuOption_create(L"Filter by stakeholders", filterByStakeHolderAction);
		struct MenuOption* email_option = menuOption_create(L"Search by customer email", SearchByCustomerEmailAction);
		struct MenuOption* tags_option = menuOption_create(L"Search by tags", SearchByTagsAction);
		struct MenuOption* title_sort_option = menuOption_create(L"Sort by title", SortByTitleAction);

		//Inserting the options into "browse_tickets" menu struct
		menu_addOption(browse_tickets, status_option);
		menu_addOption(browse_tickets, tier_option);
		menu_addOption(browse_tickets, type_option);
		menu_addOption(browse_tickets, stakeholders_option);
		menu_addOption(browse_tickets, email_option);
		menu_addOption(browse_tickets, tags_option);
		menu_addOption(browse_tickets, title_sort_option);

		//Displaying the menu "browse_tickets"
		while (menu_isOpen(browse_tickets) && !menu_hasError(browse_tickets))
		{
			system("CLS");
			wprintf(L"Browse Tickets\n==============\n");
			printTicketsArray(tickets);
			menu_tick(browse_tickets);
		}
		
		
		for(unsigned int i = 0; i < vector_getSize(tickets); ++i)
		{
			ticket_destroy(vector_getAt(tickets, i));
		}
		vector_destroy(tickets);
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
