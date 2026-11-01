// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// platformsdk
// stlport
//
// SlowDeathBehaviorModuleData FieldParse procs: Zero Hour's
// SlowDeathBehavior.cpp file statics parseFX, parseOCL and parseWeapon
// (class-scoped here for unique ledger names) on the BFME 2 layout. Target
// evidence: the table at VA 0x00C42290 (read by buildFieldParse 0x0045E93F)
// maps FX -> 0x0045E533, OCL -> 0x0045E5A4 and Weapon (0x00C42330) ->
// 0x0045E618. The phase vectors are real STLport vectors: their push_back
// stays out of line (the ICF-folded 0x004DFCB0) but its visible body is what
// lets cl keep ini in ebx for FX and OCL as retail does. The BFME 2 Sound row (0x00C42340) ->
// 0x0045E8A9 parses each token through the pinned audio token parser
// 0x00339184 into a ref-counted handle appended to the per-phase vectors at
// +0xE8 (rowed push_back 0x0005A084), setting mask bit 8 when the handle
// holds a sound; its name stays address-derived. Per-phase vectors (0xC each) start at
// +0x58 (FX), +0x88 (OCL) and +0xB8 (Weapon); the loaded-effects mask is the
// byte at +0x18C (FX 1, OCL 2, Weapon 4). Phase names at VA 0x00DC9598. BFME 2
// looks weapons up through a const AsciiString & (temporary in the instance
// argument slot, released under EH).
//
// The DeathFlags row (0x00C42390) -> 0x0045E293 is BFME 1's parseDeathFlags
// (SlowDeathBehavior_parseDeathFlags.cpp, retail 0x00209980) on BFME 2 bit
// numbers: model conditions 0x95-0x98 and 0xB1 (guarded static at VA
// 0x00E03548, its inverse at 0x00E034F8; guard word 0x00E03594) restrict the
// +0x128 model flags parsed through the rowed 0x000B937E, and status bits
// 0x1F-0x23 (static at 0x00E034E8, rowed ctor 0x0045D887) restrict the +0x174
// status bitset parsed from the same description string through the rowed
// 0x00334506. Retail gives the static initialisers no EH state, as for
// nothrow constructors; FuncInfo state 0 is the description string and
// states 1 and 2 nest inside it with no code and no action.

#include "ascii_string.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <windows.h>
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVFXList@@V?$allocator@PBVFXList@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class FXList;
namespace _STL { template <> void vector<FXList const *,allocator<FXList const *> >::_M_clear(); }

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	const char *getNextTokenOrNull(const char *seps = 0);
	int scanIndexList(const char *token, const char *const *names);
};

class FXList;
class ObjectCreationList;
class WeaponTemplate;

class FXListStore
{
public:
	const FXList *findFXList(const char *name) const;
};
extern FXListStore *TheFXListStore;

class ObjectCreationListStore
{
public:
	const ObjectCreationList *findObjectCreationList(const char *name) const;
};
extern ObjectCreationListStore *TheObjectCreationListStore;

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
};
extern WeaponStore *TheWeaponStore;

// Same 4-byte element the rowed push_back 0x0005A084 is instantiated on.
struct Rva0005A084Element { int a[1]; };
// Use the complete retail push_back at 0x0005A084 from StlportVectorPushBackFamily.
// push_back on this element is rowed in its overflow owner as vector<Rva00058BBDElement>.
struct Rva00058BBDElement { int a[1]; };
namespace _STL {
template <> void vector<Rva00058BBDElement>::push_back(const Rva00058BBDElement &);
template <> __declspec(dllimport) __forceinline void vector<Rva0005A084Element>::push_back(const Rva0005A084Element &x)
{ ((vector<Rva00058BBDElement> *)this)->push_back(*(const Rva00058BBDElement *)&x); }
}

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

class Rva0045E8A9SoundRef
{
public:
	Rva0045E8A9SoundRef() : m_ref(NULL) {}
	~Rva0045E8A9SoundRef()
	{
		if (m_ref)
			m_ref->Release_Ref();
	}
	OpaqueRefCounted *m_ref;
};

void Rva00339184(const char *token, void *store);

