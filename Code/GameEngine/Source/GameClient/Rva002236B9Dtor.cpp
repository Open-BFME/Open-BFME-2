// cl: /DNDEBUG /MD /EHsc
// ??1Rva002236B9@@QAE@XZ @0x002236B9 57B
// Hash-table dtor sharing the rowed AsciiString-pair hashtable clear
// 0x002234FE then freeing the bucket array at +4 via free 0x00030830.
// Evidence: call to rowed hashtable clear with unadjusted ecx then
// mov esi [esi+4] null-guarded free; __EH_prolog frame with and [ebp-4] 0
// and or [ebp-4] -1. Same EH clear-plus-free shape as rowed
// ??1Rva0022366C@@QAE@XZ 0x0022366C (Rva0022366CDtor.cpp precedent).
// Layout matches that table: unused at +0 buckets at +4/+8/+0xC count at +0x10.
// Outer reuses the rowed clear via cast since the address already has a row.
// Callers at 0x00224D63 and jmp at 0x002238E1.
extern "C" void __cdecl free(void *block) throw(...);

class AsciiString;
namespace rts
{
template <class T> struct hash;
}
namespace _STL
{
template <class T1, class T2> struct pair;
template <class P> struct _Select1st;
template <class T> struct equal_to;
template <class T> class allocator;
template <class V, class K, class H, class S, class E, class A>
class hashtable
{
public:
	void clear();
};
}

typedef _STL::hashtable<
	_STL::pair<const AsciiString, AsciiString>,
	AsciiString,
	rts::hash<AsciiString>,
	_STL::_Select1st<_STL::pair<const AsciiString, AsciiString> >,
	_STL::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, AsciiString> > > Rva002236B9Table;

struct Rva002236B9BucketHandle
{
	~Rva002236B9BucketHandle()
	{
		if (m_beginBuckets)
			free(m_beginBuckets);
	}
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
};

class Rva002236B9
{
public:
	~Rva002236B9();
private:
	void *m_unused00;
	Rva002236B9BucketHandle m_buckets;
	unsigned int m_numElements;
};

Rva002236B9::~Rva002236B9()
{
	((Rva002236B9Table *)this)->clear();
}
