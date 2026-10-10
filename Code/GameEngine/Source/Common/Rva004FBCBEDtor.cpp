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
	Rva004FBCBEBase():m_04(0) {}
 virtual ~Rva004FBCBEBase();
 int m_04;
};

// ??1Rva004FBCBEBase@@UAE@XZ present-unmatched
inline Rva004FBCBEBase::~Rva004FBCBEBase()
{
	*(const void **)this = g_00BC6F20;
}

// Native ctor4FBC4D..4FBCBE and WB1312F80 prove refcount4,
// UnicodeStrings8/C, mode10, -1 at14, zero coordinate18/1C/20,
// and three flags24/25/26. This coordinate constructor groups the
// float stores exactly as retail; no scheduling intrinsics or asm.
// Native12-byte vtable8634E4 holds4FBD1E then two sharedB3FD0
// no-argument empty hooks; their original names remain unknown.
struct Rva004FBCBECoord {float x,y,z;Rva004FBCBECoord():x(0.0f),y(0.0f),z(0.0f){}};
class Rva004FBCBE : public Rva004FBCBEBase
{
public:
	virtual ~Rva004FBCBE();
 virtual void slot04(){}
 virtual void slot08(){}
 Rva004FBCBE(const UnicodeString&,const UnicodeString&,int);
private:
	UnicodeString m_08;
	UnicodeString m_0C;
	int m_10,m_14;
 Rva004FBCBECoord m_coord;
 bool m_24,m_25,m_26;
};

Rva004FBCBE::~Rva004FBCBE()
{
	if (m_25) {
		if ((int)AptStrategicMessageBox::s_instance != 0) {
			((Rva0054CBEFTarget *)(void *)(int)AptStrategicMessageBox::s_instance)->method(1);
		}
	}
}

Rva004FBCBE::Rva004FBCBE(const UnicodeString&a,const UnicodeString&b,int mode)
:m_08(a),m_0C(b),m_10(mode),m_14(-1){m_24=false;m_25=false;m_26=false;}