// The death-flag masks under the names the ledger gives their rowed
// members: the 19-word model condition flags (+0x128) and the 4-word status
// bitset (+0x174).
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead rva0045D859() throw();
	void rva000B3ED3(const WeaponTemplateSetHead &other);
	unsigned int m_words[19];
};

// Retail's FuncInfo nests two further states inside the description string's
// with no code and no cleanup action: as in beginSlowDeath 0x0045DE65 they are
// modelled by two lifetimes in a scope the optimizer deletes.
void rva0045e293EliminatedSink(const void *, const void *);

namespace _STL
{
template <unsigned N> struct _Base_bitset;
template <> struct _Base_bitset<4>
{
	unsigned long _M_w[4];
	void _M_do_and(const _Base_bitset<4> &x);
};
}

typedef _STL::vector<const FXList *> FXListVec;
typedef _STL::vector<const ObjectCreationList *> OCLVec;
typedef _STL::vector<const WeaponTemplate *> WeaponTemplateVec;
typedef _STL::vector<Rva0005A084Element> SoundVec;

enum SlowDeathPhaseType
{
	SDPHASE_INITIAL = 0,
	SD_PHASE_COUNT = 4
};

// Retail RVA 0x009C9598: four phase strings followed by NULL.
const char *TheSlowDeathPhaseNames[] = { "INITIAL", "MIDPOINT", "FINAL", "HIT_GROUND", NULL };

class SlowDeathBehaviorModuleData
{
public:
	enum
	{
		HAS_FX = 0x01,
		HAS_OCL = 0x02,
		HAS_WEAPON = 0x04,
		HAS_SOUND = 0x08
	};

	static void parseFX(INI *ini, void *instance, void *store, const void *userData);
	static void parseOCL(INI *ini, void *instance, void *store, const void *userData);
	static void parseWeapon(INI *ini, void *instance, void *store, const void *userData);
	static void rva0045E8A9(INI *ini, void *instance, void *store, const void *userData);
	static void parseDeathFlags(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_unreconstructed_000[0x58];
	FXListVec m_fx[SD_PHASE_COUNT];				// +0x58
	OCLVec m_ocls[SD_PHASE_COUNT];				// +0x88
	WeaponTemplateVec m_weapons[SD_PHASE_COUNT];		// +0xB8
	SoundVec m_sounds[SD_PHASE_COUNT];			// +0xE8
	unsigned char m_unreconstructed_118[0x128 - 0x118];
	WeaponTemplateSetHead m_deathModelFlags;		// +0x128
	_STL::_Base_bitset<4> m_deathStatusFlags;		// +0x174
	unsigned char m_unreconstructed_184[0x18C - 0x184];
	unsigned char m_maskOfLoadedEffects;			// +0x18C
};

// ?parseFX@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void SlowDeathBehaviorModuleData::parseFX(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)ini->scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList(token);	// could be null! this is OK!
		self->m_fx[sdphase].push_back(fxl);
		if (fxl)
			self->m_maskOfLoadedEffects |= HAS_FX;
	}
}

// ?parseOCL@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void SlowDeathBehaviorModuleData::parseOCL(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)ini->scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const ObjectCreationList *ocl = TheObjectCreationListStore->findObjectCreationList(token);	// could be null! this is OK!
		self->m_ocls[sdphase].push_back(ocl);
		if (ocl)
			self->m_maskOfLoadedEffects |= HAS_OCL;
	}
}

// ?parseWeapon@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void SlowDeathBehaviorModuleData::parseWeapon(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)ini->scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const WeaponTemplate *wt = TheWeaponStore->findWeaponTemplate(AsciiString(token));	// could be null! this is OK!
		self->m_weapons[sdphase].push_back(wt);
		if (wt)
			self->m_maskOfLoadedEffects |= HAS_WEAPON;
	}
}

// ?rva0045E8A9@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void SlowDeathBehaviorModuleData::rva0045E8A9(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)ini->scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		Rva0045E8A9SoundRef sound;
		Rva00339184(token, &sound);
		self->m_sounds[sdphase].push_back(*(const Rva0005A084Element *)&sound);
		if (sound.m_ref)
			self->m_maskOfLoadedEffects |= HAS_SOUND;
	}
}
