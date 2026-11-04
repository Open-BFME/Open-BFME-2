# Video state views, 2026-11-04

Inspected revision: `a9286edec5`; owner: `yasinschroeder-codex3`.
Scope: the six private `Rva000724AE` views among W3DVideoBuffer.cpp's
approved donors. No source paths, ledger rows, aliases, flags or debt keys move.

## Target facts and reconstruction

The existing row at 0x000725BC writes dimensions at +0/+4, owns resource
pointers at +8/+0xC and reads/writes flags at +0x10. The row at 0x00072566
iterates a one-element array with a 0x14-byte stride; the constructor at
0x000726B0 builds the state at +0x2C before the pointers at +0x40/+0x44.
These target facts support a 0x14-byte state. They do not recover its name.

The constructor's opaque view and the clear routine's embedded views stopped
at 0x10. Correct those extents, represent the shared storage as two integers,
two pointers and the flags word, and cast to the existing resource views only
at calls. This removes the incompatible partition of +0..+8 as either one
embedded object or two integers. The clear routine still leaves flags alone.
Resolve the allocator's ambiguous `surface`/`texture` field references explicitly
before the tool performs its token-based reconciliation.

`tu_views.py .../W3DVideoBuffer.cpp --class Rva000724AE --no-merge-check`
then applied one declaration to all six files and verified the compiler layouts,
bytes, declaration coverage and external symbols. [Tool receipt](views.json).
The tool retains the seed's signed integer spelling for the two dimension
words; this does not establish original signedness or original member names.

## Verification

`./build.sh` on Clear, Check, Lock, Allocate, CtorBfme and StateAllocate:
**17/17 matched**. Four renumbered funclet labels were verified through their
parents' EH data. String, float and import checks passed.
`find_declared_unmatched.py` on the same six files: all definitions matched.
`check_csv.py`: OK (99,443 function rows, 9,334 symbol rows, 2,268 data rows).
`git diff --check`: clean.

Before editing, each file was byte-verified and its ordinary build object's
`tu_views.coff_externals` set saved. After reconciliation every external
definition/reference tuple was identical. Counts and SHA-256 of sorted JSON
tuples (default `json.dumps` formatting) were identical before and after:

| File | Tuples | SHA-256 |
| --- | ---: | --- |
| W3DVideoBufferCtorBfme.cpp | 50 | fca4d23894f0072241a767fbefade8022231bc83b275c7d50329c9d92b2d7e61 |
| Rva000724AEClear.cpp | 4 | 7f4db7771d0656c0f7b37f0f29eb0339268bfe708f4fc487c7fac9c91da9f432 |
| Rva000724C7Check.cpp | 2 | 77aceb9f7e086de95a90b33015016df9bc9099ca419db647abc0804aedc758f4 |
| Rva000724D7Lock.cpp | 4 | 5fe3a25dbe40774bdf69f3bbd0baef385914825c35eff53f26f7bb57cc3eda34 |
| W3DVideoStateAllocate.cpp | 12 | 1d72f9983d8a897e0aafa096c87a0e642cdea2a27c91dc037f0b105b0b6f5b99 |
| W3DVideoBufferAllocate.cpp | 11 | 22d3742c250e3dfbbaae303503c642439f0c9450017398d1bb2744b58b50e86b |

## Remaining prerequisites

[Link preview](link-preview.log), using the index's 2026-11-04 07:28 census
at `a62ac1c10b`, retains five clean units (576 authored bytes). The constructor
reports duplicate `??1W3DVideoBuffer@@UAE@XZ`, also seen before this edit.
Its external symbol set is unchanged. This preview is not a new census and
does not establish a linking gain or loss caused by this change.

The [merge dry run](merge-preview.log) still accepts **0/12** donors. The
carried empty flag override loses rows in Cleanup, Allocate, CtorBfme and
StateAllocate. Other candidates have no baseline match or fail the lifetime
provider guard. The seed also needs MilesAudioManager header adoption.
No merge was applied. Rva00739C70's by-value resource dependencies and the
VideoBuffer/W3DVideoBuffer base/virtual-slot disagreements remain separate
prerequisites. Resolve the existing destructor owners and duplicate provider
contract before retrying the merge; the Rva000724AE size/partition conflict is
now reconciled. No headline change or census confirmation is claimed.
