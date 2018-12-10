#include "user_container.h"
#include "user_container_util.h"
#include <leansql.h>

bool findByUserEmail(wchar_t* column, wchar_t* value, void* desired_email)
{
	return (wcscmp(column, L"Email") == 0) && (wcscmp(value, desired_email) == 0);
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
void userContainer_update(struct User* user, char* original_email)
{

}