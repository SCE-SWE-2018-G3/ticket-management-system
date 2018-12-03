#pragma once

#include "ticket.h"
#include "vector.h"

// Updates the ticketContainer with a tickets information.
// This may either update an existing ticket in the database, or add a new one.
// Tickets are identified by their ID.
void ticketContainer_update(struct Ticket*);

// Returns a vector of all tickets in the database.
// This may fail if there are too many tickets.
// You own the vector, so make sure to destroy it and its contents when you're done.
struct Vector* ticketContainer_getAll();

// Returns the saved ticket with the specified ID.
// You own the ticket, so make sure to destroy it when you're done.
struct Ticket* ticketContainer_getById(wchar_t*);
