// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_bonefxupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport
//
// ?resolveBoneLocations@BoneFXUpdate@@MAEXXZ, retail 0x00487634, 355 bytes.
//
// BoneFXUpdate virtual slot 13 (vtable 0x0084B170) resolveBoneLocations.
// Donor is BFME1 BoneFXUpdate::resolveBoneLocations
// (reference/open-bfme-1/Code/GameEngine/Source/GameLogic/Object/Update/BoneFXUpdate.cpp:542)
// via Zero Hour BoneFXUpdate.cpp:502. BFME2 layout matches the landed
// initTimes TU in this directory (moduleData at +4, object at +8,
// info arrays at +0x0C/+0x490/+0x914 element 0x24, positions at
// +0x1AC/+0x32C/+0x4AC, curBodyState at +0x62C, bonesResolved at +0x630).
// Retail inlines AsciiString::str as data+8 vs "" default (0x007BAC1C)
// and calls the rowed StringBase compare at 0x000069D6 via the AsciiString
// pin, Thing::getDrawable via pin 0x005508E2, and the rowed Drawable
// getPristineBonePositions at 0x0027274D. DEBUG_ASSERTCRASH compiles out
// under /DNDEBUG so the drawable null check emits no code.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/Thing.h"
#include "GameClient/Drawable.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/BoneFXUpdate.h"

// AsciiString::TheEmptyString: defined in Common/Rva00380200Getter.cpp.

void BoneFXUpdate::resolveBoneLocations()
{
	int i;
	Object *building = getObject();
	const BoneFXUpdateModuleData *boneFXUpdateModuleData = getBoneFXUpdateModuleData();
	if (building == 0) {
		return;
	}

	Drawable *drawable = building->getDrawable();

	if (boneFXUpdateModuleData == 0) {
		return;
	}

	for (i = 0; i < 8; ++i) {
		if (boneFXUpdateModuleData->m_fxList[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneFXListInfo *info = &(boneFXUpdateModuleData->m_fxList[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->locInfo.boneName.str(), 0, &m_FXBonePositions[m_curBodyState][i], 0, 1, 0);
		}

		if (boneFXUpdateModuleData->m_OCL[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneOCLInfo *info = &(boneFXUpdateModuleData->m_OCL[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->locInfo.boneName.str(), 0, &m_OCLBonePositions[m_curBodyState][i], 0, 1, 0);
		}

		if (boneFXUpdateModuleData->m_particleSystem[m_curBodyState][i].locInfo.boneName.compare(AsciiString::TheEmptyString) != 0) {
			const BoneParticleSystemInfo *info = &(boneFXUpdateModuleData->m_particleSystem[m_curBodyState][i]);
			drawable->getPristineBonePositions(info->locInfo.boneName.str(), 0, &m_PSBonePositions[m_curBodyState][i], 0, 1, 0);
		}
	}
	m_bonesResolved[m_curBodyState] = true;
}
