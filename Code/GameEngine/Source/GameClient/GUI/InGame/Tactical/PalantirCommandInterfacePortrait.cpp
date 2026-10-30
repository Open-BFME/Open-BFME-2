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
// (0x001FD23F) or the "MultiPortrait" image. Its caller, the interface's
// refresh 0x00529E3B, lives here too, as does the rank/timer panel update
// it calls (0x00529B6E, also a walker user). The rest of
// PalantirCommandInterface.cpp's native range stays in the units that
// already row it; this one holds the selection-walk family.

#include <list>
#include "ascii_string.h"
#include "unicode_string.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;

enum KindOfType
{
	KINDOF_IGNORED_IN_GUI = 47
};

class ThingTemplate
{
public:
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return (m_kindof[t >> 3] & (1 << (t & 7))) != 0; }

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
	__declspec(dllimport) __forceinline const PlayerTemplate *getPlayerTemplate() const { return m_playerTemplate; }

	unsigned char m_unreconstructed_000[0x34];
	const PlayerTemplate *m_playerTemplate;
};
#include "../../../../../Include/Common/TeamBFME2.h"

class Object
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	// The callers inline +0x304; do not emit a competing accessor COMDAT.
	__declspec(dllimport) __forceinline Team *getTeam() { return m_team; }
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
	__declspec(dllimport) __forceinline Bool isKindOf(KindOfType t) const { return m_template->isKindOf(t); }
	__declspec(dllimport) __forceinline Object *getObject() { return m_object; }

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

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// The Apt window manager's portrait image set (0x002239E2) and clear
// (0x00223A94) under their rowed address-derived spellings.
class Rva002239B2 { public: void rva002239E2(const AsciiString &name, const Image *image); };
class Rva00223A94 { public: int rva00223A94(const AsciiString *name); };
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &, const UnicodeString &, bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva002BED91 { public: void clear(); };
// The rank / timer panel (0x18 bytes) the interface keeps at +0x38; its
// hide (0x00528B98), rank (0x00529130) and progress (0x00529A7B) setters are
// rowed under these address-derived spellings.
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
class Rva0052914B { public: void rva0052914B(Object *obj); private: char m_data[0x10]; };

class Rva0052936C { public: void UpdateButton(int index); };

class PalantirCommandInterface
{
public:
	class Impl
	{
	public:
		void Show();
		const Image *GetCurrentPortraitImage(Object *obj);
		void rva00529E3B();
	private:
		struct Slot
		{
			char m_pad00[0x0C];
			Rva002BED91 m_callback; // +0x0C
			int m_state;            // +0x10
		};
		void UpdateButton(int index) { ((Rva0052936C *)this)->UpdateButton(index); }

		char m_pad00[0x2C];
		bool m_2C;                  // +0x2C
		bool m_shown;               // +0x2D
		ObjectID m_objectID;        // +0x30
		char m_pad34[0x38 - 0x34];
		Rva00529B6E m_rankPanel;    // +0x38 (0x18 bytes)
		Rva0052914B m_costPanel;    // +0x50 (0x10 bytes)
		const Image *m_portrait;    // +0x60
		Slot m_slots[6];            // +0x64
	};
	void rva00529FBE();
private:
	Impl *m_impl;	// +0
};

// Native 0x00529023 (34B): the first selected drawable the GUI does not ignore.
// WorldBuilder FindFirstNonIgnored, WB VA 0x013C97D0 (callsite lead, score 1.0).
static __declspec(noinline) DrawableListCIt FindFirstNonIgnored(const DrawableList &list)
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

// Retail 0x00528C01: a selected drawable's portrait as a TU static;
// GetCurrentPortraitImage inlines both calls and cl keeps this
// register-convention copy (drawable in EAX, tail jump to the object getter).
static const Image *drawablePortraitImage(Drawable *draw)
{
	return draw->getObject()->getObjectSelectedPortraitImage();
}

