// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?setLightPosition@W3DGameClientShadowShim@@QAEXHMMM@Z @0x0009A587 198B: LINK 61B plus vslot via pin plus rowed Inv_Sqrt 0x0004233A plus rowed rva0007D9CF 0x0007D9CF plus Vector3 at +0xC plus shadow global 0x00DE1FF8.
// Evidence: LINK BONUS 1 file 61B plus callers 0x0006E5EE 0x0009A706 plus prev getLightPosWorld 0x0009A497 same class Vector3 at +0xC plus BFME1 vector3 donor.
class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float v);
};

struct Vector3_9A587
{
	float X;
	float Y;
	float Z;
	Vector3_9A587 operator-() const { return Vector3_9A587(-X, -Y, -Z); }
	float Length2() const { return X * X + Y * Y + Z * Z; }
	Vector3_9A587(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3_9A587() {}
};

class Rva0007D9B5Host
{
public:
	void rva0007D9CF(const int *p);
};

extern class Rva0007DA23ResourceManager *Rva00DE1FF8Manager;

class W3DGameClientShadowShim
{
public:
	void setLightPosition(int lightIndex, float x, float y, float z);

private:
	unsigned char m_unk00[12];
	Vector3_9A587 m_lightPos[1];
};

void W3DGameClientShadowShim::setLightPosition(int lightIndex, float x, float y, float z)
{
	if (lightIndex != 0)
		return;
	m_lightPos[0].X = x;
	m_lightPos[0].Y = y;
	m_lightPos[0].Z = z;
	if ((*(void **)&Rva00DE1FF8Manager) == 0)
		return;
	Vector3_9A587 dir = -m_lightPos[0];
	float lenSq = dir.Length2();
	if (lenSq != 0.0f)
	{
		float inv = WWMath::Inv_Sqrt(lenSq);
		dir.X *= inv;
		dir.Y *= inv;
		dir.Z *= inv;
	}
	((Rva0007D9B5Host *)(*(void **)&Rva00DE1FF8Manager))->rva0007D9CF((const int *)&dir);
}
