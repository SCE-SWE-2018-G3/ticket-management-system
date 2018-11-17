#pragma once

#include "vector.h"
#include <stdlib.h>
#include <time.h>

struct Note;
struct Ticket;

struct Ticket* ticket_create(wchar_t* title, wchar_t* type, wchar_t* description, char* customer_email);
void ticket_destroy(struct Ticket*);
void ticket_addNote(struct Ticket*, wchar_t* author, wchar_t* content);
wchar_t* ticket_getId(struct Ticket*);
char* ticket_getCustomerEmail(struct Ticket*);
wchar_t* ticket_getTitle(struct Ticket*);
wchar_t* ticket_getType(struct Ticket*);
wchar_t* ticket_getSeverity(struct Ticket*);
wchar_t* ticket_getDescription(struct Ticket*);
wchar_t* ticket_getTier(struct Ticket*);
wchar_t* ticket_getStatus(struct Ticket*);
struct Vector* ticket_getTags(struct Ticket*);
struct Vector* ticket_getNotes(struct Ticket*);
time_t ticket_getDate(struct Ticket*);
void ticket_copyFrom(struct Ticket* dest, struct Ticket* src);

time_t note_getDate(struct Note*);
wchar_t* note_getAuthor(struct Note*);
wchar_t* note_getContent(struct Note*);
