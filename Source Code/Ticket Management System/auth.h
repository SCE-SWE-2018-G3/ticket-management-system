#pragma once

#include <stdbool.h>
#include <stdlib.h>

// Attempts to log-in with the provided credentials.
// Test for success by calling `auth_isAuthenticated()`.
void auth_authenticate(char* email, wchar_t* password);

// Logs out of the system
void auth_logOut();

// Are we logged in successfully?
bool auth_isAuthenticated();

// If we're logged in, are we a support giver?
bool auth_isSupportGiver();

// Gets the email of the logged in user
char* auth_getEmail();

/**
gets the user that's logged in right now
@return User* a pointer to the logged in user
*/
struct User* auth_getUser();
