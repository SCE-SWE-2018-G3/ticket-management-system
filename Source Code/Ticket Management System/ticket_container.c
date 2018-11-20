#include "ticket_container.h"
#include "vector.h"
#include <leansql.h>
#include <stdio.h>
#include <stdlib.h>

struct Vector* tickets = NULL;
bool all_in_memory = false;

void loadToMemory()
{
	if (tickets == NULL)
	{
		tickets = vector_create();
	}

	struct LeanSQL_ActionReport select = LeanSQL_select(L"Tickets", NULL, 0, NULL);
	if (select.success)
	{
		for (unsigned int i = 0; i < select.result.rows; ++i)
		{
			wchar_t* id = select.result.data[i][0];
			wchar_t* customer_email = select.result.data[i][1];
			wchar_t* title = select.result.data[i][2];
			wchar_t* type = select.result.data[i][3];
			wchar_t* severity = select.result.data[i][4];
			wchar_t* description = select.result.data[i][5];
			wchar_t* tier = select.result.data[i][6];
			wchar_t* status = select.result.data[i][7];
			wchar_t* stakeholders = select.result.data[i][8];
			wchar_t* tags = select.result.data[i][9];
			wchar_t* notes = select.result.data[i][10];
			wchar_t* creation_date = select.result.data[i][11];
			struct Ticket* ticket = ticket_create(title, type, description, customer_email);
			if (ticket != NULL)
			{
				ticket_setId(ticket, id);
				ticket_setSeverity(ticket, severity);
				ticket_setTier(ticket, tier);
				ticket_setStatus(ticket, status);
				// TODO: set stakeholders
				// TODO: set tags
				// TODO: set notes
				// TODO: set creation date
				vector_push(tickets, ticket);
			}
		}

		LeanSQL_destroyResultSet(&select.result);

		all_in_memory = true;
		return;
	}
	
	if (select.error == LEANSQL_ERROR_NO_TABLE)
	{
		wchar_t* columns[] =
		{
			L"ID",
			L"CustomerEmail",
			L"Title",
			L"Type",
			L"Severity",
			L"Description",
			L"Tier",
			L"Status",
			L"Stakeholders",
			L"Tags",
			L"Notes",
			L"CreationDate"
		};
		LeanSQL_createTable(L"Tickets", columns, 12);

		all_in_memory = true;
	}
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
			// LeanSQL_update(L"Tickets", data, NULL, 0, ? ? ? );
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
