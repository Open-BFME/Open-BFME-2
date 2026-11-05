// cl: /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"
// ?rva00273755@Drawable@@QAEXXZ @0x00273755 179B: Drawable anim draw with verified retail literal 0.5f via rowed getter 0x00270BA8 and Anim2D width/height plus draw 0x002D7127; tail to 0x002736A8 on stale frame.
// Evidence: offsets +0x354/+0x2C/+0x64 match Rva00270025 layout, TheGameLogic+0x40 frame check, m_460/m_468/m_46C rect math, callers 0x00279734, neighbours Drawable_rva00273648.
#include "../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Anim2DTemplate;
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;
struct Rva002D752DNode;
#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"
class Anim2D : public Snapshot
{
public:
    Anim2D(Anim2DTemplate *animTemplate, Anim2DCollection *collectionSystem);
    void randomizeCurrentFrame();
    void reset();
    unsigned int getCurrentFrameHeight() const;
    unsigned int getCurrentFrameWidth() const;
protected:
    virtual ~Anim2D();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    unsigned short m_currentFrame;
    unsigned int m_lastUpdateFrame;
    Anim2DTemplate *m_template;
    unsigned char m_status;
    unsigned short m_minFrame, m_maxFrame;
    unsigned int m_framesBetweenUpdates;
    float m_alpha;
    Anim2DCollection *m_collectionSystem;
    Anim2D *m_collectionSystemNext, *m_collectionSystemPrev;
    unsigned int m_cachedWidth, m_cachedHeight;
};
class Rva002D7127 : public Anim2D
{
public:
	void queue(int x, int y, int width, int height);
};

class Rva00270025
{
public:
	virtual ~Rva00270025();
    void rva0027006C(int);
	Rva002D7127 *m_items[14];
	unsigned int m_vals[14];
};

class Rva00270BA8
{
public:
	Rva00270025 *rva00270BA8();
	char m_pad00[0x354];
private:
	Rva00270025 *m_354; // +0x354
};

typedef float Real;
typedef int Int;
typedef bool Bool;





class Thing;
class Object;
class Rva002AA123 {public:int rva002AA123(int);};
class Player {
public:
    bool doesObjectQualifyForBattlePlan(Object *obj) const;
    int getBattlePlansActiveSpecific(int n) {return ((Rva002AA123*)this)->rva002AA123(n);}
    int getNumBattlePlansActive() const {return m_searchAndDestroy+m_holdTheLine+m_bombard;}
    char m_pad000[0xac];
    int m_bombard, m_holdTheLine, m_searchAndDestroy;
};
#include "../../Include/GameClient/ImageClass.h"

#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
class View
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72(); virtual void slot73(); virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	virtual void slot78(); virtual void slot79(); virtual void slot80(); virtual void slot81(); virtual void slot82(); virtual void slot83();
	virtual void slot84(); virtual void slot85(); virtual void slot86(); virtual void slot87();
	virtual Int worldToScreen(const Coord3D *, ICoord2D *);
};
extern View *TheTacticalView;
#include "../../Include/GameClient/Display.h"
extern Display *TheDisplay;

#include "../../Include/Common/Geometry.h"

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool getAmmoPipShowingInfo(void **outCapacity, unsigned *outAmmo) const;
	const Coord3D *getPosition() const
	{
		return reinterpret_cast<const Coord3D *>(reinterpret_cast<const char *>(this) + 0x38);
	}
	const GeometryInfo &getGeometryInfo() const
	{
		return *reinterpret_cast<const GeometryInfo *>(reinterpret_cast<const char *>(this) + 0xA8);
	}
};

struct Rva00277669AIView
{
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43(); virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47(); virtual void v48(); virtual void v49();
	virtual void v50(); virtual void v51(); virtual void v52(); virtual void v53(); virtual void v54(); virtual void v55();
	virtual Player *slot56();
	virtual void v57(); virtual void v58(); virtual void v59(); virtual void v60(); virtual void v61(); virtual void v62(); virtual void v63(); virtual void v64(); virtual void v65(); virtual void v66(); virtual void v67(); virtual void v68(); virtual void v69();
	virtual void v70(); virtual void v71(); virtual void v72(); virtual void v73(); virtual void v74(); virtual void v75(); virtual void v76(); virtual void v77(); virtual void v78(); virtual void v79();
	virtual void v80(); virtual void v81(); virtual void v82(); virtual void v83();
	virtual Bool slot84(Int *, Int *, Int *, Int *, Int *, Int *);
};
struct Rva00277669ObjectView
{
	char m_pad000[0x250];
	Rva00277669AIView *m_ai;
};
struct Rva00277669PlayerView
{
	char m_pad000[0x280];
	Int m_color;
};

