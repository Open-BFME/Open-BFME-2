// cl: /DBFME_ASCII_DTOR_DECL /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib /ICode/Libraries/Include /ICode/GameEngine/Source /ICode/GameEngine/Source/Common
// stlport
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

#include <string.h>

template <typename T> struct BfmeStringData;

#include "ascii_string.h"
#include "Coord3D.h"
#include <vector>
#include "GameLogicObjectLookupView.h"
#include "../../../Common/Thing/thing.h"
#include "../../../../Include/Common/ObjectModule.h"

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
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	const char *getNextSubToken(const char *expected);
	const char *getSepsColon() const { return m_sepsColon; }
	float scanReal(const char *token);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystemTemplate(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_unreconstructed[0x420];
	const char *m_sepsColon;
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage; // +0x00
	int m_argCount; // +0x04
};

class Rva004BA1C8;

struct TransitionDamageFXRecordA
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordB
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

struct TransitionDamageFXRecordC
{
	void *m_value;
	unsigned char m_locType;
	unsigned char m_pad05[3];
	AsciiString m_boneName;
	unsigned char m_randomBone;
	unsigned char m_pad0D[3];
	float m_loc[3];
};

// BFME1 supplies the string/vector semantic lead. Native callbacks 4B9C46
// and 577998 independently prove a zeroed, owned word at record offset 8;
// both four-element header arrays use the vector constructor closure256646
// and string-vector destructor2CC70. The original record names are unknown.
typedef _STL::vector<AsciiString> TransitionSmallVec;

enum TransitionDamageFXExtent
{
	BODYDAMAGETYPE_COUNT = 4,
	DAMAGE_MODULE_MAX_FX = 12
};

class UpdateModuleData
{
public:
	__declspec(dllimport) __forceinline UpdateModuleData() {}
	~UpdateModuleData();
};

class INI;

