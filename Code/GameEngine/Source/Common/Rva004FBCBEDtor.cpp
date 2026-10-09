// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ??1Rva004FBCBE@@UAE@XZ 0x004FBCBE 96B: virtual dtor with two wide strings at
// +8/+0x0C plus flag at +0x25 gating a pinned target call through global
// (int)AptStrategicMessageBox::s_instance (row says int but code uses its value as the receiver, noted).
// Vtable entry 0x00C634E4 then base 0x00BC6F20 with no base call; callers are
// the deleting dtor at 0x004FBD1E and a tail-jmp from ??1Rva004FF2C0. Boundary
// from int3 padding; byte verification decides.
#include "unicode_string.h"

class Rva0054CBEFTarget
{
public:
	void method(int arg);
};

class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend class Rva004FBCBE;};

extern const void *const g_00BC6F20[];

class __declspec(novtable) Rva004FBCBEBase
{
public:
	virtual ~Rva004FBCBEBase();
};

// ??1Rva004FBCBEBase@@UAE@XZ present-unmatched
inline Rva004FBCBEBase::~Rva004FBCBEBase()
{
	*(const void **)this = g_00BC6F20;
}

class Rva004FBCBE : public Rva004FBCBEBase
{
public:
	virtual ~Rva004FBCBE();
private:
	char m_04[4];
	UnicodeString m_08;
	UnicodeString m_0C;
	char m_10[0x25 - 0x10];
	bool m_25;
};

Rva004FBCBE::~Rva004FBCBE()
{
	if (m_25) {
		if ((int)AptStrategicMessageBox::s_instance != 0) {
			((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(1);
		}
	}
}
