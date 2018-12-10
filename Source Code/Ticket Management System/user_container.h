#pragma once

#include "user.h"

/*
*Get a user by their email.
* You own the user, so make sure to destroy it when you're done.
*@param char* email- a string representing an email.
*@return the a point of the user struct of the user that his email matches to the data base.
*/
struct User* userContainer_getByEmail(char* email);

/*
*Updates a user in the database.
*@param user- the user to update (struct user pointer)*
*@param original_email - a string of the original email the user had in case the email was changed.
*/
void userContainer_update(struct User* user,char* original_email);