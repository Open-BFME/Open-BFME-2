# Linear campaign consolidation prerequisites, 2026-11-05

Inspected revision: 593e5f243c. Owner: yasinschroeder-codex.

The fresh consolidation planner covered GameLogic/System (212 files, 53 groups).
The supported LinearCampaignManager merge probe accepted 0 of 19 donors. The
view reconciler retained no changes: six typed-layout/declspec conflicts, five
reverted reconstructions, and already-shared views. No missing-row regression
or consolidation gain is claimed.

A new concrete compiler boundary is the seed's STLport 4.6 environment:
`allocator::deallocate(pointer,size_type)` there is non-const, whereas 4.5.3
and the legacy bfmealloc shim declare it const. Rva001EC349Dtor's unused const
specialization causes C2244 when composed into the seed. Removed its three
unused allocator/proxy/base-destructor specialization declarations; retained
the vector destructor specialization the body actually calls. The complete
external `(symbol, defined)` set of its ordinary build object is unchanged.
This resolves the declaration prerequisite only; the next check is a fresh
supported merge, including all parent EH rows and provider selection.

Removed Rva001ECF66Finish's stale `present-unmatched` marker. Its actual row is
`??0Rva001ECF66@@QAE@ABV0@@Z`, 0x001ECF66, 96 bytes; the old comment spelled a
nonexistent `rva001ECF66` method. The declaration checker reports all defined
functions matched, and the normal baseline build already passed before removal.

Verification:
- `./build.sh` both changed sources: 7/7 rows exact, including five destructor
  funclets resolved through their parent's verified EH graph after label renumbering.
- `find_declared_unmatched.py` both sources: all defined functions matched.
- `link_check.py` both sources, index c95fcfcfcd (2026-11-05 05:17): both LINKS,
  204 authored bytes preserved. This is a preview, not a new census.
- No source move, pin, alias, private class or debt-key retirement.
