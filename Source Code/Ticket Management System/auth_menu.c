#include "auth_menu.h"
#include "auth.h"
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
		wchar_t new_title[64] = L"E-Mail: ";
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
		wchar_t new_title[64] = L"Password: ";
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
		wprintf(L"Invalid E-Mail or Password.\n");
	}
}

struct Menu* createAuthMenu(void(*onAuthCallback)())
{
	onAuth = onAuthCallback;
	struct Menu* menu = menu_create();
	if (menu != NULL)
	{
		menu_setTitle(menu, L"Welcome to the system\n=====================\nPlease log in:\n(Don't have a user? Contact HR)");

		email_option    = menuOption_create(L"E-Mail:",   setEmail);
		password_option = menuOption_create(L"Password:", setPassword);
		login_option    = menuOption_create(L"Log In",    login);

		menu_addOption(menu, email_option);
		menu_addOption(menu, password_option);
		menu_addOption(menu, login_option);
	}
	return menu;
}
