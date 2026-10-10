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
// refresh 0x00529E3B, lives here too; the rank/timer panel update it calls
// (0x00529B6E, also a walker user) is pinned and banked. The rest of
// PalantirCommandInterface.cpp's native range stays in the units that
// already row it; this one holds the selection-walk family.

#include <list>
#include "ascii_string.h"

typedef bool Bool;

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

#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

// The Apt window manager's portrait image set (0x002239E2) and clear
// (0x00223A94) under their rowed address-derived spellings.
class Rva002239B2 { public: void rva002239E2(const AsciiString &name, const Image *image); };
class Rva00223A94 { public: int rva00223A94(const AsciiString *name); };
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

class Rva002BED91 { public: void clear(); };
class Rva00529B6E { public: void rva00529B6E(Object *obj); private: char m_data[0x18]; };
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
