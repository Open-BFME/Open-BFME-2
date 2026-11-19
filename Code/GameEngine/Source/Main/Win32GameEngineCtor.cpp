// cl: /DNDEBUG /MD /EHsc
// platformsdk
//
// ??0Win32GameEngine@@QAE@XZ
// retail 0x00041D41, 29 bytes. Dedicated shard.
//
// ZH Win32GameEngine.cpp donor verbatim: base GameEngine ctor plus
// SetErrorMode(SEM_FAILCRITICALERRORS) saved to m_previousErrorMode at
// +0x60 plus Win32 vtable 0xBC2530. Base ctor is pinned at 0x22DA66;
// SetErrorMode resolves via its kernel32 import. Shard (not graft into
// CreateGameEngine.cpp) so the landed parent keeps calling out-of-line.

#include <windows.h>

class GameEngine
{
public:
	GameEngine();
	virtual ~GameEngine();
	virtual void m_unknown01();
	virtual void m_unknown02();
	virtual void m_unknown03();
	virtual void m_unknown04();
	virtual void m_unknown05();
	virtual void m_unknown06();
	virtual void m_unknown07();
	virtual void m_unknown08();
	virtual void reset();
	virtual void update();
	virtual void m_unknown11();
	virtual void m_unknown12();
	virtual void m_unknown13();
	virtual void init(int argc, char *argv[]);	// 0x0022E2E4
	virtual void m_unknown15();
	virtual bool rva00225AD5();
	virtual bool rva00225AFF();
	virtual void m_unknown18();
	virtual void m_unknown19();
	virtual void m_unknown20();
	virtual void m_unknown21();
	virtual bool isMultiplayerSession();	// 0x00225F76
	virtual void rva00042121();
	virtual void m_unknown24();
	virtual void setIsActive(bool active);

private:
	char m_padAfterVtable[0x60 - 4];
};

class Win32GameEngine : public GameEngine
{
public:
	Win32GameEngine();
	virtual ~Win32GameEngine();
	virtual void reset();	// 0x00041EBE
	virtual void update();	// 0x00041EC3
	virtual void rva00042121();	// 0x00042121

private:
	unsigned int m_previousErrorMode;
};

Win32GameEngine::Win32GameEngine()
{
	m_previousErrorMode = SetErrorMode(1);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?m_unknown01@GameEngine@@UAEXXZ=?loadPostProcess@UpdateModule@@MAEXXZ")
#pragma comment(linker, "/alternatename:?m_unknown03@GameEngine@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?m_unknown04@GameEngine@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?m_unknown05@GameEngine@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?m_unknown06@GameEngine@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?m_unknown08@GameEngine@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?m_unknown11@GameEngine@@UAEXXZ=?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")
#pragma comment(linker, "/alternatename:?m_unknown12@GameEngine@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?m_unknown18@GameEngine@@UAEXXZ=?friend_setList@GameMessage@@QAEXPAVGameMessageList@@@Z")
#pragma comment(linker, "/alternatename:?m_unknown19@GameEngine@@UAEXXZ=?getNext@?$CategoryModuleClass@$0A@@FXParticleSystem@@QBEPBV12@XZ")
#pragma comment(linker, "/alternatename:?m_unknown20@GameEngine@@UAEXXZ=?setForceWantingState@SupplyTruckAIUpdate@@UAEX_N@Z")
#pragma comment(linker, "/alternatename:?m_unknown21@GameEngine@@UAEXXZ=?get@Rva001DBA6DByteField@@QBEEXZ")
#pragma comment(linker, "/alternatename:?m_unknown24@GameEngine@@UAEXXZ=?get@Rva00041D5EByteField@@QBEEXZ")
#pragma comment(linker, "/alternatename:?setIsActive@GameEngine@@UAEX_N@Z=?setForceBusyState@SupplyTruckAIUpdate@@UAEX_N@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?m_unknown07@GameEngine@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")
#pragma comment(linker, "/alternatename:?m_unknown13@GameEngine@@UAEXXZ=?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")

// ??1Win32GameEngine@@UAE@XZ, retail 0x00041E9F..0x00041EB9 (26 bytes): Zero
// Hour's destructor, restoring the error mode the constructor saved, then
// the rowed GameEngine destructor 0x00225B9B as a tail call.
Win32GameEngine::~Win32GameEngine()
{
	SetErrorMode(m_previousErrorMode);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?m_unknown02@GameEngine@@UAEXXZ=?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")
#pragma comment(linker, "/alternatename:?m_unknown15@GameEngine@@UAEXXZ=?rva0022D290@GameEngine@@QAEXXZ")
