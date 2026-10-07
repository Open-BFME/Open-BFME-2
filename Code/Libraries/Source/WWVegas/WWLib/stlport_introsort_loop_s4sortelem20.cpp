// cl: /DNDEBUG /MD /EHsc
// stlport
//
// Bodies ported from Open-BFME-1's
// Libraries/Source/WWVegas/WWLib/stlport_introsort_loop_s4sortelem20.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: ??$swap@US4SortElem20@@@_STL@@YAXAAUS4So 0x003373D9 (75B).
// Callee addresses are read off retail's call sites (reverse/symbols.csv).
// Only the placed bodies are carried; the donor's other definitions are
// omitted.

// Open-BFME: STLport 4.5.3 __introsort_loop over the twenty-byte S4 record
// used by the adjacent insertion, heap, partial-sort, and partition family.
// The record has a 12-byte vector tail. AsciiString copies use the private
// StringBase constructor; cleanup calls the existing AsciiString destructor.

#include <algorithm>

template <class T>
class StringBase
{
    friend class AsciiString;
private:
    struct Header
    {
        int m_bfmeRefCount;
        unsigned short m_bfmeLength;
        unsigned short m_bfmeCapacity;
        T m_bfmeData[1];
    };

    Header *m_bfmeHeader;
    StringBase(const StringBase<T> &other);
    ~StringBase();

public:
    void set(const StringBase<T> &other);

    // Out of line: retail calls the shared StringBase<char>::compare at
    // 0x000069D6; an inline body here would emit a private copy of it.
    int compare(const StringBase<T> &other) const;

    friend struct S4SortElem20;
};


// Retail S4+0 is the AsciiString wrapper. Its four-byte StringBase subobject
// keeps the 20-byte record layout, while cleanup resolves the distinct QAE
// AsciiString destructor (RVA 0x005EE90 / ILT 0x0000D828), not the private
// StringBase<char> destructor.
// class-gate: allow AsciiString the donor's own view; the placed bodies are byte-exact under it
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other)
        : StringBase<char>(other) {}
    ~AsciiString();
    // Public copy-set uses the existing folded StringBase worker.
    void set(const AsciiString &other);
    AsciiString &operator=(const AsciiString &other)
    {
        StringBase<char>::set(other);
        return *this;
    }
    // No AsciiString::compare here: retail's comparator calls the shared
    // StringBase<char>::compare at 0x000069D6 directly (S4Cmp002EB8E0 below),
    // and a member defined in this view was emitted as a private five-byte
    // forwarding COMDAT that the link kept over BFME 2's /alternatename.
};

struct BfmeSortTailElement12;

class BfmeSortElem20Tail
{
public:
    BfmeSortElem20Tail(const BfmeSortElem20Tail &other);
    ~BfmeSortElem20Tail();
    void set(const BfmeSortElem20Tail &other);

private:
    BfmeSortTailElement12 *m_begin;
    BfmeSortTailElement12 *m_end;
    BfmeSortTailElement12 *m_capacity;
};

struct S4SortElem20
{
	AsciiString m_bfmeName;
	char m_bfmeFlag;
	BfmeSortElem20Tail m_bfmeTail;

	// Retail 0x3372EC is a 39-byte assignment body whose calls go to the
	// StringBase setter at 0x366F0 and tail setter at 0x332217. The call target
	// is pinned from the BFME1 donor's placed caller; the Ghidra boundary and
	// those callees are target evidence. Preserve the donor's field-wise copy:
	// compiler-generated whole-tail copying emits a different 38-byte body.
	S4SortElem20 &operator=(const S4SortElem20 &other)
	{
		m_bfmeName = other.m_bfmeName;
		m_bfmeFlag = other.m_bfmeFlag;
		m_bfmeTail.set(other.m_bfmeTail);
		return *this;
	}
};

struct S4Cmp002EB8E0
{
	int m_bfmeSlot;

	bool operator()(const S4SortElem20 &left,
		const S4SortElem20 &right) const
	{
		return ((const StringBase<char> &)left.m_bfmeName).compare(
			(const StringBase<char> &)right.m_bfmeName) < 0;
	}
};

namespace _STL
{

// Bind the retail 0x002EB330 partial-sort
// owner instead of emitting another helper family in this TU.
template <>
void __partial_sort<S4SortElem20 *, S4SortElem20, S4Cmp002EB8E0>(
	S4SortElem20 *, S4SortElem20 *, S4SortElem20 *,
	S4SortElem20 *, S4Cmp002EB8E0);

template void __introsort_loop<S4SortElem20 *, S4SortElem20, int,
	S4Cmp002EB8E0>(S4SortElem20 *, S4SortElem20 *, S4SortElem20 *, int,
	S4Cmp002EB8E0);

}
