#include "ticket_container.h"
#include "ticket_container_util.h"
#include "vector.h"
#include <leansql.h>
#include <stdio.h>
#include <stdlib.h>

bool findByTicketId(wchar_t* column, wchar_t* value, void* desired_id)
{
	return (wcscmp(column, L"ID") == 0) && (wcscmp(value, desired_id) == 0);
}

void ticketContainer_update(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		wchar_t* data[13];
		struct ticketContainer_wcsArrStatus* data_status = ticketContainer_wcsArrFromTicket(data, ticket);

		struct LeanSQL_ActionReport update = LeanSQL_update(L"Tickets", data, NULL, 13, findByTicketId, ticket_getId(ticket));
		if (update.success)
		{
			if (update.result.rows == 0) // Ticket does not exist, was not added
			{
				update = LeanSQL_insert(L"Tickets", data, 13);
				if (!update.success)
				{
					fwprintf(stderr, L"Could not update ticket.\n");
				}
			}
		}
		else
		{
			if (update.error == LEANSQL_ERROR_NO_TABLE)
			{
				ticketContainer_createDatabaseTable();
				update = LeanSQL_insert(L"Tickets", data, 13);
				if (!update.success)
				{
					fwprintf(stderr, L"Could not update ticket.\n");
				}
			}
			else
			{
				fwprintf(stderr, L"Could not update ticket.\n");
			}
		}

		ticketContainer_cleanUpWcsArr(data, data_status);
	}
}

struct Vector* ticketContainer_getAll()
{
	struct Vector* tickets = vector_create();
	if (tickets == NULL)
	{
		return NULL;
	}

	struct LeanSQL_ActionReport select = LeanSQL_select(L"Tickets", NULL, 0, NULL, NULL);
	if (select.success)
	{
		for (unsigned int i = 0; i < select.result.rows; ++i)
		{
			struct Ticket* ticket = ticketContainer_createTicketFromDatabaseRow(select.result.data[i]);

			if (ticket != NULL)
			{
				vector_push(tickets, ticket);
			}
		}

		LeanSQL_destroyResultSet(&select.result);
	}

	return tickets;
}

struct Ticket* ticketContainer_getById(wchar_t* ticket_id)
{
	struct Ticket* ticket = NULL;

	struct LeanSQL_ActionReport select = LeanSQL_select(L"Tickets", NULL, 0, findByTicketId, ticket_id);
	if (select.success)
	{
		if (select.result.rows == 1)
		{
			ticket = ticketContainer_createTicketFromDatabaseRow(select.result.data[0]);
		}
		else if (select.result.rows == 0)
		{
			ticket = NULL;
		}
		else
		{
			fwprintf(stderr, L"Tickets database has multiple tickets with identical IDs\n");
		}

		LeanSQL_destroyResultSet(&select.result);
	}

	return ticket;
}
