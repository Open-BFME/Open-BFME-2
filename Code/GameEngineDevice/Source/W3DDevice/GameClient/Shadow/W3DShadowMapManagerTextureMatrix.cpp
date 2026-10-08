// cl: /O1 /arch:SSE /G7 /MD
//
// The shadow-map manager at 0x00DE1FF8 (WorldBuilder's
// W3DShadowMapManager.cpp, 0x007EEC40 there): before the create-a-hero
// screen draws its map, the camera's projection is mapped into texture
// space and handed to the FX "Sas" source as shadow map 0. The class keeps
// the placeholder name W3DShadowManagerReAcquire.cpp gives the manager.

// WWMath's Vector4 / Matrix4 / Matrix3D, only as far as this body inlines
// them (fxshadernamespacesas.cpp's views).
class Vector3
{
public:
	__forceinline Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }

	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	__forceinline Vector4() {}
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }

	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D(const Vector3 &t)
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, t.X);
		Row[1].Set(0.0f, 1.0f, 0.0f, t.Y);
		Row[2].Set(0.0f, 0.0f, 1.0f, t.Z);
	}
	__forceinline void Scale(const Vector3 &scale)
	{
		Row[0][0] *= scale.X; Row[1][0] *= scale.X; Row[2][0] *= scale.X;
		Row[0][1] *= scale.Y; Row[1][1] *= scale.Y; Row[2][1] *= scale.Y;
		Row[0][2] *= scale.Z; Row[1][2] *= scale.Z; Row[2][2] *= scale.Z;
	}

	Vector4 Row[3];
};

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

// 0x00134A80 (camera.cpp): Get_D3D_Projection_Matrix times the view matrix.
class CameraClass
{
public:
	void rva00134A80(Matrix4 *set_tm);
};

class FXShaderParameterSourceNamespaceSAS
{
public:
	void SetShadowMapInfo(int shadowMapIndex, const Matrix4 &worldToShadow, RefCountPtr<TextureClass> shadowMap);
};
extern FXShaderParameterSourceNamespaceSAS *g_00DF36B4;

// TheGlobalData: the +0x62 flag turns the shadow map on.
class GlobalData
{
public:
	unsigned char m_pad00[0x62];
	bool m_62; // +0x62
};
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
	if (TheWritableGlobalData->m_62)
	{
		Rva0007671F projection;
		m_camera->rva00134A80(&projection);
		Matrix3D toTexture(Vector3(0.5f, 0.5f, 0.0f));
		toTexture.Scale(Vector3(0.5f, -0.5f, 1.0f));
		Rva0007671F worldToShadow;
		Matrix4::Multiply(toTexture, projection, &worldToShadow);
		g_00DF36B4->SetShadowMapInfo(0, worldToShadow, rva0007BB4B());
	}
}
