// cl: /O1 /GX /DNDEBUG /MD
//
// ??0BuildingBehaviorModuleData@@QAE@XZ, retail 0x00456489, 65 bytes.
// ModuleData default ctor: vtable 0xC40798 plus a four-element window-name
// member at +0x08 built in place through the compiler's eh vector
// constructor iterator (rowed ??_L at 0x629512). The table at 0xC40748
// (NightWindowName@8, FireWindowName@0x14, GlowWindowName@0x20,
// FireName@0x2C) proves four 12-byte elements; the factory at 0x24ABAF
// news 0x38, so the layout is vtable plus a 4-byte gap plus the array.
// The element setup/teardown addresses the helper takes travel as DIR32
// slots the patcher copies from retail (CrushDieModuleDataCtor precedent),
// so element linkage stays local here. Each entry leads with its window
// name (AsciiString with inline null init and declared teardown resolving
// through the folded 0x36410 pin, Topple precedent); the trailing 8 bytes
// are opaque. The opaque member teardown is also what arms the single EH
// state: with fully-defined elements the toolchain proves non-throwing
// and drops the retail frame. Member-array setup hoists above the explicit
// vtable store while the helper call stays below it, reproducing the retail
// order. Identity: ModuleFactory registers "BuildingBehavior" to factory
// 0x24ABAF which sole-calls this ctor; the rowed pool key at 0x4561C1 ends
// where the rowed parse proc at 0x456206 begins.

// TU-local string with inline null init; the declared teardown resolves
// through the existing folded AsciiString pin at 0x36410.
class AsciiString
{
public:
	AsciiString() : m_data(0) {}
	~AsciiString();

private:
	char *m_data;
};

// A window-name entry: 12 bytes (retail element size).
class BuildingWindowName
{
public:
	BuildingWindowName() {}
	~BuildingWindowName() {}

private:
	AsciiString m_name; // +0x00, the parsed window name
	unsigned char m_pad[8]; // +0x04, opaque trailing bytes
};

// Empty base (inline-empty ctor plus declared-only dtor): load-bearing for
// the EH state machine, advancing the state to 0 with no emitted code so
// the array construction below is bracketed exactly as retail (Topple
// precedent). The declared dtor is never referenced from this TU.
class BuildingBehaviorModuleDataBase
{
public:
	BuildingBehaviorModuleDataBase() {}
	~BuildingBehaviorModuleDataBase();

private:
};

class BuildingBehaviorModuleData : public BuildingBehaviorModuleDataBase
{
public:
	BuildingBehaviorModuleData();

private:
	void *m_vtable; // +0x00, explicit store (no virtuals declared)
	int m_unused04; // +0x04, unstored gap (DemoTrap precedent)
	BuildingWindowName m_windows[4]; // +0x08
};

// ??0BuildingBehaviorModuleData@@QAE@XZ @0x00456489
BuildingBehaviorModuleData::BuildingBehaviorModuleData()
	: m_vtable(reinterpret_cast<void *>(0xC40798))
{
}
