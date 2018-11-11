#pragma once

#include <stdlib.h>

struct MenuOption;

struct MenuOption* menuOption_create(wchar_t* title, void(*action)());
void menuOption_destroy(struct MenuOption*);
wchar_t* menuOption_getTitle(struct MenuOption*);
void menuOption_setTitle(struct MenuOption*, wchar_t*);
void menuOption_performAction(struct MenuOption*);
