#include "ticket.h"
#include <time.h>
#include <stdio.h>
#include <wchar.h>
#include <string.h>

wchar_t* generateRandomString(unsigned int length)
{
	wchar_t* str = malloc(sizeof(wchar_t) * (length + 1));
	if (str != NULL)
	{
		for (unsigned int i = 0; i < length; ++i)
		{
			if (i % 4 == 0 && i > 0)
			{
				str[i] = L'-';
			}
			else
			{
				wchar_t random_symbol[] = {
					(rand() % (L'Z' - L'A')) + L'A',
					(rand() % (L'9' - L'0')) + L'0'
				};
				str[i] = random_symbol[rand() % 2];
			}
		}
		str[length] = L'\0';
	}
	return str;
}

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
	wchar_t* media;

	struct Vector* stakeholders;
	struct Vector* tags;
	struct Vector* notes;
	time_t creation_date;
};

struct Ticket* ticket_create(wchar_t* title, wchar_t* type, wchar_t* description,wchar_t* media, char* customer_email)
{
	struct Ticket* ticket = malloc(sizeof(struct Ticket));
	if (ticket != NULL)
	{
		ticket->id = NULL;
		ticket->customer_email = NULL;
		ticket->title = NULL;
		ticket->type = NULL;
		ticket->severity = NULL;
		ticket->media = NULL;
		ticket->description = NULL;
		ticket->tier = NULL;
		ticket->status = NULL;
		ticket->stakeholders = NULL;
		ticket->tags = NULL;
		ticket->notes = NULL;

		ticket->id = generateRandomString(20);
		ticket_setCustomerEmail(ticket, customer_email);
		ticket_setTitle(ticket, title);
		ticket_setType(ticket, type);
		ticket_setDescription(ticket, description);
		ticket_setMedia(ticket, media);
		ticket_setTier(ticket, L"T1");
		ticket_setStatus(ticket, L"open");
		ticket->creation_date = time(NULL);
	}
	return ticket;
}

void ticket_destroy(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		if (ticket->id != NULL)
		{
			free(ticket->id);
			ticket->id = NULL;
		}
		
		if (ticket->customer_email != NULL)
		{
			free(ticket->customer_email);
			ticket->customer_email = NULL;
		}

		if (ticket->title != NULL)
		{
			free(ticket->title);
			ticket->title = NULL;
		}

		if (ticket->type != NULL)
		{
			free(ticket->type);
			ticket->type = NULL;
		}

		if (ticket->severity != NULL)
		{
			free(ticket->severity);
			ticket->severity = NULL;
		}

		if (ticket->description != NULL)
		{
			free(ticket->description);
			ticket->description = NULL;
		}

		if (ticket->tier != NULL)
		{
			free(ticket->tier);
			ticket->tier = NULL;
		}

		if (ticket->status != NULL)
		{
			free(ticket->status);
			ticket->status = NULL;
		}

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
				wchar_t* note = vector_getAt(ticket->notes, i);
				free(note);
			}
			vector_destroy(ticket->notes);
		}

		free(ticket);
	}
}

