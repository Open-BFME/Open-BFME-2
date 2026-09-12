// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport

// Evidence: retail 0x002D7B6B (76 bytes) references the string literal
// "ControlBar.wnd:LeftHUD", which ZH's Radar.cpp uses only in
// Radar::newMap():
//   Int id = NAMEKEY( "ControlBar.wnd:LeftHUD" );
//   m_radarWindow = TheWindowManager->winGetWindowFromId( NULL, id );
// The retail body prepends a BFME2-only branch not present in ZH: a
// singleton at VA 0xDFF028 is consulted first (two thiscall accessors at
// 0x2D35D6 and 0x2D35CF, pinned as an opaque "radar window override
// source" -- its real class is not recoverable from ZH/BFME1 source) and,
// only when it reports no override, the NAMEKEY/winGetWindowFromId path
// above runs. m_radarWindow sits at Radar+0x1430 (padded rather than
// reproducing every preceding member, since none of them are touched
// here); the retail function ends cleanly right after the assignment, so
// this 76-byte body is the whole of BFME2's Radar::newMap.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "Common/NameKeyGenerator.h"

class GameWindow;

// The retail call dispatches winGetWindowFromId through vtable slot 0xF0
// (slot 60), five slots further out than ZH's own GameWindowManager.h
// places it -- BFME2 inserted extra virtuals earlier in the class. The
// sixty preceding slots are not reconstructed here; only their count
// (to hold winGetWindowFromId at the right offset) is evidenced by this
// call site.
class GameWindowManager
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void _M_slot_08();
	virtual void _M_slot_0c();
	virtual void _M_slot_10();
	virtual void _M_slot_14();
	virtual void _M_slot_18();
	virtual void _M_slot_1c();
	virtual void _M_slot_20();
	virtual void _M_slot_24();
	virtual void _M_slot_28();
	virtual void _M_slot_2c();
	virtual void _M_slot_30();
	virtual void _M_slot_34();
	virtual void _M_slot_38();
	virtual void _M_slot_3c();
	virtual void _M_slot_40();
	virtual void _M_slot_44();
	virtual void _M_slot_48();
	virtual void _M_slot_4c();
	virtual void _M_slot_50();
	virtual void _M_slot_54();
	virtual void _M_slot_58();
	virtual void _M_slot_5c();
	virtual void _M_slot_60();
	virtual void _M_slot_64();
	virtual void _M_slot_68();
	virtual void _M_slot_6c();
	virtual void _M_slot_70();
	virtual void _M_slot_74();
	virtual void _M_slot_78();
	virtual void _M_slot_7c();
	virtual void _M_slot_80();
	virtual void _M_slot_84();
	virtual void _M_slot_88();
	virtual void _M_slot_8c();
	virtual void _M_slot_90();
	virtual void _M_slot_94();
	virtual void _M_slot_98();
	virtual void _M_slot_9c();
	virtual void _M_slot_a0();
	virtual void _M_slot_a4();
	virtual void _M_slot_a8();
	virtual void _M_slot_ac();
	virtual void _M_slot_b0();
	virtual void _M_slot_b4();
	virtual void _M_slot_b8();
	virtual void _M_slot_bc();
	virtual void _M_slot_c0();
	virtual void _M_slot_c4();
	virtual void _M_slot_c8();
	virtual void _M_slot_cc();
	virtual void _M_slot_d0();
	virtual void _M_slot_d4();
	virtual void _M_slot_d8();
	virtual void _M_slot_dc();
	virtual void _M_slot_e0();
	virtual void _M_slot_e4();
	virtual void _M_slot_e8();
	virtual void _M_slot_ec();
	virtual GameWindow *winGetWindowFromId( GameWindow *window, Int id );
};

extern GameWindowManager *TheWindowManager;

// Identity unknown -- not present in ZH/BFME1 Radar.cpp. Reconstructed
// purely from this call site: a global object (VA 0xDFF028) whose
// [this+0x10] sub-object exposes a 3-bit flag test (0x2D35D6, returns
// Bool) and a cached pointer (0x2D35CF, returns void*).
class RadarWindowOverrideSource
{
public:
	Bool hasOverrideWindow( void ) const;
	GameWindow *getOverrideWindow( void ) const;
};

extern RadarWindowOverrideSource *theRadarWindowOverrideSource;

class Radar
{
public:
	void newMap( void );

private:
	char m_pad[0x1430];
	GameWindow *m_radarWindow;
};

// Retail's newMap takes no stack argument (a plain "ret", not "ret 4") --
// unlike ZH's `void newMap(TerrainLogic *terrain)`, so the terrain-extent
// half of ZH's function was evidently moved elsewhere in BFME2 and this
// body is left with just the radar-window lookup.
void Radar::newMap( void )
{
	if ( theRadarWindowOverrideSource && theRadarWindowOverrideSource->hasOverrideWindow() )
	{
		m_radarWindow = theRadarWindowOverrideSource->getOverrideWindow();
	}
	else
	{
		Int id = NAMEKEY( "ControlBar.wnd:LeftHUD" );
		m_radarWindow = TheWindowManager->winGetWindowFromId( NULL, id );
	}
}
