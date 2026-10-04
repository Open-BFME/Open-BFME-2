// ?erase@Rva00056B72VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-04
// ?erase@Rva00056B72VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-04
// cl: /O1 /MD
// STLport 4.5.3 vector::erase(first,last), reference guide at BFME 1
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 inputs/vendor/stlport/stl/_vector.h.
// Target 00056B72/51 moves [last,end) into first via 00054E23, destroys
// [new_end,end) through rowed 00054ED9, updates end, and returns first.
// These fields and call relationships are target facts. The application
// element identity and the third vector pointer's use are not established here.
struct RvaCopyIteratorTag {};
struct RvaRecordCopyTag : RvaCopyIteratorTag {};
extern "C" void *Rva00054E23CopyDispatch(void *, void *, void *, const RvaCopyIteratorTag &);
extern "C" void Rva00054ED9DestroyRecords(void *, void *);
#pragma comment(linker, "/alternatename:_Rva00054ED9DestroyRecords=??$_Destroy@PAUBfmeStringTailRecord144@@@_STL@@YAXPAUBfmeStringTailRecord144@@0@Z")

struct Rva00056B72VectorView
{
    void *begin;
    void *end;
    void *capacity;
    void *erase(void *first, void *last);
};

// ?Rva00056B72VectorView::erase present-unmatched
void *Rva00056B72VectorView::erase(void *first, void *last)
{
    void *new_end = Rva00054E23CopyDispatch(last, end, first, RvaRecordCopyTag());
    Rva00054ED9DestroyRecords(new_end, end);
    end = new_end;
    return first;
}
