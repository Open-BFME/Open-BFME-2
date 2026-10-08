// ?getBridgeInfo@W3DBridge@@QAEXPAVRva0027C36A@@@Z
// partial score=0.36 date=2026-10-09
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// W3DBridge::getBridgeInfo, Zero Hour's body. BFME 2's BridgeInfo (the
// ledger's Rva0027C36A) also carries the deck quad at +0x6C (fromLeft,
// fromRight, toRight, toLeft) and its two triangles' corner indices at +0x9C.

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float val);
};

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	__forceinline float Length2() const { return X * X + Y * Y + Z * Z; }
	__forceinline void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f) {
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
			Z *= oolen;
		}
	}
	friend Vector3 operator+(const Vector3 &a, const Vector3 &b) { return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z); }
	friend Vector3 operator*(const Vector3 &a, float k) { return Vector3(a.X * k, a.Y * k, a.Z * k); }
	friend Vector3 operator-(const Vector3 &a, const Vector3 &b) { return Vector3(a.X - b.X, a.Y - b.Y, a.Z - b.Z); }
	float X;
	float Y;
	float Z;
};

struct Coord3D
{
	float x;
	float y;
	float z;
};

struct BridgeTriangle
{
	unsigned short corner[3];
};

// Zero Hour's BridgeInfo.
class Rva0027C36A
{
public:
	Coord3D from; // +0x00
	Coord3D to; // +0x0C
	float bridgeWidth; // +0x18
	Coord3D fromLeft; // +0x1C
	Coord3D fromRight; // +0x28
	Coord3D toLeft; // +0x34
	Coord3D toRight; // +0x40
	int bridgeIndex; // +0x4C
	char m_pad50[0x6C - 0x50];
	Coord3D deck[4]; // +0x6C
	BridgeTriangle triangle[2]; // +0x9C
};

class W3DBridge
{
public:
	void getBridgeInfo(Rva0027C36A *pInfo);
private:
	Vector3 m_start; // +0x00
	Vector3 m_end; // +0x0C
	float m_scale; // +0x18
	char m_pad1C[0x6C - 0x1C];
	float m_minY; // +0x6C
	float m_maxY; // +0x70
};

// ?getBridgeInfo@W3DBridge@@QAEXPAVRva0027C36A@@@Z @0x000DDB94
void W3DBridge::getBridgeInfo(Rva0027C36A *pInfo)
{
	*(Vector3 *)&pInfo->from = m_start;
	*(Vector3 *)&pInfo->to = m_end;
	pInfo->bridgeWidth = (m_maxY - m_minY) * m_scale;

	Vector3 vec = m_end - m_start;
	Vector3 vecNormal(-vec.Y, vec.X, 0);
	vecNormal.Normalize();

	pInfo->fromLeft.x = m_maxY * m_scale * vecNormal.X + m_start.X;
	pInfo->fromLeft.y = m_maxY * m_scale * vecNormal.Y + m_start.Y;
	pInfo->fromLeft.z = m_maxY * m_scale * vecNormal.Z + m_start.Z;

	pInfo->fromRight.x = m_scale * vecNormal.X * m_minY + m_start.X;
	pInfo->fromRight.y = m_scale * vecNormal.Y * m_minY + m_start.Y;
	pInfo->fromRight.z = m_scale * vecNormal.Z * m_minY + m_start.Z;

	pInfo->toLeft.x = m_maxY * m_scale * vecNormal.X + m_end.X;
	pInfo->toLeft.y = m_maxY * m_scale * vecNormal.Y + m_end.Y;
	pInfo->toLeft.z = m_maxY * m_scale * vecNormal.Z + m_end.Z;

	pInfo->toRight.x = m_scale * vecNormal.X * m_minY + m_end.X;
	pInfo->toRight.y = m_scale * vecNormal.Y * m_minY + m_end.Y;
	pInfo->toRight.z = m_scale * vecNormal.Z * m_minY + m_end.Z;

	pInfo->deck[0].x = pInfo->fromLeft.x;
	pInfo->deck[0].y = pInfo->fromLeft.y;
	pInfo->deck[0].z = pInfo->fromLeft.z;
	pInfo->deck[1].x = pInfo->fromRight.x;
	pInfo->deck[1].y = pInfo->fromRight.y;
	pInfo->deck[1].z = pInfo->fromRight.z;
	pInfo->deck[2].x = pInfo->toRight.x;
	pInfo->deck[2].y = pInfo->toRight.y;
	pInfo->deck[2].z = pInfo->toRight.z;
	pInfo->deck[3].x = pInfo->toLeft.x;
	pInfo->deck[3].y = pInfo->toLeft.y;
	pInfo->deck[3].z = pInfo->toLeft.z;
	pInfo->triangle[0].corner[0] = 0;
	pInfo->triangle[0].corner[1] = 1;
	pInfo->triangle[0].corner[2] = 2;
	pInfo->triangle[1].corner[0] = 0;
	pInfo->triangle[1].corner[1] = 2;
	pInfo->triangle[1].corner[2] = 3;
}
