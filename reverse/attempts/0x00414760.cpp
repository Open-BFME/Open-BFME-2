// ?erase@Rva00414760VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-04
// ?erase@Rva00414760VectorView@@QAEPAXPAX0@Z
// partial score=0.980392 date=2026-10-04
// cl: /O1 /MD
// STLport 4.5.3 vector::erase(first,last), reference guide at BFME 1
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 inputs/vendor/stlport/stl/_vector.h.
// Target 00414760/51 moves [last,end) into first via 00414403, destroys
// [new_end,end) through rowed 004144F0, updates end, and returns first.
// These fields and call relationships are target facts. The application
// element identity and the third vector pointer's use are not established here.
struct RvaCopyIteratorTag {};
struct RvaRecordCopyTag : RvaCopyIteratorTag {};
extern "C" void *Rva00414403CopyDispatch(void *, void *, void *, const RvaCopyIteratorTag &);
extern "C" void Rva004144F0DestroyRecords(void *, void *);
#pragma comment(linker, "/alternatename:_Rva004144F0DestroyRecords=??$_Destroy@PAUBfmeAssignRecord44@@@_STL@@YAXPAUBfmeAssignRecord44@@0@Z")

struct Rva00414760VectorView
{
    void *begin;
    void *end;
    void *capacity;
    void *erase(void *first, void *last);
};

// ?Rva00414760VectorView::erase present-unmatched
void *Rva00414760VectorView::erase(void *first, void *last)
{
    void *new_end = Rva00414403CopyDispatch(last, end, first, RvaRecordCopyTag());
    Rva004144F0DestroyRecords(new_end, end);
    end = new_end;
    return first;
}
