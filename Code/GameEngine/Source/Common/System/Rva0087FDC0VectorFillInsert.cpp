// BFME2 0x006BF800/332B: insertion of repeated non-POD 36-byte records.
// Donor: Open-BFME-1 10af19f44a89ab7ecc23195bb9a842ceafbc02c9,
// game/GameEngine/Source/Common/System/Rva0087FDC0VectorFillInsert.cpp.
// Target identity: STL vector insertion algorithm and complete Ghidra boundary;
// all ten retail call sites establish constructor/copy/fill/release/overflow.
// Application record identity remains unknown. Donor field names below are
// source provenance, not established BFME2 GeometryShape identity or types.
// Independent target evidence proves stride 36, string at 0x1C and two tail
// bytes at 0x20/0x21. Scalar/aggregate views retain native assignment codegen.
// Compiler-visible workers preserve dispatch-tag/register allocation. Their
// emitted copies reproduce the existing workers at 6BE840, 6BE370, 6BE270,
// 6BE8C0 and 6BF5E0; those ranges are already owned and are not new claims.
// Canonical constructor/string operations are linked by the explicit aliases.
// ?_M_fill_insert@?$vector@URva0087FDC0Element@@V?$allocator@URva0087FDC0Element@@@_STL@@@_STL@@QAEXPAURva0087FDC0Element@@IABU3@@Z
// cl: /O2 /Ob1 /G6 /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc_alloconly
// stlport

#include <vector>
#pragma comment(linker, "/alternatename:??0Rva006BF800RecordView@@QAE@ABU0@@Z=??0BfmeStringRecord00063BE4@@QAE@ABU0@@Z")
#pragma comment(linker, "/alternatename:?releaseBuffer@BFMERetailAsciiString@@QAEXXZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")
#pragma comment(linker, "/alternatename:??4BFMERetailAsciiString@@QAEAAV0@ABV0@@Z=?set@?$StringBase@D@@QAEXABV1@@Z")
#pragma comment(linker, "/alternatename:??0BfmeTailBE@@QAE@ABU0@@Z=??0?$StringBase@D@@AAE@ABV0@@Z")


class BFMERetailAsciiString
{
public:
	void releaseBuffer() throw();
	BFMERetailAsciiString &operator=(const BFMERetailAsciiString &);
private:
	void *m_data;
};

struct Rva006BF800RecordView
{
	int m_type;
	float m_height;
	float m_majorRadius;
	int m_minorRadius;
	int scalar10;
	int scalar14;
	float m_offsetZ;
	BFMERetailAsciiString m_name;
	bool m_enabled;
	char padding[3];

	Rva006BF800RecordView(const Rva006BF800RecordView &) throw();
	~Rva006BF800RecordView() throw() { m_name.releaseBuffer(); }
	Rva006BF800RecordView &operator=(const Rva006BF800RecordView &) throw();
};


struct Rva006BF800CoordView { int x, y, z; };
struct Rva006BF800AssignView {
    int w0, w1, w2, w3;
    Rva006BF800CoordView coord;
    BFMERetailAsciiString name;
    unsigned char byte20, byte21;
};

struct Rva0087FDC0Element : Rva006BF800RecordView
{
	Rva0087FDC0Element(const Rva0087FDC0Element &other) throw()
		: Rva006BF800RecordView(other) {}
    __forceinline Rva0087FDC0Element &operator=(const Rva0087FDC0Element &other) {
        Rva006BF800AssignView *a=(Rva006BF800AssignView *)this;
        const Rva006BF800AssignView *b=(const Rva006BF800AssignView *)&other;
        a->w0=b->w0; a->w1=b->w1; a->w2=b->w2; a->w3=b->w3;
        a->coord=b->coord; a->name=b->name; a->byte20=b->byte20; a->byte21=b->byte21;
        return *this;
    }
};

#include "../../../Include/Common/BfmeFalseBE.h"