class TransitionDamageFXModuleData : public UpdateModuleData
{
public:
	TransitionDamageFXModuleData();
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void parseParticleSystem(INI *ini, void *instance, void *store, const void *userData);
	static void NeighborIDSubobjectNameDataAppend(INI *ini, void *instance, void *store, const void *userData);

private:
	const void *m_vtable;
	unsigned int m_unused04;
	int m_damageFXTypes;
	TransitionDamageFXRecordA m_fxList[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageOCLTypes;
	TransitionDamageFXRecordB m_ocl[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	int m_damageParticleTypes;
	TransitionDamageFXRecordC m_particleSystem[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];
	TransitionSmallVec m_unkFD4[4];
	TransitionSmallVec m_unk1004[4];
	_STL::vector<Rva004BA1C8> m_tail;
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
// [EBP+8] the Drawable. Its real caller onBodyDamageStateChange (below)
// reproduces this private compiler convention.
// BFME1 f98983a7d3bb405f1a4ba94bb6a2a168062a819d supplies the readable
// TransitionDamageFXRva002520B0 algorithm. The O1/SSE2/G7 source trial placed
// 313B; target evidence separately proves offsets00/04/08/0C, 12B coordinates,
// the two existing named callees, full target file-path string, and array32
// callbacks at47A6A9/B3FD0. The original location/point typedefs are unknown.
// A scoped lifetime adapter preserves the canonical coordinate data header;
// its empty constructor/destructor are independently verified ICF twins.
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
class Drawable
{
public:
	void rva002724FD(const AsciiString &a, int b, int c, float d, float e);
	int getPristineBonePositions(const char *, int, Coord3D *, Matrix3D *, int, int) const;
	void rva002724FD(const AsciiString &name, unsigned char visible, int a, float b, float c);
};
int GetGameLogicRandomValue(int, int, char *, int);
struct Rva004B9C4DLoc {
    char field00;
    AsciiString field04;
    bool field08;
    Rva004B9C4DPoint field0C;
};
// WorldBuilder getLocalEffectPos, WB VA 0x012472F0 (callgraph lead, score 2.0).
static __declspec(noinline) Rva004B9C4DPoint getLocalEffectPos(
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
// ?onBodyDamageStateChange@TransitionDamageFX@@UAEXPBVDamageInfo@@W4BodyDamageType@@1@Z
// retail 0x004B9F18..0x004BA1B2 (666B), ret 0xC, reached through the damage
// interface at +0x10 (this-adjusted: object at -8, module data at -0xC, the
// primary object at -0x10). BFME1/ZH TransitionDamageFX::onBodyDamageStateChange
// with BFME2 changes: an isKindOf(0x45) early out, the bfmeUseFDE hook
// 0x004B9B99 on the new state, BFME2's particle-system handle and the record
// walk 0x004B9DA9 when the transition enters or leaves state 3. Module data
// layout: masks +8/+0x54C/+0xA90 ahead of FX/OCL/particle [4][12] arrays of
// 0x1C entries; particle IDs [4][12] at +0x14 of the module.
typedef unsigned int UnsignedInt;

enum KindOfType
{
	KINDOF_FIRST = 0
};

enum BodyDamageType
{
	BODY_PRISTINE = 0
};

enum DamageType
{
	DAMAGE_EXPLOSION = 1
};


class DamageInfo
{
public:
	char m_unknown00[0x08];
	ObjectID m_sourceID;			// +0x08
	char m_unknown0C[0x04];
	DamageType m_damageType;		// +0x10
};

inline bool getDamageTypeFlag(UnsignedInt flags, DamageType dt)
{
	return (flags & (1 << (dt - 1))) != 0;
}

class FXList
{
public:
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *primaryMtx = 0,
		float primarySpeed = 0.0f, const Coord3D *secondary = 0);
};

class Object;

class ObjectCreationList
{
public:
	void create(void *primary, void *secondary, void *lifetime);
	void create(void *primaryObj, void *primary, void *secondary, Int lifetimeFrames);
	static __forceinline void create(const ObjectCreationList *ocl, Object *primaryObj, const Coord3D *primary, const Coord3D *secondary)
	{
		if (ocl)
			((ObjectCreationList *)ocl)->create(primaryObj, (void *)primary, (void *)secondary, 0);
	}
};

class Dict;
class BehaviorModuleinterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0; virtual void slot10() = 0; virtual void slot11() = 0;
	virtual void slot12() = 0; virtual void slot13() = 0; virtual void slot14() = 0;
	virtual void slot15() = 0; virtual void slot16() = 0; virtual void slot17() = 0;
	virtual void slot18() = 0; virtual void slot19() = 0; virtual void slot20() = 0;
	virtual void slot21() = 0; virtual void slot22() = 0; virtual void slot23() = 0;
	virtual void slot24() = 0; virtual void slot25() = 0; virtual void slot26() = 0;
	virtual void slot27() = 0; virtual void slot28() = 0; virtual void slot29() = 0;
	virtual void slot30() = 0; virtual void slot31() = 0; virtual void slot32() = 0;
	virtual void slot33() = 0; virtual void slot34() = 0; virtual void slot35() = 0;
	virtual void slot36() = 0; virtual void slot37() = 0; virtual void slot38() = 0;
	virtual void mapLoadPostProcess(const Dict *) = 0;
};
// The three-slot table the constructor installs at +0x10 (0x010B2588).
class DamageInfo;
enum BodyDamageType;
class DamageModuleinterface
{
public:
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType) = 0;
};
class Xfer;
class Rva004BA1C8Triple {
public:
	unsigned int a;
	unsigned int b;
	unsigned int c;
};
class Rva004BA1C8 {
public:
	~Rva004BA1C8();
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);
private:
	int m_00;
	_STL::vector<AsciiString> m_04;
	unsigned int m_10;
	Rva004BA1C8Triple m_14;
	Rva004BA1C8Triple m_20;
};
class Rva004BA1D0;
class TransitionDamageFXModuleDataView;
enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};
// The neighbour-record vector at +0xD4 of the module. Its constructor is the folded
// Vector_base 0x00211E58 and its destructor the row 0x004BA35A.
class TensileFormationUpdateMember : public _STL::vector<Rva004BA1C8>
{
public:
	__forceinline TensileFormationUpdateMember() {}
	~TensileFormationUpdateMember();
};
class DamageModule : public ObjectModule,
    public BehaviorModuleinterface,
    public DamageModuleinterface
{
public:
    DamageModule(Thing *thing, const ModuleData *moduleData);
    virtual ~DamageModule();
};
// Layout from constructor 0x00252F50: interfaces at +0x0C and +0x10, 0x30
// zeroed words from +0x14, and the vector at +0xD4 (allocation 0xE0).
class TransitionDamageFX : public DamageModule
{
public:
    TransitionDamageFX(Thing *thing, const ModuleData *moduleData);
    void bfmeGoFDE();
    void bfmeUseFDE(void *r);
    void rva004B9DA9(bool applyTransition);
    virtual NameKeyType getModuleNameKey() const;
    virtual void mapLoadPostProcess(const Dict *);
    virtual void onBodyDamageStateChange(const DamageInfo *, BodyDamageType, BodyDamageType);

protected:
    virtual ~TransitionDamageFX();
    virtual void xfer(Xfer *xfer);
    const TransitionDamageFXModuleDataView *getTransitionDamageFXModuleData() const
    {
        return (const TransitionDamageFXModuleDataView *)m_moduleData;
    }

private:
    ParticleSystemID m_particleSystemID[4][12]; // +0x14
    TensileFormationUpdateMember resolvedNeighbors; // +0xD4
};

