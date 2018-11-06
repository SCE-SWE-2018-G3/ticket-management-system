#include "user.h"
#include "stdbool.h"

struct User
{
	char* email;
	wchar_t* password;
	struct ContactDetails contact_details;
	bool is_support_giver;
};
