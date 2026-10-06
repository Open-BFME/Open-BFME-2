// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1Made002CCC2D@@UAE@XZ retail 0x0050BB82 74B
// Novtable derived of Rva00507823 base rowed at 0x00507823. Destroys
// AsciiString at +0x12C via pinned ??1AsciiString at 0x00036410 EH state
// 1 then filter at +0x128 via rowed ??1Rva00360D26Member at 0x00360D26
// EH state 0 then base dtor. No derived vptr store novtable same as
// Rva00508CF7 precedent. Evidence: pinned ctor ??0Made002CCC2D at
// 0x0050BB0E builds filter at +0x128 plus nulls +0x12C plus floats
// plus vtable 0x00864EB0 plus caller deleting 0x0050BB66 calls here.
#include "ascii_string.h"

class Rva00360D26Member
{
public:
	~Rva00360D26Member();
private:
	int m_x;
};

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Made002CCC2D : public Rva00507823
{
public:
	virtual ~Made002CCC2D();
private:
	Rva00360D26Member m_filter128;
	AsciiString m_str12C;
};

Made002CCC2D::~Made002CCC2D()
{
}
