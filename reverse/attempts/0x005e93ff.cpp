// ??0Rva005E92F7@@QAE@IPAX@Z
// partial score=0.89 date=2026-10-11
// cl: /Ob2 /EHsc /MD /Ireference/shims/bfme2_ascii
// ??1Rva005E92F7@@UAE@XZ retail 0x005E92F7 60B
// MI dtor second base at +8 via pin 0x005E12D1 plus base vtable restore to g_00BC6F20.
// Layout from twin 0x005E91A9 60B and 0x005CC37C 60B plus deleting wrapper 0x005E948B.
// Evidence: EH_prolog plus two vptr stores C78030/C78010 then member-base call then BC6F20.
// Pin QAE refuted: MI with virtual second base forces virtual dtor UAE same bytes.

//
// ??0Rva005E92F7@@QAE@IPAX@Z retail 0x005E93FF (140B, ret 8; pinned for its
// caller as ??0Rva005E93FF): the primary's own table 0x00C7A630 (over the
// BC6F20 root that the destructor restores) with +4 cleared, the +8 holder
// base (rowed 0x005E1680) built from the first argument, a temporary
// "button" string and the record's first word, the 12-byte record copied
// to +0x1C, the derived tables C78030/C78010, then the holder's image
// (rowed 0x005E1158) from the record's third word through 0x005E936A
// (unrowed, address-named pin).
#include "ascii_string.h"

class Image;
const Image *Rva005E936AGet(int id);

class Rva005E12D1
{
public:
	Rva005E12D1(void *owner, const AsciiString &kind, void *id);
	virtual ~Rva005E12D1();
	void setImage(const Image *image);
};
class Rva005E1158
{
public:
	void rva005E1158(const Image *image);
};

class Rva005E92F7Base
{
public:
	Rva005E92F7Base() : m_04(0) {}
	virtual ~Rva005E92F7Base() {}
protected:
	int m_04;
};

class Rva005E92F7Mid : public Rva005E92F7Base
{
public:
	virtual ~Rva005E92F7Mid() {}
};

struct Rva005E92F7Record
{
	int m_id;
	int m_04;
	int m_image;
};

class Rva005E92F7 : public Rva005E92F7Mid, public Rva005E12D1
{
public:
	Rva005E92F7(unsigned int owner, void *record);
	virtual ~Rva005E92F7();
private:
	char m_pad0C[0x1C - 0x0C];
	Rva005E92F7Record m_record;	// +0x1C
};

inline void Rva005E12D1::setImage(const Image *image)
{
	reinterpret_cast<Rva005E1158 *>(this)->rva005E1158(image);
}

Rva005E92F7::Rva005E92F7(unsigned int owner, void *record)
	: Rva005E12D1((void *)owner, AsciiString("button"), *(void **)record)
{
	m_record = *(Rva005E92F7Record *)record;
	setImage(Rva005E936AGet(m_record.m_image));
}

Rva005E92F7::~Rva005E92F7()
{
}
