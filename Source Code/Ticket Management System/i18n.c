#include "i18n.h"
#include <stdbool.h>
#include <stdlib.h>
#include <Windows.h>
#include <io.h> // for _setmode
#include <fcntl.h> // for _setmode

wchar_t** locales[I18N_LOCALE_COUNT];
wchar_t* english[I18N_STRING_COUNT];
wchar_t* hebrew[I18N_STRING_COUNT];

enum i18n_Locale current_locale = I18N_LOCALE_ENGLISH;

bool isRtl(enum i18n_Locale locale)
{
	return locale == I18N_LOCALE_HEBREW;
}

void setFont(wchar_t* font_name)
{
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof font;
	font.nFont = 0;
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = 20;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	wcscpy(font.FaceName, font_name);
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
}

wchar_t* reverseString(wchar_t* src_str)
{
	unsigned int len = wcslen(src_str);
	wchar_t* context;
	wchar_t* src_cpy  = malloc(sizeof(wchar_t) * (len + 1u));
	if (src_cpy == NULL)
	{
		return src_str;
	}
	wcscpy(src_cpy, src_str);
	wchar_t* reversed = malloc(sizeof(wchar_t) * (len + 1u));
	if (reversed == NULL)
	{
		free(src_cpy);
		return src_str;
	}

	unsigned int i = 0;
	wchar_t* token = wcstok(src_cpy, L"\n", &context);
	while (token != NULL)
	{
		unsigned int token_len = wcslen(token);
		for (unsigned int j = 0; j < token_len; ++j)
		{
			reversed[i] = token[token_len - 1 - j];
			if (reversed[i] == L'(')
				reversed[i] = L')';
			else if (reversed[i] == L')')
				reversed[i] = L'(';
			else if (reversed[i] == L'[')
				reversed[i] = L']';
			else if (reversed[i] == L']')
				reversed[i] = L'[';
			else if (reversed[i] == L'{')
				reversed[i] = L'}';
			else if (reversed[i] == L'}')
				reversed[i] = L'{';
			++i;
		}
		reversed[i++] = L'\n';

		token = wcstok(NULL, L"\n", &context);
	}
	reversed[len] = L'\0';
	
	wprintf(L"%s\n", reversed);
	free(src_cpy);
	return reversed;
}

