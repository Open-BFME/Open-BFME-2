// ?rva001EBCD8@Rva001EBCD8@@QAEPAXPAX@Z
// partial score=0.92 date=2026-09-29
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/inputs/vendor/stlport
// stlport
//
// Sibling of stlport_list_objectptr_insert.cpp (same /O1 /EHsc /MD STL flags)
// but against pristine vendor STLport: its _algobase.h declares __copy_ptrs
// with a const __false_type& tag (rowed 0x001EBA13 takes the tag address),
// while the bfmealloc shim's copy takes it by value and cannot name that row.
#include <algorithm>

struct BfmeAssignRecord172
{
	char m_data[172];
};

namespace _STL
{
template <>
BfmeAssignRecord172 *__copy_ptrs<BfmeAssignRecord172 *, BfmeAssignRecord172 *>(
	BfmeAssignRecord172 *, BfmeAssignRecord172 *, BfmeAssignRecord172 *, const __false_type &);
}

class Slot0Receiver
{
public:
	virtual void v0(int code);
};

class Rva001EBCD8
{
public:
	void *rva001EBCD8(void *a1);
private:
	char m_pad[4];
	Slot0Receiver *m_ptr;
};

// ?rva001EBCD8@Rva001EBCD8@@QAEPAXPAX@Z retail 0x001EBCD8 62B. Custom
// erase-like method over 172B records: copies [a1+0xAC, m_ptr) down to a1
// through rowed __copy_ptrs 0x001EBA13 (prvalue tag gives the EBP frame),
// backs m_ptr off by one record, fires virtual slot 0 with 0 and returns a1.
// Callers in unclaimed 0x001EC63D/0x001EC859/0x001EC8C0.
void *Rva001EBCD8::rva001EBCD8(void *a1)
{
	_STL::__false_type tag;
	Slot0Receiver *limit = m_ptr;
	if ((BfmeAssignRecord172 *)((char *)a1 + 0xAC) != (BfmeAssignRecord172 *)limit)
		_STL::__copy_ptrs((BfmeAssignRecord172 *)((char *)a1 + 0xAC), (BfmeAssignRecord172 *)limit, (BfmeAssignRecord172 *)a1, tag);
	m_ptr = (Slot0Receiver *)((char *)m_ptr - 172);
	m_ptr->v0(0);
	return a1;
}
