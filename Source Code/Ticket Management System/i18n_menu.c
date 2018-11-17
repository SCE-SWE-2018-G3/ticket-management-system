#include "i18n_menu.h"
#include "i18n.h"

struct Menu* i18n_menu = NULL;
void(*onPickI18n)() = NULL;

void selectEnglish()
{
	i18n_setCurrentLocale(I18N_LOCALE_ENGLISH);
}

void selectHebrew()
{
	i18n_setCurrentLocale(I18N_LOCALE_HEBREW);
}

struct Menu* createI18nMenu(void(*onPickI18nCallback)())
{
	i18n_menu = menu_create();
	if (i18n_menu != NULL)
	{
		menu_setTitle(i18n_menu, L"Please select language.");
		struct MenuOption* english_option = menuOption_create(L"English", selectEnglish);
		struct MenuOption* hebrew_option = menuOption_create(L"תירבע", selectHebrew);
		struct MenuOption* continue_option = menuOption_create(L"Ok", onPickI18nCallback);

		menu_addOption(i18n_menu, english_option);
		menu_addOption(i18n_menu, hebrew_option);
		menu_addOption(i18n_menu, continue_option);
	}
	return i18n_menu;
}
