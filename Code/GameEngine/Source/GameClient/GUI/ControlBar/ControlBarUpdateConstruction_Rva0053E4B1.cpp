// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /D_STLP_NO_CSTD_FUNCTION_IMPORTS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include
// stlport
// Split from ControlBarUpdateConstruction.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// ?updateConstructionTextDisplay@ControlBar@@QAEXPAVObject@@@Z retail 0x0053E3E6 203 bytes. Donor is BFME1 ControlBarContextUI.cpp updateConstructionTextDisplay which pushes the same two literals ControlBar.wnd UnderConstructionDesc and CONTROLBAR UnderConstructionDesc and calls nameToKey winGetWindowFromId fetch format GadgetStaticTextSetText. Identity also from callers 0x0053E4B1 and 0x0053E4F1 comparing this plus 0x78 against obj plus 0x280. Recipe is donor verbatim with extern guard globals for linkability.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include "unicode_string.h"
#include "ascii_string.h"
#include "Lib/Coord3D.h"
namespace _STL { void __cdecl free(void *); }
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail copy of ?allocate@?$allocator@PBVModuleData@@@_STL@@QBEPAPBVModuleData@@IPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> const ModuleData **allocator<const ModuleData *>::allocate(size_t, const void *) const; }
// reserve is called out of line: bind it to its row (ModuleFactoryVectorReserve.cpp)
// instead of emitting this unit's copy.
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::reserve(unsigned int); }
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }

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

class Object;

#include "../../../../Include/GameClient/Bfme2GameWindow.h"

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
	virtual int constructionContainMax(); RVA0053EB81_VIRTUAL(pad29) RVA0053EB81_VIRTUAL(pad30) RVA0053EB81_VIRTUAL(pad31)
	RVA0053EB81_VIRTUAL(pad32) RVA0053EB81_VIRTUAL(pad33) RVA0053EB81_VIRTUAL(pad34) RVA0053EB81_VIRTUAL(pad35)
	RVA0053EB81_VIRTUAL(pad36) RVA0053EB81_VIRTUAL(pad37) RVA0053EB81_VIRTUAL(pad38) RVA0053EB81_VIRTUAL(pad39)
	RVA0053EB81_VIRTUAL(pad40) RVA0053EB81_VIRTUAL(pad41) RVA0053EB81_VIRTUAL(pad42) RVA0053EB81_VIRTUAL(pad43)
	RVA0053EB81_VIRTUAL(pad44) RVA0053EB81_VIRTUAL(pad45) RVA0053EB81_VIRTUAL(pad46) RVA0053EB81_VIRTUAL(pad47)
	RVA0053EB81_VIRTUAL(pad48) RVA0053EB81_VIRTUAL(pad49) RVA0053EB81_VIRTUAL(pad50) RVA0053EB81_VIRTUAL(pad51)
	RVA0053EB81_VIRTUAL(pad52) RVA0053EB81_VIRTUAL(pad53)
	virtual bool rva0053EB81SlotD8();
	RVA0053EB81_VIRTUAL(pad55)
	virtual class Player *rva0053EB81SlotE0();
	RVA0053EB81_VIRTUAL(pad57) RVA0053EB81_VIRTUAL(pad58) RVA0053EB81_VIRTUAL(pad59) RVA0053EB81_VIRTUAL(pad60)
	RVA0053EB81_VIRTUAL(pad61) RVA0053EB81_VIRTUAL(pad62) RVA0053EB81_VIRTUAL(pad63) RVA0053EB81_VIRTUAL(pad64)
	RVA0053EB81_VIRTUAL(pad65) RVA0053EB81_VIRTUAL(pad66) RVA0053EB81_VIRTUAL(pad67) virtual void constructionIterate(void (__cdecl *)(Object *, void *), void *, int);
	virtual int slot69(bool enabled);
	RVA0053EB81_VIRTUAL(pad70) RVA0053EB81_VIRTUAL(pad71) RVA0053EB81_VIRTUAL(pad72)
	RVA0053EB81_VIRTUAL(pad73) virtual int constructionContestedMax();
	virtual int rva0053EB81Slot12C();
};

