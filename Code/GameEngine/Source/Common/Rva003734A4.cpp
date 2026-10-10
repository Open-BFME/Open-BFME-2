// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// MineshaftPortalBehaviour::addArrivingObject (WorldBuilder name, MineshaftPortalBehaviour.cpp line 164: push_back onto the arriving list).
// stlport
//
// was ?rva003734A4@Rva003734A4@@QAEXPAX@Z @0x003734A4 (28B).
// Vector push_back of ScienceType field at +0x74 of arg into vector at +0x28
// via rowed push_back 0x002E01C6. EBP frame from /O1. Between 0x0037341F and
// 0x003734C0. Flags from Rva00373357 neighbour.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

enum ScienceType
{
	SCIENCE_Dummy0
};

class MineshaftPortalBehaviour
{
public:
	void addArrivingObject(void *p);
private:
	char m_pad[0x28];
	_STL::vector<ScienceType> m_vec;
};

void MineshaftPortalBehaviour::addArrivingObject(void *p)
{
	ScienceType tmp = *(ScienceType *)((char *)p + 0x74);
	m_vec.push_back(tmp);
}
