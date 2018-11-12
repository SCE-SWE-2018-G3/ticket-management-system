#pragma once

#include "ticket.h"
#include "vector.h"

void ticketContainer_update(struct Ticket*);
struct Vector* ticketContainer_getAll();
struct Ticket* ticketContainer_getById(wchar_t*);
