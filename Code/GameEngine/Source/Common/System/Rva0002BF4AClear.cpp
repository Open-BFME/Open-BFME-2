// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc
// ?rva0002BF4A@Rva0002BF4A@@QAEXXZ @0x0002BF4A 66B: thiscall clear with None plus empty.
// Evidence: ret no args; lea ecx [esi+0x838] to Rva00601BBCHelper::rva00601A8D pin; AsciiString+0x4 set None row; g_00DDF5B4 set TheEmptyString row; ints +0x8 +0xc +0x10 zeroed; byte +0x430 false; g_00DDF57C zeroed; callers are Catch funclets.
#include "ascii_string.h"
class Rva00601BBCHelper
{
public:
	void rva00601A8D();
};
extern AsciiString g_00DDF5B4;
extern int g_00DDF57C;
class Rva0002BF4A
{
public:
	void rva0002BF4A();
private:
	char m_pad00[4];
	AsciiString m_04;
	int m_08;
	int m_0c;
	int m_10;
	char m_pad14[0x430 - 0x14];
	bool m_430;
	char m_pad431[0x838 - 0x431];
	Rva00601BBCHelper m_838;
};

void Rva0002BF4A::rva0002BF4A()
{
	m_838.rva00601A8D();
	((StringBase<char> *)&m_04)->set("None");
	((StringBase<char> *)&g_00DDF5B4)->set(*(const StringBase<char> *)&AsciiString::TheEmptyString);
	m_08 = 0;
	m_0c = 0;
	m_10 = 0;
	m_430 = false;
	g_00DDF57C = 0;
}
