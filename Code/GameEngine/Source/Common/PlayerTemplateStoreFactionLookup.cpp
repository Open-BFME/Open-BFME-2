// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva001FD367@PlayerTemplateStore@@QBE_NHPAH@Z @0x001FD367 95B.
// Faction-index lookup over PlayerTemplateStore vector at +0x0C/+0x10 stride
// 0x1DC: calls rowed Rva0033A3F4Lookup on the AsciiString at template +0x18,
// writes the matching index through outIndex and returns true else false.
// Evidence: unlock lane callers at 0x0052203E and 0x00522085 in 0x00521EDA;
// vector layout and stride from sibling PlayerTemplateStoreFind/GetNth TUs.

#include "ascii_string.h"

class INI;
class Image;

enum NameKeyType
{
	NAMEKEY_INVALID = -1,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

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

class PlayerTemplateVector
{
public:
	unsigned size() const { return static_cast<unsigned>(m_last - m_first); }
	const PlayerTemplate &operator[](int index) const { return m_first[index]; }
private:
	PlayerTemplate *m_first;
	PlayerTemplate *m_last;
};

class PlayerTemplateStore
{
public:
	bool rva001FD367(int faction, int *outIndex) const;
private:
	char m_pad[0x0C];
	PlayerTemplateVector m_playerTemplates;
};

int Rva0033A3F4Lookup(const AsciiString &name);

bool PlayerTemplateStore::rva001FD367(int faction, int *outIndex) const
{
	for (int i = 0; i < m_playerTemplates.size(); ++i)
	{
		if (Rva0033A3F4Lookup(m_playerTemplates[i].side) == faction)
		{
			*outIndex = i;
			return true;
		}
	}
	return false;
}
