// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Oi /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?rva00059DF5@Rva00059DF5@@QAEXABVAsciiString@@H@Z at 0x00059DF5 (103B).
// Guard over +0x9D4 then virtual slot 0x68 then set insert at +0xA14.
// Evidence: MilesMutexGuard ctor 0x4120E/dtor 0x4122F, virtual call [eax+0x68]
// with (AsciiString,int), set insert row 0x5897D with (idx+0xD7)*12+this
// folding base 0xA14, imul 0xC needs /G7. No callers.
#include <set>

#include "ascii_string.h"

bool operator<(const AsciiString &left, const AsciiString &right);

namespace _STL
{
template <> struct less<AsciiString>
{
	bool operator()(const AsciiString &left, const AsciiString &right) const
	{
		return left < right;
	}
};
}

class MilesMutexGuard
{
public:
	MilesMutexGuard(void *mutex, int defer);
	~MilesMutexGuard();
private:
	void *m_mutex;
	int m_flags;
};

class Rva00059DF5
{
public:
	virtual void f00();
	virtual void f01();
	virtual void f02();
	virtual void f03();
	virtual void f04();
	virtual void f05();
	virtual void f06();
	virtual void f07();
	virtual void f08();
	virtual void f09();
	virtual void f10();
	virtual void f11();
	virtual void f12();
	virtual void f13();
	virtual void f14();
	virtual void f15();
	virtual void f16();
	virtual void f17();
	virtual void f18();
	virtual void f19();
	virtual void f20();
	virtual void f21();
	virtual void f22();
	virtual void f23();
	virtual void f24();
	virtual void f25();
	virtual void vf26(const AsciiString &a, int idx);
	void rva00059DF5(const AsciiString &a, int idx);
	void rva00059E5C(int idx);
private:
	char m_pad4[0x9D4 - 4];
	void *m_mutex;
	char m_pad9D8[0xA14 - 0x9D8];
	_STL::set<AsciiString> m_sets[4];
};

void Rva00059DF5::rva00059DF5(const AsciiString &a, int idx)
{
	MilesMutexGuard guard(&m_mutex, 0);
	vf26(a, idx);
	m_sets[idx].insert(a);
}

// ?rva00059E5C@Rva00059DF5@@QAEXH@Z at 0x00059E5C (82B).
// Sibling of 0x00059DF5: guard over +0x9D4 then tree clear 0x57B4B at +0xA14.
// Evidence: same mutex/sets layout, add 0xD7 imul 0xC needs /G7, ret 4 single int.
void Rva00059DF5::rva00059E5C(int idx)
{
	MilesMutexGuard guard(&m_mutex, 0);
	m_sets[idx].clear();
}
