// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??1Rva00574499@@QAE@XZ, retail 0x00574499, 68 bytes.
// Evidence: EH prolog unwind states 1..0 tear down two strings at +0x0C down to +0x08
// through the folded string release 0x00036410, then state -1 destroys the
// subobject at +0 through pinned 0x0022167C; deleting-dtor caller at 0x00574B4C
// proves ??1 identity; layout follows sibling Rva005CB3BE dtor precedent.

#include "string_base.h"

#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref); // 0x0007DEEF

// The counted handle (assignment 0x002174A4 rowed elsewhere).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			m_ptr->m_refCount++;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}

	TargetRef00217D4C *m_ptr;
};

// The help object InGameHotSpotSimpleHelp also builds (ctor 0x005398CD in
// GameClient/GUI/InGame/InGameSimpleHelp.cpp).
class InGameSimpleHelp
{
	char m_opaque[12];

public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
};

// TheGameText viewed by slot: fetch(label, exists) at +0x38.
class GameTextInterface
{
public:
	virtual ~GameTextInterface();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual UnicodeString fetch(const AsciiString &label, bool *exists) = 0;
};
extern GameTextInterface *TheGameText;



class Rva0022167C
{
public:
	~Rva0022167C();

private:
	char m_bytes[8];
};

class Rva00574499
{
public:
	~Rva00574499();
	TreeHintRef00217D4C rva005744DD() const;

private:
	Rva0022167C m_at00;
	AsciiString m_at08;
	AsciiString m_at0c;
};

Rva00574499::~Rva00574499()
{
}

// Native 005744DD..005745D8 (251B), hidden result pointer and ret 4.
// The two callers pass the same 16-byte globals whose teardown is rowed
// above. Native accesses establish labels +8/+C, GameText slot +38,
// the 12-byte InGameSimpleHelp provider, and refcount +4. The matched
// StrategicHUD CreateHelp supplies the algorithm; the original owner and
// method names here remain unknown.
TreeHintRef00217D4C Rva00574499::rva005744DD() const
{
    UnicodeString title;
    if (!((const StringBase<char> *)&m_at08)->isEmpty())
        title = TheGameText->fetch(m_at08, 0);
    UnicodeString text;
    if (!((const StringBase<char> *)&m_at0c)->isEmpty())
        text = TheGameText->fetch(m_at0c, 0);
    return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title, text));
}
