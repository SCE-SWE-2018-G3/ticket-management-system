#include "menu.h"
#include "vector.h"
#include "menu_option.h"
#include <stdio.h>

struct Menu
{
	bool is_open;
	wchar_t* error;
	wchar_t* title;
	struct Vector* options;
};

struct Menu* menu_create()
{
	struct Menu* menu = malloc(sizeof(struct Menu));
	if (menu != NULL)
	{
		menu->is_open = true;
		menu->error = NULL;
		menu->title = NULL;

		menu->options = vector_create();
		if (menu->options == NULL)
		{
			menu->is_open = false;
			menu->error = L"Failed to create options vector";
		}
	}
	return menu;
}

void menu_destroy(struct Menu* menu)
{
	if (menu != NULL)
	{
		if (menu->options != NULL)
		{
			for (unsigned int i = 0; i < vector_getSize(menu->options); ++i)
			{
				struct MenuOption* option = vector_getAt(menu->options, i);
				menuOption_destroy(option);
			}
			vector_destroy(menu->options);
		}
		free(menu);
	}
}

bool menu_hasError(struct Menu* menu)
{
	if (menu != NULL)
	{
		return menu->error != NULL;
	}
	return true;
}

bool menu_isOpen(struct Menu* menu)
{
	if (menu != NULL)
	{
		return menu->is_open;
	}
	return false;
}

wchar_t* menu_getError(struct Menu* menu)
{
	if (menu != NULL)
	{
		return menu->error;
	}
	return L"Menu is NULL";
}

void menu_setTitle(struct Menu* menu, wchar_t* title)
{
	if (menu != NULL)
	{
		menu->title = title;
	}
}

void menu_tick(struct Menu* menu)
{
	if (menu != NULL)
	{
		if (menu->title != NULL)
		{
			wprintf(L"%s\n", menu->title);
		}

		for (unsigned int i = 0; i < vector_getSize(menu->options); ++i)
		{
			struct MenuOption* option = vector_getAt(menu->options, i);
			wprintf(L"%d: %s\n", i+1, menuOption_getTitle(option));
		}
		wprintf(L"Press Q to quit.\n");

		char input[10];
		bool input_is_valid;
		do
		{
			input_is_valid = true;

			fflush(stdin);
			fgets(input, 10, stdin);
			unsigned int input_as_int = atoi(input);
			if (input_as_int != 0) // able to convert input to int
			{
				if (input_as_int >= 1 && input_as_int <= vector_getSize(menu->options))
				{
					struct MenuOption* option = vector_getAt(menu->options, input_as_int - 1);
					if (option != NULL)
					{
						menuOption_performAction(option);
					}
					else
					{
						menu->error = L"Menu has unexpectedly NULL menu option";
					}
				}
				else
				{
					input_is_valid = false;
				}
			}
			else // unable to convert input to int
			{
				wchar_t input_as_char = input[0];
				switch (input_as_char)
				{
				case('q'):
				case('Q'):
					menu->is_open = false;
					break;
				case('\n'):
					break;

				default:
					input_is_valid = false;
				}
			}

			if (!input_is_valid)
			{
				wprintf(L"Input is invalid. Try again.\n");
			}
		} while (!input_is_valid);
	}
}

void menu_addOption(struct Menu* menu, struct MenuOption* option)
{
	if (menu != NULL && option != NULL)
	{
		unsigned int old_vector_size = vector_getSize(menu->options);
		vector_resize(menu->options, old_vector_size + 1);
		vector_setAt(menu->options, old_vector_size, option);
	}
	if (menu != NULL && option == NULL)
	{
		menu->error = L"Attempted adding NULL option\n";
	}
}
