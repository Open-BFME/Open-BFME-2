# SpecialAbilityUpdateModuleData native lifetime declaration

Inspected base `413a3f8e1c9`, isolated `build/r20`, owner
`codex-01a1071d-root-isolated-r20`. This prerequisite corrects the registered
header; constructor/destructor adoption and the owning class fold follow
separately. No source move, queue retirement or bridge retirement is claimed.

The current constructor at `0044EB54` and destructor at `0044ECCE` both use
five nullable four-byte owning handles at `08/0C/10/14/34`. Their strings occupy
`40/44/48/BC/C0`. The registered header had flattened the handles into pointers
and the `18..24` constructor group into independent scalars. That omitted
destruction and initialization behavior required to share one declaration.

The header now shares the existing `OpaqueRefPtr` and `Rva0044EB54Fields18`
definitions from those owners. The handle's 12-byte destructor already owns
`0010F149`; no identity or alias is added. Its constructor still nulls the word
and its destructor conditionally calls `OpaqueRefCounted::Release_Ref`. No
copy/AddRef/conversion behavior or exception specification is introduced.
The 16-byte group keeps stores `1C=0`, `20=0`, `18=-1`, `24=-1`, before the
separate `28/2C` fields. It is a code-generation layout view, not recovery of an
original aggregate type/name. ModuleData remains the eight-byte base, and the
whole class remains `C8` with its native 31-slot interface.

## Native owner experiment

Prepared texts are preserved beside this note as `*-ctor.cpp.txt` and
`*-dtor.cpp.txt`. The header lane's source-restoring layout API compiled them
with each original source's flags, writing diagnostic objects under `build/`.
The original tracked `.cpp` files were restored byte for byte. The destructor
candidate supplies the source-local inline empty ModuleData teardown that
preserves Snapshot's final table restore; no shared destructor body is added.
The constructor retains every value/order, including the empty literal at C0.

Both diagnostic layouts are 200 bytes, with ModuleData at zero. Preliminary
strict code verification passes **15/15** existing owner rows, including the
378-byte constructor, 199-byte destructor, 28-byte deleting destructor, handle
destructor, handler and rowed actions. Both full EH graphs are **EXACT**.

Both diagnostic own tables have **31/31** native slots at RVA `0083F2A8`:
**62 slot instances**, including **58 complete emitted body comparisons** and
four existing external native bindings. Diagnostic symbol-map substitutions
relate only the already-proven placeholder destructor family to its proposed
name; no production ledger, pin or alias was changed. The actual owning fold
must still perform its normal row, object, source, link and commit verification.

## Current consumer verification

The owning dependency walk reaches 48 current C++ sources. With only the header
changed, `./build.sh` passes **722/722 code rows and 68 data rows**, 335 string
references and 24 float literals. The scoped ordinary preview retains
**48/48 LINKS, 40,537 -> 40,537 bytes** against the unchanged published index
`0e4b2640a1` (2026-11-13 20:08; census commit `50ce6f90bb`). This is no new census
or whole-game link claim. Review found no material issue in this prerequisite.

Machine evidence is in the adjacent JSON. Original controls, object layouts,
source-restoring probe, table proof and logs are in
`build/root-specialability-lifetime/`. Nonadopted audio callers' existing
OpaqueRefElement4 reference ABI is a separate identity boundary; do not add
conversions or value-return adapters to this header to hide it.

## Consolidation boundary

The fresh supported RousingSpeechUpdate dry run accepts zero of its two
remaining whole-file donors. The data constructor needs the native base
destructor-family fold; the trigger needs its actual shared views and the
recorded inline-lookup compiler-layout issue resolved. The original data
constructor/plain versus destructor/novtable issue must be judged after the
coherent base adoption, not by blindly changing the attribute. All current
source and ledger coverage remain in place.
