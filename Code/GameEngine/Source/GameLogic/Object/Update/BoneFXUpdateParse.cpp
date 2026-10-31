// cl: /FIzh_ascii.h /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfme2_bonefxupdate /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Ireference/shims/dockupdate /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfmefrustum
// stlport
// ?parseFXLocInfo@@YAXPAVINI@@PAXPAUBoneLocInfo@@@Z, retail 0x004871A7 88B.
// BoneFXUpdate parseFXLocInfo helper plus its three callers
// (parseFXList/parseObjectCreationList/parseParticleSystem). Donor is BFME1
// BoneFXUpdateModuleDataParseFXList.cpp parseFXLocInfo (bone check plus
// AsciiString set plus INIException throws) and the three parse methods
// (each calls helper then checks onlyonce then INI parse helpers).
// Evidence: strings "bone" "'bone' expected" "onlyonce" "fxlist"/"ocl"/"psys"
// in callers; callees rowed getNextToken 0x2DF97 set 0x55F5 parseBool 0x2E850
// parseGameClientRandomDelay 0x870F6 parseFXList 0x338A09 parseOCL 0x338A6F
// parsePsysTemplate 0x3395BB plus pinned CxxThrow and INIException ctor;
// callers at 0x487200/0x4872AF/0x48735E become ready on landing; layout
// locInfo +0 gameClientDelay +4 gameLogicDelay +0x10 onlyOnce +0x1C fx/ocl/psys +0x20
// matches BoneFXUpdate_initTimes 0x0C/0x490/0x914 records and retail lea offsets.

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/INI.h"
#include "GameLogic/Module/BoneFXUpdate.h"

// Native IAT 0x00BBA518 is msvcr71.dll's _strcmpi import; this unit's /D_CRTIMP= strips string.h's dllimport.
namespace BoneFXUpdateCrt {
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
}

class INIException
{
public:
	INIException(int errorCode, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
	char *mFailureMessage; // +0x00
	int mErrorCode; // +0x04
};

void parseGameClientRandomDelay( INI *ini, void *instance, GameClientRandomVariable *delay);

static void parseFXLocInfo(INI *ini, void *instance, BoneLocInfo *locInfo)
{
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "bone") == 0)
	{
		reinterpret_cast<StringBase<char> *>(&locInfo->boneName)->set(ini->getNextToken(0));
	}
	else
	{
		throw INIException(3, "'bone' expected");
	}
}

void BoneFXUpdateModuleData::parseFXList(INI *ini, void *instance, void *store, const void *userData)
{
	BoneFXListInfo *info = (BoneFXListInfo *)store;
	parseFXLocInfo(ini, instance, &info->locInfo);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, (GameClientRandomVariable *)&info->gameLogicDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "fxlist") != 0)
		throw INIException(3, "'fxlist' expected");
	INI::parseFXList(ini, instance, (void *)&info->fx, 0);
}

void BoneFXUpdateModuleData::parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData)
{
	BoneOCLInfo *info = (BoneOCLInfo *)store;
	parseFXLocInfo(ini, instance, &info->locInfo);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, (GameClientRandomVariable *)&info->gameLogicDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "ocl") != 0)
		throw INIException(3, "'ocl' expected");
	INI::parseObjectCreationList(ini, instance, (void *)&info->ocl, 0);
}

void BoneFXUpdateModuleData::parseParticleSystem(INI *ini, void *instance, void *store, const void *userData)
{
	BoneParticleSystemInfo *info = (BoneParticleSystemInfo *)store;
	parseFXLocInfo(ini, instance, &info->locInfo);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, &info->gameClientDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (BoneFXUpdateCrt::_strcmpi(token, "psys") != 0)
		throw INIException(3, "'psys' expected");
	INI::parseParticleSystemTemplate(ini, instance, (void *)&info->particleSysTemplate, 0);
}
