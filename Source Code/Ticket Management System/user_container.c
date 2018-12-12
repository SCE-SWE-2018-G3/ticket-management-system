#include "user_container.h"
#include "user_container_util.h"
#include <leansql.h>
#include <string.h>

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
	if (user == NULL)
	{
		return;
	}

	if (original_email == NULL)
	{
		original_email = user_getEmail(user);
	}

	wchar_t* original_email_wcs = malloc(sizeof(wchar_t) * (strlen(original_email) + 1));
	if (original_email_wcs == NULL)
	{
		fwprintf(stderr, L"Could not update user due to memory issue");
		return;
	}
	mbstowcs(original_email_wcs, original_email, strlen(original_email) + 1);

	wchar_t* data[6];
	struct userContainer_wcsArrStatus* data_status = userContainer_wcsArrFromUser(data, user);

	struct LeanSQL_ActionReport update = LeanSQL_update(L"Users", data, NULL, 6, findByUserEmail, original_email_wcs);
	free(original_email_wcs);
	if (update.success)
	{
		if (update.result.rows == 0) // User does not exist, was not added
		{
			update = LeanSQL_insert(L"Users", data, 6);
			if (!update.success)
			{
				fwprintf(stderr, L"Could not update user");
			}
		}
	}
	else
	{
		if (update.error == LEANSQL_ERROR_NO_TABLE)
		{
			userContainer_createDatabaseTable();
			update = LeanSQL_insert(L"Users", data, 6);
			if (!update.success)
			{
				fwprintf(stderr, L"Could not update user");
			}
		}
		else
		{
			fwprintf(stderr, L"Could not update user");
		}
	}
	
	userContainer_cleanUpWcsArr(data, data_status);
}