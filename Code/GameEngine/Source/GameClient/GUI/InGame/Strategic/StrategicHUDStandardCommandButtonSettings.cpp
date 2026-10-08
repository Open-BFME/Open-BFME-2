// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicHUD::StandardCommandButtonSettings (WorldBuilder
// StrategicHUDStandardCommandButtonSettings.cpp names CreateHelp; matched by
// call site, the name is not confirmed by a retail string). Target facts for
// 0x005E1753 (thiscall, hidden return slot): fetches the +0x0C and +0x10
// labels from TheGameText (vslot 14) when set, builds the 12-byte help
// object InGameSimpleHelp (as InGameHotSpotSimpleHelp does) from the two texts and
// returns it as a counted handle (count +0x04).
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

namespace StrategicHUD {
class StandardCommandButtonSettings
{
public:
	TreeHintRef00217D4C CreateHelp() const;

private:
	char m_pad00[0x0C];
	AsciiString m_titleLabel; // +0x0C
	AsciiString m_textLabel; // +0x10
};
}

TreeHintRef00217D4C StrategicHUD::StandardCommandButtonSettings::CreateHelp() const
{
	UnicodeString title;
	if (!((const StringBase<char> *)&m_titleLabel)->isEmpty())
		title = TheGameText->fetch(m_titleLabel, 0);
	UnicodeString text;
	if (!((const StringBase<char> *)&m_textLabel)->isEmpty())
		text = TheGameText->fetch(m_textLabel, 0);
	return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title, text));
}
