// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc_alloconly /EHsc /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
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
// "not found" and re-specify throws are throw INIException(3, ...)
// through _CxxThrowException 0x629094.

// /D_CRTIMP= makes the alloc-only shim's ::free a direct call, as in retail's
// overflow 0x002DFCF6; the "None" _strcmpi still goes through the import.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

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

// Keep the iterator comparison inline without a competing vector::empty
// COMDAT; AIUpdate.cpp owns the verified retail out-of-line body.
static __forceinline bool locomotorTemplatesEmpty(const BfmeLocomotorTemplateVector &values)
{
	return values.begin() == values.end();
}

typedef _STL::map<LocomotorSetType, BfmeLocomotorTemplateVector, _STL::less<LocomotorSetType>, _STL::allocator<_STL::pair<const LocomotorSetType, BfmeLocomotorTemplateVector> > > BfmeLocomotorSetMap;

// Reuse the verified retail container providers. Native callers use the
// out-of-line map subscript and folded pointer-vector erase/append bodies;
// suppress local default copies that the census proves differ from them.
namespace _STL { template<> BfmeLocomotorTemplateVector& BfmeLocomotorSetMap::operator[](const LocomotorSetType&); }

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

#include "ascii_string.h"

#include "../../../../Include/Common/INI/INI.h"

#include "../../../../Include/Common/NameKeyGenerator.h"

class LocomotorStore
{
public:
	LocomotorTemplate *findLocomotorTemplate(int namekey);
};

#include "../../../../Include/Common/ThingTemplate.h"

class AIUpdateModuleData
{
public:
	static void parseLocomotorSet(INI *ini, void *instance, void *store, const void *userData);

private:
	char m_pad[8];
	BfmeLocomotorSetMap m_locomotorTemplates;
};

#include "../../../../Include/Common/INI/FieldParse.h"

extern const char *TheLocomotorSetNames[];
extern NameKeyGenerator *TheNameKeyGenerator;
extern LocomotorStore *TheLocomotorStore;

// ?parseLocomotorSet@AIUpdateModuleData@@SAXPAVINI@@PAX1PBX@Z
void AIUpdateModuleData::parseLocomotorSet(INI *ini, void *instance, void *, const void *)
{
	ThingTemplate *tt = (ThingTemplate *)instance;
	AIUpdateModuleData *self = tt->friend_getAIModuleInfo();
	if (!self)
	{
		throw INIException(3, "Attempted to specify a locomotor for object %s without an AIUpdate block.", tt->getName().str());
	}

	LocomotorSetType set = (LocomotorSetType)ini->scanIndexList(ini->getNextToken(0), TheLocomotorSetNames);
	if (!locomotorTemplatesEmpty(self->m_locomotorTemplates[set]))
	{
		if (ini->getLoadType() != INI_LOAD_CREATE_OVERRIDES && ini->getLoadType() != INI_LOAD_UNKNOWN_4)
		{
			throw INIException(3, "re-specifying a LocomotorSet is no longer allowed\n");
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
			throw INIException(3, "Locomotor %s not found!\n", locoName);
		}
		self->m_locomotorTemplates[set].push_back(lt);
	}
}

// Units that declare _CxxThrowException(void *, void *) as a C++ overload
// call ?_CxxThrowException@@YGXPAX0@Z; retail calls the MSVC 7.1 throw helper
// __CxxThrowException@8 (its import thunk at 0x00629094). Same ABI: bind the spelling.
#pragma comment(linker, "/alternatename:?_CxxThrowException@@YGXPAX0@Z=__CxxThrowException@8")
