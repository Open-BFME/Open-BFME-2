// cl: /O1 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Native56BC3D..56BCE5 complete168B. WB1449940 names StrategicInGameUI::CreateHelpFor
// and source file. Counted help return follows verified56BABF; translated title
// receives the entry pointer even though the retail getter does not use it.
#include "unicode_string.h"

class Rva00220808;

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct RvaF6Ret
{
	RvaF6Ret(TargetRef00217D4C *p) : m_ptr(p)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	~RvaF6Ret()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	TargetRef00217D4C *m_ptr;
};

class InGameSimpleHelp
{
public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
private:
	char m_opaque[12];
};

typedef bool Bool;
class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, Bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, Bool *exists = 0) = 0;
};

extern GameTextInterface *TheGameText;

class Rva005E2338Elem;
UnicodeString Rva005C95CAGet(const Rva005E2338Elem *);
namespace StrategicInGameUI { RvaF6Ret CreateHelpFor(const Rva005E2338Elem *); }
RvaF6Ret StrategicInGameUI::CreateHelpFor(const Rva005E2338Elem *entry)
{
 UnicodeString help=TheGameText->fetch("STRATEGICHUD:BuildPlotHelp");
 return RvaF6Ret((TargetRef00217D4C*)new InGameSimpleHelp(Rva005C95CAGet(entry),help));
}
