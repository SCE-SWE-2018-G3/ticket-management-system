#pragma once

#include "menu_option.h"
#include <stdbool.h>
#include <stdlib.h>

struct Menu;

// Creates a new menu.
struct Menu* menu_create();

// Destroys a menu, performing deallocation of its options.
void menu_destroy(struct Menu*);

// Is the menu open?
bool menu_isOpen(struct Menu*);

// Did the menu encounter an error?
bool menu_hasError(struct Menu*);

// What is th reror that the menu encountered?
wchar_t* menu_getError(struct Menu*);

// Draws the options and asks the user to chose one.
// Performs input validation, and calls the action of the chosen MenuOption.
void menu_tick(struct Menu*);

// Sets the title of the menu. It will be displayed on each tick.
void menu_setTitle(struct Menu*, wchar_t*);

// Adds a MenuOption to the menu. The menu then owns it, so don't give multiple menues the same option object.
void menu_addOption(struct Menu*, struct MenuOption*);
