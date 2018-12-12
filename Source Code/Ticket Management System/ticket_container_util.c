#include "ticket_container_util.h"
#include "ticket.h"
#include <leansql.h>
#include <string.h>
#include <stdio.h>

#define SEPARATOR L";"

void ticketContainer_createDatabaseTable()
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
		L"CreationDate",
		L"Media"

	};
	struct LeanSQL_ActionReport creation = LeanSQL_createTable(L"Tickets", columns, 13);
	if (!creation.success)
	{
		fwprintf(stderr, L"Could not create tickets database.\n");
	}
}

struct Ticket* ticketContainer_createTicketFromDatabaseRow(wchar_t** data)
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
	long int creation_date_int = wcstol(creation_date, NULL, 10);
	wchar_t* media = data[12];

	struct Ticket* ticket = ticket_create(title, type, description,media,customer_email);
	if (ticket != NULL)
	{
		ticket_setId(ticket, id);
		ticket_setSeverity(ticket, severity);
		ticket_setTier(ticket, tier);
		ticket_setStatus(ticket, status);
		ticket_setDate(ticket, creation_date_int);

		wchar_t* ctx;

		wchar_t* stakeholder = wcstok(stakeholders, SEPARATOR, &ctx);
		if (stakeholder != NULL)
		{
			ticket_addStakeholder(ticket, stakeholder);
			while ((stakeholder = wcstok(NULL, SEPARATOR, &ctx)) != NULL)
			{
				ticket_addStakeholder(ticket, stakeholder);
			}
		}

		wchar_t* tag = wcstok(tags, SEPARATOR, &ctx);
		if (tag != NULL)
		{
			ticket_addTag(ticket, tag);
			while ((tag = wcstok(NULL, SEPARATOR, &ctx)) != NULL)
			{
				ticket_addTag(ticket, tag);
			}
		}

		wchar_t* note = wcstok(notes, SEPARATOR, &ctx);
		if (note != NULL)
		{
			ticket_addNote(ticket, note);
			while ((note = wcstok(NULL, SEPARATOR, &ctx)) != NULL)
			{
				ticket_addNote(ticket, note);
			}
		}
	}
	return ticket;
}

struct ticketContainer_wcsArrStatus
{
	bool malloced_data1;
	bool malloced_data8;
	bool malloced_data9;
	bool malloced_data10;
	bool malloced_data11;
};

struct ticketContainer_wcsArrStatus* ticketContainer_wcsArrFromTicket(wchar_t** data, struct Ticket* ticket)
{
	if (data == NULL || ticket == NULL)
	{
		return NULL;
	}
	struct ticketContainer_wcsArrStatus* status = malloc(sizeof(struct ticketContainer_wcsArrStatus));
	if (status == NULL)
	{
		fwprintf(stderr, L"Converting ticket to wcsArr failed due to memory error.\n");
		return NULL;
	}
	status->malloced_data1 = false;
	status->malloced_data8 = false;
	status->malloced_data9 = false;
	status->malloced_data10 = false;
	status->malloced_data11 = false;

	data[0] = ticket_getId(ticket);

	data[1] = malloc(sizeof(wchar_t) * (strlen(ticket_getCustomerEmail(ticket)) + 1));
	if (data[1] == NULL)
	{
		data[1] = L" ";
		fwprintf(stderr, L"Failed saving ticket customer email to database\n");
	}
	else
	{
		mbstowcs(data[1], ticket_getCustomerEmail(ticket), strlen(ticket_getCustomerEmail(ticket)) + 1);
		status->malloced_data1 = true;
	}

	data[2] = ticket_getTitle(ticket);
	data[3] = ticket_getType(ticket);
	data[4] = ticket_getSeverity(ticket);
	data[5] = ticket_getDescription(ticket);
	data[6] = ticket_getTier(ticket);
	data[7] = ticket_getStatus(ticket);
	data[12] = ticket_getMedia(ticket);

	struct Vector* stakeholders = ticket_getStakeholders(ticket);
	if (stakeholders == NULL)
	{
		data[8] = L" ";
	}
	else
	{
		unsigned int length = 0;
		for (unsigned int i = 0; i < vector_getSize(stakeholders); ++i)
		{
			length += wcslen(vector_getAt(stakeholders, i));
			length += 1;
		}
		data[8] = malloc(sizeof(wchar_t) * (length + 1));
		if (data[8] == NULL)
		{
			data[8] = L" ";
			fwprintf(stderr, L"Failed saving ticket stakeholders to database\n");
		}
		else
		{
			data[8][0] = L'\0';
			for (unsigned int i = 0; i < vector_getSize(stakeholders); ++i)
			{
				wcscat(data[8], vector_getAt(stakeholders, i));
				wcscat(data[8], SEPARATOR);
			}
			status->malloced_data8 = true;
		}
	}

	struct Vector* tags = ticket_getTags(ticket);
	if (tags == NULL)
	{
		data[9] = L" ";
	}
	else
	{
		unsigned int length = 0;
		for (unsigned int i = 0; i < vector_getSize(tags); ++i)
		{
			length += wcslen(vector_getAt(tags, i));
			length += 1;
		}
		data[9] = malloc(sizeof(wchar_t) * (length + 1));
		if (data[9] == NULL)
		{
			data[9] = L" ";
			fwprintf(stderr, L"Failed saving ticket tags to database\n");
		}
		else
		{
			data[9][0] = L'\0';
			for (unsigned int i = 0; i < vector_getSize(tags); ++i)
			{
				wcscat(data[9], vector_getAt(tags, i));
				wcscat(data[9], SEPARATOR);
			}
			status->malloced_data9 = true;
		}
	}

	struct Vector* note = ticket_getNotes(ticket);
	if (note == NULL)
	{
		data[10] = L" ";
	}
	else
	{
		unsigned int length = 0;
		for (unsigned int i = 0; i < vector_getSize(note); ++i)
		{
			length += wcslen(vector_getAt(note, i));
			length += 1;
		}
		data[10] = malloc(sizeof(wchar_t) * (length + 1));
		if (data[10] == NULL)
		{
			data[10] = L" ";
			fwprintf(stderr, L"Failed saving ticket notes to database\n");
		}
		else
		{
			data[10][0] = L'\0';
			for (unsigned int i = 0; i < vector_getSize(note); ++i)
			{
				wcscat(data[10], vector_getAt(note, i));
				wcscat(data[10], SEPARATOR);
			}
			status->malloced_data10 = true;
		}
	}

	data[11] = malloc(sizeof(wchar_t) * 100);
	if (data[11] == NULL)
	{
		data[11] = L" ";
	}
	else
	{
		swprintf(data[11], 100, L"%d", (int) ticket_getDate(ticket));
		status->malloced_data11 = true;
	}

	return status;
}

void ticketContainer_cleanUpWcsArr(wchar_t** data, struct ticketContainer_wcsArrStatus* status)
{
	if (status == NULL || data == NULL)
	{
		return;
	}

	if (status->malloced_data1 && data[1] != NULL)
	{
		free(data[1]);
		data[1] = NULL;
	}
	if (status->malloced_data8 && data[8] != NULL)
	{
		free(data[8]);
		data[8] = NULL;
	}
	if (status->malloced_data9 && data[9] != NULL)
	{
		free(data[9]);
		data[9] = NULL;
	}
	if (status->malloced_data10 && data[10] != NULL)
	{
		free(data[10]);
		data[10] = NULL;
	}
	if (status->malloced_data11 && data[11] != NULL)
	{
		free(data[11]);
		data[11] = NULL;
	}
	
	free(status);
}
