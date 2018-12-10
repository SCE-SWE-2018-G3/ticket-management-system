#pragma once

#include <stdlib.h>
#include <wchar.h>
#include <stdbool.h>
/**
* This function fixes isssues while inputting data from the user if the input is widechar also clears the buffer so 
* there are no skips in input reading.
*@param (wide char)input- a pointer to the input to put data into.
*@param (int)max_characters The maximum amount to read from the user
*/
void input_wchar(wchar_t* input, int max_characters);
/**
* This function fixes isssues while inputting data from the user if the input is char also clears the buffer so
* there are no skips in input reading.
*@param (char)input a pointer to the input to put data into.
*@param (int)max_characters The maximum amount to read from the user
*/
void input_char(char* input, int max_characters);
/**
* Checks if an email adress is valid
*@param input- the email address to check
*@return True if it's valid, else return false (1 or 0)
*/
bool input_valid_email(char* input);
