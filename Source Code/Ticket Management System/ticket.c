#include "ticket.h"
#include <time.h>
#include <stdio.h>

struct Note
{
	time_t date;
	wchar_t* author;
	wchar_t* content;
};

struct Ticket
{
	wchar_t* id;
	char* customer_email;
	wchar_t* title;
	wchar_t* type;
	wchar_t* severity;
	wchar_t* description;
	wchar_t* tier;
	wchar_t* status;
	struct Vector* stakeholders;
	struct Vector* tags;
	struct Vector* notes;
};

struct Ticket* ticket_create(wchar_t* title, wchar_t* type, wchar_t* description, char* customer_email)
{
	struct Ticket* ticket = malloc(sizeof(struct Ticket));
	if (ticket != NULL)
	{
		ticket->id = L"somerandomticketID"; // TODO: random string
		ticket->customer_email = customer_email;
		ticket->title = title;
		ticket->type = type;
		ticket->description = description;
		ticket->severity = L"unset";
		ticket->tier = L"T1";
		ticket->status = L"open";
		ticket->stakeholders = NULL;
		ticket->tags = NULL;
		ticket->notes = NULL;
	}
	return ticket;
}

void ticket_destroy(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		if (ticket->stakeholders != NULL)
		{
			for (unsigned int i = 0; i < vector_getSize(ticket->stakeholders); ++i)
			{
				wchar_t* stakeholder = vector_getAt(ticket->stakeholders, i);
				free(stakeholder);
			}
			vector_destroy(ticket->stakeholders);
		}
		if (ticket->tags != NULL)
		{
			for (unsigned int i = 0; i < vector_getSize(ticket->tags); ++i)
			{
				wchar_t* tag = vector_getAt(ticket->tags, i);
				free(tag);
			}
			vector_destroy(ticket->tags);
		}
		if (ticket->notes != NULL)
		{
			for (unsigned int i = 0; i < vector_getSize(ticket->notes); ++i)
			{
				struct Note* note = vector_getAt(ticket->notes, i);
				free(note);
			}
			vector_destroy(ticket->notes);
		}

		free(ticket);
	}
}

void ticket_addNote(struct Ticket* ticket, wchar_t* author, wchar_t* content)
{
	if (ticket != NULL)
	{
		if (ticket->notes == NULL)
		{
			struct Note* note = malloc(sizeof(struct Note));
			if (note != NULL)
			{
				note->author = author;
				note->content = content;
				note->date = time(NULL);

				ticket->notes = vector_create();
				if (ticket->notes != NULL)
				{
					vector_resize(ticket->notes, 1);
					vector_setAt(ticket->notes, 0, note);
				}
				else
				{
					fwprintf(stderr, L"Failed to create notes vector");
				}
			}
			else
			{
				fwprintf(stderr, L"Failed to create note");
			}
		}
	}
}

wchar_t* ticket_getId(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->id;
	}
	return NULL;
}

char* ticket_getCustomerEmail(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->customer_email;
	}
	return NULL;
}

wchar_t* ticket_getTitle(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->title;
	}
	return NULL;
}

wchar_t* ticket_getType(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->type;
	}
	return NULL;
}

wchar_t* ticket_getSeverity(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->severity;
	}
	return NULL;
}

wchar_t* ticket_getDescription(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->description;
	}
	return NULL;
}

wchar_t* ticket_getTier(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->tier;
	}
	return NULL;
}

wchar_t* ticket_getStatus(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->status;
	}
	return NULL;
}

struct Vector* ticket_getTags(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->tags;
	}
	return NULL;
}

struct Vector* ticket_getNotes(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->notes;
	}
	return NULL;
}

void ticket_save(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		// TODO: Save to file
	}
}