void ticket_addNote(struct Ticket* ticket, wchar_t* note_content)
{
	if (ticket != NULL)
	{
		if (ticket->notes == NULL)
		{
			ticket->notes = vector_create();
		}

		if (ticket->notes != NULL)
		{
			wchar_t* note = malloc(sizeof(wchar_t) * (wcslen(note_content)+1));
			if (note != NULL)
			{
				wcscpy(note, note_content);
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
		if (ticket->id == NULL)
		{
			ticket->id = malloc(sizeof(wchar_t) * (wcslen(id) + 1));
			if (ticket->id == NULL)
			{
				return;
			}
		}
		else if(wcslen(id) != wcslen(ticket->id))
		{
			wchar_t* old_id = ticket->id;
			ticket->id = realloc(ticket->id, sizeof(wchar_t) * (wcslen(id) + 1));
			if (ticket->id == NULL)
			{
				ticket->id = old_id;
				return;
			}
		}

		wcscpy(ticket->id, id);
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

void ticket_setCustomerEmail(struct Ticket* ticket, char* email)
{
	if (ticket != NULL)
	{
		if (ticket->customer_email == NULL)
		{
			ticket->customer_email = malloc(strlen(email) + 1);
			if (ticket->customer_email == NULL)
			{
				return;
			}
		}
		else if(strlen(email) != strlen(ticket->customer_email))
		{
			char* old_email = ticket->customer_email;
			ticket->customer_email = realloc(ticket->customer_email, strlen(email) + 1);
			if (ticket->customer_email == NULL)
			{
				ticket->customer_email = old_email;
				return;
			}
		}

		strcpy(ticket->customer_email, email);
	}
}

wchar_t* ticket_getTitle(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->title;
	}
	return NULL;
}

void ticket_setTitle(struct Ticket* ticket, wchar_t* title)
{
	if (ticket != NULL)
	{
		if (ticket->title == NULL)
		{
			ticket->title = malloc(sizeof(wchar_t) * (wcslen(title) + 1));
			if (ticket->title == NULL)
			{
				return;
			}
		}
		else if(wcslen(title) != wcslen(ticket->title))
		{
			wchar_t* old_title = ticket->title;
			ticket->title = realloc(ticket->title, sizeof(wchar_t) * (wcslen(title) + 1));
			if (ticket->title == NULL)
			{
				ticket->title = old_title;
				return;
			}
		}

		wcscpy(ticket->title, title);
	}
}

wchar_t* ticket_getType(struct Ticket* ticket)
{
	if (ticket != NULL)
	{
		return ticket->type;
	}
	return NULL;
}

void ticket_setType(struct Ticket* ticket, wchar_t* type)
{
	if (ticket != NULL)
	{
		if (ticket->type == NULL)
		{
			ticket->type = malloc(sizeof(wchar_t) * (wcslen(type) + 1));
			if (ticket->type == NULL)
			{
				return;
			}
		}
		else if(wcslen(type) != wcslen(ticket->type))
		{
			wchar_t* old_type = ticket->type;
			ticket->type = realloc(ticket->type, sizeof(wchar_t) * (wcslen(type) + 1));
			if (ticket->type == NULL)
			{
				ticket->type = old_type;
				return;
			}
		}

		wcscpy(ticket->type, type);
	}
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
		wchar_t* alloced_stakeholder = malloc(sizeof(wchar_t) * (wcslen(stakeholder) + 1));
		if (alloced_stakeholder != NULL)
		{
			wcscpy(alloced_stakeholder, stakeholder);
			vector_push(ticket->stakeholders, alloced_stakeholder);
		}
	}
}

void ticket_setSeverity(struct Ticket* ticket, wchar_t* severity)
{
	if (ticket != NULL)
	{
		if (ticket->severity == NULL)
		{
			ticket->severity = malloc(sizeof(wchar_t) * (wcslen(severity) + 1));
			if (ticket->severity == NULL)
			{
				return;
			}
		}
		else if(wcslen(severity) != wcslen(ticket->severity))
		{
			wchar_t* old_severity = ticket->severity;
			ticket->severity = realloc(ticket->severity, sizeof(wchar_t) * (wcslen(severity) + 1));
			if (ticket->severity == NULL)
			{
				ticket->severity = old_severity;
				return;
			}
		}
		wcscpy(ticket->severity, severity);
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

void ticket_setDescription(struct Ticket* ticket, wchar_t* description)
{
	if (ticket != NULL)
	{
		if (ticket->description == NULL)
		{
			ticket->description = malloc(sizeof(wchar_t) * (wcslen(description) + 1));
			if (ticket->description == NULL)
			{
				return;
			}
		}
		else if(wcslen(description) != wcslen(ticket->description))
		{
			wchar_t* old_description = ticket->description;
			ticket->description = realloc(ticket->description, sizeof(wchar_t) * (wcslen(description) + 1));
			if (ticket->description == NULL)
			{
				ticket->description = old_description;
				return;
			}
		}

		wcscpy(ticket->description, description);
	}
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
		if (ticket->tier == NULL)
		{
			ticket->tier = malloc(sizeof(wchar_t) * (wcslen(tier) + 1));
			if (ticket->tier == NULL)
			{
				return;
			}
		}
		else if (wcslen(tier) != wcslen(ticket->tier))
		{
			wchar_t* old_tier = ticket->tier;
			ticket->tier = realloc(ticket->tier, sizeof(wchar_t) * (wcslen(tier) + 1));
			if (ticket->tier == NULL)
			{
				ticket->tier = old_tier;
				return;
			}
		}

		wcscpy(ticket->tier, tier);
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

wchar_t * ticket_getMedia(struct Ticket *ticket)
{
	if (ticket != NULL)
	{
		return ticket->media;
	}
	return NULL;
}

void ticket_setStatus(struct Ticket* ticket, wchar_t* status)
{
	if (ticket != NULL)
	{
		if (ticket->status == NULL)
		{
			ticket->status = malloc(sizeof(wchar_t) * (wcslen(status) + 1));
			if (ticket->status == NULL)
			{
				return;
			}
		}
		else if (wcslen(status) != wcslen(ticket->status))
		{
			wchar_t* old_status = ticket->status;
			ticket->status = realloc(ticket->status, sizeof(wchar_t) * (wcslen(status) + 1));
			if (ticket->status == NULL)
			{
				ticket->status = old_status;
				return;
			}
		}

		wcscpy(ticket->status, status);
	}
}

void ticket_setMedia(struct Ticket *ticket, wchar_t *media)
{
	if (ticket != NULL)
	{
		if (ticket->media == NULL)
		{
			ticket->media = malloc(sizeof(wchar_t) * (wcslen(media) + 1));
			if (ticket->media == NULL)
			{
				return;
			}
		}
		else if (wcslen(media) != wcslen(ticket->media))
		{
			wchar_t* old_media = ticket->media;
			ticket->media = realloc(ticket->media, sizeof(wchar_t) * (wcslen(media) + 1));
			if (ticket->media == NULL)
			{
				ticket->media = old_media;
				return;
			}
		}
		wcscpy(ticket->media, media);
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
		wchar_t* alloced_tag = malloc(sizeof(wchar_t) * (wcslen(tag) + 1));
		if (alloced_tag != NULL)
		{
			wcscpy(alloced_tag, tag);
			vector_push(ticket->tags, alloced_tag);
		}
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

void ticket_setDate(struct Ticket* ticket, time_t time)
{
	if (ticket != NULL)
	{
		ticket->creation_date = time;
	}
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
