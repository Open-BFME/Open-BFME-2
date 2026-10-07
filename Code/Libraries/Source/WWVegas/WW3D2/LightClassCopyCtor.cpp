// cl: /MD /EHsc
//
// LightClass's copy constructor (retail 0x00130C00, 307 bytes), assignment
// (0x00130D40), destructor
// (0x00130E80), Clone (0x00130EA0), object-space bounding sphere and box
// (0x00130F40 and 0x00130F70, vtable 0x00BD23C0 slots 67 and 68) and scalar
// deleting destructor (0x00130FB0), in a dedicated TU: light.cpp builds against Zero Hour's
// RenderObjClass (0x94 bytes, three vptrs), while BFME2's is 0xC4 bytes with
// two (+0x00, +0x08).
//
// These four were first rowed as CollectionClass's. The vtable they install
// and sit in, 0x00BD23C0, is LightClass's: its slots 26 and 27 are the matched
// LightClass::Notify_Added (0x00130F00) and Notify_Removed (0x00130F20), its
// other installer 0x00130AC0 is the LightClass(LightType) constructor (the
// type stored at +0xC4, intensity 1.0 at +0xD0), Clone allocates 0x120 bytes
// (RenderObjClass's 0xC4 plus Zero Hour's LightClass members), and the copy
// constructor copies exactly those members after RenderObjClass's default
// constructor, as Zero Hour's light.cpp writes it.

class RefCountClass
{
public:
	virtual ~RefCountClass();
	int NumRefs;
};

class PersistClass
{
public:
	virtual ~PersistClass();
};

class RenderObjClass : public RefCountClass, public PersistClass
{
public:
	RenderObjClass();
	virtual ~RenderObjClass();
	RenderObjClass &operator=(const RenderObjClass &);
	virtual RenderObjClass *Clone() const = 0;
	virtual void Set_Force_Visible(int onoff);
	unsigned char Pad[0xC4 - 12];
};

// upstream layout: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h
class Vector3
{
public:
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	Vector3 &operator=(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }

	float X, Y, Z;
};

// upstream layout: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	Vector3 Center;
	float Radius;
};

// upstream layout: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

// upstream layout: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/light.h
class LightClass : public RenderObjClass
{
public:
	enum LightType
	{
		POINT = 0,
		DIRECTIONAL,
		SPOT
	};

	LightClass(LightType type = POINT);
	LightClass(const LightClass &src);
	LightClass &operator=(const LightClass &that);
	virtual ~LightClass();
	virtual RenderObjClass *Clone() const;
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
	virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
	float Get_Attenuation_Range() const { return FarAttenEnd; }

	int Type;									// +0xC4
	unsigned int Flags;							// +0xC8
	bool CastShadows;							// +0xCC
	float Intensity;							// +0xD0
	Vector3 Ambient;
	Vector3 Diffuse;
	Vector3 Specular;
	float NearAttenStart;
	float NearAttenEnd;
	float FarAttenStart;
	float FarAttenEnd;
	float SpotAngle;
	float SpotAngleCos;
	float SpotExponent;
	Vector3 SpotDirection;						// ends at +0x120
};

// upstream: reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/wwmath.h
#define WWMATH_PI			3.141592654f
#define DEG_TO_RADF(x)	(((float)x)*WWMATH_PI/180.0f)

// Zero Hour's light.cpp constructor (retail 0x00130AC0, 311 bytes).
LightClass::LightClass(LightType type) :
	Type(type),
	Flags(0),
	CastShadows(false),
	Intensity(1.0f),
	Ambient(1,1,1),
	Diffuse(1,1,1),
	Specular(1,1,1),
	NearAttenStart(0.0f),
	NearAttenEnd(0.0f),
	FarAttenStart(50.0f),
	FarAttenEnd(100.0f),
	SpotAngle(DEG_TO_RADF(45.0f)),
	SpotAngleCos(0.707f),
	SpotExponent(1.0f),
	SpotDirection(0,0,1)
{
	if (type == DIRECTIONAL) {
		Set_Force_Visible(true);	// The light has no position so culling cant work.
	}
}

// Zero Hour's light.cpp copy constructor; RenderObjClass is default-
// constructed, not copied.
LightClass::LightClass(const LightClass &src) :
	Type(src.Type),
	Flags(src.Flags),
	CastShadows(src.CastShadows),
	Intensity(src.Intensity),
	Ambient(src.Ambient),
	Diffuse(src.Diffuse),
	Specular(src.Specular),
	NearAttenStart(src.NearAttenStart),
	NearAttenEnd(src.NearAttenEnd),
	FarAttenStart(src.FarAttenStart),
	FarAttenEnd(src.FarAttenEnd),
	SpotAngle(src.SpotAngle),
	SpotAngleCos(src.SpotAngleCos),
	SpotExponent(src.SpotExponent),
	SpotDirection(src.SpotDirection)
{
}

// Zero Hour's light.cpp assignment (retail 0x00130D40): the self-check
// guards the call to the matched RenderObjClass::operator= at 0x0013B5F0.
LightClass &LightClass::operator=(const LightClass &that)
{
	if (this != &that) {
		RenderObjClass::operator=(that);

		Type = that.Type;
		Flags = that.Flags;
		CastShadows = that.CastShadows;
		Intensity = that.Intensity;
		Ambient = that.Ambient;
		Diffuse = that.Diffuse;
		Specular = that.Specular;
		NearAttenStart = that.NearAttenStart;
		NearAttenEnd = that.NearAttenEnd;
		FarAttenStart = that.FarAttenStart;
		FarAttenEnd = that.FarAttenEnd;
		SpotAngle = that.SpotAngle;
		SpotAngleCos = that.SpotAngleCos;
		SpotExponent = that.SpotExponent;
		SpotDirection = that.SpotDirection;
	}
	return *this;
}

// Empty: the compiler reinstalls the vptrs and tail-jumps to the matched
// RenderObjClass destructor at 0x0013BE20.
LightClass::~LightClass()
{
}

RenderObjClass *LightClass::Clone() const
{
	return new LightClass(*this);
}

// Zero Hour's light.cpp: a light's bounds are its far attenuation range
// (FarAttenEnd, +0x104) around the origin.
void LightClass::Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const
{
	sphere.Center.Set(0, 0, 0);
	sphere.Radius = Get_Attenuation_Range();
}

void LightClass::Get_Obj_Space_Bounding_Box(AABoxClass &box) const
{
	float r = Get_Attenuation_Range();
	box.Center.Set(0, 0, 0);
	box.Extent.Set(r, r, r);
}

// Anchor: emits the ??_G scalar-deleting-destructor COMDAT.
void deleteLight(LightClass *p)
{
	delete p;
}
