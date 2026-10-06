// cl: /DNDEBUG /MD
// ?Rva0056EDBAPick@@YAXPAH0@Z @0x0056EDBA 46B
// Random pair pick via rdtsc low bits into two parallel int[4] tables.
// Inline asm for rdtsc: MSVC 7.1 has no __rdtsc intrinsic, so __asm is the
// only way to emit 0F 31; the surrounding movs are plain C assignments.
// Unlocks 0x0056F32B 0x0056F2A5.
// Evidence: and [ebp-4]0 rdtsc mov [ebp-4]eax and-3 shl-2 two indexed loads.
// g_Va00DD2A5C: matched references place it at VA 0xdd2a5c (retail .data contents).
int g_Va00DD2A5C[4] = {
	0x17c6e74f, 0x6e41c34f, 0x1a84b34f, -1103415473
};
// g_Va00DD2A6C: matched references place it at VA 0xdd2a6c (retail .data contents).
int g_Va00DD2A6C[4] = {
	0x5bc6af4b, 0x6a41934b, 0x5204e34b, -1430552757
};
void __cdecl Rva0056EDBAPick(int *out1, int *out2);
void __cdecl Rva0056EDBAPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		rdtsc
		mov t, eax
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD2A6C[i];
	*out2 = g_Va00DD2A5C[i];
}
// g_Va00DD29BC: matched references place it at VA 0xdd29bc (retail .data contents).
int g_Va00DD29BC[4] = {
	-273905649, 0x9e6cf, -1157274225, 0x42b61c4f
};
// g_Va00DD29CC: matched references place it at VA 0xdd29cc (retail .data contents).
int g_Va00DD29CC[4] = {
	-1291022325, 0x48deecb, -1482610805, 0x4e9a144b
};
void __cdecl Rva0056ECDAPick(int *out1, int *out2);
void __cdecl Rva0056ECDAPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD29CC[i];
	*out2 = g_Va00DD29BC[i];
}
// ?rva0056EF65@Rva0056EF65@@QAEPAU1@PAX0@Z @0x0056EF65 141B chain from 0x0056ECDA
struct Rva0056EF65
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056EF65 *rva0056EF65(void *a1, void *a2);
};
Rva0056EF65 *Rva0056EF65::rva0056EF65(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ECDAPick(&p, &q);
	m_00 = p;
	m_04 = 0x18245AC1;
	m_08 = 0x18245AC5;
	m_0c = 0x0C24180A;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x18245AC1;
	m_04 = e;
	e *= b;
	e ^= 0x18245AC5;
	m_08 = e;
	e *= b;
	e ^= 0x0C24180A;
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
// ?Rva0056ED34Pick@@YAXPAH0@Z @0x0056ED34 44B gap between 0x0056ECDA and 0x0056EDBA
// g_Va00DD29FC: matched references place it at VA 0xdd29fc (retail .data contents).
int g_Va00DD29FC[4] = {
	0x5539048a, -660880950, -1441106294, -1412547510
};
// g_Va00DD2A0C: matched references place it at VA 0xdd2a0c (retail .data contents).
int g_Va00DD2A0C[4] = {
	0x119148b, -996441141, -1575606645, -203264949
};
void __cdecl Rva0056ED34Pick(int *out1, int *out2);
void __cdecl Rva0056ED34Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD2A0C[i];
	*out2 = g_Va00DD29FC[i];
}
// ?Rva0056ED60Pick@@YAXPAH0@Z @0x0056ED60 44B gap between 0x0056ED34 and 0x0056EDBA
// g_Va00DD2A1C: matched references place it at VA 0xdd2a1c (retail .data contents).
int g_Va00DD2A1C[4] = {
	-1869448881, -384734897, -1223762673, 0x1d80d14f
};
// g_Va00DD2A2C: matched references place it at VA 0xdd2a2c (retail .data contents).
int g_Va00DD2A2C[4] = {
	-860474549, -451861685, -1548820725, 0x5d049b4b
};
void __cdecl Rva0056ED60Pick(int *out1, int *out2);
void __cdecl Rva0056ED60Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD2A2C[i];
	*out2 = g_Va00DD2A1C[i];
}
// ?Rva0056ED8CPick@@YAXPAH0@Z @0x0056ED8C 46B gap rdtsc pick
// g_Va00DD2A3C: matched references place it at VA 0xdd2a3c (retail .data contents).
int g_Va00DD2A3C[4] = {
	-277978033, -1869448881, -384734897, -1223762673
};
// g_Va00DD2A4C: matched references place it at VA 0xdd2a4c (retail .data contents).
int g_Va00DD2A4C[4] = {
	-203264949, -860474549, -451861685, -1548820725
};
void __cdecl Rva0056ED8CPick(int *out1, int *out2);
void __cdecl Rva0056ED8CPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		rdtsc
		mov t, eax
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD2A4C[i];
	*out2 = g_Va00DD2A3C[i];
}
// ?Rva0056EDE8Pick@@YAXPAH0@Z @0x0056EDE8 46B gap rdtsc pick
// g_Va00DD2A7C: matched references place it at VA 0xdd2a7c (retail .data contents).
int g_Va00DD2A7C[4] = {
	0x34cbf74f, -273905649, 0x9e6cf, -1157274225
};
// g_Va00DD2A8C: matched references place it at VA 0xdd2a8c (retail .data contents).
int g_Va00DD2A8C[4] = {
	0x2443b54b, -1291022325, 0x48deecb, -1482610805
};
void __cdecl Rva0056EDE8Pick(int *out1, int *out2);
void __cdecl Rva0056EDE8Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		rdtsc
		mov t, eax
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD2A8C[i];
	*out2 = g_Va00DD2A7C[i];
}
// ?rva0056F2A5@Rva0056F2A5@@QAEPAU1@PAX0@Z @0x0056F2A5 134B
// Chain from 0x0056EDBA via Rva0056EDBAPick sibling of Rva0056EF65.
// Evidence: same 8-int obfuscated init shape as 0x0056EF65 with two constants 0x0C840885 0x0C840881.
struct Rva0056F2A5
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F2A5 *rva0056F2A5(void *a1, void *a2);
};
Rva0056F2A5 *Rva0056F2A5::rva0056F2A5(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056EDBAPick(&p, &q);
	m_00 = p;
	m_04 = 0x0C840885;
	m_08 = 0x0C840881;
	m_0c = 0x0C840885;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x0C840885;
	m_04 = e;
	e *= b;
	e ^= 0x0C840881;
	m_08 = e;
	e *= b;
	e ^= 0x0C840885;
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
// ?rva0056F21F@Rva0056F21F@@QAEPAU1@PAX0@Z @0x0056F21F 134B
// Chain from 0x0056ED8C via Rva0056ED8CPick sibling of 0x0056F2A5.
// Evidence: same 8-int obfuscated init shape with two constants 0x18245AC1 0x18245AC5.
struct Rva0056F21F
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F21F *rva0056F21F(void *a1, void *a2);
};
Rva0056F21F *Rva0056F21F::rva0056F21F(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ED8CPick(&p, &q);
	m_00 = p;
	m_04 = 0x18245AC1;
	m_08 = 0x18245AC5;
	m_0c = 0x18245AC1;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x18245AC1;
	m_04 = e;
	e *= b;
	e ^= 0x18245AC5;
	m_08 = e;
	e *= b;
	e ^= 0x18245AC1;
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
// ?rva0056F10C@Rva0056F10C@@QAEPAU1@PAX0@Z @0x0056F10C 134B
// Chain from 0x0056ED34 via Rva0056ED34Pick sibling of 0x0056F21F.
// Evidence: same 8-int obfuscated init shape with two constants 0x0C841840 0x14AC1A82.
struct Rva0056F10C
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F10C *rva0056F10C(void *a1, void *a2);
};
Rva0056F10C *Rva0056F10C::rva0056F10C(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ED34Pick(&p, &q);
	m_00 = p;
	m_04 = 0x0C841840;
	m_08 = 0x14AC1A82;
	m_0c = 0x0C841840;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x0C841840;
	m_04 = e;
	e *= b;
	e ^= 0x14AC1A82;
	m_08 = e;
	e *= b;
	e ^= 0x0C841840;
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
// ?rva0056F32B@Rva0056F32B@@QAEPAU1@PAX0@Z @0x0056F32B 134B
// Chain from 0x0056EDBA via Rva0056EDBAPick sibling of 0x0056F10C.
// Evidence: same 8-int obfuscated init shape with two constants 0x0C840885 0x100C1887.
struct Rva0056F32B
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F32B *rva0056F32B(void *a1, void *a2);
};
Rva0056F32B *Rva0056F32B::rva0056F32B(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056EDBAPick(&p, &q);
	m_00 = p;
	m_04 = 0x0C840885;
	m_08 = 0x100C1887;
	m_0c = 0x0C840885;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x0C840885;
	m_04 = e;
	e *= b;
	e ^= 0x100C1887;
	m_08 = e;
	e *= b;
	e ^= 0x0C840885;
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
// ?rva0056F192@Rva0056F192@@QAEPAU1@PAX0@Z @0x0056F192 141B
// Chain from 0x0056ED60 via Rva0056ED60Pick sibling of 0x0056EF65.
// Evidence: same 8-int obfuscated init shape with three constants 0x18245AC1 0x18245AC5 0x488C00C6.
struct Rva0056F192
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F192 *rva0056F192(void *a1, void *a2);
};
Rva0056F192 *Rva0056F192::rva0056F192(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ED60Pick(&p, &q);
	m_00 = p;
	m_04 = 0x18245AC1;
	m_08 = 0x18245AC5;
	m_0c = 0x488C00C6;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x18245AC1;
	m_04 = e;
	e *= b;
	e ^= 0x18245AC5;
	m_08 = e;
	e *= b;
	e ^= 0x488C00C6;
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
// ?rva0056F3B1@Rva0056F3B1@@QAEPAU1@PAX0@Z @0x0056F3B1 141B
// Chain from 0x0056EDE8 via Rva0056EDE8Pick sibling of 0x0056F192.
// Evidence: same 8-int obfuscated init shape with three constants 0x18245AC1 0x18245AC5 0x5C80520D.
struct Rva0056F3B1
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F3B1 *rva0056F3B1(void *a1, void *a2);
};
Rva0056F3B1 *Rva0056F3B1::rva0056F3B1(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056EDE8Pick(&p, &q);
	m_00 = p;
	m_04 = 0x18245AC1;
	m_08 = 0x18245AC5;
	m_0c = 0x5C80520D;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0x18245AC1;
	m_04 = e;
	e *= b;
	e ^= 0x18245AC5;
	m_08 = e;
	e *= b;
	e ^= 0x5C80520D;
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

// Three more pickers of the two shapes above (the 44-byte esp-entropy form and
// the 46-byte rdtsc form), each over its own pair of int[4] tables in retail
// .data, which no other unit references. Only the table operands differ from
// the rowed copies.

// ?Rva0056ECAEPick@@YAXPAH0@Z @0x0056ECAE 44B esp pick
// g_Va00DD299C: retail .data contents at VA 0xdd299c.
int g_Va00DD299C[4] = {
	-1154705398, 0xcadbeca, -349344374, 0x6b6044a
};
// g_Va00DD29AC: retail .data contents at VA 0xdd29ac.
int g_Va00DD29AC[4] = {
	-1291022325, 0x48deecb, -1482610805, 0x4e9a144b
};
void __cdecl Rva0056ECAEPick(int *out1, int *out2);
void __cdecl Rva0056ECAEPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD29AC[i];
	*out2 = g_Va00DD299C[i];
}

