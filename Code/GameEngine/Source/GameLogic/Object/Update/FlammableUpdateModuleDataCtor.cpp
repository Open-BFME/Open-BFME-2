// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_flammableupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum /Ireference/shims/moduledata /ICode/GameEngine/Include
// stlport
//
// ??0FlammableUpdateModuleData@@QAE@XZ, retail 0x0048D541..0x0048D60C (203
// bytes, EH): the FlammableUpdateModuleData constructor; the factory
// friend_newModuleData 0x0024D068 news 0x58 and calls it, and its destructor
// 0x0048D075 and field parse table 0x00C4C600 are rowed. Layout and member
// names follow FlammableUpdateModuleDataDtor.cpp. Defaults: the four delays
// zero, flame damage limit 20.0, expiration five seconds of logic frames
// (the frame-rate global at 0x00DBA4E4), damage type 6, burned status set,
// run-to-water depth 0.0 with search radius 200.0 and increment 60.0, custom
// animation -1. The CameraMarker vector is built empty (STLport vector base
// 0x00211E58) and cleared through the rowed CameraMarkerVec::erase; retail
// stores the +0x4C..+0x54 defaults on both sides of that call.
#define BFME_SNAPSHOT_NAME_SLOT
#define Matrix4x4 Matrix4  // BFME renamed it
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameLogic/Module/FlammableUpdate.h"

extern int BfmeLogicFramesPerSecond;

FlammableUpdateModuleData::FlammableUpdateModuleData()
	: m_burnedDelay(0)
	, m_aflameDuration(0)
	, m_aflameDamageDelay(0)
	, m_aflameDamageAmount(0)
	, m_flameDamageLimitData(20.0f)
	, m_flameDamageExpirationDelay(BfmeLogicFramesPerSecond * 5)
	, m_damageType(6)
{
	m_runToWaterDepth = 0.0f;
	m_runToWaterSearchRadius = 200.0f;
	m_setBurnedStatus = true;
	m_swapModelWhenAflame = false;
	m_swapModelWhenQuenched = false;
	m_swapTextureWhenAflame = false;
	m_swapTextureWhenQuenched = false;
	m_burnContained = false;
	m_runToWater = false;
	m_runToWaterSearchIncrement = 60.0f;
	m_panicLocomotorWhileAflame = false;
	m_customAnimAndDuration.reset();
	m_fireMarkers.clear();
	m_customAnimAndDuration.reset();
}
