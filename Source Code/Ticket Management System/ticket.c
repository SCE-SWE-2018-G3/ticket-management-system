#include "ticket.h"
#include <time.h>
#include <stdio.h>

wchar_t* generateRandomString(unsigned int length)
{
	wchar_t* str = malloc(sizeof(wchar_t) * (length + 1));
	if (str != NULL)
	{
		for (unsigned int i = 0; i < length; ++i)
		{
			wchar_t random_symbol[] = {
				(rand() % (L'Z' - L'A')) + L'A',
				(rand() % (L'9' - L'0')) + L'0',
				L'-'
			};
			str[i] = random_symbol[rand() % 3];
			if (i > 0 && str[i - 1] == str[i] && str[i] == '-')
			{
				--i;
			}
		}
		str[length] = L'\0';
	}
	return str;
}

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
	time_t creation_date;
};

struct Ticket* ticket_create(wchar_t* title, wchar_t* type,wchar_t* description, char* customer_email)
{
	struct Ticket* ticket = malloc(sizeof(struct Ticket));
	if (ticket != NULL)
	{
		ticket->id = generateRandomString(20);
		ticket->customer_email = customer_email;
		ticket->title = title;
		ticket->type = type;
		ticket->description = description;
		ticket->tier = L"T1";
		ticket->status = L"open";
		ticket->stakeholders = NULL;
		ticket->tags = NULL;
		ticket->notes = NULL;
		ticket->creation_date = time(NULL);
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
			ticket->notes = vector_create();
		}

		if (ticket->notes != NULL)
		{
			struct Note* note = malloc(sizeof(struct Note));
			if (note != NULL)
			{
				note->author = author;
				note->content = content;
				note->date = time(NULL);

				vector_push(ticket->notes, note);
			}
			else
			{
				fwprintf(stderr, L"Failed to create note");
			}
		}
		else
		{
			fwprintf(stderr, L"Failed to create notes vector");
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

void ticket_setId(struct Ticket* ticket, wchar_t* id)
{
	if (ticket != NULL)
	{
		ticket->id = id;
	}
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

struct Vector* ticket_getStakeholders(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->stakeholders;
	}
	return NULL;
}

void ticket_addStakeholder(struct Ticket* ticket, wchar_t* stakeholder)
{
	if (ticket != NULL)
	{
		if (ticket->stakeholders == NULL)
		{
			ticket->stakeholders = vector_create();
		}
		vector_push(ticket->stakeholders, stakeholder);
	}
}

void ticket_setSeverity(struct Ticket* ticket, wchar_t* severity)
{
	if (ticket != NULL)
	{
		ticket->severity = severity;
	}
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

void ticket_setTier(struct Ticket* ticket, wchar_t* tier)
{
	if (ticket != NULL)
	{
		ticket->tier = tier;
	}
}

wchar_t* ticket_getStatus(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->status;
	}
	return NULL;
}

void ticket_setStatus(struct Ticket* ticket, wchar_t* status)
{
	if (ticket != NULL)
	{
		ticket->status = status;
	}
}

struct Vector* ticket_getTags(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->tags;
	}
	return NULL;
}

void ticket_addTag(struct Ticket* ticket, wchar_t* tag)
{
	if (ticket != NULL)
	{
		if (ticket->tags == NULL)
		{
			ticket->tags = vector_create();
		}
		vector_push(ticket->tags, tag);
	}
}

struct Vector* ticket_getNotes(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->notes;
	}
	return NULL;
}

time_t ticket_getDate(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->creation_date;
	}
	return time(NULL);
}

time_t note_getDate(struct Note* note)
{
	if (note != NULL)
	{
		return note->date;
	}
	return time(NULL);
}

wchar_t* note_getAuthor(struct Note* note)
{
	if (note != NULL)
	{
		return note->author;
	}
	return NULL;
}

wchar_t* note_getContent(struct Note* note)
{
	if (note != NULL)
	{
		return note->content;
	}
	return NULL;
}

void ticket_copyFrom(struct Ticket* dest, struct Ticket* src)
{
	if (dest != NULL && src != NULL)
	{
		dest->id = src->id;
		dest->customer_email = src->customer_email;
		dest->title = src->title;
		dest->type = src->type;
		dest->severity = src->severity;
		dest->description = src->description;
		dest->tier = src->tier;
		dest->status = src->status;
		dest->stakeholders = src->stakeholders;
		dest->tags = src->tags;
		dest->notes = src->notes;
		dest->creation_date = src->creation_date;
	}
}
