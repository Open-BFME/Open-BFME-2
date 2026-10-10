// cl: /DNDEBUG /MD /EHsc /Oy- /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva0056A3FF@Rva0056A3FF@@QAEXPAVHostClass005C8E0A@@PAV?$vector@VRva00568A20@@V?$allocator@VRva00568A20@@@_STL@@@_STL@@@Z, retail 0x0056A3FF, 171 bytes.
//
// Chain from 0x005C8E2C (HostClass pool-ref take). Callee 0x005C8E2C rowed,
// push_back 0x0056A32B rowed, erase rowed, Release_Ref rowed.
// Evidence: [esi+8] null guard and [esi+0x46] byte match HostClass005C8E0A
// layout (+8 pool, +0x46 flag); this+0x40 vector<void*> scan-erase;
// arg2 vector<Rva00568A20> push_back with {ref,host,byte} 12B element.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

// vector<void*> begin/end otherwise instantiate per-TU COMDATs (one byte
// shape per TU flags); explicit dllimport+forceinline specializations take
// those calls inline so this TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void **vector<void*>::begin()
{ return _M_start; }
template <> __declspec(dllimport) __forceinline
void **vector<void*>::end()
{ return _M_finish; }
}

class OpaqueRefCounted
{
public:
	void Release_Ref();
};

struct BfmePoolHolder88
{
	unsigned char m_pad[0x88];
	OpaqueRefCounted m_ref;
};

class BfmePoolRef10
{
public:
	BfmePoolHolder88 *m_target;
	__forceinline BfmePoolRef10() : m_target(0) {}
	BfmePoolRef10(const BfmePoolRef10 &other);
	BfmePoolRef10 &operator=(const BfmePoolRef10 &other);
	void rva000519BD();
	__forceinline ~BfmePoolRef10() { if (m_target != 0) m_target->m_ref.Release_Ref(); }
};

class LargeGroupAudioGridCell
{
public:
	void setOverlappedLocking(bool flag);
};

class HostClass005C8E0A
{
public:
	void method_005C8E0A();
	BfmePoolRef10 rva005C8E2C();
	char m_pad00[8];
	BfmePoolRef10 m_pool08;
	char m_pad0C[0x3A];
	unsigned char m_byte46;
};

class Rva00568A20
{
public:
	BfmePoolRef10 m_ref;
	HostClass005C8E0A *m_host;
	unsigned char m_byte;
	char m_pad[3];
	Rva00568A20() : m_ref(), m_host(0) {}
};

class Rva0056A3FF
{
public:
	void rva0056A3FF(HostClass005C8E0A *host, _STL::vector<Rva00568A20> *vec);
private:
	char m_pad[0x40];
	_STL::vector<void *> m_vec4040;
};

void Rva0056A3FF::rva0056A3FF(HostClass005C8E0A *host, _STL::vector<Rva00568A20> *vec)
{
	if (host->m_pool08.m_target == 0)
		return;
	Rva00568A20 elem;
	elem.m_byte = host->m_byte46;
	elem.m_ref = host->rva005C8E2C();
	elem.m_host = host;
	vec->push_back(elem);
	void **start = (void **)m_vec4040.begin();
	void **finish = (void **)m_vec4040.end();
	for (void **p = start; p != finish; ++p)
	{
		if (*p == host)
		{
			m_vec4040.erase(p);
			break;
		}
	}
}
