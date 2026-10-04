// ?erase@Rva00312C44VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-04
// cl: /O1 /MD
// STLport 4.5.3 vector::erase(first,last), reference guide at BFME 1
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 inputs/vendor/stlport/stl/_vector.h.
// Target 00312C44/51 moves [last,end) into first via 003120FB, destroys
// [new_end,end) through rowed 0008B632, updates end, and returns first.
// These fields and call relationships are target facts. The application
// element identity and the third vector pointer's use are not established here.
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

// ?Rva00312C44VectorView::erase present-unmatched
void *Rva00312C44VectorView::erase(void *first, void *last)
{
    void *new_end = Rva003120FBCopyDispatch(last, end, first, RvaRecordCopyTag());
    Rva0008B632DestroyRecords(new_end, end);
    end = new_end;
    return first;
}
