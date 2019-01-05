#include "supportgiver_menu.h"
#include "supportgiver_menu_util.h"
#include "ticket_container.h"
#include "user_container.h"
#include "input_manip.h"
#include "user.h"
#include "auth.h"
#include <stdio.h>
#include <string.h>
#define MAX_CHARS_IN_FILTER 64
void filterByStatusAction() 
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t status[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input status:\n");
		input_wchar(status, MAX_CHARS_IN_FILTER);
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
		wchar_t tier[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input tier:\n");
		input_wchar(tier, MAX_CHARS_IN_FILTER);
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
		wchar_t type[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input type:\n");
		input_wchar(type, MAX_CHARS_IN_FILTER);
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
		wchar_t stakeholder[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input stakeholders:\n");
		input_wchar(stakeholder, MAX_CHARS_IN_FILTER);		
		struct Vector* filtered_vector = vector_filter(tickets, filterByStakeholders, stakeholder);
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
void filterByMediaAction()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL)
	{
		wprintf(L"No tickets in the system.\n");
	}
	else
	{
		wchar_t media[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input media:\n");
		input_wchar(media, MAX_CHARS_IN_FILTER);
		struct Vector* filtered_vector = vector_filter(tickets, filterByMedia, media);
		printTicketsArray(filtered_vector);
		vector_destroy(filtered_vector);
		for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
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
		char customer_email[MAX_CHARS_IN_FILTER];
		wprintf(L"please input Customer Email:\n");
		input_char(customer_email, MAX_CHARS_IN_FILTER);
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
		wchar_t tags[MAX_CHARS_IN_FILTER];
		wprintf(L"Please input tags:\n");
		input_wchar(tags, MAX_CHARS_IN_FILTER);
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
		struct MenuOption* media_option = menuOption_create(L"Filter by media", filterByMediaAction, NULL);
		struct MenuOption* email_option = menuOption_create(L"Search by customer email", SearchByCustomerEmailAction, NULL);
		struct MenuOption* tags_option = menuOption_create(L"Search by tags", SearchByTagsAction, NULL);
		struct MenuOption* title_sort_option = menuOption_create(L"Sort by title", SortByTitleAction, NULL);

		//Inserting the options into "browse_tickets" menu struct
		menu_addOption(browse_tickets, status_option);
		menu_addOption(browse_tickets, tier_option);
		menu_addOption(browse_tickets, type_option);
		menu_addOption(browse_tickets, stakeholders_option);
		menu_addOption(browse_tickets, media_option);
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
	wchar_t media[256];
	wchar_t description_support[512];
	char severity_num[10];	

	system("CLS");
	wprintf(L"Please input customer email\n");
	do
	{
		input_char(customer_email, 256);
		if (!userContainer_getByEmail(customer_email))
			printf("There is no user with that email. Try again.\n");
	} while (!userContainer_getByEmail(customer_email));	
	wprintf(L"Creating a ticket\n");
	wprintf(L"===============\n");
	wprintf(L"Please input title\n");
	input_wchar(title, 256);
	wprintf(L"Please input type\n");
	input_wchar(type_support, 256);
	wprintf(L"Please input severity.\n1. Medium\n2. High\n3. Critical\n4. Urgent\n");
	do
	{
		input_char(severity_num, 10);

		if (strcmp(severity_num,"1") && strcmp(severity_num, "2") && strcmp(severity_num, "3") && strcmp(severity_num, "4"))
		{
			wprintf(L"Invaild severity. Try again.\n");
		}
	} while (strcmp(severity_num, "1") && strcmp(severity_num, "2") && strcmp(severity_num, "3") && strcmp(severity_num, "4"));	
	wprintf(L"Please input media\n");
	input_wchar(media, 256);
	wprintf(L"Please input description\n");
	input_wchar(description_support, 512);		
	
		
	struct Ticket* ticket = ticket_create(title, type_support, description_support,media,customer_email);
	if (ticket != NULL)
	{
		wprintf(L"Please add tags (each in new line).\n");
		wprintf(L"Type END to finish.\n");
		wchar_t input[128];
		do
		{
			input_wchar(input, 128);
			if (wcscmp(input, L"END") != 0)
			{
				ticket_addTag(ticket, input);
			}
		} while (wcscmp(input, L"END") != 0);

		ticket_setSeverity(ticket, severity[severity_num[0] - '0' - 1]);
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

void editTitleAction(void* ticket)
{
	wchar_t input[128];
	wprintf(L"Please input new title.\n");
	input_wchar(input, 128);
	ticket_setTitle(ticket, input);
}

void editTierAction(void* ticket)
{
	wchar_t input[128];
	wprintf(L"Please input new tier.\n");
	input_wchar(input, 128);
	ticket_setTier(ticket, input);
}

void editStatusAction(void* ticket)
{
	wchar_t input[128];
	wprintf(L"Please input new status.\n");
	input_wchar(input, 128);
	ticket_setStatus(ticket, input);
}

void editTypeAction(void* ticket)
{
	wchar_t input[128];
	wprintf(L"Please input new type.\n");
	input_wchar(input, 128);
	ticket_setType(ticket, input);
}

void editSeverityAction(void* ticket)
{
	wchar_t* severity[] = { L"Medium", L"High", L"Critical", L"Urgent" };//////
	char severity_num[10];	
	wprintf(L"Please input severity.\n1. Medium\n2. High\n3. Critical\n4. Urgent\n");
	do
	{
		input_char(severity_num, 10);

		if (strcmp(severity_num, "1") && strcmp(severity_num, "2") && strcmp(severity_num, "3") && strcmp(severity_num, "4"))
		{
			wprintf(L"Invaild severity. Try again.\n");
		}
	} while (strcmp(severity_num, "1") && strcmp(severity_num, "2") && strcmp(severity_num, "3") && strcmp(severity_num, "4"));	
	ticket_setSeverity(ticket, severity[severity_num[0] - '0' -1]);
}

void editStakeholdersAction(void* ticket)
{
	wprintf(L"You are now adding stakeholders.\n");
	wprintf(L"Type END to finish.\n");
	
	wchar_t input[128];
	do
	{
		input_wchar(input, 128);
		if (wcscmp(input, L"END") != 0)
		{
			ticket_addStakeholder(ticket, input);
		}
	} while (wcscmp(input, L"END") != 0);
}

void editTagsAction(void* ticket)
{
	wprintf(L"You are now adding tags.\n");
	wprintf(L"Type END to finish.\n");

	wchar_t input[128];
	do
	{
		input_wchar(input, 128);
		if (wcscmp(input, L"END") != 0)
		{
			ticket_addTag(ticket, input);
		}
	} while (wcscmp(input, L"END") != 0);
}

void addNoteAction(void* ticket)
{
	time_t date = ticket_getDate(ticket);
	char* time_str = ctime(&date);
	strtok(time_str, "\n");
	wchar_t* time_wcs = malloc(sizeof(wchar_t) * (strlen(time_str) + 1));
	if (time_wcs == NULL)
	{
		return;
	}
	mbstowcs(time_wcs, time_str, strlen(time_str) + 1);

	wchar_t* email_wcs = malloc(sizeof(wchar_t) * (strlen(auth_getEmail()) + 1));
	if (email_wcs == NULL)
	{
		free(time_wcs);
		return;
	}
	mbstowcs(email_wcs, auth_getEmail(), strlen(auth_getEmail()) + 1);

	wchar_t input[512];
	wprintf(L"Please input your note.\n");
	input_wchar(input, 512 - wcslen(time_wcs) - wcslen(email_wcs) - 2*wcslen(L": "));

	wchar_t note_str[512];
	note_str[0] = L'\0';
	wcscat(note_str, time_wcs);
	wcscat(note_str, L": ");
	wcscat(note_str, email_wcs);
	wcscat(note_str, L": ");
	wcscat(note_str, input);

	ticket_addNote(ticket, note_str);

	free(email_wcs);
	free(time_wcs);
}

void viewOrUpdateTicket()
{
	system("CLS");
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

	struct MenuOption* title_option = menuOption_create(L"Edit title", editTitleAction, ticket);
	struct MenuOption* tier_option = menuOption_create(L"Edit tier", editTierAction, ticket);
	struct MenuOption* status_option = menuOption_create(L"Edit status", editStatusAction, ticket);
	struct MenuOption* stakeholders_option = menuOption_create(L"Edit stakeholders", editStakeholdersAction, ticket);
	struct MenuOption* type_option = menuOption_create(L"Edit type", editTypeAction, ticket);
	struct MenuOption* severity_option = menuOption_create(L"Edit severity", editSeverityAction, ticket);
	struct MenuOption* tags_option = menuOption_create(L"Edit tags", editTagsAction, ticket);
	struct MenuOption* note_option = menuOption_create(L"Add note", addNoteAction, ticket);

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
		wprintf(L"Media: %s\n",ticket_getMedia(ticket));
		wprintf(L"Date opened: %S\n", ctime(&date));
		wprintf(L"Tier: %s\n", ticket_getTier(ticket));
		wprintf(L"Status: %s\n", ticket_getStatus(ticket));
		wprintf(L"Type: %s\n", ticket_getType(ticket));
		wprintf(L"Severity: %s\n", ticket_getSeverity(ticket));
		wprintf(L"Tags:\n");
		struct Vector* tags = ticket_getTags(ticket);
		for (unsigned int i = 0; i < vector_getSize(tags); ++i)
		{
			wprintf(L"%s\n", (wchar_t*)vector_getAt(tags, i));
		}
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
		ticketContainer_update(ticket);
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

void mostCommonProblem(struct Vector* tickets)
{

	wchar_t tagToTrack1[64];
	wchar_t tagToTrack2[64];
	wchar_t tagToTrack3[64];

	int tagCounter1 = 0;
	int tagCounter2 = 0;
	int tagCounter3 = 0;

	wprintf(L"Please input three tags you wish to track:\n");
	input_wchar(tagToTrack1, 64);
	input_wchar(tagToTrack2, 64);
	input_wchar(tagToTrack3, 64);

	for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
	{
		struct Vector* tags = ticket_getTags(vector_getAt(tickets, i));
		for (unsigned int j = 0; j < vector_getSize(tags); ++j)
		{
			wchar_t* currentTag = vector_getAt(tags, j);
			if (wcscmp(currentTag, tagToTrack1) == 0)
				tagCounter1 += 1;
			if (wcscmp(currentTag, tagToTrack2) == 0)
				tagCounter2 += 1;
			if (wcscmp(currentTag, tagToTrack3) == 0)
				tagCounter3 += 1;
		}
	}

	wprintf(L"%d tickets opened with tag %s.\n", tagCounter1, tagToTrack1);
	wprintf(L"%d tickets opened with tag %s.\n", tagCounter2, tagToTrack2);
	wprintf(L"%d tickets opened with tag %s.\n", tagCounter3, tagToTrack3);
}

void mostCommonMedia(struct Vector* tickets)
{
	int phoneCounter = 0;
	int emailCounter = 0;
	int self_service = 0;
	int other = 0;
	for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
	{
		wchar_t* currentMedia = ticket_getMedia(vector_getAt(tickets, i));

		if (wcscmp(currentMedia, L"Phone") == 0)
			phoneCounter += 1;
		if (wcscmp(currentMedia, L"Email") == 0)
			emailCounter += 1;
		if (wcscmp(currentMedia, L"Self service") == 0)
			self_service += 1;
		if (wcscmp(currentMedia, L"Other") == 0)
			other += 1;
	}

	wprintf(L"%d tickets opened through Phone.\n", phoneCounter);
	wprintf(L"%d tickets opened through Email.\n", emailCounter);
	wprintf(L"%d tickets opened through self-service.\n", self_service);
	wprintf(L"%d tickets opened through other means.\n", other);
}

void tickets_openedToday(struct Vector* tickets)
{
	int openedToday = 0;
	time_t currentDate=time(NULL);

	for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
	{
		time_t creationDate = ticket_getDate(vector_getAt(tickets, i));
		if (currentDate - creationDate <= 86400)
			openedToday += 1;
	}

	wprintf(L"%d tickets opened in the last 24 hours.\n", openedToday);
}

void tickets_howManyClosed(struct Vector* tickets)
{
	int closedCounter = 0;

	for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
	{
		wchar_t* currentStatus = ticket_getStatus(vector_getAt(tickets, i));
		if (wcscmp(currentStatus, L"Closed") == 0 || wcscmp(currentStatus, L"closed") == 0)
			closedCounter += 1;

	}
	wprintf(L"%d tickets closed since systems' creation.\n", closedCounter);

}

void stats()
{
	struct Vector* tickets = ticketContainer_getAll();
	if (tickets == NULL || vector_getSize(tickets) == 0)
	{
		wprintf(L"No tickets in the system.\n");
		vector_destroy(tickets);
		system("PAUSE");
		return;
	}
	system("CLS");
	wprintf(L"Analytical Stats\n");
	wprintf(L"================\n");
	mostCommonProblem(tickets);
	mostCommonMedia(tickets);
	tickets_openedToday(tickets);
	tickets_howManyClosed(tickets);
	system("PAUSE");

	for (unsigned int i = 0; i < vector_getSize(tickets); ++i)
	{
		ticket_destroy(vector_getAt(tickets, i));
	}
	vector_destroy(tickets);
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
		menu_addOption(menu, menuOption_create(L"Analytical Stats", stats, NULL));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback, NULL));
	}
	return menu;
}
