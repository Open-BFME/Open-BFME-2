// ?rva00273DCF@Drawable@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /I. /ICode/Libraries/Include
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
#include "Lib/ICoord2D.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
// ?rva00273755@Drawable@@QAEXXZ @0x00273755 179B: Drawable anim draw with verified retail literal 0.5f via rowed getter 0x00270BA8 and Anim2D width/height plus draw 0x002D7127; tail to 0x002736A8 on stale frame.
// Evidence: offsets +0x354/+0x2C/+0x64 match Rva00270025 layout, TheGameLogic+0x40 frame check, m_460/m_468/m_46C rect math, callers 0x00279734, neighbours Drawable_rva00273648.
#include "../Common/GameLogicObjectLookupView.h"
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

struct DrawableKindByteView {char pad[0x108];unsigned char bits;};
struct DrawableKindWordView {char pad[0x108];unsigned bits;};
struct DrawableBonusWordView {
    unsigned bits;
    __forceinline unsigned char shifted(unsigned shiftCount) const { return bits>>shiftCount; }
};
enum ObjectStatusTypes;
extern unsigned BfmeHealingIconDisplayFrames;
class ObjectBody254
{
public:
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual float f4();
	virtual void f5();
	virtual float f6();
	virtual void f7();
	virtual void f8();
	virtual void f9();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual unsigned int f17();
};


class Object
{
public:
    void *m_vtable;
    void *m_template;
    char m_unknown008[0x254-8];
    ObjectBody254 *m_body254;
    char m_unknown258[0x380-0x258];
    DrawableBonusWordView m_bonus380;
	Player *getControllingPlayer() const;
    bool testStatus(ObjectStatusTypes) const;
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
    void rva00273DCF();
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
    void killIcon(int iconIndex) { if(m_354) m_354->rva0027006C(iconIndex); }
    static Rva002D752DNode **s_animationTemplates;
    static const Image *s_fullAmmo;
    static const Image *s_emptyAmmo;
};

// Drawable::rva00273755 (0x00273755) and Drawable::drawAmmo (0x00273808) are
// rowed in Drawable_rva00273755.cpp; this unit never calls them.


// ZH Drawable::drawHealing guide. Native template byte10D/bit4 and status19
// gates plus body-health callbacks and duration comparisons prove its role.
// Independently recovered initializer7ADF60 supplies the existing single
// duration datum. Template array and Anim2D constructor use owned providers.
void Drawable::rva00273DCF()
{
	Drawable *self = this;
	Object *object = self->m_object;
	if ((((const unsigned char *)object->m_template)[0x10d] & 4) != 0)
		return;
	if (object->testStatus((ObjectStatusTypes)0x13))
		return;

	ObjectBody254 *body = object->m_body254;
	bool update = false;
	float first = body->f4();
	if (first != body->f6()) {
		unsigned int frame = TheGameLogic->getFrame();
		if (frame > BfmeHealingIconDisplayFrames && frame - body->f17() <= BfmeHealingIconDisplayFrames)
			update = true;
	}

	unsigned int slot;
	if ((((((const DrawableKindByteView *)self->m_template) ? ((const DrawableKindByteView *)self->m_template) : ((const DrawableKindByteView *)self->m_template)))->bits & 0x80) != 0)
		slot = 1;
	else
		slot = (((const DrawableKindWordView *)self->m_template)->bits >> 8) & 2;

	if (update) {
		unsigned int idx = slot * 4;
		if (*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx) == 0) {
			Anim2D *anim = new Anim2D((Anim2DTemplate *)s_animationTemplates[slot], TheAnim2DCollection);
			*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx) = (Rva002D7127 *)anim;
		}
		if (*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx) != 0) {
			int dw = self->m_468 - self->m_460;
			int width = (*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx))->getCurrentFrameWidth();
			int height = (*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx))->getCurrentFrameHeight();
			int x = (int)((float)dw * 0.75f + (float)self->m_460 - (float)width * 0.5f);
			int y = self->m_464 - height;
			(*(Rva002D7127 **)((char *)((Rva00270BA8 *)self)->rva00270BA8()->m_items + idx))->queue(x, y, width, height);
		}
	} else if (self->m_354 != 0) {
		self->m_354->rva0027006C((int)slot);
	}
}
