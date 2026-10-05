// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>

struct Rva00540295Words { unsigned words[10];
 // ?Rva00540295Words::operator= present-unmatched
 Rva00540295Words&operator=(const Rva00540295Words&s){words[0]=s.words[0];words[1]=s.words[1];words[2]=s.words[2];words[3]=s.words[3];words[4]=s.words[4];words[5]=s.words[5];words[6]=s.words[6];words[7]=s.words[7];words[8]=s.words[8];words[9]=s.words[9];return *this;} };
template _STL::vector<Rva00540295Words>::vector(const _STL::vector<Rva00540295Words> &);
// Reference STLport4.5.3; native extent and pointer arithmetic establish
// record width40. Explicit scalar assignment form is target-supported
// for this helper shape; no application record identity or field names inferred.

#pragma comment(linker, "/alternatename:?get_allocator@?$vector@URva00540295Words@@V?$allocator@URva00540295Words@@@_STL@@@_STL@@QBE?AV?$allocator@URva00540295Words@@@2@XZ=?get_allocator@?$vector@VAsciiString@@V?$allocator@VAsciiString@@@_STL@@@_STL@@QBE?AV?$allocator@VAsciiString@@@2@XZ")

#pragma comment(linker, "/alternatename:??0?$_Vector_base@URva00540295Words@@V?$allocator@URva00540295Words@@@_STL@@@_STL@@QAE@IABV?$allocator@URva00540295Words@@@1@@Z=??0?$_Vector_base@UBfmePod40@@V?$allocator@UBfmePod40@@@_STL@@@_STL@@QAE@IABV?$allocator@UBfmePod40@@@1@@Z")

#pragma comment(linker, "/alternatename:??$__uninitialized_copy@PBURva00540295Words@@PAU1@@_STL@@YAPAURva00540295Words@@PBU1@0PAU1@ABU__false_type@0@@Z=??$__uninitialized_copy@PBVRva0054000B@@PAV1@@_STL@@YAPAVRva0054000B@@PBV1@0PAV1@ABU__false_type@0@@Z")
