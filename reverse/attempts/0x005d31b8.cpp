// ?rva005D31B8@Rva005D30EE@@QAEXHH@Z
// partial score=0.95 date=2026-10-05
// CANDIDATE (near miss, one byte off) for the APT text-set trio
// 0x005D30EE / 0x005D3153 / 0x005D31B8 (101B each).
// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// Shape decoded: if ((a,b) != cached pair) { build a UnicodeString over a
// dead 4B stack slot via 0x005D303A; Set(level, outer, suffix, text);
// destroy; cache (a,b); } Suffixes are real .rdata strings (VA-linked,
// base 0x400000): "BuildPlots" / "ArmoryPoints" / "CommandPoints".
// 0x005D303A(out*,a,b) returns out (its tail is mov eax,[ebp+8]);
// 0x005D2FD0 is the rowed Rva005D2FD0Set; 0x00036E70 is ??1UnicodeString
// (folded onto releaseBuffer, pinned).
//
// CURRENT MISS: this spelling emits `lea ecx,[ebp+0xC]` for the dtor while
// retail has `[ebp+8]` -- the late-guarded tmp takes the second slot because
// the build buffer (char buf[4]) takes the first. Declaring tmp first moves
// the guard-start (and [ebp-4],0) above the Make call, which is equally
// wrong. The guard object must be declared after Make AND take the first
// slot; no spelling found in ~90min of probing (a-k, n). Next ideas:
// out-parameter construction with delayed guard, or a different (unknown)
// original idiom for building text over the dead arg slot.
#include "string_base.h"
class UnicodeString
{
public:
	UnicodeString() {}
	~UnicodeString();
private:
	StringBase<unsigned short> *m_data;
};
struct Rva005D2FD0Inner
{
	char m_pad8[8];
	char m_name[1];
};
struct Rva005D2FD0Outer
{
	Rva005D2FD0Inner *m_ptr;
};
void __cdecl Rva005D2FD0Set(int level, Rva005D2FD0Outer *outer, const char *suffix, const UnicodeString &text);
UnicodeString *Rva005D303A(UnicodeString *out, int a, int b);
class Rva005D30EE
{
public:
	void rva005D30EE(int a, int b);
	void rva005D3153(int a, int b);
	void rva005D31B8(int a, int b);
private:
	int m_00;
	Rva005D2FD0Outer m_04;
	int m_08;
	int m_0C;
	int m_10;
	int m_14;
	int m_18;
	int m_1C;
};
void Rva005D30EE::rva005D30EE(int a, int b)
{
	if (a != m_08 || b != m_0C) {
		char buf[4];
		register UnicodeString *text = Rva005D303A((UnicodeString *)buf, a, b);
		{
			UnicodeString tmp;
			Rva005D2FD0Set(m_00, &m_04, "BuildPlots", *text);
		}
		m_08 = a;
		m_0C = b;
	}
}
void Rva005D30EE::rva005D3153(int a, int b)
{
	if (a != m_10 || b != m_14) {
		char buf[4];
		register UnicodeString *text = Rva005D303A((UnicodeString *)buf, a, b);
		{
			UnicodeString tmp;
			Rva005D2FD0Set(m_00, &m_04, "ArmoryPoints", *text);
		}
		m_10 = a;
		m_14 = b;
	}
}
void Rva005D30EE::rva005D31B8(int a, int b)
{
	if (a != m_18 || b != m_1C) {
		char buf[4];
		register UnicodeString *text = Rva005D303A((UnicodeString *)buf, a, b);
		{
			UnicodeString tmp;
			Rva005D2FD0Set(m_00, &m_04, "CommandPoints", *text);
		}
		m_18 = a;
		m_1C = b;
	}
}
