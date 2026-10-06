// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/sweep
// stlport
// ?rva00589AFF@DockUpdate@@QAEXH@Z @0x00589AFF 126B.
// DockUpdate approach-owner remove shifting owners and reached bits.
// Evidence: offsets +0x60 +0x64 +0x6c match DockUpdateCtor layout plus callers 0x00589DDD 0x00589E77 via esi-0x20 plus vector bool callees rowed in DockUpdateCtor.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

enum ObjectID
{
	INVALID_ID = 0,
	FORCE_OBJECTID_TO_LONG_SIZE = 0x7fffffff
};

#include <stl/_bvector.h>

namespace _STL
{
template <>
class vector<ObjectID, allocator<ObjectID> > : public _Vector_base<ObjectID, allocator<ObjectID> >
{
public:
	__forceinline vector() : _Vector_base<ObjectID, allocator<ObjectID> >(allocator<ObjectID>()) {}
	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	ObjectID &operator[](unsigned int index)
	{
		return _M_start[index];
	}
};
}

typedef _STL::vector<ObjectID, _STL::allocator<ObjectID> > ObjectIDVector;
typedef _STL::vector<bool, _STL::allocator<bool> > BoolVector;

class DockUpdate
{
public:
	char m_pad[0x60];
	ObjectIDVector m_owners;
	BoolVector m_reached;
	void rva00589AFF(int index);
};

void DockUpdate::rva00589AFF(int index)
{
	int last = (int)m_owners.size() - 1;
	for (; index < last; ++index)
	{
		if (m_owners[index] == INVALID_ID)
			break;
		m_owners[index] = m_owners[index + 1];
		m_reached[index] = m_reached[index + 1];
	}
	m_owners[last] = INVALID_ID;
	m_reached[last] = false;
}
