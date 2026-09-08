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

Assignment now matches all947 bytes through1A0302 after the independently
reconstructed445-byte Free and261-byte Animatable assignment dependencies.
The catalog's940-byte extent stops inside the epilogue. The orthogonal inverse
also matches211 bytes in its scoped SSE unit; object-space box still requires
the separately unresolved matrix multiply. The final rendering chain is detailed
in animation-frame-modes.md.

## Global array destruction

`HLodClass::Free` is 445 executable bytes at 19C230 followed by 3 alignment bytes.
The retail vector destructor receives flag 2, returns the allocation pointer, and
the caller invokes global operator delete[]. The source therefore uses explicit
`::delete[] Lod` rather than an unqualified delete expression (flag 3 and an
internal deallocation). This ordinary C++ ownership distinction recovers the
complete body and preserves all 81 previously matched routines. All four direct
relocations target the independently held global array deallocator 42FD80.
