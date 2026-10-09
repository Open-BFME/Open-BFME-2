// ?rva002739D1@Drawable@@QAEXXZ
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva002739D1@Drawable@@QAEXXZ
// Retail 0x002739D1..0x00273C47 (630 bytes). BANKED NEAR MISS (score ~0.85):
// same control flow and calls; this build keeps the player in EBX (push ebx,
// 645 vs 630 bytes) where retail spills it to [ebp-0x10] and reloads it for
// each plan query, which also shifts the new/ctor register roles. Tried:
// early-return guards, split declaration, cast-free draw calls.
//
// Zero Hour's Drawable::drawBattlePlans without the health-bar argument (the
// icon origin is the drawable's +0x460/+0x464 region corner): when the
// controlling player has battle plans active (sum of +0xAC/+0xB0/+0xB4) and
// the object qualifies (rowed Player::rva002AA0DE), each of the bombard /
// hold-the-line / search-and-destroy plans (rowed 0x002AA123, 1..3) creates
// its icon (slots 7..9 of the icon info from rowed 0x00270BA8; Anim2D from the
// icon template table g_00DFEB78 and TheAnim2DCollection) and draws it at
// x + n * width, y + height (rowed Anim2D draw 0x002D7127), else kills it
// (rowed 0x0027006C). WB twin 0x00CABB10.

class Thing;
class Object;

struct Rva002D752DNode;
class Rva002D752D;
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;

class Anim2D
{
public:
	Anim2D(Rva002D752DNode *tmpl, Rva002D752D *coll);
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
private:
	unsigned char m_pad[0x34];
};
class Rva002D7127 : public Anim2D
{
public:
	void rva002D7127(int x, int y, int width, int height);	// Anim2D::draw
};

class Rva00270025
{
public:
	virtual ~Rva00270025();
	void rva0027006C(int icon);	// killIcon
	Rva002D7127 *m_icon[14];
	unsigned int m_frame[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();	// getIconInfo
};

extern Rva002D752DNode **g_00DFEB78;	// the drawable icon animation templates

class Rva002AA123 { public: int rva002AA123(int plan); };	// getBattlePlansActiveSpecific

class Player
{
public:
	bool rva002AA0DE(const Thing *thing);	// doesObjectQualifyForBattlePlan
	int getBattlePlansActiveSpecific(int plan) { return ((Rva002AA123 *)this)->rva002AA123(plan); }
	int getNumBattlePlansActive() const { return m_searchAndDestroy + m_holdTheLine + m_bombard; }
	unsigned char m_pad00[0xAC];
	int m_bombard;			// +0xAC
	int m_holdTheLine;		// +0xB0
	int m_searchAndDestroy;		// +0xB4
};

class Object
{
public:
	Player *getControllingPlayer() const;
};

enum
{
	ICON_BATTLEPLAN_BOMBARD = 7,
	ICON_BATTLEPLAN_HOLDTHELINE = 8,
	ICON_BATTLEPLAN_SEARCHANDDESTROY = 9
};

class Drawable
{
public:
	void rva002739D1();

private:
	Rva00270025 *getIconInfo() { return ((Rva00270BA8 *)this)->rva00270BA8(); }
	void killIcon(int icon) { if (m_iconInfo) m_iconInfo->rva0027006C(icon); }

	unsigned char m_pad000[0xFC];
	Object *m_object;		// +0xFC
	unsigned char m_pad100[0x354 - 0x100];
	Rva00270025 *m_iconInfo;	// +0x354
	unsigned char m_pad358[0x460 - 0x358];
	int m_iconX;			// +0x460
	int m_iconY;			// +0x464
};

void Drawable::rva002739D1()
{
	Object *obj = m_object;
	if (!obj)
		return;
	Player *player = obj->getControllingPlayer();
	if (player && player->getNumBattlePlansActive() > 0 && player->rva002AA0DE((const Thing *)obj))
	{
		if (player->getBattlePlansActiveSpecific(1))
		{
			if (!getIconInfo()->m_icon[ICON_BATTLEPLAN_BOMBARD])
				getIconInfo()->m_icon[ICON_BATTLEPLAN_BOMBARD] = (Rva002D7127 *)new Anim2D(g_00DFEB78[ICON_BATTLEPLAN_BOMBARD], (Rva002D752D *)TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_icon[ICON_BATTLEPLAN_BOMBARD]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_icon[ICON_BATTLEPLAN_BOMBARD]->getCurrentFrameHeight();
			getIconInfo()->m_icon[ICON_BATTLEPLAN_BOMBARD]->rva002D7127(m_iconX, m_iconY + frameHeight, frameWidth, frameHeight);
		}
		else
		{
			killIcon(ICON_BATTLEPLAN_BOMBARD);
		}

		if (player->getBattlePlansActiveSpecific(2))
		{
			if (!getIconInfo()->m_icon[ICON_BATTLEPLAN_HOLDTHELINE])
				getIconInfo()->m_icon[ICON_BATTLEPLAN_HOLDTHELINE] = (Rva002D7127 *)new Anim2D(g_00DFEB78[ICON_BATTLEPLAN_HOLDTHELINE], (Rva002D752D *)TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_icon[ICON_BATTLEPLAN_HOLDTHELINE]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_icon[ICON_BATTLEPLAN_HOLDTHELINE]->getCurrentFrameHeight();
			getIconInfo()->m_icon[ICON_BATTLEPLAN_HOLDTHELINE]->rva002D7127(m_iconX + frameWidth, m_iconY + frameHeight, frameWidth, frameHeight);
		}
		else
		{
			killIcon(ICON_BATTLEPLAN_HOLDTHELINE);
		}

		if (player->getBattlePlansActiveSpecific(3))
		{
			if (!getIconInfo()->m_icon[ICON_BATTLEPLAN_SEARCHANDDESTROY])
				getIconInfo()->m_icon[ICON_BATTLEPLAN_SEARCHANDDESTROY] = (Rva002D7127 *)new Anim2D(g_00DFEB78[ICON_BATTLEPLAN_SEARCHANDDESTROY], (Rva002D752D *)TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_icon[ICON_BATTLEPLAN_SEARCHANDDESTROY]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_icon[ICON_BATTLEPLAN_SEARCHANDDESTROY]->getCurrentFrameHeight();
			getIconInfo()->m_icon[ICON_BATTLEPLAN_SEARCHANDDESTROY]->rva002D7127(m_iconX + frameWidth * 2, m_iconY + frameHeight, frameWidth, frameHeight);
		}
		else
		{
			killIcon(ICON_BATTLEPLAN_SEARCHANDDESTROY);
		}
	}
}
