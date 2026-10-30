// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/GameEngine/Source/Common
// Small GameEngine bodies from .text gaps no Ghidra function covers (eleventh
// batch; see GapBodiesGE01.cpp). Retail bytes establish every shape; owning
// classes are not recovered unless named, so each keeps an address-derived
// name and a view of only the members it touches. Callees and globals use the
// ledger's existing spellings.

#include "GameLogicObjectLookupView.h"

template <class T> class StringBase;
class AsciiString;
class RenderObjClass;
class Player;

// --- 0x003FB682 (67B): an opacity in (0, 1] goes to the +0x08 render object
// (rowed 0x0010E87A) and is kept at +0x98.
bool Rva0010E87A_SetOpacity(RenderObjClass *robj, float opacity);	// 0x0010E87A

class Rva003FB682
{
public:
	void setOpacity(float opacity);
private:
	char m_pad[8];
	RenderObjClass *m_robj;									// +0x08
	char m_pad0C[0x98 - 0x0C];
	float m_opacity;										// +0x98
};

void Rva003FB682::setOpacity(float opacity)
{
	if (opacity > 0.0f && opacity <= 1.0f)
	{
		Rva0010E87A_SetOpacity(m_robj, opacity);
		m_opacity = opacity;
	}
}

// --- 0x0052416D / 0x00524222 / 0x00524294 / 0x00524378 (67B each): drop a
// registered name from this string vector, telling the Apt window manager
// (rowed 0x00224455 / AptPlayer::RemoveOverButtonHandler / 0x002246B1 /
// 0x00224705) first.
StringBase<char> *Rva000BD22FFind(StringBase<char> *first, StringBase<char> *last, const StringBase<char> &value);	// 0x000BD22F

class Rva003769C2StringVector
{
public:
	AsciiString *erase(AsciiString *pos);					// 0x003769C2
	AsciiString *begin() { return m_begin; }
	AsciiString *end() { return m_end; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_storage;
};

class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva00224455 { public: int RemoveCommandMap(const AsciiString *name); };
class AptPlayer { public: void RemoveOverButtonHandler(const AsciiString &name); };
class Rva002246B1 { public: int RemoveCustomRender(const AsciiString *name); };
class Rva00224705 { public: int rva00224705(const AsciiString *name); };

class Rva0052416D : public Rva003769C2StringVector
{
public:
	void rva0052416D(const AsciiString &name);
	void rva00524222(const AsciiString &name);
	void rva00524294(const AsciiString &name);
	void rva00524378(const AsciiString &name);
};

void Rva0052416D::rva0052416D(const AsciiString &name)
{
	if (g_bfmeAptWindowManager)
	{
		AsciiString *it = (AsciiString *)Rva000BD22FFind((StringBase<char> *)begin(), (StringBase<char> *)end(), (const StringBase<char> &)name);
		if (it != end())
		{
			((Rva00224455 *)g_bfmeAptWindowManager)->RemoveCommandMap(&name);
			erase(it);
		}
	}
}

void Rva0052416D::rva00524222(const AsciiString &name)
{
	if (g_bfmeAptWindowManager)
	{
		AsciiString *it = (AsciiString *)Rva000BD22FFind((StringBase<char> *)begin(), (StringBase<char> *)end(), (const StringBase<char> &)name);
		if (it != end())
		{
			((AptPlayer *)g_bfmeAptWindowManager)->RemoveOverButtonHandler(name);
			erase(it);
		}
	}
}

void Rva0052416D::rva00524294(const AsciiString &name)
{
	if (g_bfmeAptWindowManager)
	{
		AsciiString *it = (AsciiString *)Rva000BD22FFind((StringBase<char> *)begin(), (StringBase<char> *)end(), (const StringBase<char> &)name);
		if (it != end())
		{
			((Rva002246B1 *)g_bfmeAptWindowManager)->RemoveCustomRender(&name);
			erase(it);
		}
	}
}

void Rva0052416D::rva00524378(const AsciiString &name)
{
	if (g_bfmeAptWindowManager)
	{
		AsciiString *it = (AsciiString *)Rva000BD22FFind((StringBase<char> *)begin(), (StringBase<char> *)end(), (const StringBase<char> &)name);
		if (it != end())
		{
			((Rva00224705 *)g_bfmeAptWindowManager)->rva00224705(&name);
			erase(it);
		}
	}
}

// --- 0x00219713 (68B): the first object (from GameLogic's list, linked at
// +0x8C) with template flag 0x40 at +0x11F whose controlling player is the
// local one.
class Object;

class Player
{
public:
	bool isLocalPlayer() const;								// 0x002A9D89
};

struct Rva00219713Template
{
	char m_pad[0x11F];
	unsigned char m_11F;
};

class Object
{
public:
	Player *getControllingPlayer() const;					// 0x0028AFA9
	char m_pad[4];
	Rva00219713Template *m_template;						// +0x04
	char m_pad08[0x8C - 0x08];
	Object *m_next;											// +0x8C
};

extern GameLogic *TheGameLogic;

Object *Rva00219713()
{
	for (Object *obj = TheGameLogic->getFirstObject(); obj; obj = obj->m_next)
	{
		if (obj->m_template->m_11F & 0x40)
		{
			Player *player = obj->getControllingPlayer();
			if (player && player->isLocalPlayer())
				return obj;
		}
	}
	return 0;
}
