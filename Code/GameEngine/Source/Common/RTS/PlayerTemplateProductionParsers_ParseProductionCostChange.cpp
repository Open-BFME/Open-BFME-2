// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD
// Split from PlayerTemplateProductionParsers.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
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
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class AsciiString;
class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *);
	const AsciiString &keyToName(NameKeyType key);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class INI
{
public:
	const char *getNextToken(const char *seps = 0);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	int scanIndexList(const char *token, const char *const *names);
	float dup_002EE10(const char *token);
	char prefix[8];
	int mode;
};

extern const char *TheVeterancyNames[];

namespace _STL
{
template <class T> struct less;
template <class T> class allocator;
template <class A, class B> struct pair;
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

class Rva001FDE3F
{
public:
	float &rva001FDE3F(const AsciiString &key);
private:
	unsigned char m_table[0x14];
};

class Image;

class Overridable
{
public:
	Overridable *deleteOverrides();
	const Overridable *getFinalOverride() const;

	virtual ~Overridable();
	Overridable *m_nextOverride;
	bool m_isOverride;
    char pad09[3];
	int m_extra0C;
};

class PlayerTemplate : public Overridable
{
public:
	PlayerTemplate();
    virtual ~PlayerTemplate();
    static void parseStartMoney(INI *ini, void *instance, void *store, const void *userData);
    const Image *getFlagWaterMarkImage() const;
    const Image *getEnabledImage() const;
    int rva001FD234() const;
    const Image *rva001FD23F() const;
protected:
	static void parseProductionCostChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionTimeChange(INI *ini, void *instance, void *store, const void *userData);
	static void parseProductionVeterancyLevel(INI *ini, void *instance, void *store, const void *userData);
public:
    NameKeyType m_nameKey; // +0x10
    char display14[4];
    AsciiString side;
    char beforeF4[0xF4 - 0x1C];
    ProductionChangeMap m_productionCostChanges;
    Rva001FDE3F m_productionTimeChanges;
    ProductionVeterancyMap m_productionVeterancyLevels;
    char before150[0x150 - 0x120];
    bool flag150,flag151;
    char tail152[0x170 - 0x152];
    AsciiString m_170;
    AsciiString m_174;
    char m_pad178[0x1D8 - 0x178];
    AsciiString m_1D8;
};

// ?parseProductionCostChange@PlayerTemplate@@KAXPAVINI@@PAX1PBX@Z
void PlayerTemplate::parseProductionCostChange(INI *ini, void *instance, void * /*store*/, const void * /*userData*/)
{
	PlayerTemplate *self = (PlayerTemplate *)instance;

	int buildTemplateKey = TheNameKeyGenerator->nameToKey(ini->getNextToken());
	Real percentChange = ini->dup_002EE10(ini->getNextToken());

	self->m_productionCostChanges[buildTemplateKey] = percentChange;
}



class Rva000427195
{
public:
	~Rva000427195();
};

class Rva001FE065
{
public:
	void rva001FE065();
};


