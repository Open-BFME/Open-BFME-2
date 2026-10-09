// ??0Rva000AADC1@@QAE@XZ
// partial score=0.99 date=2026-10-10
// ??0Rva000AADC1@@QAE@XZ
// partial score=0.99 date=2026-10-10
// cl: /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// BANK: native AA83B44 and WB constructor; existing dtor AADC1 and BC942C vtable prove neutral owner.
// All44 compiled bytes except vector-base callee agree; pointervector wrapper resolves142E20 but native calls base211E58.
// Full relocated-byte proof still required; no alias or E16 substitution is justified.
#include <vector>
#include <string.h>
class Rva000AADC1Base {public:virtual ~Rva000AADC1Base(){};};
class Rva000AADC1:public Rva000AADC1Base {public:Rva000AADC1()throw();virtual ~Rva000AADC1();
_STL::vector<void*> entries;float matrix[6];};
Rva000AADC1::Rva000AADC1()throw():entries(_STL::allocator<void*>())
{ memset(matrix,0,24); }
