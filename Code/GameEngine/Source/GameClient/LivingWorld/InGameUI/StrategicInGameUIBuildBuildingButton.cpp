// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// StrategicInGameUI::BuildBuildingButton (WorldBuilder
// StrategicInGameUIBuildBuildingButton.cpp). Target facts for OnLeftClicked
// 0x005E92B1 (virtual: its pointer sits at 0x00878014 in a command button
// vtable): appends message 0x6AA through TheMessageStream (vslot 18) with
// three integer arguments: the region's owner id (+0x18 -> +0x1C -> +0x12C), the region id (+0x18 -> +0x18) and
// the building choice's id (+0x1C -> +0x04). Field meanings are inferred.
//
// CreateHelp 0x005E94A7 (213 bytes, ret 4; WB 0x01608DE0 names it): the
// title is the choice's +0x18 label fetched through TheGameText (slot 14)
// when set, the text is the building template's getConstructButtonHelp
// (0x002DFE9E, WB-named, unrowed) for the region's owner; both go into a new
// 12-byte InGameSimpleHelp held by the counted-help result (same ABI as
// QueueUnitButton::CreateHelp 0x005F8D07).
#include "ascii_string.h"
#include "unicode_string.h"

struct TargetRef00217D4C
{
	void *m_vtbl;
	int m_refCount;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *ref);
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C(TargetRef00217D4C *ptr) : m_ptr(ptr)
	{
		if (m_ptr)
			++m_ptr->m_refCount;
	}
	~TreeHintRef00217D4C()
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

class GameTextInterface
{
public:
#define SLOT(n) virtual void slot##n();
	SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7)
	SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13)
#undef SLOT
	virtual UnicodeString fetch(const char *label, bool *exists = 0);
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0);
};
extern GameTextInterface *TheGameText;

class Rva003F1C22;
class LivingWorldBuildingTemplate
{
public:
	UnicodeString getConstructButtonHelp(Rva003F1C22 *player) const;
	char m_pad00[0x18];
	AsciiString m_label; // +0x18
};
class GameMessage
{
public:
	void appendIntegerArgument(int arg);
};

class MessageStream
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual GameMessage *appendType(int type);
};
extern MessageStream *TheMessageStream;

struct Rva005E92B1Owner
{
	char m_pad00[0x12C];
	int m_id; // +0x12C
};

struct Rva005E92B1Region
{
	char m_pad00[0x18];
	int m_id; // +0x18
	Rva005E92B1Owner *m_owner; // +0x1C
};

struct Rva005E92B1Choice
{
	int m_00;
	int m_id; // +0x04
};

namespace StrategicInGameUI
{
class BuildBuildingButton
{
public:
	virtual void OnLeftClicked();
	virtual TreeHintRef00217D4C CreateHelp();

private:
	char m_pad04[0x18 - 0x04];
	Rva005E92B1Region *m_region; // +0x18
	Rva005E92B1Choice *m_choice; // +0x1C
};
}

void StrategicInGameUI::BuildBuildingButton::OnLeftClicked()
{
	GameMessage *msg = TheMessageStream->appendType(0x6AA);
	msg->appendIntegerArgument(m_region->m_owner->m_id);
	msg->appendIntegerArgument(m_region->m_id);
	msg->appendIntegerArgument(m_choice->m_id);
}

TreeHintRef00217D4C StrategicInGameUI::BuildBuildingButton::CreateHelp()
{
	UnicodeString title;
	const AsciiString &label = ((const LivingWorldBuildingTemplate *)m_choice)->m_label;
	if (!label.isEmpty())
		title = TheGameText->fetch(label);
	UnicodeString text = ((const LivingWorldBuildingTemplate *)m_choice)->getConstructButtonHelp((Rva003F1C22 *)m_region->m_owner);
	return TreeHintRef00217D4C((TargetRef00217D4C *)new InGameSimpleHelp(title, text));
}
