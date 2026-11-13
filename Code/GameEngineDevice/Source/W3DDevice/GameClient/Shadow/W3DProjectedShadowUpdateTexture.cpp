// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/sweep /Ireference/shims/wwmath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// BFME1 cee35b7d8 donor: game/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DProjectedShadowUpdateTexture.cpp.
// Zero Hour W3DTextureShadow.cpp supplies the decal update purpose and UV arithmetic.
// BFME2 caller update() at 0x001094E2 calls 0x0010930F with the current light position.
// Target layout and calls independently show mask +0x34, texture +0x68, render object +0x70;
// box slot +0x110 and sphere slot +0x10C differ from the BFME1 donor view.
// The target copies the six-float box storage with the existing Region3D copy constructor
// at 0x0009AC04. Its storage view is retained without claiming donor center/extent field names.
// The scalar constants and local uvData initializer remain exactly the donor values.

class TextureBaseClass
{
public:
	void Release_Ref(void);
};

#include "Vector2.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/vector3.h
class Vector3
{
public:
	Vector3(void) {}
	Vector3(const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; }
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3 &operator = (const Vector3 &vec) { X = vec.X; Y = vec.Y; Z = vec.Z; return *this; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = X;
		float tmp_y = Y;

		X = c_angle * tmp_x - s_angle * tmp_y;
		Y = s_angle * tmp_x + c_angle * tmp_y;
	}

	friend Vector3 operator * (const Vector3 &a, float k);
	friend Vector3 operator / (const Vector3 &a, float k);

	float X;
	float Y;
	float Z;
};

inline Vector3 operator * (const Vector3 &a, float k)
{
	return Vector3((a.X * k), (a.Y * k), (a.Z * k));
}

inline Vector3 operator / (const Vector3 &a, float k)
{
	float ook = 1.0f / k;
	return Vector3((a.X * ook), (a.Y * ook), (a.Z * ook));
}

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/sphere.h
class SphereClass
{
public:
	SphereClass(void) {}

	Vector3 Center;
	float Radius;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/aabox.h
#include "../../../../../Libraries/Include/Lib/Region3D.h"

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/surfaceclass.h
class SurfaceClass
{
public:
	struct SurfaceDescription
	{
		unsigned int Format;
		unsigned int Width;
		unsigned int Height;
	};

	void Get_Description(SurfaceDescription &surface_desc);
};

// Retail 0x00176CB0 destroys the by-value surface 0x00132D70 returns.
class W3DRadarResetSurface : public SurfaceClass
{
public:
	~W3DRadarResetSurface(void);

private:
	void *m_surface;
};

class CursorTextureSlot
{
public:
	W3DRadarResetSurface Get_Surface_Level(void);

