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
