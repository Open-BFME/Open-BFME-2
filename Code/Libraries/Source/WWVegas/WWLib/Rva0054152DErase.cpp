// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O1 /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?erase@?$vector@URva0054107FRecord@@V?$allocator@URva0054107FRecord@@@_STL@@@_STL@@QAEPAURva0054107FRecord@@PAU3@0@Z retail 0x0054152D 38 bytes. Dedicated TU.
//
// STLport vector range erase for 28-byte Rva0054107FRecord with trivial destroy.
// Calls the rowed 29B copy wrapper at 0x00541214 which is an ICF fold of copy
// and __copy_ptrs for this element. Caller 0x0054226A clears then reserves.
// Sibling 0x00541553 is the same shape for another element.
#define _STLP_NO_EXCEPTIONS
#include <vector>
struct Rva0054107FRecord { Rva0054107FRecord(); Rva0054107FRecord(const Rva0054107FRecord&); Rva0054107FRecord&operator=(const Rva0054107FRecord&); private: char bytes[28]; };
typedef _STL::vector<Rva0054107FRecord, _STL::allocator<Rva0054107FRecord> > Rva0054152DVec;
// ?eraseRva0054152DRange present-unmatched
Rva0054107FRecord *eraseRva0054152DRange(Rva0054152DVec *vec, Rva0054107FRecord *first, Rva0054107FRecord *last)
{
	return vec->erase(first, last);
}
