#pragma once

#include <wchar.h>

struct User;
struct ticketContainer_wcsArrStatus;

// Creates an empty users table file.
void userContainer_createDatabaseTable();

// Creates a user from an array of 6 wide strings.
struct User* userContainer_createUserFromDatabaseRow(wchar_t** data);

// Creates an array of 6 wide strings from a user. wcsArr points to the array.
struct userContainer_wcsArrStatus* userContainer_wcsArrFromUser(wchar_t** wcsArr, struct User* user);

// Deallocates what needs to be deallocated in `wcsArr`.
void userContainer_cleanUpWcsArr(wchar_t** wcsArr, struct userContainer_wcsArrStatus*);
