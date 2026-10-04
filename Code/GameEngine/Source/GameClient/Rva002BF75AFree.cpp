// cl: /Ireference/shims/bfme2_ascii /O1 /MD
// ?rva002BF75A@Rva002BF75A@@QAEXPAX@Z @0x002BF75A 28B
// Free-node for 12-byte node (4 next + 8 pair<const AsciiString TreeHintRef00217D4C>): destroys pair at +4 via rowed 0x002BF0D6 then frees node via _free 0x00030830 with null guard.
// Evidence: unlock lane plus callers 0x002BF7DF 0x002BFAC9 set ecx plus node arg plus same shape as rowed ?rva00223591@Rva00223591@@QAEXPAX@Z 0x00223591 and ?rva00223898@Rva00223898@@QAEXPAX@Z 0x00223898.
// Private AsciiString kept not shared header: header inlines AsciiString teardown and the pair call stops resolving to rowed 0x002BF0D6.
extern "C" void __cdecl free(void *);
void __cdecl dup_002bf0d6(void);
typedef void (__fastcall *PairDtorFn)(void *p);

class AsciiString
{
public:
	~AsciiString();
private:
	char m_pad[4];
};

struct TreeHintRef00217D4C
{
	char m_body[4];
};

namespace _STL {
template <class T1, class T2> struct pair
{
	~pair();
	T1 first;
	T2 second;
};
}

class Rva002BF75A
{
public:
	void rva002BF75A(void *p);
	void rva002BF7BE();
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva002BF75A::rva002BF75A(void *p)
{
	((PairDtorFn)&dup_002bf0d6)((void *)((char *)p + 4));
	if (p)
		free(p);
}

// ?rva002BF7BE@Rva002BF75A@@QAEXXZ @0x002BF7BE 73B chain clear via rowed 0x002BF75A plus callers 0x002BFA62 0x002BFD81 plus same shape as rowed Rva00223591 clear.
void Rva002BF75A::rva002BF7BE()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			rva002BF75A(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}
