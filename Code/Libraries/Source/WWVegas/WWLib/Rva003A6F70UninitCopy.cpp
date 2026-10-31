// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /ICode/GameEngine/Source /Ireference/shims/moduledata /Ireference/shims/bfmealloc
// stlport
// ??$__uninitialized_copy@PAVRva003A6F70@@PAV1@@_STL@@YAPAVRva003A6F70@@PAV1@00ABU__false_type@0@@Z 0x0052C27E 38B evidence: copy stride 0x20 via rowed _Construct 0x0052BD04; callers 0x0052C854 0x00565DE0 0x00565E2B; sibling Rva00564C58FillN same record
#include <vector>
// ??$__uninitialized_copy@PAVRva003A6F70@@PAV1@@_STL@@YAPAVRva003A6F70@@PAV1@00ABU__false_type@0@@Z 0x0052C27E 38B evidence: copy stride 0x20 via rowed _Construct 0x0052BD04; callers 0x0052C854 0x00565DE0 0x00565E2B; sibling Rva00564C58FillN same record same flags
class Rva003A6F70
{
public:
	virtual void dummy();
	int m_04, m_08, m_0C, m_10, m_14, m_18;
	char m_1C;
	Rva003A6F70(const Rva003A6F70 &other);
};

namespace _STL { template <> void _Construct<Rva003A6F70, Rva003A6F70>(Rva003A6F70 *, const Rva003A6F70 &) throw(); }
template Rva003A6F70 *_STL::__uninitialized_copy(Rva003A6F70 *, Rva003A6F70 *, Rva003A6F70 *, const _STL::__false_type &);
