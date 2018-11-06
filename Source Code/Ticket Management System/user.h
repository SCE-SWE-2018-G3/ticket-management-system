#pragma once

#include <stdlib.h>

struct ContactDetails
{
	wchar_t* name;
	wchar_t* phone;
};

struct User;

struct User* user_create();
void user_destroy(struct User*);

