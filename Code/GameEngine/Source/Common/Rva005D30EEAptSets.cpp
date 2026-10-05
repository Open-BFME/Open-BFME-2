// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
//
// APT text setters, 101B each: if the (a, b) pair changed since last time,
// rebuild the UnicodeString via 0x005D303A (which returns it by value through
// the hidden pointer, letting the compiler thread eax straight into the Set
// call with no lea), push it through the rowed Rva005D2FD0Set with the
// per-field suffix, destroy the temporary, and cache the pair.
//
//   0x005D30EE  pair +0x08  suffix "BuildPlots"
//   0x005D3153  pair +0x10  suffix "ArmoryPoints"
//   0x005D31B8  pair +0x18  suffix "CommandPoints"
// Suffixes are real .rdata strings (VA-linked, image base 0x400000; read back
// to confirm content). 0x005D303A(out,a,b) itself formats via L"%d/%d" and
// converts via 0x00037050; only its address is needed here (new pin
// ?Rva005D303A@@YA?AVUnicodeString@@HH@Z). The temporary's destructor
// resolves through the existing ??1UnicodeString@@QAE@XZ pin at 0x00036E70
// (the folded releaseBuffer body retail call sites encode directly).
// Outer views copied from Rva005D2FD0Apt.cpp.
#include "string_base.h"
// class-gate: allow UnicodeString (proved codegen view: retail encodes the
// out-of-line ??1UnicodeString, folded onto releaseBuffer at 0x00036E70,
// directly for these temporaries (see the pin note measuring GadgetCheckBox
// +0x37); the shared header's empty inline ~UnicodeString() emits no guard
// states and cannot reproduce the and/or EH shape -- probes a-q)
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
UnicodeString Rva005D303A(int a, int b);
void __cdecl Rva005D2FD0Set(int level, Rva005D2FD0Outer *outer, const char *suffix, const UnicodeString &text);
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
		Rva005D2FD0Set(m_00, &m_04, "BuildPlots", Rva005D303A(a, b));
		m_08 = a;
		m_0C = b;
	}
}
void Rva005D30EE::rva005D3153(int a, int b)
{
	if (a != m_10 || b != m_14) {
		Rva005D2FD0Set(m_00, &m_04, "ArmoryPoints", Rva005D303A(a, b));
		m_10 = a;
		m_14 = b;
	}
}
void Rva005D30EE::rva005D31B8(int a, int b)
{
	if (a != m_18 || b != m_1C) {
		Rva005D2FD0Set(m_00, &m_04, "CommandPoints", Rva005D303A(a, b));
		m_18 = a;
		m_1C = b;
	}
}
