// cl: /Ireference/shims/bfme2_ascii /O1 /GX /DNDEBUG /MD
//
// PlayerTemplate production FieldParse procs (Zero Hour PlayerTemplate.cpp
// protected statics) on the BFME 2 layout. Target evidence: the PlayerTemplate
// table at VA 0x00BE2070 maps ProductionCostChange (0x00BE2220) -> 0x001FDF26,
// ProductionTimeChange (0x00BE2230) -> 0x001FDF73 and ProductionVeterancyLevel
// (0x00BE2240) -> 0x001FDFDB. BFME 2 deltas: the percent scan is the member
// form rowed at 0x0002EE10; the cost map (+0xF4) is the rowed map<int,float>;
// the time map (+0x100) is keyed by the template name itself through the
// unrowed lookup 0x001FDE3F (pinned by address); the veterancy map (+0x114) is
// the rowed map<int,int>.

#include "ascii_string.h"

typedef float Real;
typedef int Int;

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *nameString);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	Int scanIndexList(const char *token, const char *const *names);
	Real dup_002EE10(const char *token);	// percent-to-real scan
};

extern const char *TheVeterancyNames[];

namespace _STL
{
template <class T> struct less
{
};
template <class T> class allocator
{
};
template <class A, class B> struct pair
{
};
template <class K, class V, class C, class A> class map;
template <> class map<int, float, less<int>, allocator<pair<const int, float> > >
{
public:
	float &operator[](const int &key);
private:
	unsigned char m_tree[0xC];
};
template <> class map<int, int, less<int>, allocator<pair<const int, int> > >
{
public:
	int &operator[](const int &key);
private:
	unsigned char m_tree[0xC];
};
}

typedef _STL::map<int, float, _STL::less<int>, _STL::allocator<_STL::pair<const int, float> > > ProductionChangeMap;
typedef _STL::map<int, int, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > ProductionVeterancyMap;

// Name-keyed production-time map; its lookup body 0x001FDE3F is unrowed.
class Rva001FDE3F
{
public:
	Real &rva001FDE3F(const AsciiString &key);
private:
	unsigned char m_table[0x14];
};

class PlayerTemplate
{
protected:
	static void parseProductionCostChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionTimeChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionVeterancyLevel(INI *ini, void *instance, void *store, const void *userData);

private:
	unsigned char m_unreconstructed_000[0xF4];
	ProductionChangeMap m_productionCostChanges;		// +0xF4
	Rva001FDE3F m_productionTimeChanges;			// +0x100
	ProductionVeterancyMap m_productionVeterancyLevels;	// +0x114
};

// ?parseProductionCostChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z
void PlayerTemplate::parseProductionCostChange(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	PlayerTemplate *self = (PlayerTemplate *)instance;

	int buildTemplateKey = TheNameKeyGenerator->nameToKey(ini->getNextToken());
	Real percentChange = ini->dup_002EE10(ini->getNextToken());

	self->m_productionCostChanges[buildTemplateKey] = percentChange;
}

// ?parseProductionTimeChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z
void PlayerTemplate::parseProductionTimeChange(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	PlayerTemplate *self = (PlayerTemplate *)instance;

	AsciiString buildTemplateName(ini->getNextToken());
	Real percentChange = ini->dup_002EE10(ini->getNextToken());

	self->m_productionTimeChanges.rva001FDE3F(buildTemplateName) = percentChange;
}

// ?parseProductionVeterancyLevel@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z
void PlayerTemplate::parseProductionVeterancyLevel(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	PlayerTemplate *self = (PlayerTemplate *)instance;

	// Format is ThingTemplatename VeterancyName
	AsciiString HACK = AsciiString(ini->getNextToken());
	int buildTemplateKey = TheNameKeyGenerator->nameToKey(HACK.str());

	Int startLevel = ini->scanIndexList(ini->getNextToken(), TheVeterancyNames);
	self->m_productionVeterancyLevels[buildTemplateKey] = startLevel;
}
