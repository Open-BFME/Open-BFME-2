// cl: -DNDEBUG -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Open-BFME5: the 16-byte STLport __introsort_loop called by the matched
// Rva00477960 driver.  The retail body inlines median-of-three over the first
// integer, copies the trailing StringBase<char> handle, then calls the partition,
// recursive loop and typed partial-sort helper below.
// Parent raw tracing: ILT1492A -> iter-swap473BC0/170B (two pointers),
// ILT34F95 -> partition4747F0/133B, ILTAEBB -> this217B loop,
// ILT32501 -> partial-sort4768F0/130B. Its fourth argument is the
// STLport value-type pointer, not a depth integer (_algo.c __partial_sort).
// noinline keeps the separate retail partition call; copies/releases use
// actual StringBase<char> constructors and releaseBuffer, not dummy owners.

template <class T>
class StringBase
{
private:
	StringBase(const StringBase<T> &other);
	StringBase<T> &operator=(const StringBase<T> &other)
	{
		set(other);
		return *this;
	}

private:
	~StringBase() { releaseBuffer(); }
	void releaseBuffer();
public:
	void set(const StringBase<T> &other);
private:
	void *m_data;

	friend struct Q3SortElem16;
	friend class AsciiString;
};

// The real inline AsciiString forwarding layer is needed by the retail
// by-value copy schedule; its implicit destructor runs StringBase cleanup.
// class-gate: allow AsciiString this view is private-derives StringBase<char> with no public surface at all, so retail's owning copy schedule depends on StringBase's set/releaseBuffer being called through a private base; the shared bfme2_ascii header is public-deriving with a public destructor and its own releaseBuffer call, which is a different codegen shape. The donor places __push_heap byte-identically with this view
class AsciiString : private StringBase<char>
{
public:
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
};

struct Q3SortElem16
{
	int m_a;
	int m_b;
	int m_c;
	AsciiString m_d;
};

typedef char Q3ElementIs16[(sizeof(Q3SortElem16) == 16) ? 1 : -1];

struct Q3SortCompare
{
	void *m_state;

	__forceinline bool operator()(const Q3SortElem16 &left,
		const Q3SortElem16 &right) const
	{
		return left.m_a < right.m_a;
	}
};

__declspec(noinline) Q3SortElem16 *__unguarded_partition(Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16, Q3SortCompare);

void __partial_sort(Q3SortElem16 *, Q3SortElem16 *, Q3SortElem16 *,
	Q3SortElem16 *, Q3SortCompare);
void __make_heap(Q3SortElem16 *, Q3SortElem16 *, Q3SortCompare,
	Q3SortElem16 *, int *);
struct Rva004748F0Element
{
    int m_a;
    int m_b;
    int m_c;
    AsciiString m_d;
};
struct Rva004748F0Compare { void *m_state; };
void Rva004748F0PopHeap(Rva004748F0Element *, Rva004748F0Element *, Rva004748F0Element *,
    Rva004748F0Element, Rva004748F0Compare, int *);
void bfmeSortVOV(void *, void *, void *);

// STLport __push_heap; the matched adjust_heap body calls ILT0x49657
// to this full207B body at0x00473D60, ending ret0x00473E2E.
void __push_heap(Q3SortElem16 *first, int holeIndex,
    int topIndex, Q3SortElem16 value, Q3SortCompare comp)
{
    int parent = (holeIndex - 1) / 2;
    while (holeIndex > topIndex && comp(first[parent], value)) {
        first[holeIndex] = first[parent];
        holeIndex = parent;
        parent = (holeIndex - 1) / 2;
    }
    first[holeIndex] = value;
}
