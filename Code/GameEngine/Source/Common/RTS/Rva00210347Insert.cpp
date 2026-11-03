// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva00210347@Rva00210347@@QAEAAU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@ABU23@@Z @0x00210347 68B hash insert via resize plus bucketIndex plus node alloc
// Evidence: same 68B shape as rowed Rva002249ED 0x002249ED calling resize 0x00212858 plus rowed bucketIndex 0x00223149 plus node allocator; allocator is thiscall twin of rowed free Rva0020F569Alloc 0x0020F569 via call-site mov ecx esi like 0x001DE556; buckets at +4 and count at +0x10; caller 0x002104ED.
#include "ascii_string.h"
#include <map>

struct NoCaseTreeValue4
{
	char m_body[4];
	NoCaseTreeValue4() { *(unsigned int *)m_body = 0; }
};

typedef _STL::pair<const AsciiString, NoCaseTreeValue4> NocasePair;

struct Rva00210347Node
{
	Rva00210347Node *m_next;
	NocasePair m_value;
};

#include "../../../Include/GameLogic/Rva000427195.h"

class Rva00210347
{
public:
	NocasePair &rva00210347(const NocasePair &value);
private:
	void *m_unused;
	Rva00210347Node **m_beginBuckets;
	Rva00210347Node **m_endBuckets;
	Rva00210347Node **m_capacity;
	unsigned int m_numElements;
};

void *__stdcall Rva0020F569Alloc(const NocasePair &);
// The complete 20F569 allocator consumes the stack value and ignores ECX.
// MSVC's four-byte member-pointer representation retains the native unused
// receiver while naming the existing stdcall provider and no extra symbol.
union NativeNodeAllocCall {
 void *(__stdcall *target)(const NocasePair &);
 void *(Rva00210347::*member)(const NocasePair &);
};
typedef char NodeAllocPointerWidth[sizeof(NativeNodeAllocCall)==4 ? 1 : -1];

NocasePair &Rva00210347::rva00210347(const NocasePair &value)
{
	((Rva000427195 *)this)->rva00212858(m_numElements + 1);
	unsigned int bucket = ((Rva000427195 *)this)->bucketIndex(&value.first);
	Rva00210347Node *first = m_beginBuckets[bucket];
	NativeNodeAllocCall call={&Rva0020F569Alloc};
	Rva00210347Node *node = (Rva00210347Node *)(this->*call.member)(value);
	node->m_next = first;
	m_beginBuckets[bucket] = node;
	++m_numElements;
	return node->m_value;
}

// Native 2104ED..210566 RET4; existing insert210347 owns the name/value pair.
// The iterator provider only hashes and compares existing string bytes.
// End its nonthrowing lookup scope before constructing the conditional pair.
class Rva00056F61;
#include "../../../Include/GameClient/Rva0041534BIter.h"

class Rva00056F61
{
public:
	__declspec(nothrow) Rva0041534BIter rva0041534B(const AsciiString *key);
};

class Rva002104ED
{
public:
	NoCaseTreeValue4 &rva002104ED(const AsciiString *key);
private:
	char m_pad[0];
};


NoCaseTreeValue4 &Rva002104ED::rva002104ED(const AsciiString *key)
{
	void *node;
 { Rva0041534BIter it = ((Rva00056F61 *)this)->rva0041534B(key); node = it.m_node; }
	return node == 0 ? ((Rva00210347 *)this)->rva00210347(NocasePair(*key, NoCaseTreeValue4())).second
		: *(NoCaseTreeValue4 *)((char *)node + 8);
}


