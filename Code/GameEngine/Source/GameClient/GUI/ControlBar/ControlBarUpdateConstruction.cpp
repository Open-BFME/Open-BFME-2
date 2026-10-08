// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
//
// ?updateConstructionTextDisplay@ControlBar@@QAEXPAVObject@@@Z retail 0x0053E3E6 203 bytes. Donor is BFME1 ControlBarContextUI.cpp updateConstructionTextDisplay which pushes the same two literals ControlBar.wnd UnderConstructionDesc and CONTROLBAR UnderConstructionDesc and calls nameToKey winGetWindowFromId fetch format GadgetStaticTextSetText. Identity also from callers 0x0053E4B1 and 0x0053E4F1 comparing this plus 0x78 against obj plus 0x280. Recipe is donor verbatim with extern guard globals for linkability.
#include "unicode_string.h"
#include "ascii_string.h"
#include "Lib/Coord3D.h"
namespace _STL { void __cdecl free(void *); }
#include <vector>

typedef int Int;

enum ObjectStatusTypes
{
	Rva0053E4B1Status = 2
};

enum ObjectID
{
	Rva0053EAECObjectIDValue0 = 0
};

class Team;

class GameWindow
{
public:
    int winHide(bool);
    int winEnable(bool);
    unsigned int winSetStatus(unsigned int);
    unsigned int winClearStatus(unsigned int);
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
	virtual int slot69(bool enabled);
	RVA0053EB81_VIRTUAL(pad70) RVA0053EB81_VIRTUAL(pad71) RVA0053EB81_VIRTUAL(pad72)
	RVA0053EB81_VIRTUAL(pad73) RVA0053EB81_VIRTUAL(pad74)
	virtual int rva0053EB81Slot12C();
};

#undef RVA0053EB81_VIRTUAL

class CommandButton;
class ModuleData;
class Image;

class ConstructionExitView {
public:
    virtual void slot0()=0; virtual void slot1()=0;
    virtual void slot2()=0; virtual void slot3()=0;
    virtual void slot4()=0; virtual void slot5()=0;
    virtual void slot6()=0; virtual void slot7()=0;
    virtual const Coord3D *getRallyPoint() const=0;
};
class ExitInterface;
class Rva002A7DD0 { public: int rva002A7DD0(); };
class BfmeMemberRV { public: bool bfmeAskRV(); };
class PlayerList;
extern PlayerList *ThePlayerList;
struct ConstructionPlayerListView { char unknown00[0x10]; BfmeMemberRV *localPlayer; };
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class Rva002D368E { public: void rva002D368E(); };
class Rva002D363EOwner { public: void rva002D363E(int); };
class WindowList;
class Rva0053ED1A { public: void rva0053EFC7(WindowList &); };
// Native portrait dispatch calls the shared empty RET4 at47A69C. This
// pre-existing opaque ABI binding does not identify ControlBar as its owner.
class Gen_003bcb40 { public: void m(int); };
struct ConstructionTemplateView { char unknown00[0x122]; unsigned char flags; };
struct ConstructionObjectView { char unknown00[4]; ConstructionTemplateView *objectTemplate; };
class ControlBar;
extern ControlBar *TheControlBar;
struct ConstructionOverlayModeView { char unknown00[0x29C]; int mode; };

class Object
{
public:
	bool testStatus(ObjectStatusTypes bit) const;
	bool isLocallyControlled() const;
	ExitInterface *getObjectExitInterface() const;

