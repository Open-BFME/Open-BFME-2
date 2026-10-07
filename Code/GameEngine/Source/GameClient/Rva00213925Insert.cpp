// cl: /Ireference/shims/bfme2_ascii /Ob2 /DNDEBUG /MD /EHsc
// ?rva00213925@Rva000427195@@QAE?AUInsertRet00212A5A@@PBX@Z retail 0x00213925 36 bytes.
// Hashtable insert with grow: loads count at +0x10 inc calls pinned grow
// rva00212858 at 0x00212858 then tail-returns rowed insert rva00212A5A at
// 0x00212A5A with the same hidden return and key. Class proven by +0x10
// count and both callee owners. Callers at 0x00213E05 0x002140B8 0x00214133 0x002141AE.
// Evidence: callees 0x00212858 pinned 0x00212A5A rowed ret 8 struct-return.
// Precedent: Code/GameEngine/Source/GameClient/Rva001F93A3Insert.cpp.
#include "ascii_string.h"

struct InsertRet00212A5A
{
	InsertRet00212A5A(void *node, void *owner, unsigned char found)
		: m_node(node), m_owner(owner), m_found(found) {}
	void *m_node;
	void *m_owner;
	unsigned char m_found;
};

class Rva000427195
{
public:
	void rva00212858(unsigned int newSize);
	InsertRet00212A5A rva00212A5A(const void *key);
	InsertRet00212A5A rva00213925(const void *key);

	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

InsertRet00212A5A Rva000427195::rva00213925(const void *key)
{
	rva00212858(m_numElements + 1);
	return rva00212A5A(key);
}

// LivingWorld icon factories, native 0x00214060 / 0x002140DB / 0x00214156.
// Adjacent 0x14-byte tables are observed at +0x26C, +0x280 and +0x294.
// Their registered INI parsers and existing constructors prove each record size.
// Keep the name/pointer pair temporary: its full-expression lifetime lets the
// compiler reuse the allocation slot. InsertRet has native alignment and size 12.

class Rva003F9FA9
{
public:
	Rva003F9FA9(const AsciiString &name);
private:
	char m_unmodelled[0x30];
};

class Rva00402BE3
{
public:
	Rva00402BE3(const AsciiString &name);
private:
	char m_unmodelled[0x1C];
};

class Rva00402EFA
{
public:
	Rva00402EFA(const AsciiString &name);
private:
	char m_unmodelled[0x18];
};

template<class T> struct LivingWorldIconPair
{
    AsciiString first;
    T *second;
    LivingWorldIconPair(const AsciiString &name, T *icon) : first(name), second(icon) {}
};
class LivingWorldManager
{
public:
    Rva003F9FA9 *rva00214060(const AsciiString &name);
    Rva00402BE3 *rva002140DB(const AsciiString &name);
    Rva00402EFA *rva00214156(const AsciiString &name);
private:
    char m_unmodelled[0x26c];
    Rva000427195 m_armyIcons;
    Rva000427195 m_buildingIcons;
    Rva000427195 m_buildPlotIcons;
};

Rva003F9FA9 *LivingWorldManager::rva00214060(const AsciiString &name)
{
    Rva003F9FA9 *icon = new Rva003F9FA9(name);
    m_armyIcons.rva00213925(&static_cast<const LivingWorldIconPair<Rva003F9FA9> &>(LivingWorldIconPair<Rva003F9FA9>(name, icon)));
    return icon;
}

Rva00402BE3 *LivingWorldManager::rva002140DB(const AsciiString &name)
{
    Rva00402BE3 *icon = new Rva00402BE3(name);
    m_buildingIcons.rva00213925(&static_cast<const LivingWorldIconPair<Rva00402BE3> &>(LivingWorldIconPair<Rva00402BE3>(name, icon)));
    return icon;
}

Rva00402EFA *LivingWorldManager::rva00214156(const AsciiString &name)
{
    Rva00402EFA *icon = new Rva00402EFA(name);
    m_buildPlotIcons.rva00213925(&static_cast<const LivingWorldIconPair<Rva00402EFA> &>(LivingWorldIconPair<Rva00402EFA>(name, icon)));
    return icon;
}
