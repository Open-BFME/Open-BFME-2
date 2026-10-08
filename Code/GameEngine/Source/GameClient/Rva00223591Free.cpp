// cl: /O1 /G7 /arch:SSE /EHsc /Ireference/shims/bfme2_ascii /MD
// ?rva00223591@Rva00223591@@QAEXPAX@Z @0x00223591 28B
// Free-node for 12-byte node (4 next + 8 pair<const AsciiString TreeHintRef00222C5A>): destroys pair at +4 via rowed 0x00222C5A then frees node via _free 0x00030830 with null guard.
// Evidence: caller 0x0022380B sets ecx plus node arg; same shape as rowed ?rva00223898@Rva00223898@@QAEXPAX@Z 0x00223898.
// Private AsciiString kept not shared header: header inlines AsciiString teardown and the pair call stops resolving to rowed 0x00222C5A.
extern "C" void __cdecl free(void *);

#include "ascii_string.h"

struct TreeHintRef00222C5A
{
	char m_body[4];
};

namespace _STL {
template <class T1, class T2> struct pair
{
	pair(const T1 &,const T2 &);
	~pair();
	T1 first;
	T2 second;
};
}

class Rva000427195
{
public:
	void rva00212858(unsigned int n);
	int bucketIndex(const AsciiString *key);
};

class Rva00223124
{
public:
	void *rva00223124(const void *obj);
};

class Rva00223591
{
public:
	void rva00223591(void *p);
	void rva0022380B();
	_STL::pair<const AsciiString, TreeHintRef00222C5A> *rva00223854(const _STL::pair<const AsciiString, TreeHintRef00222C5A> *arg);
private:
	void *m_unused00;
	void **m_beginBuckets;
	void **m_endBuckets;
	void **m_storageEnd;
	unsigned int m_numElements;
};

void Rva00223591::rva00223591(void *p)
{
	((_STL::pair<const AsciiString, TreeHintRef00222C5A> *)((char *)p + 4))->~pair();
	if (p)
		free(p);
}

void Rva00223591::rva0022380B()
{
	for (unsigned i = 0; i < (unsigned)(((char *)m_endBuckets - (char *)m_beginBuckets) >> 2); ++i)
	{
		void *cur = m_beginBuckets[i];
		while (cur != 0)
		{
			void *next = *(void **)cur;
			rva00223591(cur);
			cur = next;
		}
		m_beginBuckets[i] = 0;
	}
	m_numElements = 0;
}

_STL::pair<const AsciiString, TreeHintRef00222C5A> *Rva00223591::rva00223854(const _STL::pair<const AsciiString, TreeHintRef00222C5A> *arg)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	int b = ((Rva000427195 *)this)->bucketIndex(&arg->first);
	void *old = m_beginBuckets[b];
	void *n = ((Rva00223124 *)this)->rva00223124(arg);
	*(void **)n = old;
	m_beginBuckets[b] = n;
	++m_numElements;
	return (_STL::pair<const AsciiString, TreeHintRef00222C5A> *)((char *)n + 4);
}

// Native2240CB..224163 RET4: name-keyed string default insertion.
// Iterator lifetime ends before pair construction; the verified nonthrowing
// lookup41534B permits its two-word return buffer to become the pair slot.
class Rva00056F61;
struct Rva0041534BIter {
 void *m_node;Rva00056F61 *m_table;
 Rva0041534BIter(void *n,Rva00056F61*t):m_node(n),m_table(t){}
};
class Rva00056F61 {public:__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *);};
typedef _STL::pair<const AsciiString,AsciiString> Rva002240CBPair;
class Rva002240CB {public:AsciiString &rva002240CB(const AsciiString &);};
AsciiString &Rva002240CB::rva002240CB(const AsciiString &key) {
 void *node;
 {
  Rva0041534BIter it=((Rva00056F61*)this)->rva0041534B(&key);
  node=it.m_node;
 }
 return *(AsciiString*)(!node ?
  (char*)((Rva00223591*)this)->rva00223854(
   (const _STL::pair<const AsciiString,TreeHintRef00222C5A>*)
   &static_cast<const Rva002240CBPair&>(Rva002240CBPair(key,AsciiString())))+4 : (char*)node+8);
}
