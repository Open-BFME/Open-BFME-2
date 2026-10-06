// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0025753F@@QAE@XZ @0x0025753F 5B
// Novtable empty dtor tail-jumping to the rowed base tree dtor at 0x0025742C.
// Evidence: 5B jmp; callers are Unwind funclets; base via OwnedRecord900.h.
#include "OwnedRecord900.h"
struct __declspec(novtable) Rva0025753F : public BfmeStringRecordTree900
{
	~Rva0025753F();
};
Rva0025753F::~Rva0025753F()
{
}
