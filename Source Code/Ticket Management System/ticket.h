#pragma once

#include <stdlib.h>

struct Ticket;

struct Ticket* ticket_create();
void ticket_destroy(struct Ticket*);
void ticket_addNote(struct Ticket*, wchar_t* author, wchar_t* content);
wchar_t* ticket_getId(struct Ticket*);
char* ticket_getCustomerEmail(struct Ticket*);
wchar_t* ticket_getTitle(struct Ticket*);
wchar_t* ticket_getType(struct Ticket*);
wchar_t* ticket_getSeverity(struct Ticket*);
wchar_t* ticket_getDescription(struct Ticket*);
wchar_t* ticket_getTier(struct Ticket*);
wchar_t** ticket_getStatus(struct Ticket*);
wchar_t** ticket_getTags(struct Ticket*);
struct Note** ticket_getNotes(struct Ticket*);
