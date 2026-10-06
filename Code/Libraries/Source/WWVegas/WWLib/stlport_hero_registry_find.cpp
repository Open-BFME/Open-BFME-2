// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 pointer search used by the CreateAHeroData registry.
// The verified CreateAHeroData copy calls 21D517 with its this pointer.
// Register21D517 and unregister21A624 search vector VA DFE358 through
// find20E873, which dispatches to this complete103-byte loop at5250A5.
#include <vector>
#include <algorithm>
class CreateAHeroData;
template CreateAHeroData** _STL::__find(CreateAHeroData**,CreateAHeroData**,CreateAHeroData* const&,const _STL::random_access_iterator_tag&);
template CreateAHeroData** _STL::find(CreateAHeroData**,CreateAHeroData**,CreateAHeroData* const&);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??$find@PAW4ScienceType@@W41@@_STL@@YAPAW4ScienceType@@PAW41@0ABW41@@Z=??$find@PAPAVCreateAHeroData@@PAV1@@_STL@@YAPAPAVCreateAHeroData@@PAPAV1@0ABQAV1@@Z")
