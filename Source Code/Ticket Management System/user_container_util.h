#pragma once

#include <wchar.h>

struct User;

// Creates an empty users table file.
void userContainer_createDatabaseTable();

// Creates a user from an array of 6 wide strings.
struct User* userContainer_createUserFromDatabaseRow(wchar_t** data);
