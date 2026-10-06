// cl: /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ??$_Construct@VRva00285BEC@@V1@@_STL@@YAXPAVRva00285BEC@@ABV1@@Z retail 0x0028625D 45B: EH-framed placement copy via rowed copy ctor 0x00285C30. Evidence: same 45B shape as rowed 0x00481514 plus caller 0x00286693 allocating 0x24 and constructing at +0x10.
#include <memory>
class Rva00285BEC
{
public:
	Rva00285BEC(const Rva00285BEC &other);
};
template void _STL::_Construct<Rva00285BEC, Rva00285BEC>(Rva00285BEC *, const Rva00285BEC &);