// ?Rva0056ED06Pick@@YAXPAH0@Z @0x0056ED06 46B rdtsc pick
// g_Va00DD29DC: retail .data contents at VA 0xdd29dc.
int g_Va00DD29DC[4] = {
	-1562119857, -888972913, 0x69f619cf, 0x1f9d5c4f
};
// g_Va00DD29EC: retail .data contents at VA 0xdd29ec.
int g_Va00DD29EC[4] = {
	-1569742517, -1758525045, 0x61d649cb, 0x47b1144b
};
void __cdecl Rva0056ED06Pick(int *out1, int *out2);
void __cdecl Rva0056ED06Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		rdtsc
		mov t, eax
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DD29EC[i];
	*out2 = g_Va00DD29DC[i];
}

// ?Rva00229A44Pick@@YAXPAH0@Z @0x00229A44 44B esp pick
// g_Va00DBA31C: retail .data contents at VA 0xdba31c.
int g_Va00DBA31C[4] = {
	-639134262, 0x7ae8328a, -1994976438, 0x947890a
};
// g_Va00DBA32C: retail .data contents at VA 0xdba32c.
int g_Va00DBA32C[4] = {
	-917512821, 0x326072cb, -1992357109, 0x167914b
};
void __cdecl Rva00229A44Pick(int *out1, int *out2);
void __cdecl Rva00229A44Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DBA32C[i];
	*out2 = g_Va00DBA31C[i];
}

