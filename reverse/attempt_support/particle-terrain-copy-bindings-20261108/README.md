# Rva003AE2A9 copy-table bindings, 2026-11-08

The copy/clone unit removes its three one-byte table stand-ins and refers
to existing compiler tables from ModuleTemplateCloneSlots.cpp. The opaque
class names, base-copy call, allocation size and both function signatures
are unchanged. Each native factory store independently establishes the
replacement address; no original class name or layout is newly recovered.

| Old suffix | Compiler table suffix | Native table RVA | Factory operand RVA |
|---|---|---|---|
| v0 | Rva003AC8D7Slot0 | 0081CAA4 | 003ACB3D |
| v8 | Rva003AC8D7Slot1N | 0081CAA0 | 003ACB44 |
| v10 | Rva003AC8D7Slot2 | 0081CA90 | 003ACB4B |

All three operands belong to the existing 89-byte factory at 003ACB08,
are zero-addend DIR32 references, and contain the exact native table VA.
The emitter's five rows pass strict preparation. Its compiled providers
are each only four bytes; native extents are 16/4/16. Binding them resolves
the strong stand-ins, without recovering those complete classes or tables.

Normal build.sh passes both source rows (38-byte copy and 29-byte clone)
and all five emitter rows, 7/7 total. All five factory EH graphs are exact.
Frozen-source and paired new-variant checks pass. Code bodies, relocation
positions, flags and policies agree after normalizing only the three proved
table referents. Exactly three data definitions disappear, none is added,
and all other data and undefined references are preserved. No row, source
path, pin, alias, compiler flag or new hatch changes.

The old char names have no live outside source or index consumer and no
registered data owner. Bounded replay over the affected rows, emitter and
native slot owners removes three strong-definition refusals; the same
three bridges/nine slots remain. This is a bridge prerequisite, not bridge
retirement or a new image. Preview conserves LINKS/67 plus the emitter's
356 bytes against index c885072a48 (2026-11-08 19:18).

ConstIntGetters4.cpp is held by another worker. It is neither edited nor
compiled here. Its cached six-byte getter and complete string literal
independently match native, but its full strict provider receipt is absent.
All other supporting sources have current receipts. Carry this receipt gap
into the next census/image check; the bounded replay is not full current
link closure. Full table/class recovery and real-image confirmation remain
open. No donor path, coverage, census or runtime gain is claimed.
