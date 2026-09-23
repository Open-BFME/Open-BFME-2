// cl: /O1 /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0CreateObjectDieModuleData@@QAE@XZ, retail 0x00485D88, 81 bytes.
// CreateObjectDie ModuleData default ctor over the pinned SEH intermediate
// base (??0Rva00253510@@QAE@XZ at 0x253510, shared with the Die family:
// DamageFiltered/KeepObjectDie/UpgradeDie precedent). Unlike the frameless
// DamageFiltered sibling this class carries destructible members, so the
// base and the derived both declare virtual dtors (KeepObjectDie/
// GeometryUpgrade precedent) and the compiler installs the vptr itself right
// after the base call; the DIR32 slot is patched from retail like any other
// vtable install, so no ??_7 pin is owed. The DebrisPortion int +0x38 is
// zeroed, the UpgradeRequired string +0x3C is nulled through its inline
// default ctor and cleared in the body through the rowed 0x36410 clear fold
// (Topple/Panic precedent: inline default ctor plus declared clear and
// dtor), and the CreationList vector +0x40 builds from the one-byte stack
// allocator temporary through the folded empty Vector_base at 0x211E58
// (the ObjectCreationNugget* element spelling reuses the existing pin there,
// the 29B body is T-independent). Virtuals plus the two members ride the EH
// state machine to states 0/2 exactly as retail (probe-proven: this member
// mix is the only one that brackets state 0/2 with the address hoist;
// non-virtual layouts stall at 0/1). /Oy- forces the ebp frame with the
// __EH_prolog prologue (GeometryUpgrade precedent). Size 0x4C (0x38 base +
// int + string + 12-byte vector) matches the 0x24C8C1 factory news in the
// rowed DieModuleDataFriendNew TU. Identity: ModuleFactory registers
// "CreateObjectDie" to factory 0x24C8C1 which sole-calls this ctor, the
// rowed buildFieldParse proc 0x485A74 carries the CreationList plus
// DebrisPortion plus UpgradeRequired table 0x00C4A928, and the next body at
// 0x485E19 (derived vtable 0xC4AA08) calls this ctor as its base then builds
// its +0x4C member through 0x485ADC.

#include <vector>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class ObjectCreationNugget;

class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

private:
	unsigned char m_pad[0x38 - 4];
};

class CreateObjectDieModuleData : public Rva00253510
{
public:
	CreateObjectDieModuleData();
	virtual ~CreateObjectDieModuleData();

private:
	int m_debrisPortion; // +0x38
	AsciiString m_upgradeRequired; // +0x3C
	_STL::vector<ObjectCreationNugget *> m_creationList; // +0x40
};

// ??0CreateObjectDieModuleData@@QAE@XZ @0x485D88
CreateObjectDieModuleData::CreateObjectDieModuleData()
	: m_debrisPortion(0)
	, m_upgradeRequired()
{
	m_upgradeRequired.clear();
}

// ??1CreateObjectDieModuleData@@UAE@XZ present-unmatched
CreateObjectDieModuleData::~CreateObjectDieModuleData()
{
}

// ??1Rva00253510@@UAE@XZ present-unmatched
Rva00253510::~Rva00253510()
{
}
