// cl: /GX- /O1 /G7 /arch:SSE /Ob2
// platformsdk
// Cold-slice global dword getters without vtable carriage (twin-free TU).
//
// Same shape as GlobalGetterSingles.cpp (mov eax,[mem] / ret, 6B) but kept in
// a separate TU so this batch does not contend with appends there. Each reads
// one .data dword global; identity unrecoverable, so globals and functions
// are address-derived (g_Va<VA> / Rva<RVA>Get). Opaque names witness only the
// address and the global. The /GX- line matches the sibling TUs (verified
// frameless six-byte shape).
// ww3d.cpp's private ?SyncTime@WW3D@@0IA and dx8wrapper.cpp's protected
// ?Light_Environment@DX8Wrapper@@1PAVLightEnvironmentClass@@A, read through
// TU-scoped friend views: real decorations, no alias, no second datum.
class LightEnvironmentClass;
class WW3D
{
	friend int Rva00083B7BGet(void);
	static unsigned int SyncTime;
};
class DX8Wrapper
{
	friend int Rva0014D241Get(void);
protected:
	static LightEnvironmentClass *Light_Environment;
};

// ?Rva00083B7BGet@@YAHXZ @ 0x00083b7b (6B) over 0x00DEC3CC.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00083B7BGet(void)
{
	return WW3D::SyncTime;
}

// g_Va00DB47EC: matched references place it at VA 0xdb47ec (retail .data initial value 2).
int g_Va00DB47EC = 2;

// ?Rva00094B87Get@@YAHXZ @ 0x00094b87 (6B) over 0x00DB47EC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00094B87Get(void)
{
	return g_Va00DB47EC;
}

// ?Rva0014D241Get@@YAHXZ @ 0x0014d241 (6B) over 0x00DEDA14.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0014D241Get(void)
{
	return (int)DX8Wrapper::Light_Environment;
}

// g_Va00DFE348: matched references place it at VA 0xdfe348 (zero-filled .bss).
int g_Va00DFE348;

// ?Rva0021913AGet@@YAHXZ @ 0x0021913a (6B) over 0x00DFE348.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0021913AGet(void)
{
	return g_Va00DFE348;
}

// AptSaveLoad::s_instance: matched references place it at VA 0xe032e0 (zero-filled .bss).
class AptSaveLoad { public: static AptSaveLoad *s_instance; };
// Named WB OpenScreen assertions559/560 and retail save-screen lifecycle
// identify this one pointer; public access is a reconstruction choice.
AptSaveLoad *AptSaveLoad::s_instance;

// ?Rva0023C54CGet@@YAHXZ @ 0x0023c54c (6B) over 0x00E032E0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0023C54CGet(void)
{
	return (int)AptSaveLoad::s_instance;
}

// g_Va00E0333C: matched references place it at VA 0xe0333c (zero-filled .bss).
int g_Va00E0333C;

// ?Rva00248D60Get@@YAHXZ @ 0x00248d60 (6B) over 0x00E0333C.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00248D60Get(void)
{
	return g_Va00E0333C;
}

class AptLanLobby { static AptLanLobby *s_instance; public: static AptLanLobby *Instance() { return s_instance; } };

// ?Rva00248D66Get@@YAHXZ @ 0x00248d66 (6B) over 0x00E03354.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00248D66Get(void)
{
	return (int)AptLanLobby::Instance();
}

// g_Va00DBB708: matched references place it at VA 0xdbb708 (retail .data initial value 1073741824).
int g_Va00DBB708 = 1073741824;

// ?Rva0027C220Get@@YAHXZ @ 0x0027c220 (6B) over 0x00DBB708.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0027C220Get(void)
{
	return g_Va00DBB708;
}

struct GlobalA04450;
extern GlobalA04450 *g_Va00A04450;

// ?Rva0029A26FGet@@YAHXZ @ 0x0029a26f (6B) over 0x00E04450.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0029A26FGet(void)
{
	return (int)g_Va00A04450;
}

// g_Va00E04478: matched references place it at VA 0xe04478 (zero-filled .bss).
int g_Va00E04478;

// ?Rva0031AA00Get@@YAHXZ @ 0x0031aa00 (6B) over 0x00E04478.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0031AA00Get(void)
{
	return g_Va00E04478;
}

// g_Va00E032C8: matched references place it at VA 0xe032c8 (zero-filled .bss).
int g_Va00E032C8;

