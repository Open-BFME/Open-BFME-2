// cl: /DNDEBUG /MD /Ob2

bool __stdcall isLeapYear(int year)
{
	bool result = false;
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
			return true;
		result = year % 400 == 0;
	}
	return result;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?dateIsYearLeap@AptDate@@QAE_NH@Z=?isLeapYear@@YG_NH@Z")
