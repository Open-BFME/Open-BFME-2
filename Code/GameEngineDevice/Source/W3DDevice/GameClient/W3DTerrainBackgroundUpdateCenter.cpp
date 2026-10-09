// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [00112230,00112259),41B, RET4 and [0011234C,001125BE),626B, RET4.
// BFME 2 W3DTerrainBackground::updateCenter (WorldBuilder: same file, with
// "Too many cameras used for culling, increase MAX_CULLING_CAMERAS" and the
// camera.IsBound assert); the ZH updateCenter is the semantic guide.
// Target facts: up to three culling cameras each set a status (+0x00..+0x08,
// Cull_Box slot +0x208 against the bounds at +0x0C: culled 2, visible 1,
// unused 0); the global getter 0x00117C00 forces 1x; the first camera comes
// from the 41-byte group helper 0x00112230; the 2x distance is
// sqr(170s + 25 + 260s) with s = TheDisplay slot +0x40 / 1024 clamped to
// [0.5, 2.5]; the nearest corner distance goes to +0x64; TheGlobalData
// +0x4A enables 2x, +0xEA0 forces it. Group and helper names are
// address-derived views.

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	Vector3(const Vector3 &v) { X = v.X; Y = v.Y; Z = v.Z; }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	float X;
	float Y;
	float Z;
};

inline Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z);
}

class AABoxClass
{
public:
	Vector3 Center;
	Vector3 Extent;
};

