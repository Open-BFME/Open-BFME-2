# LinearCampaign copy-constructor header prerequisite

Base: `6c1baf9f1d`. Scope: `Rva001ECF66Finish.cpp`, retail `0x001ECF66`, 96 bytes, approved for `LinearCampaignManager.cpp`.

The supported consolidation probe rejects this donor because its handwritten primary `allocator` definition conflicts with the seed's STLport headers. Replace the primary allocator, tag and template declarations with the real STLport 4.6 header environment used by the seed. Keep the existing GeometryShape vector/base specializations and placeholder element view: this change supplies no new element identity or layout evidence. The copy loop is now an inline, noinline explicit specialization, preserving its COMDAT selection and the visible unused-tag proof needed for the constructor's stack shape. The `_Construct` specialization remains a declaration bound to the existing provider.

Verification:

- `find_declared_unmatched.py`: all defined functions already matched, before and after.
- `./build.sh Code/Libraries/Source/WWVegas/WWLib/Rva001ECF66Finish.cpp`: 1/1 matched; strings, floats and imports pass.
- Read-only comparison of baseline and rebuilt COFF objects: constructor (96 bytes) and copy helper (38 bytes) have identical bytes and relocation tuples. All external references, weak externals, aliases and includes are identical. The unused private `__false_type` constructor definition disappears; the real header emits an empty allocator destructor COMDAT instead. No alias is removed.
- `link_check.py` against index `c95fcfcfcd` (2026-11-05 05:17): LINKS, 96 -> 96 bytes. This is a prediction, not a new census result.
- Narrow register searches found no debt, hatch, header-queue or flag-override keys owned by the donor. No path moves or ledger changes in this prerequisite.

The initial broad `tu_views.py` probe retained no changes and accepted no donors. The supported merge must be rerun after committing this prerequisite; other private views, suppression/codegen differences and LINK-040's element identity remain open.
