// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG
//
// ??1Made002CCC90@@UAE@XZ retail 0x0050BD9D 56B
// Novtable derived of Rva00507823 base rowed at 0x00507823. Destroys
// AsciiString at +0x128 via pinned ??1AsciiString at 0x00036410 EH state
// 0 then calls base dtor. No derived vptr store novtable same as
// Rva00508CF7 precedent at 0x00508CF7. Evidence: pinned ctor
// ??0Made002CCC90 at 0x0050BD45 stores vtable 0x00864F78 plus caller
// deleting 0x0050BD81 calls here plus same 56B EH shape as rowed
// CloudBreak 0x004C47F3.
#include "ascii_string.h"

class Rva00507823
{
public:
	virtual ~Rva00507823();
private:
	unsigned char m_pad[0x128 - 4];
};

class __declspec(novtable) Made002CCC90 : public Rva00507823
{
public:
	virtual ~Made002CCC90();
private:
	AsciiString m_str128;
};

Made002CCC90::~Made002CCC90()
{
}
