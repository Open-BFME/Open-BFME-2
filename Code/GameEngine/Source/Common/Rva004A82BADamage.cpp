// cl: /DNDEBUG /MD /GX-
// ?Rva004A82BAAttemptDamage@@YAXPAVObject@@@Z @0x004A82BA 59B
// Free function: build DamageInfo (0x7C) on stack via rowed Rva00263895Member ctor,
// set fields +8=0 +0x10=8 +0x1C=6 +0x20=float from g_00C53840, call Object::attemptDamage.
// Evidence: leaf lane; callees rowed 0x00263895 ctor and pinned 0x0029848E attemptDamage;
// callers in 0x004A86E7 region; DamageInfo 0x7C view per Rva00263895Init.cpp;
// and [m],0 zero idiom needs /O1; movss needs /arch:SSE.
extern float g_00C53840;

class DamageInfo;

class Object
{
public:
	void attemptDamage(DamageInfo *info);
};

class Rva00263895Member
{
public:
	Rva00263895Member();

	char m_00[8];
	int m_08;
	char m_0C[4];
	int m_10;
	char m_14[8];
	int m_1C;
	float m_20;
	char m_24[0x58];
};

void __cdecl Rva004A82BAAttemptDamage(Object *obj)
{
	Rva00263895Member info;
	info.m_08 = 0;
	info.m_10 = 8;
	info.m_1C = 6;
	info.m_20 = g_00C53840;
	obj->attemptDamage((DamageInfo *)&info);
}
