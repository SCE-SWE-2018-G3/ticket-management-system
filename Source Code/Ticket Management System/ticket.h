#pragma once

#include "vector.h"
#include <stdlib.h>
#include <time.h>

struct Note;
struct Ticket;

// Ticket:

// Creates a new ticket.
struct Ticket* ticket_create(wchar_t* title, wchar_t* type, wchar_t* description, char* customer_email);

// Destroys a ticket, performing deallocation.
void ticket_destroy(struct Ticket*);

// Getters:
wchar_t* ticket_getId(struct Ticket*);
char* ticket_getCustomerEmail(struct Ticket*);
wchar_t* ticket_getTitle(struct Ticket*);
wchar_t* ticket_getType(struct Ticket*);
wchar_t* ticket_getSeverity(struct Ticket*);
struct Vector* ticket_getStakeholders(struct Ticket*);
wchar_t* ticket_getDescription(struct Ticket*);
wchar_t* ticket_getTier(struct Ticket*);
wchar_t* ticket_getStatus(struct Ticket*);
struct Vector* ticket_getTags(struct Ticket*);
struct Vector* ticket_getNotes(struct Ticket*);
time_t ticket_getDate(struct Ticket*);

// Setters:
void ticket_setId(struct Ticket*, wchar_t*);
void ticket_setCustomerEmail(struct Ticket*, char*);
void ticket_setTitle(struct Ticket*, wchar_t*);
void ticket_setType(struct Ticket*, wchar_t*);
void ticket_setSeverity(struct Ticket*, wchar_t*);
void ticket_setSeverity(struct Ticket*, wchar_t*);
void ticket_setDescription(struct Ticket*, wchar_t*);
void ticket_setTier(struct Ticket*, wchar_t*);
void ticket_setStatus(struct Ticket*, wchar_t*);
void ticket_setStakeholders(struct Ticket*, wchar_t*);
void ticket_setTags(struct Ticket*, wchar_t*);
void ticket_setDate(struct Ticket*, time_t);

void ticket_addTag(struct Ticket*, wchar_t* tag);
void ticket_addStakeholder(struct Ticket*, wchar_t* stakeholder);
void ticket_addNote(struct Ticket*, wchar_t* content);

// Makes a new ticket out of an existing ticket
void ticket_copyFrom(struct Ticket* dest, struct Ticket* src);
