// cl: /Ireference/shims/bfme2_ascii /MD
//
// ??0AIUpgrade@@QAE@XZ 26B @0x00597331: ctor for AIUpgrade over base
// Rva0055B0CC ctor at 0x0055B048, then zeroes dwords at +0x2C and +0x30
// (retail `and [m],0` /O1 idiom) and installs vtable 0x00870BD0.
// Evidence: base call plus two and-zero stores plus vptr store, callers at
// 0x005970F0 and 0x005DAFC8 (the latter its Rva005DAFD7 derived ctor).
// Base layout verbatim from landed sibling
// Code/GameEngine/Source/Common/Rva005DAAB6Slot15.cpp; dtor row
// ??1AIUpgrade@@UAE@XZ at 0x0059734B proves the class.

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

class AIUpgrade : public Rva0055B0CC
{
public:
	AIUpgrade();
	virtual ~AIUpgrade();
private:
	int m_2C;
	int m_30;
};

AIUpgrade::AIUpgrade()
	: m_2C(0)
	, m_30(0)
{
}
