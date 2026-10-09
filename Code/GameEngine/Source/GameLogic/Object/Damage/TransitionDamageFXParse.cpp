// cl: /ICode/Libraries/Include/Lib /Ireference/shims/bfme2_ascii /DNDEBUG /DWIN32 /D_WINDOWS /DBFME_MODULE_NO_MPO /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
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


#include "Coord3D.h"

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

// Native 004B9C4D..004B9D86 is the complete 313B getLocalEffectPos helper:
// Ghidra boundary and WB12472F0 call graph/source-path/line339 corroborate
// the algorithm. Native EDI holds the location prefix, ESI the result, and
// [EBP+8] the Drawable. The ordinary emission anchor reproduces this private
// compiler convention; it has no independent target body or progress claim.
// BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d supplies the readable
// TransitionDamageFXRva002520B0 algorithm. The O1/SSE2/G7 source trial placed
// 313B; target evidence separately proves offsets00/04/08/0C, 12B coordinates,
// the two existing named callees, full target file-path string, and array32
// callbacks at47A6A9/B3FD0. The original location/point typedefs are unknown.
// A scoped lifetime adapter preserves the canonical coordinate data header;
// its empty constructor/destructor are independently verified ICF twins.
#include "Coord3D.h"
#include "ascii_string.h"

// The target's 32-element array uses nontrivial, empty coordinate lifetimes.
// Keep the canonical three-float data layout and express those lifetimes in
// a scoped adapter; this does not assert a new original target point type.
struct Rva004B9C4DPoint : Coord3D {
    Rva004B9C4DPoint() {}
    ~Rva004B9C4DPoint() {}
    // ??0Rva004B9C4DPoint@@QAE@ABU0@@Z absent-from-retail
    Rva004B9C4DPoint(const Rva004B9C4DPoint &other) {
        x=other.x; y=other.y; z=other.z;
    }
};
class Matrix3D;
class Drawable {
public:
    int getPristineBonePositions(const char *, int, Coord3D *, Matrix3D *, int, int) const;
};
int GetGameLogicRandomValue(int, int, char *, int);
struct Rva004B9C4DLoc {
    char field00;
    AsciiString field04;
    bool field08;
    Rva004B9C4DPoint field0C;
};
static __declspec(noinline) Rva004B9C4DPoint rva004B9C4D(
    const Rva004B9C4DLoc *loc, Drawable *draw)
{
    if (loc->field00==0 && draw) {
        if (!loc->field08) {
            Rva004B9C4DPoint pos;
            int count=draw->getPristineBonePositions(loc->field04.str(),0,&pos,0,1,0);
            if (count==0) return loc->field0C;
            return pos;
        } else {
            Rva004B9C4DPoint positions[32];
            int count=draw->getPristineBonePositions(loc->field04.str(),1,positions,0,32,0);
            if (count==0) return loc->field0C;
            int pick=GetGameLogicRandomValue(0,count-1,
                "C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Damage\\TransitionDamageFX.cpp",339);
            return positions[pick];
        }
    }
    return loc->field0C;
}
// ?emitRva004B9C4D absent-from-retail
Rva004B9C4DPoint emitRva004B9C4D(const Rva004B9C4DLoc *loc,Drawable *draw) {
    return rva004B9C4D(loc,draw);
}
