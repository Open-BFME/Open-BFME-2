// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /MD
// ??0Rva005C44A3@@QAE@ABV?$StringBase@D@@@Z @0x005C44A3 32B.
// The body first delegates to Rva004FA830's matched string constructor,
// clears two dwords, then installs the vtable at 0x008745D4.
#include "ascii_string.h"

class Rva004FA830
{
public:
	virtual ~Rva004FA830();
	Rva004FA830(const StringBase<char> &);

private:
	StringBase<char> m_s;
};

extern const char g_00C745D4[];

class Rva005C44A3 : public Rva004FA830
{
public:
	Rva005C44A3(const StringBase<char> &);

private:
	int m_08;
	int m_0c;
};

Rva005C44A3::Rva005C44A3(const StringBase<char> &value)
	: Rva004FA830(value), m_08(0), m_0c(0)
{
	*(const char **)this = g_00C745D4;
}
