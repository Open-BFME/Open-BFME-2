# HLOD against the verified BFME2 base object

Select the scoped RenderObj declaration already proven by its base methods and
vtable. HLOD's previous declaration read Scene at80 instead of78 and used
obsolete virtual indices. All70 previously matched HLOD routines remain exact.
The independently held HLOD copy constructor227 at1A0410 establishes primary
vtable BD6780 and secondary BD677C. Each newly recovered virtual method was
checked against its actual primary-table slot before claiming bytes.

The first11 routines cover2066 executable bytes: bounding sphere237, maximum
screen size102, box intersection176, object-space sphere130, polygon count185,
scene addition126, scene removal134, LOD increment203, decrement203, selection238,
and subobject removal332. The complete final returns were checked; several
catalog entries stop9-16 bytes early and are not used as proof of size.

Assignment is947 bytes through1A0302, not the catalog's940. Its code shape now
matches but requires independently reconstructed Free and Animatable assignment
callees before it can be claimed. The object-space box also needs the orthogonal
inverse and matrix-multiply dependency closure. These are not included in the
initial2066-byte recovery.

## Global array destruction

`HLodClass::Free` is 445 executable bytes at 19C230 followed by 3 alignment bytes.
The retail vector destructor receives flag 2, returns the allocation pointer, and
the caller invokes global operator delete[]. The source therefore uses explicit
`::delete[] Lod` rather than an unqualified delete expression (flag 3 and an
internal deallocation). This ordinary C++ ownership distinction recovers the
complete body and preserves all 81 previously matched routines. All four direct
relocations target the independently held global array deallocator 42FD80.
