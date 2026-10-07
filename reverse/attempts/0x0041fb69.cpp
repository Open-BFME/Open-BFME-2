// ?rva0041FB69@Rva0041FB69@@QAEHPBD@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?rva0041FB69@Rva0041FB69@@QAEHPBD@Z, retail 0x0041FB69 (206B).
// Ref table slot 0x0083B910 neighbours deleting-dtor and next slot; callers none.
// Evidence: AsciiString temps, hash-table find at +4, dot-split fallback, int at node+8.

#include "ascii_string.h"
#include <string.h>

__declspec(dllimport) char *__cdecl strchr(const char *s, int c);

class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key) throw();
};

class Rva0041FB69
{
public:
	int rva0041FB69(const char *arg);
private:
	char m_pad00[0x4];
	Rva00056F61 m_04;
};

int Rva0041FB69::rva0041FB69(const char *arg)
{
	if (arg == 0)
		return 1;
	void *found;
	{
		AsciiString tmp(arg);
		found = m_04.rva00056F61(&tmp);
	}
	if (found != 0)
		return *(int *)((char *)found + 8);
	char *dot = strchr((char *)arg, '.');
	if (dot != 0)
	{
		AsciiString prefix(arg, 0, (int)(dot - arg));
		void *found2;
		{
			AsciiString tmp2(prefix.str());
			found2 = m_04.rva00056F61(&tmp2);
		}
		if (found2 != 0)
			return *(int *)((char *)found2 + 8);
		return 1;
	}
	else
		return 1;
}
