#include "menu_option.h"

struct MenuOption
{
	wchar_t* title;
	void (*action)();
};

struct MenuOption* menuOption_create(wchar_t* title, void(*action)())
{
	struct MenuOption* option = malloc(sizeof(struct MenuOption));
	if (option != NULL)
	{
		option->title = title;
		option->action = action;
	}
	return option;
}

void menuOption_destroy(struct MenuOption* option)
{
	if (option != NULL)
	{
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

void menuOption_performAction(struct MenuOption* option)
{
	if (option != NULL && option->action != NULL)
	{
		option->action();
	}
}
