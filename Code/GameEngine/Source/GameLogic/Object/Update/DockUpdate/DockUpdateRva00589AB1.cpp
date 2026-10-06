// cl: /EHsc /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /Ireference/shims/sweep
// stlport
// ?rva00589AB1@Rva00589AB1@@QAEXPAX@Z @0x00589AB1 78B.
// DockUpdate-like approach-owner mark-reached: search owners for arg+0x74 id and set reached bit.
// Evidence: offsets +0x40 +0x44 size sar2 plus vector bool call rowed 0x0006BE1F in DockUpdateCtor plus caller 0x004A159E passing object plus neighbour DockUpdateRemove layout.
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

class Rva00589AB1
{
public:
	char m_pad[0x40];
	ObjectIDVector m_owners;
	BoolVector m_reached;
	void rva00589AB1(void *arg);
};

void Rva00589AB1::rva00589AB1(void *arg)
{
	int target = *(int *)((char *)arg + 0x74);
	for (unsigned int i = 0; i < m_owners.size(); ++i)
	{
		if (m_owners[i] == target)
		{
			m_reached[i] = true;
			break;
		}
	}
}
