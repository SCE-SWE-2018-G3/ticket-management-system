#include  "Input_manip.h"

void input_wchar(wchar_t** input ,int max_characters)
{
	wchar_t* context;
	fgetws(input, max_characters, stdin);	
	wcstok(input, L"\n",&context);	
	fflush(stdin); //clears the buffer just in case there is input that exceeds the limit.
}
void input_char(char** input, int max_characters)
{
	fgets(input, max_characters, stdin);
	strtok(input, "\n");
	fflush(stdin);	
}
bool input_valid_email(char* input)
{
	//TODO
	return true;
}