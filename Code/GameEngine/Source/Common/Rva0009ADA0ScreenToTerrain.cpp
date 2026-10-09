// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva0009ADA0@Rva0009D55BProduct@@UAEXPBHPAVVector3@@@Z retail 0x0009ADA0..0x0009AE98
// (248 bytes). Slot 14 (+0x38) of the view vtable 0x00BC89C8 whose slot 27
// is the rowed per-frame update 0x0009B0B7 (same class view). A screen to
// terrain projection in the shape of ZH W3DView::screenToTerrain: when the
// rowed terrain pick 0x002BF2B7 (Rva002BF4F3::rva002BF2B7) hits it returns;
// otherwise slot 13 yields a ray start and direction whose sum is the ray
// end and the ray from the +0xC0 render object's position (rowed
// RenderObjClass::Get_Position 0x0013B8A0) is intersected with the plane
// at TheLivingWorldManager's +0xE4 height (Vector3::Find_X_At_Z and
// Find_Y_At_Z inlined); the world z is cleared.

class Vector3
{
public:
	float X;
	float Y;
	float Z;

	static float Find_X_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.X + ((z - p1.Z) * ((p2.X - p1.X) / (p2.Z - p1.Z)));
	}
	static float Find_Y_At_Z(float z, const Vector3 &p1, const Vector3 &p2)
	{
		return p1.Y + ((z - p1.Z) * ((p2.Y - p1.Y) / (p2.Z - p1.Z)));
	}
};

class RenderObjClass
{
public:
	Vector3 Get_Position() const;
};

class Rva002BF4F3
{
public:
	bool rva002BF2B7(int screen, Vector3 *world);
};

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;

struct Rva0009ADA0Manager
{
	char m_pad000[0xE4];
	float m_heightE4; // +0xE4
};

class Rva0009D55BProduct
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13(const int *screen, Vector3 *start, Vector3 *dir);
	virtual void rva0009ADA0(const int *screen, Vector3 *world);

private:
	char m_pad004[0xC0 - 0x04];
	RenderObjClass *m_cameraC0; // +0xC0
};

void Rva0009D55BProduct::rva0009ADA0(const int *screen, Vector3 *world)
{
	if (reinterpret_cast<Rva002BF4F3 *>(this)->rva002BF2B7((int)screen, world))
		return;

	Vector3 start;
	Vector3 dir;
	v13(screen, &start, &dir);

	Vector3 end;
	end.X = dir.X + start.X;
	end.Y = dir.Y + start.Y;
	end.Z = dir.Z + start.Z;

	float z = reinterpret_cast<Rva0009ADA0Manager *>(TheLivingWorldManager)->m_heightE4;
	world->X = Vector3::Find_X_At_Z(z, m_cameraC0->Get_Position(), end);
	world->Y = Vector3::Find_Y_At_Z(z, m_cameraC0->Get_Position(), end);
	world->Z = 0.0f;
}
