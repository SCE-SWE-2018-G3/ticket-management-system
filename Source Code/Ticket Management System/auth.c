#include "auth.h"

bool authenticated = false;
bool support_giver = true;

void auth_authenticate(char* email, wchar_t* password)
{
	authenticated = true; // TODO
}

bool auth_isAuthenticated()
{
	return authenticated;
}

bool auth_isSupportGiver()
{
	return support_giver;
}