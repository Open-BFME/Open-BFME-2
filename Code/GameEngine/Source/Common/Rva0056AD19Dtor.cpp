// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc
// ??1Rva0056AD19@@UAE@XZ retail 0x0056AD19 88B
// Own vptrs C6D1EC (+0) and C6D1B0 (+8, inside the first base); the member at
// +0x14 is emptied in the body through the rowed ?clear@Rva002BED91
// 0x002BED91 (EH state 1), then its inline dtor releases the ref through the rowed
// fastcall ReleaseTreeHintRef00217D4C 0x0007DEEF when set (state 0); then the
// rowed MI base dtor ??1Rva0056AC26@@UAE@XZ 0x0056AC26. Caller: rowed ??_G
// 0x0056B0A3 (vtable 0x00C6D1EC). Names address-derived.

// Constructor 0x0056AFCF is the complete RET4 body ending at 0x0056B0A3.
// Native C6D1EC/C6D1B0 vptrs identify the existing destructor owner; its
// caller allocates 0x18 bytes and the retained-reference holder is at +0x14.
// WB 1446940 independently supplies the two TutorialCompleted string calls,
// allocation of the 0x28-byte popup and the retained-reference/world dispatch.
// The callback and popup's original class names remain unknown. Address-owned
// class names below belong to their existing actual constructor/destructor rows.
// New real popup constructor 0x004FBC4D (113B) closes the old missing dependency.
// The text service slot +0x3C uses its established const char*/bool* contract.
// The world dispatch consumes the holder's four-byte pointer prefix; this does
// not claim the concrete vector element's original identity or its overflow ABI.
#include "unicode_string.h"

struct TargetRef00217D4C;
class Rva0056AC26Owner;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);

class Rva002BED91
{
public:
	Rva002BED91() : m_ref(0) {}
	void set(TargetRef00217D4C *);
	~Rva002BED91()
	{
		if (m_ref)
			ReleaseTreeHintRef00217D4C(m_ref);
	}
	void clear();

private:
	TargetRef00217D4C *m_ref;
};

#include "../../Include/Common/Rva0056AC26A.h"

#include "../../Include/Common/Rva0056AC26B.h"

#include "../../Include/Common/Rva0056AC26.h"

class Rva0056AD19 : public Rva0056AC26
{
public:
	Rva0056AD19(Rva0056AC26Owner *);
	virtual ~Rva0056AD19();
	// Retail table 0x0086D1EC slot 1 is the shared false body 0x0047A699.
	virtual bool ac26Slot1();

private:
	Rva002BED91 m_14; // +0x14
};

Rva0056AD19::~Rva0056AD19()
{
	m_14.clear();
}

bool Rva0056AD19::ac26Slot1()
{
	return false;
}


#include "../../Include/GameClient/GameText.h"
extern GameTextInterface *TheGameText;

class Rva004FBCBEBase
{
public:
    virtual ~Rva004FBCBEBase();
    int m_04;
};
struct Rva004FBCBECoord { float x, y, z; };
class Rva004FBCBE : public Rva004FBCBEBase
{
public:
    virtual ~Rva004FBCBE();
    virtual void slot04();
    virtual void slot08();
    Rva004FBCBE(const UnicodeString &, const UnicodeString &, int);
private:
    UnicodeString m_08, m_0C;
    int m_10, m_14;
    Rva004FBCBECoord m_coord;
    bool m_24, m_25, m_26;
};
struct Rva002B9062Element { int m_x; };
class Rva002B9A85
{
public:
    void rva002B9A85(const Rva002B9062Element &);
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

Rva0056AD19::Rva0056AD19(Rva0056AC26Owner *owner)
    : Rva0056AC26(owner)
{
    UnicodeString title = TheGameText->fetch("WOTRTutorial:TutorialCompletedTitle", 0);
    UnicodeString text = TheGameText->fetch("WOTRTutorial:TutorialCompletedText", 0);
    m_14.set((TargetRef00217D4C *)new Rva004FBCBE(title, text, 0));
    ((Rva002B9A85 *)TheLivingWorldLogic)->rva002B9A85((const Rva002B9062Element &)m_14);
}
