#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

void action()
{
	wprintf(L"We have success!\n");
	wprintf(L"יש לנו הצלחה\n");
}

int main(int argc, wchar_t* argv[])
{
	struct Menu* menu = menu_create();
	if (menu == NULL)
	{
		fwprintf(stderr, L"Could not create menu\n");
		return EXIT_FAILURE;
	}

	while (menu_isOpen(menu) && !menu_hasError(menu))
	{
		menu_tick(menu);
	}

	if (menu_hasError(menu))
	{
		fwprintf(stderr, L"Error in menu: %s\n", menu_getError(menu));
		menu_destroy(menu);
		return EXIT_FAILURE;
	}

	menu_destroy(menu);
	return EXIT_SUCCESS;
}
