// cl: /O1 /MD
// STLport 4.5.3 non-trivial pointer-copy dispatch, guided by the existing
// BFME 1 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 algorithm header.
// Target facts: 003120FB/29 forwards first,last,result to rowed 00311602/54
// with a local empty iterator tag and null distance pointer. Its unused
// fourth argument is the tag address pushed by erase at 00312C44.
// Record identity is unknown; the worker independently proves stride 184.
// No application class or complete element layout is claimed here.
struct RvaCopyIteratorTag {};
extern "C" void *Rva00311602CopyRecords(void *first, void *last, void *result,
    const RvaCopyIteratorTag &tag, int *distance);
#pragma comment(linker, "/alternatename:_Rva00311602CopyRecords=??$__copy@PAUBfmeStringHeadRecord184@@PAU1@H@_STL@@YAPAUBfmeStringHeadRecord184@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z")

// ?Rva003120FBCopyDispatch present-unmatched
extern "C" void *Rva003120FBCopyDispatch(void *first, void *last, void *result,
    const RvaCopyIteratorTag &)
{
    RvaCopyIteratorTag tag;
    return Rva00311602CopyRecords(first, last, result, tag, 0);
}

// Native 00054E23/29 has the same dispatch ABI; worker 00053F6E is already
// rowed and independently proves stride 144. No element layout is inferred.
extern "C" void *Rva00053F6ECopyRecords(void *, void *, void *,
    const RvaCopyIteratorTag &, int *);
#pragma comment(linker, "/alternatename:_Rva00053F6ECopyRecords=??$__copy@PAUBfmeStringTailRecord144@@PAU1@H@_STL@@YAPAUBfmeStringTailRecord144@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z")

// ?Rva00054E23CopyDispatch present-unmatched
extern "C" void *Rva00054E23CopyDispatch(void *first, void *last, void *result,
    const RvaCopyIteratorTag &)
{
    RvaCopyIteratorTag tag;
    return Rva00053F6ECopyRecords(first, last, result, tag, 0);
}

// Native 00414403/29 has the same dispatch ABI; worker 004143A4 is already
// rowed and independently proves stride 44. No element layout is inferred.
extern "C" void *Rva004143A4CopyRecords(void *, void *, void *,
    const RvaCopyIteratorTag &, int *);
#pragma comment(linker, "/alternatename:_Rva004143A4CopyRecords=??$__copy@PAUBfmeAssignRecord44@@PAU1@H@_STL@@YAPAUBfmeAssignRecord44@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z")

// ?Rva00414403CopyDispatch present-unmatched
extern "C" void *Rva00414403CopyDispatch(void *first, void *last, void *result,
    const RvaCopyIteratorTag &)
{
    RvaCopyIteratorTag tag;
    return Rva004143A4CopyRecords(first, last, result, tag, 0);
}

// Native 003B8B44/29 has the same dispatch ABI; worker 003F421D is already
// rowed and independently proves stride 104. No element layout is inferred.
extern "C" void *Rva003F421DCopyRecords(void *, void *, void *,
    const RvaCopyIteratorTag &, int *);
#pragma comment(linker, "/alternatename:_Rva003F421DCopyRecords=??$__copy@PAUBfmeAssignRecord104@@PAU1@H@_STL@@YAPAUBfmeAssignRecord104@@PAU1@00ABUrandom_access_iterator_tag@0@PAH@Z")

// ?Rva003B8B44CopyDispatch present-unmatched
extern "C" void *Rva003B8B44CopyDispatch(void *first, void *last, void *result,
    const RvaCopyIteratorTag &)
{
    RvaCopyIteratorTag tag;
    return Rva003F421DCopyRecords(first, last, result, tag, 0);
}
