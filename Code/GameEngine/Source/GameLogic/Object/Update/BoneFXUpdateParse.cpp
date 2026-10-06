// cl: /Ireference/shims/dockupdate /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_namekey /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader /Ireference/shims/bfme2htree /Ireference/shims/bfme2renderobj /Ireference/shims/bfmecamera /Ireference/shims/bfmelight /Ireference/shims/bfmeparticlehandle /Ireference/shims/bfmeparticleload /Ireference/shims/bfmeparticlequat /Ireference/shims/bfmeparticlesave /Ireference/shims/bfmeparticleline /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene -D_STLP_USE_STATIC_LIB -DNDEBUG -DWIN32 -D_WINDOWS /Ireference/shims/bfmefrustum
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


typedef int Int;
typedef int Bool;
typedef float Real;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

template <typename T> struct BfmeStringData;

template <typename T> class StringBase
{
public:
	void set(const T *text);
private:
	BfmeStringData<T> *m_data;
};

class AsciiString : public StringBase<char>
{
public:
	AsciiString() {}
};

class GameClientRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

class GameLogicRandomVariable
{
public:
	int m_type;
	float m_low;
	float m_high;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getSepsColon() { return m_sepsColon; }
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);
private:
	char _pad[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
};

void parseGameClientRandomDelay(INI *ini, void *instance, GameClientRandomVariable *delay);

struct BoneLocInfo
{
	AsciiString boneName;
};

struct BaseBoneListInfo
{
	BoneLocInfo locInfo;
	GameClientRandomVariable gameClientDelay;
	GameLogicRandomVariable gameLogicDelay;
	Int onlyOnce;
};

struct BoneFXListInfo : public BaseBoneListInfo
{
	const void *fx;
};

struct BoneOCLInfo : public BaseBoneListInfo
{
	const void *ocl;
};

struct BoneParticleSystemInfo : public BaseBoneListInfo
{
	const void *particleSysTemplate;
};

class BoneFXUpdateModuleData
{
public:
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

static void parseFXLocInfo(INI *ini, void *instance, BoneLocInfo *locInfo)
{
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "bone") == 0)
	{
		locInfo->boneName.set(ini->getNextToken(0));
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
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, (GameClientRandomVariable *)&info->gameLogicDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "fxlist") != 0)
		throw INIException(3, "'fxlist' expected");
	INI::parseFXList(ini, instance, (void *)&info->fx, 0);
}

void BoneFXUpdateModuleData::parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData)
{
	BoneOCLInfo *info = (BoneOCLInfo *)store;
	parseFXLocInfo(ini, instance, &info->locInfo);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, (GameClientRandomVariable *)&info->gameLogicDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "ocl") != 0)
		throw INIException(3, "'ocl' expected");
	INI::parseObjectCreationList(ini, instance, (void *)&info->ocl, 0);
}

void BoneFXUpdateModuleData::parseParticleSystem(INI *ini, void *instance, void *store, const void *userData)
{
	BoneParticleSystemInfo *info = (BoneParticleSystemInfo *)store;
	parseFXLocInfo(ini, instance, &info->locInfo);
	const char *token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "onlyonce") != 0)
		throw INIException(3, "'onlyonce' expected");
	INI::parseBool(ini, instance, &info->onlyOnce, 0);
	parseGameClientRandomDelay(ini, instance, &info->gameClientDelay);
	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "psys") != 0)
		throw INIException(3, "'psys' expected");
	INI::parseParticleSystemTemplate(ini, instance, (void *)&info->particleSysTemplate, 0);
}
