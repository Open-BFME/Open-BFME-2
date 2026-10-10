// ?rva00529B6E@Rva00529B6E@@QAEXPAVObject@@@Z
// partial score=0.85 date=2026-10-10
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
//
// PalantirCommandInterface::Impl::GetCurrentPortraitImage (native
// 0x005293D3..0x005294FC, RET 4; WorldBuilder 0x013CACB0 names the
// operation) and the two file-static selection walkers it calls with
// private register conventions (0x00529023: result buffer in EAX, list in
// ECX; 0x00529045: result buffer in EAX, list in EDX, iterator on the
// stack), reproduced by `static __declspec(noinline)` definitions in the
// caller's unit. Both skip selected drawables whose template is
// KINDOF_IGNORED_IN_GUI (+0x10D bit 7, the byte test W3DWaypointBuffer's
// drawWaypoints shows). The getter returns the given object's selected
// portrait (when it has the 0x002911B7 template or its own), else the
// portrait shared by every selectable drawable, else, for a non-empty
// selection, the first drawable's controlling player template image
// (0x001FD23F) or the "MultiPortrait" image. The rest of
// PalantirCommandInterface.cpp's native range stays in the units that
// already row it; this one holds the selection-walk family.

#include <list>
#include "ascii_string.h"
#include "unicode_string.h"

typedef bool Bool;
class Object;

enum KindOfType
{
	KINDOF_IGNORED_IN_GUI = 47
};

class ThingTemplate
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

	unsigned char m_unreconstructed_000[0x108];
	unsigned char m_kindof[12];
};

class Image;
class PlayerTemplate
{
public:
	const Image *rva001FD23F() const;
};
class Player
{
public:
	const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }

	unsigned char m_unreconstructed_000[0x34];
	const PlayerTemplate *m_playerTemplate;
};
class Team
{
public:
	Player *getControllingPlayer() const;
};

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Team *getTeam() { return m_team; }
	ThingTemplate *rva002911B7();
	const Image *getObjectSelectedPortraitImage();

	void *m_vtable;
	ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0x304 - 0x08];
	Team *m_team;
};

class Drawable
{
public:
	__forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	Object *getObject() { return m_object; }

	void *m_vtable;
	const ThingTemplate *m_template;
	unsigned char m_unreconstructed_008[0xFC - 0x08];
	Object *m_object;
};

typedef _STL::list<Drawable *> DrawableList;
typedef DrawableList::const_iterator DrawableListCIt;

class InGameUI
{
public:
#define BFME_UI_SLOT(n) virtual void slot##n() = 0;
	BFME_UI_SLOT(00) BFME_UI_SLOT(01) BFME_UI_SLOT(02) BFME_UI_SLOT(03)
	BFME_UI_SLOT(04) BFME_UI_SLOT(05) BFME_UI_SLOT(06) BFME_UI_SLOT(07)
	BFME_UI_SLOT(08) BFME_UI_SLOT(09) BFME_UI_SLOT(10) BFME_UI_SLOT(11)
	BFME_UI_SLOT(12) BFME_UI_SLOT(13) BFME_UI_SLOT(14) BFME_UI_SLOT(15)
	BFME_UI_SLOT(16) BFME_UI_SLOT(17) BFME_UI_SLOT(18) BFME_UI_SLOT(19)
	BFME_UI_SLOT(20) BFME_UI_SLOT(21) BFME_UI_SLOT(22) BFME_UI_SLOT(23)
	BFME_UI_SLOT(24) BFME_UI_SLOT(25) BFME_UI_SLOT(26) BFME_UI_SLOT(27)
	BFME_UI_SLOT(28) BFME_UI_SLOT(29) BFME_UI_SLOT(30) BFME_UI_SLOT(31)
	BFME_UI_SLOT(32) BFME_UI_SLOT(33) BFME_UI_SLOT(34) BFME_UI_SLOT(35)
	BFME_UI_SLOT(36) BFME_UI_SLOT(37) BFME_UI_SLOT(38) BFME_UI_SLOT(39)
	BFME_UI_SLOT(40) BFME_UI_SLOT(41) BFME_UI_SLOT(42) BFME_UI_SLOT(43)
	BFME_UI_SLOT(44) BFME_UI_SLOT(45) BFME_UI_SLOT(46) BFME_UI_SLOT(47)
	BFME_UI_SLOT(48) BFME_UI_SLOT(49) BFME_UI_SLOT(50) BFME_UI_SLOT(51)
	BFME_UI_SLOT(52) BFME_UI_SLOT(53) BFME_UI_SLOT(54) BFME_UI_SLOT(55)
	BFME_UI_SLOT(56) BFME_UI_SLOT(57) BFME_UI_SLOT(58) BFME_UI_SLOT(59)
	BFME_UI_SLOT(60) BFME_UI_SLOT(61) BFME_UI_SLOT(62) BFME_UI_SLOT(63)
	BFME_UI_SLOT(64) BFME_UI_SLOT(65) BFME_UI_SLOT(66) BFME_UI_SLOT(67)
	BFME_UI_SLOT(68) BFME_UI_SLOT(69) BFME_UI_SLOT(70) BFME_UI_SLOT(71)
	BFME_UI_SLOT(72)
#undef BFME_UI_SLOT
	virtual const DrawableList *getAllSelectedDrawables() const = 0; // +0x124
};
extern InGameUI *TheInGameUI;

class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};
extern ImageCollection *TheMappedImageCollection;

