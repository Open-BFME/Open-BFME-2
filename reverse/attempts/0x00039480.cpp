// ?SimpleMatch@Debug@@SA_NPBD0@Z
// partial score=0.7 date=2026-09-10
// cl: /O2 /G6 /Oy- /DNDEBUG /MD
//
// Debug::SimpleMatch, retail 0x00039480. Recursive '*' glob; uppercase
// letters in the string are folded by adding 32 before the compare.

class Debug
{
public:
	static bool SimpleMatch(const char *str, const char *pattern);
};

bool Debug::SimpleMatch(const char *str, const char *pattern)
{
	const char *s = str;
	const char *p = pattern;
	for (;;)
	{
		char c = *s;
		char q = *p;
		if (c == 0)
		{
			if (q == '*')
				goto star;
			return c == q;
		}
		if (q == 0)
			return c == q;
		if (q == '*')
			goto star;
		if (c >= 'A' && c <= 'Z')
		{
			++s;
			++p;
			if (c + 32 != q)
				return false;
		}
		else
		{
			++s;
			++p;
			if (c != q)
				return false;
		}
	}

star:
	++p;
	if (*s != 0)
	{
		for (;;)
		{
			if (SimpleMatch(s, p))
				return true;
			++s;
			if (*s == 0)
				break;
		}
	}
	return *s == *p;
}