#define BFME_PAD_VIRTUAL(n) virtual void pad##n();
#define BFME_PAD_VIRTUAL8(n) BFME_PAD_VIRTUAL(n##0) BFME_PAD_VIRTUAL(n##1) \
	BFME_PAD_VIRTUAL(n##2) BFME_PAD_VIRTUAL(n##3) BFME_PAD_VIRTUAL(n##4) \
	BFME_PAD_VIRTUAL(n##5) BFME_PAD_VIRTUAL(n##6) BFME_PAD_VIRTUAL(n##7)

class CameraClass
{
public:
	virtual void Delete_This();
	BFME_PAD_VIRTUAL8(0) BFME_PAD_VIRTUAL8(1) BFME_PAD_VIRTUAL8(2)
	BFME_PAD_VIRTUAL8(3) BFME_PAD_VIRTUAL8(4) BFME_PAD_VIRTUAL8(5)
	BFME_PAD_VIRTUAL8(6) BFME_PAD_VIRTUAL8(7) BFME_PAD_VIRTUAL8(8)
	BFME_PAD_VIRTUAL8(9) BFME_PAD_VIRTUAL8(a) BFME_PAD_VIRTUAL8(b)
	BFME_PAD_VIRTUAL8(c) BFME_PAD_VIRTUAL8(d) BFME_PAD_VIRTUAL8(e)
	BFME_PAD_VIRTUAL8(f)
	BFME_PAD_VIRTUAL(g0)
	virtual bool Cull_Box(const AABoxClass &box);

	void Add_Ref() { m_numRefs++; }
	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

private:
	int m_numRefs;
};

class RenderObjClass
{
public:
	Vector3 Get_Position(void) const;
};

template <class T> class RefCountPtr
{
public:
	RefCountPtr() : m_referent(0) {}
	RefCountPtr(const RefCountPtr<T> &rhs) : m_referent(rhs.m_referent)
	{
		if (m_referent)
			m_referent->Add_Ref();
	}
	~RefCountPtr()
	{
		if (m_referent)
			m_referent->Release_Ref();
	}
	T *peek() const { return m_referent; }
	T *operator->() const { return m_referent; }
	bool isNull() const { return m_referent == 0; }

private:
	T *m_referent;
};

class Rva00112230CameraGroup
{
public:
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	const RefCountPtr<CameraClass> &operator[](unsigned int i) const { return m_begin[i]; }
	RefCountPtr<CameraClass> rva00112230() const;

private:
	RefCountPtr<CameraClass> *m_begin;
	RefCountPtr<CameraClass> *m_end;
};

int Rva00117C00Get();

class Display
{
public:
	BFME_PAD_VIRTUAL8(0) BFME_PAD_VIRTUAL8(1)
	virtual unsigned int getWidth();
};

extern Display *TheDisplay;

class GlobalData
{
public:
	unsigned char m_pad00[0x4A];
	bool m_allowTexture2X;
	unsigned char m_pad4b[0xEA0 - 0x4B];
	int m_stretchTerrain;
};

extern GlobalData *TheWritableGlobalData;
#define TheGlobalData TheWritableGlobalData

struct BfmeResetTextureRef
{
	void clear();
};

extern "C" double __cdecl sqrt(double);

class W3DTerrainBackground
{
public:
	void updateCenter(const Rva00112230CameraGroup &cameraGroup);

private:
	enum { MAX_CULLING_CAMERAS = 3 };

	__forceinline bool isCulled()
	{
		for (int i = 0; i < MAX_CULLING_CAMERAS; i++) {
			if (m_cullStatus[i] == 1)
				return false;
		}
		return true;
	}

	__forceinline void clearTextures()
	{
		m_terrainTexture.clear();
		m_terrainTexture2.clear();
	}

	int m_cullStatus[MAX_CULLING_CAMERAS];
	AABoxClass m_bounds;
	unsigned char m_pad24[0x38 - 0x24];
	BfmeResetTextureRef m_terrainTexture;
	unsigned char m_pad39[0x40 - 0x39];
	BfmeResetTextureRef m_terrainTexture2;
	unsigned char m_pad41[0x44 - 0x41];
	int m_texMultiplier;
	unsigned char m_pad48[0x64 - 0x48];
	float m_cameraDistance;
};

RefCountPtr<CameraClass> Rva00112230CameraGroup::rva00112230() const
{
	if (empty())
		return RefCountPtr<CameraClass>();
	return m_begin[0];
}

void W3DTerrainBackground::updateCenter(const Rva00112230CameraGroup &cameraGroup)
{
	if (cameraGroup.size() > MAX_CULLING_CAMERAS)
		return;

	int i;
	for (i = 0; i < cameraGroup.size(); i++) {
		m_cullStatus[i] = cameraGroup[i]->Cull_Box(m_bounds) ? 2 : 1;
	}
	for (; i < MAX_CULLING_CAMERAS; i++) {
		m_cullStatus[i] = 0;
	}

	if (isCulled()) {
		clearTextures();
		m_texMultiplier = 1;
		return;
	}
	if (Rva00117C00Get() > 0) {
		m_texMultiplier = 1;
		return;
	}

	float minDistSqr = -1.0f;
	RefCountPtr<CameraClass> camera = cameraGroup.rva00112230();
	if (camera.isNull())
		return;

	Vector3 cameraPos = ((RenderObjClass *)camera.peek())->Get_Position();
	for (int x = -1; x < 2; x++) {
		for (int y = -1; y < 2; y++) {
			for (int z = -1; z < 2; z++) {
				Vector3 corner = m_bounds.Center;
				corner.X += m_bounds.Extent.X * x;
				corner.Y += m_bounds.Extent.Y * y;
				corner.Z += m_bounds.Extent.Z * z;
				float distSqr = (cameraPos - corner).Length2();
				if (distSqr < minDistSqr || minDistSqr < 0.0f)
					minDistSqr = distSqr;
			}
		}
	}

	float mipDistance = 260.0f;
	float mipSlop = 170.0f;
	if (TheDisplay) {
		float scale = TheDisplay->getWidth() / 1024.0f;
		if (scale < 0.5f)
			scale = 0.5f;
		else if (scale > 2.5f)
			scale = 2.5f;
		mipDistance = scale * 260.0f;
		mipSlop = scale * 170.0f;
	}
	float mip2xDistance = mipDistance + (mipSlop + 25.0f);
	float mip2xDistanceSqr = mip2xDistance * mip2xDistance;

	m_cameraDistance = (float)sqrt(minDistSqr);
	m_texMultiplier = 1;
	if (TheGlobalData->m_allowTexture2X
		&& (minDistSqr < mip2xDistanceSqr || TheGlobalData->m_stretchTerrain)) {
		m_texMultiplier = 2;
	} else {
		clearTextures();
	}
}
