#pragma once

#include "menu_option.h"
#include <stdbool.h>
#include <stdlib.h>

struct Menu;

struct Menu* menu_create();
void menu_destroy(struct Menu*);
bool menu_hasError(struct Menu*);
bool menu_isOpen(struct Menu*);
wchar_t* menu_getError(struct Menu*);
void menu_setTitle(struct Menu*, wchar_t*);
void menu_tick(struct Menu*);
void menu_addOption(struct Menu*, struct MenuOption*);
