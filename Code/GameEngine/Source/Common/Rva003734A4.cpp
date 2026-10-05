// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva003734A4@Rva003734A4@@QAEXPAX@Z @0x003734A4 (28B).
// Vector push_back of ScienceType field at +0x74 of arg into vector at +0x28
// via rowed push_back 0x002E01C6. EBP frame from /O1. Between 0x0037341F and
// 0x003734C0. Flags from Rva00373357 neighbour.
#include <vector>

enum ScienceType
{
	SCIENCE_Dummy0
};

class Rva003734A4
{
public:
	void rva003734A4(void *p);
private:
	char m_pad[0x28];
	_STL::vector<ScienceType> m_vec;
};

void Rva003734A4::rva003734A4(void *p)
{
	ScienceType tmp = *(ScienceType *)((char *)p + 0x74);
	m_vec.push_back(tmp);
}
