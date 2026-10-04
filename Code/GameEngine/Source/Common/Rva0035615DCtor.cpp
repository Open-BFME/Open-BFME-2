// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /MD /EHsc
// ??0Rva0035615D@@QAE@ABVAsciiString@@ABVRva0036CA00Str@@1_N@Z @0x0035615D 97B. Unlock lane: ctor storing vtable 0x00814EBC, base Rva00490470 then StringBase at +0x10 plus two Rva0036CA00Str at +0x14/+0x18 plus ints 1/1 and bool at +0x24; callers at 0x0023DE2C etc; unblocks 0x0023DD48.
#include "ascii_string.h"

class Rva00490470
{
public:
	Rva00490470();
	virtual ~Rva00490470();
private:
	char m_pad[0x0C];
};

class Rva0036CA00Str
{
	void *m_item;
public:
	__declspec(nothrow) Rva0036CA00Str(const Rva0036CA00Str &other);
	~Rva0036CA00Str();
};

class Rva0035615D : public Rva00490470
{
public:
	Rva0035615D(const AsciiString &a, const Rva0036CA00Str &b, const Rva0036CA00Str &c, bool d);
	virtual ~Rva0035615D();
private:
	AsciiString m_s10;
	Rva0036CA00Str m_s14;
	Rva0036CA00Str m_s18;
	int m_1c;
	int m_20;
	bool m_24;
};

Rva0035615D::Rva0035615D(const AsciiString &a, const Rva0036CA00Str &b, const Rva0036CA00Str &c, bool d)
	: m_s10(a), m_s14(b), m_s18(c), m_1c(1), m_20(1), m_24(d)
{
}

// ??1Rva0035615D@@UAE@XZ present-unmatched
Rva0035615D::~Rva0035615D()
{
}
