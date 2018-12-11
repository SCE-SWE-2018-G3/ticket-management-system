#include "supportgiver_menu.h"
#include "supportgiver_menu_util.h"
#include "ticket_container.h"
#include "user_container.h"
#include "input_manip.h"
#include "user.h"
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
		struct MenuOption* status_option = menuOption_create(L"Filter by status", filterByStatusAction, NULL);
		struct MenuOption* tier_option = menuOption_create(L"Filter by tier", filterByTierAction, NULL);
		struct MenuOption* type_option = menuOption_create(L"Filter by type", filterByTypeAction, NULL);
		struct MenuOption* stakeholders_option = menuOption_create(L"Filter by stakeholders", filterByStakeHolderAction, NULL);
		struct MenuOption* email_option = menuOption_create(L"Search by customer email", SearchByCustomerEmailAction, NULL);
		struct MenuOption* tags_option = menuOption_create(L"Search by tags", SearchByTagsAction, NULL);
		struct MenuOption* title_sort_option = menuOption_create(L"Sort by title", SortByTitleAction, NULL);

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
		
		menu_destroy(browse_tickets);
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

void viewOrUpdateTicket()
{
	wchar_t ticket_id[64];
	wprintf(L"Please input ticket ID\n");
	input_wchar(ticket_id, 64);

	struct Ticket* ticket = ticketContainer_getById(ticket_id);
	if (ticket == NULL)
	{
		wprintf(L"Ticket not found.\n");
		system("PAUSE");
		return;
	}

	struct User* ticket_customer = userContainer_getByEmail(ticket_getCustomerEmail(ticket));
	if (ticket_customer == NULL)
	{
		wprintf(L"Ticket has no associated customer.\n");
		system("PAUSE");
		ticket_destroy(ticket);
		return;
	}

	struct Menu* menu = menu_create();
	if (menu == NULL)
	{
		fwprintf(stderr, L"Could not create menu\n");
		user_destroy(ticket_customer);
		ticket_destroy(ticket);
		return;
	}

	struct MenuOption* title_option = menuOption_create(L"Edit title", doNothing2, NULL);
	struct MenuOption* tier_option = menuOption_create(L"Edit tier", doNothing2, NULL);
	struct MenuOption* status_option = menuOption_create(L"Edit status", doNothing2, NULL);
	struct MenuOption* stakeholders_option = menuOption_create(L"Edit stakeholders", doNothing2, NULL);
	struct MenuOption* type_option = menuOption_create(L"Edit type", doNothing2, NULL);
	struct MenuOption* severity_option = menuOption_create(L"Edit severity", doNothing2, NULL);
	struct MenuOption* tags_option = menuOption_create(L"Edit tags", doNothing2, NULL);
	struct MenuOption* note_option = menuOption_create(L"Add note", doNothing2, NULL);

	menu_addOption(menu, title_option);
	menu_addOption(menu, tier_option);
	menu_addOption(menu, status_option);
	menu_addOption(menu, stakeholders_option);
	menu_addOption(menu, type_option);
	menu_addOption(menu, severity_option);
	menu_addOption(menu, tags_option);
	menu_addOption(menu, note_option);

	while (menu_isOpen(menu) && !menu_hasError(menu))
	{
		time_t date = ticket_getDate(ticket);

		system("CLS");
		wprintf(L"Ticket details\n==============\n");
		wprintf(L"Customer:\n");
		wprintf(L"\tEmail: %S\n", user_getEmail(ticket_customer));
		struct ContactDetails contact = user_getContactDetails(ticket_customer);
		wprintf(L"\tName: %s\n", contact.name);
		wprintf(L"\tPhone: %s\n", contact.phone);
		wprintf(L"Ticket ID: %s\n", ticket_getId(ticket));
		wprintf(L"Title: %s\n", ticket_getTitle(ticket));
		wprintf(L"Description: %s\n", ticket_getDescription(ticket));
		wprintf(L"Date opened: %S", ctime(&date));
		wprintf(L"Tier: %s\n", ticket_getTier(ticket));
		wprintf(L"Status: %s\n", ticket_getStatus(ticket));
		wprintf(L"Type: %s\n", ticket_getType(ticket));
		wprintf(L"Severity: %s\n", ticket_getSeverity(ticket));
		wprintf(L"Stakeholders:\n");
		struct Vector* stakeholders = ticket_getStakeholders(ticket);
		for (unsigned int i = 0; i < vector_getSize(stakeholders); ++i)
		{
			wprintf(L"%s\n", (wchar_t*)vector_getAt(stakeholders, i));
		}
		wprintf(L"Notes:\n");
		struct Vector* notes = ticket_getNotes(ticket);
		for (unsigned int i = 0; i < vector_getSize(notes); ++i)
		{
			wprintf(L"%s\n", (wchar_t*)vector_getAt(notes, i));
		}

		wprintf(L"What would you like to do?\n");
		menu_tick(menu);
	}

	menu_destroy(menu);
	user_destroy(ticket_customer);
	ticket_destroy(ticket);
}

void createUser()
{
	char email[128];
	wchar_t password[128];
	wchar_t name[128];
	wchar_t phone[128];
	wchar_t supportgiver[32];
	bool is_supportgiver = false;

	system("CLS");
	wprintf(L"Create user\n");
	wprintf(L"===========\n");
	wprintf(L"Please input new user E-mail.\n");
	input_char(email, 128);
	wprintf(L"Please input new user password.\n");
	input_wchar(password, 128);
	wprintf(L"Please input new user name.\n");
	input_wchar(name, 128);
	wprintf(L"Please input new user phone.\n");
	input_wchar(phone, 128);
	wprintf(L"Are they a support giver? (warning: this gives them full access to the system)\n");
	wprintf(L"(yes/no)\n");
	do
	{
		input_wchar(supportgiver, 32);
		if (wcscmp(supportgiver, L"yes") == 0)
		{
			is_supportgiver = true;
		}
		else if (wcscmp(supportgiver, L"no") != 0)
		{
			wprintf(L"Invalid input. Try again.\n");
		}
	} while (wcscmp(supportgiver, L"yes") != 0 && wcscmp(supportgiver, L"no") != 0);

	struct User* user = user_create(email, password, false, NULL, is_supportgiver, name, phone);
	userContainer_update(user, NULL);
	user_destroy(user);
}

struct Menu* createSupportGiverMenu(void(*onLogOutCallback)())
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Open Ticket", openTickets, NULL));
		menu_addOption(menu, menuOption_create(L"View / Update Ticket", viewOrUpdateTicket, NULL));
		menu_addOption(menu, menuOption_create(L"Browse Tickets", browseTickets, NULL));
		menu_addOption(menu, menuOption_create(L"Create User", createUser, NULL));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback, NULL));
	}
	return menu;
}