// Three more pickers beside 0x00229A44, each over its own pair of int[4] tables
// in retail .data that no other unit references: 0x00229A18 and 0x00229A70 take
// the ebp form (as in Rva003F10D0Pick.cpp), 0x00229A9C the esp form; only the
// table operands differ from the rowed picker of each form.

// ?Rva00229A18Pick@@YAXPAH0@Z @0x00229A18 44B ebp pick
// g_Va00DBA2FC: retail .data contents at VA 0xdba2fc.
int g_Va00DBA2FC[4] = {
	-880315382, -804461238, 0x3e79a00a, -1154241462
};
// g_Va00DBA30C: retail .data contents at VA 0xdba30c.
int g_Va00DBA30C[4] = {
	-888970165, -660034293, 0x32fde04b, -341853173
};
void __cdecl Rva00229A18Pick(int *out1, int *out2);
void __cdecl Rva00229A18Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, ebp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DBA30C[i];
	*out2 = g_Va00DBA2FC[i];
}

// ?Rva00229A70Pick@@YAXPAH0@Z @0x00229A70 44B ebp pick
// g_Va00DBA33C: retail .data contents at VA 0xdba33c.
int g_Va00DBA33C[4] = {
	0x7ae8328a, -1994976438, 0x947890a, 0x1db904ca
};
// g_Va00DBA34C: retail .data contents at VA 0xdba34c.
int g_Va00DBA34C[4] = {
	0x326072cb, -1992357109, 0x167914b, 0x119148b
};
void __cdecl Rva00229A70Pick(int *out1, int *out2);
void __cdecl Rva00229A70Pick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, ebp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DBA34C[i];
	*out2 = g_Va00DBA33C[i];
}

