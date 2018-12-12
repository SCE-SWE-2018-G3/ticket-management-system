#pragma once

#include <stdbool.h>

struct Vector;

void printTicketsArray(struct Vector* tickets);

bool filterByStatus(void* ticket, void* status);
bool filterByTier(void* ticket1, void* tier);
bool filterByType(void* ticket1, void* type);
bool filterByStakeholders(void* ticket1, void* stakeholders);
bool filterByMedia(void* ticket1, void* media);


bool searchByCustomerEmail(void* ticket1, void* customer_email);
bool searchByTags(void* ticket, void* tag);

bool sortByTitle(void* ticket1, void* ticket2);
