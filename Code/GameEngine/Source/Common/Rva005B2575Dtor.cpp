// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// ??1Rva005B2575@@UAE@XZ, retail 0x005B2575, 86 bytes.
// Dtor of Rva005B2575 over inline base: closes CahBonus InitGadgets Apt screen
// via pin-only _bfme_closeAptScreen plus rowed StringBase PBD ctor plus rowed
// releaseBuffer. Two vtable stores from derived plus inline base dtor.
// Evidence: literal CahBonus::InitGadgets plus rowed StringBase 0x00037BA0
// plus pin 0x0041149A plus rowed releaseBuffer 0x00036410 plus caller 0x005B25CE.
#include "ascii_string.h"

void _bfme_closeAptScreen(const AsciiString &);

class Rva005B2575Base
{
public:
	virtual ~Rva005B2575Base() {}
};

class Rva005B2575 : public Rva005B2575Base
{
public:
	virtual ~Rva005B2575();
};

Rva005B2575::~Rva005B2575()
{
	AsciiString s("CahBonus::InitGadgets");
	_bfme_closeAptScreen(s);
}
