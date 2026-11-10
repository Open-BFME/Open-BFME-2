// cl: /O1 /arch:SSE /G7 /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
//
// The shadow-map manager at 0x00DE1FF8 (WorldBuilder's
// W3DShadowMapManager.cpp, 0x007EEC40 there): before the create-a-hero
// screen draws its map, the camera's projection is mapped into texture
// space and handed to the FX "Sas" source as shadow map 0. The class keeps
// the placeholder name W3DShadowManagerReAcquire.cpp gives the manager.

// WWMath's Vector4 / Matrix4 / Matrix3D, only as far as this body inlines
// them (fxshadernamespacesas.cpp's views).
#include "matrix3d.h"
#include "../../../../../Libraries/Source/WWVegas/WW3D2/CameraClass.h"

// WWMath matrix3d.h's inline Set(position) and Scale(Vector3), kept as file-local bodies.
static __forceinline void matrixSetPosition(Matrix3D &m, const Vector3 &t)
{
	m[0].Set(1.0f, 0.0f, 0.0f, t.X);
	m[1].Set(0.0f, 1.0f, 0.0f, t.Y);
	m[2].Set(0.0f, 0.0f, 1.0f, t.Z);
}
static __forceinline void matrixScale(Matrix3D &m, const Vector3 &scale)
{
	m[0][0] *= scale.X; m[1][0] *= scale.X; m[2][0] *= scale.X;
	m[0][1] *= scale.Y; m[1][1] *= scale.Y; m[2][1] *= scale.Y;
	m[0][2] *= scale.Z; m[1][2] *= scale.Z; m[2][2] *= scale.Z;
}

class Matrix4
{
public:
	static void Multiply(const Matrix3D &a, const Matrix4 &b, Matrix4 *res);

protected:
	Vector4 Row[4];
};

// The 0x40-byte matrix (rowed ctor 0x0007671F).
class Rva0007671F : public Matrix4
{
public:
	Rva0007671F();
};

// The texture handle and its counted pointer (fxshadernamespacesas.cpp).
class TextureBaseClass
{
public:
	__forceinline void Add_Ref() { ++m_refCount; }
	void Release_Ref();

private:
	void *m_vtable;
	unsigned short m_refCount;
};

class TextureClass : public TextureBaseClass
{
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &that) : ptr(that.ptr)
	{
		if (ptr)
			ptr->Add_Ref();
	}
	~RefCountPtr()
	{
		if (ptr)
			ptr->Release_Ref();
	}
	T &operator*() const { return *ptr; }

	T *ptr;
};


class FXShaderParameterSourceNamespaceSAS
{
public:
	void SetShadowMapInfo(int shadowMapIndex, const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap);
};
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;

// TheGlobalData: the +0x62 flag turns the shadow map on.
#include "../../../../../GameEngine/Include/Common/GlobalData.h"
extern GlobalData *TheWritableGlobalData;

class Rva0007DA23ResourceManager
{
public:
	void rva0007C18E();
	RefCountPtr<TextureClass> rva0007BB4B();

private:
	CameraClass *m_camera; // +0x00
};

// Retail 0x0007C18E, 206 bytes.
void Rva0007DA23ResourceManager::rva0007C18E()
{
	if (TheWritableGlobalData->m_useShadowMapping)
	{
		Rva0007671F projection;
		m_camera->rva00134A80(&projection);
		Matrix3D toTexture;
		matrixSetPosition(toTexture, Vector3(0.5f, 0.5f, 0.0f));
		matrixScale(toTexture, Vector3(0.5f, -0.5f, 1.0f));
		Rva0007671F worldToShadow;
		Matrix4::Multiply(toTexture, projection, &worldToShadow);
		g_00DF36B4->SetShadowMapInfo(0, worldToShadow, rva0007BB4B());
	}
}
