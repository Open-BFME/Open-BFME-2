// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva003B930D@Rva003B8BAA@@QAEXPAV?$vector@JV?$allocator@J@_STL@@@_STL@@@Z @0x003B930D 92B.
// Filter member vector at +0x14 by unsigned char Rva003B8B2A check, collecting
// matching indices as long into output vector via rowed reserve 0x002B712E
// plus ICF push_back 0x004DFCB0 (long J twin pinned there). Evidence: this is
// Rva003B8BAA via global g_00E02D6C same as Rva003B8BAA lookups; caller
// 0x00522116 in 0x00521EDA passes stack vector and uses first element for
// GameInfo+0x58; callees rowed Rva003B8B2A 0x003B8B2A plus reserve/push_back;
// flags from stlport_pod_vector_bodies.cpp; unsigned loop gives sar-je plus jb,
// unsigned char cast gives test al.
// The native17B unsigned-max provider is owned by stlport_narrow_istream.cpp
// at0x13740. Declare it here instead of emitting a private compiler variant.
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <vector>

// Existing native49B long-vector fold is supplied by WeaponRebuildScatterTargets.
namespace _STL {
template <> void vector<long>::push_back(const long &);
}

class Rva003B8B2A
{
	char m_pad00[0x1C];
	int m_field1C;
	int m_field20;
	char m_pad24[0x4C - 0x24];
	unsigned char m_flag4C;
public:
	int rva003B8B2A();
};

class Rva003B8BAA
{
	char m_pad[0x14];
	_STL::vector<Rva003B8B2A *> m_vec14;
public:
	void rva003B930D(_STL::vector<long> *out);
};

void Rva003B8BAA::rva003B930D(_STL::vector<long> *out)
{
	out->reserve(m_vec14.size());
	for (long i = 0; i < m_vec14.size(); ++i)
	{
		Rva003B8B2A *elem = m_vec14[i];
		if ((unsigned char)elem->rva003B8B2A())
			out->push_back(i);
	}
}
