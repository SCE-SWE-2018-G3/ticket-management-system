#pragma once

#include <stdbool.h>
#include <stdlib.h>

void auth_authenticate(wchar_t* email, wchar_t* password);
bool auth_authenticated();
bool auth_isSupportGiver();
