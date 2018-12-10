#include "user_container_util.h"
#include "user.h"
#include <string.h>
#include <stdlib.h>
#include <leansql.h>

void userContainer_createDatabaseTable()
{
	wchar_t* columns[] =
	{
		L"Email",
		L"Password",
		L"Salt",
		L"Support Giver?",
		L"Name",
		L"Phone"
	};
	struct LeanSQL_ActionReport creation = LeanSQL_createTable(L"Users", columns, 6);
	if (!creation.success)
	{
		fwprintf(stderr, L"Could not create users database.\n");
	}
}

struct User* userContainer_createUserFromDatabaseRow(wchar_t** data)
{
	wchar_t* wide_email = data[0];
	char email[128];
	wcstombs(email, wide_email, 128);
	wchar_t* password = data[1];
	wchar_t* salt = data[2];
	wchar_t* is_support_giver_str = data[3];
	bool is_support_giver = is_support_giver_str && (is_support_giver_str[0] == '1') || !wcscmp(is_support_giver_str, L"true");
	wchar_t* name = data[4];
	wchar_t* phone = data[5];

	struct User* user = user_create(email, password, true, salt, is_support_giver, name, phone);
	return user;
}

struct userContainer_wcsArrStatus
{
	// No need for this right now.
	bool reserved_for_future_expansion;
};

struct userContainer_wcsArrStatus* userContainer_wcsArrFromUser(wchar_t** data, struct User* user)
{
	if (data == NULL || user == NULL)
	{
		return NULL;
	}

	struct userContainer_wcsArrStatus* status = malloc(sizeof(struct userContainer_wcsArrStatus));
	if (status == NULL)
	{
		fwprintf(stderr, L"Converting user to wcsArr failed due to memory error.\n");
		return NULL;
	}

	data[0] = user_getEmail(user);
	data[1] = user_getPasswordHash(user);
	data[2] = user_getPasswordSalt(user);
	data[3] = user_isSupportGiver(user) ? L"1" : L"0";

	struct ContactDetails user_contact_details = user_getContactDetails(user);
	data[4] = user_contact_details.name;
	data[5] = user_contact_details.phone;

	return status;
}

void userContainer_cleanUpWcsArr(wchar_t** data, struct userContainer_wcsArrStatus* status)
{
	if (status == NULL || data == NULL)
	{
		return;
	}

	// Reserved for future expansion

	free(status);
}