const Image *PalantirCommandInterface::Impl::GetCurrentPortraitImage(Object *obj)
{
	const Image *image = 0;
	if (obj != 0)
	{
		const ThingTemplate *thingTemplate = obj->rva002911B7();
		if (thingTemplate == 0)
			thingTemplate = obj->getTemplate();
		if (thingTemplate == 0)
			return 0;
		image = obj->getObjectSelectedPortraitImage();
	}
	else
	{
		const DrawableList *list = TheInGameUI->getAllSelectedDrawables();
		DrawableListCIt it = FindFirstNonIgnored(*list);
		if (it != list->end())
		{
			image = drawablePortraitImage(*it);
			if (image)
			{
				for (it = rva00529045(*list, it); it != list->end(); it = rva00529045(*list, it))
				{
					if (drawablePortraitImage(*it) != image)
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

// Native 0x00529B6E (571B, RET 4): the rank / timer panel update. The
// selected object's progress record (or, without one, the record every
// selectable drawable shares; mode none = 2 when they differ) from the rowed
// 0x00528CEB; a mode change hides the panel, mode none keeps it hidden;
// otherwise the panel is shown once (ShowRankInterface through the Apt
// window manager's invoke 0x00222A8B), the rank set when it changed (rank
// mode) or the time-remaining caption set on the first show (timer mode),
// and the progress refreshed when it changed.
struct Rva00528CEBResult
{
	Rva00528CEBResult() : mode(2), rank(0), progress(0.0f) {}

	int mode;
	int rank;
	float progress;
};
Rva00528CEBResult rva00528CEB(Object *obj);

// The record compare 0x00528B37 (Rva00528B37Compare.cpp), visible here as a
// COMDAT copy of the rowed body: seeing that it keeps no copy of the
// records' addresses lets cl hold the result's mode in a register across the
// panel calls, as retail does.
extern float g_Va00BC2424;
#include <math.h>
struct Rva00528B37Key
{
	int m_a;
	int m_b;
	float m_f;
};
__declspec(noinline) inline int Rva00528B37Equal(const Rva00528B37Key *a, const Rva00528B37Key *b)
{
	if (a->m_a != b->m_a)
		return false;
	if (a->m_b != b->m_b)
		return false;
	if (fabs(a->m_f - b->m_f) < g_Va00BC2424)
		return true;
	return false;
}

class Rva00222A8BTarget { public: int invoke(void *, const char *, int, const char *, void *, void *, void *, void *); };
class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0; virtual void slot08() = 0; virtual void slot0c() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0; virtual void slot18() = 0; virtual void slot1c() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0; virtual void slot28() = 0; virtual void slot2c() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;			// +0x3C
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;	// +0x38
};
extern GameTextInterface *TheGameText;

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
		DrawableListCIt it = FindFirstNonIgnored(*list);
		if (it != list->end())
		{
			Drawable *draw = *it;
			result = rva00528CEB(draw->getObject());
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
	if (m_mode != 2)
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
			UnicodeString text = TheGameText->fetch(timeRemaining);
			g_bfmeAptWindowManager->bfmeSetText(heroRank, text, false);
		}
		if (result.progress != m_progress)
			((Rva00529A7B *)this)->rva00529A7B(result.progress);
	}
	else
	{
		hide();
	}
}

// Native 0x00529E3B..0x00529F3D: the interface's per-frame refresh. While
// shown it resolves the selected object (+0x30), swaps the CommandUI
// portrait image when it changed, refreshes the six buttons and the rank
// (0x00529B6E) and cost (0x0052914B) panels; hidden, it clears every
// button's callback and state.
void PalantirCommandInterface::Impl::rva00529E3B()
{
	if (m_2C && !m_shown)
		Show();
	if (m_shown)
	{
		Object *obj = 0;
		if (m_objectID)
			obj = TheGameLogic->findObjectByID(m_objectID);
		const Image *image = GetCurrentPortraitImage(obj);
		if (image != m_portrait)
		{
			if (image)
				((Rva002239B2 *)g_bfmeAptWindowManager)->rva002239E2(AsciiString("CommandUI/Portrait"), image);
			else if (m_portrait)
				((Rva00223A94 *)g_bfmeAptWindowManager)->rva00223A94(&AsciiString("CommandUI/Portrait"));
			m_portrait = image;
		}
		for (int i = 0; i < 6; ++i)
			UpdateButton(i);
		m_rankPanel.rva00529B6E(obj);
		if (obj)
			m_costPanel.rva0052914B(obj);
	}
	else
	{
		for (int i = 0; i < 6; ++i)
		{
			m_slots[i].m_callback.clear();
			m_slots[i].m_state = 0;
		}
	}
}

// ?rva00529FBE@PalantirCommandInterface@@QAEXXZ @0x00529FBE 7B: the outer
// class forwards to its Impl (mov ecx, [ecx]; tail jump to
// Impl::rva00529E3B above). Called at 0x002D3679 and 0x002D66C1.
// Address-named.
void PalantirCommandInterface::rva00529FBE()
{
	m_impl->rva00529E3B();
}
