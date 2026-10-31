// cl: /D__PLACEMENT_VEC_NEW_INLINE /FIzh_ascii.h /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/sweep_bfme1_outofline /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Include/Lib /ICode/Libraries/Include /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2
// stlport
// ?reset@W3DRadar@@UAEXXZ, retail 0x0004E2FA..0x0004E3A1 (167 bytes, EH). Zero Hour's
// W3DRadar::reset: the base Radar::reset, then under the DX8 thread lock the overlay and
// shroud textures' top surfaces are cleared to zero (rowed Get_Surface_Level 0x00132D70,
// clear 0x00116780, surface handle dtor 0x00176CB0) and the terrain texture reference is
// cleared (0x0004D75B); two primary-table steps (+0x20, +0x28) follow and the +0x1460 flag is
// set. The override is entered through the SubsystemInterface sub-object at +4 of the
// W3DRadar object, which the compiler adjusts for.
#include "always.h"
#undef W3DMPO_GLUE
#define W3DMPO_GLUE(ARGCLASS)
#define Matrix4x4 Matrix4  // BFME renamed it
#include "W3DDevice/Common/W3DRadar.h"

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

// Texture holder released and nulled by the rowed 0x0004D75B.
struct BfmeResetTextureRef
{
public:
	void clear();
	void *m_texture; // +0x00
};

void W3DRadar::reset()
{
	Radar::reset();
	BFMEDX8DeviceLock lock;
	m_terrainTexture.Get_Surface_Level().clear(false);
	m_overlayTexture.Get_Surface_Level().clear(false);
	reinterpret_cast<BfmeResetTextureRef *>(&m_terrainTextureAlt)->clear();
	rva0004F580();
	clearShroud();
	m_dirty = true;
}
