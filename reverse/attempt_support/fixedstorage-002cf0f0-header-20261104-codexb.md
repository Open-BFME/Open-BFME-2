# Fixed-storage header cohort, 2026-11-04

Inspected revision: `03e6ba9ac6ba3d7e27fc12637d271aa6fa4cec0e`.
Scope: the two queued consumers of
`Code/GameEngine/Include/Common/BfmeFixedStorage002CF0F0.h`.

## Accepted copy consumer

`Rva0021E85ACopy.cpp` never accesses its private storage's `int m_00`.
Replacing that declaration with the canonical header retains the four-byte
member and the existing nothrow copy-constructor binding. The automatic
rewriter conservatively refuses the `int` to `char[4]` field mapping; no field
rewrite is needed here because the only operation is member copy construction.

Verification:

- `./build.sh Code/GameEngine/Source/Common/Rva0021E85ACopy.cpp`: 5/5 exact;
  string, float and import checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- `header_adopt_lane.py accept --class BfmeFixedStorage002CF0F0` for this source:
  PASS; retired its single queue row through the owning tool.
- Ordinary `link_check.py` on the current object: LINKS, 283 -> 283 linked bytes;
  census baseline 2026-11-04 07:28 at `a62ac1c10b`. This is a preview preserving
  existing linking, not a new census or headline gain.

## Remaining constructor consumer

`Rva005E5A38Ctor.cpp` constructs its by-value argument through the existing
`Rva005E5A24Init` helper before calling `Rva005CBA04`. Its private default
constructor performs that initialization; the canonical default constructor
is empty. Automatic adoption therefore fails the 46-byte row at `0x005E5A38`.

A local inline factory was also tried: default-construct canonical storage,
call `Rva005E5A24Init((BitFlags<11> *)&storage)`, return storage by value, and
pass the result to the base constructor. The compiled body introduces another
copy-constructor call and saves EDI; it does not match retail. Retail begins
`55 8b ec 51 56 51 8b c4`, while this trial begins
`55 8b ec 51 56 57 51 8d 45 fc`. The trial was reverted; the original source
again passes 1/1 and the declared-unmatched check.

The remaining queue row is retained. Before retrying, establish an appropriate
shared initialization interface or recover the actual mask type and its
constructor contract; changing the shared empty default constructor for this
consumer alone is not justified. No shared header, row, pin, alias or compiler
flag changed in this cohort.