// ?Rva00229A9CPick@@YAXPAH0@Z @0x00229A9C 44B esp pick
// g_Va00DBA35C: retail .data contents at VA 0xdba35c.
int g_Va00DBA35C[4] = {
	-1048022134, -880315382, -804461238, 0x3e79a00a
};
// g_Va00DBA36C: retail .data contents at VA 0xdba36c.
int g_Va00DBA36C[4] = {
	-1716753461, -888970165, -660034293, 0x32fde04b
};
void __cdecl Rva00229A9CPick(int *out1, int *out2);
void __cdecl Rva00229A9CPick(int *out1, int *out2)
{
	unsigned int t = 0;
	__asm {
		mov t, esp
	}
	unsigned int i = t & 3;
	*out1 = g_Va00DBA36C[i];
	*out2 = g_Va00DBA35C[i];
}

// The obfuscation constants 0x008C0A84 and 0x008C0A80 below are written in
// decimal (9177732, 9177728): they are seed and XOR values, not image addresses.
// ?rva0022C743@Rva0022C743@@QAEPAU1@PAX0@Z @0x0022C743 134B
// Chain from 0x00229A44 via Rva00229A44Pick sibling of 0x0056F2A5.
// Evidence: same 8-int obfuscated init shape with two constants 0x008C0A84 0x008C0A80; caller 0x0022CB8F passes this plus two ptrs.
struct Rva0022C743
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0022C743 *rva0022C743(void *a1, void *a2);
};
Rva0022C743 *Rva0022C743::rva0022C743(void *a1, void *a2)
{
	int p;
	int q;
	Rva00229A44Pick(&p, &q);
	m_00 = p;
	m_04 = 9177732;
	m_08 = 9177728;
	m_0c = 9177732;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 9177732;
	m_04 = e;
	e *= b;
	e ^= 9177728;
	m_08 = e;
	e *= b;
	e ^= 9177732;
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
// ?rva0022C7C9@Rva0022C7C9@@QAEPAU1@PAX0@Z @0x0022C7C9 141B
// Chain from 0x00229A70 via Rva00229A70Pick sibling of 0x0022C743.
// Evidence: same 8-int obfuscated init shape with three constants 0x008C0A84 0x008C0A80 0x0C844203; caller 0x0022CBE8 passes this plus two ptrs.
struct Rva0022C7C9
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0022C7C9 *rva0022C7C9(void *a1, void *a2);
};
Rva0022C7C9 *Rva0022C7C9::rva0022C7C9(void *a1, void *a2)
{
	int p;
	int q;
	Rva00229A70Pick(&p, &q);
	m_00 = p;
	m_04 = 9177732;
	m_08 = 9177728;
	m_0c = 0x0C844203;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 9177732;
	m_04 = e;
	e *= b;
	e ^= 9177728;
	m_08 = e;
	e *= b;
	e ^= 0x0C844203;
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
// ?rva0022C6B6@Rva0022C6B6@@QAEPAU1@PAX0@Z @0x0022C6B6 141B
// Chain from 0x00229A18 via Rva00229A18Pick sibling of 0x0022C7C9.
// Evidence: same 8-int obfuscated init shape with three constants 0x008C0A84 0x008C0A80 0x1C0C404F; caller 0x0022CB36 passes this plus two ptrs.
struct Rva0022C6B6
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0022C6B6 *rva0022C6B6(void *a1, void *a2);
};
Rva0022C6B6 *Rva0022C6B6::rva0022C6B6(void *a1, void *a2)
{
	int p;
	int q;
	Rva00229A18Pick(&p, &q);
	m_00 = p;
	m_04 = 9177732;
	m_08 = 9177728;
	m_0c = 0x1C0C404F;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 9177732;
	m_04 = e;
	e *= b;
	e ^= 9177728;
	m_08 = e;
	e *= b;
	e ^= 0x1C0C404F;
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
// ?rva0022C856@Rva0022C856@@QAEPAU1@PAX0@Z @0x0022C856 141B
// Chain from 0x00229A9C via Rva00229A9CPick sibling of 0x0022C6B6.
// Evidence: same 8-int obfuscated init shape with three constants 0x008C0A84 0x008C0A80 0x502808C8; caller 0x0022CC41 passes this plus two ptrs.
struct Rva0022C856
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0022C856 *rva0022C856(void *a1, void *a2);
};
Rva0022C856 *Rva0022C856::rva0022C856(void *a1, void *a2)
{
	int p;
	int q;
	Rva00229A9CPick(&p, &q);
	m_00 = p;
	m_04 = 9177732;
	m_08 = 9177728;
	m_0c = 0x502808C8;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 9177732;
	m_04 = e;
	e *= b;
	e ^= 9177728;
	m_08 = e;
	e *= b;
	e ^= 0x502808C8;
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
struct Rva0056EED8
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056EED8 *rva0056EED8(void *a1, void *a2);
};
Rva0056EED8 *Rva0056EED8::rva0056EED8(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ECAEPick(&p, &q);
	m_00 = p;
	m_04 = 0xc841840;
	m_08 = 0x14ac1a82;
	m_0c = 0x4044ad0;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0xc841840;
	m_04 = e;
	e *= b;
	e ^= 0x14ac1a82;
	m_08 = e;
	e *= b;
	e ^= 0x4044ad0;
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
struct Rva0056EFF2
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056EFF2 *rva0056EFF2(void *a1, void *a2);
};
Rva0056EFF2 *Rva0056EFF2::rva0056EFF2(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ED06Pick(&p, &q);
	m_00 = p;
	m_04 = 0xc840885;
	m_08 = 0xc840881;
	m_0c = 0x48845055;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0xc840885;
	m_04 = e;
	e *= b;
	e ^= 0xc840881;
	m_08 = e;
	e *= b;
	e ^= 0x48845055;
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
// ?rva0056F07F@Rva0056F07F@@QAEPAU1@PAX0@Z @0x0056F07F 141B gap between 0x0056EFF2 and 0x0056F10C
// Same 8-int obfuscated init shape via Rva0056ED06Pick with constants 0xc840885 0x100c1887 0x48845055.
struct Rva0056F07F
{
	int m_00;
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	Rva0056F07F *rva0056F07F(void *a1, void *a2);
};
Rva0056F07F *Rva0056F07F::rva0056F07F(void *a1, void *a2)
{
	int p;
	int q;
	Rva0056ED06Pick(&p, &q);
	m_00 = p;
	m_04 = 0xc840885;
	m_08 = 0x100c1887;
	m_0c = 0x48845055;
	m_10 = *(int *)a1;
	m_14 = *(int *)a2;
	int b = q;
	int e = b;
	e *= b;
	e ^= 0xc840885;
	m_04 = e;
	e *= b;
	e ^= 0x100c1887;
	m_08 = e;
	e *= b;
	e ^= 0x48845055;
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
