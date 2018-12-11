#pragma once

#include <stdlib.h>

struct MenuOption;

// Creates a new menu option. `action` will be called when it's selected.
// `data` will be sent to `action` each time.
struct MenuOption* menuOption_create(wchar_t* title, void(*action)(), void* data);

// Destroys a menu option.
void menuOption_destroy(struct MenuOption*);

// Calls the `action` that was passed to `menuOption_create`.
void menuOption_performAction(struct MenuOption*);

wchar_t* menuOption_getTitle(struct MenuOption*);
void menuOption_setTitle(struct MenuOption*, wchar_t*);
