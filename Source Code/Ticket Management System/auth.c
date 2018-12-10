#include "auth.h"
#include "user_container.h"

struct User* authenticated_user = NULL;

void auth_authenticate(char* email, wchar_t* password)
{
	if (auth_isAuthenticated())
	{
		auth_logOut();
	}

	if (email != NULL && password != NULL)
	{
		struct User* user = userContainer_getByEmail(email);
		if (user != NULL)
		{
			if (user_passwordMatches(user, password))
			{
				authenticated_user = user;
			}
		}
	}
}

void auth_logOut()
{
	if (authenticated_user != NULL)
	{
		user_destroy(authenticated_user);
		authenticated_user = NULL;
	}
}

bool auth_isAuthenticated()
{
	return authenticated_user != NULL;
}

bool auth_isSupportGiver()
{
	return authenticated_user != NULL && user_isSupportGiver(authenticated_user);
}

char* auth_getEmail()
{
	return user_getEmail(authenticated_user);
}

struct User* auth_getUser()
{	
	return authenticated_user;
}