class Drawable
{
public:
    void rva00273755();
    void rva002736A8();
    void drawAmmo();
    void rva002739D1();
    void rva00277669();
    const Coord3D *getPosition() const;
private:
    unsigned char m_pad000[0xfc];
    Object *m_object;
    int m_id;
    unsigned char m_pad104[0x354-0x104];
    Rva00270025 *m_354;
    unsigned char m_pad358[0x43c-0x358];
    bool m_selected;
    unsigned char m_pad43d[0x460-0x43d];
    int m_460, m_464, m_468, m_46c;
    Rva00270025 *getIconInfo() { return ((Rva00270BA8 *)this)->rva00270BA8(); }
    void killIcon(int n) { if(m_354) m_354->rva0027006C(n); }
    static Rva002D752DNode **s_animationTemplates;
    static const Image *s_fullAmmo;
    static const Image *s_emptyAmmo;
    static const Image *s_pipImage;
    static const Image *s_pipOverlay;
};

__declspec(noinline) inline void Drawable::rva00273755()
{
	if (m_354 == 0)
		return;
	if (((Rva00270BA8 *)this)->rva00270BA8()->m_items[10] == 0)
		return;
	unsigned int cur = TheGameLogic->getFrame();
	unsigned int v = ((Rva00270BA8 *)this)->rva00270BA8()->m_vals[10];
	if (v >= cur) {
		int dw = m_468 - m_460;
		int w = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameWidth();
		int h = ((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->getCurrentFrameHeight();
		int y = m_46c - h;
		int x = (int)((float)dw * 0.5f + (float)m_460 - (float)w * 0.5f);
		((Rva00270BA8 *)this)->rva00270BA8()->m_items[10]->queue(x, y, w, h);
	} else {
		rva002736A8();
	}
}

// BFME1 cee35b7d8 Drawable_drawAmmo.cpp and ZH Drawable.cpp are semantic
// guides. Target 273808..2739D1 independently shows the 43C gate, FC Object,
// full/empty images, 28AEF5 ammo pair, 460 left edge, and UI/View/Display slots.
// Target offsets DC/F8/9BD differ from donor GlobalData. The actual writable
// singleton is used; the position aggregate keeps the donor scalar-copy shape.
__declspec(noinline) inline void Drawable::drawAmmo()
{
    const Object *obj = m_object;
    if (!TheWritableGlobalData->m_showObjectHealth) return;
    if (!m_selected) {
        InGameUI *ui = TheInGameUI;
        if (!ui) return;
        Int drawableID = m_id;
        if (ui->getMousedOverDrawableID() != drawableID) return;
    }
    Player *localPlayer = ThePlayerList->getLocalPlayer();
    if (obj->getControllingPlayer() != localPlayer) return;
    Int numTotal, numFull;
    if (!obj->getAmmoPipShowingInfo(reinterpret_cast<void **>(&numTotal), reinterpret_cast<unsigned *>(&numFull))) return;
    if (!s_fullAmmo) return;
    const Image *emptyAmmo = s_emptyAmmo;
    if (!emptyAmmo) return;
    Real scale = 1.0f;
    Int boxWidth = (Int)((Real)emptyAmmo->getImageWidth()*scale);
    Int boxHeight = (Int)((Real)emptyAmmo->getImageHeight()*scale);
    ICoord2D screenCenter;
    Coord3D pos = {obj->getPosition()->x, obj->getPosition()->y, obj->getPosition()->z};
    pos.x += TheWritableGlobalData->m_ammoPipWorldOffset.x;
    pos.y += TheWritableGlobalData->m_ammoPipWorldOffset.y;
    pos.z += TheWritableGlobalData->m_ammoPipWorldOffset.z + obj->getGeometryInfo().getMaxHeightAbovePosition();
    if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0) return;
    Real bounding = obj->getGeometryInfo().m_boundingSphereRadius*scale;
    Int posx = m_460;
    Int posy = screenCenter.y + (Int)(TheWritableGlobalData->m_ammoPipScreenOffset.y*bounding);
    for (Int i=0; i<numTotal; ++i) {
        TheDisplay->drawImage(i<numFull ? s_fullAmmo : s_emptyAmmo, posx, posy+1,
            posx+boxWidth, posy+1+boxHeight, -1, 2);
        posx += boxWidth + 1;
    }
}

// ZH Drawable::drawBattlePlans is the semantic guide (BF1 cee35b7d8);
// WB CABB10 and complete native 2739D1..273C47 establish the renderer
// relationship, target no-argument ABI, player eligibility, slots7..9,
// and native rect members460/464. Original target spelling remains unknown.
// A volatile player carrier preserves the witnessed reloads per plan;
// eligibility uses the unqualified result. Snapshot-derived Anim2D is the
// owned 52-byte class from 2D6D63, replacing the old opaque storage view.
// Capture Y then X before getIconInfo; this retains height in EAX and width
// in EDI and pushes arguments before the getter. For the third icon, capture
// only the left edge and keep left+width*2 inside the call argument.
// Native allocation, constructor, draw, kill and EH relationships all match.
void Drawable::rva002739D1()
{
	Object *obj = m_object;
	if (!obj)
		return;
	Player *active = obj->getControllingPlayer();
    Player *volatile player = active;
	if (active && active->getNumBattlePlansActive() > 0 && active->doesObjectQualifyForBattlePlan(obj))
	{
		if (player->getBattlePlansActiveSpecific(1))
		{
			if (!getIconInfo()->m_items[7])
				getIconInfo()->m_items[7] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[7], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[7]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[7]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460;
            getIconInfo()->m_items[7]->queue(x,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(7);
		}

		if (player->getBattlePlansActiveSpecific(2))
		{
			if (!getIconInfo()->m_items[8])
				getIconInfo()->m_items[8] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[8], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[8]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[8]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460 + frameWidth;
            getIconInfo()->m_items[8]->queue(x,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(8);
		}

		if (player->getBattlePlansActiveSpecific(3))
		{
			if (!getIconInfo()->m_items[9])
				getIconInfo()->m_items[9] = (Rva002D7127 *)new Anim2D((Anim2DTemplate *)s_animationTemplates[9], TheAnim2DCollection);
			int frameWidth = getIconInfo()->m_items[9]->getCurrentFrameWidth();
			int frameHeight = getIconInfo()->m_items[9]->getCurrentFrameHeight();
			int y=m_464+frameHeight;
            int x=m_460;
            getIconInfo()->m_items[9]->queue(x+frameWidth*2,y,frameWidth,frameHeight);
		}
		else
		{
			killIcon(9);
		}
	}
}

// Native 277669..2778E1 (632B), no-argument thiscall. Same pip row as drawAmmo
// but driven by the object's AI interface (+0x250): slot 56 is a second owner
// check, slot 84 returns six counts (total, full, four unused). Tint is the
// controlling player's color (+0x280) for filled pips, grey otherwise.
static inline Int GameMakeColor(Int r, Int g, Int b, Int a) { return (a << 24) | (r << 16) | (g << 8) | b; }

void Drawable::rva00277669()
{
    Object *obj = m_object;
    Rva00277669AIView *ai = ((Rva00277669ObjectView *)obj)->m_ai;
    if (!ai) return;
    if (!TheWritableGlobalData->m_showObjectHealth) return;
    if (!m_selected) {
        InGameUI *ui = TheInGameUI;
        if (!ui) return;
        Int drawableID = m_id;
        if (ui->getMousedOverDrawableID() != drawableID) return;
    }
    if (obj->getControllingPlayer() != ThePlayerList->getLocalPlayer()
        && ai->slot56() != ThePlayerList->getLocalPlayer()) return;
    Int numTotal, numFull, unused0, unused1, unused2, unused3;
    if (!ai->slot84(&numTotal, &numFull, &unused0, &unused1, &unused2, &unused3)) return;
    Real scale = 1.0f;
    Int boxWidth = (Int)((Real)s_pipImage->getImageWidth()*scale);
    Int boxHeight = (Int)((Real)s_pipImage->getImageHeight()*scale);
    ICoord2D screenCenter;
    const Coord3D *objPos = getPosition();
    Coord3D pos = {objPos->x, objPos->y, objPos->z};
    pos.x += TheWritableGlobalData->m_containerPipWorldOffset.x;
    pos.y += TheWritableGlobalData->m_containerPipWorldOffset.y;
    pos.z += TheWritableGlobalData->m_containerPipWorldOffset.z + obj->getGeometryInfo().getMaxHeightAbovePosition();
    if (TheTacticalView->worldToScreen(&pos, &screenCenter) != 0) return;
    Real bounding = obj->getGeometryInfo().m_boundingSphereRadius*scale;
    Int posx = m_460;
    Int posy = screenCenter.y + (Int)(TheWritableGlobalData->m_containerPipScreenOffset.y*bounding);
    static const Int emptyColor = GameMakeColor(127, 127, 127, 255);
    Player *owner = obj->getControllingPlayer();
    Int ownerColor = owner ? ((Rva00277669PlayerView *)owner)->m_color : -1;
    for (Int i=0; i<numTotal; ++i) {
        TheDisplay->drawImage(s_pipImage, posx, posy, posx+boxWidth, posy+boxHeight, i<numFull ? ownerColor : emptyColor, 2);
        TheDisplay->drawImage(s_pipOverlay, posx, posy, posx+boxWidth, posy+boxHeight, -1, 2);
        posx += boxWidth + 1;
    }
}
// Select-any: another unit compiles a copy of the same names; the anchor keeps the rowed bodies emitted.
// ?bfmeAnchorDrawableRva00273755 absent-from-retail
void bfmeAnchorDrawableRva00273755(Drawable *drawable) { drawable->rva00273755(); drawable->drawAmmo(); }