class PalantirCommandInterface
{
public:
	class Impl
	{
	public:
		const Image *GetCurrentPortraitImage(Object *obj);
	};
};

// Native 0x00529023 (34B): the first selected drawable the GUI does not ignore.
static __declspec(noinline) DrawableListCIt rva00529023(const DrawableList &list)
{
	DrawableListCIt it = list.begin();
	for (; it != list.end(); ++it)
		if (!(*it)->isKindOf(KINDOF_IGNORED_IN_GUI))
			break;
	return it;
}

// Native 0x00529045 (38B): the next one after it.
static __declspec(noinline) DrawableListCIt rva00529045(const DrawableList &list, DrawableListCIt it)
{
	for (++it; it != list.end(); ++it)
		if (!(*it)->isKindOf(KINDOF_IGNORED_IN_GUI))
			break;
	return it;
}

const Image *PalantirCommandInterface::Impl::GetCurrentPortraitImage(Object *obj)
{
	const Image *image = 0;
	if (obj != 0)
	{
		const ThingTemplate *tmpl = obj->rva002911B7();
		if (tmpl == 0)
			tmpl = obj->getTemplate();
		if (tmpl == 0)
			return 0;
		image = obj->getObjectSelectedPortraitImage();
	}
	else
	{
		const DrawableList *list = TheInGameUI->getAllSelectedDrawables();
		DrawableListCIt it = rva00529023(*list);
		if (it != list->end())
		{
			image = (*it)->getObject()->getObjectSelectedPortraitImage();
			if (image)
			{
				for (it = rva00529045(*list, it); it != list->end(); it = rva00529045(*list, it))
				{
					if ((*it)->getObject()->getObjectSelectedPortraitImage() != image)
					{
						image = 0;
						break;
					}
				}
			}
		}
		if (!image)
		{
			static const AsciiString multiPortrait("MultiPortrait");
			if (!list->empty())
			{
				Player *player = list->front()->getObject()->getTeam()->getControllingPlayer();
				if (player && player->getPlayerTemplate())
					image = player->getPlayerTemplate()->rva001FD23F();
				if (!image)
					image = TheMappedImageCollection->findImageByName(multiPortrait);
			}
		}
	}
	return image;
}

// ---- the selection rank / timer panel (native 0x00529B6E, RET 4) ----
// The selected object's (or every selectable drawable's common) progress
// record from the rowed 0x00528CEB (PalantirObjectProgress.cpp): mode
// rank 0 / timer 1 / none 2, rank, progress.
struct Rva00528CEBResult
{
	Rva00528CEBResult() : mode(2), rank(0), progress(0.0f) {}

	int mode;
	int rank;
	float progress;
};
Rva00528CEBResult rva00528CEB(Object *obj);
struct Rva00528B37Key;
int Rva00528B37Equal(const Rva00528B37Key *a, const Rva00528B37Key *b);

class Rva00222A8BTarget { public: int invoke(void *, const char *, int, const char *, void *, void *, void *, void *); };
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &, const UnicodeString &, bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0c() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1c() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;
class Rva00528B98 { public: void rva00528B98(); };
class Rva00529130 { public: void rva00529130(int rank); };
class Rva00529A7B { public: void rva00529A7B(float progress); };

class Rva00529B6E
{
public:
	void rva00529B6E(Object *obj);
private:
	void hide() { ((Rva00528B98 *)this)->rva00528B98(); }
	void *m_level;     // +0x00
	bool m_shown;      // +0x04
	int m_mode;        // +0x08
	bool m_rankSet;    // +0x0C
	int m_rank;        // +0x10
	float m_progress;  // +0x14
};

void Rva00529B6E::rva00529B6E(Object *obj)
{
	Rva00528CEBResult result;
	if (obj)
	{
		result = rva00528CEB(obj);
	}
	else
	{
		const DrawableList *list = TheInGameUI->getAllSelectedDrawables();
		DrawableListCIt it = rva00529023(*list);
		if (it != list->end())
		{
			result = rva00528CEB((*it)->getObject());
			if (result.mode != 2)
			{
				for (it = rva00529045(*list, it); it != list->end(); it = rva00529045(*list, it))
				{
					Rva00528CEBResult other = rva00528CEB((*it)->getObject());
					if (!(unsigned char)Rva00528B37Equal((const Rva00528B37Key *)&other, (const Rva00528B37Key *)&result))
					{
						result.mode = 2;
						break;
					}
				}
			}
		}
	}
	if (result.mode != m_mode)
	{
		hide();
		m_mode = result.mode;
	}
	if (m_mode == 2)
	{
		hide();
	}
	else
	{
	bool wasShown = m_shown;
	if (!wasShown)
	{
		((Rva00222A8BTarget *)g_bfmeAptWindowManager)->invoke(m_level, "ShowRankInterface", 0, 0, 0, 0, 0, 0);
		m_shown = true;
		m_rankSet = false;
		m_progress = -1.0f;
	}
	if (m_mode == 0)
	{
		if (!m_rankSet || result.rank != m_rank)
			((Rva00529130 *)this)->rva00529130(result.rank);
	}
	else if (m_mode == 1 && !wasShown)
	{
		static AsciiString heroRank("APT:HeroRank");
		static AsciiString timeRemaining("APT:PalantirTimeRemaining");
		g_bfmeAptWindowManager->bfmeSetText(heroRank, TheGameText->fetch(timeRemaining), false);
	}
	if (result.progress != m_progress)
		((Rva00529A7B *)this)->rva00529A7B(result.progress);
	}
}
