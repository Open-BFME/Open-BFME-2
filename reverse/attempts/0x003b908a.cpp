// ?erase@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord104@@PAU3@0@Z
// partial score=0.98 date=2026-10-04
// cl: /O1
// stlport
//
// ?erase@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@QAEPAUBfmeAssignRecord104@@PAU3@0@Z
// @ 0x003B908A (51B): range erase over vector<BfmeAssignRecord104>. Shifts
// the tail down with rowed CopyDispatch 0x003B8B44 then destroys the vacated
// tail with rowed Destroy 0x003B8E13, stores the new finish and returns first.
// Follows BfmeAssignRecord32 erase (0x00173FB6 51B) and BfmeAssignRecord172 erase
// (0x001EBDFA 51B): prvalue tag forces the EBP frame with tag at [ebp+0xb].
struct BfmeAssignRecord104 {
	~BfmeAssignRecord104();
	unsigned char m_pad[104];
};

struct RvaCopyIteratorTag {};
struct RvaVector104Tag : RvaCopyIteratorTag {};

extern "C" BfmeAssignRecord104 *Rva003B8B44CopyDispatch(BfmeAssignRecord104 *first, BfmeAssignRecord104 *last, BfmeAssignRecord104 *result, const RvaCopyIteratorTag &tag);
extern "C" void Rva003B8E13DestroyRecords(BfmeAssignRecord104 *, BfmeAssignRecord104 *);
#pragma comment(linker, "/alternatename:_Rva003B8E13DestroyRecords=?Rva003B8E13DestroyRange@@YAXPAURva003B8B61Elem@@0@Z")

namespace _STL {

template <class Type>
class allocator {
};

template <class Type, class Allocator>
class vector {
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);
private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

}

_STL::vector<BfmeAssignRecord104, _STL::allocator<BfmeAssignRecord104> >::iterator
_STL::vector<BfmeAssignRecord104, _STL::allocator<BfmeAssignRecord104> >::erase(iterator first, iterator last)
{
	iterator result = Rva003B8B44CopyDispatch(last, m_finish, first, RvaVector104Tag());
	Rva003B8E13DestroyRecords(result, m_finish);
	m_finish = result;
	return first;
}
