// cl: /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport remove_copy 0x0054872C 39B plus remove 0x005487D2 46B
// for CreateAHeroData pointers.
// Evidence: remove calls find 0x0020E873 then remove_copy with
// found+1 for the same CreateAHeroData registry;
// remove_copy loop skips value via pointer compare and compacts forward.
#include <vector>
#include <algorithm>
class CreateAHeroData;
template CreateAHeroData **_STL::remove_copy(CreateAHeroData **, CreateAHeroData **, CreateAHeroData **, CreateAHeroData * const &);
template CreateAHeroData **_STL::remove(CreateAHeroData **, CreateAHeroData **, CreateAHeroData * const &);
