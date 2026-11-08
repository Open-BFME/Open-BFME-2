# type_info: correct source table, runtime archive selection still open

2026-11-08, root recovery seat; source base ee6718dbac. The default picker
served the 86-byte TypeInfoCopyConstructor.cpp package and refused table
RVA 0087C730 as `unsupported-selection`. The complete source was read;
normal build.sh passes both native bodies (11 and 75 bytes), and the frozen
file check finds no unmatched definitions. No source or ledger was changed.

The current compiler table is a complete 4-byte SELECT_ANY COMDAT, offset
zero, with one DIR32 relocation to `??_Etype_info@@UAEPAXI@Z` (RVA 00629048).
Retail has precisely that positive slot; the following dword is zero and
is outside this table. The inferred data-ledger size of 628 does not mean
the table has 157 slots: the planner stops after the first code pointer.
With just the source's two matched rows and its current object, the normal
planner returns already_correct=1, no bridge and no refusal.

The same bounded replay including the normal runtime archives returns one
unsupported-selection refusal. The pinned msvcrt.lib ti_inst.obj member
also defines this name, as SELECT_LARGEST (6). Its section is eight bytes:
an RTTI locator relocation at offset zero, followed by the table symbol at
offset four and a relocation to the same vector deleting destructor.
The archive candidate is deliberately included by the planner regardless
of whether it will be extracted. Its selection is checked before the
already-correct test. Changing the current source's table or flags would
leave that candidate and refusal intact.

The archive additionally defines the private assignment operator and RTTI
symbols. The two recovered source rows alone do not prove this member is
never extracted. This is an unresolved archive/provider boundary, not a
proven false reject. The useful next check is all kept providers and live
references for those remaining names, or actual extraction evidence from
the next maintained real image. A checker change requires separate proof
and normal tooling review; existing selection-6 rejection tests stand.

`proof.json` records object/member hashes, native bytes, table bindings and
both bounded plans. Independent native review confirmed the archive cause.
No complete image, global provider clearance, census gain or runtime result
is claimed. Claims were released after banking this handoff.
