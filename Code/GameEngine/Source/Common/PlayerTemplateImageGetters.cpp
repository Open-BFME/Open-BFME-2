// cl: /Ireference/shims/bfme2_ascii
// PlayerTemplate image getters via TheMappedImageCollection (0x00DFF078).
// ?getFlagWaterMarkImage@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD1FB 19B (AsciiString at +0x170)
// ?getEnabledImage@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD221 19B (AsciiString at +0x174)
// ?rva001FD23F@PlayerTemplate@@QBEPBVImage@@XZ @0x001FD23F 19B (AsciiString at +0x1D8)
// BFME1 PlayerTemplate.cpp getHeadWaterMarkImage/getFlagWaterMarkImage/getSideIconImage/
// getGeneralImage/getEnabledImage all do TheMappedImageCollection->findImageByName(member).
// Retail class proven by callers derefing Player+0x34 (getPlayerTemplate): 0x001FD221 used by
// GadgetButtonSetEnabledImage at 0x0050E135/0x0050E321, 0x001FD1FB by winSetEnabledImage at
// 0x0050E66B, 0x001FD23F on PlayerTemplate from getControllingPlayer at 0x005294C7.
// Sibling offsets 0x170/0x174 are adjacent AsciiStrings and 0x1D8 closes the 0x1DC object.
#include "ascii_string.h"

class Image;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;


int Rva0033A3F4Lookup(const AsciiString &name);

class INI;

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

const Image *PlayerTemplate::getFlagWaterMarkImage() const
{
	return TheMappedImageCollection->findImageByName(m_170);
}

const Image *PlayerTemplate::getEnabledImage() const
{
	return TheMappedImageCollection->findImageByName(m_174);
}

int PlayerTemplate::rva001FD234() const
{
	return Rva0033A3F4Lookup(side);
}

const Image *PlayerTemplate::rva001FD23F() const
{
	return TheMappedImageCollection->findImageByName(m_1D8);
}
