#include "supportgiver_menu.h"

void doNothing2()
{
}

struct Menu* createSupportGiverMenu(void(*onLogOutCallback)())
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Open Ticket", doNothing2));
		menu_addOption(menu, menuOption_create(L"View / Update Ticket", doNothing2));
		menu_addOption(menu, menuOption_create(L"Browse Tickets", doNothing2));
		menu_addOption(menu, menuOption_create(L"Create User", doNothing2));
		menu_addOption(menu, menuOption_create(L"Log Out", onLogOutCallback));
	}
	return menu;
}
