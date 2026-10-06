// cl: /Ireference/shims/bfme2_ascii /Oy- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?EraseRange@Rva005EDA8AVector@@QAEPAUBfmeStringRecord005ED5F3@@PAU2@0@Z @0x005EDA8A 51B: range erase over 20-byte BfmeStringRecord005ED5F3 copying [last finish) to first via rowed __copy_ptrs 0x005ED869 destroying tail via rowed _Destroy 0x005EDA14 storing new finish returning first. Evidence: same 51B shape as rowed erase siblings Rva0015229C Rva002983DA; callees rowed; caller 0x005EE09A.
struct BfmeStringRecord005ED5F3;
namespace _STL {
struct __false_type {};
template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);
template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}
class Rva005EDA8AVector {
public:
    struct BfmeStringRecord005ED5F3 *EraseRange(struct BfmeStringRecord005ED5F3 *first, struct BfmeStringRecord005ED5F3 *last);
private:
    void *m_start;
    struct BfmeStringRecord005ED5F3 *m_finish;
    void *m_end;
};
struct BfmeStringRecord005ED5F3 *Rva005EDA8AVector::EraseRange(struct BfmeStringRecord005ED5F3 *first, struct BfmeStringRecord005ED5F3 *last)
{
    struct BfmeStringRecord005ED5F3 *newFinish = _STL::__copy_ptrs(last, m_finish, first, *(const _STL::__false_type *)((const char *)&first + 3));
    _STL::_Destroy(newFinish, m_finish);
    m_finish = newFinish;
    return first;
}
