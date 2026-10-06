// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva00A9CC7@@UAE@XZ retail 0x000A9CC7 111B
// Own vptr BC9400; under EH state 1, when the AsciiString at +4 is not empty
// (rowed isEmpty 0x00001E2F), the Apt window manager global
// g_bfmeAptWindowManager (VA 0x00DFE4CC) gets the rowed
// ?rva00223D02@Rva00223D02@@QAEXPBVAsciiString@@PAVCreateAHeroData@@@Z
// 0x00223D02 with that name and this object; when TheDisplayStringManager
// (VA 0x00DFEAD8) is set the display string at +8 is freed through its
// slot +0x3C and cleared; then the AsciiString member's releaseBuffer
// 0x00036410 runs and the base's inline dtor restores BC93BC.
// Manager view as in Rva00271496Free.cpp. Names address-derived.
#include "ascii_string.h"

class CreateAHeroData;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00223D02
{
public:
	void rva00223D02(const AsciiString *name, CreateAHeroData *data);
};

class DisplayString;

class DisplayStringManager
{
public:
	virtual ~DisplayStringManager() {}
	virtual void managerSlot04() = 0;
	virtual void managerSlot08() = 0;
	virtual void managerSlot0C() = 0;
	virtual void managerSlot10() = 0;
	virtual void managerSlot14() = 0;
	virtual void managerSlot18() = 0;
	virtual void managerSlot1C() = 0;
	virtual void managerSlot20() = 0;
	virtual void managerSlot24() = 0;
	virtual void managerSlot28() = 0;
	virtual void managerSlot2C() = 0;
	virtual void managerSlot30() = 0;
	virtual void managerSlot34() = 0;
	virtual DisplayString *newDisplayString();
	virtual void freeDisplayString(DisplayString *s);
};

extern DisplayStringManager *TheDisplayStringManager;

class Rva00A9CC7Base
{
public:
	virtual ~Rva00A9CC7Base() {}
};

class Rva00A9CC7 : public Rva00A9CC7Base
{
public:
	virtual ~Rva00A9CC7();

private:
	AsciiString m_name; // +0x04
	DisplayString *m_display; // +0x08
};

Rva00A9CC7::~Rva00A9CC7()
{
	if (!m_name.isEmpty())
		((Rva00223D02 *)g_bfmeAptWindowManager)->rva00223D02(&m_name, reinterpret_cast<CreateAHeroData *>(this));
	if (TheDisplayStringManager)
	{
		TheDisplayStringManager->freeDisplayString(m_display);
		m_display = 0;
	}
}
