// cl: /O1 /G7 /arch:SSE /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva003191E2@Rva003193EC@@UAEXHH@Z @0x003191E2 207B (RET 8): slot 0 of the
// listener table 0x00C0C824 that the Rva003193EC constructors (0x00319D01,
// 0x0031A257) store at +4 over the two-callback base 0x00C62A20, so `this` is
// the object +4. Mode 0 rebuilds the army summary (+0x78) state: the owner's
// 0x003191B1 refresh, ArmySummary 0x0040CC8F, then 0x003190E7(true); mode 1
// clears the owner flags (0x0031917A). Unless the second argument is set, a
// presentation at +0x88 is refreshed (0x003FE05E), the summary's display name
// (+0x68) and description (+0x6C) strings are rebuilt and it is updated
// (0x005392C2). Rva003193EC.cpp holds the class's other rows; it keeps a
// private StringBase view for its out-of-line validate calls, which the
// shared UnicodeString header these temporaries need cannot share a unit with.
#include "unicode_string.h"

class Rva00220808;
class Rva0040CFC7;
UnicodeString GetArmySummaryName(Rva00220808 *src);
UnicodeString GetArmySummaryDescription(Rva0040CFC7 *army, int rule);

class ArmySummary { public: void rva0040CC8F(); };
class Rva00319924 { public: void clearFlags(); };
class Rva003FE05E { public: void rva003FE05E(); };
class Rva005392C2 { public: void rva005392C2(); };

class Rva003193ECPrimary
{
public:
	virtual ~Rva003193ECPrimary();
};

// The two-callback listener base (0x00C62A20: both slots an empty RET 8).
class Rva003193ECListener
{
public:
	virtual void rva003191E2(int mode, int keepPresentation) {}
	virtual void slot1(int, int) {}
};

class Rva003193EC : public Rva003193ECPrimary, public Rva003193ECListener
{
public:
	virtual void rva003191E2(int mode, int keepPresentation);
	void rva003190E7(bool flag);
	void rva003191B1();
private:
	char m_pad08[0x68 - 0x08];
	UnicodeString m_displayName;		// +0x68
	UnicodeString m_description;		// +0x6C
	char m_pad70[0x78 - 0x70];
	ArmySummary *m_summary;			// +0x78
	char m_pad7C[0x88 - 0x7C];
	Rva003FE05E *m_presentation;		// +0x88
};

void Rva003193EC::rva003191E2(int mode, int keepPresentation)
{
	switch (mode)
	{
	case 0:
		rva003191B1();
		m_summary->rva0040CC8F();
		rva003190E7(true);
		break;
	case 1:
		((Rva00319924 *)this)->clearFlags();
		break;
	}
	if (keepPresentation == 0 && m_presentation != 0)
	{
		rva003190E7(true);
		m_presentation->rva003FE05E();
		m_displayName = GetArmySummaryName((Rva00220808 *)m_summary);
		Rva0040CFC7 *army = (Rva0040CFC7 *)m_summary;
		m_description = GetArmySummaryDescription(army, 1);
		((Rva005392C2 *)m_presentation)->rva005392C2();
	}
}
