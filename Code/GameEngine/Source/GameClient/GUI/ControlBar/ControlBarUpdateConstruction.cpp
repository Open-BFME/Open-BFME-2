// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?updateConstructionTextDisplay@ControlBar@@QAEXPAVObject@@@Z retail 0x0053E3E6 203 bytes. Donor is BFME1 ControlBarContextUI.cpp updateConstructionTextDisplay which pushes the same two literals ControlBar.wnd UnderConstructionDesc and CONTROLBAR UnderConstructionDesc and calls nameToKey winGetWindowFromId fetch format GadgetStaticTextSetText. Identity also from callers 0x0053E4B1 and 0x0053E4F1 comparing this plus 0x78 against obj plus 0x280. Recipe is donor verbatim with extern guard globals for linkability.
#include "unicode_string.h"

typedef int Int;

enum ObjectStatusTypes
{
	Rva0053E4B1Status = 2
};

class GameWindow
{
};

#define RVA0053EB81_VIRTUAL(name) virtual void name();

// Vtable offsets used by the target method. The object type and the virtual
// method identities remain unresolved; only the three observed slots are
// typed by their return use.
class Rva0053EB81Subject
{
public:
	RVA0053EB81_VIRTUAL(pad00) RVA0053EB81_VIRTUAL(pad01) RVA0053EB81_VIRTUAL(pad02) RVA0053EB81_VIRTUAL(pad03)
	RVA0053EB81_VIRTUAL(pad04) RVA0053EB81_VIRTUAL(pad05) RVA0053EB81_VIRTUAL(pad06) RVA0053EB81_VIRTUAL(pad07)
	RVA0053EB81_VIRTUAL(pad08) RVA0053EB81_VIRTUAL(pad09) RVA0053EB81_VIRTUAL(pad10) RVA0053EB81_VIRTUAL(pad11)
	RVA0053EB81_VIRTUAL(pad12) RVA0053EB81_VIRTUAL(pad13) RVA0053EB81_VIRTUAL(pad14) RVA0053EB81_VIRTUAL(pad15)
	RVA0053EB81_VIRTUAL(pad16) RVA0053EB81_VIRTUAL(pad17) RVA0053EB81_VIRTUAL(pad18) RVA0053EB81_VIRTUAL(pad19)
	RVA0053EB81_VIRTUAL(pad20) RVA0053EB81_VIRTUAL(pad21) RVA0053EB81_VIRTUAL(pad22) RVA0053EB81_VIRTUAL(pad23)
	RVA0053EB81_VIRTUAL(pad24) RVA0053EB81_VIRTUAL(pad25) RVA0053EB81_VIRTUAL(pad26) RVA0053EB81_VIRTUAL(pad27)
	RVA0053EB81_VIRTUAL(pad28) RVA0053EB81_VIRTUAL(pad29) RVA0053EB81_VIRTUAL(pad30) RVA0053EB81_VIRTUAL(pad31)
	RVA0053EB81_VIRTUAL(pad32) RVA0053EB81_VIRTUAL(pad33) RVA0053EB81_VIRTUAL(pad34) RVA0053EB81_VIRTUAL(pad35)
	RVA0053EB81_VIRTUAL(pad36) RVA0053EB81_VIRTUAL(pad37) RVA0053EB81_VIRTUAL(pad38) RVA0053EB81_VIRTUAL(pad39)
	RVA0053EB81_VIRTUAL(pad40) RVA0053EB81_VIRTUAL(pad41) RVA0053EB81_VIRTUAL(pad42) RVA0053EB81_VIRTUAL(pad43)
	RVA0053EB81_VIRTUAL(pad44) RVA0053EB81_VIRTUAL(pad45) RVA0053EB81_VIRTUAL(pad46) RVA0053EB81_VIRTUAL(pad47)
	RVA0053EB81_VIRTUAL(pad48) RVA0053EB81_VIRTUAL(pad49) RVA0053EB81_VIRTUAL(pad50) RVA0053EB81_VIRTUAL(pad51)
	RVA0053EB81_VIRTUAL(pad52) RVA0053EB81_VIRTUAL(pad53)
	virtual bool rva0053EB81SlotD8();
	RVA0053EB81_VIRTUAL(pad55)
	virtual int rva0053EB81SlotE0();
	RVA0053EB81_VIRTUAL(pad57) RVA0053EB81_VIRTUAL(pad58) RVA0053EB81_VIRTUAL(pad59) RVA0053EB81_VIRTUAL(pad60)
	RVA0053EB81_VIRTUAL(pad61) RVA0053EB81_VIRTUAL(pad62) RVA0053EB81_VIRTUAL(pad63) RVA0053EB81_VIRTUAL(pad64)
	RVA0053EB81_VIRTUAL(pad65) RVA0053EB81_VIRTUAL(pad66) RVA0053EB81_VIRTUAL(pad67) RVA0053EB81_VIRTUAL(pad68)
	RVA0053EB81_VIRTUAL(pad69) RVA0053EB81_VIRTUAL(pad70) RVA0053EB81_VIRTUAL(pad71) RVA0053EB81_VIRTUAL(pad72)
	RVA0053EB81_VIRTUAL(pad73) RVA0053EB81_VIRTUAL(pad74)
	virtual int rva0053EB81Slot12C();
};

