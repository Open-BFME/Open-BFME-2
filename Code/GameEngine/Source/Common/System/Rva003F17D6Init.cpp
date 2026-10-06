// cl: /Oy- /DNDEBUG /MD /GX-
// ?rva003F17D6@Rva003F17D6@@QAEPAU1@PAX0@Z @0x003F17D6 141B
// ?rva003F1863@Rva003F1863@@QAEPAU1@PAX0@Z @0x003F1863 141B
// ?rva003F18F0@Rva003F18F0@@QAEPAU1@PAX0@Z @0x003F18F0 134B
// ?rva003F1976@Rva003F1976@@QAEPAU1@PAX0@Z @0x003F1976 141B
// Obfuscated 8-int inits siblings of Rva0056EF65 141B / Rva0056F10C 134B per
// Rva0056EDBAPick.cpp precedent: pick pair via rowed picks into p/q,
// store p at +0, constants at +4/+8/+0c, deref args into +0x10/+0x14, chain.
// Evidence: callers 0x003F1D56/0x003F1DAF/0x003F1E08/0x003F1E61; callees rowed.
void __cdecl Rva003F10D0Pick(int *out1, int *out2);
void __cdecl Rva003F10FCPick(int *out1, int *out2);
void __cdecl Rva003F1128Pick(int *out1, int *out2);
void __cdecl Rva003F1154Pick(int *out1, int *out2);
struct Rva003F17D6
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva003F17D6 *rva003F17D6(void *a1, void *a2);
};
Rva003F17D6 *Rva003F17D6::rva003F17D6(void *a1, void *a2)
{
	int p;
	int q;
	Rva003F10D0Pick(&p, &q);
	m_00 = p;
	m_04 = 0x10AC50C0;
	m_08 = 0x14804842;
	m_0c = 0x004241A4F;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x10AC50C0;
	m_04 = e;
	e *= b;
	e ^= 0x14804842;
	m_08 = e;
	e *= b;
	e ^= 0x004241A4F;
	m_0c = e;
	e *= b;
	m_10 ^= e;
	e = m_10;
	e *= b;
	m_14 ^= e;
	e = m_14;
	e *= b;
	m_18 ^= e;
	e = m_18;
	e *= b;
	m_1c ^= e;
	return this;
}
struct Rva003F1863
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva003F1863 *rva003F1863(void *a1, void *a2);
};
Rva003F1863 *Rva003F1863::rva003F1863(void *a1, void *a2)
{
	int p;
	int q;
	Rva003F10FCPick(&p, &q);
	m_00 = p;
	m_04 = 0x10AC50C0;
	m_08 = 0x14804842;
	m_0c = 0x14804843;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x10AC50C0;
	m_04 = e;
	e *= b;
	e ^= 0x14804842;
	m_08 = e;
	e *= b;
	e ^= 0x14804843;
	m_0c = e;
	e *= b;
	m_10 ^= e;
	e = m_10;
	e *= b;
	m_14 ^= e;
	e = m_14;
	e *= b;
	m_18 ^= e;
	e = m_18;
	e *= b;
	m_1c ^= e;
	return this;
}
struct Rva003F18F0
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva003F18F0 *rva003F18F0(void *a1, void *a2);
};
Rva003F18F0 *Rva003F18F0::rva003F18F0(void *a1, void *a2)
{
	int p;
	int q;
	Rva003F1128Pick(&p, &q);
	m_00 = p;
	m_04 = 0x10AC50C0;
	m_08 = 0x14804842;
	m_0c = 0x10AC50C0;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x10AC50C0;
	m_04 = e;
	e *= b;
	e ^= 0x14804842;
	m_08 = e;
	e *= b;
	e ^= 0x10AC50C0;
	m_0c = e;
	e *= b;
	m_10 ^= e;
	e = m_10;
	e *= b;
	m_14 ^= e;
	e = m_14;
	e *= b;
	m_18 ^= e;
	e = m_18;
	e *= b;
	m_1c ^= e;
	return this;
}
struct Rva003F1976
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva003F1976 *rva003F1976(void *a1, void *a2);
};
Rva003F1976 *Rva003F1976::rva003F1976(void *a1, void *a2)
{
	int p;
	int q;
	Rva003F1154Pick(&p, &q);
	m_00 = p;
	m_04 = 0x10AC50C0;
	m_08 = 0x14804842;
	m_0c = 0x1ACC;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x10AC50C0;
	m_04 = e;
	e *= b;
	e ^= 0x14804842;
	m_08 = e;
	e *= b;
	e ^= 0x1ACC;
	m_0c = e;
	e *= b;
	m_10 ^= e;
	e = m_10;
	e *= b;
	m_14 ^= e;
	e = m_14;
	e *= b;
	m_18 ^= e;
	e = m_18;
	e *= b;
	m_1c ^= e;
	return this;
}
