#include "user_container.h"
#include <leansql.h>

bool findByUserEmail(wchar_t* column, wchar_t* value, void* desired_email)
{
	return (wcscmp(column, L"Email") == 0) && (wcscmp(value, desired_email) == 0);
}

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

struct User* userContainer_getByEmail(char* email)
{
	struct User* user = NULL;

	wchar_t email_wcs[128];
	mbstowcs(email_wcs, email, 128);

	struct LeanSQL_ActionReport select = LeanSQL_select(L"Users", NULL, 0, findByUserEmail, email_wcs);
	if (select.success)
	{
		if (select.result.rows == 1)
		{
			user = userContainer_createUserFromDatabaseRow(select.result.data[0]);
		}
		else if (select.result.rows == 0)
		{
			user = NULL;
		}
		else
		{
			fwprintf(stderr, L"Users database has multiple users with identical emails\n");
		}

		LeanSQL_destroyResultSet(&select.result);
	}

	return user;
}
