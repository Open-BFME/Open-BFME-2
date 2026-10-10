// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?xfer@CrateCollide@@MAEXPAVXfer@@@Z, retail 0x004BC617 64B: slot 3 (offset 0x0C)
// of vtable 0x0085A618 (class of rowed dtor ??1Rva004BC4FC@@UAE@XZ, the opaque
// CrateCollide dtor immediately before rowed ctor ??0CrateCollide at 0x004BC523).
// Version(1,2) via Xfer slot 0x28 then the rowed Rva004CE56D::xfer at
// 0x004CE56D, then bool at +0x14 via Xfer slot 0x90 gated on version>=2.
// Layout is the rowed 0x14-byte CollideModule base from CrateCollideConstructor
// plus bool m_everExecuted at +0x14. Donor is ZH CrateCollide::xfer (Version 1
// plus CollideModule base); BFME2 adds the bool and bumps to (1,2).

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class Thing;
#include "ascii_string.h"
class ModuleData;

class Xfer
{
public:
	class Version;

	Xfer();
	virtual ~Xfer();

	void Version1();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class BehaviorModule
{
public:
	BehaviorModule(Thing *thing, const ModuleData *moduleData);

	virtual void behaviorModuleAnchor();

private:
	unsigned char m_data[8];
};

class InlineCollideModuleInterface
{
public:
	virtual void collideModuleInterfaceAnchor();
};

class Object;
struct Coord3D;

// The collide interface at +0x10 (vftable 0x00C5A600): onCollide is slot 0.
class ModuleInterface
{
public:
	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal) = 0;
};

class CollideModule : public BehaviorModule,
	public InlineCollideModuleInterface,
	public ModuleInterface
{
public:
	CollideModule(Thing *thing, const ModuleData *moduleData);
	void xfer(Xfer *xfer);
};

class Rva004CE56D
{
public:
	void xfer(Xfer *xfer);
};

class CrateCollide : public CollideModule
{
public:
	CrateCollide(Thing *thing, const ModuleData *moduleData);

	virtual void onCollide(Object *other, const Coord3D *loc, const Coord3D *normal);

protected:
	virtual void xfer(Xfer *xfer);

private:
	bool m_everExecuted;
};

void CrateCollide::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	((Rva004CE56D *)this)->xfer(xfer);
	if (version.m_minimum >= 2) {
		*xfer == m_everExecuted;
	}
}

// ?onCollide@CrateCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z, retail 0x004BC56D
// 170B (RET 12), slot 0 of the collide interface (this = module +0x10).
// Zero Hour's CrateCollide::onCollide; BFME 2 records m_everExecuted before
// the crate is destroyed. isValidToExecute and executeCrateBehavior are the
// primary-table slots +0x34/+0x30; module data +0x48 execute FX, +0x4C pickup
// animation name, +0x50/+0x54 its display time and z rise. The animation
// lookup is the address-named 0x002D752D on TheAnim2DCollection.
struct CrateCollideModuleData
{
	unsigned char m_pad00[0x48];
	const class FXList *m_executeFX;		// +0x48
	AsciiString m_pickupAnimation;			// +0x4C
	float m_pickupAnimDisplayTimeInSeconds;		// +0x50
	float m_pickupAnimZRise;			// +0x54
};
struct CrateCollideModuleFields { void *m_vptr; const CrateCollideModuleData *m_moduleData; Object *m_object; };
struct CrateCollideSlots
{
#define SLOT(N) virtual void slot##N();
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07) SLOT(08) SLOT(09) SLOT(10) SLOT(11)
#undef SLOT
	virtual bool executeCrateBehavior(Object *other);	// +0x30
	virtual bool isValidToExecute(const Object *other) const;	// +0x34
};
class FXList { public: static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary); };
#include "../../../../Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct GameLogicDrawIconUIView { unsigned char m_pad00[0x9A]; bool m_drawIconUI; };
struct Rva002D752DNode;
class Rva002D752D { public: Rva002D752DNode *rva002D752D(const StringBase<char> &name); };
class Anim2DCollection;
extern Anim2DCollection *TheAnim2DCollection;
class Anim2DTemplate;
enum WorldAnimationOptions { WORLD_ANIM_FADE_ON_EXPIRE = 1 };
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"
struct ObjectPositionView { unsigned char m_pad00[0x38]; Coord3D m_pos; };
class InGameUI { public: void addWorldAnimation(Anim2DTemplate *anim, const Coord3D *pos, WorldAnimationOptions options, float durationInSeconds, float zRisePerSecond); };
extern InGameUI *TheInGameUI;

void CrateCollide::onCollide(Object *other, const Coord3D *loc, const Coord3D *normal)
{
	const CrateCollideModuleData *modData = reinterpret_cast<CrateCollideModuleFields *>(this)->m_moduleData;
	CrateCollideSlots *crate = reinterpret_cast<CrateCollideSlots *>(this);

	// If the crate can be picked up, perform the game logic and destroy the crate.
	if( crate->isValidToExecute( other ) )
	{
		if( crate->executeCrateBehavior( other ) )
		{
			if( modData->m_executeFX != 0 )
				FXList::doFXObj( modData->m_executeFX, other, 0 );
			m_everExecuted = true;
			TheGameLogic->destroyObject( reinterpret_cast<CrateCollideModuleFields *>(this)->m_object );
		}

		// play animation in the world at this spot if there is one
		if( TheAnim2DCollection && modData->m_pickupAnimation.isEmpty() == false &&
			reinterpret_cast<GameLogicDrawIconUIView *>(TheGameLogic)->m_drawIconUI )
		{
			Anim2DTemplate *animTemplate = reinterpret_cast<Anim2DTemplate *>(
				reinterpret_cast<Rva002D752D *>(TheAnim2DCollection)->rva002D752D( *reinterpret_cast<const StringBase<char> *>(&modData->m_pickupAnimation) ));
			TheInGameUI->addWorldAnimation( animTemplate,
				&reinterpret_cast<ObjectPositionView *>(reinterpret_cast<CrateCollideModuleFields *>(this)->m_object)->m_pos,
				WORLD_ANIM_FADE_ON_EXPIRE,
				modData->m_pickupAnimDisplayTimeInSeconds,
				modData->m_pickupAnimZRise );
		}
	}
}
