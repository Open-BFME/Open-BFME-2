// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva001EB6A5@Rva001EB6A5@@QAE_NPAURva001EB6A5Out@@@Z, retail 0x001EB6A5, 89 bytes.
// Finish from stash 0.93 (eax edx swap for add base idx): copies m_C0 to out+8,
// add is (m_C3==0 and m_C0!=0) ? 1 : 0, idx is base m_0C plus add via rowed
// rva001EB3A6 returning BfmeAssignRecord36, null gives false else out strings
// from rec+0 and rec+0xC via StringBase set and true. Ret 4. Uses shared
// ascii_string header so assignments inline to rowed set 0x000366F0. Evidence:
// prev Rva001EB435Check layout, caller 0x001EB74B unblocks 0x001EB74B.
#include "ascii_string.h"

struct BfmeAssignRecord36
{
	AsciiString s;
	int a[8];
};

class Rva001EB3A6
{
public:
	BfmeAssignRecord36 *rva001EB3A6(int i);
};

struct Rva001EB6A5Out
{
	AsciiString m_s0;
	AsciiString m_s1;
	unsigned char m_flag;
};

class Rva001EB6A5
{
public:
	bool rva001EB6A5(Rva001EB6A5Out *out);
private:
	char m_00[4];
	Rva001EB3A6 *m_04;
	char m_08[4];
	int m_0C;
	char m_10[0xB0];
	unsigned char m_C0;
	char m_pad[2];
	unsigned char m_C3;
};

bool Rva001EB6A5::rva001EB6A5(Rva001EB6A5Out *out)
{
	unsigned char *pC0 = &m_C0;
	out->m_flag = *pC0;
	int add;
	if (m_C3 == 0 && *pC0 != 0)
		add = 1;
	else
		add = 0;
	BfmeAssignRecord36 *rec = m_04->rva001EB3A6(m_0C + add);
	if (rec == 0)
		return false;
	out->m_s0 = rec->s;
	out->m_s1 = *(AsciiString *)((char *)rec + 0xc);
	return true;
}
