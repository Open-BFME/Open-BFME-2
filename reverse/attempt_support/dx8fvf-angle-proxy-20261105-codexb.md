# dx8fvf AngleFXInfo allocation-proxy prerequisite

Inspected revision: `73b351a370`, 2026-11-05. Claims cover dx8fvf.cpp and
its three candidate donors. The scoped consolidation planner's current report
records original-path evidence, mixed routing, private declarations and compiler
settings as prerequisites; it supplies no new TU approval.

The initial `tu_skeleton.py --merge .../dx8fvf.cpp --dry-run` accepts no donor.
`Rva00181500Finish.cpp` passes bytes in the composition, but the link guard
refuses its new `_STLP_alloc_proxy<AngleFXInfo *, AngleFXInfo,
allocator<AngleFXInfo> >::allocate` copy because it breaks another unit's copy.
The other donors retain their independent flag and include conflicts.

The donor now specializes that proxy operation locally as dllimport/forceinline,
calling its existing allocator base with the same count and null hint. This is
the existing STLport inline-operation pattern; no alias, pin, compiler flag,
shared header, ledger identity or baseline changes. It preserves the allocation
semantics and prevents emission of the competing external function.

Verification:

- `./build.sh .../Rva00181500Finish.cpp`: 1/1 matched, the complete 78-byte
  allocate-and-copy row at 0x00181500; literal/import/float checks pass.
- `find_declared_unmatched.py`: all defined functions already matched.
- Before/after COFF comparison: all 13 retained external code definitions have
  identical bytes and relocation names/types/offsets. Exactly one external
  definition disappears: the proxy allocate method. No definition is added.
- `link_check.py` reports LINKS, 78 -> 78 bytes; `--new-variants` passes.
  Index census: 2026-11-05 15:52, `112a456a2c`. This is a preview, not a census.
- The repeated merge dry run accepts dx8fvf.cpp plus Rva00181500Finish.cpp,
  verifies 13 code rows and passes the census link guard, including the
  affected-copy check that refused the original composition.

The next step is applying that verified merge through tu_skeleton. Remaining
donors are unchanged: AngleFXInfoVectorInsertOverflow.cpp's empty flag override
costs the destination three region-default rows; StructureToppleUpdate.cpp has
ICoord2D and HMODULE declaration conflicts. No full real-link or census result
is claimed by this prerequisite.
