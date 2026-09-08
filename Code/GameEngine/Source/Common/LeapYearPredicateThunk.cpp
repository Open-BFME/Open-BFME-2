// cl: /DNDEBUG /MD /O2 /Ob2

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