void i18n_init()
{
	_setmode(_fileno(stdout), _O_U16TEXT); // Set cmd.exe to allow unicode
	setFont(L"Miriam Fixed"); // We're changing the font because the default cmd.exe font doesn't support Hebrew

	english[I18N_STRING_BROWSE_TICKETS] = L"Browse Tickets";
	hebrew [I18N_STRING_BROWSE_TICKETS] = L"עיון בקריאות";
	english[I18N_STRING_TICKETS_THAT_ANSWER_CRITERIA] = L"Tickets that answer the criteria";
	hebrew [I18N_STRING_TICKETS_THAT_ANSWER_CRITERIA] = L"קריאות שעונות לקריטריונים";
	english[I18N_STRING_TICKETS_FILTER_QUESTION] = L"Would you like to search/filter/sort the results?";
	hebrew [I18N_STRING_TICKETS_FILTER_QUESTION] = L"התרצה לחפש/לסנן/למיין את התוצאות?";
	english[I18N_STRING_FILTER_BY_STATUS] = L"Filter by status";
	hebrew [I18N_STRING_FILTER_BY_STATUS] = L"סינון לפי סטאטוס";
	english[I18N_STRING_FILTER_BY_TIER] = L"Filter by tier";
	hebrew [I18N_STRING_FILTER_BY_TIER] = L"סינון לפי רמה";
	english[I18N_STRING_FILTER_BY_TYPE] = L"Filter by type";
	hebrew [I18N_STRING_FILTER_BY_TYPE] = L"סינון לפי טיפוס";
	english[I18N_STRING_FILTER_BY_STAKEHOLDERS] = L"Filter by stakeholders";
	hebrew [I18N_STRING_FILTER_BY_STAKEHOLDERS] = L"סינון לפי בעלי עניין";
	english[I18N_STRING_SEARCH_BY_CUSTOMER_EMAIL] = L"Search by customer email";
	hebrew [I18N_STRING_SEARCH_BY_CUSTOMER_EMAIL] = L"חיפוש לפי דוא\"ל לקוח";
	english[I18N_STRING_SEARCH_BY_TAGS] = L"Search by tags";
	hebrew [I18N_STRING_SEARCH_BY_TAGS] = L"חיפוש לפי תגיות";
	english[I18N_STRING_SORT_BY_TITLE] = L"Sort by title";
	hebrew [I18N_STRING_SORT_BY_TITLE] = L"מיון לפי כותרת";
	english[I18N_STRING_GO_BACK] = L"Press Q to go back.";
	hebrew [I18N_STRING_GO_BACK] = L"לחץ Q לחזרה.";
	english[I18N_STRING_QUIT] = L"Press Q quit.";
	hebrew [I18N_STRING_QUIT] = L"לחץ Q ליציאה.";
	english[I18N_STRING_PLEASE_INPUT_STATUS] = L"Please input status.";
	hebrew [I18N_STRING_PLEASE_INPUT_STATUS] = L"הזן סטאטוס.";
	english[I18N_STRING_INVALID_INPUT] = L"Input is invalid. Try again.";
	hebrew [I18N_STRING_INVALID_INPUT] = L"הקלט אינו תקין. נסה שוב.";
	english[I18N_STRING_NO_TICKETS] = L"No tickets in the system.";
	hebrew [I18N_STRING_NO_TICKETS] = L"אין קריאות במערכת.";
	english[I18N_STRING_SUPPORTGIVER_WELCOME] = L"Welcome\nWhat would you like to do?";
	hebrew [I18N_STRING_SUPPORTGIVER_WELCOME] = L"ברוכים הבאים\nמה תרצו לעשות?";
	english[I18N_STRING_SUPPORTGIVER_OPENTICKET] = L"Open Ticket";
	hebrew [I18N_STRING_SUPPORTGIVER_OPENTICKET] = L"פתיחת קריאה";
	english[I18N_STRING_SUPPORTGIVER_VIEWTICKET] = L"View / Update Ticket";
	hebrew [I18N_STRING_SUPPORTGIVER_VIEWTICKET] = L"קרא / עדכן קריאה";
	english[I18N_STRING_SUPPORTGIVER_BROWSETICKETS] = L"Browse Tickets";
	hebrew [I18N_STRING_SUPPORTGIVER_BROWSETICKETS] = L"עיין בקריאות";
	english[I18N_STRING_SUPPORTGIVER_CREATEUSER] = L"Create User";
	hebrew [I18N_STRING_SUPPORTGIVER_CREATEUSER] = L"צור משתמש";
	english[I18N_STRING_LOG_OUT] = L"Log Out";
	hebrew [I18N_STRING_LOG_OUT] = L"יציאה מהמערכת";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT] = L"Contact Support";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT] = L"צור קשר עם תמיכה";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_DESCRIPTION] = L"Please describe what happened.";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_DESCRIPTION] = L"תאר בבקשה את מה שקרה.";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_TITLE] = L"Please give a short title to the incident.";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_TITLE] = L"הזן בבקשה כותרת קצרה לתקרית.";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_TYPE] = L"Please list the type(s) related to this incident.";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_TYPE] = L"הזן בבקשה טיפוסים הקשורים לתקרית.";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS] = L"Support Call Saved";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS] = L"קריאת השירות נשמרה";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_ELABORATION] = L"Your support call was saved in the system.";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_ELABORATION] = L"קריאת השירות שלך נשמרה במערכת.";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_TICKETID] = L"Your ticket ID is:";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_TICKETID] = L"מזהה הקריאה שלך הוא:";
	english[I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_PLEASESAVE] = L"Please save this ID for future reference.";
	hebrew [I18N_STRING_CUSTOMER_CONTACTSUPPORT_SUCCESS_PLEASESAVE] = L"שמור נא את מזהה זה לבירורים נוספים.";
	english[I18N_STRING_CUSTOMER_VIEWTICKET] = L"View Support Call Status";
	hebrew [I18N_STRING_CUSTOMER_VIEWTICKET] = L"צפה בסטאטוס קריאת שירות";
	english[I18N_STRING_CUSTOMER_VIEWTICKET_DESCRIPTION] = L"Please input the ticket ID given to you when contacting support.\nAlternatively, find the ticket ID by going back and selecting 'List My Support Calls'.";
	hebrew [I18N_STRING_CUSTOMER_VIEWTICKET_DESCRIPTION] = L"הזן בבקשה את מזהה הקריאה שקיבלת כשיצרת קשר עם התמיכה.\nאלטרנטיבית, מצא את מזהה הקריאה על ידי חזרה ובחירת האפשרות 'רשימת הקריאות שלי'.";
	english[I18N_STRING_TICKET_ID] = L"Ticket ID";
	hebrew [I18N_STRING_TICKET_ID] = L"מזהה קריאה";
	english[I18N_STRING_TICKET_TITLE] = L"Title";
	hebrew [I18N_STRING_TICKET_TITLE] = L"כותרת";
	english[I18N_STRING_TICKET_DATE] = L"Date opened";
	hebrew [I18N_STRING_TICKET_DATE] = L"תאריך פתיחה";
	english[I18N_STRING_TICKET_STATUS] = L"Status";
	hebrew [I18N_STRING_TICKET_STATUS] = L"סטאטוס";
	english[I18N_STRING_TICKET_TIER] = L"Tier";
	hebrew [I18N_STRING_TICKET_TIER] = L"רמה";
	english[I18N_STRING_TICKET_TYPE] = L"Type";
	hebrew [I18N_STRING_TICKET_TYPE] = L"טיפוס";
	english[I18N_STRING_TICKET_SEVERITY] = L"Severity";
	hebrew [I18N_STRING_TICKET_SEVERITY] = L"חומרה";
	english[I18N_STRING_TICKET_DESCRIPTION] = L"Description";
	hebrew [I18N_STRING_TICKET_DESCRIPTION] = L"תיאור";
	english[I18N_STRING_TICKET_NOTES] = L"Notes";
	hebrew [I18N_STRING_TICKET_NOTES] = L"הערות";
	english[I18N_STRING_NOTE_DATE] = L"Date";
	hebrew [I18N_STRING_NOTE_DATE] = L"תאריך";
	english[I18N_STRING_NOTE_AUTHOR] = L"Author";
	hebrew [I18N_STRING_NOTE_AUTHOR] = L"מחבר";
	english[I18N_STRING_NO_TICKET_BY_ID] = L"Could not find ticket with this ID.";
	hebrew [I18N_STRING_NO_TICKET_BY_ID] = L"כישלון במציאת קריאה עם מזהה זה.";
	english[I18N_STRING_CUSTOMER_WELCOME] = L"Welcome\nWhat would you like to do?";
	hebrew [I18N_STRING_CUSTOMER_WELCOME] = L"ברוכים הבאים\nמה תרצה לעשות?";
	english[I18N_STRING_CUSTOMER_LISTTICKETS] = L"List My Support Calls";
	hebrew [I18N_STRING_CUSTOMER_LISTTICKETS] = L"רשימת הקריות שלי";
	english[I18N_STRING_CUSTOMER_UPDATECONTACTINFO] = L"Update Contact Information";
	hebrew [I18N_STRING_CUSTOMER_UPDATECONTACTINFO] = L"עדכון פרטי התקשרות";
	english[I18N_STRING_CUSTOMER_FAQ] = L"FAQ / Q&A";
	hebrew [I18N_STRING_CUSTOMER_FAQ] = L"שאלות נפוצות ותשובות";
	english[I18N_STRING_AUTH_WELCOME] = L"Welcome to the system\n=====================\nPlease log in:\n(Don't have a user? Contact HR)";
	hebrew [I18N_STRING_AUTH_WELCOME] = L"ברוכים הבאים למערכת\n=====================\nאנא בצע כניסה:\n(לא רשום במערכת? צור קשר עם כ\"א)";
	english[I18N_STRING_AUTH_EMAIL] = L"E-Mail: ";
	hebrew [I18N_STRING_AUTH_EMAIL] = L"דוא\"ל: ";
	english[I18N_STRING_AUTH_PASSWORD] = L"Password: ";
	hebrew [I18N_STRING_AUTH_PASSWORD] = L"סיסמה: ";
	english[I18N_STRING_AUTH_LOGIN] = L"Log In";
	hebrew [I18N_STRING_AUTH_LOGIN] = L"כניסה";
	english[I18N_STRING_AUTH_INVALID] = L"Invalid E-Mail or Password.";
	hebrew [I18N_STRING_AUTH_INVALID] = L"דוא\"ל או סיסמה שגויים.";

	locales[I18N_LOCALE_ENGLISH] = english;
	locales[I18N_LOCALE_HEBREW] = hebrew;
	
	for (unsigned int i = 0; i < I18N_LOCALE_COUNT; ++i)
	{
		if (isRtl(i))
		{
			for (unsigned int j = 0; j < I18N_STRING_COUNT; ++j)
			{
				wchar_t* reversed_str = reverseString(locales[i][j]);
				if (reversed_str != NULL)
				{
					locales[i][j] = reversed_str;
				}
			}
		}
	}
}

// TODO: Write a deinit function

enum i18n_Locale i18n_getCurrentLocale()
{
	return current_locale;
}

void i18n_setCurrentLocale(enum i18n_Locale locale)
{
	current_locale = locale;
}

wchar_t* i18n_getString(enum i18n_StringId id, enum i18n_Locale locale)
{
	if (id >= 0 && id < I18N_STRING_COUNT && locale >= 0 && (locale < I18N_LOCALE_COUNT || locale == I18N_LOCALE_CURRENT))
	{
		if (locale == I18N_LOCALE_CURRENT)
		{
			locale = current_locale;
		}
		return locales[locale][id];
	}
	return L"";
}
