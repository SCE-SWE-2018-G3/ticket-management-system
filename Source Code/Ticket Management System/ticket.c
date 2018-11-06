#include "ticket.h"
#include <time.h>

struct Note
{
	time_t date;
	wchar_t* author;
	wchar_t* content;
};

struct Ticket
{
	wchar_t* id;
	wchar_t* customer_email;
	wchar_t* title;
	wchar_t* type;
	wchar_t* severity;
	wchar_t* description;
	wchar_t* tier;
	wchar_t* status;
	wchar_t** stakeholders;
	wchar_t** tags;
	struct Note** notes;
};
