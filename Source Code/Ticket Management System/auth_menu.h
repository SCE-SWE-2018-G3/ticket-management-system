#pragma once

#include "menu.h"

// Creates the authentication menu.
// This handles logging in to the system.
struct Menu* createAuthMenu(void(*onAuthCallback)());
