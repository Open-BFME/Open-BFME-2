// ??0InvisibilityUpdateModuleData@@QAE@XZ
// partial score=0.96 date=2026-09-24
// ??0InvisibilityUpdateModuleData@@QAE@XZ
// partial score=0.96 date=2026-09-24
// cl: /O1 /arch:SSE /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??0InvisibilityUpdateModuleData@@QAE@XZ, retail 0x00255474, 198 bytes.
// Invisibility Update ModuleData: own table at 0x00C52468 carries
// InvisibilityNugget at +0x08, UpdatePeriod at +0xC0, RequiredUpgrades at
// +0xC4, ForbiddenUpgrades at +0x144, Broadcast at +0x1C4,
// BroadcastObjectFilter at +0x1C8, BroadcastRange at +0x1CC,
// StartsActive at +0x1D0 and the move-to-stealthy voice name at +0x1D4;
// the ModuleData factory at 0x0025553A news 0x1DC with this ctor as its
// sole raw caller and the proc at 0x004A381C is rowed, and the
// InvisibilityUpdate behavior pool key at 0x004A393C sits in the same
// cluster. 194/198 positional, single wall: retail keeps the EH state-3
// store late (inside the first memset call setup, just before the call)
// while every probed shape flushes it early (just before the first
// clear80 call). All calls, stores, frame, epilogue and tail otherwise
// identical (masked). Zero new pins (all callees resolve through existing
// rows and pins: 0x2542F3 ctor, clear80 0x1EAE6F, construct 0x3623E5,
// memset 0x6291AE, FixedStorage copy 0x4543D, applyFilter 0x362120).
// PROVEN (decisive probe matrix, build/probe_matrix.py recipe):
// (1) SILENT-STATE-FLUSH: call-free (implicit/trivial) dtor-member
// completions flush their state before the next call of ANY kind
// (throw() irrelevant); call-construction states flush just-in-time
// before the next THROWING call (throw() suppresses).
// (2) Entry store-0 needs the empty UpdateModuleData base (inline ctor
// plus declared-only dtor, silent, Topple pattern); without a base the
// first store lands post-m08-call instead of pre-vtable.
// (3) Init-listed inline-ctor wrapper members emit their stores in init
// position (they do NOT sink past body calls), so tail-member wrappers
// cannot fix the flush.
// (4) Empty-dtor locals do NOT advance states (P12).
// Refuted: wrapper tail members (early stores plus early flush), member
// dtor removal (loses all states, 194B), filter-only dtor (flush-1
// early), /O2, /G6, /G7, /Os, /Ot, /Oy-, barrier, volatile, decl-order
// and reorder variants. The three late states need a completion
// mechanism positioned after the setup calls with no visible calls and
// no early flush; no such mechanism was found (explicit member
// construction is stateless per CallHelp law, placement-new guards,
// temps are untracked, locals emit dtor calls). Do NOT retry blind.
// t=120 model=peppy-penguin score=0.96 stash=reverse/attempts/0x00255474.cpp

#include <string.h>

extern "C" void *memset(void *, int, unsigned int);

class BfmeFixedStorage0004543D
{
public:
	BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other);

private:
	unsigned char m_bytes[28];
};

class Rva002542F3Member
{
public:
	Rva002542F3Member();

private:
	unsigned char m_data[0x9C];
};

class Rva001EAE6FHelper
{
public:
	Rva001EAE6FHelper *clear80() throw();
	~Rva001EAE6FHelper();

private:
	char m_pad[0x80];
};

class Rva003623E5Member
{
public:
	void construct() throw();
	~Rva003623E5Member();

private:
	int m_filterData;
};

class Rva003623E5Filter
{
public:
	void applyFilter(BfmeFixedStorage0004543D storage);
};

class UpdateModuleData
{
public:
	UpdateModuleData();
	~UpdateModuleData();
};

inline UpdateModuleData::UpdateModuleData()
{
}

class InvisibilityUpdateModuleData : public UpdateModuleData
{
public:
	InvisibilityUpdateModuleData();

private:
	void *m_vtable; // +0x00
	int m_unused04; // +0x04, retail never stores it
	Rva002542F3Member m_nugget; // +0x08
	unsigned char m_padA4[0xC0 - 0x08 - 0x9C]; // +0xA4
	int m_updatePeriod; // +0xC0
	Rva001EAE6FHelper m_requiredUpgrades; // +0xC4
	Rva001EAE6FHelper m_forbiddenUpgrades; // +0x144
	bool m_broadcast; // +0x1C4
	unsigned char m_pad1C5[3];
	Rva003623E5Member m_filter; // +0x1C8
	float m_broadcastRange; // +0x1CC
	bool m_startsActive; // +0x1D0
	unsigned char m_pad1D1[3];
	int m_voiceMoveName; // +0x1D4
	int m_voicePad; // +0x1D8
};

// ??0InvisibilityUpdateModuleData@@QAE@XZ @0x00255474
InvisibilityUpdateModuleData::InvisibilityUpdateModuleData()
	: m_vtable((void *)0x00BF3640)
	, m_nugget()
	, m_updatePeriod(10)
	, m_requiredUpgrades()
	, m_forbiddenUpgrades()
	, m_filter()
{
	m_requiredUpgrades.clear80();
	m_forbiddenUpgrades.clear80();
	m_broadcast = false;
	m_filter.construct();
	m_broadcastRange = 0.0f;
	m_startsActive = false;
	m_voiceMoveName = 0;
	m_voicePad = 0;
	memset(&m_requiredUpgrades, 0, 0x80);
	memset(&m_forbiddenUpgrades, 0, 0x80);
	reinterpret_cast<Rva003623E5Filter *>(&m_filter)->applyFilter(
		BfmeFixedStorage0004543D(*reinterpret_cast<const BfmeFixedStorage0004543D *>(0x00DFEFA4)));
}
