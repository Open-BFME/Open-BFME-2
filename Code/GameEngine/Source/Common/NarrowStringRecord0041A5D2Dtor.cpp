// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??1BfmeNarrowRecord0041A5D2@@QAE@XZ @0x0041A200, 65B: dtor of the
// two-string record (text0 +0, text1 +0x10) whose default ctor 0x0041A1CF
// and copy assign 0x0041A7F7 are rowed in NarrowStringRecordCopyBFME2.cpp.
// Retail frees both string buffers with EH states around the extern "C"
// _free calls, so this TU uses /EHs (the /EHsc sibling drops those states).
// Callers: 0x0041A241/0x0041A3C4/0x0041A486/0x0041A843/0x0041A96D.
#include <memory>
#include <string>
#include "BfmeNarrowRecord0041A5D2.h"
BfmeNarrowRecord0041A5D2::~BfmeNarrowRecord0041A5D2() {}
