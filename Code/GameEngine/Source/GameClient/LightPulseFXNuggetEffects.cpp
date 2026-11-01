// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?doFXObj@LightPulseFXNugget@@UBEXPBVObject@@0@Z 117B @0x001E03B4: virtual slot 2
// (offset 0x8) of vtable 0x007DD790 installed by rowed ctor 0x001E0321.
// BFME1 donor reference/open-bfme-1/Code/GameEngine/Source/GameClient/LightPulseFXNuggetEffects.cpp
// (doFXObj with radius plus boundingCirclePct branch plus TheDisplay->createLightPulse).
// Member offsets from retail FieldParse table 0x00BDCBD8 (Color@0x148 Radius@0x154
// RadiusAsPercent@0x158 IncreaseTime@0x15C DecreaseTime@0x160) matching rowed ctor TU.
// Object position at +0x38 and bounding radius at +0xB8 from retail loads;
// Display createLightPulse at vtable slot 0xBC; TheDisplay global DIR32 masked by gate.

#include "../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../Libraries/Include/Lib/RGBColor.h"

class Matrix3D;

class Object
{
public:
	const Coord3D *getPosition() const { return &m_position; }
	float getBoundingCircleRadius() const { return m_boundingCircleRadius; }

private:
	unsigned char m_pad00[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad44[0xB8 - 0x44];
	float m_boundingCircleRadius; // +0xB8
};

#include "../../Include/GameClient/Display.h"

extern Display *TheDisplay;

class FXNugget
{
public:
	virtual ~FXNugget();
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	unsigned char m_pad04[0x148 - 4];
};

class LightPulseFXNugget : public FXNugget
{
public:
	virtual void doFXPos(const Coord3D *, const Matrix3D *, float, const Coord3D *) const;
	virtual void doFXObj(const Object *, const Object *) const;

private:
	RGBColor m_color; // +0x148
	float m_radius; // +0x154
	float m_boundingCirclePct; // +0x158
	unsigned int m_increaseFrames; // +0x15C
	unsigned int m_decreaseFrames; // +0x160
};

void LightPulseFXNugget::doFXObj(const Object *primary, const Object *) const
{
	if (primary)
	{
		float radius = m_radius;
		if (m_boundingCirclePct > 0.0f)
		{
			radius = primary->getBoundingCircleRadius() * m_boundingCirclePct;
		}

		TheDisplay->createLightPulse(primary->getPosition(), &m_color, 1.0f, radius, m_increaseFrames, m_decreaseFrames);
	}
}
