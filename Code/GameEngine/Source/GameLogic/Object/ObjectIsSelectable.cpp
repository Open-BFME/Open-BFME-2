// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// ?isSelectable@Object@@QBE_NXZ @0x0028D7FD (114B).
// BFME2 rewrite of the BFME1 donor Object::isSelectable
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Object.cpp:3474).
// Check order is preserved (ALWAYS gate -> UNSELECTABLE status -> dead gate ->
// second kind gate -> selectable flag with InGameUI override) but BFME2 reads
// template kind bytes directly where the ancestor called isKindOf, and adds the
// InGameUI slot48 override. Pin notes the donor call site at
// changeObjectPanelFlagForSingleObject 0x003C4D00; 12 raw callers listed in the
// packet (0x0027174F 0x00292FE5 0x0029538B 0x00347EB4 0x003C4D00 0x0042FB6B
// 0x004D6D70 0x0052500C 0x00525EA4 0x00525F2C 0x005271D2 0x005399E6).
//
// Offsets (all retail-measured): template +0x04 (same slot Object.cpp and
// Object_isAbleToAttack.cpp document), kind bytes +0x10F/+0x111 (same area
// Object_isAbleToAttack.cpp models as m_kindByte10F etc.; base +0x108 holds
// STRUCTURE bit 0x80 per InGameUI_selectMatchingAcrossMap.cpp), template byte
// +0x632 compared to the testStatus result (retail cmp [edi+0x632],al), Object
// m_isSelectable +0x434 (proven by ?setSelectable@Object@@QAEX_N@Z at
// 0x0028B76D: mov [ecx+0x434],al), private status +0x438 bit0 EFFECTIVELY_DEAD
// (bfmeobjectlayout shim; same byte ObjectScriptStatus.cpp pads around),
// TheInGameUI at 0x00DFEDF0 (RVA 0x009FEDF0; same global the
// ?doDisplayText@ScriptActions@@IAEXABVAsciiString@@@Z stash uses for
// InGameUI::message) with the +0xC0 virtual returning the +0x14==0x18 guard.
// testStatus(3) is OBJECT_STATUS_UNSELECTABLE (index 3; rowed at 0x0004E536,
// declared only so the gate resolves the E8 by full mangled name).

typedef bool Bool;

enum ObjectStatusTypes;

#include "../../../Include/Common/ThingTemplate.h"

#include "../../../Include/GameClient/CommandButton.h"

#include "../../../Include/GameClient/InGameUI.h"

extern InGameUI *TheInGameUI;

class Object
{
public:
	Bool testStatus(ObjectStatusTypes bit) const;
	Bool isSelectable() const;

private:
	char m_pad00[4];
	ThingTemplate *m_template;
	char m_pad08[0x434 - 0x08];
	Bool m_isSelectable;
	char m_pad435[0x438 - 0x434 - 1];
	unsigned char m_priv438;
};

Bool Object::isSelectable() const
{
	ThingTemplate *thingTemplate = m_template;
	if ((thingTemplate->m_kindof[1] & (1U << 26)) != 0)
		return true;
	Bool b = testStatus((ObjectStatusTypes)3);
	if (b)
		return false;
	if (thingTemplate->m_keepSelectableWhenDead == b)
	{
		if ((m_priv438 & 1) != 0)
			return false;
	}
	if ((thingTemplate->m_kindof[2] & (1U << 9)) != 0)
		return false;
	Bool sel = m_isSelectable;
	const CommandButton *command = TheInGameUI->getGUICommand();
	if (command != 0 && command->getCommandType() == (GUICommandType)0x18 && (m_template->m_kindof[1] & (1U << 28)) != 0)
		sel = true;
	return sel;
}
