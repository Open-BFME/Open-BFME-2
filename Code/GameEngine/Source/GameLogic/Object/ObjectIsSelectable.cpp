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

struct ThingTemplate
{
	unsigned char m_pad[0x10F];
	unsigned char m_byte10F;
	unsigned char m_pad110;
	unsigned char m_byte111;
	unsigned char m_pad112[0x632 - 0x112];
	unsigned char m_byte632;
};

class InGameUIRet
{
public:
	unsigned char m_pad[0x14];
	int m_field14;
};

class InGameUI
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual InGameUIRet *slot48();
};

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
	ThingTemplate *tmpl = m_template;
	if ((tmpl->m_byte10F & 4) != 0)
		return true;
	Bool b = testStatus((ObjectStatusTypes)3);
	if (b)
		return false;
	if (tmpl->m_byte632 == b)
	{
		if ((m_priv438 & 1) != 0)
			return false;
	}
	if ((tmpl->m_byte111 & 2) != 0)
		return false;
	Bool sel = m_isSelectable;
	InGameUIRet *r = TheInGameUI->slot48();
	if (r != 0 && r->m_field14 == 0x18 && (m_template->m_byte10F & 0x10) != 0)
		sel = true;
	return sel;
}