class BodyModuleInterface
{
public:
	virtual void b00(); virtual void b01(); virtual void b02(); virtual void b03(); virtual void b04();
	virtual void b05(); virtual void b06(); virtual void b07();
	virtual int getStatus(); // slot 8
	virtual void b09();
	virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14();
	virtual const DamageInfo *getLastDamageInfo() const; // slot 15
};

class Object : public Thing
{
public:
	bool isKindOf(KindOfType t) const;
	unsigned getID() const { return m_id; }
	Module *findDamageModule(NameKeyType key) const { return findModule(key); }
	BodyModuleInterface *getBodyModule() const { return m_body; }

protected:
	Module *findModule(NameKeyType key) const;

public:
	unsigned char m_unmodelled60[0x14];
	unsigned m_id;					// +0x74
	unsigned char m_unmodelled78[0x254 - 0x78];
	BodyModuleInterface *m_body;	// +0x254
};

extern GameLogic *TheGameLogic;

struct Rva001F3899Arg
{
	int m_00;
	int m_04;
	int m_08;
};
class Rva001F3899Slot
{
public:
	void set(const Rva001F3899Arg &arg);
};
struct Rva001F3C43Arg;
class Rva001F3C43Slot
{
public:
	void set(const Rva001F3C43Arg *arg);
};

class ParticleSystem
{
public:
	void setPosition(const Coord3D *pos)
	{
		((Rva001F3899Slot *)this)->set(*(const Rva001F3899Arg *)pos);
	}
	void attachToObject(const Object *obj)
	{
		((Rva001F3C43Slot *)this)->set((const Rva001F3C43Arg *)obj);
	}

	char m_unknown00[0xA8];
	ParticleSystemID m_systemID; // +0xA8
};
ParticleSystem *Make001FCBD7();

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
};
class BfmeParticleSystemHandleBase
{
public:
	~BfmeParticleSystemHandleBase()
	{
		if (m_system)
			((RvaSmartPtr12 *)this)->rva0004CBC0();
	}
	ParticleSystem *m_system;
	BfmeParticleSystemHandleBase *m_previous;
	BfmeParticleSystemHandleBase *m_next;
};
class BfmeParticleSystemHandle : public BfmeParticleSystemHandleBase
{
public:
	operator bool() const { return m_system != 0; }
	ParticleSystem *operator->() const
	{
		return m_system ? m_system : Make001FCBD7();
	}
};

class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *sysTemplate, bool createSlaves);
	void destroyParticleSystemByID(ParticleSystemID id);
};
extern ParticleSystemManager *TheParticleSystemManager;

