// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1Made002CC774@@UAE@XZ @0x00509564 (56B).
// DamageFieldNugget dtor: novtable derived of Rva00507823 base rowed at
// 0x00507823. Destroys AsciiString at +0x130 via rowed releaseBuffer
// 0x00036410 (StringBase<char> inline dtor) EH state 0 then base dtor. No
// derived vptr store novtable same as Rva00508CF7 precedent. Size 0x134
// from WeaponNuggetParse news. Unblocks deleting dtor 0x00509548.
#include "ascii_string.h"


class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Made002CC774 : public Rva00507823
{
public:
	virtual ~Made002CC774();
private:
	int m_128;
	int m_12C;
	AsciiString m_130;
};

Made002CC774::~Made002CC774()
{
}
