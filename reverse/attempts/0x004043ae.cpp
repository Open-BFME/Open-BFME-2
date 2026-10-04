// ?erase@?$vector@VRva00403927@@V?$allocator@VRva00403927@@@_STL@@@_STL@@QAEPAVRva00403927@@PAV3@0@Z
// partial score=0.96 date=2026-10-04
// cl: /O1
// stlport
//
// ?erase@?$vector@VRva00403927@@V?$allocator@VRva00403927@@@_STL@@@_STL@@QAEPAVRva00403927@@PAV3@0@Z @0x004043AE 51B
// Range erase over vector<Rva00403927> (stride 0x14 element: two ints + vector<AsciiString> at +8,
// layout owner Rva00403927Assign.cpp). Shifts the tail down with __copy_ptrs then destroys
// the vacated tail with _Destroy, stores the new finish and returns first. Evidence: retail
// 51B EBP frame with tag at [ebp+0xb], 4-push copy + 2-push destroy shape, callees rowed
// copy 0x00403BD2 (29B wrapper via rowed __copy 0x004039E0) and destroy_aux 0x00214B09 (25B
// loop via rowed dtor 0x00214ADC); caller 0x0040450E passes [esi],[esi+4]; same 51B shape as
// BfmeAssignRecord32 erase 0x00173FB6 and BfmeStringRecord005DDD40 erase 0x00381B1F.
class Rva00403927
{
	char m_pad[20];

public:
	Rva00403927(const Rva00403927 &that);
	~Rva00403927();
	Rva00403927 &operator=(const Rva00403927 &that);
};

namespace _STL
{

struct __false_type
{
	__false_type()
	{
	}
};

struct random_access_iterator_tag
{
};

template <class Type>
class allocator
{
};

template <class Type, class Allocator>
class vector
{
public:
	typedef Type *iterator;
	iterator erase(iterator first, iterator last);

private:
	iterator m_start;
	iterator m_finish;
	iterator m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);

}

// ?erase@?$vector@VRva00403927@@V?$allocator@VRva00403927@@@_STL@@@_STL@@QAEPAVRva00403927@@PAV3@0@Z present-unmatched
inline _STL::vector<Rva00403927, _STL::allocator<Rva00403927> >::iterator
_STL::vector<Rva00403927, _STL::allocator<Rva00403927> >::erase(iterator first, iterator last)
{
	_STL::__false_type tag;
	iterator result = _STL::__copy_ptrs(last, m_finish, first, tag);
	_STL::_Destroy(result, m_finish);
	m_finish = result;
	return first;
}

#pragma inline_depth(0)
// ?bfmeEmitStlportVectorRva00403927Erase@@YAXPAV?$vector@VRva00403927@@V?$allocator@VRva00403927@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitStlportVectorRva00403927Erase(_STL::vector<Rva00403927, _STL::allocator<Rva00403927> > *vec)
{
	vec->erase(0, 0);
}
#pragma inline_depth()
