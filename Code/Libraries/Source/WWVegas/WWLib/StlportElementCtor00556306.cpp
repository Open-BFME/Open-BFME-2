// cl: /O1 /MD
//
// ??0Rva00556306@@QAE@ABHABURva005564EBSub@@@Z @0x00556306 29B
// Two-argument element constructor: int plus subobject (0x38630B). Retail
// copies *a to +0 then copy-constructs +4 via pinned
// ??0Rva005564EBSub@@QAE@ABU0@@Z; ret 8. Caller 0x0055935E builds the
// 0x54c element from key [ebp+8] and Sub from 0x0055621F. Layout int-plus-
// subobject only; subobject size/lifetime from 0x00556375 body.
struct Rva005564EBSub
{
	Rva005564EBSub(const Rva005564EBSub &o);
	~Rva005564EBSub();
};

struct Rva00556306
{
	int m_00;
	Rva005564EBSub m_04;
	Rva00556306(const int &a, const Rva005564EBSub &b);
};

Rva00556306::Rva00556306(const int &a, const Rva005564EBSub &b)
	: m_00(a)
	, m_04(b)
{
}