// ?Rva00320607Get@@YAHXZ @ 0x00320607 (6B) over 0x00E032C8.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00320607Get(void)
{
	return g_Va00E032C8;
}

// VA 0x00DBD0F0 is PolygonTrigger's private ?s_currentID@PolygonTrigger@@0HA,
// defined in PolygonTrigger.cpp (initial 1); reached through a friend view.
class PolygonTrigger
{
	friend int Rva00328A65Get(void);
	static int s_currentID;
};

// ?Rva00328A65Get@@YAHXZ @ 0x00328a65 (6B) over 0x00DBD0F0.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00328A65Get(void)
{
	return PolygonTrigger::s_currentID;
}

class AptQuitMenu;
extern AptQuitMenu *TheAptQuitMenu;

// ?Rva00376D17Get@@YAHXZ @ 0x00376d17 (6B) over 0x00E04910.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D17Get(void)
{
	return (int)TheAptQuitMenu;
}

extern int g_Va00A04908;

// ?Rva00376D1DGet@@YAHXZ @ 0x00376d1d (6B) over 0x00E04908.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D1DGet(void)
{
	return g_Va00A04908;
}

class AptStrategicMessageBox {private: static AptStrategicMessageBox *s_instance; friend int Rva00376D23Get(void);};
// (int)AptStrategicMessageBox::s_instance: matched references place it at VA 0xe05fac (zero-filled .bss).


// ?Rva00376D23Get@@YAHXZ @ 0x00376d23 (6B) over 0x00E05FAC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00376D23Get(void)
{
	return (int)AptStrategicMessageBox::s_instance;
}

// g_Va00E032FC: matched references place it at VA 0xe032fc (zero-filled .bss).
int g_Va00E032FC;

// ?Rva0038071EGet@@YAHXZ @ 0x0038071e (6B) over 0x00E032FC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0038071EGet(void)
{
	return g_Va00E032FC;
}

class AptMessenger { public: static AptMessenger *s_instance; };

// ?Rva00380724Get@@YAHXZ @ 0x00380724 (6B) over 0x00E046B8.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00380724Get(void)
{
	return (int)AptMessenger::s_instance;
}

class DisconnectMenu;
extern DisconnectMenu *TheDisconnectMenu;

// ?Rva0040596CGet@@YAHXZ @ 0x0040596c (6B) over 0x00E048D0.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0040596CGet(void)
{
	return (int)TheDisconnectMenu;
}
struct Rva00517048;
extern Rva00517048 *g_Va00A04904;

// ?Rva00415E8AGet@@YAHXZ @ 0x00415e8a (6B) over 0x00E04904.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00415E8AGet(void)
{
	return (int)g_Va00A04904;
}

// g_Va00E0330C: matched references place it at VA 0xe0330c (zero-filled .bss).
int g_Va00E0330C;

// ?Rva0043C6E4Get@@YAHXZ @ 0x0043c6e4 (6B) over 0x00E0330C.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0043C6E4Get(void)
{
	return g_Va00E0330C;
}

extern int g_Va00E06398;

// ?Rva0044C5C1Get@@YAHXZ @ 0x0044c5c1 (6B) over 0x00E06398.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0044C5C1Get(void)
{
	return g_Va00E06398;
}

// BfmeLogicFramesPerSecond: matched references place it at VA 0xdba4e4 (retail .data initial value 5).
int BfmeLogicFramesPerSecond = 5;

// ?Rva004B879DGet@@YAHXZ @ 0x004b879d (6B) over 0x00DBA4E4.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004B879DGet(void)
{
	return BfmeLogicFramesPerSecond;
}

// Current AptOnlineCustomMatch: its ctor005A5BC7 stores this, and dtor005A0009
// clears this same value. Preserve the existing 32-bit address storage ABI.
int g_currentAptOnlineCustomMatch;

// ?Rva004FDA11Get@@YAHXZ @ 0x004fda11 (6B) over 0x00E063EC.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004FDA11Get(void)
{
	return g_currentAptOnlineCustomMatch;
}

// g_Va00DFEFD8: matched references place it at VA 0xdfefd8 (zero-filled .bss).
int g_Va00DFEFD8;

// ?Rva0050B426Get@@YAHXZ @ 0x0050b426 (6B) over 0x00DFEFD8.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0050B426Get(void)
{
	return g_Va00DFEFD8;
}

