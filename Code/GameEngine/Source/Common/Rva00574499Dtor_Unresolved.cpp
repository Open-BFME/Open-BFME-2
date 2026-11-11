// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// Split from Rva00574499Dtor.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// ??1Rva00574499@@QAE@XZ, retail 0x00574499, 68 bytes.
// Evidence: EH prolog unwind states 1..0 tear down two strings at +0x0C down to +0x08
// through the folded string release 0x00036410, then state -1 destroys the
// subobject at +0 through pinned 0x0022167C; deleting-dtor caller at 0x00574B4C
// proves ??1 identity; layout follows sibling Rva005CB3BE dtor precedent.

#include "string_base.h"

#include "ascii_string.h"
#include "unicode_string.h"

#include "../../../Libraries/Source/Apt/AptRefTarget.h"
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

// The counted handle (assignment 0x002174A4 rowed elsewhere).


// The help object InGameHotSpotSimpleHelp also builds (ctor 0x005398CD in
// GameClient/GUI/InGame/InGameSimpleHelp.cpp).
class InGameSimpleHelp
{
	char m_opaque[12];

public:
	InGameSimpleHelp(const UnicodeString &title, const UnicodeString &text);
};

// TheGameText viewed by slot: fetch(label, exists) at +0x38.
#include "../../Include/GameClient/GameText.h"
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



#include "../../Include/Common/Rva0042D6B4PtrChaseField.h"

class Rva001FF3A9
{
public:
    void rva001FF3A9(const TreeHintRef00217D4C &ref);
};

extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;

class Rva005749B7
{
public:
    void rva005749B7(int unused);
private:
    char m_pad00[0x18];
    Rva0042D6B4PtrChaseField *m_at18;
    char m_pad1c[0x4C];
    TreeHintRef00217D4C m_at68;
};

class Rva00574A19
{
public:
    void rva00574A19(int unused);
private:
    char m_pad00[0x14];
    Rva0042D6B4PtrChaseField *m_at14;
    char m_pad18[0x54];
    TreeHintRef00217D4C m_at6c;
};

// Native 005749B7..00574A19 and 00574A19..00574A7B: 98-byte callers
// of the recovered help factory. Each target independently proves its
// receiver offsets, global source, getter, assignment and virtual forwarder.
// ret 4 proves one ignored stack word; its meaning remains unknown.
// Assignment destroys the factory temporary before notifying the target.
void Rva005749B7::rva005749B7(int)
{
    Rva001FF3A9 *target = (Rva001FF3A9 *)m_at18->get();
    if (target != 0)
    {
        m_at68 = ((Rva00574499 *)&g_Va00E062FC)->rva005744DD();
        target->rva001FF3A9(m_at68);
    }
}

void Rva00574A19::rva00574A19(int)
{
    Rva001FF3A9 *target = (Rva001FF3A9 *)m_at14->get();
    if (target != 0)
    {
        m_at6c = ((Rva00574499 *)&g_Va00E0630C)->rva005744DD();
        target->rva001FF3A9(m_at6c);
    }
}
