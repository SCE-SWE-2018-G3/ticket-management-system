#pragma once

#include <stdlib.h>
#include <stdbool.h>

struct ContactDetails
{
	wchar_t* name;
	wchar_t* phone;
};

struct User;

// Creates a new user object
struct User* user_create(char* email, wchar_t* password, wchar_t* salt, bool is_support_giver, wchar_t* name, wchar_t* phone);

// Destroys a user object
void user_destroy(struct User*);

// Getters:
char* user_getEmail(struct User*);
bool user_isSupportGiver(struct User*);

// Setters:
void user_setEmail(struct User*, char*);
void user_setPassword(struct User*, wchar_t*);
void user_setSalt(struct User*, wchar_t*);
void user_setName(struct User*, wchar_t*);
void user_setPhone(struct User*, wchar_t*);

// Checks if the saved password of the user matches the password given
bool user_passwordMatches(struct User*, wchar_t* password);
