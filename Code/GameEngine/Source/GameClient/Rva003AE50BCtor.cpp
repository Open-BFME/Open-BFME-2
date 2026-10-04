// cl: /O1 /EHsc /arch:SSE2
// ??0Rva003AE50B@@QAE@PAX0@Z @0x005600F8 49B
// Ctor forwarding two void args to the pinned ParticleModule005F2CA0 base
// ctor (0x0055C86D), then storing vtable VA 0x00C1D440 plus data VAs
// 0x00C1BD10/0x00C1C780(s_slot3E4first)/0x00C1D430 at +0/+0x14/+0x18.
// Base size 0x14 proven by derived offsets; +0x18 stored twice like retail
// (first overwritten). Flags mirror Rva00560135Ctor.cpp. Caller 0x003ABACE.
extern const void *const g_00C1BD10[];
extern const void *const g_00C1D440[];
extern const void *const g_00C1D430[];
extern "C" int s_slot3E4first;

class ParticleModule005F2CA0
{
public:
	ParticleModule005F2CA0(void *a, void *b);

private:
	char m_base[0x14];
};

class __declspec(novtable) Rva003AE50B : public ParticleModule005F2CA0
{
public:
	Rva003AE50B(void *a, void *b);

private:
	void *m_14;
	void *volatile m_18;
};

Rva003AE50B::Rva003AE50B(void *a, void *b)
	: ParticleModule005F2CA0(a, b)
{
	m_18 = (void *)g_00C1BD10;
	*(const void **)this = g_00C1D440;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1D430;
}

// ??0Rva00560A1B@@QAE@PAX0@Z @0x00560A1B 49B twin of the ctor above over the
// same pinned base: vtable VA 0x00C1D47C plus data VAs 0x00C1BD30 and
// 0x00C1D46C at +0x18 (twice) with s_slot3E4first at +0x14. Same volatile
// +0x18 recipe and flags.
extern const void *const g_00C1BD30[];
extern const void *const g_00C1D47C[];
extern const void *const g_00C1D46C[];

class __declspec(novtable) Rva00560A1B : public ParticleModule005F2CA0
{
public:
	Rva00560A1B(void *a, void *b);

private:
	void *m_14;
	void *volatile m_18;
};

Rva00560A1B::Rva00560A1B(void *a, void *b)
	: ParticleModule005F2CA0(a, b)
{
	m_18 = (void *)g_00C1BD30;
	*(const void **)this = g_00C1D47C;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1D46C;
}

// ??0Rva003AE61F@@QAE@PAX0@Z @0x00561375 49B twin over the same pinned base:
// vtable VA 0x00C1D4B8 plus data VAs 0x00C1BD50/0x00C1C780(s_slot3E4first)/
// 0x00C1D4A8 at +0/+0x14/+0x18 (twice). Same volatile +0x18 recipe and flags.
// Evidence: push esi push [esp+0xc] mov esi ecx push [esp+0xc] call 0x0055C86D
// then stores at +0x18/+0/+0x14/+0x18; caller at 0x003ABB2E; naming stores
// vtable 0x0081D4B8 at [this] proving Rva003AE61F.
extern const void *const g_00C1BD50[];
extern const void *const g_00C1D4B8[];
extern const void *const g_00C1D4A8[];

class __declspec(novtable) Rva003AE61F : public ParticleModule005F2CA0
{
public:
	Rva003AE61F(void *a, void *b);

private:
	void *m_14;
	void *volatile m_18;
};

Rva003AE61F::Rva003AE61F(void *a, void *b)
	: ParticleModule005F2CA0(a, b)
{
	m_18 = (void *)g_00C1BD50;
	*(const void **)this = g_00C1D4B8;
	m_14 = (void *)&s_slot3E4first;
	m_18 = (void *)g_00C1D4A8;
}
