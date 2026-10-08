// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
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

// Native 0x005B4A46..0x005B4AD9 (147B), CahAppearance cleanup.
// Same two-table destructor shape as the rowed CahBonus cleanup above;
// slot-0 delete wrapper 0x005B4C7B calls its address-derived nonvirtual name.
// Target-only layout: readiness byte +0xD, two AsciiString temporaries,
// Apt portrait erase thunk 0x00223A94 and IMEManager virtual slot +0x40.
// The concrete application class name and remaining fields are unknown.
class Rva005B4A46Base
{
public:
	virtual void slot00();
	~Rva005B4A46Base() {}
};
class Rva005B4A46 : public Rva005B4A46Base
{
public:
	virtual void slot00();
	~Rva005B4A46();
private:
	char m_unknown04[9];
	bool m_ready0D;
};
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};
extern class BfmeAptWindowManager *g_bfmeAptWindowManager;
class Rva005B4A46IMEView
{
public:
	virtual void slot00(); virtual void slot04(); virtual void slot08();
	virtual void slot0C(); virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C(); virtual void slot20();
	virtual void slot24(); virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34(); virtual void slot38();
	virtual void slot3C(); virtual void slot40();
};
extern class IMEManager *TheIMEManager;
Rva005B4A46::~Rva005B4A46()
{
	{
		AsciiString key("CahAppearance::InitGadgets");
		_bfme_closeAptScreen(key);
	}
	{
		AsciiString key("CahAppearance::Portrait");
		reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&key);
	}
	if (m_ready0D)
		reinterpret_cast<Rva005B4A46IMEView *>(TheIMEManager)->slot40();
}
