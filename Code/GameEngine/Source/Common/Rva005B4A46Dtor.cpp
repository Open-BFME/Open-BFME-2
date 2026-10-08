// cl: /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
// Native 005B4A46..005B4AD9 (147B): CahAppearance cleanup. Both literals
// identify its Apt resources; the application class name remains unresolved.
// The final vptr is the rowed Rva005B253F base's table (VA C72B74).
// Lead: Rva005B2575Dtor.cpp's string/screen cleanup and inline base teardown.
#include "ascii_string.h"

void _bfme_closeAptScreen(const AsciiString &name);
class Rva00223A94
{
public:
	int rva00223A94(const AsciiString *key);
};
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class IMEManager
{
public:
	virtual void m00() = 0;
	virtual void m04() = 0;
	virtual void m08() = 0;
	virtual void m0C() = 0;
	virtual void m10() = 0;
	virtual void m14() = 0;
	virtual void m18() = 0;
	virtual void m1C() = 0;
	virtual void m20() = 0;
	virtual void m24() = 0;
	virtual void m28() = 0;
	virtual void m2C() = 0;
	virtual void m30() = 0;
	virtual void m34() = 0;
	virtual void m38() = 0;
	virtual void m3C() = 0;
	virtual void m40() = 0;
};
extern IMEManager *TheIMEManager;

class Rva005B253F
{
public:
	virtual ~Rva005B253F() {}
private:
	void *m_04;
};

class Rva005B4A46 : public Rva005B253F
{
public:
	virtual ~Rva005B4A46();
private:
	void *m_window08;
	char m_pad0C;
	bool m_imeActive;
};

Rva005B4A46::~Rva005B4A46()
{
	_bfme_closeAptScreen(AsciiString("CahAppearance::InitGadgets"));
	{
		AsciiString name("CahAppearance::Portrait");
		reinterpret_cast<Rva00223A94 *>(g_bfmeAptWindowManager)->rva00223A94(&name);
	}
	if (m_imeActive)
		TheIMEManager->m40();
}
