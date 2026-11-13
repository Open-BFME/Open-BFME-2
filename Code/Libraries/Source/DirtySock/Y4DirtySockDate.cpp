// cl: /Ob1
/* EA DirtySock calendar date, ported verbatim from BFME1
 * Y4DirtySockDate.cpp. Retail setDay 0x0066B920 (93B Ghidra, 120B BFME1).
 *
 * Separate TU because it is optimised (/Ob1, no /GZ); the socket and text
 * units are /Od /GZ and cannot share flags with it.
 */

bool __fastcall Rva007FF3F0IsLeapYear(int year);

#include "../../../GameEngine/Include/Common/Rva007FF700Date.h"

bool __fastcall Rva007FF3F0IsLeapYear(int year)
{
	if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
		return true;
	else
		return false;
}

Rva007FF700Date::Rva007FF700Date()
{
	m_month = 1;
	m_year = 1900;
	setDay(1);
}

int Rva007FF700Date::setDay(int day)
{
	int dayLimit;

	switch (m_month)
	{
	case 2:
		dayLimit = 28 + (Rva007FF3F0IsLeapYear(m_year) ? 1 : 0);
		break;

	case 4:
	case 6:
	case 9:
	case 11:
		dayLimit = 30;
		break;

	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		dayLimit = 31;
		break;

	default:
		return -1;
	}

	if (day <= 0 || day > dayLimit)
		return -2;

	m_day = day;
	return 0;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0Rva007FF700FeslString@@QAE@XZ=??0Rva007FF700Date@@QAE@XZ")
