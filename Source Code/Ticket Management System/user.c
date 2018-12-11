#include "user.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "openssl/sha.h"

void sha256(char *src, char dst[65])
{
	unsigned char hash[SHA256_DIGEST_LENGTH];
	SHA256_CTX sha256;
	SHA256_Init(&sha256);
	SHA256_Update(&sha256, src, strlen(src));
	SHA256_Final(hash, &sha256);
	int i = 0;
	for (i = 0; i < SHA256_DIGEST_LENGTH; i++)
	{
		sprintf(dst + (i * 2), "%02x", hash[i]);
	}
	dst[64] = 0;
}

struct User
{
	char* email;
	char* password;
	char* salt;
	struct ContactDetails contact_details;
	bool is_support_giver;
};

struct User* user_create(char* email, wchar_t* password, bool is_hashed, wchar_t* salt, bool is_support_giver, wchar_t* name, wchar_t* phone)
{
	struct User* user = malloc(sizeof(struct User));
	if (user != NULL)
	{
		user->email = NULL;
		user->password = NULL;
		user->salt = NULL;
		user->contact_details.name = NULL;
		user->contact_details.phone = NULL;
		user->is_support_giver = is_support_giver;

		user_setEmail(user, email);
		user_setPassword(user, password, is_hashed);
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

char* user_getPasswordHash(struct User* user)
{
	if (user != NULL)
	{
		return user->password;
	}
	return NULL;
}

char* user_getPasswordSalt(struct User* user)
{
	if (user != NULL)
	{
		return user->salt;
	}
	return NULL;
}

struct ContactDetails user_getContactDetails(struct User* user)
{
	if (user != NULL)
	{
		return user->contact_details;
	}
	
	struct ContactDetails def;
	def.name = NULL;
	def.phone = NULL;
	return def;
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

	if (user != NULL)
	{
		if (user->email == NULL)
		{
			user->email = malloc(strlen(email) + 1);
			if (user->email == NULL)
			{
				return;
			}
		}
		else if (strlen(email) != strlen(user->email))
		{
			char* old_email = user->email;
			user->email = realloc(user->email, strlen(email) + 1);
			if (user->email == NULL)
			{
				user->email = old_email;
				return;
			}
		}

		strcpy(user->email, email);
	}
}

void user_setPassword(struct User* user, wchar_t* password_wcs, bool is_hashed)
{
	if (user != NULL && password_wcs != NULL)
	{
		char hash[65];
		char password[128];
		wcstombs(password, password_wcs, 128);
		unsigned int len;

		if (!is_hashed)
		{
			sha256(password, hash);
			len = strlen(hash);
		}
		else
		{
			len = strlen(password);
		}
		
		if (user->password != NULL)
		{
			free(user->password);
		}

		user->password = malloc(len + 1);
		if (user->password != NULL)
		{
			if (is_hashed)
			{
				strcpy(user->password, password);
			}
			else
			{
				strcpy(user->password, hash);
			}
		}
	}
}

void user_setSalt(struct User* user, wchar_t* salt_wcs)
{
	// TODO
}

void user_setName(struct User* user, wchar_t* name)
{
	if (user != NULL)
	{
		if (user->contact_details.name == NULL)
		{
			user->contact_details.name = malloc(sizeof(wchar_t) * (wcslen(name) + 1));
			if (user->contact_details.name == NULL)
			{
				return;
			}
		}
		else if (wcslen(name) != wcslen(user->contact_details.name))
		{
			wchar_t* old_name = user->contact_details.name;
			user->contact_details.name =realloc(user->contact_details.name, sizeof(wchar_t) * (wcslen(name) + 1));
			if (user->contact_details.name == NULL)
			{
				user->contact_details.name = old_name;
				return;
			}
		}

		wcscpy(user->contact_details.name, name);
	}
}

void user_setPhone(struct User* user, wchar_t* phone)
{
	if (user != NULL)
	{
		if (user->contact_details.phone == NULL)
		{
			user->contact_details.phone = malloc(sizeof(wchar_t) * (wcslen(phone) + 1));
			if (user->contact_details.phone == NULL)
			{
				return;
			}
		}
		else if (wcslen(phone) != wcslen(user->contact_details.phone))
		{
			wchar_t* old_phone = user->contact_details.phone;
			user->contact_details.phone = realloc(user->contact_details.phone, sizeof(wchar_t) * (wcslen(phone) + 1));
			if (user->contact_details.phone == NULL)
			{
				user->contact_details.phone = old_phone;
				return;
			}
		}

		wcscpy(user->contact_details.phone, phone);
	}
}

bool user_passwordMatches(struct User* user, wchar_t* password_wcs)
{
	if (user != NULL)
	{
		char hash[65];
		char password[128];
		wcstombs(password, password_wcs, 128);
		sha256(password, hash);

		return !strcmp(user->password, hash);
	}
	return false;
}
