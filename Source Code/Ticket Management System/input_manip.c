#include  "input_manip.h"
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
	//TODO
	return true;
}