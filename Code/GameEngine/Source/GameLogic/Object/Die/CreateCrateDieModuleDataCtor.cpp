// cl: /O1 /MD /GX /DNDEBUG /Oy- /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0CreateCrateDieModuleData@@QAE@XZ, retail 0x002572EE, 74 bytes.
// CreateCrateDie ModuleData default ctor over the pinned SEH intermediate
// base (??0Rva00253510@@QAE@XZ at 0x253510, shared with the Die family).
// The base and the derived both declare virtual dtors (KeepObjectDie/
// CreateObjectDieModuleDataCtor precedent) and the compiler installs the
// vptr itself right after the base call; the DIR32 slot is patched from
// retail like any other vtable install, so no ??_7 pin is owed. The single
// member is the crate-name list +0x38, a _STL::list<AsciiString> (BFME1
// donor field m_crateNameList, an AsciiStringList) built from the one-byte
// stack allocator temporary through the folded _List_base ctor at 0x4EC36C
// (the AsciiString-element spelling reuses the existing pin there) and
// cleared in the body through the rowed _List_base clear at 0x239D49. The
// base plus the list ride the EH state machine to states 0/1 exactly as
// retail (probe-proven: virtual base plus one list reaches 0/1; a
// non-virtual base stalls with no pre-clear state). /Oy- forces the ebp
// frame with the __EH_prolog prologue. Size 0x3C (0x38 base + 4-byte list:
// STLport lists are a single head pointer) matches the 0x25739D factory
// news in the rowed DieModuleDataFriendNew TU. Identity: ModuleFactory
// registers "CreateCrateDie" to factory 0x25739D which sole-calls this ctor
// (pin 4079, superseded by this row).

#include <list>

class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	void clear();
	~AsciiString();

private:
	void *m_data;
};

class Rva00253510
{
public:
	Rva00253510();
	virtual ~Rva00253510();

private:
	unsigned char m_pad[0x38 - 4];
};

class CreateCrateDieModuleData : public Rva00253510
{
public:
	CreateCrateDieModuleData();
	virtual ~CreateCrateDieModuleData();

private:
	_STL::list<AsciiString> m_crateNameList; // +0x38
};

// ??0CreateCrateDieModuleData@@QAE@XZ @0x2572EE
CreateCrateDieModuleData::CreateCrateDieModuleData()
{
	m_crateNameList.clear();
}

// ??1CreateCrateDieModuleData@@UAE@XZ present-unmatched
CreateCrateDieModuleData::~CreateCrateDieModuleData()
{
}

// ??1Rva00253510@@UAE@XZ present-unmatched
Rva00253510::~Rva00253510()
{
}
