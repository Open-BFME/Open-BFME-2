// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva00373357@Rva00373357@@QAEXXZ @0x00373357 (28B).
// Vector clear-and-free over ScienceType at +0: erase via rowed
// vector erase 0x00532803 then _free 0x00030830 the start when non-null.
// Callers 0x00373422 0x003734D9 unblock 2. Flags from vector owner.
#include <vector>

extern "C" void __cdecl free(void *p);

enum ScienceType
{
	SCIENCE_Dummy0
};

class Rva00373357
{
public:
	void rva00373357();
	void *rva0037341F(bool b);
private:
	_STL::vector<ScienceType> m_vec;
};

// ?rva00373357@Rva00373357@@QAEXXZ
void Rva00373357::rva00373357()
{
	m_vec.erase(m_vec.begin(), m_vec.end());
	ScienceType *p = &*m_vec.begin();
	if (p != 0)
		free(p);
}

void *Rva00373357::rva0037341F(bool b)
{
	rva00373357();
	if (b & 1)
		::operator delete((void *)this);
	return (void *)this;
}