class TransitionDamageFXModuleDataView
{
public:
	char m_unknown00[0x08];
	UnsignedInt m_damageFXTypes;		// +0x08
	FXDamageFXListInfo m_fxList[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];		// +0x0C
	UnsignedInt m_damageOCLTypes;		// +0x54C
	FXDamageOCLInfo m_OCL[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];			// +0x550
	UnsignedInt m_damageParticleTypes;	// +0xA90
	FXDamageParticleSystemInfo m_particleSystem[BODYDAMAGETYPE_COUNT][DAMAGE_MODULE_MAX_FX];	// +0xA94
	char m_unknownFD4[0x60];
	_STL::vector<Rva004BA1D0> neighbors;	// +0x1034
};

void TransitionDamageFX::onBodyDamageStateChange(const DamageInfo *damageInfo, BodyDamageType oldState, BodyDamageType newState)
{
	Object *obj = getObject();
	if (obj->isKindOf((KindOfType)0x45))
		return;

	Object *damageSource = 0;
	Int i;
	Drawable *draw = obj->getDrawable();
	const TransitionDamageFXModuleDataView *modData = getTransitionDamageFXModuleData();

	if (damageInfo)
		damageSource = TheGameLogic->findObjectByID(damageInfo->m_sourceID);

	for (i = 0; i < DAMAGE_MODULE_MAX_FX; i++)
	{
		if (m_particleSystemID[oldState][i] != INVALID_PARTICLE_SYSTEM_ID)
		{
			TheParticleSystemManager->destroyParticleSystemByID(m_particleSystemID[oldState][i]);
			m_particleSystemID[oldState][i] = INVALID_PARTICLE_SYSTEM_ID;
		}
	}

	bfmeUseFDE((void *)newState);

	if (newState > oldState)
	{
		Coord3D pos;
		const DamageInfo *lastDamageInfo = getObject()->getBodyModule()->getLastDamageInfo();

		for (i = 0; i < DAMAGE_MODULE_MAX_FX; i++)
		{
			if (modData->m_fxList[newState][i].fx)
			{
				if (lastDamageInfo == 0 ||
						getDamageTypeFlag(modData->m_damageFXTypes, lastDamageInfo->m_damageType))
				{
					pos = getLocalEffectPos((const Rva004B9C4DLoc *)&modData->m_fxList[newState][i].locInfo, draw);
					getObject()->convertBonePosToWorldPos(&pos, 0, &pos, 0);
					FXList::doFXPos((const FXList *)modData->m_fxList[newState][i].fx, &pos);
				}
			}

			if (modData->m_OCL[newState][i].ocl)
			{
				if (lastDamageInfo == 0 ||
						getDamageTypeFlag(modData->m_damageOCLTypes, lastDamageInfo->m_damageType))
				{
					pos = getLocalEffectPos((const Rva004B9C4DLoc *)&modData->m_OCL[newState][i].locInfo, draw);
					getObject()->convertBonePosToWorldPos(&pos, 0, &pos, 0);
					ObjectCreationList::create((const ObjectCreationList *)modData->m_OCL[newState][i].ocl,
						getObject(), &pos, damageSource->getPosition());
				}
			}

			const ParticleSystemTemplate *pSystemT =
				(const ParticleSystemTemplate *)modData->m_particleSystem[newState][i].particleSysTemplate;
			if (pSystemT)
			{
				if (lastDamageInfo == 0 ||
						getDamageTypeFlag(modData->m_damageParticleTypes, lastDamageInfo->m_damageType))
				{
					BfmeParticleSystemHandle pSystem = TheParticleSystemManager->createParticleSystem(pSystemT, true);
					if (pSystem)
					{
						pos = getLocalEffectPos((const Rva004B9C4DLoc *)&modData->m_particleSystem[newState][i].locInfo, draw);
						pSystem->setPosition(&pos);
						pSystem->attachToObject(getObject());
						m_particleSystemID[newState][i] = pSystem->m_systemID;
					}
				}
			}
		}
	}

	if (newState != oldState && (newState == 3 || oldState == 3))
		rva004B9DA9(true);
}