	TextureBaseClass *m_texture;
};

// The AssetReference returned at 0x001085B4 is the one-pointer texture
// holder passed to CursorTextureSlot::Get_Surface_Level at 0x00132D70.
class AssetReference : public CursorTextureSlot
{
public:
	~AssetReference(void)
	{
		if (m_texture)
			m_texture->Release_Ref();
	}
};

// Retail 0x001085B4 reads the AssetReference at shadow-texture +0x30.
#include "../../../../Include/W3DDevice/GameClient/Rva001085B4.h"

// Offsets witnessed by this body and the landed destructor at 0x007AF4E0;
// the order matches the Zero Hour W3DShadowTexture.
class W3DShadowTexture
{
public:
	void setLightPosHistory(Vector3 &pos) { m_lastLightPosition = pos; }
	void setBoundingSphere(SphereClass &sphere) { m_areaEffectSphere = sphere; }
	void setBoundingBox(Region3D &box) { m_areaEffectBox.Region3D::Region3D(box); }
	// Reuse the rowed 0x00108603 provider; its field-copy body cannot throw.
	void setDecalUVAxis(Vector3 &u, Vector3 &vec) throw();

private:
	char m_unmodelled00[0x34];
	Vector3 m_lastLightPosition;		// +0x34
	char m_unmodelled40[0x24];
	Region3D m_areaEffectBox;			// +0x64
	SphereClass m_areaEffectSphere;		// +0x7C
	Vector3 m_shadowUV[2];				// +0x8C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/rendobj.h
class RenderObjClass
{
public:
	virtual void v00(void);
	virtual void v01(void);
	virtual void v02(void);
	virtual void v03(void);
	virtual void v04(void);
	virtual void v05(void);
	virtual void v06(void);
	virtual void v07(void);
	virtual void v08(void);
	virtual void v09(void);
	virtual void v10(void);
	virtual void v11(void);
	virtual void v12(void);
	virtual void v13(void);
	virtual void v14(void);
	virtual void v15(void);
	virtual void v16(void);
	virtual void v17(void);
	virtual void v18(void);
	virtual void v19(void);
	virtual void v20(void);
	virtual void v21(void);
	virtual void v22(void);
	virtual void v23(void);
	virtual void v24(void);
	virtual void v25(void);
	virtual void v26(void);
	virtual void v27(void);
	virtual void v28(void);
	virtual void v29(void);
	virtual void v30(void);
	virtual void v31(void);
	virtual void v32(void);
	virtual void v33(void);
	virtual void v34(void);
	virtual void v35(void);
	virtual void v36(void);
	virtual void v37(void);
	virtual void v38(void);
	virtual void v39(void);
	virtual void v40(void);
	virtual void v41(void);
	virtual void v42(void);
	virtual void v43(void);
	virtual void v44(void);
	virtual void v45(void);
	virtual void v46(void);
	virtual void v47(void);
	virtual void v48(void);
	virtual void v49(void);
	virtual void v50(void);
	virtual void v51(void);
	virtual void v52(void);
	virtual void v53(void);
	virtual void v54(void);
	virtual void v55(void);
	virtual void v56(void);
	virtual void v57(void);
	virtual void v58(void);
	virtual void v59(void);
	virtual void v60(void);
	virtual void v61(void);
	virtual void v62(void);
	virtual void v63(void);
	virtual void v64(void);
	virtual void v65(void);
	virtual void v66(void);
	virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const; // +0x10C
	virtual void Get_Obj_Space_Bounding_Box(Region3D &box) const; // +0x110

	Vector3 Get_Position(void) const;
};

#define DECAL_TEXELS_PER_WORLD_UNIT	(64.0f/20.0f)	//64 texels per 2 terrain cells (20 units)

class W3DProjectedShadow
{
public:
	void updateTexture(Vector3 &lightPos);

private:
	char m_unmodelled00[0x34];
	unsigned int m_unmodelled34;			// +0x34 decal-kind mask test 0x2C61
	char m_unmodelled38[0x30];
	W3DShadowTexture *m_shadowTexture[1];	// +0x68
	void *m_unmodelled6C;
	RenderObjClass *m_robj;					// +0x70
};

void W3DProjectedShadow::updateTexture(Vector3 &lightPos)
{
	//default uv coordinates before rotation starting at top/left going clockwise
	static Vector2 uvData[4]={Vector2(-0.5,-0.5f),Vector2(-0.5,0.5f),Vector2(0.5f,0.5f),Vector2(-0.5f,0.5f)};

	if (m_unmodelled34 & 0x2C61)
	{	//decal shadows use artist supplied textures.  We just need to tweak the uv coordinates to match
		//the light direction.
		Vector3 objPos=m_robj->Get_Position();
		Vector3 objectToLight;
		objectToLight.Set(1.0f,0.0f,0.0f);

		SurfaceClass::SurfaceDescription surface_desc;
		((Rva001085B4 *)m_shadowTexture[0])->rva001085B4().Get_Surface_Level().Get_Description(surface_desc);
		//default shadow texture points along world -x axis (west).  Rotate uv coordinates to fit actual light direction
		Vector3 uVec = objectToLight * DECAL_TEXELS_PER_WORLD_UNIT / (float)surface_desc.Width;
		objectToLight.Rotate_Z(-1.0f,0.0f);	//rotate u vector by -90 degress to get v vector.
		Vector3 vVec = objectToLight * DECAL_TEXELS_PER_WORLD_UNIT / (float)surface_desc.Height;

		m_shadowTexture[0]->setDecalUVAxis(uVec, vVec);

		Region3D	box;
		SphereClass	sphere;
		m_robj->Get_Obj_Space_Bounding_Box(box);	//shadow uses same bounding box as object
		m_robj->Get_Obj_Space_Bounding_Sphere(sphere);

		m_shadowTexture[0]->setBoundingSphere(sphere);
		m_shadowTexture[0]->setBoundingBox(box);
	}

	m_shadowTexture[0]->setLightPosHistory(lightPos);	//store position of light at time of texture update.
}
