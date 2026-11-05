// cl: /MD
//
// ?rva002A9ACC@Rva002A9ACC@@QAEXPBVDict@@@Z retail 0x002A9ACC 105B
// Two Dict color reads via rowed NameKey caches at 0x00DBDE64 and 0x00DBDE6C
// plus rowed Dict getInt at 0x003131CA. First hit writes +0x280 and +0x284
// second hit overwrites +0x284 with alpha 0xFF000000 ORed. Caller 0x002AFCDF.
// Evidence: retail calls rowed get 0x00148F5E twice and rowed getInt twice.
enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class Rva00148F5ECache
{
public:
	Rva00148F5ECache(const char *name) : m_key(NAMEKEY_INVALID), m_name(name) {}
	NameKeyType get();
private:
	NameKeyType m_key;
	const char *m_name;
};

// VA 0x00DBDE64 / 0x00DBDE6C are TheKey_playerColor / TheKey_playerNightColor,
// defined once by WorldHeightMap.cpp (INSTANTIATE_WELL_KNOWN_KEYS) as const
// StaticNameKey records; this unit reads them through its Rva00148F5ECache view.
class StaticNameKey;
extern const StaticNameKey TheKey_playerColor;
extern const StaticNameKey TheKey_playerNightColor;

#include "../../Include/Common/Dict.h"

class Rva002A9ACC
{
public:
	void rva002A9ACC(const Dict*);
	char m_pad00[0x280];
private:
	int m_color1; // +0x280
	int m_color2; // +0x284
};

void Rva002A9ACC::rva002A9ACC(const Dict *dict)
{
	if (!dict)
		return;
	bool exists;
	int color = dict->getInt(((Rva00148F5ECache &)TheKey_playerColor).get(), &exists);
	if (exists)
	{
		color |= 0xFF000000;
		m_color1 = color;
		m_color2 = color;
	}
	int nightColor = dict->getInt(((Rva00148F5ECache &)TheKey_playerNightColor).get(), &exists);
	if (exists)
	{
		nightColor |= 0xFF000000;
		m_color2 = nightColor;
	}
}

// ?removeCommandPoints@Player@@QAEXPAURva002A7588In@@@Z 35B @0x002A9B58 (WorldBuilder Player.cpp:1663; addCommandPoints 0x002A9B35, :1646): thiscall with one arg ret4 void.
// Evidence: add ecx 0x60 once then cmp [edx+0x61c] jle to choose rowed 0x002A7513 void vs rowed 0x002A75C9 int.
// Callers at 0x0028DB00 0x0028EB0E 0x0028EBB7 0x00290DD3. LINK BONUS via 0x0028EB42.
struct Rva002A7588In
{
	char m_pad[4];
	void *m_p4;
};

struct Rva002A9B58Mid
{
	char _pad[0x61c];
	int _61c;
};

class Rva002A7513
{
public:
	void rva002A7513(void *a);
};

class Rva002A75C9
{
public:
	int rva002A75C9(Rva002A7588In *p);
};

class Rva002A7500
{
public:
	void rva002A7500(void *a);
};

class Rva002A75B8
{
public:
	int rva002A75B8(Rva002A7588In *p);
};

#include "../../Include/Common/Player.h"

void Player::removeCommandPoints(Rva002A7588In *p)
{
	Rva002A7513 *a = (Rva002A7513 *)((char *)this + 0x60);
	Rva002A75C9 *b = (Rva002A75C9 *)((char *)this + 0x60);
	Rva002A9B58Mid *mid = (Rva002A9B58Mid *)p->m_p4;
	if (mid->_61c > 0)
		a->rva002A7513(p);
	else
		b->rva002A75C9(p);
}

void Player::addCommandPoints(Rva002A7588In *p)
{
	Rva002A7500 *a = (Rva002A7500 *)((char *)this + 0x60);
	Rva002A75B8 *b = (Rva002A75B8 *)((char *)this + 0x60);
	Rva002A9B58Mid *mid = (Rva002A9B58Mid *)p->m_p4;
	if (mid->_61c > 0)
		a->rva002A7500(p);
	else
		b->rva002A75B8(p);
}
