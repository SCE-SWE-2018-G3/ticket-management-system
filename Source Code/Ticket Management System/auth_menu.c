#include "auth_menu.h"
#include "auth.h"
#include "i18n.h"
#include <stdio.h>
#include <string.h>

char* email;
wchar_t* password;
struct MenuOption* email_option;
struct MenuOption* password_option;
struct MenuOption* login_option;
void (*onAuth)() = NULL;

void setEmail()
{
	char input[100];
	fgets(input, 10, stdin);
	strtok(input, "\n");
	email = input;
	if (email_option != NULL)
	{
		wchar_t email_wchar[64];
		email_wchar[0] = L'\0';
		swprintf(email_wchar, 64, L"%S", email);
		wchar_t new_title[64];
		wcscpy(new_title, i18n_getString(I18N_STRING_AUTH_EMAIL, I18N_LOCALE_CURRENT));
		wcscat(new_title, email_wchar);
		menuOption_setTitle(email_option, new_title);
	}
}

void setPassword()
{
	wchar_t* context;
	wchar_t input[100];
	fgetws(input, 10, stdin);
	wcstok(input, L"\n", &context);
	password = input;
	if (email_option != NULL)
	{
		wchar_t new_title[64];
		wcscpy(new_title, i18n_getString(I18N_STRING_AUTH_PASSWORD, I18N_LOCALE_CURRENT));
		wcscat(new_title, password);
		menuOption_setTitle(password_option, new_title);
	}
}

void login()
{
	auth_authenticate(email, password);
	if (auth_isAuthenticated())
	{
		if (onAuth != NULL)
		{
			onAuth();
		}
	}
	else
	{
		wprintf(L"%s\n", i18n_getString(I18N_STRING_AUTH_INVALID, I18N_LOCALE_CURRENT));
	}
}

struct Menu* createAuthMenu(void(*onAuthCallback)())
{
	onAuth = onAuthCallback;
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, i18n_getString(I18N_STRING_AUTH_WELCOME, I18N_LOCALE_CURRENT));
		
		email_option    = menuOption_create(i18n_getString(I18N_STRING_AUTH_EMAIL, I18N_LOCALE_CURRENT),   setEmail);
		password_option = menuOption_create(i18n_getString(I18N_STRING_AUTH_PASSWORD, I18N_LOCALE_CURRENT), setPassword);
		login_option    = menuOption_create(i18n_getString(I18N_STRING_AUTH_LOGIN, I18N_LOCALE_CURRENT),    login);

		menu_addOption(menu, email_option);
		menu_addOption(menu, password_option);
		menu_addOption(menu, login_option);
	}
	return menu;
}
