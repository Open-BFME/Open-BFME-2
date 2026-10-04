// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /G7 /EHsc
// ?rva00351570@Rva00351570@@QAEXABURva00351570Src@@@Z, RVA 0x00351570, 222 bytes.
// Copy from template/init struct to instance. Evidence: dword copies +0/+4,
// 12B via movsd x3 at +8, +0x14/+0x18 via [ptr+0x74] or 0, strings at
// +0x1c/+0x20 via set from [[src+0x1c]+0x30]+0x10/+0x14 or empty or release,
// vector at +0x24 via rowed Rva0035149F 0x0035149F from src+0x20, dwords
// +0x30..+0x3c, Rva003427DD at +0x40 via rowed 0x003427DD from src+0x3c,
// far dwords +0xbc/+0xc0 from src+0xb8/+0xbc. Callers 0x00267B9A 0x0036BCA9.
#include "ascii_string.h"
struct BfmeVec12
{
	float x, y, z;
};
class Rva0035149F
{
public:
	BfmeVec12 *m_start;
	BfmeVec12 *m_finish;
	BfmeVec12 *m_end;
	Rva0035149F &rva0035149F(const Rva0035149F &other);
};
class Rva003427DD
{
public:
	char m_data[0x7C];
	Rva003427DD &operator=(const Rva003427DD &src);
};
struct Rva00351570_Has74
{
	char m_pad[0x74];
	int m_74;
};
struct Rva00351570_MidB
{
	char m_pad[0x10];
	AsciiString m_10;
	AsciiString m_14;
};
struct Rva00351570_MidA
{
	char m_pad[0x30];
	Rva00351570_MidB *m_30;
};
struct Rva00351570Src
{
	int m_00;
	int m_04;
	BfmeVec12 m_08;
	Rva00351570_Has74 *m_14;
	Rva00351570_Has74 *m_18;
	Rva00351570_MidA *m_1C;
	Rva0035149F m_20;
	int m_2C;
	int m_30;
	int m_34;
	int m_38;
	Rva003427DD m_3C;
	int m_B8;
	int m_BC;
};
class Rva00351570
{
public:
	int m_00;
	int m_04;
	BfmeVec12 m_08;
	int m_14;
	int m_18;
	AsciiString m_1C;
	AsciiString m_20;
	Rva0035149F m_24;
	int m_30;
	int m_34;
	int m_38;
	int m_3C;
	Rva003427DD m_40;
	int m_BC;
	int m_C0;
	void rva00351570(const Rva00351570Src &src);
};
void Rva00351570::rva00351570(const Rva00351570Src &src)
{
	m_00 = src.m_00;
	m_04 = src.m_04;
	m_08 = src.m_08;
	m_14 = src.m_14 ? src.m_14->m_74 : 0;
	m_18 = src.m_18 ? src.m_18->m_74 : 0;
	if (src.m_1C != 0)
	{
		Rva00351570_MidB *b0 = src.m_1C->m_30;
		((StringBase<char> &)m_1C).set(!b0 ? (const StringBase<char> &)AsciiString::TheEmptyString : (const StringBase<char> &)b0->m_10);
		Rva00351570_MidB *b1 = src.m_1C->m_30;
		((StringBase<char> &)m_20).set(!b1 ? (const StringBase<char> &)AsciiString::TheEmptyString : (const StringBase<char> &)b1->m_14);
	}
	else
	{
		((StringBase<char> &)m_1C).clear();
		((StringBase<char> &)m_20).clear();
	}
	m_24.rva0035149F(src.m_20);
	m_30 = src.m_2C;
	m_34 = src.m_30;
	m_38 = src.m_34;
	m_3C = src.m_38;
	m_40 = src.m_3C;
	m_BC = src.m_B8;
	m_C0 = src.m_BC;
}
