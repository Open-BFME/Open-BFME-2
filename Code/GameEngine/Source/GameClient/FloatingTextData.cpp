// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /DNDEBUG
//
// ??1FloatingTextData@@UAE@XZ @0x0029D3B0 75B (formerly the address name Rva0029D3B0;
// the ctor 0x0029D352 installs the same vtable 0x007FD1C0).
// Dtor storing vtable 0x007FD1C0, releasing DisplayString slot via
// TheDisplayStringManager slot 15 when +0xC is set, then wide releaseBuffer
// on the UnicodeString at +8. Evidence: vtable store, rowed slot 15 target
// via TheDisplayStringManager, rowed wide releaseBuffer 0x00036E70.

#include "unicode_string.h"

#include "../../Include/GameClient/DisplayStringManager.h"

class FloatingTextData
{
public:
	virtual ~FloatingTextData();
	unsigned char m_pad04[0x8 - 4];
	UnicodeString m_08; // +8
	DisplayString *m_0C; // +0xC
};

FloatingTextData::~FloatingTextData()
{
	if (m_0C != 0)
		TheDisplayStringManager->freeDisplayString(m_0C);
	m_0C = 0;
}
