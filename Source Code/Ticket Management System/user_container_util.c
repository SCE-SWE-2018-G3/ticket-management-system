#include "user_container_util.h"
#include "user.h"
#include <string.h>
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
