// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva004E18A2@@PAV1@@_STL@@YAPAVRva004E18A2@@PAV1@00ABU__false_type@0@@Z 0x0052C2A4 38B evidence: copy stride 0x10 via rowed _Construct 0x0052BD16; callers 0x0052C898 0x00565F4B 0x00565F96; siblings Rva003A6F70UninitCopy Rva003A6360UninitCopy
#include <vector>
class Rva0036CA00Str
{
public:
	Rva0036CA00Str(const Rva0036CA00Str &other);
private:
	int m_00;
};

// ??$__uninitialized_copy@PAVRva004E18A2@@PAV1@@_STL@@YAPAVRva004E18A2@@PAV1@00ABU__false_type@0@@Z 0x0052C2A4 38B evidence: copy stride 0x10 via rowed _Construct 0x0052BD16; callers 0x0052C898 0x00565F4B 0x00565F96; siblings Rva003A6F70UninitCopy Rva003A6360UninitCopy same flags
class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();
	Rva004E18A2(const Rva004E18A2 &other);
private:
	int m_04;
	Rva0036CA00Str m_08;
	unsigned char m_0C;
};

namespace _STL { template <> void _Construct<Rva004E18A2, Rva004E18A2>(Rva004E18A2 *, const Rva004E18A2 &) throw(); }
template Rva004E18A2 *_STL::__uninitialized_copy(Rva004E18A2 *, Rva004E18A2 *, Rva004E18A2 *, const _STL::__false_type &);
