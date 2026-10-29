// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport46
//
// STLport 4.5.3 vector<T>::clear() for element types whose range erase is
// already matched in WWLib/StlportVectorEraseRangeFamily.cpp. clear() is
// erase(begin(), end()), eleven bytes with the erase called out of line:
//
//   push [ecx+4] (_M_finish) / push [ecx] (_M_start) / call erase / ret
//
// The vector view here only declares erase, so this unit emits the clears
// and never a second copy of the erase bodies. Element types are that
// family's code-generation views (incomplete; no layout claimed); the class
// key matches the erase row of the same vector.

namespace _STL
{

template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc = allocator<_Tp> >
class vector
{
public:
	typedef _Tp *iterator;
	iterator erase(iterator __first, iterator __last);
	void clear() { erase(_M_start, _M_finish); }

protected:
	_Tp *_M_start;
	_Tp *_M_finish;
	_Tp *_M_end_of_storage;
};

}

class RvaSmartPtr12;
struct Rva00079EA1Element;
struct Rva000C1CAEElement;
struct Rva00079554Record;
struct Rva000BEDF0Record;
class Rva00151DAB;
class BfmeStringTailRecord156;
struct Rva00213949Element;
struct OpaqueRefElement4;
struct Rva002DCFEEElement;
struct Rva002E2690Element;
struct Elem003AF9E0;
class Rva0032A3A9Element;
class Rva003371B1;
struct Rva003F610FElement;
struct Rva004043AEElement;
struct Rva0040538FElement;
struct Rva0040DC56Element;
struct Rva00520211Element;
struct Rva00566A42Element;
struct Rva005DC408Element;
struct Rva005F8620Element;

template void _STL::vector<RvaSmartPtr12 >::clear();
template void _STL::vector<Rva00079EA1Element >::clear();
template void _STL::vector<Rva000C1CAEElement >::clear();
template void _STL::vector<Rva00079554Record >::clear();
template void _STL::vector<Rva000BEDF0Record >::clear();
template void _STL::vector<Rva00151DAB >::clear();
template void _STL::vector<BfmeStringTailRecord156 >::clear();
template void _STL::vector<Rva00213949Element >::clear();
template void _STL::vector<OpaqueRefElement4 >::clear();
template void _STL::vector<Rva002DCFEEElement >::clear();
template void _STL::vector<Rva002E2690Element >::clear();
template void _STL::vector<Elem003AF9E0 >::clear();
template void _STL::vector<Rva0032A3A9Element >::clear();
template void _STL::vector<Rva003371B1 >::clear();
template void _STL::vector<Rva003F610FElement >::clear();
template void _STL::vector<Rva004043AEElement >::clear();
template void _STL::vector<Rva0040538FElement >::clear();
template void _STL::vector<Rva0040DC56Element >::clear();
template void _STL::vector<Rva00520211Element >::clear();
template void _STL::vector<Rva00566A42Element >::clear();
template void _STL::vector<Rva005DC408Element >::clear();
template void _STL::vector<Rva005F8620Element >::clear();
