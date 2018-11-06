#pragma once

#include <stdbool.h>
#include <stdlib.h>

void auth_authenticate(char* email, wchar_t* password);
bool auth_isAuthenticated();
bool auth_isSupportGiver();
char* auth_getEmail();
