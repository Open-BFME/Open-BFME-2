// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /ICode/Libraries/Include/Lib
//
// ?iterateDrawablesInRegion@W3DView@@UAEHPAUIRegion2D@@P6AHPAVDrawable@@PAX@Z2@Z
// retail 0x00086245..0x0008647C (567 bytes RET 0x0C). It is slot 10 of the
// W3DView vtable at 0x007C7568 (pickDrawable slot 9 / setWidth 14 / getWidth
// 15 / setHeight 16 / getHeight 17 are the neighbours). The body follows the
// Zero Hour W3DView::iterateDrawablesInRegion spine through the Open-BFME-1 donor
// game/GameEngineDevice/Source/W3DDevice/GameClient/W3DViewIterateDrawablesInRegionBfme.cpp
// (75fe8bad1b2244e6bc97ae83fbfc96e10d1a302d).
// The steps: normalize the screen region against the origin (+0x20/+0x24) and the
// view size / pick a single drawable when the region is a point (pick mask
// from rowed Rva0030F099 of TheInGameUI's +0x8B8 force-attack byte OR 0x100)
// / walk TheGameClient's drawables (slot 17 / next at +0x104) projecting
// each position (pinned Drawable::getPosition 0x002763E6) through the +0x104
// camera (rowed CameraClass::Project 0x00135390).
// BFME 2 target facts: the callback returns an int and is compared with
// 0 and 1 (eax tests), so it is typed Int. A result of 0 counts the drawable
// and a result of 1 sets the count to 1.
#include "Coord3D.h"

typedef int Int;
typedef float Real;
typedef bool Bool;
typedef unsigned int UnsignedInt;

struct ICoord2D
{
	Int x;
	Int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

class Vector3
{
public:
	Real X;
	Real Y;
	Real Z;
};

class CameraClass
{
public:
	enum ProjectionResType
	{
		INSIDE_FRUSTUM,
		OUTSIDE_FRUSTUM,
		OUTSIDE_NEAR_CLIP,
		OUTSIDE_FAR_CLIP
	};
	ProjectionResType Project(Vector3 &dest, const Vector3 &ws_point) const;
};

enum PickType
{
	PICK_TYPE_FORCE_32 = 0x7fffffff
};

class Drawable
{
public:
	const Coord3D *getPosition() const;
	Drawable *getNextDrawable() const { return m_nextDrawable; }
private:
	unsigned char m_pad00[0x104];
	Drawable *m_nextDrawable;				// +0x104
};

class GameClientView
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16)
#undef V
	virtual Drawable *firstDrawable();		// slot 17
};

class GameClient;
extern GameClient *TheGameClient;

class InGameUI
{
public:
	Bool isInForceAttackMode() const { return m_forceAttackMode; }
private:
	unsigned char m_pad00[0x8B8];
	Bool m_forceAttackMode;					// +0x8B8
};
extern InGameUI *TheInGameUI;

UnsignedInt Rva0030F099(Bool forceAttackMode);

class W3DView
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
#undef V
	virtual Drawable *pickDrawable(const ICoord2D *screen, Bool forceAttack, PickType pickType);	// slot 9
	virtual Int iterateDrawablesInRegion(IRegion2D *screenRegion,
		Int (*callback)(Drawable *draw, void *userData), void *userData);					// slot 10
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void setWidth(Int width);		// slot 14
	virtual Int getWidth();					// slot 15
	virtual void setHeight(Int height);		// slot 16
	virtual Int getHeight();				// slot 17
protected:
	unsigned char m_pad04[0x20 - 0x04];
	Int m_originX;							// +0x20
	Int m_originY;							// +0x24
	unsigned char m_pad28[0x104 - 0x28];
	CameraClass *m_3DCamera;				// +0x104
};

Int W3DView::iterateDrawablesInRegion(IRegion2D *screenRegion,
	Int (*callback)(Drawable *draw, void *userData), void *userData)
{
	Int count = 0;
	Drawable *draw;
	Vector3 screen, world, pos;
	Real normalizedRegion[4];
	Bool regionIsPoint = false;

	if (screenRegion)
	{
		if (screenRegion->hi.y - screenRegion->lo.y == 0 &&
			screenRegion->hi.x - screenRegion->lo.x == 0)
		{
			regionIsPoint = true;
		}
		normalizedRegion[0] = ((Real)(screenRegion->lo.x - m_originX) / (Real)getWidth()) * 2.0f - 1.0f;
		normalizedRegion[1] = -(((Real)(screenRegion->hi.y - m_originY) / (Real)getHeight()) * 2.0f - 1.0f);
		normalizedRegion[2] = ((Real)(screenRegion->hi.x - m_originX) / (Real)getWidth()) * 2.0f - 1.0f;
		normalizedRegion[3] = -(((Real)(screenRegion->lo.y - m_originY) / (Real)getHeight()) * 2.0f - 1.0f);
	}

	Drawable *onlyDrawableToTest = 0;
	if (regionIsPoint)
	{
		PickType pickType = (PickType)(Rva0030F099(TheInGameUI->isInForceAttackMode()) | 0x100);
		onlyDrawableToTest = pickDrawable(&screenRegion->lo, true, pickType);
		if (onlyDrawableToTest == 0)
			return 0;
	}

	for (draw = ((GameClientView *)TheGameClient)->firstDrawable(); draw; draw = draw->getNextDrawable())
	{
		Bool inside;
		if (onlyDrawableToTest)
		{
			draw = onlyDrawableToTest;
			inside = true;
		}
		else
		{
			inside = false;
			if (screenRegion == 0)
			{
				inside = true;
			}
			else
			{
				pos = *(const Vector3 *)draw->getPosition();
				world.X = pos.X;
				world.Y = pos.Y;
				world.Z = pos.Z;
				if (m_3DCamera->Project(screen, world) == CameraClass::INSIDE_FRUSTUM &&
					screen.X >= normalizedRegion[0] &&
					screen.X <= normalizedRegion[2] &&
					screen.Y >= normalizedRegion[1] &&
					screen.Y <= normalizedRegion[3])
				{
					inside = true;
				}
			}
		}
		if (inside)
		{
			Int result = callback(draw, userData);
			if (result == 0)
				++count;
			else if (result == 1)
				count = 1;
		}
		if (onlyDrawableToTest)
			break;
	}
	return count;
}
