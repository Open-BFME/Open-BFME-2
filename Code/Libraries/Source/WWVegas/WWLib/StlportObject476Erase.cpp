// flags: region default (reverse/retail_inventory/flag_regions.csv)
// stlport
// ?erase@?$vector@UBfmeObject476@@V?$allocator@UBfmeObject476@@@_STL@@@_STL@@QAEPAUBfmeObject476@@PAU3@0@Z @0x001FEFB9 51B: range erase over vector<BfmeObject476>. Shifts tail down with rowed __copy_ptrs 0x001FEF62 then destroys vacated tail with rowed _Destroy 0x001FD6A4 stores new finish returns first. Evidence: retail 51B push-ebp frame plus lea-tag at ebp+b plus copy then destroy shape calling rowed copy_ptrs and Destroy; callers 0x001FF21D 0x001FF26B; sibling BfmeAssignRecord172 erase 0x001EBDFA 51B prvalue false_type tag shape.
struct BfmeObject476
{
    virtual ~BfmeObject476();
    unsigned char opaque[472];
    BfmeObject476();
    BfmeObject476(const BfmeObject476 &);
};
namespace _STL
{
struct __false_type
{
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
    iterator _M_start;
    iterator _M_finish;
    iterator _M_endOfStorage;
};
template <class InputIter, class OutputIter, class Distance>
OutputIter __copy(InputIter first, InputIter last, OutputIter result, const random_access_iterator_tag &tag, Distance *extra);
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag)
{
    __false_type local;
    return __copy(first, last, result, reinterpret_cast<const random_access_iterator_tag &>(local), (int *)0);
}
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}
_STL::vector<BfmeObject476, _STL::allocator<BfmeObject476> >::iterator _STL::vector<BfmeObject476, _STL::allocator<BfmeObject476> >::erase(iterator first, iterator last)
{
    iterator result = _STL::__copy_ptrs(last, _M_finish, first, _STL::__false_type());
    _STL::_Destroy(result, _M_finish);
    _M_finish = result;
    return first;
}
