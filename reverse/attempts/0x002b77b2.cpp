// ?rva002B77B2@LivingWorldLogic@@QAEIXZ
// partial score=0.88 date=2026-10-09
// cl: /O1 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <set>
class LivingWorldLogic { public: void rva002B693F(void*); unsigned int rva002B77B2(); };
unsigned int LivingWorldLogic::rva002B77B2() { _STL::set<int> keys; rva002B693F(&keys); return keys.size(); }
