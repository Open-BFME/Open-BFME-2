// cl: /O1 /EHsc /MD /arch:SSE /G7 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva002B8817@Rva002B8817@@QAEXPAX0@Z @0x002B8817 73B. Tree at this+0x130 iterated via _M_increment; each node second at +0x14 is call object and vector element; filter arg +0x14 compared to call return; on equality push element to vector arg; prev 0x002B87E0 next 0x002B8860 contiguous; callees rowed push_back 0x004DFCB0 and _M_increment 0x00024250 plus pinned 0x004FBED6; caller 0x00576C0C; address-derived honest name.
// Evidence: retail push ebp mov ebp esp push ecx push ebx mov ebx [ecx+130] push esi mov esi [ebx+8] cmp je push edi mov ecx [esi+14] mov eax [ebp+8] mov edi [eax+14] mov [ebp-4] ecx call 0x4FBED6 cmp eax edi jne mov ecx [ebp+C] lea eax [ebp-4] push call 0x4DFCB0 push esi call 0x24250 mov esi eax cmp pop ecx jne pop edi pop esi pop ebx leave ret 8.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <map>
#include <vector>

struct Rva004DFCB0Element
{
	unsigned word0;
};

class Rva004FBED6Call
{
public:
	void *rva004FBED6();
};

struct Rva002B8817Filter
{
	char m_pad00[0x14];
	void *m_14;
};

typedef _STL::map<int, Rva004DFCB0Element> Rva002B8817Map;
typedef _STL::vector<Rva004DFCB0Element> Rva002B8817Vec;

class Rva002B8817
{
public:
	void rva002B8817(void *a, void *b);
private:
	char m_pad00[0x130];
	void *m_phead130;
};

void Rva002B8817::rva002B8817(void *a, void *b)
{
	Rva002B8817Filter *filter = (Rva002B8817Filter *)a;
	Rva002B8817Vec *vec = (Rva002B8817Vec *)b;
	typedef _STL::pair<const int, Rva004DFCB0Element> Pair130;
	typedef _STL::_Rb_tree_node<Pair130> Node130;
	Node130 *header = (Node130 *)m_phead130;
	Node130 *first = *(Node130 **)((char *)header + 8);
	Rva002B8817Map::iterator end((Node130 *)header);
	for (Rva002B8817Map::iterator it = (Node130 *)first; it != end; ++it) {
		Rva004FBED6Call *obj = (Rva004FBED6Call *)(*it).second.word0;
		void *filtVal = filter->m_14;
		Rva004DFCB0Element e;
		e.word0 = (unsigned)obj;
		void *ret = obj->rva004FBED6();
		if (ret == filtVal)
			vec->push_back(e);
	}
}
