#include "menu_option.h"
#include <stdbool.h>
#include <string.h>

struct MenuOption
{
	wchar_t* title;
	void (*action)();
	void* data;
};

struct MenuOption* menuOption_create(wchar_t* title, void(*action)(), void* data)
{
	struct MenuOption* option = malloc(sizeof(struct MenuOption));
	if (option != NULL)
	{
		option->title = malloc(sizeof(wchar_t) * (wcslen(title) + 1));
		if (option->title != NULL)
		{
			option->title = wcscpy(option->title, title);
		}
		option->action = action;
		option->data = data;
	}
	return option;
}

void menuOption_destroy(struct MenuOption* option)
{
	if (option != NULL)
	{
		if (option->title != NULL)
		{
			free(option->title);
			option->title = NULL;
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
		if (option->title != NULL)
		{
			free(option->title);
		}

		option->title = malloc(sizeof(wchar_t) * (wcslen(title) + 1));
		if (option->title != NULL)
		{
			wcscpy(option->title, title);
		}
	}
}

void menuOption_performAction(struct MenuOption* option)
{
	if (option != NULL && option->action != NULL)
	{
		option->action(option->data);
	}
}
