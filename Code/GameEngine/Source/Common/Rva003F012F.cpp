// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD
// ?rva003F012F@Rva003F012F@@QAEHXZ @0x003F012F 90B via vec at +0x60 stride 0x18 plus AsciiString at +4 plus lookup 0x00210390 via +0x130
// Evidence: callees rowed rva00210390 0x00210390; callers 0x003F08F1 plus thunk 0x003F0DC6; unblocks 0x003F08EE; offsets +0x60 start +0x64 finish +0x130 holder +4 str +8 result.
#include "ascii_string.h"

class Rva00210390
{
public:
	void *rva00210390(const AsciiString *s);
};

struct Entry003F012F
{
	char m_pad00[4];
	AsciiString m_str04;
	int m_result08;
	char m_pad0C[0x18 - 0x0C];
};

struct Vec003F012F
{
	Entry003F012F *m_start;
	Entry003F012F *m_finish;
	unsigned size() const { return ((char *)m_finish - (char *)m_start) / 0x18; }
};

class Rva003F012F
{
public:
	void rva003F012F();
private:
	char m_pad00[0x60];
	Vec003F012F m_vec60;
	char m_pad68[0x130 - 0x68];
	Rva00210390 *m_holder130;
};

void Rva003F012F::rva003F012F()
{
	unsigned idx = 0;
	if (m_vec60.size() <= 0u)
		return;
	do {
		void *res = m_holder130->rva00210390(&m_vec60.m_start[idx].m_str04);
		int val;
		if (res != 0)
			val = *(int *)((char *)res + 0x12c);
		else
			val = -1;
		m_vec60.m_start[idx].m_result08 = val;
		++idx;
	} while (idx < m_vec60.size());
}