	float getConstructionPercent()
	{
		return m_constructionPercent;
	}

private:
	unsigned char m_pad000[0x74];

public:
	ObjectID m_74;
	ObjectID getID() const { return m_74; }

private:
	unsigned char m_pad078[0x1d8];

public:
	Rva0053EB81Subject *m_250;

private:
	unsigned char m_pad254[0x2c];
	float m_constructionPercent;
	unsigned char m_pad284[0x80];

public:
	const Team *m_304;
	const Team *getTeam() const { return m_304; }
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
    void rva0053E4F1(Object *);
    void rva0031B641(GameWindow *, const CommandButton *);
    const CommandButton *findCommandButton(const AsciiString &);
    void showRallyPoint(const Coord3D *);
	void rva0053E4B1();
	void rva0053E6E1();
	void updateContextContestedStructureInventory();
	void rva0053E783(void *object, int flag);
	void switchToContext(int context, void *object);
	void rva0031D230();

protected:
	void updateContextStructureInventory();
    static const Image *calculateVeterancyOverlayForObject(const Object *);

private:
	unsigned char m_pad0[0x6c];
	Rva0053E4B1Owner *m_6c;
	unsigned char m_pad70[8];
	float m_displayedConstructPercent;
	unsigned char m_pad7c[4];
	int m_80;
    unsigned char m_pad084[0x58];
    GameWindow *commandWindows[32];
    unsigned char m_pad15c[0x144];
    Rva0053ED1A *overlaySink;
};

class Player;

class PlayerList
{
public:
	unsigned char m_pad00[0x10];
	union
	{
		int m_10;
		Player *m_localPlayer;
	};
};

extern PlayerList *ThePlayerList;

enum Relationship
{
	Rva0053EAECRelationshipValue0 = 0
};

class Team
{
};

class Player
{
public:
	Relationship getRelationship(const Team *team) const;
};

class BuildListInfo
{
public:
	int getDesiredGatherers();
};

class GameMessage
{
public:
	void appendObjectIDArgument(ObjectID objectID);
};

class MessageStream
{
public:
	virtual void slot00();
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
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual GameMessage *appendMessage(int type);
};

// Target data row names this global MessageStreamSubsystem at RVA 0x00A00950
// (VA 0x00E00950); the BFME1 donor calls it TheMessageStream.
extern MessageStream *MessageStreamSubsystem;

class InGameUI;

class Rva0053EAECInGameUIView
{
public:
	virtual void slot00();
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
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39();
	virtual void slot40();
	virtual void slot41();
	virtual void slot42();
	virtual void slot43();
	virtual void slot44();
	virtual void slot45();
	virtual void slot46();
	virtual void slot47();
	virtual void slot48();
	virtual void slot49();
	virtual void slot50();
	virtual void slot51();
	virtual void slot52();
	virtual void slot53();
	virtual void slot54();
	virtual void slot55();
	virtual void slot56();
	virtual void slot57();
	virtual void slot58();
	virtual void slot59();
	virtual void slot60();
	virtual void slot61();
	virtual void slot62();
	virtual void slot63();
	virtual void slot64();
	virtual void slot65();
	virtual void slot66();
	virtual void slot67(Int value);
};

extern InGameUI *TheInGameUI;

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
void ControlBar::updateContextContestedStructureInventory()
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

// Target 0x0053EAEC..0x0053EB80, 149 bytes. The same-name BFME1
// updateContextStructureInventory is the semantic donor. Target bytes support
// the +0x74 ObjectID argument, +0x304 Team pointer, +0x250 contain interface,
// player-locality and relationship checks, gatherer query, and virtual calls.
// The donor supplies the method name and high-level operation; these target
// offsets, callee identities, and slot numbers are independently observed.
void ControlBar::updateContextStructureInventory()
{
	Object *object = m_6c->m_fc;
	Player *localPlayer = ThePlayerList->m_localPlayer;
	if (!object->isLocallyControlled() &&
		localPlayer->getRelationship(object->getTeam()) != (Relationship)1)
	{
		Int desiredGatherers = ((BuildListInfo *)object)->getDesiredGatherers();
		if (desiredGatherers)
		{
			GameMessage *message = MessageStreamSubsystem->appendMessage(0x3ed);
			message->appendObjectIDArgument(object->getID());
			((Rva0053EAECInGameUIView *)TheInGameUI)->slot67(desiredGatherers);
		}
		goto rva0053EAECdone;
	}

	Rva0053EB81Subject *contain = object->m_250;
	if (contain && m_80 != contain->slot69(false))
		rva0053E783(object, 0);
rva0053EAECdone:
	;
}

