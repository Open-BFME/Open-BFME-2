// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?getMetaMapRec@MetaMap@@IAEPAVMetaMapRec@@W4Type@GameMessage@@@Z retail
// 0x001DB537 107B. Search the m_metaMaps list at +0xC for m_meta == t and
// return it; else allocate 0x24 via rowed operator new, default-construct the
// two UnicodeStrings, store t plus donor defaults key 0 trans 0 mod 0 usable 0
// category 6, clear both strings via rowed wide releaseBuffer 0x00036E70,
// prepend to the list and return the node. Evidence: ZH donor MetaEvent.h
// MetaMap layout plus MetaEvent.cpp body plus caller 0x001DB5A2 passing
// GameMessage::Type plus rowed new and releaseBuffer.
#include "unicode_string.h"


class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
};

class MetaMapRec
{
public:
	MetaMapRec *m_next;
	GameMessage::Type m_meta;
	int m_key;
	int m_transition;
	int m_modState;
	int m_usableIn;
	int m_category;
	UnicodeString m_description;
	UnicodeString m_displayName;
};

class MetaMap
{
protected:
	MetaMapRec *getMetaMapRec(GameMessage::Type t);
private:
	char m_pad[0xC];
	MetaMapRec *m_metaMaps;
};

MetaMapRec *MetaMap::getMetaMapRec(GameMessage::Type t)
{
	for (MetaMapRec *map = m_metaMaps; map != 0; map = map->m_next) {
		if (map->m_meta == t)
			return map;
	}
	MetaMapRec *m = new MetaMapRec;
	m->m_meta = t;
	m->m_key = 0;
	m->m_transition = 0;
	m->m_modState = 0;
	m->m_usableIn = 0;
	m->m_category = 6;
	m->m_description.clear();
	m->m_displayName.clear();
	m->m_next = m_metaMaps;
	m_metaMaps = m;
	return m;
}

// Native1DB4C4..1DB4CF is a complete11-byte RET-delimited leaf after RET.
// Clean BF1 9cb MetaMapRecConstructorThunk.cpp and DebugCommandMap.cpp
// both expose this shape. No direct call, tail jump or stored target address
// selects either original owner. Preserve only the independently witnessed
// contract: zero four-byte fields1C/20 and return the receiver in EAX.
// The nearby actual MetaMapRec allocator and INI tables corroborate the
// two-word construction pattern, but do not prove this leaf's class identity.
class Rva001DB4C4Fields
{
public:
    Rva001DB4C4Fields *initialize();
private:
    unsigned char unknown[0x1C];
    unsigned first;
    unsigned second;
};
Rva001DB4C4Fields *Rva001DB4C4Fields::initialize()
{
    first = 0;
    second = 0;
    return this;
}
