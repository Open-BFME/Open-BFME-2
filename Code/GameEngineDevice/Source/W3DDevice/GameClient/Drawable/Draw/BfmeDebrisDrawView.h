#pragma once

// Shared declaration for the rowed debris animation, transfer and transform bodies.
// Field order and the second interface at +0x0C are the transfer donor's
// existing BFME 2 view, backed by ctor 0x000B1C41 and dtor 0x000B1CE2.
// Animation names and INITIAL/FLYING/FINAL come from setAnimNames' existing
// declaration; pointer types replace the transfer-only void pointers.
typedef int Int;
typedef int Color;
typedef bool Bool;
enum ShadowType { SHADOW_NONE = 0 };
#include "ascii_string.h"

class FXList;
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
class ModuleData;
class Object;
#include "../../../../../../GameEngine/Include/Common/BfmeXfer.h"

class HAnimClass;
class RenderObjClass;
class Shadow;
#include "../../../../../../GameEngine/Include/GameClient/DrawableBFME2.h"
// The transform donor uses DrawableModule: its drawable is at +0x08.
class DrawableModule {
public:
	DrawableModule(Thing *thing, const ModuleData *moduleData);
	virtual ~DrawableModule();
	void xfer(Xfer *xfer);
protected:
	const ModuleData *m_moduleData;
	Drawable *m_drawable;
	Drawable *getDrawable() { return m_drawable; }
};
class DrawModule : public DrawableModule {
public:
	DrawModule(Thing *thing, const ModuleData *moduleData);
protected:
	virtual void xfer(Xfer *xfer);
};
class DebrisDrawInterface {
public:
	virtual void setModelName(AsciiString name, Color color, ShadowType type) = 0;
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX) = 0;
};
class W3DDebrisDraw : public DrawModule, public DebrisDrawInterface {
public:
	W3DDebrisDraw(Thing *thing, const ModuleData *moduleData);
	virtual void reactToTransformChange(const Matrix3D *oldMtx, const Coord3D *oldPos, float oldAngle);
	virtual void setModelName(AsciiString name, Color color, ShadowType type);
	virtual void setAnimNames(AsciiString initial, AsciiString flying, AsciiString final, const FXList *finalFX);
protected:
	virtual void xfer(Xfer *xfer);
private:
	AsciiString m_modelName;
	Color m_modelColor;
	AsciiString m_animInitial;
	AsciiString m_animFlying;
	AsciiString m_animFinal;
	enum AnimStateType { INITIAL, FLYING, FINAL, STATECOUNT };
	RenderObjClass *m_renderObject;
	HAnimClass *m_anims[STATECOUNT];
	const FXList *m_fxFinal;
	Int m_state;
	Int m_frames;
	Bool m_finalStop;
	Shadow *m_shadow;
};
