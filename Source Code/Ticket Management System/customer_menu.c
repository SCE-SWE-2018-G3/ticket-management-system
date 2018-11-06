#include "customer_menu.h"

void doNothing1()
{
}

struct Menu* createCustomerMenu()
{
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome\nWhat would you like to do?");
		menu_addOption(menu, menuOption_create(L"Contact Support", doNothing1));
		menu_addOption(menu, menuOption_create(L"View Support Call Status", doNothing1));
		menu_addOption(menu, menuOption_create(L"List My Support Calls", doNothing1));
		menu_addOption(menu, menuOption_create(L"Update Contact Information", doNothing1));
		menu_addOption(menu, menuOption_create(L"FAQ / Q&A", doNothing1));
		menu_addOption(menu, menuOption_create(L"Log Out", doNothing1));
	}
	return menu;
}
