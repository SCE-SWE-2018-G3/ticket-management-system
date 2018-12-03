#pragma once

#include "menu.h"

// Creates the customer menu.
// This sets up its business logic.
struct Menu* createCustomerMenu(void(*onLogOutCallback)());
