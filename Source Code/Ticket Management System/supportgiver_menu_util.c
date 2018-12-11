#include "supportgiver_menu_util.h"
#include "vector.h"
#include "ticket.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
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

bool sortByTitle(void* ticket1, void* ticket2)
{
	return wcscmp(ticket_getTitle(ticket1), ticket_getTitle(ticket2)) > 0;
}
