#pragma once

#include <wchar.h>

struct Ticket;
struct ticketContainer_wcsArrStatus;

// Creates an empty tickets table file.
void ticketContainer_createDatabaseTable();

// Creates a ticket from an array of 13 wide strings.
struct Ticket* ticketContainer_createTicketFromDatabaseRow(wchar_t** data);

// Creates an array of 13 wide strings from a ticket. wcsArr points to the array.
struct ticketContainer_wcsArrStatus* ticketContainer_wcsArrFromTicket(wchar_t** wcsArr, struct Ticket* ticket);

// Deallocates what needs to be deallocated in `wcsArr`.
void ticketContainer_cleanUpWcsArr(wchar_t** wcsArr, struct ticketContainer_wcsArrStatus*);
