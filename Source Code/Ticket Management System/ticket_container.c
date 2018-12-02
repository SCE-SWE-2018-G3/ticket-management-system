#include "ticket_container.h"
#include "vector.h"
#include <leansql.h>
#include <stdio.h>
#include <stdlib.h>

bool findByTicketId(wchar_t* column, wchar_t* value, void* desired_id)
{
	return (wcscmp(column, L"ID") == 0) && (wcscmp(value, desired_id) == 0);
}

void createDatabaseTable()
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
	struct LeanSQL_ActionReport creation = LeanSQL_createTable(L"Tickets", columns, 12);
	if (!creation.success)
	{
		fwprintf(stderr, L"Could not create tickets database.\n");
	}
}

struct Ticket* createTicketFromDatabaseRow(wchar_t** data)
{
	wchar_t* id = data[0];
	wchar_t* wide_customer_email = data[1];
	char customer_email[128];
	wcstombs(customer_email, wide_customer_email, 128);
	wchar_t* title = data[2];
	wchar_t* type = data[3];
	wchar_t* severity = data[4];
	wchar_t* description = data[5];
	wchar_t* tier = data[6];
	wchar_t* status = data[7];
	wchar_t* stakeholders = data[8];
	wchar_t* tags = data[9];
	wchar_t* notes = data[10];
	wchar_t* creation_date = data[11];
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
	}
	return ticket;
}

void ticketContainer_update(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		wchar_t* data[12];
		data[0] = ticket_getId(ticket);
		data[1] = malloc(sizeof(wchar_t) * (strlen(ticket_getCustomerEmail(ticket)) + 1));
		if (data[1] != NULL)
		{
			mbstowcs(data[1], ticket_getCustomerEmail(ticket), strlen(ticket_getCustomerEmail(ticket)) + 1);
		}
		data[2] = ticket_getTitle(ticket);
		data[3] = ticket_getType(ticket);
		data[4] = ticket_getSeverity(ticket);
		data[5] = ticket_getDescription(ticket);
		data[6] = ticket_getTier(ticket);
		data[7] = ticket_getStatus(ticket);
		data[8] = L" "; // TODO: Stakeholders
		data[9] = L" "; // TODO: Tags
		data[10] = L" "; // TODO: Notes
		data[11] = L" "; // TODO: creation date

		struct LeanSQL_ActionReport update = LeanSQL_update(L"Tickets", data, NULL, 12, findByTicketId, ticket_getId(ticket));
		if (update.success)
		{
			if (update.result.rows == 0) // Ticket does not exist, was not added
			{
				update = LeanSQL_insert(L"Tickets", data, 12);
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
				createDatabaseTable();
				update = LeanSQL_insert(L"Tickets", data, 12);
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
		if (data[1] != NULL)
		{
			free(data[1]);
		}
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
			struct Ticket* ticket = createTicketFromDatabaseRow(select.result.data[i]);

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
			ticket = createTicketFromDatabaseRow(select.result.data[0]);
		}
		else
		{
			fwprintf(stderr, L"Tickets database has multiple tickets with identical IDs\n");
		}

		LeanSQL_destroyResultSet(&select.result);
	}

	return ticket;
}
