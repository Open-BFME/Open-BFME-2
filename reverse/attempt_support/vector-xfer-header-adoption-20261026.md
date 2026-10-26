# Vector transfer canonical Xfer adoption

Inspected upstream `6a57c22ccc`, BFME 1 reference `f633d0e97a`.
The default header queue selected `Rva003F2394Xfer.cpp`.

| Source in Common/System | Verified rows | Bytes | Ordinary link preview | Queue rows retired |
| --- | ---: | ---: | --- | ---: |
| Rva003F2394Xfer.cpp | 1 | 204 | 204 -> 204 | 1 |

Each listed source was read in full and passes the frozen-file checker.
The private Xfer class is replaced by the registered `BfmeXfer.h`. A local
`XferVectorTypes.h` supplies operand declarations before that include, including
when the TU composer hoists headers. No shared canonical header, ledger, pin,
string, vector layout, element helper or exception declaration is changed.

The two-byte `{1,1}` version buffer is passed as `Xfer::Version &` at slot
0x28. The existing string-pointer operand uses the canonical opaque slot-0x2C
type; the chained unsigned count still uses slot 0x78. `IsStoring() const`
retains the mode call at slot 0x08. No layout for either opaque operand is
invented.

An initial named string-pointer local grew the frame from 0x0C to 0x10 and
shifted the exception scratch storage. The final inline operand conversion
preserves the original temporary's full-expression lifetime and stack reuse;
all 204 bytes then match again. It is declared once in the local include,
avoiding duplicate helper definitions if consumers are composed later.

Normal `build.sh`, before/after `find_declared_unmatched.py`, and the owning
`header_adopt_lane.py accept --class Xfer` pass. Before/after ordinary link
previews use index `f995f30157` (2026-10-25 21:36 UTC). These already-linked
bytes are retained; the result is header-queue retirement, not new matched
or census-linked bytes. No complete-image or runtime result is claimed.
