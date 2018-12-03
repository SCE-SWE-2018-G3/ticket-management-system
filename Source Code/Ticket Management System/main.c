#include "auth_menu.h"
#include "customer_menu.h"
#include "supportgiver_menu.h"
#include "auth.h"
#include <leansql.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Menu* auth_menu = NULL;
struct Menu* customer_menu = NULL;
struct Menu* supportgiver_menu = NULL;
struct Menu* current_menu = NULL;

void whenAuth()
{
	if (auth_isSupportGiver())
	{
		current_menu = supportgiver_menu;
	}
	else
	{
		current_menu = customer_menu;
	}
}

void whenLogOut()
{
	auth_logOut();
	current_menu = auth_menu;
}

bool init()
{
	srand((unsigned int) time(NULL));

	LeanSQL_init("database");

	auth_menu = createAuthMenu(whenAuth);
	if (auth_menu == NULL)
	{
		return false;
	}

	customer_menu = createCustomerMenu(whenLogOut);
	if (customer_menu == NULL)
	{
		return false;
	}

	supportgiver_menu = createSupportGiverMenu(whenLogOut);
	if (supportgiver_menu == NULL)
	{
		return false;
	}

	return true;
}

void deinit()
{
	if (auth_menu != NULL)
	{
		menu_destroy(auth_menu);
		auth_menu = NULL;
	}
	if (customer_menu != NULL)
	{
		menu_destroy(customer_menu);
		customer_menu = NULL;
	}
	if (supportgiver_menu != NULL)
	{
		menu_destroy(supportgiver_menu);
		supportgiver_menu = NULL;
	}
}

int main(int argc, wchar_t* argv[])
{
	if (!init())
	{
		fwprintf(stderr, L"Could not create menu\n");
		deinit();
		return EXIT_FAILURE;
	}

	current_menu = auth_menu;

	while (menu_isOpen(current_menu) && !menu_hasError(current_menu))
	{
		system("CLS");
		menu_tick(current_menu);
	}

	if (menu_hasError(current_menu))
	{
		fwprintf(stderr, L"Error in menu: %s\n", menu_getError(current_menu));
		deinit();
		return EXIT_FAILURE;
	}

	deinit();
	return EXIT_SUCCESS;
}
