// cl: /O1 /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 tree copy and cleanup for the target record at 0x2CF550.
#include "OwnedRecord900.h"
template BfmeStringRecordTree900::~_Rb_tree();
template void BfmeStringRecordTree900::clear();
template void BfmeStringRecordTree900::_M_erase(BfmeStringRecordTree900::_Link_type);
