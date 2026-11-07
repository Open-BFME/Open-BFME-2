### LINK-626: pin-only destructor bindings leave 13 names undefined in the real link

Status: Open (handoff to the active deleting-dtor identity work). Updated: 2026-11-07; ancalgonn-swarm-link.
Real links: `2d963894b9` (run 42323777563) 223 unresolved, 0 duplicates; `bbb1979380` (run 42328971153)
234 unresolved, 0 duplicates: 13 names newly missing, 2 newly resolved.

**Cause (measured).** Four commits on 2026-11-07 replaced empty private destructor bodies, which were not
retail's code at those addresses, with declarations plus a `reverse/symbols.csv` pin to the retail
destructor each deleting dtor calls: `99051e8efb`, `0b28664ee5`, `8e618085ec` and `9e1df1c621`. That is
right for code identity: the empty bodies were wrong bindings, and eleven code-identity keys retired.
But only the census link aliases a pinned name to the address's matched row (its `alias` category,
linked through `/alternatename`). `tools/exit_link.py` reads no pins, so in the real link each declared
destructor has no definition.

| missing name | referenced from | pinned retail target | matched row at that address |
|---|---|---|---|
| `??1Rva006C5930Dtor@@UAE@XZ` | `WWLib/Rva00170C0Siblings.cpp` (`??_G` 0x00118640) | 0x006C5930 | `?apply@Rva0006C5930DwordImmSetter@@QAEXXZ` (7 B; `??1DebugCmdInterface@@MAE@XZ` is pinned there too) |
| `??1Rva00120FB0Dtor@@UAE@XZ` | same (`??_G` 0x00122110) | 0x00120FB0 | `??1?$VectorClass@PAVFontCharsBuffer@@@@UAE@XZ` (render2dsentence.cpp) |
| `??1Rva00141C30Dtor@@UAE@XZ` | same (`??_G` 0x00141C10) | 0x00141C30 | `??1Rva00140C00@@UAE@XZ` (InlineDtorDeletingDtorsC03.cpp) |
| `??1Rva00155330Dtor@@UAE@XZ` | same (`??_G` 0x00156840) | 0x00155330 | `??1?$VectorClass@VModelNodeClass@HLodClass@@@@UAE@XZ` (hlod.cpp) and a folded `DynamicVectorClass` row |
| `??1Rva00156750Dtor@@UAE@XZ` | same (`??_G` 0x00157110) | 0x00156750 | `??1?$VectorClass@UAddInfoStruct@MixFileFactoryClass@@@@UAE@XZ` (mixfile.cpp) |
| `??1Rva00625800Dtor@@UAE@XZ` | same (`??_G` 0x00626D90) | 0x00625800 | `?bfmeUnhookZU@BfmeThingZU@@QAEXXZ` (BfmeOneHundredSixtyTwo.cpp) |
| `??1Rva0066C730Dtor@@UAE@XZ` | same (`??_G` 0x00663410) | 0x0066C730 | `?reset@Rva00800290Buffer@@QAEXXZ` (Fesl/util.cpp, 35 B) |
| `??1Rva0073A900Dtor@@UAE@XZ` | same (`??_G` 0x0073AAC0) | 0x0073A900 | `?bfmeDtorCDE@BfmeThingCDE@@QAEXXZ` (BfmeThingCDEDestructor.cpp) |
| `??1Rva0070A530@@UAE@XZ` | `Common/Rva006CBF40Siblings.cpp` | 0x00709B80 | `??1Rva00709B80@@UAE@XZ` (Rva006D6470Derived.cpp) |
| `??1Rva0070A560@@UAE@XZ` | same | 0x00709B80 | same |
| `??1Rva0070A590@@UAE@XZ` | same | 0x00709B80 | same |
| `??1Rva006DE320@@UAE@XZ` | `Apt/AptValue.cpp` | 0x006DE350 | `??1AptValue@@MAE@XZ` / `??1Rva006DE350@@UAE@XZ` (AptValue.cpp) |
| `??1Rva006F84C0@@UAE@XZ` | `Common/Rva006F84C0DeletingDtor.cpp` | 0x006F8460 | `??1Rva006F8460@@UAE@XZ` (Rva006F8460Dtor.cpp) |

