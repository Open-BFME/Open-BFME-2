// cl: /Ob1
/* EA DirtySock date parser, ported verbatim from BFME1
 * Y4DirtySockDateParse.c. Retail 0x0066BA00 (452B).
 *
 * Format "%3s-%d-%d", English month names JAN..DEC, year below 1900 returns
 * -3, unknown month -1, otherwise setDay. Own TU so setDay stays a call.
 */

#include <stdio.h>
#include <string.h>

#include "../../../GameEngine/Include/Common/Rva007FF700Date.h"

int Rva007FF700Date::parse(const char *text)
{
	char month[4];
	int day;
	int year;
	int iMonth;

	month[0] = 0;
	sscanf(text, "%3s-%d-%d", month, &day, &year);

	if (strcmp(month, "JAN") == 0)
		iMonth = 1;
	else if (strcmp(month, "FEB") == 0)
		iMonth = 2;
	else if (strcmp(month, "MAR") == 0)
		iMonth = 3;
	else if (strcmp(month, "APR") == 0)
		iMonth = 4;
	else if (strcmp(month, "MAY") == 0)
		iMonth = 5;
	else if (strcmp(month, "JUN") == 0)
		iMonth = 6;
	else if (strcmp(month, "JUL") == 0)
		iMonth = 7;
	else if (strcmp(month, "AUG") == 0)
		iMonth = 8;
	else if (strcmp(month, "SEP") == 0)
		iMonth = 9;
	else if (strcmp(month, "OCT") == 0)
		iMonth = 10;
	else if (strcmp(month, "NOV") == 0)
		iMonth = 11;
	else if (strcmp(month, "DEC") == 0)
		iMonth = 12;
	else
		return -1;

	m_month = iMonth;
	if (year >= 1900)
	{
		m_year = year;
		return setDay(day);
	}
	return -3;
}