#undef RVA0053EB81_VIRTUAL

class CommandButton;
class ModuleData;

class ExitInterface;
class PlayerList;
extern PlayerList *ThePlayerList;
class RadarWindowOverrideSource;
extern RadarWindowOverrideSource *theRadarWindowOverrideSource;
class WindowList;
class Rva0053ED1A { public: void rva0053EFC7(WindowList &); };
// Native portrait dispatch calls the shared empty RET4 at47A69C. This
// pre-existing opaque ABI binding does not identify ControlBar as its owner.
class ControlBar;
extern ControlBar *TheControlBar;
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
	__declspec(dllimport) __forceinline const Team *getTeam() const { return m_304; }
};

struct Rva0053E4B1Owner
{
	unsigned char m_pad[0xfc];
	Object *m_fc;
};

class Image;
#include "../../../../Include/Common/ThingTemplate.h"
class Rva002A7DDEArg;
class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;
// Reuse the existing lookup provider's eight-byte table-cell ABI. Native
// inventory callbacks store a window word followed by its contained ObjectID.
#include "../../../../Include/Common/ControlBarInventoryEntry.h"
extern ControlBarInventoryEntry ControlBarInventoryEntries[32];
const Image *getButtonImage(ThingTemplate *, Object *);
void GadgetButtonSetEnabledImage_Rva002C0433(GameWindow *, const Image *);
void Rva003284ED(GameWindow *, int);

class ControlBar
{
public:
	void updateConstructionTextDisplay(Object *obj);
	void setPortraitByObject(Object *obj);
protected:
    void populateUnderConstruction(Object *);
public:
    void setControlCommand(GameWindow *, const CommandButton *);
    const CommandButton *findCommandButton(const AsciiString &);
    void showRallyPoint(const Coord3D *);
	void rva0053E4B1();
	void rva0053E6E1();
	void updateContextContestedStructureInventory();
protected:
	void populateStructureInventory(Object *building, bool contested);
public:
	void switchToContext(int context, void *object);
	void rva0031D230();

protected:
	void updateContextStructureInventory();
    static void populateButtonProc(Object *, void *);
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

#include "../../../../Include/Common/PlayerList.h"

extern PlayerList *ThePlayerList;

enum Relationship
{
	Rva0053EAECRelationshipValue0 = 0
};

#include "../../../../Include/Common/TeamBFME2.h"

#include "../../../../Include/Common/Player.h"

#include "../../../../Include/Common/MessageStream.h"


// Target data row names this global MessageStreamSubsystem at RVA 0x00A00950
// (VA 0x00E00950); the BFME1 donor calls it TheMessageStream.
extern class MessageStream *TheMessageStream;

class InGameUI;

extern InGameUI *TheInGameUI;

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

#include "../../../../Include/Common/NameKeyGenerator.h"

extern NameKeyGenerator *TheNameKeyGenerator;

#include "../../../../Include/GameClient/GameWindowManager.h"

extern GameWindowManager *TheWindowManager;

#include "../../../../Include/GameClient/GameText.h"

extern GameTextInterface *TheGameText;

void __cdecl GadgetStaticTextSetText(GameWindow *win, UnicodeString text);

extern unsigned int g_00E05F60;


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

	Player *localPlayer = ThePlayerList->m_local;
	if (!subject->rva0053EB81SlotD8() || subject->rva0053EB81SlotE0() != localPlayer)
		return rva0031D230();
	if (m_80 != subject->rva0053EB81Slot12C())
		populateStructureInventory(object, true);
}



// Complete native53E6E1..53E6E6: unchanged-this, zero-argument tail call.
// The owned per-frame update invokes it in context4. Its historical method
// identity is unresolved; retain the existing address-derived binding.
void ControlBar::rva0053E6E1()
{
    rva0031D230();
}



