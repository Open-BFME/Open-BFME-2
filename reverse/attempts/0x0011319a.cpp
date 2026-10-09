// ?getTriangleIntersection@W3DTerrainBackground@@QAEXPAVVector3@@HHHHABV2@11@Z
// partial score=0.85 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native [0011319A,00113399),511B, RET32. W3DTerrainBackground::
// getTriangleIntersection (WorldBuilder name, "Bad index" assert in
// W3DTerrainBackground.cpp). For every grid point of the (width+1) x
// (height+1) block at (x, y), clamped to the map extent (+0x08/+0x0C) and
// placed at (origin + cell) * 10 - border (+0x10) * 10, it casts a vertical
// segment spanning the triangle's z range (+/- 1) against the triangle
// through castTriangle (0x001130D1, thiscall on this) and stores the hit z
// into the X (mode 1) or Y (mode 2) of the grid record (stride 0x0C,
// row pitch +0x58 + 1); the mode is at +0xC8. WWMath CastResultStruct,
// LineSegClass and RayCollisionTestClass shapes follow the ZH headers.

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) { X = x; Y = y; Z = z; }
	void Set(float x, float y, float z) { X = x; Y = y; Z = z; }
	float X;
	float Y;
	float Z;
};

struct CastResultStruct
{
	CastResultStruct() { Reset(); }
	void Reset()
	{
		StartBad = false;
		Fraction = 1.0f;
		Normal.Set(0.0f, 0.0f, 0.0f);
		SurfaceType = 0;
		ComputeContactPoint = false;
		ContactPoint.Set(0.0f, 0.0f, 0.0f);
	}

	bool StartBad;
	float Fraction;
	Vector3 Normal;
	unsigned int SurfaceType;
	bool ComputeContactPoint;
	Vector3 ContactPoint;
};

class LineSegClass
{
public:
	LineSegClass(const Vector3 &p0, const Vector3 &p1);

private:
	unsigned char m_storage[0x34];
};

class RayCollisionTestClass
{
public:
	RayCollisionTestClass(const LineSegClass &ray, CastResultStruct *res,
		int collisionType, bool checkTranslucent, bool checkHidden);

	CastResultStruct *Result;

private:
	unsigned char m_storage[0x40];
};

class WorldHeightMap
{
public:
	unsigned char m_pad00[0x08];
	int m_width;
	int m_height;
	int m_borderSize;
};

inline float Min(float a, float b) { return a < b ? a : b; }
inline float Max(float a, float b) { return a > b ? a : b; }

class W3DTerrainBackground
{
public:
	bool castTriangle(RayCollisionTestClass &raytest,
		const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);
	void getTriangleIntersection(Vector3 *heights, int x, int y, int width, int height,
		const Vector3 &v0, const Vector3 &v1, const Vector3 &v2);

private:
	unsigned char m_pad00[0x50];
	int m_xOrigin;
	int m_yOrigin;
	int m_width;
	WorldHeightMap *m_map;
	unsigned char m_pad60[0xC8 - 0x60];
	int m_mode;
};

void W3DTerrainBackground::getTriangleIntersection(Vector3 *heights, int x, int y, int width, int height,
	const Vector3 &v0, const Vector3 &v1, const Vector3 &v2)
{
	int maxX = m_map->m_width - 1;
	int maxY = m_map->m_height - 1;
	float minZ = Min(v2.Z, Min(v0.Z, v1.Z));
	float maxZ = Max(v2.Z, Max(v0.Z, v1.Z));

	Vector3 start;
	Vector3 end;
	for (int i = 0; i <= width; i++) {
		for (int j = 0; j <= height; j++) {
			int cellX = x + i;
			if (cellX >= maxX)
				cellX = maxX;
			int cellY = y + j;
			if (cellY >= maxY)
				cellY = maxY;
			int idx = (m_width + 1) * cellY + cellX;

			CastResultStruct result;
			float border = m_map->m_borderSize * 10.0f;
			float xPos = (m_xOrigin + cellX) * 10.0f - border;
			float yPos = (m_yOrigin + cellY) * 10.0f - border;
			start.X = xPos;
			start.Y = yPos;
			start.Z = maxZ + 1.0f;
			end.X = xPos;
			end.Y = yPos;
			end.Z = minZ - 1.0f;
			LineSegClass ray(start, end);
			result.ComputeContactPoint = true;
			RayCollisionTestClass raytest(ray, &result, 2, false, false);
			if (castTriangle(raytest, v0, v1, v2)) {
				float z = raytest.Result->ContactPoint.Z;
				if (m_mode == 2)
					heights[idx].Y = z;
				else if (m_mode == 1)
					heights[idx].X = z;
			}
		}
	}
}
