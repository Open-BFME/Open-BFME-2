// ?erase@Rva00312C44VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-05
// cl: /O1 /MD
// STLport 4.5.3 vector::erase(first,last) for the BfmeStringHeadRecord184
// vector, recovered at retail 0x00312C44 (51 bytes).
//
// Target facts, all read off retail's own bytes: 0x00312C44 pushes the address
// of a local empty iterator tag, then first, then this->_M_finish, then last,
// then calls the copy dispatch 0x003120FB and keeps the returned pointer in
// EDI; it then calls the rowed range dtor 0x0008B632 with (new_finish,
// this->_M_finish), stores the returned pointer into this->_M_finish, and
// returns first. The call relationships and the three-vector layout are target
// facts. Element identity is established independently by the stride-184
// evidence in StlportRecordRangeCopyDispatch.cpp; no application class name is
// asserted.
//
// The tag is spelled as the DERIVED empty type RvaRecordCopyTag rather than the
// STLport base: a temporary of the base, which has no members, makes MSVC7
// materialise a zero byte in the frame (xor eax,eax / stosb) and the body grows
// to 58 bytes. The derived type contributes no members either, so the callee
// still receives an empty tag and its already-resolved dispatch is unaffected.
struct RvaCopyIteratorTag {};
struct RvaRecordCopyTag : RvaCopyIteratorTag {};
extern "C" void *Rva003120FBCopyDispatch(void *, void *, void *, const RvaCopyIteratorTag &);
extern "C" void Rva0008B632DestroyRecords(void *, void *);
#pragma comment(linker, "/alternatename:_Rva0008B632DestroyRecords=??$_Destroy@PAUBfmeStringHeadRecord184@@@_STL@@YAXPAUBfmeStringHeadRecord184@@0@Z")

struct Rva00312C44VectorView
{
    void *begin;
    void *end;
    void *capacity;
    void *erase(void *first, void *last);
};

// ?erase@Rva00312C44VectorView@@QAEPAXPAX0@Z @0x00312C44 51B
void *Rva00312C44VectorView::erase(void *first, void *last)
{
    void *new_end = Rva003120FBCopyDispatch(last, end, first, RvaRecordCopyTag());
    Rva0008B632DestroyRecords(new_end, end);
    end = new_end;
    return first;
}
