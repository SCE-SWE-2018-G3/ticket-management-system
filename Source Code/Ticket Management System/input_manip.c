#include  "input_manip.h"
#include "user_container.h"
#include <stdio.h>
#include <string.h>

void input_wchar(wchar_t* input, int max_characters)
{
	if (input != NULL)
	{
		wchar_t* context;
		fgetws(input, max_characters, stdin);	
		wcstok(input, L"\n",&context);	
		fflush(stdin); // Clears the buffer just in case there is input that exceeds the limit.
	}
}
void input_char(char* input, int max_characters)
{
	if (input != NULL)
	{
		fgets(input, max_characters, stdin);
		strtok(input, "\n");
		fflush(stdin); // Clears the buffer just in case there is input that exceeds the limit.
	}
}

bool input_valid_email(char* input)
{
	bool valid = true;
	if (strchr(input, '@') != strrchr(input, '@') || strchr(input, '@') == NULL) //Checks if there is exactly 1 @ in the email.
		valid = false;
	if (userContainer_getByEmail(input) != NULL) //Checks if the email is already in the database.
		valid = false;
	return valid;
}