// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_bonefxupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport
// BoneFXUpdate::initTimes — retail 0x0048750B / 297B.
// Upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp
// (BoneFXUpdate::initTimes, ZH uses REAL_TO_INT; retail BFME2 uses a plain
// (int) cast which calls __ftol2 — same transfer BFME1 landed in
// reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate_initTimes.cpp).
// Layout notes (all verified against the target disasm):
// - GameLogic::m_frame at +0x40 (ZH/BFME1 have +0x3C; BFME2 added 4 bytes).
// - BoneFXUpdateModuleData matches ZH exactly: m_fxList at +0x0C (base 0x08 +
//   m_damageFXTypes 4), m_OCL at +0x490, m_particleSystem at +0x914, element
//   size 0x24.
// - BoneFXUpdate matches ZH: m_moduleData at +4, m_nextFXFrame at +0x2C,
//   m_nextOCLFrame at +0xAC, m_curBodyState at +0x62C.
// - BoneLocInfo is a single-AsciiString wrapper at offset 0.
// - AsciiString::compare is DECLARED only so the three call sites encode the
//   retail StringBase::compare at 0x000069D6 (see symbols.csv pin); defining it
//   locally with memcmp (as BFME1 did) would call memcmp instead and mismatch.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "GameLogic/GameLogic.h"
#include "GameLogic/Module/BoneFXUpdate.h"

// AsciiString::TheEmptyString: defined in Common/Rva00380200Getter.cpp.

GameLogic *TheGameLogic;

void BoneFXUpdate::initTimes()
{
	int i;
	const BoneFXUpdateModuleData *boneFXUpdateModuleData = getBoneFXUpdateModuleData();
	// Retail reads GameLogic's current-frame field at +0x40; the included
	// GeneralsMD getFrame() view reads +0x3C. Keep the target-specific layout
	// local to this body instead of changing the shared GameLogic header.
	struct BfmeGameLogicFrameView {
		UnsignedByte unknown[0x40];
		Int frame;
	};
	int now = ((const BfmeGameLogicFrameView *)TheGameLogic)->frame;

	for (i = 0; i < BONE_FX_MAX_BONES; ++i) {
		if (boneFXUpdateModuleData->m_fxList[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextFXFrame[m_curBodyState][i] = now + (int)boneFXUpdateModuleData->m_fxList[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextFXFrame[m_curBodyState][i] = -1;
		}
		if (boneFXUpdateModuleData->m_OCL[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextOCLFrame[m_curBodyState][i] = now + (int)boneFXUpdateModuleData->m_OCL[m_curBodyState][i].gameLogicDelay.getValue();
		} else {
			m_nextOCLFrame[m_curBodyState][i] = -1;
		}
		if (boneFXUpdateModuleData->m_particleSystem[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			m_nextParticleSystemFrame[m_curBodyState][i] = now + (int)boneFXUpdateModuleData->m_particleSystem[m_curBodyState][i].gameClientDelay.getValue();
		} else {
			m_nextParticleSystemFrame[m_curBodyState][i] = -1;
		}
	}
}
