#include "ticket_container.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

struct Vector* tickets = NULL;
bool all_in_memory = false;

void loadToMemory()
{
	// TODO
	all_in_memory = true;
}

bool filterByTicketId(void* ticket, void* ticket_id)
{
	return wcscmp(ticket_getId(ticket), ticket_id) != 0;
}

void ticketContainer_update(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		if (tickets == NULL)
		{
			loadToMemory();
		}

		if (all_in_memory)
		{
			struct Vector* found_tickets = vector_filter(tickets, filterByTicketId, ticket_getId(ticket));
			if (vector_getSize(found_tickets) == 0)
			{
				vector_push(tickets, ticket);
			}
			else
			{
				for (unsigned int i = 0; i < vector_getSize(found_tickets); ++i)
				{
					struct Ticket* found_ticket = vector_getAt(found_tickets, i);
					ticket_copyFrom(found_ticket, ticket);
				}
			}
			// TODO: Save to file / db
		}
		else
		{
			// TODO
		}
	}
}

struct Vector* ticketContainer_getAll()
{
	if (tickets == NULL)
	{
		loadToMemory();
	}

	if (all_in_memory)
	{
		return tickets;
	}
	else
	{
		// TODO: Get from file / db
	}
	return NULL;
}

struct Ticket* ticketContainer_getById(wchar_t* ticket)
{
	if (tickets == NULL)
	{
		loadToMemory();
	}

	if (all_in_memory)
	{
		struct Vector* found_tickets = vector_filter(tickets, filterByTicketId, ticket);
		if (vector_getSize(found_tickets) == 0)
		{
			return NULL;
		}
		else
		{
			if (vector_getSize(found_tickets) != 1)
			{
				fwprintf(stderr, L"Ticket container has multiple tickets with same ID.\n");
			}

			struct Ticket* found_ticket = vector_getAt(found_tickets, 0);
			return found_ticket;
		}
	}
	else
	{
		// TODO: Find in file / db
	}
	return NULL;
}
