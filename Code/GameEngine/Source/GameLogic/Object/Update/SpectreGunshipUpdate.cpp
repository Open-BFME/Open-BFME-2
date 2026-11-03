// cl: /Ireference/shims/zh_outofline /Ireference/shims/partitionfilterzh /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
// This donor Object view does not use native disabled-mask +0x1C8.
// Keep its unrecovered callers separate from native Object::isDisabled.
#define isDisabled spectreGunshipUpdateDonorIsDisabled
// stlport
// Ported verbatim from the Generals Zero Hour reference (GameEngine/Source/GameLogic/Object/Update/SpectreGunshipUpdate.cpp); this unit had no counterpart under Code/.
#define Matrix4x4 Matrix4  // BFME renamed it
#define __PLACEMENT_VEC_NEW_INLINE  // always.h/GameMemory.h define array placement-new themselves
// stlport
// BFME 2 has no SpectreGunshipUpdate: this unit carried Zero Hour's port, and
// its one row is the 10-byte setter at 0x00238D83 (`mov eax,[esp+4];
// mov [ecx+0x64],eax; ret 4`), rowed as Zero Hour's inline
// SpectreGunshipUpdate::setLogicalStatus. The unrowed Zero Hour bodies
// (initiateIntentToDoSpecialPower, the module data's field table and the
// PartitionFilterLiveMapEnemies filter) referenced names no object defines
// (friend_enableAfterburners, Drawable::clearAndSetModelConditionState) and
// emitted a non-retail Locomotor::setFlag copy; they are gone.
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#define DEFINE_DEATH_NAMES

// INCLUDES ///////////////////////////////////////////////////////////////////////////////////////
#include "Common\GameAudio.h"
#include "Common\ThingTemplate.h"
#include "Common\ThingFactory.h"
#include "Common\Player.h"
#include "Common\PlayerList.h"
#include "Common\Xfer.h"
#include "Common\ClientUpdateModule.h"

#include "GameClient\ControlBar.h"
#include "GameClient\GameClient.h"
#include "GameClient\Drawable.h"
#include "GameClient\ParticleSys.h"
#include "GameClient\FXList.h"
#include "GameClient/ParticleSys.h"

#include "GameLogic\Locomotor.h"
#include "GameLogic\GameLogic.h"
#include "GameLogic\PartitionManager.h"
#include "GameLogic\Object.h"
#include "GameLogic/PartitionFilterZh.h"
#include "GameLogic\ObjectIter.h"
#include "GameLogic\Weaponset.h"
#include "GameLogic\Weapon.h"
#include "GameLogic\TerrainLogic.h"
#include "GameLogic\Module\SpecialPowerModule.h"
#include "GameLogic\Module\SpectreGunshipUpdate.h"
#include "GameLogic\Module\PhysicsUpdate.h"
#include "GameLogic\Module\LaserUpdate.h"
#include "GameLogic\Module\ActiveBody.h"
#include "GameLogic\Module\AIUpdate.h"
#include "GameLogic\Module\ContainModule.h"

// setLogicalStatus is a protected inline, and its Zero Hour callers are gone.
// A pointer to it needs the derived class's access and a dynamic initializer
// (the class has multiple bases), so this unit keeps it emitted through one
// call from a derived class's static member instead. That struct is never
// constructed, and neither it nor the function is retail code.
struct BfmeSpectreGunshipUpdateInlineAnchor : public SpectreGunshipUpdate
{
	static void keepSetLogicalStatus(BfmeSpectreGunshipUpdateInlineAnchor *update);
};
// ?keepSetLogicalStatus@BfmeSpectreGunshipUpdateInlineAnchor@@SAXPAU1@@Z absent-from-retail
void BfmeSpectreGunshipUpdateInlineAnchor::keepSetLogicalStatus(BfmeSpectreGunshipUpdateInlineAnchor *update)
{
	update->setLogicalStatus(GUNSHIP_STATUS_INSERTING);
}