#undef RVA0053EB81_VIRTUAL

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;

	float getConstructionPercent()
	{
		return m_constructionPercent;
	}

private:
	unsigned char m_pad000[0x250];

public:
	Rva0053EB81Subject *m_250;

private:
	unsigned char m_pad254[0x2c];
	float m_constructionPercent;
};

struct Rva0053E4B1Owner
{
	unsigned char m_pad[0xfc];
	Object *m_fc;
};

class ControlBar
{
public:
	void updateConstructionTextDisplay(Object *obj);
	void rva0053E4B1();
	void rva0053EB81();
	void rva0053E783(void *object, int flag);
	void switchToContext(int context, void *object);
	void rva0031D230();

private:
	unsigned char m_pad0[0x6c];
	Rva0053E4B1Owner *m_6c;
	unsigned char m_pad70[8];
	float m_displayedConstructPercent;
	unsigned char m_pad7c[4];
	int m_80;
};

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	int m_10;
};

extern PlayerList *ThePlayerList;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual void pad45();
	virtual void pad46();
	virtual void pad47();
	virtual void pad48();
	virtual void pad49();
	virtual void pad50();
	virtual void pad51();
	virtual void pad52();
	virtual void pad53();
	virtual void pad54();
	virtual void pad55();
	virtual void pad56();
	virtual void pad57();
	virtual void pad58();
	virtual void pad59();
	virtual GameWindow *winGetWindowFromId(GameWindow *window, Int id);
};

extern GameWindowManager *TheWindowManager;

class GameTextInterface
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual const UnicodeString *slot44(const char *label, bool *exists);
};

extern GameTextInterface *TheGameText;

void __cdecl GadgetStaticTextSetText(GameWindow *win, UnicodeString text);

extern unsigned int g_Va00E05F64;
extern unsigned int g_00E05F60;

void ControlBar::updateConstructionTextDisplay(Object *obj)
{
	UnicodeString text;
	static unsigned int descID = TheNameKeyGenerator->nameToKey("ControlBar.wnd:UnderConstructionDesc");
	GameWindow *descWindow = TheWindowManager->winGetWindowFromId(0, (Int)descID);
	text.format(TheGameText->slot44("CONTROLBAR:UnderConstructionDesc", 0), obj->getConstructionPercent());
	GadgetStaticTextSetText(descWindow, text);
	m_displayedConstructPercent = obj->getConstructionPercent();
}

// ?rva0053E4B1@ControlBar@@QAEXXZ @0x0053E4B1 64B: inspect the selected
// object's status bit 2, then compare its +0x280 construction value to the
// cached ControlBar value at +0x78. The owner path through +0x6C/+0xFC is a
// target-layout view; the original method name remains unknown.
void ControlBar::rva0053E4B1()
{
	Object *obj = m_6c->m_fc;
	if (!obj->testStatus(Rva0053E4B1Status)) {
		return rva0031D230();
	}
	if (m_displayedConstructPercent != obj->getConstructionPercent()) {
		updateConstructionTextDisplay(obj);
	}
}

// Retail 0x0053EB81, 114 bytes. Address-derived method name. The ControlBar
// association follows the target thiscall shape and the +0x6C owner path also
// used by matched sibling 0x0053E4B1. The selected object at
// owner->object+0x250 is only an ABI view; its class and virtual method
// meanings remain unresolved.
void ControlBar::rva0053EB81()
{
	Rva0053E4B1Owner *owner = m_6c;
	Object *object = owner->m_fc;
	Rva0053EB81Subject *subject = object->m_250;
	if (!subject)
	{
		switchToContext(0, owner);
		return;
	}

	int localPlayer = ThePlayerList->m_10;
	if (!subject->rva0053EB81SlotD8() || subject->rva0053EB81SlotE0() != localPlayer)
		return rva0031D230();
	if (m_80 != subject->rva0053EB81Slot12C())
		rva0053E783(object, 1);
}
