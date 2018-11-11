#include "auth.h"

bool authenticated = false;
bool support_giver = false;

void auth_authenticate(char* email, wchar_t* password)
{
	authenticated = true; // TODO
}

void auth_logOut()
{
	authenticated = false; // TODO
}

bool auth_isAuthenticated()
{
	return authenticated;
}

bool auth_isSupportGiver()
{
	return support_giver;
}

char* auth_getEmail()
{
	// TODO
	return "somecustomer@gmail.com";
}
