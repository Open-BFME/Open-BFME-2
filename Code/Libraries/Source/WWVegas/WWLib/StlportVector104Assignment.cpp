// cl: /O1 /MD
// STLport 4.5.3 vector assignment semantic/control-flow guide: BFME 1
// 1281192f682ce6f29b8f06b7daea4b5e8fdfbb24 inputs/vendor/stlport/stl/_vector.c.
// Native 003F5254/206 proves three pointer fields, stride 104, self guard,
// capacity branch, allocation/copy plus clear, copy/destroy shrinking branch,
// and copy/uninitialized-copy growing branch, then finish=start+source_count.
// Element is an opaque stride-only view; native destruction uses virtual slot0.
// No POD semantics, string offset, or application element name is asserted.
struct RvaCopyIteratorTag {};
struct RvaVector104Tag : RvaCopyIteratorTag {};
struct RvaVector104Element { unsigned char opaque[104]; };
extern "C" void *Rva003B8B44CopyDispatch(void *, void *, void *, const RvaCopyIteratorTag &);
extern "C" void Rva003B8E13DestroyRecords(void *, void *);
extern "C" void *Rva003F417EConstructRecords(const void *, const void *, void *, const RvaCopyIteratorTag &);
#pragma comment(linker, "/alternatename:_Rva003B8E13DestroyRecords=?Rva003B8E13DestroyRange@@YAXPAURva003B8B61Elem@@0@Z")
#pragma comment(linker, "/alternatename:_Rva003F417EConstructRecords=??$__uninitialized_copy@PBUBfmePod104@@PAU1@@_STL@@YAPAUBfmePod104@@PBU1@0PAU1@ABU__false_type@0@@Z")
struct Rva003F5254Vector104
{
    RvaVector104Element *begin, *end, *capacity_end;
    RvaVector104Element *allocateCopy(unsigned, const RvaVector104Element *, const RvaVector104Element *);
    void clearStorage();
    Rva003F5254Vector104 &operator=(const Rva003F5254Vector104 &);
};
#pragma comment(linker, "/alternatename:?allocateCopy@Rva003F5254Vector104@@QAEPAURvaVector104Element@@IPBU2@0@Z=??$_M_allocate_and_copy@PBUBfmePod104@@@?$vector@UBfmePod104@@V?$allocator@UBfmePod104@@@_STL@@@_STL@@IAEPAUBfmePod104@@IPBU2@0@Z")
#pragma comment(linker, "/alternatename:?clearStorage@Rva003F5254Vector104@@QAEXXZ=?_M_clear@?$vector@UBfmeAssignRecord104@@V?$allocator@UBfmeAssignRecord104@@@_STL@@@_STL@@IAEXXZ")

// ?Rva003F5254Vector104::operator= present-unmatched
Rva003F5254Vector104 &Rva003F5254Vector104::operator=(const Rva003F5254Vector104 &x)
{
    if (&x != this) {
        const unsigned xlen = x.end - x.begin;
        if (xlen > unsigned(capacity_end - begin)) {
            RvaVector104Element *tmp = allocateCopy(xlen, x.begin + 0, x.end + 0);
            clearStorage();
            begin = tmp;
            capacity_end = begin + xlen;
        } else if (unsigned(end - begin) >= xlen) {
            void *i = Rva003B8B44CopyDispatch(x.begin + 0, x.end + 0, begin, RvaVector104Tag());
            Rva003B8E13DestroyRecords(i, end);
        } else {
            Rva003B8B44CopyDispatch(x.begin, x.begin + (end - begin), begin, RvaVector104Tag());
            Rva003F417EConstructRecords(x.begin + (end - begin), x.end + 0, end, RvaVector104Tag());
        }
        end = begin + xlen;
    }
    return *this;
}
