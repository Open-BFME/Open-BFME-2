// ?rva005F8A7E@Rva005F8A7E@@QAEXXZ
// partial score=0.78 date=2026-10-06
// cl: /O1 /arch:SSE /DNDEBUG /MD
// ?rva005F8A7E@Rva005F8A7E@@QAEXXZ @0x005F8A7E 158B evidence: thiscall member
// guards on just-landed __cdecl ?Rva005F88F4Get@@YAHH@Z @0x005F88F4 (m_20)
// plus its result's virtual slot 7 (+0x1C, m_28) into a byte bool, feeds it
// to sub-object at +8 (pinned direct thiscalls 0x005E1160/68/70/78/8B),
// counts m_28 matches over the slot-13 (+0x34) vec with pointer bounds, then
// dispatches: matches>0 calls 0x005E1168 else 0x005E1170; matches>0 builds
// banked-partial 0x005F8A0C(m_20,m_28,m_2C) via nested-call arg reuse
// (add-esp-8 plus movss plus outer ret-4) into 0x005E1178, else tail-jmps
// 0x005E118B. matches is early-declared (push ebx placement) and counted in
// edx with an ebx join copy; ok is byte bool with raw push. Sub/result/vec
// views are TU-local (slots honest, dummies structural).
#include <xmmintrin.h>

class Rva005F8A7ESub;
void __fastcall rva005E1160(Rva005F8A7ESub *sub, bool ok);
void __fastcall rva005E1168(Rva005F8A7ESub *sub, int matches);
void __fastcall rva005E1170(Rva005F8A7ESub *sub);
void __fastcall rva005E1178(Rva005F8A7ESub *sub, float r);
void __fastcall rva005E118B(Rva005F8A7ESub *sub);

struct Rva005F8A7EVec
{
	int m_begin;
	int m_end;
};

class Rva005F8A7ERes
{
public:
	virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
	virtual void w04(); virtual void w05(); virtual void w06();
	virtual bool rva005F8A7ECheck(int arg);	// slot 7 (+0x1C)
	virtual void w08(); virtual void w09(); virtual void w10(); virtual void w11();
	virtual void w12();
	virtual Rva005F8A7EVec *rva005F8A7EGetVec();	// slot 13 (+0x34)
};

class Rva005F8A7E
{
public:
	void rva005F8A7E();
private:
	char m_pad[0x20];
	int m_20;
	int m_24;
	int m_28;
	int m_2C;
};

int __cdecl Rva005F88F4Get(int arg);
__m128 __cdecl Rva005F8A0C(int a, int b, int c);

// ?rva005F8A7E@Rva005F8A7E@@QAEXXZ present-unmatched
void Rva005F8A7E::rva005F8A7E()
{
	Rva005F8A7ERes *res = (Rva005F8A7ERes *)Rva005F88F4Get(m_20);
	bool ok;
	if (res && res->rva005F8A7ECheck(m_28))
		ok = true;
	else
		ok = false;
	Rva005F8A7ESub *sub = (Rva005F8A7ESub *)((char *)this + 8);
	rva005E1160(sub, ok);
	int matches;
	if (res)
	{
		Rva005F8A7EVec *vec = res->rva005F8A7EGetVec();
		int *end = (int *)vec->m_end;
		int *p = (int *)vec->m_begin;
		matches = 0;
		while (p != end)
		{
			if (*p == m_28)
				++matches;
			++p;
		}
	}
	else
	{
		matches = 0;
	}
	if (matches > 0)
		rva005E1168(sub, matches);
	else
		rva005E1170(sub);
	if (matches > 0)
	{
		float r;
		_mm_store_ss(&r, Rva005F8A0C(m_20, m_28, m_2C));
		rva005E1178(sub, r);
	}
	else
		return rva005E118B(sub);
}
