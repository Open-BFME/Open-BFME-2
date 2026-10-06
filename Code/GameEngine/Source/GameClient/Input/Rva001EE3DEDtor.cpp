// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??1Rva001EE3DE@@UAE@XZ, retail 0x001EE3DE, 165 bytes.
// Virtual dtor: vtable 0x007E0358, manual release of ptr at +0x4FA8 via
// DisplayManager global 0x009FEAD8 slot 0x3C (FreeEntry, Rva0025FC61 precedent),
// Wide strings at +0x1300/+0x12FC/+0x12F8 and narrow at +0x126C via
// releaseBuffer, CursorInfo[0x54] array at +0xC via ??_M, base
// GameEngineDeletingBase dtor. Evidence: ??_G caller; no donor.
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"

class DisplayManager
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void FreeEntry(void *p);
};

extern DisplayManager *g_009FEAD8;

struct CursorInfo {
	~CursorInfo();
	unsigned char m_pad[0x54];
};

class GameEngineDeletingBase
{
public:
	virtual ~GameEngineDeletingBase();
};

class Rva001EE3DE : public GameEngineDeletingBase
{
public:
	virtual ~Rva001EE3DE();

private:
	unsigned char m_pad04[8];
	CursorInfo m_arr0C[0x38];
	AsciiString m_str126C;
	unsigned char m_pad1270[0x12F8 - 0x1270];
	UnicodeString m_str12F8;
	UnicodeString m_str12FC;
	UnicodeString m_str1300;
	unsigned char m_pad1304[0x4FA8 - 0x1304];
	void *m_ptr4FA8;
};

Rva001EE3DE::~Rva001EE3DE()
{
	if (m_ptr4FA8 != 0)
		g_009FEAD8->FreeEntry(m_ptr4FA8);
	m_ptr4FA8 = 0;
}