// g_Va00E06394: matched references place it at VA 0xe06394 (zero-filled .bss).
int g_Va00E06394;

// ?Rva005114B7Get@@YAHXZ @ 0x005114b7 (6B) over 0x00E06394.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005114B7Get(void)
{
	return g_Va00E06394;
}

// g_Va00E06544: matched references place it at VA 0xe06544 (zero-filled .bss).
int g_Va00E06544;

// ?Rva00516E0AGet@@YAHXZ @ 0x00516e0a (6B) over 0x00E06544.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00516E0AGet(void)
{
	return g_Va00E06544;
}

// g_Va00E06548: matched references place it at VA 0xe06548 (zero-filled .bss).
int g_Va00E06548;

// ?Rva00516E48Get@@YAHXZ @ 0x00516e48 (6B) over 0x00E06548.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00516E48Get(void)
{
	return g_Va00E06548;
}

// g_Va00E0492C: matched references place it at VA 0xe0492c (zero-filled .bss).
int g_Va00E0492C;

// ?Rva0051AEE9Get@@YAHXZ @ 0x0051aee9 (6B) over 0x00E0492C.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0051AEE9Get(void)
{
	return g_Va00E0492C;
}

// g_Va00E046BC: matched references place it at VA 0xe046bc (zero-filled .bss).
int g_Va00E046BC;

// ?Rva005AE5E8Get@@YAHXZ @ 0x005ae5e8 (6B) over 0x00E046BC.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005AE5E8Get(void)
{
	return g_Va00E046BC;
}

// g_Va00E06480: matched references place it at VA 0xe06480 (zero-filled .bss).
int g_Va00E06480;

// ?Rva005B901EGet@@YAHXZ @ 0x005b901e (6B) over 0x00E06480.
// Follows a ret-with-pop (prev C2), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005B901EGet(void)
{
	return g_Va00E06480;
}

// g_Va00E06550: matched references place it at VA 0xe06550 (zero-filled .bss).
int g_Va00E06550;

// ?Rva005BA33EGet@@YAHXZ @ 0x005ba33e (6B) over 0x00E06550.
// Follows a ret (prev C3), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva005BA33EGet(void)
{
	return g_Va00E06550;
}

extern int g_Va00E0ABB0;

// ?Rva006891A0Get@@YAHXZ @ 0x006891a0 (6B) over 0x00E0ABB0.
// Follows padding (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006891A0Get(void)
{
	return g_Va00E0ABB0;
}

class AptValue; extern AptValue *gpUndefinedValue;

// ?Rva006F5100Get@@YAHXZ @ 0x006f5100 (6B) over 0x00E18078.
// Follows padding (prev CC), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva006F5100Get(void)
{
	return (*(int *)&gpUndefinedValue);
}


class BfmeObjELB;
extern BfmeObjELB *g_bfmeObjELB;

// ?Rva00415E90Get@@YAHXZ @ 0x00415e90 (6B) over 0x00E062EC.
// Follows a ret (prev C3); next is a frameless fn start; no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00415E90Get(void)
{
	return (int)g_bfmeObjELB;
}

struct GlobalA046B4;
extern GlobalA046B4 *g_Va00A046B4;

// ?Rva0050E9CDGet@@YAHXZ @ 0x0050e9cd (6B) over 0x00E046B4.
// Follows a ret-with-pop (prev C2 0C 00); next is a frameless fn start;
// phase-clean in 512B window; one E8 caller at 0x002D68D6.
// Opaque address-derived name.
int Rva0050E9CDGet(void)
{
	return (int)g_Va00A046B4;
}

// ?g_Va00E0ABB0@@3HA: matched references place it at VA 0xe0abb0; also referenced as ?g_bfmeThingUCHead@@3PAVBfmeNodeUC@@A.
int g_Va00E0ABB0;
// AptMessenger::s_instance owns the native messenger pointer at VA 0x00E046B8.
AptMessenger *AptMessenger::s_instance;
// ?g_Va00E06398@@3HA: matched references place it at VA 0xe06398 (the open file transfer popup).
int g_Va00E06398;
// ?g_Va00E18078@@3HA: the global at VA 0xe18078 is ?g_aptUndefinedAtE18078@@3PAVBfmeAptValue006DCD20@@A.

