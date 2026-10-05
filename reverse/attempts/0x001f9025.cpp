// ?rva001F9025@Rva001F9025@@QAEXXZ
// partial score=0.85 date=2026-10-05
// Banked near-miss for F1 anchor 0x001F9025 (59B). Matches 57/59 bytes:
// everything through the M1 call is exact (EH prolog + cookie DIR32,
// push ecx/esi, mov esi,ecx, mov [ebp-0x10],esi, and [ebp-4],0,
// neg/lea/sbb/and guard, call M1). Missing: `or [ebp-4],-1` after M1,
// and retail has no ctor return-this (mov eax,esi).
// Tried: void method (no EH frame), void method + try/catch (wrong frame:
// ebp-0x14 + ebx/edi saves), void method + function-try (65B),
// dtor + explicit dtor (extra push edi + auto-destroy call at end),
// union dtor (C2623: union member with dtor is illegal),
// void method + explicit opaque-dtor call (25B, no EH at all),
// storage-placement dtor (25B, no EH).
// Conclusion: needs void/no-return-this + ctor-style EH frame + state -1
// with exactly 2 calls and no auto-destruction. M2 is the rowed
// ?rva001F4206@Rva001F4206@@QAEXXZ (release+delete); M1 chain mapped:
// 9025->18167, A5BB->9B69, A5F6->9B69, AB1E->A5BB, B829->A5F6,
// B98A->AB1E, B9C5->B829, BB29->B98A, BB64->B9C5, BCDC->BB29.
// 0x001F8167 itself is dtor-shaped (release loop + operator delete);
// 0x001F9B69 is another same-shape instance. Next: find what emits
// or [ebp-4],-1 in a void EH method with no dtor calls (try/finally?
// scope guard with dismissed inline dtor?).

class Rva001F4206
{
public:
	void rva001F4206();
};

class H1F8167
{
public:
	~H1F8167();
	void m001F8167();
private:
	int m_00;
};

class Rva001F9025 : public Rva001F4206
{
public:
	Rva001F9025();
private:
	char m_pad00[4];
	H1F8167 m_04;
};
Rva001F9025::Rva001F9025()
{
	H1F8167 *p = this ? &m_04 : 0;
	p->m001F8167();
	Rva001F4206::rva001F4206();
}
