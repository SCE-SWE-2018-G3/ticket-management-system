#pragma once

#include "vector.h"
#include <stdlib.h>
#include <time.h>

struct Note;
struct Ticket;

// Ticket:

struct Ticket* ticket_create(wchar_t* title, wchar_t* type, wchar_t* description, char* customer_email);
void ticket_destroy(struct Ticket*);

void ticket_addNote(struct Ticket*, wchar_t* author, wchar_t* content);

wchar_t* ticket_getId(struct Ticket*);
void ticket_setId(struct Ticket*, wchar_t*);

char* ticket_getCustomerEmail(struct Ticket*);
void ticket_setCustomerEmail(struct Ticket*, char*);

wchar_t* ticket_getTitle(struct Ticket*);
void ticket_setTitle(struct Ticket*, wchar_t*);

wchar_t* ticket_getType(struct Ticket*);
void ticket_setType(struct Ticket*, wchar_t*);

wchar_t* ticket_getSeverity(struct Ticket*);
void ticket_setSeverity(struct Ticket*, wchar_t*);

struct Vector* ticket_getStakeholders(struct Ticket*);
void ticket_addStakeholder(struct Ticket*, wchar_t* stakeholder);

void ticket_setSeverity(struct Ticket*, wchar_t*);

wchar_t* ticket_getDescription(struct Ticket*);
void ticket_setDescription(struct Ticket*, wchar_t*);

wchar_t* ticket_getTier(struct Ticket*);
void ticket_setTier(struct Ticket*, wchar_t*);

wchar_t* ticket_getStatus(struct Ticket*);
void ticket_setStatus(struct Ticket*, wchar_t*);

struct Vector* ticket_getTags(struct Ticket*);
void ticket_addTag(struct Ticket*, wchar_t* tag);

struct Vector* ticket_getNotes(struct Ticket*);
time_t ticket_getDate(struct Ticket*);
void ticket_setDate(struct Ticket*, time_t);

void ticket_copyFrom(struct Ticket* dest, struct Ticket* src);

// Note:

time_t note_getDate(struct Note*);
wchar_t* note_getAuthor(struct Note*);
wchar_t* note_getContent(struct Note*);
