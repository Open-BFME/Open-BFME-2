// ?parseFX@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
// partial score=0.9 date=2026-10-07
// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
//
// SlowDeathBehaviorModuleData FieldParse proc: Zero Hour's
// SlowDeathBehavior.cpp file static parseWeapon (class-scoped here for a
// unique ledger name) on the BFME 2 layout. Target evidence: the table at VA
// 0x00C42290 (read by buildFieldParse 0x0045E93F) maps Weapon (0x00C42330)
// -> 0x0045E618 (FX 0x0045E533 / OCL 0x0045E5A4 keep ini in a register and
// are not reproduced here yet). The BFME 2 Sound row (0x00C42340) ->
// 0x0045E8A9 parses each token through the pinned audio token parser
// 0x00339184 into a ref-counted handle appended to the per-phase vectors at
// +0xE8 (rowed push_back 0x0005A084), setting mask bit 8 when the handle
// holds a sound; its name stays address-derived. Per-phase vectors (0xC each) start at
// +0x58 (FX), +0x88 (OCL) and +0xB8 (Weapon); the loaded-effects mask is the
// byte at +0x18C (FX 1, OCL 2, Weapon 4). Phase names at VA 0x00DC9598. BFME 2
// looks weapons up through a const AsciiString & (temporary in the instance
// argument slot, released under EH).

#include "ascii_string.h"

#define NULL 0

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

namespace _STL
{
template <class T> class allocator
{
};
template <class T, class A> class vector;
template <> class vector<const FXList *, allocator<const FXList *> >
{
public:
	void push_back(const FXList *const &x);
private:
	const FXList **m_start;
	const FXList **m_finish;
	const FXList **m_endOfStorage;
};
template <> class vector<const ObjectCreationList *, allocator<const ObjectCreationList *> >
{
public:
	void push_back(const ObjectCreationList *const &x);
private:
	const ObjectCreationList **m_start;
	const ObjectCreationList **m_finish;
	const ObjectCreationList **m_endOfStorage;
};
template <> class vector<Rva0005A084Element, allocator<Rva0005A084Element> >
{
public:
	void push_back(const Rva0005A084Element &x);
private:
	Rva0005A084Element *m_start;
	Rva0005A084Element *m_finish;
	Rva0005A084Element *m_endOfStorage;
};
template <> class vector<const WeaponTemplate *, allocator<const WeaponTemplate *> >
{
public:
	void push_back(const WeaponTemplate *const &x);
private:
	const WeaponTemplate **m_start;
	const WeaponTemplate **m_finish;
	const WeaponTemplate **m_endOfStorage;
};
}

typedef _STL::vector<const FXList *, _STL::allocator<const FXList *> > FXListVec;
typedef _STL::vector<const ObjectCreationList *, _STL::allocator<const ObjectCreationList *> > OCLVec;
typedef _STL::vector<const WeaponTemplate *, _STL::allocator<const WeaponTemplate *> > WeaponTemplateVec;
typedef _STL::vector<Rva0005A084Element, _STL::allocator<Rva0005A084Element> > SoundVec;

enum SlowDeathPhaseType
{
	SDPHASE_INITIAL = 0,
	SD_PHASE_COUNT = 4
};

extern const char *TheSlowDeathPhaseNames[];

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

	unsigned char m_unreconstructed_000[0x58];
	FXListVec m_fx[SD_PHASE_COUNT];				// +0x58
	OCLVec m_ocls[SD_PHASE_COUNT];				// +0x88
	WeaponTemplateVec m_weapons[SD_PHASE_COUNT];		// +0xB8
	SoundVec m_sounds[SD_PHASE_COUNT];			// +0xE8
	unsigned char m_unreconstructed_118[0x18C - 0x118];
	unsigned char m_maskOfLoadedEffects;			// +0x18C
};

// ?parseFX@SlowDeathBehaviorModuleData@@SAXPAVINI@@PAX1PBX@Z
void SlowDeathBehaviorModuleData::parseFX(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	SlowDeathBehaviorModuleData *self = (SlowDeathBehaviorModuleData *)instance;
	SlowDeathPhaseType sdphase = (SlowDeathPhaseType)ini->scanIndexList(ini->getNextToken(), TheSlowDeathPhaseNames);
	for (const char *token = ini->getNextToken(); token != NULL; token = ini->getNextTokenOrNull())
	{
		const FXList *fxl = TheFXListStore->findFXList(token);
		self->m_fx[sdphase].push_back(fxl);
		if (fxl)
			self->m_maskOfLoadedEffects |= HAS_FX;
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
