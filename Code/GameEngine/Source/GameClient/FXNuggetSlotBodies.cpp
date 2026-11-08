// cl: /DNDEBUG /MD
//
// FX nugget doFXPos/doFXObj slot bodies (classes, member offsets and type ids
// as in their ctor units; behaviour follows Zero Hour's FXList.cpp). Kept out
// of FXList.cpp's ZH port, whose inline copies have Zero Hour's 5-argument
// doFXPos and so never share a name with these.
//
// ?doFXPos@CameraShakerVolumeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z 62B @0x001E0760
// ?doFXObj@CameraShakerVolumeFXNugget@@UBEXPBVObject@@0@Z 65B @0x001E079E
//     slots 1 and 2 of vtable 0x00BDD7CC: TheTacticalView->Add_Camera_Shake
//     (View slot 0xA8) at the position (or the object's +0x38 position) with
//     the radius/duration/amplitude at +0x154/+0x158/+0x15C.
// ?doFXPos@ViewShakeFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z 39B @0x001E0802
//     slot 1 of vtable 0x00BDD7E0: TheTacticalView->shake (View slot 0x1AC)
//     with the shake type at +0x148, when both the position and the view exist.
// ?doFXPos@LightPulseFXNugget@@UBEXPBUCoord3D@@PBVMatrix3D@@M0@Z 65B @0x001E0373
//     slot 1 of vtable 0x00BDD790 (doFXObj is LightPulseFXNuggetEffects.cpp's):
//     TheDisplay->createLightPulse (Display slot 0xBC) with the color at +0x148,
//     inner radius 1, the radius at +0x154 and the frame counts at +0x15C/+0x160.

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

class Matrix3D;

#include "../GameLogic/Object/object.h"

#include "../../Include/GameClient/View.h"

extern View *TheTacticalView;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const = 0;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class CameraShakerVolumeFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;
	virtual void doFXObj(const Object *primary, const Object *secondary) const;

private:
	float m_fieldB4; // +0x148
	float m_fieldB8; // +0x14C
	float m_fieldBC; // +0x150
	float m_radius; // +0x154
	float m_durationSeconds; // +0x158
	float m_amplitudeDegrees; // +0x15C
};

void CameraShakerVolumeFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const
{
	if (primary)
	{
		TheTacticalView->Add_Camera_Shake(*primary, m_radius, m_durationSeconds, m_amplitudeDegrees);
	}
}

void CameraShakerVolumeFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		TheTacticalView->Add_Camera_Shake(*primary->getPosition(), m_radius, m_durationSeconds, m_amplitudeDegrees);
	}
}

class ViewShakeFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;

private:
	View::CameraShakeType m_shake; // +0x148
};

void ViewShakeFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const
{
	if (primary)
	{
		if (TheTacticalView)
		{
			TheTacticalView->shake(primary, m_shake);
		}
	}
}

#include "../../Include/GameClient/Display.h"

extern Display *TheDisplay;

class LightPulseFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *primary, const Matrix3D *primaryMtx, float primarySpeed, const Coord3D *secondary) const;

private:
	RGBColor m_color; // +0x148
	float m_radius; // +0x154
	float m_boundingCirclePct; // +0x158
	unsigned int m_increaseFrames; // +0x15C
	unsigned int m_decreaseFrames; // +0x160
};

void LightPulseFXNugget::doFXPos(const Coord3D *primary, const Matrix3D *, float, const Coord3D *) const
{
	if (primary)
	{
		TheDisplay->createLightPulse(primary, &m_color, 1.0f, m_radius, m_increaseFrames, m_decreaseFrames);
	}
}