// Clean BF1 9cbfb551fe Common/Rva000CBC30Get.cpp semantic donor, normal O1/SSE/G7.
// Native 00380517..00380523 has its own complete RET boundary and establishes
// receiver0 float pointer, indexed FLD, RET4. Original owner and full array bound remain
// unresolved; this separate address-owned view models only observed accesses.
class Rva00380517Array {
public: float getValue(int index);
private: float *values;
};
float Rva00380517Array::getValue(int index) { return values[index]; }

// TerrainLogic water-update view at secondary this+4. BF1 donor 874e38488
// TerrainLogicUpdate.cpp supplies the water-transition algorithm; target 285B
// fixes flag 0x40, records 0x64/count 0x564 and visual slot 17. Keep it beside the
// established rate getter so ordinary /Ob2 inlining reuses its single data
// owner and introduces no address-global declaration or alias.
#include "GameLogicObjectLookupView.h"
typedef bool Bool;
typedef float Real;
typedef int Int;
extern GameLogic *TheGameLogic;
#include <windows.h>

struct WaterHandle;
struct TerrainWaterDispatch {
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
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
 virtual void setWaterHeight(const WaterHandle *,Real,Real,Bool);
};
class TerrainVisual {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void slot14();
 virtual void slot15();
 virtual void slot16();
 virtual void update();
};
// Retail 0x0027CE71 loads VA 0x00DFF080 then calls vslot +0x44.
// Use the existing storage owner; TheTerrainVisual in other units denotes
// the distinct campaign-manager global at VA 0x00DFDC8C.
class G00DFF080Obj;
extern G00DFF080Obj *TheTerrainVisual;
// Native TerrainLogic subsystem table BFB28C slot10 names this update role.
// This is an entry-ABI view: ECX is the secondary SubsystemInterface at +4,
// so the observed flag/record/count offsets below are relative to that entry,
// rather than offsets from TerrainLogic's complete-object Snapshot pointer.
class TerrainLogic {
public:
 virtual void update();
 char pad04[0x40-4];
 Bool m_bridgeDamageStatesChanged;
 char pad41[0x64 - 0x41];
 struct DynamicWaterEntry {
  const WaterHandle *waterTable;
  Real changePerFrame, targetHeight, damageAmount, currentHeight;
 } m_waterToUpdate[64];
 Int m_numWaterToUpdate;
};
void TerrainLogic::update( void )
{
	m_bridgeDamageStatesChanged = false;

	if( m_numWaterToUpdate )
	{
		const WaterHandle *water;
		Real changePerFrame, damageAmount, targetHeight, currentHeight;
		Bool finalTransition,
				 doDamageThisFrame = (TheGameLogic->getFrame() % Rva004B879DGet()) == 0;

		for( Int i = m_numWaterToUpdate - 1; i >= 0; --i )
		{
			water = m_waterToUpdate[ i ].waterTable;
			changePerFrame = m_waterToUpdate[ i ].changePerFrame;
			targetHeight = m_waterToUpdate[ i ].targetHeight;
			damageAmount = m_waterToUpdate[ i ].damageAmount;
			currentHeight = m_waterToUpdate[ i ].currentHeight;

			finalTransition = FALSE;
			if( changePerFrame > 0 )
			{
				if( currentHeight + changePerFrame >= targetHeight )
					finalTransition = TRUE;
			}
			else
			{
				if( currentHeight + changePerFrame <= targetHeight )
					finalTransition = TRUE;
			}

			if( finalTransition == TRUE )
			{
				reinterpret_cast<TerrainWaterDispatch *>((char *)this - 4)->setWaterHeight( water, targetHeight, damageAmount, TRUE );
				for( Int j = i; j < m_numWaterToUpdate; j++ )
					m_waterToUpdate[ i ] = m_waterToUpdate[ j ];
				m_numWaterToUpdate -= 1;
			}
			else
			{
				if( doDamageThisFrame == FALSE )
					damageAmount = 0.0f;
				currentHeight += changePerFrame;
				m_waterToUpdate[ i ].currentHeight = currentHeight;
				reinterpret_cast<TerrainWaterDispatch *>((char *)this - 4)->setWaterHeight( water, currentHeight, damageAmount, FALSE );
			}
		}
	}
	reinterpret_cast<TerrainVisual *>(TheTerrainVisual)->update();
}