struct BfmeTailBE
{
	char *m_p;
	BfmeTailBE(const BfmeTailBE &);
};

struct BfmeGroup10BE
{
	int m_10;
	int m_14;
	int m_18;
	BfmeTailBE m_1C;
	char m_20;
	char m_21;
};

struct BfmeElemBE
{
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	BfmeGroup10BE m_10;
};

// ?bfmeFillBE present-unmatched
__declspec(noinline) inline BfmeElemBE *bfmeFillBE(BfmeElemBE *first, unsigned count,
	const BfmeElemBE &value, const BfmeFalseBE &)
{
	BfmeElemBE *cur = first;
	while (count > 0)
	{
		if (cur != 0)
			new (cur) BfmeElemBE(value);
		++cur;
		--count;
	}
	return cur;
}

namespace _STL
{
	template <>
	__forceinline Rva0087FDC0Element *uninitialized_fill_n(
		Rva0087FDC0Element *first, unsigned count, const Rva0087FDC0Element &value)
	{
		BfmeFalseBE tag;
		return (Rva0087FDC0Element *)bfmeFillBE((BfmeElemBE *)first, count,
			*(const BfmeElemBE *)&value, tag);
	}
}


namespace _STL {
template <> __forceinline void _Construct<Rva0087FDC0Element, Rva0087FDC0Element>(
    Rva0087FDC0Element *p, const Rva0087FDC0Element &value) {
    new ((BfmeElemBE *)p) BfmeElemBE(*(const BfmeElemBE *)&value);
}
}


namespace _STL {
// ?_M_insert_overflow present-unmatched
template <> __declspec(noinline) inline void vector<Rva0087FDC0Element>::_M_insert_overflow(
    Rva0087FDC0Element *pos, const Rva0087FDC0Element &value,
    const __false_type &, unsigned fill, bool atEnd)
{
    unsigned oldSize = (unsigned)(this->_M_finish - this->_M_start);
    const unsigned &growth = oldSize < fill ? fill : oldSize;
    unsigned length = growth + oldSize;
    Rva0087FDC0Element *newStart = length ? (Rva0087FDC0Element *)allocator<char>::allocate(length * sizeof(Rva0087FDC0Element), 0) : 0;
    Rva0087FDC0Element *newFinish = __uninitialized_copy(this->_M_start, pos, newStart,
        reinterpret_cast<const __false_type &>(atEnd));
    if (fill == 1) {
        if (newFinish != 0)
            new ((Rva006BF800RecordView *)newFinish) Rva006BF800RecordView(value);
        ++newFinish;
    } else {
        newFinish = (Rva0087FDC0Element *)bfmeFillBE((BfmeElemBE *)newFinish, fill, *(const BfmeElemBE *)&value,
            reinterpret_cast<const BfmeFalseBE &>(atEnd));
    }
    if (!atEnd)
        newFinish = __uninitialized_copy(pos, this->_M_finish, newFinish,
            reinterpret_cast<const __false_type &>(atEnd));
    Rva0087FDC0Element *last = this->_M_finish;
    Rva0087FDC0Element *first = this->_M_start;
    for (; first != last; ++first)
        first->m_name.releaseBuffer();
    if (this->_M_start != 0)
        ::free(this->_M_start);
    this->_M_start = newStart;
    this->_M_finish = newFinish;
    this->_M_end_of_storage._M_data = newStart + length;
}
}

template void _STL::vector<Rva0087FDC0Element>::_M_fill_insert(
	Rva0087FDC0Element *, unsigned, const Rva0087FDC0Element &);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?insert@BfmeVec60@@QAEXPAUBfmeElem60@@IABU2@@Z=?_M_fill_insert@?$vector@URva0087FDC0Element@@V?$allocator@URva0087FDC0Element@@@_STL@@@_STL@@QAEXPAURva0087FDC0Element@@IABU3@@Z")
