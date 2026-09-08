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
