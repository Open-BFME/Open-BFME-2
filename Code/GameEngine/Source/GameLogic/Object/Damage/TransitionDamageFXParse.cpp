// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ?parseFXLocInfo@@YAXPAVINI@@PAXPAUFXLocInfo@@@Z, retail 0x004B9917, 319 bytes.
// TransitionDamageFX parseFXLocInfo helper plus its three callers
// (parseFXList/parseObjectCreationList/parseParticleSystem). Donor is BFME1
// TransitionDamageFX.cpp parseFXLocInfo (bone + RandomBone + loc with
// AsciiString temp plus INIException throws) and the three parse methods
// (each calls helper then checks fxlist/ocl/psys then INI parse helper).
// Evidence: strings "bone" "loc" "randombone" "parseFXLocInfo: Bone name not
// followed by RandomBone specifie..." "'loc' or 'bone' expected" plus
// "fxlist"/"ocl"/"psys" in callers; callees rowed getNextToken 0x2DF97
// getNextSubToken 0x2E06B scanReal 0x2EDA5 parseBool 0x2E850 plus pinned
// AsciiString assign 0x366F0 and CxxThrow; callers at 0x4B9A6A/0x4B9AD6/
// 0x4B9B41 become ready on landing; layout locType +0 boneName +4
// randomBone +8 loc +0xC matches TransitionDamageFXModuleDataCtor 0x1C
// records (void* +0 locType +4 boneName +8 randomBone +0xC loc +0x10).

typedef int Int;
typedef float Real;
typedef unsigned char UnsignedByte;

extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

template <typename T> struct BfmeStringData;

#include "ascii_string.h"


struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

typedef char FXDamageLocType;
enum
{
	FX_DAMAGE_LOC_TYPE_BONE = 0,
	FX_DAMAGE_LOC_TYPE_COORD = 1
};

struct FXLocInfo
{
	FXDamageLocType locType;
	char _pad0[3];
	AsciiString boneName;
	UnsignedByte randomBone;
	char _pad1[3];
	Coord3D loc;
};

struct FXDamageFXListInfo
{
	const void *fx;
	FXLocInfo locInfo;
};

struct FXDamageOCLInfo
{
	const void *ocl;
	FXLocInfo locInfo;
};

struct FXDamageParticleSystemInfo
{
	const void *particleSysTemplate;
	FXLocInfo locInfo;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextSubToken(const char *expected);
	Real scanReal(const char *token);
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

class TransitionDamageFXModuleData
{
public:
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
};

static void parseFXLocInfo(INI *ini, void *instance, FXLocInfo *locInfo)
{
	const char *token = ini->getNextToken(ini->getSepsColon());

	if (_strcmpi(token, "bone") == 0)
	{
		{
			AsciiString boneName(ini->getNextToken(0));
			AsciiString &dst = locInfo->boneName;
			dst = boneName;
		}
		locInfo->locType = FX_DAMAGE_LOC_TYPE_BONE;

		token = ini->getNextToken(ini->getSepsColon());
		if (_strcmpi(token, "randombone") != 0)
		{
			throw INIException(3, "parseFXLocInfo: Bone name not followed by RandomBone specifier.");
		}

		INI::parseBool(ini, instance, &locInfo->randomBone, 0);
	}
	else if (_strcmpi(token, "loc") == 0)
	{
		locInfo->loc.x = ini->scanReal(ini->getNextSubToken("X"));
		locInfo->loc.y = ini->scanReal(ini->getNextSubToken("Y"));
		locInfo->loc.z = ini->scanReal(ini->getNextSubToken("Z"));
		locInfo->locType = FX_DAMAGE_LOC_TYPE_COORD;
	}
	else
	{
		throw INIException(3, "'loc' or 'bone' expected");
	}
}

void TransitionDamageFXModuleData::parseFXList(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token;
	FXDamageFXListInfo *info = (FXDamageFXListInfo *)store;

	parseFXLocInfo(ini, instance, &info->locInfo);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "fxlist") != 0)
	{
		throw INIException(3, "'fxlist' expected");
	}

	INI::parseFXList(ini, instance, &info->fx, 0);
}

void TransitionDamageFXModuleData::parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token;
	FXDamageOCLInfo *info = (FXDamageOCLInfo *)store;

	parseFXLocInfo(ini, instance, &info->locInfo);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "ocl") != 0)
	{
		throw INIException(3, "'ocl' expected");
	}

	INI::parseObjectCreationList(ini, instance, store, &info->ocl);
}

void TransitionDamageFXModuleData::parseParticleSystem(INI *ini, void *instance, void *store, const void *userData)
{
	const char *token;
	FXDamageParticleSystemInfo *info = (FXDamageParticleSystemInfo *)store;

	parseFXLocInfo(ini, instance, &info->locInfo);

	token = ini->getNextToken(ini->getSepsColon());
	if (_strcmpi(token, "psys") != 0)
	{
		throw INIException(3, "'psys' expected");
	}

	INI::parseParticleSystemTemplate(ini, instance, store, &info->particleSysTemplate);
}
