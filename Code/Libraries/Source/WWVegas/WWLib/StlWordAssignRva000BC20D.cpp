// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>

struct Rva000BC20DWords { unsigned words[6];
 // ?Rva000BC20DWords::operator= present-unmatched
 Rva000BC20DWords&operator=(const Rva000BC20DWords&s){words[0]=s.words[0];words[1]=s.words[1];words[2]=s.words[2];words[3]=s.words[3];words[4]=s.words[4];words[5]=s.words[5];return *this;} };
template _STL::vector<Rva000BC20DWords>& _STL::vector<Rva000BC20DWords>::operator=(const _STL::vector<Rva000BC20DWords> &);
// Reference STLport4.5.3; native extent and pointer arithmetic establish
// record width24. Explicit scalar assignment form is target-supported
// for this helper shape; no application record identity or field names inferred.

#pragma comment(linker, "/alternatename:??$_M_allocate_and_copy@PBURva000BC20DWords@@@?$vector@URva000BC20DWords@@V?$allocator@URva000BC20DWords@@@_STL@@@_STL@@IAEPAURva000BC20DWords@@IPBU2@0@Z=??$_M_allocate_and_copy@PBUBfmePod24@@@?$vector@UBfmePod24@@V?$allocator@UBfmePod24@@@_STL@@@_STL@@IAEPAUBfmePod24@@IPBU2@0@Z")

#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBURva000BC20DWords@@PAU1@@_STL@@YAPAURva000BC20DWords@@PBU1@0PAU1@ABU__false_type@0@@Z=??$copy@PAUBfmeStringRecord000B9534@@PAU1@@_STL@@YAPAUBfmeStringRecord000B9534@@PAU1@00@Z")

#pragma comment(linker, "/alternatename:??$__copy_ptrs@PBURva000BC20DWords@@PAU1@@_STL@@YAPAURva000BC20DWords@@PBU1@0PAU1@ABU__false_type@0@@Z=??$copy@PAUBfmeStringRecord000B9534@@PAU1@@_STL@@YAPAUBfmeStringRecord000B9534@@PAU1@00@Z")

#pragma comment(linker, "/alternatename:??$__uninitialized_copy@PBURva000BC20DWords@@PAU1@@_STL@@YAPAURva000BC20DWords@@PBU1@0PAU1@ABU__false_type@0@@Z=??$__uninitialized_copy@PBUBfmePod24@@PAU1@@_STL@@YAPAUBfmePod24@@PBU1@0PAU1@ABU__false_type@0@@Z")
