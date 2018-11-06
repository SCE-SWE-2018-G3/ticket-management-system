#include "menu_option.h"
#include <stdbool.h>
#include <string.h>

struct MenuOption
{
	wchar_t* title;
	void (*action)();
	bool title_was_malloced;
};

struct MenuOption* menuOption_create(wchar_t* title, void(*action)())
{
	struct MenuOption* option = malloc(sizeof(struct MenuOption));
	if (option != NULL)
	{
		option->title = title;
		option->action = action;
		option->title_was_malloced = false;
	}
	return option;
}

void menuOption_destroy(struct MenuOption* option)
{
	if (option != NULL)
	{
		if (option->title_was_malloced)
		{
			free(option->title);
		}
		free(option);
	}
}

wchar_t* menuOption_getTitle(struct MenuOption* option)
{
	if (option != NULL)
	{
		return option->title;
	}
	return NULL;
}

void menuOption_setTitle(struct MenuOption* option, wchar_t* title)
{
	if (option != NULL)
	{
		if (option->title_was_malloced && option->title != NULL)
		{
			free(option->title);
		}

		option->title = malloc(sizeof(wchar_t) * wcslen(title));
		if (option->title != NULL)
		{
			option->title_was_malloced = true;
			wcscpy(option->title, title);
		}
	}
}

void menuOption_performAction(struct MenuOption* option)
{
	if (option != NULL && option->action != NULL)
	{
		option->action();
	}
}
