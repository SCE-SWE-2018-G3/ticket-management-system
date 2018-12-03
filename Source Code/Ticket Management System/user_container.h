#pragma once

#include "user.h"

// Get a user by their email.
// You own the user, so make sure to destroy it when you're done.
struct User* userContainer_getByEmail(char*);
