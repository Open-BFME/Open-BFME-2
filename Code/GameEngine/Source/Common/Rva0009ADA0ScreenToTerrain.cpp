// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?screenToTerrain@Rva0009D55BProduct@@UAEXPBHPAVVector3@@@Z retail 0x0009ADA0..0x0009AE98
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

	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 &operator=(const Vector3 &v)
	{
		X = v.X;
		Y = v.Y;
		Z = v.Z;
		return *this;
	}
	void Set(float x, float y, float z)
	{
		X = x;
		Y = y;
		Z = z;
	}

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
	float m_terrainHeight; // +0xE4
	char m_pad0E8[0x1D0 - 0xE8];
	float m_step1D0;  // +0x1D0
};

class View
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
	virtual bool v08(); // +0x20
};
extern View *TheTacticalView;

class Rva0009AD06Target
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02(int enable); // +0x08
	virtual void v03(int enable); // +0x0C
};

struct Rva0009AD06Holder
{
	Rva0009AD06Target * volatile m_ptr;
};

class Rva0009AC2FSub
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
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20(); // +0x50
	char m_pad04[0x44 - 0x04];
	float m_val44;      // +0x44
};

template <class T>
inline const T &rvaMinRef(const T &lhs, const T &rhs)
{
	return lhs < rhs ? lhs : rhs;
}

template <class T>
inline const T &rvaMaxRef(const T &lhs, const T &rhs)
{
	return lhs > rhs ? lhs : rhs;
}

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
	virtual void screenToTerrain(const int *screen, Vector3 *world);
	virtual void v15();
	virtual float rva0009AC2F();
	virtual void rva0009AD06(int enable);
	virtual void rva0009AD24(int enable);
	virtual void v19();
	virtual void v20();
	virtual void rva0009AFCE(int delta);
	virtual void rva0009B023(const Vector3 *pos);
	virtual void v23();
	virtual bool rva0009AF90();
	virtual void v25();
	virtual void rva0009AFA5(float val);
	virtual void v27();
	virtual void rva0009AC4E(Vector3 *out);
	virtual void rva0009AC77(Vector3 *out);
	virtual void v30();
	virtual void v31();
	virtual void v32();
	virtual void v33();
	virtual void v34();
	virtual void v35();
	virtual void v36();
	virtual void v37();
	virtual void v38();
	virtual void v39();
	virtual void rva0009AD4D(bool snap);
	virtual void rva0009AD78(bool snap);

private:
	char m_pad004[0xC0 - 0x04];
	RenderObjClass *m_cameraC0;     // +0xC0
	Rva0009AD06Holder m_holderC4;   // +0xC4
	char m_pad0C8[0xD4 - 0xC8];
	Rva0009AC2FSub *m_subD4;        // +0xD4
	char m_pad0D8[0xF8 - 0xD8];
	Vector3 m_posF8;                // +0xF8
	char m_pad104[0x110 - 0x104];
	Vector3 m_pos110;               // +0x110
	char m_pad11C[0x124 - 0x11C];
	float m_minX124;                // +0x124
	float m_minY128;                // +0x128
	float m_maxX12C;                // +0x12C
	float m_maxY130;                // +0x130
	float m_position134;            // +0x134
	float m_velocity138;            // +0x138
};

void Rva0009D55BProduct::screenToTerrain(const int *screen, Vector3 *world)
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

	float terrainHeight = reinterpret_cast<Rva0009ADA0Manager *>(TheLivingWorldManager)->m_terrainHeight;
	world->X = Vector3::Find_X_At_Z(terrainHeight, m_cameraC0->Get_Position(), end);
	world->Y = Vector3::Find_Y_At_Z(terrainHeight, m_cameraC0->Get_Position(), end);
	world->Z = 0.0f;
}

float Rva0009D55BProduct::rva0009AC2F()
{
	Rva0009AC2FSub *sub = m_subD4;
	if (sub)
	{
		sub->v20();
		return sub->m_val44;
	}
	return 0.0f;
}

void Rva0009D55BProduct::rva0009AC4E(Vector3 *out)
{
	out->Set(m_pos110.X, m_pos110.Y, m_pos110.Z);
}

void Rva0009D55BProduct::rva0009AC77(Vector3 *out)
{
	out->Set(m_posF8.X, m_posF8.Y, m_posF8.Z);
}

void Rva0009D55BProduct::rva0009AD06(int enable)
{
	if (m_holderC4.m_ptr && enable)
		m_holderC4.m_ptr->v02(enable);
}

void Rva0009D55BProduct::rva0009AD24(int enable)
{
	if (m_holderC4.m_ptr && enable)
		m_holderC4.m_ptr->v03(enable);
}

// Retail 0x0009AD4D (43B) and 0x0009AD78 (40B), vtable slots 40 and 41: set
// the +0x138 velocity to the negated 0x00DE5E08 or to the 0x00DE5E04 rate,
// replaced by a unit step when the flag is set.
// Owned here: retail .data starts both at 0 (VA 0x00DE5E08, 0x00DE5E04).
float g_00DE5E08 = 0;
float g_00DE5E04 = 0;

void Rva0009D55BProduct::rva0009AD4D(bool snap)
{
	m_velocity138 = -g_00DE5E08;
	if (snap)
		m_velocity138 = -1.0f;
}

void Rva0009D55BProduct::rva0009AD78(bool snap)
{
	m_velocity138 = g_00DE5E04;
	if (snap)
		m_velocity138 = 1.0f;
}

// Retail 0x0009AF90 (21B), vtable slot 24 just before 0x0009AFA5: whether
// the 0x00DE5E44 float has reached the position at +0x134.
// Owned here (also read by Rva0009B0B7Update.cpp); retail .data starts it at 0 (VA 0x00DE5E44).
float g_00DE5E44 = 0;

bool Rva0009D55BProduct::rva0009AF90()
{
	return g_00DE5E44 >= m_position134;
}

void Rva0009D55BProduct::rva0009AFA5(float val)
{
	m_position134 = (val < 0.0f) ? 0.0f : ((val > 1.0f) ? 1.0f : val);
}

void Rva0009D55BProduct::rva0009AFCE(int delta)
{
	if ((delta > 0 && m_position134 > 0.0f) || (delta < 0 && m_position134 < 1.0f))
		m_velocity138 -= (float)delta * reinterpret_cast<Rva0009ADA0Manager *>(TheLivingWorldManager)->m_step1D0;
}

void Rva0009D55BProduct::rva0009B023(const Vector3 *pos)
{
	m_posF8 = *pos;
	if (TheTacticalView->v08())
	{
		m_posF8.X = rvaMinRef(m_posF8.X, m_maxX12C);
		m_posF8.Y = rvaMinRef(m_posF8.Y, m_maxY130);
		m_posF8.X = rvaMaxRef(m_posF8.X, m_minX124);
		m_posF8.Y = rvaMaxRef(m_posF8.Y, m_minY128);
	}
}