// Native 0x0053E4F1..0x0053E6E1, 496 bytes. WB 0x01123660 names the
// under-construction workflow; clean BFME1 ba7ddda7 ControlBarUnderConstruction
// supplies its source structure. Native evidence establishes 32 windows at
// +0xDC, the template +0x122 flag, overlay mode +0x29C and sink +0x2A0.
// Address-derived bindings retain unresolved target names and access levels.
// The real STLport vector owns the temporary window list; its existing
// pointer-vector push provider is reused through a storage/ABI view.
void ControlBar::rva0053E4F1(Object *objectUnderConstruction)
{
    if (!objectUnderConstruction) {
        if (theRadarWindowOverrideSource)
            ((Rva002D368E *)theRadarWindowOverrideSource)->rva002D368E();
        return;
    }
    for (int i=0; i<32; ++i) {
        if (commandWindows[i]) {
            commandWindows[i]->winHide(true);
            rva0031B641(commandWindows[i],0);
        }
    }
    bool overlay=((ConstructionOverlayModeView *)TheControlBar)->mode==1;
    _STL::vector<GameWindow *> windows;
    bool locallyControlled=objectUnderConstruction->isLocallyControlled();
    bool lit=(unsigned char)((Rva002A7DD0 *)ThePlayerList)->rva002A7DD0() || locallyControlled;
    const CommandButton *commandButton=findCommandButton("Command_CancelConstruction");
    GameWindow *win=commandWindows[0];
    if (!(((ConstructionObjectView *)objectUnderConstruction)->objectTemplate->flags&4)
        && commandButton && win) {
        win->winHide(false);
        if (overlay && lit) {
            win->winSetStatus(0x4000000);
            ((_STL::vector<const ModuleData *> *)&windows)->push_back(
                reinterpret_cast<const ModuleData *const &>(win));
        } else {
            win->winClearStatus(0x4000000);
        }
        rva0031B641(win,commandButton);
        if (locallyControlled) {
            win->winEnable(true);
            win->winClearStatus(0x40000000);
        } else if (((ConstructionPlayerListView *)ThePlayerList)->localPlayer->bfmeAskRV()) {
            win->winEnable(false);
            win->winClearStatus(0x40000000);
        } else {
            win->winEnable(false);
            win->winSetStatus(0x40000000);
        }
    }
    updateConstructionTextDisplay(objectUnderConstruction);
    ((Gen_003bcb40 *)this)->m((int)objectUnderConstruction);
    ExitInterface *exit=objectUnderConstruction->getObjectExitInterface();
    if (exit) showRallyPoint(((ConstructionExitView *)exit)->getRallyPoint());
    if (theRadarWindowOverrideSource)
        ((Rva002D363EOwner *)theRadarWindowOverrideSource)->rva002D363E((int)objectUnderConstruction);
    overlaySink->rva0053EFC7(*(WindowList *)&windows);
}

// Complete native53E6E1..53E6E6: unchanged-this, zero-argument tail call.
// The owned per-frame update invokes it in context4. Its historical method
// identity is unresolved; retain the existing address-derived binding.
void ControlBar::rva0053E6E1()
{
    rva0031D230();
}

// The inventory callback's native call53E727 reaches the shared null-return
// body atD43D0 with one cdecl Object pointer. WB1118900 also returns null.
// BFME1 ba7ddda7 context UI and the ZH structure-inventory source supply this
// helper's role, name and const parameter; the historical target declaration
// is unasserted. The emitted3-byte body is a complete byte/relocation twin.
__declspec(noinline) const Image *ControlBar::calculateVeterancyOverlayForObject(const Object *)
{
    return 0;
}
