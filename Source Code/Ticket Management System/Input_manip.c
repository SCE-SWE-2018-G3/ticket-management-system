#include  "Input_manip.h"

wchar_t* input_wchar(wchar_t** input ,int max_characters)
{
	wchar_t* context;
	fgetws(input, max_characters, stdin);
	fflush(stdin); //clears the buffer just in case there is input that exceeds the limit.
	wcstok(input, L"\n",&context);	
	return input;
}
char* input_char(char** input, int max_characters)
{
	fgets(input, max_characters, stdin);
	strtok(input, "\n");
	fflush(stdin);
	return input;
}
bool input_valid_email(char* input)
{
	//TODO
	return true;
}