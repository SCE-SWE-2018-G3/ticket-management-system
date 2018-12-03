#include "user.h"
#include "stdbool.h"

struct User
{
	char* email;
	wchar_t* password;
	struct ContactDetails contact_details;
	bool is_support_giver;
};

struct User* user_create(char* email, wchar_t* password, wchar_t* salt, bool is_support_giver, wchar_t* name, wchar_t* phone)
{
	struct User* user = malloc(sizeof(struct User));
	if (user != NULL)
	{
		user->email = NULL;
		user->password = NULL;
		user->contact_details.name = NULL;
		user->contact_details.phone = NULL;
		user->is_support_giver = is_support_giver;

		user_setEmail(user, email);
		user_setPassword(user, password);
		user_setSalt(user, salt);
		user_setName(user, name);
		user_setPhone(user, phone);
	}
	return user;
}

void user_destroy(struct User* user)
{
	if (user != NULL)
	{
		if (user->email != NULL)
		{
			free(user->email);
			user->email = NULL;
		}
		if (user->password != NULL)
		{
			free(user->password);
			user->password = NULL;
		}
		if (user->contact_details.name != NULL)
		{
			free(user->contact_details.name);
			user->contact_details.name = NULL;
		}
		if (user->contact_details.phone != NULL)
		{
			free(user->contact_details.phone);
			user->contact_details.phone = NULL;
		}
		free(user);
	}
}

char* user_getEmail(struct User* user)
{
	if (user != NULL)
	{
		return user->email;
	}
	return NULL;
}

bool user_isSupportGiver(struct User* user)
{
	if (user != NULL)
	{
		return user->is_support_giver;
	}
	return false;
}

void user_setEmail(struct User* user, char* email)
{
	// TODO
}

void user_setPassword(struct User* user, wchar_t* password)
{
	// TODO
}

void user_setSalt(struct User* user, wchar_t* salt)
{
	// TODO
}

void user_setName(struct User* user, wchar_t* name)
{
	// TODO
}

void user_setPhone(struct User* user, wchar_t* phone)
{
	// TODO
}

bool user_passwordMatches(struct User* user, wchar_t* password)
{
	if (user != NULL)
	{
		// TODO
	}
	return false;
}
