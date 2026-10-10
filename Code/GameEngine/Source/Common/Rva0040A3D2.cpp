// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Os
// Native40A3D2..40A3F9: pointer-vector search by class/subclass indices.
// Caller5B54ED passes integers, and the complete rowed172B search40A283
// steps four bytes and invokes the two-key predicate40A187 at each element.
// stlport
#include <algorithm>

class CreateAHeroData;
class Rva0040A187
{
public:
	Rva0040A187(int major, int minor) : m_val0(major), m_val4(minor) {}
	bool rva0040A187(const void *arg) const;
	bool operator()(CreateAHeroData *p) const { return rva0040A187(p); }
private:
	int m_val0, m_val4;
};

class Rva0040A3D2
{
public:
	CreateAHeroData *rva0040A3D2(int major, int minor);

private:
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
};

CreateAHeroData *Rva0040A3D2::rva0040A3D2(int major, int minor)
{
	Rva0040A187 predicate(major, minor);
	CreateAHeroData **end = m_end;
	CreateAHeroData **found = _STL::find_if(m_begin, end, predicate);
	return (found == end) ? 0 : *found;
}
