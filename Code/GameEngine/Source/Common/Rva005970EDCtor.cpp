// cl: /Ireference/shims/bfme2_ascii /MD
//
// ??0Rva005970ED@@QAE@XZ 33B @0x005970ED: ctor over base Rva0059734B ctor
// at 0x00597331, then sets dword at +0x3C to -1 (retail `or [m],-1` /O1
// idiom), byte at +0x34 and dwords at +0x38/+0x40 to 0, and installs vtable
// 0x00870B88. Evidence: base call plus or-minus-one plus zero stores plus
// vptr store, callers at 0x004EAF8E 0x004EB21B 0x00597CFB. Base layouts
// from landed siblings Rva005DAAB6Slot15.cpp and Rva0059734BCtor.cpp;
// owner identity unproven so honest address name.

#include "ascii_string.h"

enum ObjectID
{
	INVALID_ID = 0
};

class Rva0055B0CC
{
public:
	Rva0055B0CC();
	virtual ~Rva0055B0CC();
private:
	float m_04;
	ObjectID m_08;
	AsciiString m_0C;
	unsigned int m_10;
	int m_pad14;
	float m_18;
	int m_pad1C;
	bool m_20;
	bool m_21;
	ObjectID m_24;
	bool m_28;
};

class Rva0059734B : public Rva0055B0CC
{
public:
	Rva0059734B();
	virtual ~Rva0059734B();
private:
	int m_2C;
	int m_30;
};

class Rva0059710EHelper
{
public:
	virtual int f0(int x);
};

class Rva005970ED : public Rva0059734B
{
public:
	Rva005970ED();
	void rva0059710E(int x);
private:
	bool m_34;
	Rva0059710EHelper *m_38;
	int m_3C;
	int m_40;
};

Rva005970ED::Rva005970ED()
	: m_34(false)
	, m_38(0)
	, m_3C(-1)
	, m_40(0)
{
}

void Rva005970ED::rva0059710E(int x)
{
	m_40 = m_38->f0(x);
}
