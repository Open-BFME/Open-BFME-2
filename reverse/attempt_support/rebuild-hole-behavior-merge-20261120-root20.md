# RebuildHoleBehavior consolidation and module-data lifetime

The pool-key and behavior destructor donors moved in two guarded merges.
The final build verified 34 function rows across RebuildHoleBehavior.cpp
and RebuildHoleBehaviorModuleDataDtor.cpp, and all five EH graphs were
exact. The scoped preview found 2,147 linked bytes, the same total as
the original four-file cohort against census 179f73d302. This evidence
covers those translation units. Whole-image verification is pending.

## Retired paths

- RebuildHoleBehaviorPoolKey.cpp moved four approved rows. The
  getModuleNameKey parent at 0x004832D7 carries cleanup 0x0078BC40 and
  handler 0x0078BC4D. The pool key at 0x00A037C4 and compiler guard at
  0x00A037C8 keep their addresses. The merged COFF uses storage class
  STATIC for the guard and relocates it to the same address. The data
  ledger still spells the old $S1 ordinal, which the shadow checker
  reports against the emitted $S6.
- RebuildHoleBehaviorDtor.cpp moved five approved rows and the distinct
  RebuildHoleBehavior::loadPostProcess fold alias. The canonical
  0x00497805 row stays with BattlePlanUpdate.cpp. At primary table
  0x00C49A74 slot 1 the merged object references the same decorated
  override, a five-byte tail jump binding UpdateModule at 0x0058B03E.
  The shadow TU audit reports A2 because the address map tracks the
  canonical row. The merge tool verifies the named alias separately.

The first consumer audit covered the range from a9dbdea3d45 through the
pool merge. The second covered the range from 753fc76c4e3 through the
behavior destructor merge. Searches found no source include, tool,
hook, workflow, registry input or build configuration referring to a
removed donor. Remaining names appear in source provenance, prior class
observations, historical ledger notes and the generated census snapshot.

## Remaining module-data donor

The 48-byte destructor at 0x0048334A and EH rows at 0x0078BC57 and
0x0078BC5F are approved for RebuildHoleBehavior.cpp. The current ordinary
merge fails C2653 after composing the donor ahead of the seed's class.
An explicit definition using its concrete leaf class adds a six-byte
leaf vptr store to the destructor at offset +0x11 under both /GX and
/EHsc. The retail destructor destroys AsciiString at +0x10 and ends by
restoring the Snapshot vptr.

The scratch composed object 2f3ac9707d024d70.obj matches all 34 rows.
Use Common/ModuleData.h with a TU-local inline base destructor, as in
RampageBehavior.cpp. Replace the private +0x04 placeholder with the
inherited tag and represent +0x10 as AsciiString. Initialize the floats
at +0x08 and +0x0C in the constructor initializer list. Leave the leaf
destructor implicit. The existing constructor and table cause VC7.1 to
emit the 48-byte destructor naturally. Its 124-byte table matches all
31 retail target identities, including the compiler weak deleting
destructor default from the slot's ??_E to the rowed ??_G at 0x0048332E.
No emission helper is required in the composed source.

The ordinary merge retains the donor's explicit destructor body.
The donor owns only that body and compiler-emitted EH rows, so it has
no rowed call that would emit the implicit body separately. The
prepared split refuses donors containing only the destination's rows,
and emit-move accepts deleting thunks rather than this complete
destructor. A supported full-donor transaction needs to replace the
explicit body and transfer the three rows atomically under the normal
byte, EH, link, provider and register checks. The donor remains separate.
ModuleDataBuildFieldParse.cpp is a separate mixed donor and was kept.
