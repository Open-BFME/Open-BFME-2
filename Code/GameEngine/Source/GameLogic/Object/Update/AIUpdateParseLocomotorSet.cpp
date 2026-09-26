// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD
// stlport
//
// ?parseLocomotorSet@AIUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
// retail 0x0026E699 (302 bytes).
//
// Zero Hour AIUpdate.cpp proves the name and shape: null-guard the
// AIUpdate block, scan the set index, reject re-specification unless the
// load is override-tolerant, clear the set vector, then loop tokens
// (skipping empties and "None"), key each through TheNameKeyGenerator,
// find its template through TheLocomotorStore, and push it. BFME2
// differences: the load-type gate also accepts type 4 alongside
// INI_LOAD_CREATE_OVERRIDES (2); the map subscript is the out-of-line
// rowed 0x1EA05B; the clear lowers to the folded voidptr erase 0x31BD55;
// pushes lower to the folded const-pointer push_back 0x4DFCB0; the
// "not found" and re-specify throws build INIException(3, ...) inline
// and throw through the pinned _CxxThrowException 0x629094.

#include <map>
#include <vector>

class LocomotorTemplate;

// LocomotorSetType values from the Zero Hour donor
// (GameEngine/Include/GameLogic/Module/AIUpdate.h); saved in save files.
enum LocomotorSetType
{
	LOCOMOTORSET_INVALID = -1,

	LOCOMOTORSET_NORMAL = 0,
	LOCOMOTORSET_NORMAL_UPGRADED,
	LOCOMOTORSET_FREEFALL,
	LOCOMOTORSET_WANDER,
	LOCOMOTORSET_PANIC,
	LOCOMOTORSET_TAXIING,
	LOCOMOTORSET_SUPERSONIC,
	LOCOMOTORSET_SLUGGISH,

	LOCOMOTORSET_COUNT
};

typedef _STL::vector<const LocomotorTemplate *> BfmeLocomotorTemplateVector;

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;

enum INILoadType
{
	INI_LOAD_INVALID = 0,
	INI_LOAD_OVERWRITE = 1,
	INI_LOAD_CREATE_OVERRIDES = 2,
	INI_LOAD_MULTIFILE = 3,
	// Provisional: retail 0x0026E699 treats 2 and 4 as override-tolerant.
	// Zero Hour only defines 0-3; the BFME2 meaning of 4 is unproven.
	INI_LOAD_UNKNOWN_4 = 4
};

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class AsciiString
{
public:
	const char *str() const { return m_data ? m_data + 8 : ""; }

private:
	char *m_data;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	const char *getNextTokenOrNull(const char *seps);
	int scanIndexList(const char *token, const char *const *table);
	INILoadType getLoadType() const { return m_loadType; }

private:
	char m_pad[8];
	INILoadType m_loadType;
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *str);
};

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int namekey);
};

class ThingTemplate
{
public:
	class AIUpdateModuleData *friend_getAIModuleInfo();
	const AsciiString &getName() const { return m_name; }

private:
	char m_pad[0x64];
	AsciiString m_name;
};

class AIUpdateModuleData
{
public:
	static void parseLocomotorSet(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_pad[8];
	BfmeLocomotorSetMap m_locomotorTemplates;
};

class INIException
{
public:
	INIException(int argumentCount, const char *format, ...);

	char *mFailureMessage;
	int m_argumentCount;
};

__declspec(noreturn) void __stdcall _CxxThrowException(void *pExc, void *pInfo);
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);

extern const char *TheLocomotorSetNames[];
extern NameKeyGenerator *TheNameKeyGenerator;
extern LocomotorStore *TheLocomotorStore;

// Address anchor only: the throw sites push this object's address as an
// immediate (DIR32, filled from retail by the gate -- Crate precedent).
// Its content is never compared.
struct ParseLocomotorThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseLocomotorThrowInfoAnchor parseLocomotorThrowInfoAnchor = { 0, 0, 0, 0 };

// ?parseLocomotorSet@AIUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void AIUpdateModuleData::parseLocomotorSet(INI *ini, void *instance, void *, const void *)
{
	ThingTemplate *tt = (ThingTemplate *)instance;
	AIUpdateModuleData *self = tt->friend_getAIModuleInfo();
	if (!self)
	{
		INIException e(3, "Attempted to specify a locomotor for object %s without an AIUpdate block.", tt->getName().str());
		_CxxThrowException(&e, (void *)&parseLocomotorThrowInfoAnchor);
	}

	LocomotorSetType set = (LocomotorSetType)ini->scanIndexList(ini->getNextToken(0), TheLocomotorSetNames);
	if (!self->m_locomotorTemplates[set].empty())
	{
		if (ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES && ini->getLoadType() != INI_LOAD_UNKNOWN_4)
		{
			INIException e(3, "re-specifying a LocomotorSet is no longer allowed\n");
			_CxxThrowException(&e, (void *)&parseLocomotorThrowInfoAnchor);
		}
	}

	self->m_locomotorTemplates[set].clear();
	for (const char *locoName = ini->getNextToken(0); locoName; locoName = ini->getNextTokenOrNull(0))
	{
		if (!*locoName || _strcmpi(locoName, "None") == 0)
			continue;

		NameKeyType locoKey = TheNameKeyGenerator->nameToKey(locoName);
		const LocomotorTemplate *lt = TheLocomotorStore->findLocomotorTemplate(locoKey);
		if (!lt)
		{
			INIException e(3, "Locomotor %s not found!\n", locoName);
			_CxxThrowException(&e, (void *)&parseLocomotorThrowInfoAnchor);
		}
		self->m_locomotorTemplates[set].push_back(lt);
	}
}