**Two repair shapes (not started; for the identity work in progress).**
- *Derived classes, 5 names* (`Rva0070A530`, `Rva0070A560`, `Rva0070A590`, `Rva006DE320`, `Rva006F84C0`).
  Retail's scalar deleting dtor calls the base class's complete dtor directly. The source needs a shape
  in which the derived class's own destructor generates no separate body and the deleting dtor calls
  the base destructor. Per `9e1df1c621`, an implicit destructor compiled as a second copy at `/O1`, so
  this needs compiler experiments per class.
- *Owner-class reconciliation, 8 names* (`Rva00170C0Siblings.cpp`). A scalar deleting dtor belongs to the
  class whose destructor it calls, as this unit's header already records for 0x00157E60 and 0x00616490.
  Each model class becomes the class that owns the called body, with that row renamed to a destructor
  where its current name is a placeholder method (`bfmeUnhookZU`, `bfmeDtorCDE`, `apply`; `reset` lives
  in the FESL SDK's util.cpp and needs care). The `VectorClass<P*>` destructors fold, so which
  instantiation owns each deleting dtor needs its own evidence.

**Tooling finding: the push audit did not see this (corrected 2026-11-07).** The first diagnosis
blamed the census's pin aliasing; the census index shows otherwise. `tools/link_batch_audit.py` rejudges
only units whose prior census verdict is `linked`, and `Rva00170C0Siblings.cpp` was `linked: False`
(its empty destructors were `losers`/`wrong_selected`); its "provider disappeared" review line fires
only when the old verdict was not `wrong`. So the removal of wrong-but-present definitions was invisible
to it, while the real link, which ignores verdicts, still used them. The audit now reports a
**real-link loss**: a name defined before the batch, by no kept object after, still referenced by a kept
object, judged from object symbol tables alone (`real_link_losses`, report mode first). Measured by
compiling each of the four units at its parent and at the commit: the rule finds all 13 names
(8 + 3 + 1 + 1), each still referenced by its own unit.

**Handoff.** Pin-only binding of a destructor (or any referenced function) costs a real-link
definition. Until the real owner's name is spelled in source, the real link's unresolved count rises
by one per name. Prefer binding the reference to the owner row's real symbol in the same change. Not
reverted: the code-identity gain is right, and the repair is forward.

Measurement: `build/drift_review/ops/link_42323777563` and `link_42328971153` (`errors.tsv` diff).
Census confirmation: not claimed.

**Cleared, same pattern, data side (2026-11-07).** Four `symbols.csv` pins named
`?s_head@?$CategoryModuleClass@$0N@FXParticleSystem@@2PAV12@A` at 0x009FDD44, 48, 4C and 54.
Retail's export table names those addresses `?s_first@...@@0PBV12@B` (export 1863 and siblings),
`reverse/data_rows.csv` rows them under that exported spelling, and all nine consumer units read
`s_first` in source - only four header comments still said `s_head`. The real link therefore
reported each pinned name as a missing definition, which is this entry's pattern on a data
address rather than a destructor.

The pins were also plain admission violations: `pin_admission.py` states a pin must lie in an
executable section ("data pins do nothing for REL32 resolution") and must not give a second,
different name to an address that already has a real one. Both pins and the stale comments are
gone; the byte gate was unaffected, since no body resolves through a data pin, and the pin count
fell by four.

Remaining on this family: `reverse/data_ledger.csv` still carries the nine `s_head` names. That
file is tool-written from the DIR32 relocations and symbol tables of matched objects
(`tools/data_ledger.py`, "never edit by hand"), so the names persist from objects built before
the source settled on `s_first`. Whoever has a current object cache should rewrite it; this seat
did not, and a regeneration from a stale cache would be worse than leaving it. The nine
`Rva001F8*Parse.cpp` / `Rva001FA8DDParse.cpp` blocker rows should clear with it.
