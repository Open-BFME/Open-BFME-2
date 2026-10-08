// ?rva0040CC3C@Rva0040CC3C@@QAE_NPAVRva00376A62@@@Z
// partial score=0.93 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva0040CC3C@Rva0040CC3C@@QAE_NPAVRva00376A62@@@Z @0x0040CC3C 83B: thiscall bool scanning int array at +4C..+50 via base get then Rva00376A62 contains. Evidence: unlock lane; rowed get 0x0040CBB8 and contains 0x00376A62; callers 0x003EA94E 0x0040ECAA unclaimed; prev Rva0040CC1B next Rva0040F454Cmp same flags.
#include "ascii_string.h"

struct Rva0040CB3AEntry
{
	int first;
	int second;
};

class Rva0040CB3AIndexedField
{
public:
	int find(int key) const throw();
	int get(int key) const throw();
private:
	char m_pad[0x40];
	Rva0040CB3AEntry *m_begin;
	Rva0040CB3AEntry *m_end;
};

class Rva00376A62
{
	unsigned char m_pad[8];
	StringBase<char> *m_begin;
	StringBase<char> *m_end;
	void *m_end_of_storage;
	StringBase<char> m_14;
public:
	bool rva00376A62(const StringBase<char> &val) throw();
};

class Rva0040CC3C : public Rva0040CB3AIndexedField
{
	char m_pad48[4];
	const int *m_begin2;
	const int *m_end2;
public:
	bool rva0040CC3C(Rva00376A62 *arg);
};

bool Rva0040CC3C::rva0040CC3C(Rva00376A62 *arg)
{
	const int *cur = m_begin2;
	const int *end = m_end2;
	int diff = *(int *)((char *)arg + 0xC) - *(int *)((char *)arg + 8);
	if ((diff & 0xFFFFFFFC) == 0)
		return false;
	for (; cur != end; ++cur)
	{
		int v = get(*cur);
		if (v != 0)
		{
			if (arg->rva00376A62(*(const StringBase<char> *)(v + 4)))
				return true;
		}
	}
	return false;
}
