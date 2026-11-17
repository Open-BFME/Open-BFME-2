# Canonical holder view in the planning update

On 2026-11-17, based on `e8e34c0e8f6`, replaced the private `Rva00575383` view in
`Rva00575723Update.cpp` with its existing canonical header. The field at +4 is a
`void *` in that contract. An explicit cast preserves the previous placeholder
pointer interpretation for the already rowed getter; no semantic type identity is inferred.

The native before/after object graphs have the same three runtime sections,
including all contents, relocation targets, external definitions, COMDAT policies
and weak bindings. The normal current object independently equals those graphs.
The original flat eight-byte view and canonical eight-byte polymorphic view retain
the pointer at +4; the old four-byte prefix padding was unused storage.

`./build.sh` passed **102/102 rows across all ten relevant units**. The supported
`link_check.py --prepare-current` then populated strict reusable dependency receipts
for that same cohort and its ordinary byte gates passed **102/102** again. The owning
`header_adopt_lane.py accept` passed with the other nine units supplied as mandatory
providers and retired exactly this consumer's queue row. Its provider context is
committed with the source and queue change. No header, contract or other source changes.

The holder still needs its full four-slot interface. This adoption emits no new
destructor or table and does not claim a bridge retirement or a working image.
The rejected lifetime alternatives and remaining prerequisites are recorded separately.

Native evidence: [object/layout proof](holder-update-canonical-20261117-root20.json).
