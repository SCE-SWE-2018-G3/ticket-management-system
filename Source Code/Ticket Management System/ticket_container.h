#pragma once

#include "ticket.h"

struct TicketContainer;

void ticketContainer_update(struct Ticket*);
struct Ticket* ticketContainer_getAll(struct Ticket*);
struct Ticket* ticketContainer_getById(wchar_t*);
