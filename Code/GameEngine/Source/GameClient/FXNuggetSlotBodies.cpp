// cl: /O1 /DNDEBUG /MD /arch:SSE
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
	virtual ~Object();
	const Coord3D *getPosition() const { return &m_position; }

private:
	unsigned char m_pad04[0x38 - 4];
	Coord3D m_position; // +0x38
};

class View
{
public:
	virtual void s000(); virtual void s001(); virtual void s002(); virtual void s003();
	virtual void s004(); virtual void s005(); virtual void s006(); virtual void s007();
	virtual void s008(); virtual void s009(); virtual void s010(); virtual void s011();
	virtual void s012(); virtual void s013(); virtual void s014(); virtual void s015();
	virtual void s016(); virtual void s017(); virtual void s018(); virtual void s019();
	virtual void s020(); virtual void s021(); virtual void s022(); virtual void s023();
	virtual void s024(); virtual void s025(); virtual void s026(); virtual void s027();
	virtual void s028(); virtual void s029(); virtual void s030(); virtual void s031();
	virtual void s032(); virtual void s033(); virtual void s034(); virtual void s035();
	virtual void s036(); virtual void s037(); virtual void s038(); virtual void s039();
	virtual void s040(); virtual void s041();
	virtual void Add_Camera_Shake(const Coord3D &position, float radius, float duration, float power); // +0xA8
	virtual void s043(); virtual void s044(); virtual void s045(); virtual void s046();
	virtual void s047(); virtual void s048(); virtual void s049(); virtual void s050();
	virtual void s051(); virtual void s052(); virtual void s053(); virtual void s054();
	virtual void s055(); virtual void s056(); virtual void s057(); virtual void s058();
	virtual void s059(); virtual void s060(); virtual void s061(); virtual void s062();
	virtual void s063(); virtual void s064(); virtual void s065(); virtual void s066();
	virtual void s067(); virtual void s068(); virtual void s069(); virtual void s070();
	virtual void s071(); virtual void s072(); virtual void s073(); virtual void s074();
	virtual void s075(); virtual void s076(); virtual void s077(); virtual void s078();
	virtual void s079(); virtual void s080(); virtual void s081(); virtual void s082();
	virtual void s083(); virtual void s084(); virtual void s085(); virtual void s086();
	virtual void s087(); virtual void s088(); virtual void s089(); virtual void s090();
	virtual void s091(); virtual void s092(); virtual void s093(); virtual void s094();
	virtual void s095(); virtual void s096(); virtual void s097(); virtual void s098();
	virtual void s099(); virtual void s100(); virtual void s101(); virtual void s102();
	virtual void s103(); virtual void s104(); virtual void s105(); virtual void s106();
	virtual void shake(const Coord3D *epicenter, int shakeType); // +0x1AC
};

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
	int m_shake; // +0x148
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

class Display
{
public:
	virtual void d00();
	virtual void d01();
	virtual void d02();
	virtual void d03();
	virtual void d04();
	virtual void d05();
	virtual void d06();
	virtual void d07();
	virtual void d08();
	virtual void d09();
	virtual void d10();
	virtual void d11();
	virtual void d12();
	virtual void d13();
	virtual void d14();
	virtual void d15();
	virtual void d16();
	virtual void d17();
	virtual void d18();
	virtual void d19();
	virtual void d20();
	virtual void d21();
	virtual void d22();
	virtual void d23();
	virtual void d24();
	virtual void d25();
	virtual void d26();
	virtual void d27();
	virtual void d28();
	virtual void d29();
	virtual void d30();
	virtual void d31();
	virtual void d32();
	virtual void d33();
	virtual void d34();
	virtual void d35();
	virtual void d36();
	virtual void d37();
	virtual void d38();
	virtual void d39();
	virtual void d40();
	virtual void d41();
	virtual void d42();
	virtual void d43();
	virtual void d44();
	virtual void d45();
	virtual void d46();
	virtual void createLightPulse(const Coord3D *pos, const RGBColor *color, float innerRadius, float attenuationWidth, unsigned int increaseFrames, unsigned int decreaseFrames); // +0xBC
};

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
