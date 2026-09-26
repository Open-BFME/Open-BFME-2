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

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct RGBColor
{
	float red;
	float green;
	float blue;
};

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

class Display
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46();
	virtual void createLightPulse(const Coord3D *pos, const RGBColor *color, float innerRadius, float attenuationWidth, unsigned int increaseFrames, unsigned int decreaseFrames);
};

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
