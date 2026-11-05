// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "reference/shims/moduledata/Common/Snapshot.h"
// ?rva00273755@Drawable@@QAEXXZ @0x00273755 179B: Drawable anim draw with verified retail literal 0.5f via rowed getter 0x00270BA8 and Anim2D width/height plus draw 0x002D7127; tail to 0x002736A8 on stale frame.
// Evidence: offsets +0x354/+0x2C/+0x64 match Rva00270025 layout, TheGameLogic+0x40 frame check, m_460/m_468/m_46C rect math, callers 0x00279734, neighbours Drawable_rva00273648.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;

class Anim2DTemplate;
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;
struct Rva002D752DNode;
class Anim2D : public Snapshot
{
public:
    Anim2D(Anim2DTemplate *, Anim2DCollection *);
	unsigned int getCurrentFrameWidth() const;
	unsigned int getCurrentFrameHeight() const;
protected:
    virtual ~Anim2D();
    virtual void loadPostProcess();
    virtual const char *GetSnapshotName() const;
    virtual void xfer(Xfer *);
private:
    char m_storage[0x30];
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





class Player;
#include "../../Include/GameClient/ImageClass.h"

#include "../../Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

#include "../../Include/Common/PlayerList.h"
extern PlayerList *ThePlayerList;

#include "../../Include/GameClient/InGameUI.h"
extern InGameUI *TheInGameUI;
#include "../../Include/GameClient/View.h"
extern View *TheTacticalView;
#include "../../Include/GameClient/Display.h"
extern Display *TheDisplay;

#include "../../Include/Common/Geometry.h"

struct DrawableKindWordView {char pad[0x108];unsigned bits;};
struct DrawableBonusWordView {
    unsigned bits;
    __forceinline unsigned char shifted(unsigned n) const { return bits>>n; }
};
class Object
{
public:
    void *m_vtable;
    void *m_template;
    char m_unknown008[0x380-8];
    DrawableBonusWordView m_bonus380;
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

class Drawable
{
public:
    void rva00273755();
    void rva002736A8();
    void drawAmmo();
    void rva00273F74();
private:
    void *m_vtable;
    void *m_template;
    unsigned char m_pad008[0xfc-8];
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

// ZH Drawable::drawEnthusiastic is the guide. Retail 273F74..27411F
// independently tests Object+380 bits8/15 and selects slots11/12 from the
// named template array. Scale is target template+108 sign-bit/2000/200;
// target Y uses the drawable bottom edge directly (no donor height term).
void Drawable::rva00273F74()
{
    const Object *obj = m_object;
    if (obj->m_bonus380.shifted(8)&1) {
        int icon = 11;
        if (obj->m_bonus380.shifted(15)&1) icon=12;
        if (getIconInfo()->m_items[icon]==0)
            getIconInfo()->m_items[icon]=(Rva002D7127*)new Anim2D((Anim2DTemplate*)s_animationTemplates[icon],TheAnim2DCollection);
        if (getIconInfo()->m_items[icon]!=0) {
            int barWidth = m_468-m_460;
            unsigned kind = ((const DrawableKindWordView*)m_template)->bits;
            Real scale;
            if ((kind&0x80) || (kind&0x2000)) scale=1.0f;
            else if (kind&0x200) scale=0.75f;
            else scale=0.5f;
            int frameWidth=(int)(getIconInfo()->m_items[icon]->getCurrentFrameWidth()*scale);
            int frameHeight=(int)(getIconInfo()->m_items[icon]->getCurrentFrameHeight()*scale);
            ICoord2D screen;
            screen.x=(int)((float)m_460+(barWidth*0.25f)-(frameWidth*0.5f));
            screen.y=m_46c;
            getIconInfo()->m_items[icon]->queue(screen.x,screen.y,frameWidth,frameHeight);
        }
    } else {
        killIcon(11);
        killIcon(12);
    }
}
