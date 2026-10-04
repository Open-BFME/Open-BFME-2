// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
// ??1Rva005D40A6@@UAE@XZ retail 0x005D40A6 114B.
// Dtor with vtable 0x008759D0, DisplayString at +0x24 freed via manager slot 0x3C,
// UnicodeString at +0x28, Rva00524265 at +0x18, Rva0052413E at +0x0c, AsciiString
// at +0x08. EH states 3/2/1/0/-1. Unblocks 0x0057A2B0 0x005D4141.
// Evidence: callees rowed releaseBuffer narrow/wide plus rowed dtors, manager 0x009FEAD8 slot 0x3C.
#include "ascii_string.h"
#include "unicode_string.h"

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

class Rva00524265
{
public:
	~Rva00524265();
private:
	char m_pad[0x0c];
};

class Rva0052413E
{
public:
	~Rva0052413E();
private:
	char m_pad[0x0c];
};

class Rva005D40A6
{
public:
	virtual ~Rva005D40A6();
private:
	int m_04;
	AsciiString m_08;
	Rva0052413E m_0c;
	Rva00524265 m_18;
	DisplayString *m_24;
	UnicodeString m_28;
};

Rva005D40A6::~Rva005D40A6()
{
	if (TheDisplayStringManager != 0 && m_24 != 0)
		TheDisplayStringManager->freeDisplayString(m_24);
}

class Rva00222A8BTarget;
extern Rva00222A8BTarget *TheRva00222A8BTarget;
extern const char g_Rva0107301CEmptyString[];

int __cdecl Rva00524EF4AptCall(Rva00222A8BTarget *t, void *a1, const char *a2, const char *a3);

class Rva005D4118
{
public:
	void rva005D4118();
private:
	int m_00;
	void *m_04;
	const char *m_08;
};
void Rva005D4118::rva005D4118()
{
	const char *s = m_08 ? m_08 + 8 : g_Rva0107301CEmptyString;
	Rva00524EF4AptCall(TheRva00222A8BTarget, m_04, s, "Flash");
}
